#include "watchlistsymbolmodel.h"

#include "watchlistsmodel.h"
#include "ksymbol.h"

#include <QDebug>

class WatchListSymbolModel::Private {
public:
    QString name;
    bool favoriteMark;
    QString colorpeg;
};

WatchListSymbolModel::WatchListSymbolModel(QObject *parent, const QString &name)
    :KSymbolModel (parent)
    ,m_data(new Private)
{
    if(!name.isEmpty())
        setWatchlistName(name);

    m_data->favoriteMark = false;
    QStringList allkeys = m_allSymbols.keys();
    for (int i=0; i< m_allSymbols.count(); ++i) {
        connect(m_allSymbols[allkeys[i]], &KSymbol::jsonDataChanged,
                this, &WatchListSymbolModel::dataUpdatedHandler, Qt::UniqueConnection);
    }
}

WatchListSymbolModel::~WatchListSymbolModel()
{
    delete m_data;
    m_data = nullptr;
}

QString WatchListSymbolModel::watchlistName() const
{
    return m_data->name;
}

void WatchListSymbolModel::setWatchlistName(const QString &name)
{
    if(m_data->name != name ) {
        m_data->name = name;
        emit watchlistNameChanged(name);
    }
}

bool WatchListSymbolModel::favoriteMark() const
{
    return m_data->favoriteMark;
}

void WatchListSymbolModel::setFavoriteMark(bool favorite)
{
    if(m_data->favoriteMark != favorite) {
        m_data->favoriteMark = favorite;
        WatchListsModel::instance()->updateWatchlistDataModel(m_data->name);
        emit favoriteMarkChanged(favorite);
    }
}

QString WatchListSymbolModel::colorPeg() const
{
    return m_data->colorpeg;
}

void WatchListSymbolModel::setColorPeg(const QString &color)
{
    if(m_data->colorpeg != color) {
        m_data->colorpeg = color;
        emit colorPegChanged(color);
    }
}

WatchListSymbolModel *WatchListSymbolModel::clone()
{
    WatchListSymbolModel *watchlist = new WatchListSymbolModel(WatchListsModel::instance(), m_data->name + QString::number(rowCount()));
    watchlist->setSymbols(allSymbols());
    watchlist->setColorPeg(colorPeg());
    return watchlist;
}

bool WatchListSymbolModel::addSymbol(const QString &symbol)
{
    if(KSymbolModel::addSymbol(symbol)) {
        KSymbol *ksymbol = m_allSymbols[symbol];
        ksymbol->setCacheEnabled(true);
        ksymbol->fetchQuote(true);
        connect(m_allSymbols[symbol], &KSymbol::jsonDataChanged,
                this, &WatchListSymbolModel::dataUpdatedHandler, Qt::UniqueConnection);
        return true;
    }

    return false;
}

void WatchListSymbolModel::setSymbols(QHash<QString, KSymbol *> symbols)
{
    KSymbolModel::setSymbols(symbols);

    QStringList allkeys = m_allSymbols.keys();
    for (int i=0; i< m_allSymbols.count(); ++i) {
        m_allSymbols[allkeys[i]]->setCacheEnabled(true);
        connect(m_allSymbols[allkeys[i]], &KSymbol::jsonDataChanged,
                this, &WatchListSymbolModel::dataUpdatedHandler, Qt::UniqueConnection);
    }
}

void WatchListSymbolModel::refresh()
{
    QStringList allkeys = m_allSymbols.keys();
    for (int i=0; i<m_allSymbols.count(); ++i) {
        m_allSymbols[allkeys[i]]->refresh();
    }
}

void WatchListSymbolModel::dataUpdatedHandler(const QJsonObject &jsonData)
{
    if(!jsonData.value(KSymbolProperty::Symbol).isNull()) {
        QModelIndex indx = index(jsonData.value(KSymbolProperty::OrderIndex).toInt());
        emit dataChanged(indx, indx);
    }
}
