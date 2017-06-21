#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QKeyEvent>

#include "../game_objects/timer.h"
#include "../game_objects/user.h"
#include "../game_objects/player.h"
#include "../game_objects/goal.h"

#include "../game_objects/blockbuilder.h"
#include "../game_objects/blockwaiter.h"
#include "../game_objects/brokenblockbuilder.h"

#include "level.h"

class LevelScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer* _timer, User* _user, QWidget *parent = 0);
    ~LevelScene();

signals:
    void levelComplete();
    void levelFail();
    void didFirstInput();

public slots:
    void timeUpdate();
    void PlayerAnimation();
    void timerStart();
    void finishLevel();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    //  Для отрисовки окна окончания уровня
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity, int flag);
    void displayGameOverWindow(QString textToDisplay);

    //  Проверка на коллизии с блоками
    bool intersect(Player* player, QList<QGraphicsItem*> list);

    Timer* timer;
    User* user;
    Player* player;
    Goal* goal;

    bool isWin;
    bool hasKey;
    bool firstInput;

    // Вектор абстрактных блоков для каждого уровня
    QVector<AbstractBlock*> startBlocks;

    // Храним указатель для доступа к timerLabel
    QGraphicsView* view;
    QLabel* timerLabel;

    Level* level;

    // Блок для анимации полета
    int yAnimation;
    bool upAnimation;
    Timer* timerAnimation;
};

#endif // LEVELSCENE_H
