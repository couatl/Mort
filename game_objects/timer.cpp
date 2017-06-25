#include "timer.h"
#include <QString>

Timer::Timer(QObject* parent, int _time, int _period, bool start):
    QTimer(parent), time(_time)
{
    this->setInterval(_period);
    if(start)
        this->start();
}

void Timer::decrease()
{
    time--;
}

QString Timer::getDecoratedTime()
{
    QString minutes = QString::number(getTime() / 60);
    QString seconds = "0";
    if (getTime() % 60 >= 10)
    {
        seconds = QString::number(getTime() % 60);
    }
    else
    {
        seconds += QString::number(getTime() % 60);
    }

    return QString(minutes + ":" + seconds);
}

void Timer::setTime(int _time)
{
    time = _time;
}
