#ifndef KOPI_H
#define KOPI_H

#include <QObject>

class Kopi : public QObject
{
    Q_OBJECT
public:

    enum KopiAppStatus {
        Uknown = -1,
        Blank,
        StartingUp,
        ShuttingDown,
        SavingSettings,
        ReadingSettings,
        Processing,
        Idle
    };

    Q_ENUM(KopiAppStatus)

    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString localStorePath READ localStorePath WRITE setLocalStorePath NOTIFY localStorePathChanged)

    ~Kopi();
    static Kopi *instance();

    int status() const;

    QString localStorePath() const;
    void setLocalStorePath(const QString &path);

    Q_INVOKABLE bool storeLocally();
    Q_INVOKABLE bool readLocalStore();
    Q_INVOKABLE bool checkDefaultLocalStore();
    Q_INVOKABLE QString stringify(uint number);

Q_SIGNALS:
    void statusChanged(int status);
    void localStorePathChanged(const QString &path);

private:
    explicit Kopi(QObject *parent = nullptr);
    void setStatus(int status);

    static Kopi *m_instance;

    class Private;
    Private *m_data;
};

#endif // KOPI_H
