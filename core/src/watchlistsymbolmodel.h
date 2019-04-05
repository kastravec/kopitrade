#ifndef SYMBOLWATCHLISTMODEL_H
#define SYMBOLWATCHLISTMODEL_H

#include "ksymbolmodel.h"

class WatchListSymbolModel : public KSymbolModel
{
    Q_OBJECT

public:
    Q_PROPERTY(QString watchlistName READ watchlistName WRITE setWatchlistName NOTIFY watchlistNameChanged)
    Q_PROPERTY(bool favoriteMark READ favoriteMark WRITE setFavoriteMark NOTIFY favoriteMarkChanged)
    Q_PROPERTY(QString colorPeg READ colorPeg WRITE setColorPeg NOTIFY colorPegChanged)

    WatchListSymbolModel(QObject *parent = nullptr, const QString &name = QString());
    ~WatchListSymbolModel();

    QString watchlistName() const;
    void setWatchlistName(const QString &name);

    bool favoriteMark() const;
    void setFavoriteMark(bool favorite);

    QString colorPeg() const;
    void setColorPeg(const QString &color);

    Q_INVOKABLE WatchListSymbolModel *clone();
    Q_INVOKABLE bool addSymbol(const QString &symbol);
    Q_INVOKABLE void setSymbols(QHash<QString, KSymbol*> symbols);
    Q_INVOKABLE void refresh();

Q_SIGNALS:
    void watchlistNameChanged(const QString &name);
    void favoriteMarkChanged(bool favorite);
    void colorPegChanged(const QString &color);

private Q_SLOTS:
    void dataUpdatedHandler(const QJsonObject &jsonData);

private:
    class Private;
    Private *m_data;
};

#endif // SYMBOLWATCHLISTMODEL_H
