#ifndef LEVEL_H
#define LEVEL_H

#include <QXmlStreamReader>

#include "../game_objects/player.h"
#include "../game_objects/goal.h"
#include "../game_objects/key.h"

#include "../game_objects/blockbuilder.h"
#include "../game_objects/blockwaiter.h"
#include "../game_objects/brokenblockbuilder.h"

class LevelScene;

class Level
{
public:
    explicit Level(LevelScene* _scene);
    ~Level();

    void loadLevel(int level);
    QVector<AbstractBlock*>& getBlocks() {
        return blocks;
    }

    Player* getPlayer() { return player; }
    Goal* getGoal() { return goal; }
    Key* getKey() { return key; }

private:
    QXmlStreamReader xmlReader;
    void parseCounts();
    void parseElements();
    void parseElement();

    BlockWaiter waiter;
    BlockBuilder builder;
    BrokenBlockBuilder builder_2;

    QVector<AbstractBlock*> blocks;
    Player* player;
    Goal* goal;
    Key* key;

    int countBlocks, countBrokenBlocks;

protected:
    LevelScene* scene;
};

#endif // LEVEL_H
