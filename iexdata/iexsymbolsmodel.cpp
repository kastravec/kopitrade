#include "iexsymbolsmodel.h"

#include "ksymbol.h"
#include "iexdataendpoint.h"

#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

IEXSymbolsModel * IEXSymbolsModel::m_instance = nullptr;
IEXSymbolsModel *IEXSymbolsModel::instance()
{
    if(!m_instance)
        m_instance = new IEXSymbolsModel;

    return m_instance;
}
IEXSymbolsModel::IEXSymbolsModel(QObject *parent)
    :KSymbolModel(parent)
{

}

IEXSymbolsModel::~IEXSymbolsModel()
{
}

void IEXSymbolsModel::refresh()
{
    clearData();
    fetchRegionSymbols(IEXCloudGlobals::All_Symbols);
    fetchRegionSymbols(IEXCloudGlobals::All_Symbols_FR);
    fetchRegionSymbols(IEXCloudGlobals::All_Symbols_NL);
    fetchForexSymbols();

    fetchRegionSymbols(IEXCloudGlobals::All_Symbols_GB);
//    fetchRegionSymbols(IEXCloudGlobals::All_Symbols_IE);
    //    fetchRegionSymbols(IEXCloudGlobals::All_Symbols_MX);
    //    fetchRegionSymbols(IEXCloudGlobals::All_Symbols_PT);
//    fetchRegionSymbols(IEXCloudGlobals::All_Symbols_BE);
    //    fetchRegionSymbols(IEXCloudGlobals::All_Symbols_CA);
}

KSymbol *IEXSymbolsModel::iexSymbol(const QString &symbol)
{
    if(KSymbolModel::symbol(symbol))
        return qobject_cast<KSymbol *>(KSymbolModel::symbol(symbol));

    return nullptr;
}

bool IEXSymbolsModel::fromJsonArray(const QJsonArray &json)
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
    return true;
}

void IEXSymbolsModel::fetchRegionSymbols(int iexregion)
{
    if(iexregion == IEXCloudGlobals::Undefined || iexregion == IEXCloudGlobals::All_Forex
        || iexregion == IEXCloudGlobals::Cryptocurrency)
        return;

    IEXDataEndpoint *m_iexDataEndpoint = new IEXDataEndpoint(this, iexregion);
    connect(m_iexDataEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
            this, &IEXSymbolsModel::iexDataResponseHandler);
    connect(m_iexDataEndpoint, &IEXDataEndpoint::errorDataReceived,
            this, &IEXSymbolsModel::iexDataErrorHandler);

    m_iexDataEndpoint->fetchData();
    setBusy(true);
}

void IEXSymbolsModel::fetchForexSymbols()
{
    IEXDataEndpoint *m_iexDataEndpoint = new IEXDataEndpoint(this, IEXCloudGlobals::All_Forex);
    connect(m_iexDataEndpoint, &IEXDataEndpoint::jsonDataReceivedChanged,
            this, &IEXSymbolsModel::iexForexDataHandler);
    connect(m_iexDataEndpoint, &IEXDataEndpoint::errorDataReceived,
            this, &IEXSymbolsModel::iexDataErrorHandler);

    m_iexDataEndpoint->fetchData();
    setBusy(true);
}

void IEXSymbolsModel::fetchCryptoSymbols()
{
}

void IEXSymbolsModel::iexDataErrorHandler(int errorCode, const QByteArray &data)
{
    qDebug()<<"ERROR FETCHING ALL SYMBOLS: " << errorCode << data;
    setBusy(false);
}

void IEXSymbolsModel::iexDataResponseHandler(const QJsonValue &data)
{
    if(data.isNull()) {
        setBusy(false);
        return;
    }

    QJsonArray symbArray = data.toArray();
    int counter = symbArray.count();

    QHash<QString, KSymbol *> allsymbols;
    KSymbol *ksymbol = nullptr;

    for(int i=0; i<counter; ++i) {
        QJsonObject symbolJsonObj = symbArray[i].toObject();
        ksymbol = new KSymbol(this);
        QJsonObject jsondt;
        ksymbol->setSymbol(symbolJsonObj.value("symbol").toString());
        jsondt.insert(KSymbolProperty::Symbol, symbolJsonObj.value("symbol"));
        jsondt.insert(KSymbolProperty::Symbol_Name, symbolJsonObj.value("name"));
        jsondt.insert(KSymbolProperty::Market_Cap, symbolJsonObj.value("marketCap"));
        jsondt.insert(KSymbolProperty::Industry, symbolJsonObj.value("sector"));
        jsondt.insert(KSymbolProperty::Exchange, symbolJsonObj.value("primaryExchange"));
        jsondt.insert(KSymbolProperty::Last_Closed_Price, symbolJsonObj.value("close"));
        jsondt.insert(KSymbolProperty::Symbol_ID, symbolJsonObj.value("iexId"));
        jsondt.insert(KSymbolProperty::Region, symbolJsonObj.value("region"));

        QString stocktype = symbolJsonObj.value("type").toString();
        if(stocktype == "ad")
            jsondt.insert(KSymbolProperty::Type, KSymbol::ADR);
        else if(stocktype == "re")
            jsondt.insert(KSymbolProperty::Type, KSymbol::REIT);
        else if(stocktype == "ce")
            jsondt.insert(KSymbolProperty::Type, KSymbol::ClosedEndFund);
        else if(stocktype == "si")
            jsondt.insert(KSymbolProperty::Type, KSymbol::SecondaryIssue);
        else if(stocktype == "lp")
            jsondt.insert(KSymbolProperty::Type, KSymbol::LimitedPartnership);
        else if(stocktype == "cs")
            jsondt.insert(KSymbolProperty::Type, KSymbol::CommonStock);
        else if(stocktype == "et")
            jsondt.insert(KSymbolProperty::Type, KSymbol::ETF);
        else if(stocktype.isEmpty())
            jsondt.insert(KSymbolProperty::Type, KSymbol::Undefined);

        jsondt.insert(KSymbolProperty::OrderIndex, i);
        ksymbol->setJsonData(jsondt);
        allsymbols[ksymbol->symbol()] = ksymbol;
    }

    setSymbols(allsymbols);

    if(rowCount() > 8000) {
        m_modelStatus = Ready;
        emit modelStatusChanged(m_modelStatus);
    }

    setBusy(false);
    sender()->deleteLater();
}

void IEXSymbolsModel::iexForexDataHandler(const QJsonValue &data)
{
    if(data.isNull()) {
        setBusy(false);
        return;
    }

    QHash<QString, KSymbol *> allsymbols;
    KSymbol *ksymbol = nullptr;

    QJsonArray symbArray = data.toObject().value("pairs").toArray();
    int counter = symbArray.count();
    for (int i = 0; i < counter; ++i) {
        ksymbol = new KSymbol(this);
        QJsonObject jsondt;
        ksymbol->setSymbol(symbArray[i].toObject().value("fromCurrency").toString()
                           +symbArray[i].toObject().value("toCurrency").toString());
        jsondt.insert(KSymbolProperty::Symbol, ksymbol->symbol());
        jsondt.insert(KSymbolProperty::Symbol_Name, ksymbol->symbol());
        jsondt.insert(KSymbolProperty::Symbol_Description, ksymbol->symbol());
        jsondt.insert(KSymbolProperty::OrderIndex, i);
        jsondt.insert(KSymbolProperty::Type, KSymbol::Currency);
        ksymbol->setJsonData(jsondt);
        allsymbols[ksymbol->symbol()] = ksymbol;
    }

    setSymbols(allsymbols);
    setBusy(false);
    sender()->deleteLater();
}
