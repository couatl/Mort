#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include "timer.h"

class Player : public QGraphicsItem
{
public:
    explicit Player(QGraphicsItem *parent = 0);

    void walk(bool right);
//    void jump();
//    void fall();

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    int getDirection() const {
        return direction;
    }

    void setX(int _x) {
        x = _x;
    }
    void setY(int _y) {
        y = _y;
    }
    void setXY(int _x, int _y) {
        x = _x;
        y = _y;
    }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void rotate();

public slots:
    void animation();

private:
    enum State {
        stand,
        move
    };

    QPixmap playerImage;
    QPixmap playerImageRotate;

    State state;

    int x;
    int y;
    int direction;
};

#endif // PLAYER_H
