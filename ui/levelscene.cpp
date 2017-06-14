#include "levelscene.h"

#include <QPalette>


LevelScene::LevelScene(QGraphicsView* _view, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    timer(_timer), user(_user),
    view(_view)
{
    this->setSceneRect(0, 0, 960, 540);
    QPixmap _background(":/rsc/images/bg.png");
    _background = _background.scaled(543, 540, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(_background));

    player = new Player();
    this->addItem(player);
}

LevelScene::~LevelScene() {

}
