#include "httprest.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QDebug>

NetworkAccessManager *NetworkAccessManager::m_instance = nullptr;
NetworkAccessManager *NetworkAccessManager::instance()
{
    if(m_instance == nullptr)
        m_instance = new NetworkAccessManager;

    return m_instance;
}

NetworkAccessManager::~NetworkAccessManager()
{
}

NetworkAccessManager::NetworkAccessManager(QObject *parent)
    :QNetworkAccessManager(parent)
{
}

class HttpRest::Private
{
public:
    int status;
    QUrl baseUrl;
    QJsonObject urlParameters;
    QJsonObject httpHeaders;
    QHash<int, QVariant> httpAttributes;
    QUrlQuery urlQuery;
    QNetworkRequest httpRequest;
    QNetworkReply *httpResponse;
    NetworkAccessManager *networkAccessManager;
    QByteArray lastResponseData;
};

HttpRest::HttpRest(QObject *parent)
    :QObject(parent)
    ,m_data(new Private)
{
    m_data->baseUrl = QString();
    m_data->status = Null;
    m_data->httpResponse = nullptr;
    m_data->networkAccessManager = NetworkAccessManager::instance();
    m_data->networkAccessManager->setRedirectPolicy(QNetworkRequest::SameOriginRedirectPolicy);

    QJsonObject headers;
    headers.insert(QString("Content-Type"), QJsonValue(QString("application/json")));
    headers.insert(QString("Accept-Type"), QJsonValue(QString("application/json")));
    setHttpHeaders(headers);
}

HttpRest::~HttpRest()
{
    delete m_data;
    m_data = nullptr;
}

int HttpRest::status() const
{
    return m_data->status;
}

void HttpRest::setStatus(int status)
{
    if(m_data->status != status) {
        m_data->status = status;

        if(m_data->status == RequestInvalid) {
            if(m_data->httpResponse)
                m_data->httpResponse->deleteLater();
        }
        emit statusChanged(m_data->status);
    }
}

QUrl HttpRest::baseUrl() const
{
    return m_data->baseUrl;
}

void HttpRest::setBaseUrl(const QUrl &url)
{
    if(m_data->baseUrl != url) {
        m_data->baseUrl = url;
        emit baseUrlChanged(m_data->baseUrl);
    }
}

QUrl HttpRest::url() const
{
    return m_data->httpRequest.url();
}

void HttpRest::setUrl(const QUrl &url)
{
    if(m_data->httpRequest.url() != url ) {
        m_data->httpRequest.setUrl(url);
        emit urlChanged(m_data->httpRequest.url());
    }
}

QJsonObject HttpRest::urlParameters() const
{
    return m_data->urlParameters;
}

void HttpRest::setUrlParameters(const QJsonObject &param)
{
    m_data->urlParameters = param;
    for(int i=0; i<m_data->urlParameters.count(); ++i) {
        m_data->urlQuery.addQueryItem(m_data->urlParameters.keys()[i],
                                      m_data->urlParameters.value(m_data->urlParameters.keys()[i]).toString());
    }

    emit urlParametersChanged(m_data->urlParameters);
}

QJsonObject HttpRest::httpHeaders() const
{
    return m_data->httpHeaders;
}

void HttpRest::setHttpHeaders(QJsonObject &headers)
{
    m_data->httpHeaders = headers;

    QString key;
    for(int i=0; i<m_data->httpHeaders.count(); ++i) {
        key = m_data->httpHeaders.keys()[i];
        m_data->httpRequest.setRawHeader(key.toLatin1(), m_data->httpHeaders.value(key).toString().toLatin1());
    }

    emit httpHeadersChanged(m_data->httpHeaders);
}

QByteArray HttpRest::lastResponseData() const
{
    return m_data->lastResponseData;
}

void HttpRest::setHttpAttribute(QNetworkRequest::Attribute attribute, const QVariant &value)
{
    //TODO check validity of attribute values
    m_data->httpRequest.setAttribute(attribute, value);

    if(value.isNull())
        m_data->httpAttributes.remove(attribute);
    else
        m_data->httpAttributes[attribute] = value;

}

/**
 * @brief HttpRest::validateHttpRequest
 *
 * Call this function each to check and validate your http request.
 * This function is called by Risip on each network request.
 */
void HttpRest::validateHttpRequest()
{
    //check if base url is not set
    if(m_data->baseUrl.isEmpty()) {
        setStatus(RequestInvalid);
        return;
    }

    //setting the url query first
    //check if url is valid and then setting the url if valid
    if(!m_data->urlQuery.isEmpty())
        m_data->baseUrl.setQuery(m_data->urlQuery);

    if(!m_data->baseUrl.isValid()) {
        setStatus(RequestInvalid);
        return;
    }

    setUrl(m_data->baseUrl);
    setStatus(RequestReady); //MUST set this in order for a request to succeed
}

void HttpRest::get()
{
    sendHttpRequest(QString("GET"));
}

void HttpRest::post(const QByteArray &data)
{
    sendHttpRequest(QString("POST"), data);
}

void HttpRest::post(const QJsonObject &json)
{
    QJsonDocument jsondata(json);
    post(jsondata.toJson());
}

