#include "player.h"

#include <QPainter>

#include <QDebug>

Player::Player(int _x, int _y, QGraphicsItem *parent) : QGraphicsItem(parent),
    x(_x),
    y(_y),
    direction(1),
    yAnimation(0)
{
   // QImage image = QImage(":/rsc/images/Death_Character.png");
    playerImageRotate = QPixmap::fromImage(QImage(":/rsc/images/Death_Character.png").mirrored(true, false));
    playerImageRotate = playerImageRotate.scaled(128, 132, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    playerImage = QPixmap(":/rsc/images/Death_Character.png");
    playerImage = playerImage.scaled(128, 132, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    this->setPos(x,y);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(pos().x(), pos().y(), direction == 1 ? playerImage : playerImageRotate);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

    y = pos().y() - yAnimation;
}

QRectF Player::boundingRect() const {
    return QRectF(pos().x(), pos().y(), 128, 132+2*(14-yAnimation));
}

void Player::setYAnimation(int _yAnimation)
{
    yAnimation = _yAnimation;
}

void Player::setState(State _state){
    state = _state;
}

void Player::walk(bool right)
{
    int step = 25;
    if (right)
    {
        x=pos().x()+step;
    }
    else
    {
        x=pos().x()-step;
    }

    if (x < 0)
        x = 0;
}

void Player::fall()
{
    state = falling;
}

 void Player::rotate()
 {
    direction *= -1;
 }
