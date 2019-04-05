#ifndef KSYMBOL_H
#define KSYMBOL_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>

class KSymbol : public QObject
{
    Q_OBJECT
public:
    enum Type {
        CommonStock = 100,
        ETF,
        ADR,
        REIT,
        ClosedEndFund,
        SecondaryIssue,
        LimitedPartnership,
        Warrant,
        OpenEndedFund,
        ClosedEndedFund,
        PreferredStock,
        Comodity,
        Cryptocurreny,
        Currency,
        Index,
        Undefined = -1
    };

    enum Properties {
        SymbolId = 700,
        Symbol,
        SymbolName,
        SymbolDescription,
        Logo,
        Industry,
        Sector
    };

    Q_ENUM(Type)
    Q_ENUM(Properties)
    Q_PROPERTY(int symbolType READ symbolType NOTIFY symbolTypeChanged)
    Q_PROPERTY(int symbolID READ symbolID NOTIFY symbolIDChanged)
    Q_PROPERTY(QString symbolName READ symbolName NOTIFY symbolNameChanged)
    Q_PROPERTY(int marketCap READ marketCap NOTIFY marketCapChanged)
    Q_PROPERTY(QString exchange READ exchange NOTIFY exchangeChanged)
    Q_PROPERTY(double price READ price NOTIFY priceChanged)
    Q_PROPERTY(double dailyChangePercent READ dailyChangePercent NOTIFY dailyChangePercentChanged)
    Q_PROPERTY(QString logoUrl READ logoUrl NOTIFY logoUrlChanged)
    Q_PROPERTY(int priceIncreased READ priceIncreased NOTIFY priceIncreasedChanged)
    Q_PROPERTY(QString region READ region NOTIFY regionChanged)

    Q_PROPERTY(int orderIndex READ orderIndex WRITE setOrderIndex NOTIFY orderIndexChanged)
    Q_PROPERTY(bool cacheEnabled READ cacheEnabled WRITE setCacheEnabled NOTIFY cacheEnabledChanged)
    Q_PROPERTY(QString symbol READ symbol WRITE setSymbol NOTIFY symbolChanged)
    Q_PROPERTY(QJsonObject jsonData READ jsonData WRITE setJsonData NOTIFY jsonDataChanged)
    Q_PROPERTY(QJsonValue newJsonData READ newJsonData WRITE setNewJsonData NOTIFY newJsonDataChanged)
    Q_PROPERTY(QByteArray rawData READ rawData WRITE setRawData NOTIFY rawDataChanged)
    Q_PROPERTY(int refreshInterval READ refreshInterval WRITE setRefreshInterval NOTIFY refreshIntervalChanged)

    explicit KSymbol(QObject *parent = nullptr);
    ~KSymbol();

    int symbolID() const;
    int symbolType() const;
    QString symbolName() const;
    int marketCap() const;
    QString exchange() const;
    double price() const;
    double dailyChangePercent() const;
    QString logoUrl() const;
    int priceIncreased() const;
    QString region() const;

    int orderIndex() const;
    void setOrderIndex(int index);

    bool cacheEnabled() const;
    void setCacheEnabled(bool cached);

    void setSymbol(const QString &symbol);
    QString symbol() const;

    QJsonObject jsonData() const;
    void setJsonData(const QJsonObject &json);

    QJsonValue newJsonData() const;
    void setNewJsonData(const QJsonValue &json);

    QByteArray rawData() const;
    void setRawData(const QByteArray &data);

