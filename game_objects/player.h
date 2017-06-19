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

    void fall();
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
    
    void animation();

private:
    QPixmap playerImage;
    QPixmap playerImageRotate;

    QPixmap playerImage, playerImageRotate;
    State state;

    int x;
    int y;
    int direction;
    int yAnimation;
};

#endif // PLAYER_H
