#include "ksymbol.h"
#include "ksymbolmodel.h"

#include "iexdataendpoint.h"
#include "kopi.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>

#include <QDebug>

QByteArray KSymbolProperty::Symbol = "Symbol";
QByteArray KSymbolProperty::Symbol_ID = "Symbol_ID";
QByteArray KSymbolProperty::Symbol_Name = "Symbol_Name";
QByteArray KSymbolProperty::Symbol_Description = "Symbol_Description";
QByteArray KSymbolProperty::Market_Cap = "Market_Cap";
QByteArray KSymbolProperty::Industry = "Industry";
QByteArray KSymbolProperty::Exchange = "Exchange";
QByteArray KSymbolProperty::Last_Closed_Price = "Last_Closed_Price";
QByteArray KSymbolProperty::Logo = "Logo";
QByteArray KSymbolProperty::DailyChangePercent = "DailyChangePercent";
QByteArray KSymbolProperty::Region = "Region";
QByteArray KSymbolProperty::Type = "Type";
QByteArray KSymbolProperty::OrderIndex = "OrderIndex";

class KSymbol::Private
{
public:
    QJsonObject jsonData;
    QJsonValue newJsonData;
    int refreshInterval;
    bool cacheEnabled;
};

KSymbol::KSymbol(QObject *parent)
    :QObject(parent)
    ,m_data(new Private)
{
    m_data->jsonData.insert(KSymbolProperty::Symbol_ID, -1);
    m_data->jsonData.insert(KSymbolProperty::Type, -1);
    m_data->refreshInterval = -1;
    m_data->cacheEnabled = false;
}

KSymbol::~KSymbol()
{
    delete m_data;
    m_data = nullptr;
}

int KSymbol::symbolType() const
{
    return m_data->jsonData.value(KSymbolProperty::Type).toInt();
}

void KSymbol::setSymbolType(int type)
{
    if(m_data->jsonData.value(KSymbolProperty::Type).toInt() != type) {
        m_data->jsonData.insert(KSymbolProperty::Type, type);
        emit symbolTypeChanged(type);
    }
}

int KSymbol::symbolID() const
{
    return m_data->jsonData.value(KSymbolProperty::Symbol_ID).toInt();
}

void KSymbol::setSymbolID(int id)
{
    if(m_data->jsonData.value(KSymbolProperty::Symbol_ID).toInt() != id) {
        m_data->jsonData.insert(KSymbolProperty::Symbol_ID, id);
        emit symbolIDChanged(id);
    }
}

int KSymbol::marketCap() const
{
    return m_data->jsonData.value(KSymbolProperty::Market_Cap).toInt();
}

QString KSymbol::exchange() const
{
    return m_data->jsonData.value(KSymbolProperty::Exchange).toString();
}

double KSymbol::price() const
{
    return m_data->jsonData.value(KSymbolProperty::Last_Closed_Price).toDouble();
}

double KSymbol::dailyChangePercent() const
{
    return m_data->jsonData.value(KSymbolProperty::DailyChangePercent).toDouble();
}

QString KSymbol::logoUrl() const
{
    //not fetching the logo from iex servers since all logos have the same base URL
    if(symbolType() == KSymbol::CommonStock)
        return QString("https://storage.googleapis.com/iex/api/logos/") + symbol() + ".png";

//    if(!m_data->jsonData.value(KSymbolProperty::Logo).isNull())
//        return m_data->jsonData.value(KSymbolProperty::Logo).toString();

    return QString();
}

QString KSymbol::symbol() const
{
    return m_data->jsonData.value(KSymbolProperty::Symbol).toString();
}

void KSymbol::setSymbol(const QString &symbol)
{
    if(m_data->jsonData.value(KSymbolProperty::Symbol).toInt() != symbol) {
        m_data->jsonData.insert(KSymbolProperty::Symbol, symbol);
        emit symbolChanged(symbol);
    }
}

QString KSymbol::symbolName() const
{
    return m_data->jsonData.value(KSymbolProperty::Symbol_Name).toString();
}

QJsonObject KSymbol::jsonData() const
{
    return m_data->jsonData;
}

