#include "kscheduler.h"

#include <QTimer>
#include <QDate>

#include <QDebug>

class KScheduler::Private {

public:
    QTimer *timer;
    bool repeat;
    int from;
    int to;
    bool runOnWeekends;
};

KScheduler::KScheduler(QObject *parent)
    :QObject(parent)
      ,m_data(new Private)
{
    m_data->timer = new QTimer(this);
    m_data->timer->setInterval(5000);
    m_data->repeat = true;
    m_data->from = 8;
    m_data->to = 22;
    m_data->runOnWeekends = false;

    connect(m_data->timer, &QTimer::timeout, this, &KScheduler::timerTriggerHandle);
}

KScheduler::~KScheduler()
{
    delete m_data;
    m_data = nullptr;
}

int KScheduler::interval() const
{
    return m_data->timer->interval();
}

void KScheduler::setInterval(int newInterval)
{
    if(m_data->timer->interval() != newInterval) {
        m_data->timer->setInterval(newInterval);
        emit intervalChanged(newInterval);
    }
}

bool KScheduler::repeat() const
{
    return m_data->repeat;
}

void KScheduler::setRepeat(bool repeat)
{
    if(m_data->repeat != repeat) {
        m_data->repeat = repeat;
        emit repeatChanged(repeat);
    }
}

int KScheduler::from() const
{
    return m_data->from;
}

void KScheduler::setFrom(int from)
{
    if(m_data->from != from) {
        m_data->from = from;
        emit fromChanged(m_data->from);
    }
}

int KScheduler::to() const
{
    return m_data->to;
}

void KScheduler::setTo(int to)
{
    if(m_data->to != to) {
        m_data->to = to;
        emit toChanged(to);
    }
}

bool KScheduler::runOnWeekends() const
{
    return m_data->runOnWeekends;
}

void KScheduler::setRunOnWeekends(bool run)
{
    if(m_data->runOnWeekends != run) {
        m_data->runOnWeekends = run;
        emit runOnWeekendsChanged(run);
    }
}

void KScheduler::start()
{
    m_data->timer->start();
}

void KScheduler::stop()
{
    m_data->timer->stop();
}

void KScheduler::timerTriggerHandle()
{
    if(timeToRun())
        emit triggered();
}

bool KScheduler::timeToRun()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    if(!m_data->runOnWeekends)
        if(currentDateTime.date().dayOfWeek() == Qt::Saturday
            || currentDateTime.date().dayOfWeek() == Qt::Sunday)
            return false;

    if(currentDateTime.time().hour() < m_data->from
        || currentDateTime.time().hour() > m_data->to)
        return false;

    return true;
}
