#include "abstractblock.h"

#include <QPainter>

AbstractBlock::AbstractBlock(int _x, int _y, QGraphicsItem *parent, int _width, const QString &path):
    QGraphicsItem(parent),
    width(_width),
    x(_x), y(_y)
{
    if (path != "")  {
        blockImage = QPixmap(path);
        blockImage = blockImage.scaled(width, 87, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }

    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

void AbstractBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(x, y, blockImage);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

QRectF AbstractBlock::boundingRect() const
{
    return QRectF(x, y, width, 87);
}

void AbstractBlock::setImage(const QString &path, int _width)
{
    if (path == "")  {
        return;
    }

    width = _width;
    blockImage = QPixmap(path);
    blockImage = blockImage.scaled(width, 87, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void AbstractBlock::setXY(int _x, int _y)
{
    x = _x;
    y = _y;
}

void AbstractBlock::setType(AbstractBlock::BlockType _type)
{
    m_type = _type;
}
