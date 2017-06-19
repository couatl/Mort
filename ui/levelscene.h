#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QVector>
#include <QKeyEvent>

#include "../game_objects/timer.h"
#include "../game_objects/user.h"
#include "../game_objects/player.h"
#include "../game_objects/goal.h"

#include "../game_objects/blockbuilder.h"
#include "../game_objects/blockwaiter.h"

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
    void didFirstInput();

public slots:
    void timeUpdate();
    void playerAnimation();
    void timerStart();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Timer* timer;
    User* user;
    Player* player;

    bool hasKey;

    // Blocks for all levels
    QVector<AbstractBlock*> startBlocks;

    // to get timer label
    QGraphicsView* view;
    QLabel* timerLabel;

    QGraphicsPixmapItem* clockImage;

    Level* level;

    // flying animation
    int yAnimation;
    bool upAnimation;
    Timer* timerAnimation;

    bool firstInput;
};

#endif // LEVELSCENE_H
