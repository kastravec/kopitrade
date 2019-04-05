#ifndef KACCOUNT_H
#define KACCOUNT_H

#include <QObject>

class KAccount : public QObject
{
    Q_OBJECT
public:
    enum AccountType {
        Live = 1,
        Demo,
        Test,
        Undefined = -1
    };

    Q_ENUM(AccountType)

    Q_PROPERTY(QString accountName READ accountName WRITE setAccountName NOTIFY accountNameChanged)
    Q_PROPERTY(int accountType READ accountType WRITE setAccountType NOTIFY accountTypeChanged)
    Q_PROPERTY(double availableAmount READ availableAmount WRITE setAvailableAmount NOTIFY availableAmountChanged)
    Q_PROPERTY(double investedAmount READ investedAmount WRITE setInvestedAmount NOTIFY investedAmountChanged)
    Q_PROPERTY(double availableEquity READ availableEquity WRITE setAvailableEquity NOTIFY availableEquityChanged)

    explicit KAccount(QObject *parent = nullptr, int type = KAccount::Demo);
    ~KAccount();

    QString accountName() const;
    void setAccountName(const QString &name);

    int accountType() const;
    void setAccountType(int type);

    double availableAmount() const;
    void setAvailableAmount(double amount);

    double investedAmount() const;
    void setInvestedAmount(double amount);

    double availableEquity() const;
    void setAvailableEquity(double amount);

Q_SIGNALS:
    void accountNameChanged(const QString &name);
    void accountTypeChanged(int type);
    void availableAmountChanged(double amount);
    void investedAmountChanged(double amount);
    void availableEquityChanged(double amount);

private:
    class Private;
    Private *m_data;
};

#endif // KACCOUNT_H
