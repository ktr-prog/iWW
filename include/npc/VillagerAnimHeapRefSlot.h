#ifndef NPC_VILLAGERANIMHEAPREFSLOT_H
#define NPC_VILLAGERANIMHEAPREFSLOT_H

#include "types.h"
#include "npc/NpcResPool.h"

extern "C" void VillagerAnimHeapRef_Init(s32 *p);
extern "C" void VillagerAnimHeapRef_Deinit();
struct VillagerAnimHeapRef {
    /* 0x0 */ u32 slot;
    VillagerAnimHeapRef() { VillagerAnimHeapRef_Init((s32 *)&slot); }
    ~VillagerAnimHeapRef() { VillagerAnimHeapRef_Deinit(); }
};

struct VillagerAnimHeapRefSlot : NpcResSlot {
    VillagerAnimHeapRefSlot();
    ~VillagerAnimHeapRefSlot();
    /* 0x4 */ VillagerAnimHeapRef heapRef;
    void assign(u32 x);
};

#endif
