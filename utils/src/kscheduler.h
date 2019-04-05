#ifndef KSCHEDULER_H
#define KSCHEDULER_H

#include <QObject>

class KScheduler : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(bool repeat READ repeat WRITE setRepeat NOTIFY repeatChanged)
    Q_PROPERTY(int from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(int to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(bool runOnWeekends READ runOnWeekends WRITE setRunOnWeekends NOTIFY runOnWeekendsChanged)

    explicit KScheduler(QObject *parent = nullptr);
    ~KScheduler();

    int interval() const;
    void setInterval(int newInterval);

    bool repeat() const;
    void setRepeat(bool repeat);

    int from() const;
    void setFrom(int from);

    int to() const;
    void setTo(int to);

    bool runOnWeekends() const;
    void setRunOnWeekends(bool run);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

Q_SIGNALS:
    void triggered();
    void deactivated();
    void intervalChanged(int interval);
    void repeatChanged(bool repeat);
    void fromChanged(int from);
    void toChanged(int to);
    void runOnWeekendsChanged(bool run);

private Q_SLOTS:
    void timerTriggerHandle();

private:
    bool timeToRun();

    class Private;
    Private *m_data;
};

#endif // KSCHEDULER_H
