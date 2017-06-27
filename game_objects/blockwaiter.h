#ifndef BLOCKWAITER_H
#define BLOCKWAITER_H

#include "abstractblockbuilder.h"
#include <QDebug>

class BlockWaiter
{
private:
    AbstractBlockBuilder* builder;

public:
    BlockWaiter(): builder(nullptr) {}
    ~BlockWaiter() {}

    void setBlockBuilder(AbstractBlockBuilder* b) {
        builder = b;
    }

    QList<AbstractBlock*> getBlock() const {
        return builder->getBlock();
    }

    void constructBlock(int x, int y){
        builder->createNewBlock(x, y);
        builder->buildPixmap();
        builder->buildType();
    }
};

#endif // BLOCKWAITER_H
