#include "levelscene.h"

#include <QPalette>
#include <QDebug>

LevelScene::LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    timer(_timer),
    user(_user),
    startBlocks(QVector<Block*>(10)),
    view(_view),
    timerLabel(_timerLabel),
    yAnimation(0),
    upAnimation(true),
    timerAnimation(new Timer(nullptr, 60, 20)),
    firstInput(false)
{
    this->setSceneRect(0, 0, 960, 540);
    QPixmap _background(":/rsc/images/bg.png");
    _background = _background.scaled(543, 540, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(_background));

    for (int i = 0; i < 10; i++)  {
        int j = i<4 ? i : i+2;
        startBlocks[i] = new Block(0 + j*86, 453);
        this->addItem(startBlocks[i]);
    }

    broken = new BrokenBlock(startBlocks[3]->boundingRect().topRight().x(), 453);
    this->addItem(broken);

    QString minutes = QString::number(timer->getTime() / 60);
    QString seconds = "0";
    if (timer->getTime() % 60 >= 10)
    {
        seconds = QString::number(timer->getTime() % 60);
    }
    else
    {
        seconds += QString::number(timer->getTime() % 60);
    }

    this->addItem(new Block(50,250));

    player = new Player(0, 0);
    this->addItem(player);

    timerLabel->setText(minutes + ":" + seconds);
    if (timer->getTime() <= 10)
        timerLabel->setStyleSheet("QLabel { color : red; }");

    connect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
    connect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
    connect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);
}

LevelScene::~LevelScene() {
    delete player;
    for (int i = 0; i < 4; i++)  {
              delete startBlocks[i];
          }
    delete broken;
    delete timerAnimation;
}

void LevelScene::PlayerAnimation()
{
    if (player->pos().y()>=(540-132)/2)
    {
        disconnect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
        disconnect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
        emit levelFail();
    }

    //falling
    int isFall = player->getState()==Player::falling ? 2 : 0;

    //flying animation
    if (isFall==0)
    {
        if (yAnimation==14 || yAnimation==-14)
        {
            upAnimation = !upAnimation;
        }
        if (upAnimation)
        {
            yAnimation++;
        }
        else
        {
            yAnimation--;
        }
        player->setYAnimation(yAnimation);
    }

    //apply changes
    player->setPos(player->getX()==player->pos().x() ? player->pos().x() : player->pos().x()+player->getDirection(), (player->getY()+yAnimation+isFall));

    if (player->collidingItems().isEmpty())
    {
        player->setState(Player::falling);
    }
    else if (player->getState() == Player::falling)
    {
        if (intersect(player, player->collidingItems()))
           player->setState(Player::normal);
    }

    //qDebug() << player->collidingItems();
}

void LevelScene::timerStart()
{
    timer->start();
    disconnect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);
}

void LevelScene::keyPressEvent(QKeyEvent *event)
{
    if (!firstInput)  {
        firstInput = true;
        emit didFirstInput();
    }

    switch (event->key()) {
    case Qt::Key_Right:
    case Qt::Key_D:
        if (player->getDirection() == -1)
            player->rotate();
        player->walk(true);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if (player->getDirection() == 1)
            player->rotate();
        player->walk(false);
        break;
    case Qt::Key_Space:
    case Qt::Key_Up:
        //jump()
        break;
    }
}

void LevelScene::timeUpdate()
{
    if (timer->getTime() == 0) {
        timerLabel->setStyleSheet("QLabel { color : red; }");
        timerLabel->setText("0:00");
        timer->stop();
        emit levelFail();
        return;
    }

    timer->decrease();
    if(timer->getTime() > 0) {
        QString minutes = QString::number(timer->getTime() / 60);
        QString seconds = "0";
        if (timer->getTime() % 60 >= 10)
        {
            seconds = QString::number(timer->getTime() % 60);
        }
        else
        {
            seconds += QString::number(timer->getTime() % 60);
        }

        timerLabel->setText(minutes + ":" + seconds);
        if (timer->getTime() <= 10)
            timerLabel->setStyleSheet("QLabel { color : red; }");
    }
    else if(timer->getTime() == 0)
    {
        timerLabel->setStyleSheet("QLabel { color : red; }");
        timerLabel->setText("0:00");
        timer->stop();
        emit levelFail();
    }
}

bool LevelScene::intersect(Player* player,QList<QGraphicsItem*> list)
{
    for (auto i: list)
    {
        if (player->boundingRect().y()*2+player->boundingRect().height() - i->boundingRect().top() <= 3)
        {
            qDebug() << player->boundingRect() << i->boundingRect().top();
            return true;
        }
    }
    return false;
}
