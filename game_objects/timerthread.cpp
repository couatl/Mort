#include "timerthread.h"

void TimerThread::run()
{
    timer->start();
    connect(timer, &Timer::timeout, this, &TimerThread::timeoutSlot);
}

void TimerThread::timeoutSlot()
{
}
