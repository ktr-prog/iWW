#ifndef TOWN_TOWNMAP_H
#define TOWN_TOWNMAP_H

#include "types.h"
#include "item/ItemId.h"
#include "gfx/VecFx32.h"
#include "town/MapBlockEntry.h"


struct AcreItemGrid {
    ItemId e[0x100];
    AcreItemGrid();
    ~AcreItemGrid();
};

extern "C" void BuriedMask_Construct();
extern "C" void BuriedMask_Destruct();
struct BuriedMask {
    u8 data[0x20];
    BuriedMask() { BuriedMask_Construct(); }
    ~BuriedMask() { BuriedMask_Destruct(); }
};

class TownMap {
public:
    u8 acres[0x24];
    AcreItemGrid items[16];
    BuriedMask buried[16];
    u8 grassType : 2;
    u8 groundSeason : 6;

    TownMap();
    ~TownMap();

    MapBlockEntry *buildBlockEntries(void *heap);
    void updateGroundSeason();
    u32 getGrassType();
    BOOL toTownAcreIndex(Vec2 *out, Vec2 *in);
    BOOL isTownAcre(s32 x, s32 y);
    u16 *getAcreBuried(Vec2 *in);
    u16 *getAcreItems(Vec2 *in);
    void clear();
};

#endif
