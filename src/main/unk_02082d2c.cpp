#include "types.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "npc/NpcResPool.h"
#include "town/Unk_02082e80_Grid.h"
#include "npc/SpNpcAnimHeapRefSlot.h"
#include "npc/VillagerAnimHeapRefSlot.h"
#include "npc/NpcBodyAnimSlot.h"
#include "npc/VillagerAnimHeapRefPool.h"
#include "npc/NpcSpawner.h"
#include "npc/NpcBodyAnimPool.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020821c4.h"
#include "proto/main/unk_02082d2c.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02097444.h"


extern "C" {
extern u8 gFieldSceneKind;
}

static inline BOOL Unk_02083058_IsA() { return gFieldSceneKind == 0 ? TRUE : FALSE; }

static inline TownBlockCell *Unk_02082e80_GetCell(Unk_02082e80_Grid *g, u32 x, u32 y) {
    if (x < g->size[0] && y < g->size[1] && g->blocks != NULL) {
        return &g->blocks[y * g->size[0] + x];
    }
    return NULL;
}

NpcResSlot::NpcResSlot() { inUse = 0; }

NpcResSlot::~NpcResSlot() {}

NpcResPool::NpcResPool(s32 n) { numSlots = n; }

NpcResPool::~NpcResPool() {}


