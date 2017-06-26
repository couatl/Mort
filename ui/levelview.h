#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#include <QGraphicsView>
#include <QGLFormat>

class LevelView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LevelView(QWidget *parent = nullptr);
    ~LevelView();

private:
    QGLWidget *OpenGLWidget;
};

#endif // LEVELVIEW_H
