#include "levelscene.h"

#include <QPalette>
#include <QThread>

#include <QDebug>

LevelScene::LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    timer(_timer),
    user(_user),
    startBlocks(QVector<AbstractBlock*>(13)),
    view(_view),
    timerLabel(_timerLabel),
    yAnimation(0),
    upAnimation(true),
    timerAnimation(new Timer(this, 60, 20)),
    firstInput(false)
{
    // ширина равна 86 (ширина 1 блока) * 24
    this->setSceneRect(0, 0, 2064, 520);
    QPixmap _background(":/rsc/images/bg.png");
    _background = _background.scaled(543, 540, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(_background));
      
    player = new Player(0, 0);
    this->addItem(player);

    // Block Building
    BlockWaiter waiter;
    BlockBuilder builder;
    waiter.setBlockBuilder(&builder);
    for (int i = 0; i < 8; i++)  {
        waiter.constructBlock(i*86, 453);
        startBlocks[i] = waiter.getBlock().first();
        addItem(startBlocks[i]);
    }

    BrokenBlockBuilder builder_2;
    waiter.setBlockBuilder(&builder_2);
    waiter.constructBlock(8*86, 453);
    QList<AbstractBlock*> blockList = waiter.getBlock();
    startBlocks[8] = blockList.first();
    startBlocks[9] = blockList.last();
    addItem(startBlocks[8]);
    addItem(startBlocks[9]);
    waiter.constructBlock(11*86, 453);
    blockList = waiter.getBlock();
    startBlocks[10] = blockList.first();
    startBlocks[11] = blockList.last();
    addItem(startBlocks[10]);
    addItem(startBlocks[11]);

    timerLabel->setText(timer->getDecoratedTime());
    if (timer->getTime() <= 10)
        timerLabel->setStyleSheet("QLabel { color : red; }");

    timerAnimation->moveToThread(QThread::currentThread());

    connect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
    connect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
    connect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);
}

LevelScene::~LevelScene() {
    delete player;
    for (int i = 0; i < 4; i++)  {
        delete startBlocks[i];
    }
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
    case Qt::Key_W:
        // TODO: jump
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
        timerLabel->setText(timer->getDecoratedTime());
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
