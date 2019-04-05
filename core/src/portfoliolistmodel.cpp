#include "portfoliolistmodel.h"

#include "portfolio.h"

#include <QModelIndex>
#include <QDebug>


PortfolioListModel *PortfolioListModel::m_instance = nullptr;
PortfolioListModel::PortfolioListModel(QObject *parent)
    :QAbstractListModel (parent)
{
}

PortfolioListModel *PortfolioListModel::instance()
{
    if(m_instance == nullptr)
        m_instance = new PortfolioListModel;

    return m_instance;
}

PortfolioListModel::~PortfolioListModel()
{

}

QHash<int, QByteArray> PortfolioListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Portfolio_ID] = "Portfolio_ID";
    roles[Portfolio_Name] = "Portfolio_Name";

    return roles;
}

int PortfolioListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_allPortfolios.count();
}

QVariant PortfolioListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
            || index.row() >= m_allPortfolios.count())
        return QVariant();

    QString portfolioName = m_allPortfoliosCache.at(index.row());
    Portfolio *portfolio = m_allPortfolios.value(portfolioName);

    switch (role) {
    case Portfolio_ID:
        return portfolio->portfolioID();
    case Portfolio_Name:
        return portfolioName;
    default:
        return QVariant();
    }

}

Portfolio *PortfolioListModel::findPortfolio(const QString &name)
{
    if(m_allPortfolios.contains(name))
        return m_allPortfolios[name];

    return nullptr;
}

Portfolio *PortfolioListModel::createAndAdd(const QString &name)
{
    if(!name.isEmpty()) {
        Portfolio *portfl = new Portfolio(this);
        portfl->setName(name);
        addPortfolio(portfl);
        return portfl;
    }

    return nullptr;
}

void PortfolioListModel::addPortfolio(Portfolio *portfolio)
{
    if(portfolio != nullptr
            && !m_allPortfolios.contains(portfolio->name())) {

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        portfolio->setID(rowCount());
        m_allPortfolios.insert(portfolio->name(), portfolio);
        m_allPortfoliosCache.append(portfolio->name());
        endInsertRows();
    }
}

void PortfolioListModel::removePortfolio(Portfolio *portfolio)
{
    if(portfolio != nullptr)
        removePortfolio(portfolio->name());
}

void PortfolioListModel::removePortfolio(const QString &name)
{
    if(m_allPortfolios.contains(name)) {
        int index = m_allPortfoliosCache.indexOf(name);
        beginRemoveRows(QModelIndex(), index, index);

        Portfolio *portfolio = m_allPortfolios.take(name);
        portfolio->deleteLater();
        m_allPortfoliosCache.removeAll(name);
        endRemoveRows();
    }
}

QList<Portfolio *> PortfolioListModel::portfolioList() const
{
    return m_allPortfolios.values();
}
