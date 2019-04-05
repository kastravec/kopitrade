#include "ksymbolmodel.h"
#include "ksymbol.h"

#include "iexsymbolsmodel.h"

#include <QDebug>

KSymbolModel::KSymbolModel(QObject *parent)
    :QAbstractListModel (parent)
{
    m_modelStatus = KSymbolModel::Unknown;
    setBusy(false);
}

KSymbolModel::~KSymbolModel()
{

}

QHash<int, QByteArray> KSymbolModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Symbol_ID] = KSymbolProperty::Symbol_ID;
    roles[Symbol] = KSymbolProperty::Symbol;
    roles[Symbol_Name] = KSymbolProperty::Symbol_Name;
    roles[Symbol_Description] = KSymbolProperty::Symbol_Description;
    roles[Market_Cap] = KSymbolProperty::Market_Cap;
    roles[Industry] = KSymbolProperty::Industry;
    roles[Exchange] = KSymbolProperty::Exchange;
    roles[Last_Closed_Price] = KSymbolProperty::Last_Closed_Price;
    roles[Logo] = KSymbolProperty::Logo;
    roles[PriceIncreased] = "PriceIncreased";
    roles[DailyChangePercent] = "DailyChangePercent";
    roles[DailyChangeUnits] = "DailyChangeUnits";
    roles[OrderIndex] = "OrderIndex";
    roles[Type] = "Type";
    return roles;
}

int KSymbolModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_allSymbolsCacheOrdered.count();
}

QVariant KSymbolModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
        || index.row() >= m_allSymbols.count())
        return QVariant();

    if(!m_allSymbolsCacheOrdered[index.row()])
        return QVariant();

    switch (role) {
    case Symbol:
        return m_allSymbolsCacheOrdered[index.row()]->symbol(); //symb;
    case Symbol_Name:
        return m_allSymbolsCacheOrdered[index.row()]->symbolName(); //m_allSymbols.value(symb)->symbolName();
    case Last_Closed_Price:
        return m_allSymbolsCacheOrdered[index.row()]->price(); //QString::number(m_allSymbols.value(symb)->price());
    case Logo:
            return m_allSymbolsCacheOrdered[index.row()]->logoUrl();
    case PriceIncreased:
        return m_allSymbolsCacheOrdered[index.row()]->priceIncreased(); //m_allSymbols.value(symb)->priceIncreased();
    case DailyChangePercent:
        if(m_allSymbolsCacheOrdered[index.row()]->symbolType() == KSymbol::CommonStock)
            return QString::number(m_allSymbolsCacheOrdered[index.row()]->dailyChangePercent());
        else
            return QString("-");
    case OrderIndex:
        return m_allSymbolsCacheOrdered[index.row()]->orderIndex(); //m_allSymbols.value(symb)->orderIndex();
    case Type:
        return m_allSymbolsCacheOrdered[index.row()]->symbolType(); //m_allSymbols.value(symb)->symbolType();
    default:
        return QVariant();
    }
}

int KSymbolModel::modelStatus() const
{
    return m_modelStatus;
}

bool KSymbolModel::busy() const
{
    return m_busy;
}

bool KSymbolModel::addSymbol(const QString &symbol)
{
    if(!symbol.isEmpty() && !m_allSymbols.contains(symbol)) {
        KSymbol *ksymb = IEXSymbolsModel::instance()->symbol(symbol);
        if(ksymb)
            return addSymbol(ksymb);
    }

    return false;
}

bool KSymbolModel::addSymbol(KSymbol *symbol)
{
    if(!symbol)
        return false;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_allSymbols.insert(symbol->symbol(), symbol);
    symbol->setOrderIndex(m_allSymbolsCacheOrdered.count());
    m_allSymbolsCacheOrdered.append(symbol);
    endInsertRows();

    return true;
}

