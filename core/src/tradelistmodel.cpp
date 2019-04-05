#include "tradelistmodel.h"

#include "trade.h"

TradeListModel::TradeListModel(QObject *parent)
    :QAbstractListModel (parent)
{

}

TradeListModel::~TradeListModel()
{
}

Portfolio *TradeListModel::portfolio() const
{
    return m_portfolio;
}

void TradeListModel::setPortfolio(Portfolio *portfolio)
{
    if(m_portfolio != portfolio && portfolio != nullptr) {
        m_portfolio = portfolio;
        emit portfolioChanged(m_portfolio);
    }
}

QHash<int, QByteArray> TradeListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TradeListModel::TradeID] = "TradeID";
    roles[TradeListModel::TradeName] = "TradeName";

    return roles;
}

int TradeListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_allTrades.count();
}

QVariant TradeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
            || index.row() >= m_allTrades.count())
        return QVariant();

    Trade *trade = m_allTrades.value(m_allTrades.keys().at(index.row()));

    switch (role) {
    case TradeID:
        return trade->tradeID();
    case TradeName:
        return trade->name();
    default:
        return QVariant();
    }
}

Trade *TradeListModel::findTrade(int id)
{
    if(m_allTrades.contains(id))
        return m_allTrades[id];

    return nullptr;
}

void TradeListModel::addTrade(Trade *trade)
{
    if(trade != nullptr && m_portfolio != nullptr) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        emit layoutAboutToBeChanged();

        m_allTrades.insert(trade->tradeID(), trade);
        trade->setPortfolio(m_portfolio);

        endInsertColumns();
        emit layoutChanged();
    }
}

void TradeListModel::removeTrade(Trade *trade)
{
    if(trade != nullptr)
        removeTrade(trade->tradeID());
}

void TradeListModel::removeTrade(int id)
{
    if(m_allTrades.contains(id)) {
        beginRemoveRows(QModelIndex(), id, 1);

        Trade *trade = m_allTrades.take(id);
        trade->deleteLater();

        endRemoveRows();
    }
}

QList<Trade *> TradeListModel::allTrades()
{
    return m_allTrades.values();
}
