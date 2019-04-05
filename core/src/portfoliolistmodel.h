#ifndef PORTFOLIOLISTMODEL_H
#define PORTFOLIOLISTMODEL_H

#include <QAbstractListModel>

class Portfolio;

class PortfolioListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PortfolioDataListRole {
        Portfolio_ID = Qt::UserRole +1,
        Portfolio_Name
    };

    Q_ENUM(PortfolioDataListRole)
    static PortfolioListModel *instance();
    ~PortfolioListModel();

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE Portfolio *findPortfolio(const QString &name);
    Q_INVOKABLE Portfolio *createAndAdd(const QString &name);
    Q_INVOKABLE void addPortfolio(Portfolio *portfolio);
    Q_INVOKABLE void removePortfolio(Portfolio *portfolio);
    Q_INVOKABLE void removePortfolio(const QString &name);
    Q_INVOKABLE QList<Portfolio *> portfolioList() const;

private:
    explicit PortfolioListModel(QObject *parent = nullptr);

    static PortfolioListModel *m_instance;
    QHash<QString, Portfolio*> m_allPortfolios;
    QStringList m_allPortfoliosCache;
};

#endif // PORTFOLIOLISTMODEL_H
