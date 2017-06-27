#ifndef GOAL_H
#define GOAL_H

#include <QGraphicsItem>

class Goal : public QGraphicsItem
{
public:
    explicit Goal(int _x = 0, int _y = 0, QGraphicsItem *parent = 0);
    virtual ~Goal() { }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPixmap image;

    int x;
    int y;
};

#endif // GOAL_H
