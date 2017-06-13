#include "view.h"

View::View() {
    this->setFixedSize(QSize(960, 540));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::sceneSet(QGraphicsScene *scene) {
    setScene(scene);
    emit sceneChanged();
}


