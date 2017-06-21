#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // Конструктор
    Button(QString name, QFont font, QGraphicsItem* parent=NULL);

    // Методы событий
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();

private:
    QGraphicsTextItem* text;
};

#endif // BUTTON_H
