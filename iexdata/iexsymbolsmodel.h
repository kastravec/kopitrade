#ifndef IEXSYMBOLSMODEL_H
#define IEXSYMBOLSMODEL_H

#include <QAbstractListModel>

#include "ksymbolmodel.h"

class KSymbol;
class IEXDataEndpoint;

class IEXSymbolsModel : public KSymbolModel
{
    Q_OBJECT
public:
    static IEXSymbolsModel *instance();
    ~IEXSymbolsModel();

    Q_INVOKABLE void refresh();
    Q_INVOKABLE KSymbol *iexSymbol(const QString &symbol);
    Q_INVOKABLE bool fromJsonArray(const QJsonArray &json);

    Q_INVOKABLE void fetchRegionSymbols(int iexregion);
    Q_INVOKABLE void fetchForexSymbols();
    Q_INVOKABLE void fetchCryptoSymbols();

private Q_SLOTS:
    void iexDataResponseHandler(const QJsonValue &data);
    void iexForexDataHandler(const QJsonValue &data);
    void iexDataErrorHandler(int errorCode, const QByteArray &data);

protected:
    IEXSymbolsModel(QObject *parent = nullptr);

private:
    static IEXSymbolsModel *m_instance;
};

#endif // IEXSYMBOLSMODEL_H
