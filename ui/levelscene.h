#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>

#include "../game_objects/timer.h"
#include "../game_objects/user.h"
#include "../game_objects/player.h"

class LevelScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit LevelScene(QGraphicsView* _view, Timer* _timer, User* _user, QWidget *parent = 0);
    ~LevelScene();

signals:

public slots:

private:
    Timer* timer;
    User* user;
    Player* player;

    // to get timer label
    QGraphicsView* view;

    QGraphicsPixmapItem* clockImage;
};

#endif // LEVELSCENE_H
