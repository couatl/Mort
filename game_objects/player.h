#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include "timer.h"

class Player : public QGraphicsItem
{
public:
    explicit Player(int _x, int _y, QGraphicsItem *parent = 0);

    enum State {
        normal,
        jumping,
        falling
    };

    void walk(bool right);
//    void jump();
    int getX() const { return x; }
    int getY() const { return y; }
    int getYAnimation() const { return yAnimation; }
    int getDirection() const { return direction; }
    State getState() const { return state; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);   

    void rotate();
    void setYAnimation(int _yAnimation);
    void setState(State _state);

public slots:
    void animation();

private:

    int x,y, direction, yAnimation;

    QPixmap playerImage, playerImageRotate;
    State state;
};

#endif // PLAYER_H
