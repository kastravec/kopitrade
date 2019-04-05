#ifndef IEXCLOUDGLOBALS_H
#define IEXCLOUDGLOBALS_H

#include <QObject>
#include <QJsonObject>

class IEXCloudGlobals : public QObject
{
    Q_OBJECT
public:
    enum Type {
        All_Symbols = 0,
        All_Symbols_CA, //canada
        All_Symbols_GB, //great britain - london
        All_Symbols_MX, //mexico
        All_Symbols_PT, //portugal - lisbon
        All_Symbols_BE, //belgium - brussels
        All_Symbols_FR, //france - paris
        All_Symbols_IE, //ireland - dublin
        All_Symbols_NL, //Netherland - amsterdam
        All_Symbols_US, //United states - all
        All_Forex,
        ForexRate,
        Stock,
        Markets,
        Cryptocurrency,
        Undefined = -1
    };

    enum Environment {
        Sandbox = 12,
        Live,
        Unknown = -1
    };

    Q_ENUM(Type)
    Q_ENUM(Environment)

    Q_PROPERTY(int environment READ environment WRITE setEnvironment NOTIFY environmentChanged)
    Q_PROPERTY(QString publicToken READ publicToken WRITE setPublicToken NOTIFY publicTokenChanged)
    Q_PROPERTY(QString privateToken READ privateToken WRITE setPrivateToken NOTIFY privateTokenChanged)
    Q_PROPERTY(QString apiHost READ apiHost WRITE setApiHost NOTIFY apiHostChanged)
    Q_PROPERTY(QString apiSandboxHost READ apiSandboxHost WRITE setApiSandboxHost NOTIFY apiSandboxHostChanged)
    Q_PROPERTY(QString sandboxToken READ sandboxToken WRITE setSandboxToken NOTIFY sandboxTokenChanged)
    Q_PROPERTY(QString apiVersion READ apiVersion WRITE setApiVersion NOTIFY apiVersionChanged)

    Q_PROPERTY(QString globalApiHost READ globalApiHost NOTIFY globalApiHostChanged)
    Q_PROPERTY(int globalEnvironment READ globalEnvironment NOTIFY globalEnvironmentChanged)
    Q_PROPERTY(QString globalToken READ globalToken NOTIFY globalTokenChanged)

    Q_PROPERTY(QJsonObject configData READ configData WRITE setConfigData NOTIFY configDataChanged)

    static IEXCloudGlobals *instance();
    ~IEXCloudGlobals();

    int environment() const;
    void setEnvironment(int env);

    QString publicToken() const;
    void setPublicToken(const QString &token);

    QString privateToken() const;
    void setPrivateToken(const QString &token);

    QString apiHost() const;
    void setApiHost(const QString &host);

    QString apiSandboxHost() const;
    void setApiSandboxHost(const QString &sandbox);

    QString sandboxToken() const;
    void setSandboxToken(const QString &token);

    QString apiVersion() const;
    void setApiVersion(const QString &version);

    QJsonObject configData() const;
    void setConfigData(const QJsonObject &json);

    QString globalApiHost() const;
    int globalEnvironment() const;
    QString globalToken() const;

   Q_INVOKABLE void readLocalIEXConfig();
   Q_INVOKABLE void storeIEXConfigLocally();

Q_SIGNALS:
    void environmentChanged(int environment);
    void publicTokenChanged(const QString &token);
    void privateTokenChanged(const QString &token);
    void apiHostChanged(const QString &host);
    void apiSandboxHostChanged(const QString &host);
    void sandboxTokenChanged(const QString &token);
    void apiVersionChanged(const QString &version);
    void configDataChanged(const QJsonObject &config);

    void globalApiHostChanged(const QString &host);
    void globalEnvironmentChanged(int environment);
    void globalTokenChanged(const QString &token);

private:
    explicit IEXCloudGlobals(QObject *parent = nullptr);
    void setGlobalApiHost(const QString &host);
    void setGlobalEnvironment(int environment);
    void setGlobalToken(const QString &token);
    void updateGlobalVariables();

    static IEXCloudGlobals *m_instance;
    QJsonObject m_iexCloudData;

    QString m_globalApiHost;
    int m_globalEnvironment;
    QString m_globalToken;
};

class IEXCloudGlobalVariables
{
public:
    static QByteArray EnvironmentType;
    static QByteArray APIHostLive;
    static QByteArray APIHostSandbox;
    static QByteArray APILiveVersion;
    static QByteArray PublicToken;
    static QByteArray PrivateToken;
    static QByteArray SandboxToken;
};

#endif // IEXCLOUDGLOBALS_H