void KSymbol::setJsonData(const QJsonObject &json)
{
    if(m_data->jsonData != json) {
        m_data->jsonData = json;
        emit jsonDataChanged(m_data->jsonData);

        //setting key data / id and symbol
        setSymbol(m_data->jsonData.value(KSymbolProperty::Symbol).toString());
        setSymbolID(m_data->jsonData.value(KSymbolProperty::Symbol_ID).toInt());
        emit symbolNameChanged(m_data->jsonData.value(KSymbolProperty::Symbol_Name).toString());
        emit logoUrlChanged(m_data->jsonData.value(KSymbolProperty::Logo).toString());
//        emit priceChanged(price());
//        emit priceStringChanged(priceString());
//        emit marketCapChanged(marketCap());
//        emit exchangeChanged(exchange());
        emit rawDataChanged(rawData());
    }
}

QJsonValue KSymbol::newJsonData() const
{
    return m_data->newJsonData;
}

void KSymbol::setNewJsonData(const QJsonValue &json)
{
    if(m_data->newJsonData != json) {
        m_data->newJsonData = json;
//        emit newJsonDataChanged(json);
    }
}

QByteArray KSymbol::rawData() const
{
    QJsonDocument jsdoc(m_data->jsonData);
    return jsdoc.toJson();
}

void KSymbol::setRawData(const QByteArray &data)
{
    QJsonDocument jsdoc = QJsonDocument::fromJson(data);
    QJsonObject jsobj(jsdoc.object());
    setJsonData(jsobj);
    emit rawDataChanged(data);
}

int KSymbol::refreshInterval() const
{
    return m_data->refreshInterval;
}

int KSymbol::priceIncreased() const
{
    return m_data->jsonData.value("priceIncreased").toInt();
}

QString KSymbol::region() const
{
    return m_data->jsonData.value(KSymbolProperty::Region).toString();
}

int KSymbol::orderIndex() const
{
    return m_data->jsonData.value(KSymbolProperty::OrderIndex).toInt();
}

void KSymbol::setOrderIndex(int index)
{
    if(m_data->jsonData.value(KSymbolProperty::OrderIndex).toInt() != index) {
        m_data->jsonData.insert(KSymbolProperty::OrderIndex, index);
        emit orderIndexChanged(index);
//        emit jsonDataChanged(m_data->jsonData);
    }
}

bool KSymbol::cacheEnabled() const
{
    return m_data->cacheEnabled;
}

void KSymbol::setCacheEnabled(bool cached)
{
    if(m_data->cacheEnabled != cached) {
        m_data->cacheEnabled = cached;
        emit cacheEnabledChanged(cached);
        if(!cached)
            clearLocalStore();
    }
}

void KSymbol::refresh()
{
    fetchQuote(true);
}

void KSymbol::setRefreshInterval(int interval)
{
    if(m_data->refreshInterval != interval) {
        m_data->refreshInterval = interval;

        if(m_data->refreshInterval != -1)
            qDebug()<<"time interval" << interval;

        emit refreshIntervalChanged(interval);
    }
}

void KSymbol::fetchQuote(bool refresh)
{
    if(refresh) {
        IEXDataEndpoint *iexEndpoint = new IEXDataEndpoint(this);

        if(symbolType() == KSymbol::CommonStock) {
            iexEndpoint->setType(IEXCloudGlobals::Stock);
            iexEndpoint->fetchData(QString("/")
                                   + symbol()
                                   + QString("/quote"));
        } else if (symbolType() == KSymbol::Currency) {
            iexEndpoint->setType(IEXCloudGlobals::ForexRate);
            iexEndpoint->fetchData(QString("/")
                                   + symbol().mid(0,3)
                                   + QString("/")
                                   +symbol().mid(3,3));
        }

        connect(iexEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
                this, &KSymbol::newQuoteDataHandler, Qt::DirectConnection);
        connect(iexEndpoint, &IEXDataEndpoint::errorDataReceived,
                this, &KSymbol::errorResponse, Qt::DirectConnection);
    } else {
        if(!fetchQuoteLocally())
            fetchQuote(true);
    }
}

