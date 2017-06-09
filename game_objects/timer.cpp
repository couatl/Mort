#include "timer.h"

Timer::Timer(QObject* parent, int _time, int _period):
    QTimer(parent), time(_time)
{
    this->start(_period);
}

void Timer::decrease()
{
    time--;
}

void Timer::setTime(int _time)
{
    time = _time;
}
