#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QLabel>
#include <QWidget>
#include <QPushButton>

class View : public QGraphicsView   {
    Q_OBJECT

signals:
    void sceneChanged();

public:
    View();
    void sceneSet(QGraphicsScene *);
    void drawBackground();
};

#endif // VIEW_H
