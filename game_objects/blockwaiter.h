#ifndef BLOCKWAITER_H
#define BLOCKWAITER_H

#include "abstractblockbuilder.h"

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
    AbstractBlock* getBlock() const {
        return builder->getBlock();
    }
    void constructBlock(int x, int y){
        builder->createNewBlock(x, y);
        builder->buildPixmap();
    }

};

#endif // BLOCKWAITER_H
