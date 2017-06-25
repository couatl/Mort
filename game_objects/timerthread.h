#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include "timer.h"

class TimerThread: public QThread
{
    Timer* timer;
    void run();

public:
    TimerThread(Timer* _timer):
        timer(_timer)
    { }
    Timer* getTimer() {
        return timer;
    }
    int getTime() {
        return timer->getTime();
    }
    QString getDecoratedTime() {
        return timer->getDecoratedTime();
    }
private slots:
    void timeoutSlot();
};

#endif // TIMERTHREAD_H
