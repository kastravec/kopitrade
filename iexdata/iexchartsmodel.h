#ifndef IEXCHARTSMODEL_H
#define IEXCHARTSMODEL_H

#include <QAbstractTableModel>
#include <QJsonObject>

class IEXChartsModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    enum IEXChartsModelDataRole {
        XPos = 22,
        YPos,
        XYPos
    };

    Q_ENUM(IEXChartsModelDataRole)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(QString symbol READ symbol WRITE setSymbol NOTIFY symbolChanged)

    IEXChartsModel(QObject *parent = nullptr);
    ~IEXChartsModel();

    bool busy() const;

    QString symbol() const;
    void setSymbol(const QString &symbol);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void fecthChart();

Q_SIGNALS:
    void busyChanged(bool busy);
    void symbolChanged(const QString &symbol);

private Q_SLOTS:
    void newChartDataHandler(const QJsonValue &jsonData);
    void newChartDataErrorHandler(int errorCode, const QByteArray &data);

private:
    void clearData();
    void setBusy(bool busy);

    QString m_symbol;
    QList< QList<double> > m_chartData;
    bool m_busy;
};

#endif // IEXCHARTSMODEL_H
