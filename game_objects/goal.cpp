#include "goal.h"

#include <QPainter>

Goal::Goal(int _x, int _y, QGraphicsItem *parent) : QGraphicsItem(parent),
    x(_x), y(_y)
{
    image = QPixmap(":/rsc/images/goal.png");
    image = image.scaled(86, 132, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    this->setPos(x,y);
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

QRectF Goal::boundingRect() const
{
    return QRectF(x, y, 86, 132);
}

void Goal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(x, y, image);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}
