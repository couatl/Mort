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

    QGLWidget *OpenGLWidget;
private:
};

#endif // LEVELVIEW_H
