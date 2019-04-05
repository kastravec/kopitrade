#include "asset.h"

#include "portfolio.h"
#include "assetlistmodel.h"
#include "ksymbol.h"

class Asset::Private
{
public:
    double tradePrice;
    Portfolio *portfolio;
    int type;
    int id;
    KSymbol *ksymbol;
};

Asset::Asset(QObject *parent)
    :QObject(parent)
    ,m_data(new Private)
{
    m_data->id = -1;
    initAsset(Asset::Undefined, 0);
}

Asset::~Asset()
{
    delete m_data;
    m_data = nullptr;
}

int Asset::assetID() const
{
    return m_data->id;
}

int Asset::type() const
{
    return m_data->type;
}

Portfolio *Asset::portfolio() const
{
    return m_data->portfolio;
}

void Asset::setPortfolio(Portfolio *port)
{
    if(m_data->portfolio != port && port != nullptr) {
        m_data->portfolio = port;
        setParent(m_data->portfolio);
        setID(m_data->portfolio->assetsModel()->rowCount() +1);
        emit portfolioChanged(m_data->portfolio);
    }
}

double Asset::tradePrice() const
{
    return m_data->tradePrice;
}

void Asset::setTradePrice(double price)
{

}

KSymbol *Asset::ksymbol() const
{
    return m_data->ksymbol;
}

void Asset::setKsymbol(KSymbol *symbol)
{
    if(m_data->ksymbol != symbol) {
        m_data->ksymbol = symbol;
        emit ksymbolChanged(symbol);
    }
}

void Asset::initAsset(int type, double price)
{
    m_data->type = type;
}

void Asset::setType(int type)
{
    if(m_data->type != type) {
        m_data->type = type;
        emit typeChanged(m_data->type);
    }
}

void Asset::setID(int id)
{
    m_data->id = id;
}
