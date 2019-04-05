#include "assetlistmodel.h"

#include "portfolio.h"
#include "asset.h"
#include "ksymbol.h"

AssetListModel::AssetListModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

AssetListModel::~AssetListModel()
{

}

Portfolio *AssetListModel::portfolio() const
{
    return m_portfolio;
}

void AssetListModel::setPortfolio(Portfolio *portfolio)
{
    if(m_portfolio != portfolio && portfolio != nullptr) {
        m_portfolio = portfolio;
        emit portfolioChanged(m_portfolio);
    }
}

QHash<int, QByteArray> AssetListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AssetID] = "AssetID";
    roles[AssetName] = "AssetName";

    return roles;
}

int AssetListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_allAssets.count();
}

QVariant AssetListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
        || index.row() >= m_allAssets.count())
        return QVariant();

    Asset *asset = m_allAssets.value(m_allAssets.keys().at(index.row()));

    switch (role) {
    case AssetID:
        return asset->assetID();
    case AssetName:
        return asset->ksymbol()->symbolName();
    default:
        return QVariant();
    }
}

void AssetListModel::addAsset(Asset *asset)
{
    if(asset != nullptr && m_portfolio != nullptr) {

        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        m_allAssets.insert(asset->assetID(), asset);
        asset->setPortfolio(m_portfolio);

        endInsertColumns();
    }
}

void AssetListModel::removeAsset(Asset *asset)
{
    if(asset != nullptr)
        removeAsset(asset->assetID());
}

void AssetListModel::removeAsset(int id)
{
    if(m_allAssets.contains(id)) {
        beginRemoveRows(QModelIndex(), id, 1);

        Asset *asset = m_allAssets.take(id);
        asset->deleteLater();

        endRemoveRows();
    }
}

QList<Asset *> AssetListModel::allAssets() const
{
    return m_allAssets.values();
}
