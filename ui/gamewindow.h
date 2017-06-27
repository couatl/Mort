#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "levelscene.h"
#include "levelview.h"

#include "../game_objects/user.h"
#include "../game_objects/timer.h"
#include "../game_objects/clock.h"

#include "../game_objects/clockfacade.h"

//  TODO: loading
//  TODO: jump 1) баг ходит после прыжка
//  TODO:      2) плохое считывание клавиш при прыжке

//  TODO: переделать под слоты/сигналы с индексом
//  TODO: uml-диаграммы

//  TODO: кроссплатформенность

//  TODO: архитектура уровня

//  TODO: лейблы с подсказками
//  TODO: информация об умершем
//  TODO: таймер в другом потоке


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

    void launchGame(int id);
    void completedGame(int id);
    void failedGame(int id);

//    void launchGame_1();
//    void completedGame_1();
//    void failedGame_1();

    void on_pushButton_clicked();

    void on_actionMute_triggered();

signals:
    void clicked(int id);
//    void clicked_1();
//    void clicked_2();
//    void clicked_3();

protected:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);

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

    int id_selected, idLevel;

    ClockFacade* clockFacade;

    QVector<QLabel*> times;

    QTimer* timer_message;

    QLabel* loading;
    QFont font;
    QPalette palette;

    LevelView* view;
    LevelScene* scene;

    QMediaPlayer* messagePlayer;
    QMediaPlayer* backgroundPlayer;
    QMediaPlayer* levelScenePlayer;
};

#endif // GAMEWINDOW_H
