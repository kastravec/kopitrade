#include "trade.h"

#include "portfolio.h"
#include "tradelistmodel.h"
#include "asset.h"

class Trade::Private
{
public:
    QDateTime timestamp;
    Portfolio *portfolio;
    Asset *asset;
    QString name;
    int id;
    int status;
};

Trade::Trade(QObject *parent, int id)
    :QObject(parent)
    ,m_data(new Private)
{
    m_data->asset = nullptr;
    m_data->id = id;
}

Trade::~Trade()
{
    delete m_data;
    m_data = nullptr;
}

int Trade::tradeID() const
{
    return m_data->id;
}

QDateTime Trade::timestamp() const
{
    return m_data->timestamp;
}

int Trade::status() const
{
    return m_data->status;
}

Portfolio *Trade::portfolio() const
{
    return m_data->portfolio;
}

void Trade::setPortfolio(Portfolio *port)
{
    if(m_data->portfolio != port) {
        m_data->portfolio = port;
        emit portfolioChanged(m_data->portfolio);
    }
}

Asset *Trade::asset() const
{
    return m_data->asset;
}

void Trade::setAsset(Asset *asset)
{
    if(m_data->asset != asset) {
        m_data->asset = asset;
        emit assetChanged(m_data->asset);
    }
}

QString Trade::name() const
{
    return m_data->name;
}

void Trade::setName(const QString &name)
{
    if(m_data->name != name) {
        m_data->name = name;
        emit nameChanged(m_data->name);
    }
}

void Trade::open()
{
}

void Trade::close()
{
    if(m_data->portfolio == nullptr)
        return;
}

void Trade::setID(int id)
{
    m_data->id = id;
    setName(QString("Trade-") + QString::number(id));
}
