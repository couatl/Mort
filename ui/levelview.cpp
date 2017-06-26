#include "levelview.h"

LevelView::LevelView(QWidget *parent):
    QGraphicsView(parent)
{
    setFixedSize(960, 540);
    // OpenGL
    setCacheMode(QGraphicsView::CacheBackground);
    setRenderHint(QPainter::Antialiasing);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGLFormat fmt(QGL::SampleBuffers | QGL::DirectRendering);
    fmt.setSwapInterval(0);
    fmt.setDoubleBuffer(false);
    OpenGLWidget = new QGLWidget(fmt);
    setViewport(OpenGLWidget);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

LevelView::~LevelView()
{
    delete OpenGLWidget;
}
