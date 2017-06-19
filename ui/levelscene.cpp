#include "levelscene.h"

#include <QPalette>
#include <QThread>

#include <QDebug>

LevelScene::LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    timer(_timer), user(_user),
    startBlocks(QVector<AbstractBlock*>(10)),
    view(_view),
    timerLabel(_timerLabel),
    yAnimation(0),
    upAnimation(true),
    timerAnimation(new Timer(this, 60, 20)),
    firstInput(false)
{   
    this->setSceneRect(0, 0, 960, 540);
    QPixmap _background(":/rsc/images/bg.png");
    _background = _background.scaled(543, 540, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(_background));

    player = new Player(0, 0);
    this->addItem(player);

    // Block Building
    BlockWaiter waiter;
    BlockBuilder builder;
    waiter.setBlockBuilder(&builder);
    for (int i = 0; i < 10; i++)  {
        waiter.constructBlock(i*86, 453);
        startBlocks[i] = waiter.getBlock();
        addItem(startBlocks[i]);
    }

    for (int i = 0; i < 4; i++)  {
            startBlocks[i] = new Block(0 + i*86, 453);
            this->addItem(startBlocks[i]);
    }

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

    timerAnimation->moveToThread(QThread::currentThread());

    connect(timerAnimation, &Timer::timeout, this, &LevelScene::playerAnimation);
    connect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
    connect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);
}

LevelScene::~LevelScene() {
    delete player;
    for (int i = 0; i < 4; i++)  {
        delete startBlocks[i];
    }
    delete timerAnimation;
}

void LevelScene::playerAnimation()
{
    //falling
    int isFall = player->getState() == Player::falling ? 2 : 0;

    //flying animation
    if (isFall == 0)
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
    player->setPos(player->getX()==player->pos().x() ? player->pos().x() :
                                                       player->pos().x() + player->getDirection(),
                   (player->getY() + yAnimation + isFall));

    if (player->collidingItems().isEmpty())
    {
        player->setState(Player::falling);
    }
    else if (player->getState() == Player::falling)
    {
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
    else if (key == Qt::Key_Space || key == Qt::Key_Up ||
             key == Qt::Key_W) {
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
        return;
    }
    else if(timer->getTime() == 0)
    {
        timerLabel->setStyleSheet("QLabel { color : red; }");
        timerLabel->setText("0:00");
        timer->stop();
        emit levelFail();
        return;
    }
}
