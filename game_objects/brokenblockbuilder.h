#ifndef BRPKENBLOCKBUILDER_H
#define BRPKENBLOCKBUILDER_H

#include "abstractblockbuilder.h"

#include <QDebug>

#define distance 138

class BrokenBlockBuilder: public AbstractBlockBuilder
{
protected:
    std::unique_ptr<AbstractBlock> secondBlock;

public:
    BrokenBlockBuilder(): AbstractBlockBuilder()
    {}
    ~BrokenBlockBuilder() {}

    QList<AbstractBlock*> getBlock() {
        qDebug() << "Broken get block";
        QList<AbstractBlock*> list;
        list.insert(0, block.release());
        list.insert(1, secondBlock.release());
        //list.push_back(block.release());
        //list.push_back(secondBlock.release());
        return list;
    }

    void createNewBlock(int x, int y) {
        qDebug() << "Broken create block";
        block.reset(new AbstractBlock(x, y));
        secondBlock.reset(new AbstractBlock(x + distance + 60, y));
    }

    void buildPixmap() {
        block->setImage(":/rsc/images/broken_left.png", 60);
        secondBlock->setImage(":/rsc/images/broken_right.png", 60);
    }
};

#endif // BRPKENBLOCKBUILDER_H