void HttpRest::postMultipart(QHttpMultiPart *parts)
{
    sendMultipartRequest(QString("POST"), parts);
}

void HttpRest::put(const QByteArray &data)
{
    sendHttpRequest(QString("PUT"), data);
}

void HttpRest::putMultipart(QHttpMultiPart *parts)
{
    sendMultipartRequest(QString("PUT"), parts);
}

void HttpRest::patch(const QByteArray &data)
{
    sendHttpRequest(QString("PATCH"), data);
}

void HttpRest::patchMultipart(QHttpMultiPart *parts)
{
    sendMultipartRequest(QString("PATCH"), parts);
}

void HttpRest::deleteData()
{
    sendHttpRequest(QString("DELETE"));
}

/**
 * @brief HttpRest::sendHttpRequest
 * @param httpVerb the HTTP verb for the request, i.e. GET, POST, etc
 * @param data any data to be sent, i.e. for a POST type of requests
 *
 * Internal API.
 */
void HttpRest::sendHttpRequest(const QString &httpVerb, const QByteArray &data)
{
    if(httpVerb.isEmpty())
        return;

    //always validating request
    validateHttpRequest();

    if(m_data->status == RequestReady) {
        if(httpVerb == QString("GET"))
            m_data->httpResponse = m_data->networkAccessManager->get(m_data->httpRequest);
        else if(httpVerb == QString("POST"))
            m_data->httpResponse = m_data->networkAccessManager->post(m_data->httpRequest, data);
        else if(httpVerb == QString("PUT"))
            m_data->networkAccessManager->put(m_data->httpRequest, data);
        else if(httpVerb == QString("PATCH"))
            m_data->networkAccessManager->sendCustomRequest(m_data->httpRequest, QByteArray("PATCH"));
        else if(httpVerb == QString("DELETE"))
            m_data->networkAccessManager->deleteResource(m_data->httpRequest);
        else {
            //esle there is no proper HTTP verb set so simply update status and return;
            setStatus(RequestInvalid);
            return;
        }

        connect(m_data->httpResponse, &QNetworkReply::finished,
                this, &HttpRest::networkResponseHandler, Qt::DirectConnection);
        connect(m_data->httpResponse, &QNetworkReply::metaDataChanged,
                this, &HttpRest::networkResponseMetadataHandler, Qt::DirectConnection);
        connect(m_data->httpResponse, &QNetworkReply::sslErrors,
                this, &HttpRest::networkResponseSslErrorsHandler, Qt::DirectConnection);
        connect(m_data->httpResponse, &QNetworkReply::downloadProgress,
                this, &HttpRest::networkResponseDownloadHandler, Qt::DirectConnection);
        connect(m_data->httpResponse, &QNetworkReply::uploadProgress,
                this, &HttpRest::networkResponseUploadHandler, Qt::DirectConnection);

        //updating status
        setStatus(RequestRunning);
    }
}

/**
 * @brief HttpRest::sendMultipartRequest
 * @param httpVerb
 * @param httpParts
 *
 * Internal API.
 *
 * Same as sendHttpRequest but for Multi HTTP parts.
 *
 */
void HttpRest::sendMultipartRequest(const QString &httpVerb, QHttpMultiPart *httpParts)
{
    if(httpVerb.isEmpty())
        return;

    validateHttpRequest();
}

/**
 * @brief HttpRest::networkResponseHandler
 *
 * Internal API.
 *
 * Handling the response from a request. This is connected to the QNetworkReply::finished signal.
 */
void HttpRest::networkResponseHandler()
{
    m_data->lastResponseData = m_data->httpResponse->readAll();
    if(m_data->httpResponse->error() == QNetworkReply::NoError) {
        emit replyReady(m_data->lastResponseData);
        setStatus(ResponseReady);
    } else {
        emit replyError(m_data->httpResponse->error(), m_data->lastResponseData);
        setStatus(ResponseError);
    }

    emit lastResponseDataChanged(m_data->lastResponseData);

    //closing and deleting the finished network resposne.
    m_data->httpResponse->close();
    m_data->httpResponse->deleteLater();
}

/**
 * @brief HttpRest::networkResponseMetadataHandler
 *
 * Internal API.
 */
void HttpRest::networkResponseMetadataHandler()
{
//    qDebug()<<"HTTP REPLY METADATA: " <<m_data->httpResponse->rawHeaderList();
}

void HttpRest::networkResponseErrorHandler(int code)
{
//    qDebug()<<"HTTP RESPONSE ERROR: " << code;
//    emit replyError(code);
}

void HttpRest::networkResponseDownloadHandler(qint64 bytesReceived, qint64 bytesTotal)
{
//    qDebug()<<"HTTP DOWNLOAD PROGRESS: " << bytesReceived << bytesTotal;
}

void HttpRest::networkResponseUploadHandler(qint64 bytesSent, qint64 bytesTotal)
{
//    qDebug()<<"HTTP UPLOAD PROGRESS: " <<bytesSent <<bytesTotal;
}

void HttpRest::networkResponseSslErrorsHandler(const QList<QSslError> &errors)
{
    emit sslErrors(errors);
}
