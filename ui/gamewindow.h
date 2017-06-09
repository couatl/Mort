#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "../game_objects/user.h"
#include "../game_objects/timer.h"
#include "../game_objects/clock.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

private slots:
    void about();
    void update();

private:

    void drawClocks();
    void drawBackground();
    void clockWrite();
    void clockRead(bool first_input);

    Ui::GameWindow *ui;
    User user;

    QVector<Timer*> timers;
    QVector<Clock*> clocks;
    QVector<QLabel*> times;
};

#endif // GAMEWINDOW_H
