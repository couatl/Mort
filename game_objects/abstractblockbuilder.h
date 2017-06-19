#ifndef ABSTRACTBLOCKBUILDER_H
#define ABSTRACTBLOCKBUILDER_H

#include "abstractblock.h"
#include <memory>

class AbstractBlockBuilder
{
protected:
    std::unique_ptr<AbstractBlock> block;

public:
    AbstractBlockBuilder() {}
    virtual ~AbstractBlockBuilder() {}

    AbstractBlock* getBlock() {
        return block.release();
    }

    void createNewBlock(int x, int y) {
        block.reset(new AbstractBlock(x, y));
    }

    virtual void buildPixmap() = 0;
};

#endif // ABSTRACTBLOCKBUILDER_H
