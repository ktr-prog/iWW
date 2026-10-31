#ifndef NPC_NPCBODYANIMSLOT_H
#define NPC_NPCBODYANIMSLOT_H

#include "types.h"
#include "npc/NpcResPool.h"
#include "player/AnimSlotRef.h"

struct NpcBodyAnimSlot : NpcResSlot {
    NpcBodyAnimSlot();
    ~NpcBodyAnimSlot();
    /* 0x01 */ AnimSlotRef layers[3];
    void assignLayer(s32 a, s32 i);
};

#endif
