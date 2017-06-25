#include "button.h"

#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>

Button::Button(QString name, QFont font, QGraphicsItem *parent): QGraphicsRectItem(parent){
    // Рисуется прямоугольник
    setRect(0,0,100,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    setBrush(brush);

    // Текст кнопки
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2- text->boundingRect().width()+2;
    int yPos = rect().height()/4 - text->boundingRect().height()/2-4;
    text->setPos(xPos,yPos);
    text->setFont(font);

    // Подключаем реакцию на hover-события
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
    // Смена цвета на серый
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);
    emit clicked();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
    // Смена цвета на белый
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    setBrush(brush);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->ignore();
    // Смена цвета на светло-серый
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::lightGray);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->ignore();
    // Смена цвета на белый
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    setBrush(brush);
}