void KSymbol::fetchPrice(bool refresh)
{
    if(price() <= 0 || refresh) {
        IEXDataEndpoint *iexEndpoint = new IEXDataEndpoint(this);

        if(symbolType() == KSymbol::CommonStock) {
            iexEndpoint->setType(IEXCloudGlobals::Stock);
            iexEndpoint->fetchData(QString("/")
                                   + symbol()
                                   + QString("/price"));
        } else if (symbolType() == KSymbol::Currency) {
            iexEndpoint->setType(IEXCloudGlobals::ForexRate);
            iexEndpoint->fetchData(QString("/")
                                   + symbol().mid(0,3)
                                   + QString("/")
                                   +symbol().mid(3,3));
        }

        connect(iexEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
                this, &KSymbol::newPriceDataHandler, Qt::DirectConnection);
        connect(iexEndpoint, &IEXDataEndpoint::errorDataReceived,
                this, &KSymbol::errorResponse, Qt::DirectConnection);
    }
}

void KSymbol::fetchKeyStats(bool refresh)
{
    if(refresh) {
        IEXDataEndpoint *iexEndpoint = new IEXDataEndpoint(this, IEXCloudGlobals::Stock);
        iexEndpoint->fetchData(QString("/")
                               + symbol()
                               + QString("/stats"));

        connect(iexEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
                this, &KSymbol::newKeyStatsDataHandler, Qt::DirectConnection);
        connect(iexEndpoint, &IEXDataEndpoint::errorDataReceived,
                this, &KSymbol::errorResponse, Qt::DirectConnection);
    } else {
        if(!fetchKeyStatsLocally())
            fetchKeyStats(true);
    }
}

void KSymbol::fetchFinancials(const QString &option, bool refresh)
{
    if(refresh) {
        IEXDataEndpoint *iexEndpoint = new IEXDataEndpoint(this, IEXCloudGlobals::Stock);
        iexEndpoint->fetchData(QString("/")
                               + symbol()
                               + QString("/financials"));

        connect(iexEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
                this, &KSymbol::newFinancialsDataHandler, Qt::DirectConnection);
        connect(iexEndpoint, &IEXDataEndpoint::errorDataReceived,
                this, &KSymbol::errorResponse, Qt::DirectConnection);
    } else {
        if(!fetchFinancialsLocally(option))
            fetchFinancials(option, true);
    }
}

void KSymbol::fetchEarnings(bool refresh)
{

}

void KSymbol::fetchCompany(bool refresh)
{
    if(refresh) {
        IEXDataEndpoint *iexEndpoint = new IEXDataEndpoint(this, IEXCloudGlobals::Stock);
        iexEndpoint->fetchData(QString("/")
                               + symbol()
                               + QString("/company"));

        connect(iexEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
                this, &KSymbol::newCompanyDataHandler, Qt::DirectConnection);
        connect(iexEndpoint, &IEXDataEndpoint::errorDataReceived,
                this, &KSymbol::errorResponse, Qt::DirectConnection);
    } else {
        if(!fetchCompanyLocally())
            fetchCompany(true);
    }
}

void KSymbol::fetchLogo(bool refresh)
{
    if(logoUrl().isEmpty() || refresh) {
        IEXDataEndpoint *iexEndpoint = new IEXDataEndpoint(this, IEXCloudGlobals::Stock);
        iexEndpoint->setType(IEXCloudGlobals::Stock);
        iexEndpoint->fetchData(QString("/")
                               + symbol()
                               + QString("/logo"));

        connect(iexEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
                this, &KSymbol::newLogoDataHandler, Qt::DirectConnection);
        connect(iexEndpoint, &IEXDataEndpoint::errorDataReceived,
                this, &KSymbol::errorResponse, Qt::DirectConnection);
    }
}

void KSymbol::fetchNews(const QString &option, bool refresh)
{
    //    if(logoUrl().isEmpty() || refresh) {
    IEXDataEndpoint *iexEndpoint = new IEXDataEndpoint(this, IEXCloudGlobals::Stock);
    iexEndpoint->fetchData(QString("/")
                           + symbol()
                           + QString("/news"));

    connect(iexEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
            this, &KSymbol::newNewsDataHandler, Qt::DirectConnection);
    connect(iexEndpoint, &IEXDataEndpoint::errorDataReceived,
            this, &KSymbol::errorResponse, Qt::DirectConnection);
    //    }
}

