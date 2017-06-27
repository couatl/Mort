#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QKeyEvent>
#include <QMediaPlayer>


#include "../game_objects/timer.h"
#include "../game_objects/user.h"
#include "../game_objects/house.h"
#include "../game_objects/key.h"

#include "level.h"

class LevelScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer* _timer, User* _user, QWidget *parent = 0);
    ~LevelScene();

    Timer* getTimerAnimation()
    { return timerAnimation; }

signals:
    void levelComplete();
    void levelFail();
    void didFirstInput();

public slots:
    void timeUpdate();
    void PlayerAnimation();
    void timerStart();
    void finishLevel();
    void playerJump(qreal factor);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    //  Для отрисовки окна окончания уровня
    void displayGameOverWindow(QString textToDisplay);

    //  Проверка на коллизии с блоками
    bool intersect(Player* player, QList<QGraphicsItem*> list);

    Timer* timer;
    User* user;
    Player* player;
    Key* key;
    Goal* goal;
    House* house;

    bool isWin;
    bool hasKey;
    bool firstInput;

    // Храним указатель для доступа к timerLabel
    QGraphicsView* view;
    QLabel* timerLabel;

    // Фасад уровня
    Level* level;

    // Блок для анимации полета
    int yAnimation;
    bool upAnimation;
    Timer* timerAnimation;

    int countMoved;
    int groundLevel;

    QGraphicsSimpleTextItem* timerText;
    QGraphicsPixmapItem* keyLabel;

    QMediaPlayer* keyPlayer;

};

#endif // LEVELSCENE_H
