#ifndef NPC_SPNPCANIMHEAPREFSLOT_H
#define NPC_SPNPCANIMHEAPREFSLOT_H

#include "types.h"
#include "npc/NpcResPool.h"

extern "C" void SpNpcAnimHeapRef_Init(s32 *p);
extern "C" void SpNpcAnimHeapRef_Deinit();
struct SpNpcAnimHeapRef {
    /* 0x0 */ u32 slot;
    SpNpcAnimHeapRef() { SpNpcAnimHeapRef_Init((s32 *)&slot); }
    ~SpNpcAnimHeapRef() { SpNpcAnimHeapRef_Deinit(); }
};

struct SpNpcAnimHeapRefSlot : NpcResSlot {
    /* 0x4 */ SpNpcAnimHeapRef heapRef;
    void assign(u32 id);
    SpNpcAnimHeapRefSlot();
    ~SpNpcAnimHeapRefSlot();
};

#endif
