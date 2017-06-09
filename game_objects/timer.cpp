#include "timer.h"

Timer::Timer(QObject* parent, int _time):
    QTimer(parent), time(_time)
{
    this->start(1000);
}

void Timer::decrease()
{
    time--;
}

void Timer::setTime(int _time)
{
    time = _time;
}
