#ifndef HOUSE_H
#define HOUSE_H

#include <QGraphicsItem>

class House: public QGraphicsItem
{
public:
    House(int _x, int _y, QGraphicsItem* parent = 0);
    virtual ~House() { }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap image;

    int x;
    int y;
};

#endif // HOUSE_H
