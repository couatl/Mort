#include "timer.h"

Timer::Timer(QObject* parent, int _time):
    QTimer(parent), time(_time)
{
    this->start(1000);
}

void Timer::stop()
{
    this->stop();
}

void Timer::decrease()
{
    time--;
}
