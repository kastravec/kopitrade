#include "portfolio.h"

#include "portfoliolistmodel.h"
#include "asset.h"
#include "trade.h"
#include "assetlistmodel.h"
#include "tradelistmodel.h"

#include <QHash>

class Portfolio::Private
{
public:
    AssetListModel *assetsModel;
    TradeListModel *tradesModel;
    QString name;
    int id;
    int type;
};

Portfolio::Portfolio(QObject *parent, int id)
    :QObject(parent)
    ,m_data(new Private)
{
    initPortfolio(id);
}

Portfolio::~Portfolio()
{
    delete m_data;
    m_data = nullptr;
}

int Portfolio::portfolioID() const
{
    return m_data->id;
}

QString Portfolio::name() const
{
    return m_data->name;
}

void Portfolio::setName(const QString &name)
{
    if(m_data->name != name) {
        m_data->name = name;
        emit nameChanged(m_data->name);
    }
}

int Portfolio::type() const
{
    return m_data->type;
}

void Portfolio::setType(int type)
{
    if(m_data->type != type) {
        m_data->type = type;
        emit typeChanged(type);
    }
}

AssetListModel *Portfolio::assetsModel() const
{
    return m_data->assetsModel;
}

void Portfolio::setAssetsModel(AssetListModel *model)
{
    if(m_data->assetsModel != model) {
        m_data->assetsModel->deleteLater();
        m_data->assetsModel = model;
        m_data->assetsModel->setParent(this);
        emit assetsModelChanged(m_data->assetsModel);
    }
}

TradeListModel *Portfolio::tradesModel() const
{
    return m_data->tradesModel;
}

void Portfolio::setTradesModel(TradeListModel *model)
{
    if(m_data->tradesModel != model) {
        m_data->tradesModel->deleteLater();
        m_data->tradesModel = model;
        emit tradesModelChanged(m_data->tradesModel);
    }
}

void Portfolio::addTrade(Trade *trade)
{
    if(trade != nullptr) {
        trade->setPortfolio(this);
        m_data->tradesModel->addTrade(trade);
    }
}

void Portfolio::addAsset(Asset *asset)
{
    m_data->assetsModel->addAsset(asset);
}

void Portfolio::setID(int id)
{
    m_data->id = id;
}

void Portfolio::initPortfolio(int id)
{
    m_data->assetsModel = new AssetListModel(this);
    m_data->tradesModel = new TradeListModel(this);

    m_data->assetsModel->setPortfolio(this);
    m_data->tradesModel->setPortfolio(this);

    setID(id);
    setType(Undefined);
}
