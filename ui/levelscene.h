#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QVector>

#include "../game_objects/timer.h"
#include "../game_objects/user.h"
#include "../game_objects/player.h"
#include "../game_objects/block.h"
#include "../game_objects/goal.h"
#include "../game_objects/brokenblock.h"

#include "level.h"

class LevelScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer* _timer, User* _user, QWidget *parent = 0);
//    explicit LevelScene(int level_id, QGraphicsView* _view, Timer* _timer, User* _user, QWidget *parent = 0);
    ~LevelScene();

signals:
    void levelComplete();
    void levelFail();

public slots:
    void update();

private:
    Timer* timer;
    User* user;
    Player* player;

    bool hasKey;

    // 4 start blocks for all levels
    QVector<Block*> startBlocks;

    BrokenBlock* broken;

    // to get timer label
    QGraphicsView* view;
    QLabel* timerLabel;

    QGraphicsPixmapItem* clockImage;

    Level* level;
};

#endif // LEVELSCENE_H
