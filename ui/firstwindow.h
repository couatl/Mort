#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsPixmapItem>

#include "../game_objects/timer.h"
#include "../game_objects/user.h"

#include "view.h"

namespace Ui {
class FirstWindow;
}

class FirstWindow : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit FirstWindow(View* _view, QWidget *parent = 0, User* _user = nullptr);
    ~FirstWindow();

private slots:
    void ok_clicked();

signals:
    void ok_click();
    void destroy();

private:
    void writeMessage();

    User* user;

    Timer* timer_message;

    View* view;

    QGraphicsPixmapItem* background;
    QLabel* labelMessage;
    QLabel* errorMessage;
    QLineEdit* usernameLine;
    QPushButton* okButton;
};

#endif // FIRSTWINDOW_H
