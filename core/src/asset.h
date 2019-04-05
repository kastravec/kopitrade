#ifndef ASSET_H
#define ASSET_H

#include <QObject>

class Portfolio;
class KSymbol;

class Asset : public QObject
{
    Q_OBJECT
public:
    enum AssetType {
        Undefined = 0,
        Crypto,
        Stock,
        Index,
        ETF,
        Commodity,
        Currenncy
    };

    Q_ENUM(AssetType)
    Q_PROPERTY(int assetID READ assetID CONSTANT)
    Q_PROPERTY(int type READ type NOTIFY typeChanged)
    Q_PROPERTY(Portfolio * portfolio READ portfolio WRITE setPortfolio NOTIFY portfolioChanged)
    Q_PROPERTY(double tradePrice READ tradePrice WRITE setTradePrice NOTIFY tradePriceChanged)
    Q_PROPERTY(KSymbol * ksymbol READ ksymbol WRITE setKsymbol NOTIFY ksymbolChanged)

    explicit Asset(QObject *parent = nullptr);
    ~Asset();

    int assetID() const;
    int type() const;
    Portfolio *portfolio() const;
    void setPortfolio(Portfolio *port);
    double tradePrice() const;
    void setTradePrice(double price);

    KSymbol *ksymbol() const;
    void setKsymbol(KSymbol *symbol);

Q_SIGNALS:
    void typeChanged(int type);
    void portfolioChanged(Portfolio *portfolio);
    void tradePriceChanged(double tradePrice);
    void ksymbolChanged(KSymbol *symbol);

protected:
    void initAsset(int type, double marketPrice);
    void setType(int type);

private:
    void setID(int id);

    class Private;
    Private *m_data;
};

#endif // ASSET_H
