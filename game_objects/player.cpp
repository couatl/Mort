#include "player.h"

#include <QPainter>

Player::Player(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    playerImage = QPixmap(":/rsc/images/Death_Character.png");
    playerImage = playerImage.scaled(128, 132, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //painter->drawPixmap();
    painter->drawPixmap(0, 150, playerImage);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, 128, 132);
}
