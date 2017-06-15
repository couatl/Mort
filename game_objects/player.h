#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>

class Player : public QGraphicsItem
{
public:
    explicit Player(QGraphicsItem *parent = 0);
//    virtual ~Player();
//    void walk();
//    void jump();
//    void fall();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    enum State {
        stand,
        move
    };

    QPixmap playerImage;
    State state;
};

#endif // PLAYER_H
