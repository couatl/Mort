#ifndef BROKENBLOCK_H
#define BROKENBLOCK_H

#include <QGraphicsItem>

class BrokenBlock : public QGraphicsItem
{
public:
    explicit BrokenBlock(int _x, int _y, int _dist = 130, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QPixmap leftBlock;
    QPixmap rightBlock;

    int distance;

    int x;
    int y;
};

#endif // BROKENBLOCK_H