void KSymbol::fetchDividends(const QString &option, bool refresh)
{

}

void KSymbol::fetchEarningsToday(bool refresh)
{

}

void KSymbol::fetchRelevantSymbols(const QString &option, bool refresh)
{

}

void KSymbol::fetchIncomeStatement(const QString &option, bool refresh)
{
    if(refresh) {
        IEXDataEndpoint *iexEndpoint = new IEXDataEndpoint(this, IEXCloudGlobals::Stock);
        iexEndpoint->fetchData(QString("/")
                               + symbol()
                               + QString("/income"));

        connect(iexEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
                this, &KSymbol::newIncomeStatementDataHandler, Qt::DirectConnection);
        connect(iexEndpoint, &IEXDataEndpoint::errorDataReceived,
                this, &KSymbol::errorResponse, Qt::DirectConnection);
    } else {
        if(!fetchIncomeStatementLocally(option))
            fetchIncomeStatement(option, true);
    }
}

void KSymbol::newQuoteDataHandler(const QJsonValue &data)
{
    setNewJsonData(data);
    if(symbolType() == KSymbol::CommonStock) {
        setDailyChangePercent(data.toObject().value("changePercent").toDouble());
        setPrice(data.toObject().value("latestPrice").toDouble());
    } else if (symbolType() == KSymbol::Currency) {
        setPrice(data.toObject().value("rate").toDouble());
    }

    emit newQuoteData(data);
    emit jsonDataChanged(m_data->jsonData);

    storeLocally("-quote", m_data->newJsonData);
    sender()->deleteLater();
}

void KSymbol::newKeyStatsDataHandler(const QJsonValue &data)
{
    if(data.isNull()) {
        sender()->deleteLater();
        return;
    }

    setNewJsonData(data);
    emit newKeyStatsData(data);

    storeLocally("-keystats", m_data->newJsonData);
    sender()->deleteLater();
}

void KSymbol::newPriceDataHandler(const QJsonValue &data)
{
    QString datavalue = data.toObject().value("data").toString();
    setPrice(datavalue.toDouble());
    setNewJsonData(data);
    emit newPriceData(data);
    sender()->deleteLater();
}

void KSymbol::newFinancialsDataHandler(const QJsonValue &data)
{
    setNewJsonData(data);
    emit newFinancialsData(data);
    storeLocally("-financials", m_data->newJsonData);
    sender()->deleteLater();
}

void KSymbol::newCompanyDataHandler(const QJsonValue &data)
{
    setNewJsonData(data);
    emit newCompanyData(data);
    storeLocally("-company", m_data->newJsonData);
    sender()->deleteLater();
}

void KSymbol::newLogoDataHandler(const QJsonValue &data)
{
    setNewJsonData(data);
    setLogoUrl(data.toObject().value("url").toString());
    emit newLogoData(data);
    sender()->deleteLater();
}

void KSymbol::newNewsDataHandler(const QJsonValue &data)
{
    setNewJsonData(data);
    emit newNewsData(data);
    sender()->deleteLater();
}

void KSymbol::newEarningsDataHandler(const QJsonValue &data)
{

}

void KSymbol::newDividendsDataHandler(const QJsonValue &data)
{

}

void KSymbol::newEarningsTodayDataHandler(const QJsonValue &data)
{

}

void KSymbol::newRelevantSymbolsDataHandler(const QJsonValue &data)
{

}

void KSymbol::newIncomeStatementDataHandler(const QJsonValue &data)
{
    setNewJsonData(data);
    emit newIncomeStatementData(data);
    storeLocally("-income", m_data->newJsonData);
    sender()->deleteLater();
}

void KSymbol::responseErrorHandler(int errorCode, const QByteArray &data)
{
    qDebug()<<"ERROR DATA FETCHING : " << symbol() << errorCode << data;
    emit errorResponse(errorCode, data);
    sender()->deleteLater();
}

bool KSymbol::fetchQuoteLocally()
{
    QJsonObject jsdata = readLocalStore("-quote");
    if(!jsdata.isEmpty()) {
        setNewJsonData(jsdata);
        emit newQuoteData(m_data->newJsonData);
        return true;
    }

    return false;
}

