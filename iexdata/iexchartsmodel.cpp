#include "iexchartsmodel.h"
#include "iexdataendpoint.h"
#include "iexcloudglobals.h"

#include <QJsonArray>

#include <QDebug>

IEXChartsModel::IEXChartsModel(QObject *parent)
    :QAbstractTableModel (parent)
{
    setBusy(false);
}

IEXChartsModel::~IEXChartsModel()
{

}

bool IEXChartsModel::busy() const
{
    return m_busy;
}

QString IEXChartsModel::symbol() const
{
    return m_symbol;
}

void IEXChartsModel::setSymbol(const QString &symbol)
{
    if(m_symbol != symbol) {
        m_symbol = symbol;
        emit symbolChanged(symbol);
    }
}

QHash<int, QByteArray> IEXChartsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[XPos] = "XPos";
    roles[YPos] = "YPos";
    roles[XYPos] = "XYPos";

    return roles;
}

int IEXChartsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_chartData.count()/2;
}

int IEXChartsModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant IEXChartsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
        || index.row() >= m_chartData.count())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case XYPos:
        return m_chartData[index.row()][index.column()];
    default:
        return QVariant();
    }
}

void IEXChartsModel::fecthChart()
{
    setBusy(true);
    IEXDataEndpoint *iexdatapoint = new IEXDataEndpoint(this, IEXCloudGlobals::Stock);
    iexdatapoint->fetchData(QString("/")
                           + symbol()
                           + QString("/chart/5y"));

//    qDebug()<<"FETCHING CHART URL : " << iexdatapoint->apiURL();

    connect(iexdatapoint, &IEXDataEndpoint::jsonDataReceivedChanged,
            this, &IEXChartsModel::newChartDataHandler);
    connect(iexdatapoint, &IEXDataEndpoint::errorDataReceived,
            this, &IEXChartsModel::newChartDataErrorHandler);
}

void IEXChartsModel::newChartDataHandler(const QJsonValue &jsonData)
{
    if(jsonData.isNull()) {
        setBusy(false);
        return;
    }

//    qDebug()<<" FETCHING CHARTS DATA " << jsonData;
    clearData();

    beginInsertRows(QModelIndex(), 0, m_chartData.count() -1);
    QJsonArray symbArray = jsonData.toArray();
    int counter = symbArray.count();
    QJsonObject jsobj;
    for(int i=0; i<counter; ++i) {
        jsobj = symbArray[i].toObject();
        QList<double> p;
        p.append(jsobj.value("open").toDouble());
        p.append(jsobj.value("close").toDouble());
        m_chartData.append(p);
    }

    endInsertRows();
    setBusy(false);
}

void IEXChartsModel::newChartDataErrorHandler(int errorCode, const QByteArray &data)
{
    qDebug()<<"ERROR FETCHING CHARTS DATA " << errorCode << data;
    setBusy(false);
}

void IEXChartsModel::clearData()
{
    setBusy(true);
    beginResetModel();
    m_chartData.clear();
    resetInternalData();
    endResetModel();
    setBusy(false);
}

void IEXChartsModel::setBusy(bool busy)
{
    if(m_busy != busy) {
        m_busy = busy;
        emit busyChanged(busy);
    }
}
