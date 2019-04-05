#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <QObject>
#include <QQmlListProperty>
#include <QAbstractItemModel>

class Asset;
class Trade;
class AssetListModel;
class TradeListModel;

class Portfolio : public QObject
{
    Q_OBJECT
public:

    enum Type {
        Test_Live = 22,
        Test_Virtual,
        Test_Demo,
        Undefined = -1
    };

    Q_PROPERTY(int portfolioID READ portfolioID CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(AssetListModel * assetsModel READ assetsModel WRITE setAssetsModel NOTIFY assetsModelChanged)
    Q_PROPERTY(TradeListModel * tradesModel READ tradesModel WRITE setTradesModel NOTIFY tradesModelChanged)

    explicit Portfolio(QObject *parent = nullptr, int portfolioID = -1);
    ~Portfolio();

    int portfolioID() const;

    QString name() const;
    void setName(const QString &name);

    int type() const;
    void setType(int type);

    AssetListModel *assetsModel() const;
    void setAssetsModel(AssetListModel *model);

    TradeListModel *tradesModel() const;
    void setTradesModel(TradeListModel *model);

    Q_INVOKABLE void addTrade(Trade *trade);
    Q_INVOKABLE void addAsset(Asset *asset);

Q_SIGNALS:
    void assetsModelChanged(QAbstractItemModel *model);
    void tradesModelChanged(QAbstractItemModel *model);
    void nameChanged(QString &name);
    void typeChanged(int type);

protected:
    friend class PortfolioListModel;

    void setID(int portfolioID);
    void initPortfolio(int id);

private:
    class Private;
    Private *m_data;
};

#endif // PORTFOLIO_H
