#ifndef ASSETLISTMODEL_H
#define ASSETLISTMODEL_H

#include <QAbstractListModel>

class Asset;
class Portfolio;

class AssetListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AssetListModelDataRole {
        AssetID = Qt::UserRole +1,
        AssetName
    };

    Q_ENUM(AssetListModelDataRole)

    Q_PROPERTY(Portfolio * portfolio READ portfolio WRITE setPortfolio NOTIFY portfolioChanged)

    AssetListModel(QObject *parent = nullptr);
    ~AssetListModel();

    Portfolio *portfolio() const;
    void setPortfolio(Portfolio *portfolio);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void addAsset(Asset *asset);
    Q_INVOKABLE void removeAsset(Asset *asset);
    Q_INVOKABLE void removeAsset(int id);
    Q_INVOKABLE QList<Asset *> allAssets() const;

Q_SIGNALS:
    void portfolioChanged(Portfolio *portfolio);

private:
    QHash<int, Asset *> m_allAssets;
    Portfolio *m_portfolio;
};

#endif // ASSETLISTMODEL_H
