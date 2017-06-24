#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QObject>

class Timer: public QTimer
{
    Q_OBJECT
public:
    Timer(QObject* parent = nullptr, int _time = 61, int _period = 1000, bool start = true);
    virtual ~Timer() {}
    void decrease();

    inline int getTime() const
    { return time; }
    QString getDecoratedTime();

    void setTime(int _time);
private:
    int time;
};

#endif // TIMER_H
