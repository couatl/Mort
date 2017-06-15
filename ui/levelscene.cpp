#include "levelscene.h"

#include <QPalette>

#include <QDebug>


LevelScene::LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    view(_view), timerLabel(_timerLabel),
    timer(_timer), user(_user),
    startBlocks(QVector<Block*>(4))
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
//    qDebug() << startBlocks[3]->boundingRect().topRight().x();
    broken = new BrokenBlock(startBlocks[3]->boundingRect().topRight().x(), 453);
    this->addItem(broken);

    timer->start();
    connect(timer, &Timer::timeout, this, &LevelScene::update);
}

LevelScene::~LevelScene() {
    delete player;
    for (int i = 0; i < 4; i++)  {
        delete startBlocks[i];
    }
    delete broken;
}

void LevelScene::update()
{
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
