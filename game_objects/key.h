#ifndef KEY_H
#define KEY_H

#include <QGraphicsItem>

class Key: public QGraphicsItem
{
public:
    Key(int _x, int _y, QGraphicsItem* parent = 0);
    virtual ~Key() { }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap image;

    int x;
    int y;
};

#endif // KEY_H
