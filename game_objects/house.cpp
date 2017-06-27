#include "house.h"

#include <QPainter>

House::House(int _x, int _y, QGraphicsItem *parent) : QGraphicsItem(parent),
    x(_x), y(_y)
{
    image = QPixmap(":/rsc/images/house.png");
    image = image.scaled(284, 240, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

QRectF House::boundingRect() const
{
    return QRectF(x, y, 284, 240);
}

void House::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(x, y, image);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}
