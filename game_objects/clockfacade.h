#ifndef CLOCKFACADE_H
#define CLOCKFACADE_H

#include <QVector>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "../game_objects/timer.h"
#include "../game_objects/user.h"
#include "../game_objects/clock.h"

//      Facade pattern

class ClockFacade
{
public:
    ClockFacade();
    ~ClockFacade();

    void read(QWidget* widget);
    void write();
    void hide();
    void show();
    void draw();
    int press(int &id_selected);

    void fail(int index);
    void succeed(int index);
    void stop(int index);
    int time(int index);

    QVector<Timer*> clock_timers;

private:
    QVector<Clock*> clocks;
};

#endif // CLOCKFACADE_H
