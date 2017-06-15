#include "player.h"

#include <QPainter>

Player::Player(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    playerImage = QPixmap(":/rsc/images/Death_Character.png");
    playerImage = playerImage.scaled(128, 132, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    x = 10;
    y = 305;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(x, y, playerImage);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

QRectF Player::boundingRect() const {
    return QRectF(x, y, 128, 132);
}
