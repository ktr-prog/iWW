#ifndef NPC_NPCBODYANIMPOOL_H
#define NPC_NPCBODYANIMPOOL_H

#include "types.h"
#include "npc/NpcResPool.h"
#include "npc/NpcBodyAnimSlot.h"
#include "player/AnimSlotRef.h"

struct NpcBodyAnimPool : NpcResPool {
    /* 0x08 */ NpcBodyAnimSlot slots[5];
    NpcBodyAnimPool();
    virtual ~NpcBodyAnimPool();
    virtual NpcBodyAnimSlot *getSlot(u32 i);
    virtual void occupySlot(u32 i);
    AnimSlotRef *getLayer(u32 i, u32 off);
};

#endif
