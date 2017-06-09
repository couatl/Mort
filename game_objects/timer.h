#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QObject>

class Timer: public QTimer
{
    Q_OBJECT
public:
    Timer(QObject* parent = nullptr, int _time = 60);
    void stop();
    void decrease();

    int getTime() const
    { return time; }

private:
    int time;
};

#endif // TIMER_H
