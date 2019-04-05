#ifndef WATCHLISTSMODEL_H
#define WATCHLISTSMODEL_H

#include <QAbstractListModel>
#include <QJsonObject>

class WatchListSymbolModel;

class WatchListsModelBase : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_PROPERTY(WatchListSymbolModel * defaultWatchlist READ defaultWatchlist WRITE setDefaultWatchlist NOTIFY defaultWatchlistChanged)
    Q_PROPERTY(WatchListSymbolModel * activeWatchlist READ activeWatchlist NOTIFY activeWatchlistChanged)

    enum WatchListsModelDataRole {
        WatchListNameRole = Qt::UserRole + 1,
        WatchListColorPegRole,
        WatchListFavoriteRole
    };

    Q_ENUM(WatchListsModelDataRole)
    explicit WatchListsModelBase(QObject *parent = nullptr);
    ~WatchListsModelBase();

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    WatchListSymbolModel *defaultWatchlist() const;
    void setDefaultWatchlist(WatchListSymbolModel *watchlist);

    WatchListSymbolModel *activeWatchlist() const;
    void setActiveWatchlist(WatchListSymbolModel *watchlist);

    Q_INVOKABLE void setActiveWatchlist(const QString &watchlistName);
    Q_INVOKABLE void setActiveWatchlist(int index);
    Q_INVOKABLE void checkDefaultWatchlist();

    Q_INVOKABLE QJsonObject toJSON() const;
    Q_INVOKABLE bool fromJSON(const QJsonObject &json);
    Q_INVOKABLE WatchListSymbolModel *findWatchList(const QString &name);
    Q_INVOKABLE int findWatchListIndex(const QString &name);
    Q_INVOKABLE WatchListSymbolModel *createWatchlist(const QString &name);
    Q_INVOKABLE WatchListSymbolModel *createWatchlist(const QJsonObject &json);
    Q_INVOKABLE bool addWatchList(WatchListSymbolModel *findWatchList);
    Q_INVOKABLE bool removeWatchList(WatchListSymbolModel *watchListModdel, bool deleteObject = true);
    Q_INVOKABLE bool removeWatchList(const QString &name, bool deleteObject = true);
    Q_INVOKABLE WatchListSymbolModel *clone(const WatchListSymbolModel *watchlistModel);
    Q_INVOKABLE void resetData(bool deleteData = true);

    void updateWatchlistDataModel(const QString &name);

Q_SIGNALS:
    void defaultWatchlistChanged(WatchListSymbolModel *watchlist);
    void activeWatchlistChanged(WatchListSymbolModel *watchlist);

private:
    void findNextPossibleActiveWatchlist(const QString &name);

    QHash<QString, WatchListSymbolModel *> m_allWatchlistModels;
    QList<QString> m_allWatchlistNames;
    WatchListSymbolModel *m_defaultWatchlist;
    WatchListSymbolModel *m_activeWatchlist;
};

class WatchListsModel : public WatchListsModelBase
{
    Q_OBJECT
public:
    static WatchListsModel *instance();
    ~WatchListsModel();

private:
    explicit WatchListsModel(QObject *parent = nullptr);
    static WatchListsModel *m_instance;
};

#endif // WATCHLISTSMODEL_H
