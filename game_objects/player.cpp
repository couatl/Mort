#include "player.h"

#include <QDebug>
#include <QPainter>

Player::Player(int _x, int _y, QGraphicsObject *parent) : QGraphicsObject(parent),
    x(_x),
    y(_y),
    direction(1),
    yAnimation(0),
    jumpFact(0)
{
   // QImage image = QImage(":/rsc/images/Death_Character.png");
    playerImageRotate = QPixmap::fromImage(QImage(":/rsc/images/Death_Character.png").mirrored(true, false));
    playerImageRotate = playerImageRotate.scaled(90, 93, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    playerImage = QPixmap(":/rsc/images/Death_Character.png");
    playerImage = playerImage.scaled(90, 93, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    this->setPos(x,y);

    jumpAnimation = new QPropertyAnimation(this);
    jumpAnimation->setTargetObject(this);
    jumpAnimation->setPropertyName("jumpFactor");
    jumpAnimation->setStartValue(0);
    jumpAnimation->setKeyValueAt(0.5, 1);
    jumpAnimation->setEndValue(0);
    jumpAnimation->setDuration(900);
    jumpAnimation->setEasingCurve(QEasingCurve::OutInSine);

    this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(pos().x(), pos().y(), direction == 1 ? playerImage : playerImageRotate);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
  
    y = pos().y() - yAnimation;
}

QRectF Player::boundingRect() const {
    return QRectF(pos().x(), pos().y(), 90, 93+2*(14-yAnimation));
}

void Player::setYAnimation(int _yAnimation)
{
    yAnimation = _yAnimation;
}

void Player::setState(State _state){
    state = _state;
}

void Player::setJumpFactor(const qreal& pos)
{
    if (pos == jumpFact)
           return;
    jumpFact = pos;

    emit jumpFactorChanged(jumpFact);
}

qreal Player::jumpFactor() const
{
    return jumpFact;
}

void Player::walk(bool right)
{
    int step = 25;
    if (right)
    {
        x = pos().x() + step;
    }
    else
    {
        x = pos().x() - step;
    }
    if (x < 0)
        x = 0;
}

void Player::jump() {
    if (QAbstractAnimation::Stopped == jumpAnimation->state()) {
        state = jumping;
        jumpAnimation->start();
        emit signalJump();
    }
}

void Player::fall()
{
    state = falling;
}

 void Player::rotate()
 {
    direction *= -1;
 }
