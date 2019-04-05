#ifndef KOPRESTLESS_H
#define KOPRESTLESS_H

#include <QObject>

class KopiRestLess : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString apiHost READ apiHost WRITE setApiHost NOTIFY apiHostChanged)

    ~KopiRestLess();
    static KopiRestLess *instance();

    QString apiHost() const;
    void setApiHost(const QString &host);

Q_SIGNALS:
    void apiHostChanged(const QString &host);

private:
    explicit KopiRestLess(QObject *parent = nullptr);

    class Private;
    Private *m_data;

    static KopiRestLess *m_instance;
};

#endif // KOPRESTLESS_H
