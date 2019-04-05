#ifndef KSYMBOLMODEL_H
#define KSYMBOLMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>

class KSymbol;

class KSymbolModel: public QAbstractListModel
{
    Q_OBJECT

public:
    enum ModelStatus {
        Ready = 222,
        Busy,
        Error,
        Unknown = -1
    };

    enum DefaultPropertiesDataRole {
        Symbol = Qt::UserRole +1,
        Symbol_ID,
        Symbol_Name,
        Symbol_Description,
        Market_Cap,
        Industry,
        Exchange,
        Last_Closed_Price,
        Logo,
        PriceIncreased,
        DailyChangePercent,
        DailyChangeUnits,
        OrderIndex,
        Type
    };

    Q_ENUM(ModelStatus)
    Q_ENUM(DefaultPropertiesDataRole)

    Q_PROPERTY(int modelStatus READ modelStatus NOTIFY modelStatusChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

    explicit KSymbolModel(QObject *parent = nullptr);
    ~KSymbolModel();

    virtual QHash<int, QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int modelStatus() const;
    bool busy() const;

    Q_INVOKABLE virtual bool addSymbol(const QString &symbol);
    Q_INVOKABLE virtual void setSymbols(QHash<QString, KSymbol*> symbols);
    Q_INVOKABLE QHash<QString, KSymbol*> allSymbols() const;
    Q_INVOKABLE QJsonArray toJsonArray() const;
    Q_INVOKABLE virtual bool fromJsonArray(const QJsonArray &json);
    Q_INVOKABLE virtual void clearData();
    Q_INVOKABLE virtual KSymbol *symbol(const QString &symbol) const;
    Q_INVOKABLE virtual KSymbol *symbol(int index) const;
    Q_INVOKABLE bool removeSymbol(const QString &sym = QString(), bool deleteObject = false);
    Q_INVOKABLE bool removeSymbolObject(KSymbol *symbol = nullptr, bool deleteObject = false);

    Q_INVOKABLE void swapIndexOrder(int from, int to);

Q_SIGNALS:
    void modelStatusChanged(int modelStatus);
    void busyChanged(bool busy);

protected:
    void setBusy(bool busy);
    bool addSymbol(KSymbol *symbol);
    void populateSymbolCache();
    void reorderIndexes();

protected:
    int m_modelStatus;
    bool m_busy;
    QHash<QString, KSymbol *> m_allSymbols;
    QList<KSymbol*> m_allSymbolsCacheOrdered;
};

#endif // KSYMBOLMODEL_H
