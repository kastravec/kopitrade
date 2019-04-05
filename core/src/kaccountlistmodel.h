#ifndef KACCOUNTLISTMODEL_H
#define KACCOUNTLISTMODEL_H

#include <QAbstractListModel>

class KAccount;

class KAccountListModel: public QAbstractListModel
{
    Q_OBJECT

public:

    static KAccountListModel *instance();
    ~KAccountListModel();

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void addAccount(KAccount *account);
    Q_INVOKABLE KAccount *account(const QString &name);

private:
    explicit KAccountListModel(QObject *parent = nullptr);

    static KAccountListModel *m_instance;
    QHash<QString, KAccount *> m_allAccounts;
    QStringList m_allAccountsCache;
};

#endif // KACCOUNTLISTMODEL_H
