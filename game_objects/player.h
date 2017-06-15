#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>

class Player : public QGraphicsItem
{
public:
    explicit Player(QGraphicsItem *parent = 0);

//    void walk();
//    void jump();
//    void fall();

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
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

private:
    enum State {
        stand,
        move
    };

    QPixmap playerImage;
    State state;

    int x;
    int y;
};

#endif // PLAYER_H
