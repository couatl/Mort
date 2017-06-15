#include "brokenblock.h"

#include <QPainter>

BrokenBlock::BrokenBlock(int _x, int _y, int _dist, QGraphicsItem *parent) :
    QGraphicsItem(parent), distance(_dist),
    x(_x), y(_y)
{
    leftBlock = QPixmap(":/rsc/images/broken_left.png");
    leftBlock = leftBlock.scaled(60, 87, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    rightBlock = QPixmap(":/rsc/images/broken_right.png");
    rightBlock = rightBlock.scaled(60, 87, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void BrokenBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(x, y, leftBlock);
    painter->drawPixmap(x + distance, y, rightBlock);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

QRectF BrokenBlock::boundingRect() const
{
    return QRectF(x, y, 60*2 + distance, 87);
}
