#ifndef TRADE_H
#define TRADE_H

#include <QObject>
#include <QDateTime>

class Portfolio;
class Asset;

class Trade : public QObject
{
    Q_OBJECT
public:
    enum TradeType {
        UndefinedTradeType = -1,
        Sell,
        Buy
    };

    enum AssetTradeType {
        UndefinedAssetTradeType = -1,
        CFD,
        OWNERSHIP
    };

    enum TradeStatus {
        UndefinedTradeStatus = -1,
        Closed,
        InProgress,
        Active_cfd
    };

    Q_ENUM(TradeType)
    Q_ENUM(AssetTradeType)
    Q_ENUM(TradeStatus)

    Q_PROPERTY(int tradeID READ tradeID CONSTANT)
    Q_PROPERTY(QDateTime timestamp READ timestamp CONSTANT)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(Portfolio * portfolio READ portfolio WRITE setPortfolio NOTIFY portfolioChanged)
    Q_PROPERTY(Asset * asset READ asset WRITE setAsset NOTIFY assetChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    explicit Trade(QObject *parent = nullptr, int id = -1);
    ~Trade();

    int tradeID() const;
    QDateTime timestamp() const;
    int status() const;

    Portfolio *portfolio() const;
    void setPortfolio(Portfolio *port);

    Asset *asset() const;
    void setAsset(Asset *asset);

    QString name() const;
    void setName(const QString &name);

    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

Q_SIGNALS:
    void statusChanged(int status);
    void portfolioChanged(Portfolio *portfolio);
    void assetChanged(Asset *asset);
    void nameChanged(const QString &name);

private:
    friend class TradeManager;
    void setID(int id);

    class Private;
    Private *m_data;
};

#endif // TRADE_H
