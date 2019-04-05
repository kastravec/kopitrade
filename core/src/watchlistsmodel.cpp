#include "watchlistsmodel.h"
#include "watchlistsymbolmodel.h"

#include "ksymbol.h"
#include <QDebug>

WatchListsModelBase::WatchListsModelBase(QObject *parent)
    : QAbstractListModel (parent)
    ,m_defaultWatchlist(new WatchListSymbolModel(this, QString("my watchlist")))
    ,m_activeWatchlist(nullptr)
{
}

WatchListsModelBase::~WatchListsModelBase()
{

}

QHash<int, QByteArray> WatchListsModelBase::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[WatchListNameRole] = "WatchListNameRole";
    roles[WatchListColorPegRole] = "WatchListColorPegRole";
    roles[WatchListFavoriteRole] = "WatchListFavoriteRole";
    return roles;
}

int WatchListsModelBase::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_allWatchlistNames.count();
}

QVariant WatchListsModelBase::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
            || index.row() >= m_allWatchlistNames.count())
        return QVariant();

    QString watchlistName = m_allWatchlistNames.at(index.row());
    WatchListSymbolModel *watchlist = m_allWatchlistModels.value(watchlistName);

    switch (role) {
    case WatchListNameRole:
        if(watchlist)
            return watchlistName;
        else
            return QVariant();
    case WatchListFavoriteRole:
        return watchlist->favoriteMark();
    case WatchListColorPegRole:
        return watchlist->colorPeg();
    default:
        return QVariant();
    }
}

WatchListSymbolModel *WatchListsModelBase::defaultWatchlist() const
{
    return m_defaultWatchlist;
}

void WatchListsModelBase::setDefaultWatchlist(WatchListSymbolModel *watchlist)
{
    if(m_defaultWatchlist != watchlist) {
        m_defaultWatchlist = watchlist;
        emit defaultWatchlistChanged(watchlist);
    }
}

WatchListSymbolModel *WatchListsModelBase::activeWatchlist() const
{
    return m_activeWatchlist;
}

void WatchListsModelBase::setActiveWatchlist(const QString &watchlistName)
{
    WatchListSymbolModel *watchlist = findWatchList(watchlistName);
    if(!watchlist)
        return;

    if(!watchlistName.isEmpty()) {
        setActiveWatchlist(watchlist);
    }
}

void WatchListsModelBase::setActiveWatchlist(int index)
{
    if( m_allWatchlistNames.count() > index && index > -1)
        setActiveWatchlist(m_allWatchlistNames.at(index));
}

void WatchListsModelBase::setActiveWatchlist(WatchListSymbolModel *watchlist)
{
    if(m_activeWatchlist != watchlist) {
        m_activeWatchlist = watchlist;
        emit activeWatchlistChanged(watchlist);
    }
}

void WatchListsModelBase::checkDefaultWatchlist()
{
    if(rowCount() <= 0) {
        WatchListSymbolModel * watchlist = createWatchlist("my watchlist");
        watchlist->setFavoriteMark(true);
        setActiveWatchlist(watchlist);
    } else {
    }
}

QJsonObject WatchListsModelBase::toJSON() const
{
    QJsonObject jsonObject;
    QJsonArray jsonarray;

    WatchListSymbolModel *watchlist = nullptr;

    for (int i=0; i<m_allWatchlistModels.count(); ++i) {
        QJsonObject watchlistJsonObject;
        watchlist = m_allWatchlistModels.value(m_allWatchlistNames.at(i));
        watchlistJsonObject.insert("name", watchlist->watchlistName());
        watchlistJsonObject.insert("favoriteMark", watchlist->favoriteMark());
        watchlistJsonObject.insert("symbols", watchlist->toJsonArray());
        jsonarray.append(watchlistJsonObject);
    }

    if(m_activeWatchlist)
        jsonObject.insert("activeWatchlist", m_activeWatchlist->watchlistName());
    else
        jsonObject.insert("activeWatchlist", "my watchlist");

    jsonObject.insert("watchlists", jsonarray);

    return jsonObject;
}

bool WatchListsModelBase::fromJSON(const QJsonObject &json)
{
    if(!json.isEmpty()) {
        QJsonArray watchlistsArray = json.value("watchlists").toArray();

        for (int i = 0; i < watchlistsArray.count(); ++i) {
            QJsonObject jsobj = watchlistsArray.at(i).toObject();
            createWatchlist(jsobj);
        }

        setActiveWatchlist(json.value("activeWatchlist").toString());
        return true;
    }

    return false;
}

