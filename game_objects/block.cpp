#include "block.h"

#include <QPainter>

Block::Block(int _x, int _y, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    x(_x), y(_y)
{
    blockImage = QPixmap(":/rsc/images/tile.png");
    blockImage = blockImage.scaled(86, 87, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(x, y, blockImage);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

QRectF Block::boundingRect() const
{
    return QRectF(x, y, 86, 87);
}
