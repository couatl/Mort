#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPropertyAnimation>

#include "levelscene.h"

#include "../game_objects/user.h"
#include "../game_objects/timer.h"
#include "../game_objects/clock.h"

#include "../game_objects/clockfacade.h"

//  TODO: баг зависание игрока
//  TODO: мигание loading
//  TODO: экраны выключения/включения

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    void clearAll();
    void showAll();

private slots:
    void about();

    void startLoading();
    void endLoading();
    void processLoading();

    void launchGame_1();
    void completedGame_1();
    void failedGame_1();

    void on_pushButton_clicked();

signals:
    void clicked_1();
    void clicked_2();
    void clicked_3();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    //  Creating clock objects and setting images
    void drawClocks();

    //  Draws loading window background
    void drawLoading();

    //  Draws main window background
    void drawBackground();
    void drawShelf();

    // Clocks writing/reading from file
    void clockWrite();
    void clockRead();

    void writeMessage();

    QPropertyAnimation* animationStart;
    QPropertyAnimation* animationEnd;

    Ui::GameWindow *ui;

    User user;

    int id_selected;

    ClockFacade* clockFacade;

    QVector<QLabel*> times;

    QTimer* timer_message;

    QLabel* loading;
    QFont font;
    QPalette palette;

    LevelScene* scene;
};

#endif // GAMEWINDOW_H
