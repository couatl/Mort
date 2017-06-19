#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QGraphicsItem>

class AbstractBlock : public QGraphicsItem
{
public:
    AbstractBlock(int _x = 0, int _y = 0, QGraphicsItem *parent = 0, int _width = 86, const QString& path = "");

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setImage(const QString& path, int _width);
    void setXY(int _x, int _y);

protected:
    QPixmap blockImage;

    int width;

    int x;
    int y;
};

#endif // ABSTRACTBLOCK_H
