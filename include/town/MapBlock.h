#ifndef TOWN_MAPBLOCK_H
#define TOWN_MAPBLOCK_H

#include "types.h"
#include "uptr.h"
#include "gfx/VecFx32.h"
#include "town/MapBlockAcre.h"

class BgAcreModel;

class MapBlock {
public:
    void clear();
    void bindBg(BgAcreModel *s, void *bcl, u32 mapSlot);
    void init(s32 a, VecFx32 *v, u16 *layer0, u16 *layer1, u16 *buriedMask, BgAcreModel *k2, void *bcl, s32 k4, s32 k5,
              u32 mapSlot);

    s32 acreId;
    s32 blockX;
    s32 blockZ;
    VecFx32 pos;
    u16 *layers[2];
    BgAcreModel *bgModel;
    u16 *buried;
};


#endif
