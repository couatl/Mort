#ifndef ABSTRACTBLOCKBUILDER_H
#define ABSTRACTBLOCKBUILDER_H

#include "abstractblock.h"
#include <QList>
#include <memory>

class AbstractBlockBuilder
{
protected:
    std::unique_ptr<AbstractBlock> block;

public:
    AbstractBlockBuilder() {}
    virtual ~AbstractBlockBuilder() {}

    virtual QList<AbstractBlock*> getBlock() {
        QList<AbstractBlock*> list;
        list.push_back(block.release());
        return list;
    }

    virtual void createNewBlock(int x, int y) {
        block.reset(new AbstractBlock(x, y));
    }

    virtual void buildPixmap() = 0;
};

#endif // ABSTRACTBLOCKBUILDER_H
