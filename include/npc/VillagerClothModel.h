#ifndef NPC_VILLAGERCLOTHMODEL_H
#define NPC_VILLAGERCLOTHMODEL_H

#include "types.h"
#include "uptr.h"
#include "gfx/MatTexVramTask.h"
#include "npc/NpcResHandle.h"

class VillagerActor;

class VillagerClothModel {
public:
    VillagerClothModel() { construct(); }
    ~VillagerClothModel() { destruct(); }
    u16 *getItem();
    void release();
    BOOL change(VillagerActor *parent, u16 *id);
    void *buildTexture(VillagerActor *parent, u16 *id);
    BOOL init(VillagerActor *parent, u16 *id);
    VillagerClothModel *destruct();
    VillagerClothModel *construct();

    /* 0x00 */ u32 matTexTask[HOST_SIZED(0x28, MatTexVramTask) / 4] HOST_ALIGN8;
    /* 0x28 */ u16 clothItem;
    /* 0x2a */ u8 pad_2a[2];
    /* 0x2c */ u8 texPatBuf[HOST_SIZED(8, NpcClothTexHandle)] HOST_ALIGN8;
};

#endif