WatchListSymbolModel *WatchListsModelBase::findWatchList(const QString &name)
{
    if(!name.isEmpty() && m_allWatchlistNames.contains(name)) {
        return m_allWatchlistModels.value(name);
    }

    return nullptr;
}

int WatchListsModelBase::findWatchListIndex(const QString &name)
{
    return m_allWatchlistNames.indexOf(name);
}

WatchListSymbolModel *WatchListsModelBase::createWatchlist(const QString &name)
{
    WatchListSymbolModel *watchlist = nullptr;
    if(!name.isEmpty()) {
        watchlist = new WatchListSymbolModel(this, name);
        if(!addWatchList(watchlist)) {
            delete watchlist;
            watchlist = nullptr;
        }
    }

    return watchlist;
}

WatchListSymbolModel *WatchListsModelBase::createWatchlist(const QJsonObject &json)
{
    WatchListSymbolModel *watchlist = nullptr;
    if(!json.isEmpty()) {
        QString watchlistName = json.value("name").toString();
        if(!watchlistName.isEmpty()) {
            watchlist = createWatchlist(watchlistName);
            if(watchlist) {
                watchlist->setFavoriteMark(json.value("favoriteMark").toBool());
                watchlist->fromJsonArray(json.value("symbols").toArray());
            }
        }
    }

    return watchlist;
}

bool WatchListsModelBase::addWatchList(WatchListSymbolModel *watchListModel)
{
    if(watchListModel && !m_allWatchlistModels.contains(watchListModel->watchlistName())) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_allWatchlistNames.append(watchListModel->watchlistName());
        m_allWatchlistModels.insert(watchListModel->watchlistName(), watchListModel);
        endInsertRows();
        return true;
    }

    return false;
}

bool WatchListsModelBase::removeWatchList(WatchListSymbolModel *watchListModdel, bool deleteObject)
{
    if(watchListModdel)
        return removeWatchList( watchListModdel->watchlistName(), deleteObject);

    return false;
}

bool WatchListsModelBase::removeWatchList(const QString &name, bool deleteObject)
{
    if(!name.isEmpty() && m_allWatchlistNames.contains(name)) {
        if(m_activeWatchlist->watchlistName() == name)
            findNextPossibleActiveWatchlist(name);

        int rowpos = m_allWatchlistNames.indexOf(name);
        beginRemoveRows(QModelIndex(), rowpos, rowpos);
        if(deleteObject)
            m_allWatchlistModels.take(name)->deleteLater();
        else
            m_allWatchlistModels.remove(name);

        m_allWatchlistNames.removeAll(name);
        endRemoveRows();
        checkDefaultWatchlist();
        return true;
    }

    return false;
}

WatchListSymbolModel *WatchListsModelBase::clone(const WatchListSymbolModel *watchlistModel)
{
    WatchListSymbolModel *watchlist = nullptr;

    return watchlist;
}

void WatchListsModelBase::resetData(bool deleteData)
{
    beginResetModel();

    for (int i = 0; i < m_allWatchlistModels.count(); ++i) {
        if(deleteData)
            m_allWatchlistModels.take(m_allWatchlistModels.keys().at(i))->deleteLater();
        else
            m_allWatchlistModels.remove(m_allWatchlistModels.keys().at(i));
    }

    m_allWatchlistModels.clear();
    m_allWatchlistNames.clear();
    resetInternalData();
    endResetModel();
}

void WatchListsModelBase::updateWatchlistDataModel(const QString &name)
{
    int rowpos = m_allWatchlistNames.indexOf(name);
    QModelIndex indx = index(rowpos);
    QVector<int> rols;
    rols<<WatchListFavoriteRole;
    emit dataChanged(indx,indx, rols);
}

void WatchListsModelBase::findNextPossibleActiveWatchlist(const QString &name)
{
    QList<WatchListSymbolModel*> list = m_allWatchlistModels.values();
    for(int i=0; i<list.count(); ++i) {
        if(list[i]->watchlistName() != name)
            setActiveWatchlist(list[i]);
    }
}

WatchListsModel *WatchListsModel::m_instance = nullptr;
WatchListsModel *WatchListsModel::instance()
{
    if(!m_instance)
        m_instance = new WatchListsModel;

    return m_instance;
}

WatchListsModel::WatchListsModel(QObject *parent)
    :WatchListsModelBase (parent)
{
}

WatchListsModel::~WatchListsModel()
{
}

