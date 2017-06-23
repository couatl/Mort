#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include "timer.h"

class Player : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor
                                   NOTIFY jumpFactorChanged)

public:
    explicit Player(int _x, int _y, QGraphicsObject *parent = 0);
    virtual ~Player() {}

    enum State {
        normal,
        jumping,
        falling
    };

    void walk(bool right);
    void jump();

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

    void setJumpFactor(const qreal& pos);
    qreal jumpFactor() const;

    QPropertyAnimation* jumpAnimation;
signals:
    void jumpFactorChanged(qreal);
    void signalJump();

public slots:

private:
    QPixmap playerImage;
    QPixmap playerImageRotate;

    State state;

    int x;
    int y;

    int direction;
    int yAnimation;

    qreal jumpFact;
};

#endif // PLAYER_H
