#ifndef HTTPREST_H
#define HTTPREST_H

#include <QObject>

#include <QUrlQuery>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QNetworkAccessManager>

class QHttpMultiPart;

class NetworkAccessManager : public QNetworkAccessManager
{
public:
    static NetworkAccessManager *instance();
    ~NetworkAccessManager();

private:
    NetworkAccessManager(QObject *parent = nullptr);

    static NetworkAccessManager *m_instance;
};

class HttpRest : public QObject
{
    Q_OBJECT
public:
    enum Status {
        RequestReady = 101,
        RequestRunning,
        ResponseReady,
        ResponseError,
        RequestInvalid,
        Null = -1
    };

    Q_ENUM(Status)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(QUrl baseUrl READ baseUrl WRITE setBaseUrl NOTIFY baseUrlChanged)
    Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
    Q_PROPERTY(QJsonObject urlParameters READ urlParameters WRITE setUrlParameters NOTIFY urlParametersChanged)
    Q_PROPERTY(QJsonObject httpHeaders READ httpHeaders WRITE setHttpHeaders NOTIFY httpHeadersChanged)
    Q_PROPERTY(QByteArray lastResponseData READ lastResponseData NOTIFY lastResponseDataChanged)

    explicit HttpRest(QObject *parent = nullptr);
    ~HttpRest();

    int status() const;

    QUrl baseUrl() const;
    void setBaseUrl(const QUrl &url);

    QUrl url() const;
    void setUrl(const QUrl &url);

    QJsonObject urlParameters() const;
    void setUrlParameters(const QJsonObject &param);

    QJsonObject httpHeaders() const;
    void setHttpHeaders(QJsonObject &headers);

    QByteArray lastResponseData() const;

    Q_INVOKABLE void setHttpAttribute(QNetworkRequest::Attribute attribute, const QVariant &value = QVariant());
    Q_INVOKABLE void validateHttpRequest();
    Q_INVOKABLE void get();
    Q_INVOKABLE void post(const QByteArray &data);
    Q_INVOKABLE void post(const QJsonObject &json);
    Q_INVOKABLE void postMultipart(QHttpMultiPart *parts);
    Q_INVOKABLE void put(const QByteArray &data);
    Q_INVOKABLE void putMultipart(QHttpMultiPart *parts);
    Q_INVOKABLE void patch(const QByteArray &data);
    Q_INVOKABLE void patchMultipart(QHttpMultiPart *parts);
    Q_INVOKABLE void deleteData();

Q_SIGNALS:
    void statusChanged(int status);
    void baseUrlChanged(const QUrl &url);
    void urlPrefixChanged(const QString &prefix);
    void urlChanged(const QUrl &url);
    void urlParametersChanged(QJsonObject &parameters);
    void httpHeadersChanged(QJsonObject &headers);
    void replyReady(const QByteArray &data);
    void replyError(int errorCode, const QByteArray &data);
    void sslErrors(const QList<QSslError> &errors);
    void lastResponseDataChanged(const QByteArray &data);

private Q_SLOTS:
    void networkResponseHandler();
    void networkResponseMetadataHandler();
    void networkResponseErrorHandler(int code);
    void networkResponseDownloadHandler(qint64 bytesReceived, qint64 bytesTotal);
    void networkResponseUploadHandler(qint64 bytesSent, qint64 bytesTotal);
    void networkResponseSslErrorsHandler(const QList<QSslError> &errors);

private:
    void setStatus(int status);
    void sendHttpRequest(const QString &httpVerb, const QByteArray &data = QByteArray());
    void sendMultipartRequest(const QString &httpVerb, QHttpMultiPart *httpParts);

    class Private;
    Private *m_data;
};


#endif // HTTPREST_H
