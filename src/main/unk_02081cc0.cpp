#include "types.h"
#include "npc/NpcResPool.h"
#include "npc/NpcResHandle.h"
#include "npc/VillagerAnimHeapRefPool.h"
#include "npc/NpcBodyAnimPool.h"
#include "npc/NpcResPools.h"
#include "proto/main/unk_02081cc0.h"
#include "proto/main/unk_020821c4.h"


NpcResHandle::NpcResHandle() : slot(-1) {}

NpcResHandle::~NpcResHandle() {}

BOOL NpcResHandle::acquire() {
    NpcResPool *c = getPool();
    BOOL r = FALSE;
    if (c) {
        if (slot == -1) {
            u32 i = c->findFreeSlot();
            if (i < (u32)c->numSlots) {
                slot = i;
                c->occupySlot(slot);
                r = TRUE;
            }
        } else {
            r = TRUE;
        }
    }
    return r;
}

void NpcResHandle::release() {
    NpcResPool *c = getPool();
    if (c) {
        c->releaseSlot(slot);
        slot = -1;
    }
}

NpcBodyAnimHandle::NpcBodyAnimHandle() {}

NpcBodyAnimHandle::~NpcBodyAnimHandle() {}

AnimSlotRef *NpcBodyAnimHandle::getBodyAnimLayer(u32 off) {
    NpcResPool *c = getPool();
    AnimSlotRef *r = 0;
    if (c) {
        r = static_cast<NpcBodyAnimPool *>(c)->getLayer(slot, off);
    }
    return r;
}

VillagerAnimHeapHandle::VillagerAnimHeapHandle() {}

VillagerAnimHeapHandle::~VillagerAnimHeapHandle() {}

VillagerAnimHeapRef *VillagerAnimHeapHandle::getVillagerAnimHeapRef() {
    NpcResPool *p = getPool();
    VillagerAnimHeapRef *r = 0;
    if (p) {
        r = static_cast<VillagerAnimHeapRefPool *>(p)->getHeapRef((s8)slot);
    }
    return r;
}

SpNpcAnimHeapHandle::SpNpcAnimHeapHandle() {}

SpNpcAnimHeapHandle::~SpNpcAnimHeapHandle() {}

SpNpcAnimHeapRef *SpNpcAnimHeapHandle::getSpNpcAnimHeapRef() {
    NpcResPool *p = getPool();
    SpNpcAnimHeapRef *r = 0;
    if (p) {
        r = static_cast<SpNpcAnimHeapRefPool *>(p)->getHeapRef((s8)slot);
    }
    return r;
}

NpcClothTexHandle::NpcClothTexHandle() {}

NpcClothTexHandle::~NpcClothTexHandle() {}

CharaClothTexRef *NpcClothTexHandle::getClothTex() {
    NpcResPool *p = getPool();
    CharaClothTexRef *r = 0;
    if (p) {
        r = static_cast<NpcClothTexPool *>(p)->getClothTex((s8)slot);
    }
    return r;
}

NpcTexPatBufRefHandle::NpcTexPatBufRefHandle() {}

NpcTexPatBufRefHandle::~NpcTexPatBufRefHandle() {}

NpcTexPatBufRef *NpcTexPatBufRefHandle::getTexPatBufRef() {
    NpcResPool *p = getPool();
    NpcTexPatBufRef *r = 0;
    if (p) {
        r = static_cast<NpcTexPatBufRefPool *>(p)->getBufRef((s8)slot);
    }
    return r;
}

NpcFaceAnimHandle::NpcFaceAnimHandle() {}

NpcFaceAnimHandle::~NpcFaceAnimHandle() {}

CharaFaceAnimRef *NpcFaceAnimHandle::getFaceAnim() {
    NpcResPool *p = getPool();
    CharaFaceAnimRef *r = 0;
    if (p) {
        r = static_cast<NpcFaceAnimPool *>(p)->getFaceAnim((s8)slot);
    }
    return r;
}

NpcTexPatHeapHandle::NpcTexPatHeapHandle() {}

NpcTexPatHeapHandle::~NpcTexPatHeapHandle() {}

CharaFaceAnimWorkRef *NpcTexPatHeapHandle::getTexPatHeapRef() {
    NpcResPool *p = getPool();
    CharaFaceAnimWorkRef *r = 0;
    if (p) {
        r = static_cast<NpcTexPatHeapPool *>(p)->getHeapRef((s8)slot);
    }
    return r;
}

NpcHeldItemModelHandle::NpcHeldItemModelHandle() {}

NpcHeldItemModelHandle::~NpcHeldItemModelHandle() {}

BOOL NpcHeldItemModelHandle::loadHeldItem(u16 *a) {
    NpcResPool *p = getPool();
    BOOL r = FALSE;
    if (p) {
        r = static_cast<NpcHeldItemModelPool *>(p)->loadItem((s8)slot, a);
    }
    return r;
}

HeldItemModel *NpcHeldItemModelHandle::getHeldItemModel() {
    NpcResPool *p = getPool();
    if (p) {
        return static_cast<NpcHeldItemModelPool *>(p)->getModel((s8)slot);
    }
    return 0;
}

extern "C" void NpcResPools_ClearAll() {
    NpcBodyAnimPool_Get()->clearAllSlots();
    NpcClothTexPool_Get()->clearAllSlots();
    NpcTexPatBufRefPool_Get()->clearAllSlots();
    NpcFaceAnimPool_Get()->clearAllSlots();
    NpcTexPatHeapPool_Get()->clearAllSlots();
    NpcHeldItemModelPool_Get()->clearAllSlots();
}

extern "C" void NpcResPools_ClearOnSceneCreate() { NpcResPools_ClearAll(); }

extern "C" void NpcResPools_ClearOnSceneDelete() { NpcResPools_ClearAll(); }

NpcResPool *NpcHeldItemModelHandle::getPool() { return NpcHeldItemModelPool_Get(); }

NpcResPool *NpcTexPatHeapHandle::getPool() { return NpcTexPatHeapPool_Get(); }

NpcResPool *NpcFaceAnimHandle::getPool() { return NpcFaceAnimPool_Get(); }

NpcResPool *NpcTexPatBufRefHandle::getPool() { return NpcTexPatBufRefPool_Get(); }

NpcResPool *NpcClothTexHandle::getPool() { return NpcClothTexPool_Get(); }

NpcResPool *SpNpcAnimHeapHandle::getPool() { return SpNpcAnimHeapRefPool_Get(); }

NpcResPool *VillagerAnimHeapHandle::getPool() { return VillagerAnimHeapRefPool_Get(); }

NpcResPool *NpcBodyAnimHandle::getPool() { return NpcBodyAnimPool_Get(); }

