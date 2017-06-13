#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QVector>
#include <QGraphicsTextItem>

#include "view.h"

#include "../game_objects/clock.h"
#include "../game_objects/timer.h"

class MainScene : public QWidget
{
    Q_OBJECT
public:
    explicit MainScene(QWidget *parent = 0);
//    void drawBackground();
//    void drawShelf();
//    void drawClocks();

signals:

public slots:

private:
    QVector<Clock*> clocks;
    QVector<Timer*> timers;

    QVector<QGraphicsTextItem*> times;
};

#endif // MAINSCENE_H
