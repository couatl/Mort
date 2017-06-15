#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsItem>

class Block : public QGraphicsItem
{
public:
    explicit Block(int _x, int _y, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QPixmap blockImage;

    int x;
    int y;
};

#endif // BLOCK_H