bool KSymbol::fetchKeyStatsLocally()
{
    QJsonObject jsdata = readLocalStore("-keystats");
    if(!jsdata.isEmpty()) {
        setNewJsonData(jsdata);
        emit newKeyStatsData(m_data->newJsonData);
        return true;
    }

    return false;
}

bool KSymbol::fetchFinancialsLocally(const QString &option)
{
    QJsonObject jsdata = readLocalStore("-financials");
    if(!jsdata.isEmpty()) {
        setNewJsonData(jsdata);
        emit newFinancialsData(m_data->newJsonData);
        return true;
    }

    return false;
}

bool KSymbol::fetchCompanyLocally()
{
    QJsonObject jsdata = readLocalStore("-company");
    if(!jsdata.isEmpty()) {
        setNewJsonData(jsdata);
        emit newCompanyData(m_data->newJsonData);
        return true;
    }

    return false;
}

bool KSymbol::fetchIncomeStatementLocally(const QString &option)
{
    QJsonObject jsdata = readLocalStore("-income");
    if(!jsdata.isEmpty()) {
        setNewJsonData(jsdata);
        emit newIncomeStatementData(m_data->newJsonData);
        return true;
    }

    return false;
}

void KSymbol::setPriceIncreased(int increased)
{
    if(m_data->jsonData.value("priceIncreased").toInt() != increased) {
        m_data->jsonData.insert("priceIncreased", increased);
        emit priceIncreasedChanged(increased);
    }
}

void KSymbol::iexQuoteResponseDataHandler(const QJsonValue &data)
{
    setNewJsonData(data);
    sender()->deleteLater();
}


void KSymbol::setLogoUrl(const QString &url)
{
    if(m_data->jsonData.value(KSymbolProperty::Logo).toString() != url) {
        m_data->jsonData.insert(KSymbolProperty::Logo, url);
        emit logoUrlChanged(url);
        emit jsonDataChanged(m_data->jsonData);
    }
}

void KSymbol::setPrice(double price)
{
    double lastprice = m_data->jsonData.value(KSymbolProperty::Last_Closed_Price).toDouble();

    if( lastprice != price) {
        if(lastprice > price)
            setPriceIncreased(0);
        else
            setPriceIncreased(1);

        m_data->jsonData.insert(KSymbolProperty::Last_Closed_Price, price);
        emit priceChanged(price);
    } else {
        setPriceIncreased(-1);
    }
}

void KSymbol::setDailyChangePercent(double change)
{
    double lastChange = m_data->jsonData.value(KSymbolProperty::DailyChangePercent).toDouble();
    if(lastChange != change *100) {
        m_data->jsonData.insert(KSymbolProperty::DailyChangePercent, change*100);
        emit dailyChangePercentChanged(change *100);
    }
}

void KSymbol::storeLocally(const QString &fileSuffix, const QJsonValue &data)
{
    if(m_data->cacheEnabled) {
        QDir pwdir(Kopi::instance()->localStorePath());
        QString cacheFilePath = Kopi::instance()->localStorePath() + "/cache/stocks/" + symbol();
        if(!pwdir.exists(cacheFilePath))
            pwdir.mkdir(cacheFilePath);

        QFile keystatsFile(cacheFilePath + "/" + symbol() + fileSuffix + ".json");
        if(keystatsFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&keystatsFile);
            QJsonDocument jsDoc(data.toObject());
            stream <<jsDoc.toJson();
            keystatsFile.close();
        }
    }
}

QJsonObject KSymbol::readLocalStore(const QString &fileSuffix)
{
    QFile file(Kopi::instance()->localStorePath() + "/cache/stocks/" + symbol() + "/" + symbol() +fileSuffix + ".json");
    if(file.exists() && file.open(QIODevice::ReadOnly)) {
        QJsonDocument jsDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
        return jsDoc.object();
    }

    return QJsonObject();
}

bool KSymbol::clearLocalStore()
{
    QDir pwdir(Kopi::instance()->localStorePath() + "/cache/stocks/" + symbol());
    bool cleared = pwdir.removeRecursively();
    return cleared;
}
