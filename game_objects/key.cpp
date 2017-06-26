#include "key.h"

#include <QPainter>

Key::Key(int _x, int _y, QGraphicsItem *parent):
    x(_x), y(_y), QGraphicsItem(parent)
{
    image = QPixmap(":/rsc/images/key.png");
    image = image.scaled(35, 27, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

QRectF Key::boundingRect() const
{
    return QRectF(x, y, 35, 27);
}

void Key::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(x, y, image);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}
