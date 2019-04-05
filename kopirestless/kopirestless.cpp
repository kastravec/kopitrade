#include "kopirestless.h"

class KopiRestLess::Private {
public:
    QString apiHost;
    QString apiUrlSuffix;
};

KopiRestLess::KopiRestLess(QObject *parent)
    : QObject(parent)
    ,m_data(new Private)
{
    m_data->apiHost = "http://api.kopitrade.net";
}

KopiRestLess::~KopiRestLess()
{
    delete m_data;
    m_data = nullptr;
}

KopiRestLess *KopiRestLess::m_instance = nullptr;
KopiRestLess *KopiRestLess::instance()
{
    if(!m_instance)
        m_instance = new KopiRestLess;

    return m_instance;
}

QString KopiRestLess::apiHost() const
{
    return m_data->apiHost;
}

void KopiRestLess::setApiHost(const QString &host)
{
    if(m_data->apiHost != host) {
        m_data->apiHost = host;
        emit apiHostChanged(host);
    }
}
