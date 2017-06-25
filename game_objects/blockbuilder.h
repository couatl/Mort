#ifndef BLOCKBUILDER_H
#define BLOCKBUILDER_H

#include "abstractblockbuilder.h"

class BlockBuilder: public AbstractBlockBuilder
{
public:
    BlockBuilder() :  AbstractBlockBuilder() {}
    ~BlockBuilder() {}

    void buildPixmap() {
        block->setImage(":/rsc/images/tile.png", 86);
    }
    void buildType() {
        block->setType(AbstractBlock::Block);
    }
};

#endif // BLOCKBUILDER_H
