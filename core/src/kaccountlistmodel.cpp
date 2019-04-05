#include "kaccountlistmodel.h"

KAccountListModel *KAccountListModel::m_instance = nullptr;
KAccountListModel *KAccountListModel::instance()
{
    if(m_instance == nullptr)
        m_instance = new KAccountListModel;

    return m_instance;
}

KAccountListModel::KAccountListModel(QObject *parent)
    :QAbstractListModel (parent)
{

}

KAccountListModel::~KAccountListModel()
{

}

QHash<int, QByteArray> KAccountListModel::roleNames() const
{

}

int KAccountListModel::rowCount(const QModelIndex &parent) const
{

}

QVariant KAccountListModel::data(const QModelIndex &index, int role) const
{

}

void KAccountListModel::addAccount(KAccount *account)
{

}

KAccount *KAccountListModel::account(const QString &name)
{

}
