#include "levelscene.h"

#include <QPalette>

#include <QDebug>

LevelScene::LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    view(_view), timer(_timer),
    timerLabel(_timerLabel), user(_user),
    startBlocks(QVector<Block*>(4)),
    yAnimation(0),
    upAnimation(true),
    timerAnimation(new Timer(nullptr, 60, 20)),
    firstInput(false)
{   
    this->setSceneRect(0, 0, 960, 540);
    QPixmap _background(":/rsc/images/bg.png");
    _background = _background.scaled(543, 540, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(_background));

    player = new Player();
    this->addItem(player);

    for (int i = 0; i < 4; i++)  {
        startBlocks[i] = new Block(0 + i*86, 453);
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

    timerLabel->setText(minutes + ":" + seconds);
    if (timer->getTime() <= 10)
        timerLabel->setStyleSheet("QLabel { color : red; }");

    connect(timerAnimation, &Timer::timeout, this, &LevelScene::playerAnimation);
    connect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
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

void LevelScene::playerAnimation()
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
    player->setPos(player->getX()==player->pos().x() ? player->pos().x() : player->pos().x()+(player->pos().x() > player->getX() ? -1 : 1), player->getY()+yAnimation);
}

void LevelScene::timerStart()
{
    timer->start();
}

void LevelScene::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if (!firstInput)  {
        firstInput = true;
        emit didFirstInput();
    }

    if (key == Qt::Key_Right || key == Qt::Key_D) {
        if (player->getDirection() == -1)
            player->rotate();
        player->walk(true);
    }
    else if (key == Qt::Key_Left || key == Qt::Key_A) {
        if (player->getDirection() == 1)
            player->rotate();
        player->walk(false);
    }
    else if (key == Qt::Key_Space || key == Qt::Key_Up) {
        // TODO: jump
    }
}

void LevelScene::timeUpdate()
{
    if (timer->getTime() == 0) {
        timerLabel->setStyleSheet("QLabel { color : red; }");
        timerLabel->setText("0:00");
        timer->stop();
        emit levelFail();
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