void KSymbolModel::setSymbols(QHash<QString, KSymbol *> symbols)
{
    int counter = symbols.count();
    QStringList allkeys = symbols.keys();
    for (int i = 0; i < counter; ++i) {
        m_allSymbols.insert(allkeys[i], symbols.value(allkeys[i]));
    }

    populateSymbolCache();
}

QHash<QString, KSymbol *> KSymbolModel::allSymbols() const
{
    return m_allSymbols;
}

QJsonArray KSymbolModel::toJsonArray() const
{
    QJsonArray jsonarray;
    for(int i=0; i<m_allSymbolsCacheOrdered.count(); ++i)
        jsonarray.append( m_allSymbolsCacheOrdered[i]->jsonData() );

    return jsonarray;
}

bool KSymbolModel::fromJsonArray(const QJsonArray &json)
{
    setBusy(true);
    QHash <QString, KSymbol *> allSymbols;
    KSymbol *symbl = nullptr;
    for (int i = 0; i < json.count(); ++i) {
        symbl = new KSymbol(this);
        symbl->setJsonData(json.at(i).toObject());
        allSymbols.insert(symbl->symbol(), symbl);
    }

    setSymbols(allSymbols);
    setBusy(false);
}

KSymbol *KSymbolModel::symbol(const QString &symbol) const
{
    if(m_allSymbols.contains(symbol))
        return m_allSymbols[symbol];

    return nullptr;
}

KSymbol *KSymbolModel::symbol(int index) const
{
    if(index < m_allSymbolsCacheOrdered.count())
        return m_allSymbolsCacheOrdered.at(index);

    return nullptr;
}

void KSymbolModel::setBusy(bool busy)
{
    if(m_busy != busy) {
        m_busy = busy;
        emit busyChanged(busy);
    }
}

void KSymbolModel::clearData()
{
    beginResetModel();
    KSymbol *symb = nullptr;
    for (int i = 0; i < m_allSymbolsCacheOrdered.count(); ++i) {
        symb = m_allSymbols.take(m_allSymbolsCacheOrdered[i]->symbol());
        symb->deleteLater();
    }

    m_allSymbolsCacheOrdered.clear();
    m_allSymbols.clear();
    resetInternalData();
    endResetModel();
}

bool KSymbolModel::removeSymbol(const QString &sym, bool deleteObject)
{
    return removeSymbolObject(symbol(sym), deleteObject);
}

bool KSymbolModel::removeSymbolObject(KSymbol *symbol, bool deleteObject)
{
    if(symbol) {
        if(m_allSymbols.contains(symbol->symbol())) {
            int rowpos = m_allSymbolsCacheOrdered.indexOf(symbol);
            beginRemoveRows(QModelIndex(), rowpos, rowpos);
            m_allSymbols.remove(symbol->symbol());
            m_allSymbolsCacheOrdered.removeAll(symbol);
            symbol->setCacheEnabled(false);
            reorderIndexes();
            symbol->setOrderIndex(-1);
            if(deleteObject)
                symbol->deleteLater();

            endRemoveRows();
            return true;
        }
    }

    return false;
}

void KSymbolModel::populateSymbolCache()
{
    beginResetModel();

    int counter = m_allSymbols.count();
    QStringList allkeys = m_allSymbols.keys();
    m_allSymbolsCacheOrdered.clear();
    for (int i=0; i<counter; ++i)
        m_allSymbolsCacheOrdered.insert(m_allSymbols.value(allkeys[i])->orderIndex(), m_allSymbols.value(allkeys[i]));

    endResetModel();
}

void KSymbolModel::reorderIndexes()
{
    KSymbol *ksymbol = nullptr;
    for (int i = 0; i<m_allSymbolsCacheOrdered.count(); ++i) {
        ksymbol = m_allSymbolsCacheOrdered[i];
        ksymbol->setOrderIndex(m_allSymbolsCacheOrdered.indexOf(ksymbol));
    }
}

void KSymbolModel::swapIndexOrder(int from, int to)
{
    beginResetModel();

    m_allSymbolsCacheOrdered.move(from, to);
    reorderIndexes();

    endResetModel();
}


