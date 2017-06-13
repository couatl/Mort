#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QVector>

#include "../game_objects/user.h"
#include "../game_objects/timer.h"
#include "../game_objects/clock.h"

#include "firstwindow.h"
#include "view.h"
#include "mainscene.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    void firstWindow();
    void startLoading();
    void clearAll();
    void showAll();

private slots:
    void about();
    void update();

    void endLoading();
    void afterLoading();

    void firstWindowClosed();

    void launchGame_1();

signals:
    void clicked_1();
    void clicked_2();
    void clicked_3();

    void loadingEnd();


protected:
    //void mousePressEvent(QMouseEvent* event);

private:
    void createScene();

    //  Creating clock objects and setting images
    void drawClocks();

    //  Draws loading window background
    void drawLoading();

    //  Draws main window background
    void drawBackground();
    void drawShelf();

    // Clocks writing/reading from file
    void clockWrite();
    void clockRead(bool first_input);

    Ui::GameWindow *ui;

    User user;

    int id_selected;
    int mode;

//    QVector<Timer*> timers;
    QVector<Clock*> clocks;
//    QVector<QLabel*> times;

    View* view;

    FirstWindow* first;
    MainScene* main;
};

#endif // GAMEWINDOW_H
