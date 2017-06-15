#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>

class LevelScene;

class Level : public QWidget
{
    Q_OBJECT
public:
    explicit Level(LevelScene* _scene, QWidget *parent = 0);

signals:

public slots:

protected:
    LevelScene* scene;
};

#endif // LEVEL_H