    void setRefreshInterval(int interval);
    int refreshInterval() const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void fetchQuote(bool refresh = false);
    Q_INVOKABLE void fetchPrice(bool refresh = false);
    Q_INVOKABLE void fetchKeyStats(bool refresh = false);
    Q_INVOKABLE void fetchFinancials(const QString &option  = QString(), bool refresh = false);
    Q_INVOKABLE void fetchEarnings(bool refresh = false);
    Q_INVOKABLE void fetchCompany(bool refresh = false);
    Q_INVOKABLE void fetchLogo(bool refresh = false);
    Q_INVOKABLE void fetchNews(const QString &option = QString(), bool refresh = false);
    Q_INVOKABLE void fetchDividends(const QString &option  = QString(), bool refresh = false);
    Q_INVOKABLE void fetchEarningsToday(bool refresh = false);
    Q_INVOKABLE void fetchRelevantSymbols(const QString &option  = QString(), bool refresh = false);
    Q_INVOKABLE void fetchIncomeStatement(const QString &option = QString(), bool refresh = false);

Q_SIGNALS:
    void symbolTypeChanged(int type);
    void symbolIDChanged(int id);
    void symbolChanged(const QString &symbol);
    void symbolNameChanged(const QString &name);
    void marketCapChanged(int marketcap);
    void exchangeChanged(const QString &exchange);
    void priceChanged(double price);
    void dailyChangePercentChanged(double change);
    void jsonDataChanged(const QJsonObject &json);
    void newJsonDataChanged(const QJsonValue &json);
    void rawDataChanged(const QByteArray &data);
    void logoUrlChanged(const QString &url);
    void refreshIntervalChanged(int interval);
    void priceIncreasedChanged(int increased);
    void regionChanged(const QString &region);

    void orderIndexChanged(int orderIndex);
    void cacheEnabledChanged(bool cacheEnabled);
    void errorResponse(int errorCode, const QByteArray &data);
    void newQuoteData(const QJsonValue &data);
    void newPriceData(const QJsonValue &data);
    void newKeyStatsData(const QJsonValue &data);
    void newFinancialsData(const QJsonValue &data);
    void newEarningsData(const QJsonValue &data);
    void newCompanyData(const QJsonValue &data);
    void newLogoData(const QJsonValue &data);
    void newNewsData(const QJsonValue &data);
    void newDividendsData(const QJsonValue &data);
    void newEarningsTodayData(const QJsonValue &data);
    void newRelevantSymbolsData(const QJsonValue &data);
    void newIncomeStatementData(const QJsonValue &data);

private Q_SLOTS:
    void newQuoteDataHandler(const QJsonValue &data);
    void newKeyStatsDataHandler(const QJsonValue &data);
    void newPriceDataHandler(const QJsonValue &data);
    void newFinancialsDataHandler(const QJsonValue &data);
    void newCompanyDataHandler(const QJsonValue &data);
    void newLogoDataHandler(const QJsonValue &data);
    void newNewsDataHandler(const QJsonValue &data);
    void newEarningsDataHandler(const QJsonValue &data);
    void newDividendsDataHandler(const QJsonValue &data);
    void newEarningsTodayDataHandler(const QJsonValue &data);
    void newRelevantSymbolsDataHandler(const QJsonValue &data);
    void newIncomeStatementDataHandler(const QJsonValue &data);
    void iexQuoteResponseDataHandler(const QJsonValue &data);
    void responseErrorHandler(int errorCode, const QByteArray &data);

private:
    bool fetchQuoteLocally();
    bool fetchKeyStatsLocally();
    bool fetchFinancialsLocally(const QString &option  = QString());
    bool fetchEarningsLocally();
    bool fetchCompanyLocally();
    bool fetchNewsLocally(const QString &option = QString());
    void fetchDividendsLocally(const QString &option  = QString());
    void fetchEarningsTodayLocally();
    void fetchRelevantSymbolsLocally(const QString &option  = QString());
    bool fetchIncomeStatementLocally(const QString &option = QString());

    void setSymbolType(int type);
    void setSymbolID(int id);
    void setPriceIncreased(int increased);
    void setLogoUrl(const QString &url);
    void setPrice(double price);
    void setDailyChangePercent(double change);

    bool checkIEXEndpointReady();

    void storeLocally(const QString &fileSuffix, const QJsonValue &data);
    QJsonObject readLocalStore(const QString &fileSuffix);
    bool clearLocalStore();

    class Private;
    Private *m_data;
};

class KSymbolProperty
{
public:
    static QByteArray Symbol;
    static QByteArray Symbol_ID;
    static QByteArray Symbol_Name;
    static QByteArray Symbol_Description;
    static QByteArray Market_Cap;
    static QByteArray Industry;
    static QByteArray Exchange;
    static QByteArray Last_Closed_Price;
    static QByteArray Logo;
    static QByteArray DailyChangePercent;
    static QByteArray Region;
    static QByteArray Type;
    static QByteArray OrderIndex;
};

#endif // KSYMBOL_H
