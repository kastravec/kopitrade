#ifndef TRADELISTMODEL_H
#define TRADELISTMODEL_H

#include <QAbstractListModel>

class Trade;
class Portfolio;

class TradeListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum TradeListModelDataRole {
        TradeID = Qt::UserRole +1,
        TradeName
    };

    Q_ENUM(TradeListModelDataRole)
    Q_PROPERTY(Portfolio * portfolio READ portfolio WRITE setPortfolio NOTIFY portfolioChanged)

    TradeListModel(QObject *parent = nullptr);
    ~TradeListModel();

    Portfolio *portfolio() const;
    void setPortfolio(Portfolio *portfolio);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE Trade *findTrade(int id);
    Q_INVOKABLE void addTrade(Trade *trade);
    Q_INVOKABLE void removeTrade(Trade *trade);
    Q_INVOKABLE void removeTrade(int id);
    Q_INVOKABLE QList<Trade *> allTrades();

Q_SIGNALS:
    void portfolioChanged(Portfolio *portfolio);

private:
    QHash<int, Trade *> m_allTrades;
    Portfolio *m_portfolio;
};

#endif // TRADELISTMODEL_H
