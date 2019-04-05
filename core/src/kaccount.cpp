#include "kaccount.h"

class KAccount::Private {
public:
    int accountType;
    QString accountName;
    double availableAmount;
    double investedAmount;
    double availableEquity;
};

KAccount::KAccount(QObject *parent, int type)
    :QObject(parent)
    ,m_data(new Private)
{
    setAccountType(type);
}

KAccount::~KAccount()
{
    delete m_data;
    m_data = nullptr;
}

QString KAccount::accountName() const
{
    return m_data->accountName;
}

void KAccount::setAccountName(const QString &name)
{
    if(m_data->accountName != name) {
        m_data->accountName = name;
        emit accountNameChanged(name);
    }
}

int KAccount::accountType() const
{
    return m_data->accountType;
}

void KAccount::setAccountType(int type)
{
    if(m_data->accountType != type) {
        m_data->accountType = type;
        emit accountTypeChanged(type);
    }
}

double KAccount::availableAmount() const
{
    return m_data->availableAmount;
}

void KAccount::setAvailableAmount(double amount)
{
    if(m_data->availableAmount != amount) {
        m_data->availableAmount = amount;
        emit availableAmountChanged(amount);
    }
}

double KAccount::investedAmount() const
{
    return m_data->investedAmount;
}

void KAccount::setInvestedAmount(double amount)
{
    if(m_data->investedAmount != amount) {
        m_data->investedAmount = amount;
        emit investedAmountChanged(amount);
    }
}

double KAccount::availableEquity() const
{
    return m_data->availableEquity;
}

void KAccount::setAvailableEquity(double amount)
{
    if(m_data->availableEquity != amount) {
        m_data->availableAmount = amount;
        emit availableEquityChanged(amount);
    }
}
