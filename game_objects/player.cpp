#include "player.h"

#include <QPainter>

Player::Player(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    x = 10;
    y = 147;
    direction = 1;

    playerImageRotate = QPixmap::fromImage(QImage(":/rsc/images/Death_Character.png").mirrored(true, false));
    playerImageRotate = playerImageRotate.scaled(128, 132, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    playerImage = QPixmap(":/rsc/images/Death_Character.png");
    playerImage = playerImage.scaled(128, 132, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    setPos(x,y);
}

void Player::walk(bool right)
{
    int step = 25;
    if (right)
    {
        x = pos().x()+step;
    }
    else
    {
        x = pos().x()-step;
    }

    if (x < 0)
        x = 0;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(pos().x(), pos().y(), direction == 1 ? playerImage : playerImageRotate);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void Player::rotate()
{
   direction *= -1;
}

QRectF Player::boundingRect() const {
    return QRectF(pos().x(), pos().y(), 128, 132);
}
