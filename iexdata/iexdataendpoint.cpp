#include "iexdataendpoint.h"
#include "httprest.h"

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class IEXDataEndpoint::Private {
public:
    int type;
    QJsonValue jsondata;
    QUrl apiUrl;
};

IEXDataEndpoint::IEXDataEndpoint(QObject *parent, int type)
    :QObject (parent)
      ,m_data(new Private)
{
    m_data->type = IEXCloudGlobals::Undefined;
    setType(type);
}

IEXDataEndpoint::~IEXDataEndpoint()
{
    delete m_data;
    m_data = nullptr;
}

int IEXDataEndpoint::type() const
{
    return m_data->type;
}

void IEXDataEndpoint::setType(int t)
{
    if(m_data->type != t){
        m_data->type = t;
        emit typeChanged(t);
    }
}

QJsonValue IEXDataEndpoint::jsonDataReceived() const
{
    return m_data->jsondata;
}

QUrl IEXDataEndpoint::apiURL() const
{
    return m_data->apiUrl;
}

void IEXDataEndpoint::setApiURL(const QUrl &url)
{
    if(m_data->apiUrl != url) {
        m_data->apiUrl = url;
        emit apiURLChanged(url);
    }
}

void IEXDataEndpoint::fetchData(const QString &options)
{
    updateApiURL();

    if(!ready())
        return;

    QString dataURL = m_data->apiUrl.url();
    dataURL.append(options);
    dataURL.append("?token=" + IEXCloudGlobals::instance()->globalToken());
    setApiURL(dataURL);
    HttpRest *rest = new HttpRest;
    rest->setBaseUrl(dataURL);
    rest->get();

    connect(rest, &HttpRest::replyReady, this, &IEXDataEndpoint::iexDataDataReply);
    connect(rest, &HttpRest::replyError, this, &IEXDataEndpoint::iexDataRequestError);
}

bool IEXDataEndpoint::ready() const
{
    if(m_data->type != IEXCloudGlobals::Undefined
        && m_data->apiUrl.isValid())
        return true;

    return false;
}

void IEXDataEndpoint::iexDataDataReply(const QByteArray &datareply)
{
    QJsonDocument jsondoc = QJsonDocument::fromJson(datareply);
    if(jsondoc.isArray()){
        m_data->jsondata = jsondoc.array();
    }else if (jsondoc.isObject()) {
        m_data->jsondata = jsondoc.object();
    } else {
        QJsonObject jsondata;
        jsondata.insert("data", QString(datareply));
        m_data->jsondata = jsondata;
    }

    emit jsonDataReceivedChanged(m_data->jsondata);
    sender()->deleteLater();
}

void IEXDataEndpoint::iexDataRequestError(int errorCode, const QByteArray &error)
{
    if(!error.isEmpty()) {
        emit errorDataReceived(errorCode, error);
    }
    sender()->deleteLater();
}

void IEXDataEndpoint::updateApiURL()
{
    //setting the endpoint based on the type
    switch (m_data->type) {
    case IEXCloudGlobals::ForexRate:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/fx/rate"));
        break;
    case IEXCloudGlobals::All_Forex:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/fx/symbols"));
        break;
    case IEXCloudGlobals::All_Symbols:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/symbols"));
        break;
    case IEXCloudGlobals::Stock:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/stock"));
        break;
    case IEXCloudGlobals::Cryptocurrency:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/crypto"));
        break;
    case IEXCloudGlobals::Markets:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/markets"));
        break;
    case IEXCloudGlobals::All_Symbols_CA:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/ca/symbols"));
        break;//canada
    case IEXCloudGlobals::All_Symbols_GB:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/gb/symbols"));
        break;//great britain - london
    case IEXCloudGlobals::All_Symbols_MX:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/mx/symbols"));
        break;//mexico
    case IEXCloudGlobals::All_Symbols_PT:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/pt/symbols"));
        break;//portugal - lisbon
    case IEXCloudGlobals::All_Symbols_BE:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/be/symbols"));
        break;//belgium - brussels
    case IEXCloudGlobals::All_Symbols_FR:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/fr/symbols"));
        break;//france - paris
    case IEXCloudGlobals::All_Symbols_IE:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/ie/symbols"));
        break;//ireland - dublin
    case IEXCloudGlobals::All_Symbols_NL:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/nl/symbols"));
        break; //Netherland - amsterdam
    case IEXCloudGlobals::All_Symbols_US:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost() + QString("/ref-data/region/us/symbols"));
        break; //United states - all
    case IEXCloudGlobals::Undefined:
    default:
        setApiURL(IEXCloudGlobals::instance()->globalApiHost());
        break;
    }
}

