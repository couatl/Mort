#ifndef BLOCKBUILDER_H
#define BLOCKBUILDER_H

#include "abstractblockbuilder.h"

class BlockBuilder: public AbstractBlockBuilder
{
public:
    BlockBuilder() :  AbstractBlockBuilder() {}
    ~BlockBuilder() {}

    void buildPixmap();
};

#endif // BLOCKBUILDER_H
