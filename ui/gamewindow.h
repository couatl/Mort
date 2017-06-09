#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "../game_objects/user.h"
#include "../game_objects/timer.h"

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
    Ui::GameWindow *ui;
    User user;
    Timer* timer;
};

#endif // GAMEWINDOW_H
