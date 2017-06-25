#ifndef BRPKENBLOCKBUILDER_H
#define BRPKENBLOCKBUILDER_H

#include "abstractblockbuilder.h"

#define DISTANCE 138
#define WIDTH 60

class BrokenBlockBuilder: public AbstractBlockBuilder
{
protected:
    std::unique_ptr<AbstractBlock> secondBlock;

public:
    BrokenBlockBuilder(): AbstractBlockBuilder()
    {}
    ~BrokenBlockBuilder() {}

    QList<AbstractBlock*> getBlock() {
        QList<AbstractBlock*> list;
        list.insert(0, block.release());
        list.insert(1, secondBlock.release());
        return list;
    }

    void createNewBlock(int x, int y) {
        block.reset(new AbstractBlock(x, y));
        secondBlock.reset(new AbstractBlock(x + DISTANCE + WIDTH, y));
    }

    void buildPixmap() {
        block->setImage(":/rsc/images/broken_left.png", WIDTH);
        secondBlock->setImage(":/rsc/images/broken_right.png", WIDTH);
    }
    void buildType() {
        block->setType(AbstractBlock::BrokenBlock);
        secondBlock->setType(AbstractBlock::BrokenBlock);
    }
};

#endif // BRPKENBLOCKBUILDER_H
