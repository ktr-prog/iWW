#ifndef TOWN_TOWNBLOCKMAP_H
#define TOWN_TOWNBLOCKMAP_H

#include "types.h"
#include "town/BlockMap.h"

class TownBlockMap : public BlockMap {
public:
    void releaseBg();
    void bindBg();
    void updateAcreIds();
    void freeBlocks(void *heap);
    BOOL build(void *heap);
    void clear();
};

#endif
