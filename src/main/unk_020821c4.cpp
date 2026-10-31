#include "types.h"
#include "npc/NpcResPool.h"
#include "player/AnimSlotRef.h"
#include "actor/CharaClothTexRef.h"
#include "actor/CharaFaceAnimRef.h"
#include "actor/CharaFaceAnimWorkRef.h"
#include "npc/SpNpcAnimHeapRefSlot.h"
#include "npc/VillagerAnimHeapRefSlot.h"
#include "npc/NpcBodyAnimSlot.h"
#include "npc/VillagerAnimHeapRefPool.h"
#include "npc/NpcBodyAnimPool.h"
#include "npc/NpcResPools.h"
#include "player/HeldItemModel.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205dfa4.h"
#include "proto/main/unk_020821c4.h"


extern "C" {
void NpcTexPatBufRef_Assign(void *, s32 v);
void SpNpcAnimHeapRef_Assign(void *, s32 x);
void VillagerAnimHeapRef_Assign(void *, s32 x);
}

extern const s32 sNpcBodyAnimLayerIdBases[];
const s32 sNpcBodyAnimLayerIdBases[3] = {4, 0xd, 0x12};

void NpcResPool::clearAllSlots() {
    for (s32 i = 0; i < numSlots; i++) {
        NpcResSlot *p = getSlot(i);
        if (p) p->inUse = 0;
    }
}

void NpcResPool::releaseSlot(u32 i) {
    if (i < (u32)numSlots) {
        NpcResSlot *p = getSlot(i);
        if (p) p->inUse = 0;
    }
}

s32 NpcResPool::findFreeSlot() {
    s32 r = -1;
    for (s32 i = 0; i < numSlots; i++) {
        NpcResSlot *p = getSlot(i);
        if (p && p->inUse == 0) {
            r = i;
            break;
        }
    }
    return r;
}

NpcBodyAnimSlot::NpcBodyAnimSlot() {}

NpcBodyAnimSlot::~NpcBodyAnimSlot() {}

void NpcBodyAnimSlot::assignLayer(s32 a, s32 i) {
    AnimSlotRef_Assign(&layers[i], a);
}

NpcBodyAnimPool::NpcBodyAnimPool() : NpcResPool(5) {}

NpcBodyAnimPool::~NpcBodyAnimPool() {}

extern "C" NpcBodyAnimPool *NpcBodyAnimPool_Get() { return &sNpcBodyAnimPool; }

void NpcBodyAnimPool::occupySlot(u32 i) {
    if (i < (u32)numSlots) {
        for (s32 k = 0; k < 3; k++) {
            NpcBodyAnimPool_Get()->slots[i].assignLayer(i + sNpcBodyAnimLayerIdBases[k], k);
            NpcBodyAnimPool_Get()->slots[i].inUse = 1;
        }
    }
}

NpcBodyAnimSlot *NpcBodyAnimPool::getSlot(u32 i) {
    NpcBodyAnimSlot *r = 0;
    if (i < (u32)numSlots) r = &slots[i];
    return r;
}

AnimSlotRef *NpcBodyAnimPool::getLayer(u32 i, u32 off) {
    AnimSlotRef *r = 0;
    if (i < (u32)numSlots) r = &NpcBodyAnimPool_Get()->slots[i].layers[off];
    return r;
}

VillagerAnimHeapRefSlot::VillagerAnimHeapRefSlot() {}

VillagerAnimHeapRefSlot::~VillagerAnimHeapRefSlot() {}

void VillagerAnimHeapRefSlot::assign(u32 x) {
    VillagerAnimHeapRef_Assign(&heapRef, x);
    inUse = 1;
}

VillagerAnimHeapRefPool::VillagerAnimHeapRefPool() : NpcResPool(8) {}

VillagerAnimHeapRefPool::~VillagerAnimHeapRefPool() {}

extern "C" VillagerAnimHeapRefPool *VillagerAnimHeapRefPool_Get() { return &sVillagerAnimHeapRefPool; }

void VillagerAnimHeapRefPool::occupySlot(u32 i) {
    if (i < (u32)numSlots) {
        u32 t = 0;
        t += i;
        VillagerAnimHeapRefPool_Get()->slots[i].assign(t);
    }
}

VillagerAnimHeapRefSlot *VillagerAnimHeapRefPool::getSlot(u32 i) {
    VillagerAnimHeapRefSlot *r = 0;
    if (i < (u32)numSlots) r = &slots[i];
    return r;
}

VillagerAnimHeapRef *VillagerAnimHeapRefPool::getHeapRef(u32 i) {
    VillagerAnimHeapRef *r = 0;
    if (i < (u32)numSlots) {
        VillagerAnimHeapRefSlot *e = &VillagerAnimHeapRefPool_Get()->slots[i];
        r = &e->heapRef;
    }
    return r;
}

SpNpcAnimHeapRefSlot::SpNpcAnimHeapRefSlot() {}

SpNpcAnimHeapRefSlot::~SpNpcAnimHeapRefSlot() {}

void SpNpcAnimHeapRefSlot::assign(u32 id) {
    SpNpcAnimHeapRef_Assign(&heapRef, id);
    inUse = 1;
}

SpNpcAnimHeapRefPool::SpNpcAnimHeapRefPool() : NpcResPool(4) {}

SpNpcAnimHeapRefPool::~SpNpcAnimHeapRefPool() {}

extern "C" SpNpcAnimHeapRefPool *SpNpcAnimHeapRefPool_Get() { return &sSpNpcAnimHeapRefPool; }

void SpNpcAnimHeapRefPool::occupySlot(u32 i) {
    if (i < (u32)numSlots) {
        u32 id = 0;
        id += i;
        SpNpcAnimHeapRefPool_Get()->slots[i].assign(id);
    }
}

SpNpcAnimHeapRefSlot *SpNpcAnimHeapRefPool::getSlot(u32 i) {
    SpNpcAnimHeapRefSlot *r = 0;
    if (i < (u32)numSlots) {
        r = &slots[i];
    }
    return r;
}

SpNpcAnimHeapRef *SpNpcAnimHeapRefPool::getHeapRef(u32 i) {
    SpNpcAnimHeapRef *r = 0;
    if (i < (u32)numSlots) {
        SpNpcAnimHeapRefSlot *e = &SpNpcAnimHeapRefPool_Get()->slots[i];
        r = &e->heapRef;
    }
    return r;
}

NpcClothTexSlot::NpcClothTexSlot() {}

NpcClothTexSlot::~NpcClothTexSlot() {}

void NpcClothTexSlot::assign(u32 id) {
    ((CharaClothTexRef *)(&clothTex))->assign(id);
    inUse = 1;
}

void NpcClothTexSlot::release() {
    ((CharaClothTexRef *)(&clothTex))->release();
    inUse = 0;
}

NpcClothTexPool::NpcClothTexPool() : NpcResPool(5) {}

NpcClothTexPool::~NpcClothTexPool() {}

extern "C" NpcClothTexPool *NpcClothTexPool_Get() { return &sNpcClothTexPool; }

void NpcClothTexPool::occupySlot(u32 i) {
    if (i < (u32)numSlots) {
        u32 id = 5;
        id += i;
        NpcClothTexPool_Get()->slots[i].assign(id);
    }
}

void NpcClothTexPool::releaseSlot(u32 i) {
    NpcResPool::releaseSlot(i);
    if (i < (u32)numSlots) {
        NpcClothTexPool_Get()->slots[i].release();
    }
}

NpcClothTexSlot *NpcClothTexPool::getSlot(u32 i) {
    NpcClothTexSlot *r = 0;
    if (i < (u32)numSlots) {
        r = &slots[i];
    }
    return r;
}

CharaClothTexRef *NpcClothTexPool::getClothTex(u32 i) {
    CharaClothTexRef *r = 0;
    if (i < (u32)numSlots) {
        NpcClothTexSlot *e = &NpcClothTexPool_Get()->slots[i];
        r = &e->clothTex;
    }
    return r;
}

NpcTexPatBufRefSlot::NpcTexPatBufRefSlot() {}

NpcTexPatBufRefSlot::~NpcTexPatBufRefSlot() {}

void NpcTexPatBufRefSlot::assign(u32 id) {
    NpcTexPatBufRef_Assign(&bufRef, id);
    inUse = 1;
}

NpcTexPatBufRefPool::NpcTexPatBufRefPool() : NpcResPool(5) {}

NpcTexPatBufRefPool::~NpcTexPatBufRefPool() {}

extern "C" NpcTexPatBufRefPool *NpcTexPatBufRefPool_Get() { return &sNpcTexPatBufRefPool; }

void NpcTexPatBufRefPool::occupySlot(u32 i) {
    if (i < (u32)numSlots) {
        u32 id = 0;
        id += i;
        NpcTexPatBufRefPool_Get()->slots[i].assign(id);
    }
}

NpcTexPatBufRefSlot *NpcTexPatBufRefPool::getSlot(u32 i) {
    NpcTexPatBufRefSlot *r = 0;
    if (i < (u32)numSlots) {
        r = &slots[i];
    }
    return r;
}

NpcTexPatBufRef *NpcTexPatBufRefPool::getBufRef(u32 i) {
    NpcTexPatBufRef *r = 0;
    if (i < (u32)numSlots) {
        NpcTexPatBufRefSlot *e = &NpcTexPatBufRefPool_Get()->slots[i];
        r = &e->bufRef;
    }
    return r;
}

NpcFaceAnimSlot::NpcFaceAnimSlot() {}

NpcFaceAnimSlot::~NpcFaceAnimSlot() {}

void NpcFaceAnimSlot::assign(u32 id) {
    ((CharaFaceAnimRef *)(&faceAnim))->assign(id);
    inUse = 1;
}

NpcFaceAnimPool::NpcFaceAnimPool() : NpcResPool(5) {}

NpcFaceAnimPool::~NpcFaceAnimPool() {}

extern "C" NpcFaceAnimPool *NpcFaceAnimPool_Get() { return &sNpcFaceAnimPool; }

void NpcFaceAnimPool::occupySlot(u32 i) {
    if (i < (u32)numSlots) {
        u32 id = 4;
        id += i;
        NpcFaceAnimPool_Get()->slots[i].assign(id);
    }
}

NpcFaceAnimSlot *NpcFaceAnimPool::getSlot(u32 i) {
    NpcFaceAnimSlot *r = 0;
    if (i < (u32)numSlots) {
        r = &slots[i];
    }
    return r;
}

CharaFaceAnimRef *NpcFaceAnimPool::getFaceAnim(u32 i) {
    CharaFaceAnimRef *r = 0;
    if (i < (u32)numSlots) {
        NpcFaceAnimSlot *e = &NpcFaceAnimPool_Get()->slots[i];
        r = &e->faceAnim;
    }
    return r;
}

NpcTexPatHeapSlot::NpcTexPatHeapSlot() {}

NpcTexPatHeapSlot::~NpcTexPatHeapSlot() {}

void NpcTexPatHeapSlot::assign(u32 id) {
    ((CharaFaceAnimWorkRef *)(&workRef))->assign(id);
    inUse = 1;
}

NpcTexPatHeapPool::NpcTexPatHeapPool() : NpcResPool(5) {}

NpcTexPatHeapPool::~NpcTexPatHeapPool() {}

extern "C" NpcTexPatHeapPool *NpcTexPatHeapPool_Get() { return &sNpcTexPatHeapPool; }

void NpcTexPatHeapPool::occupySlot(u32 i) {
    if (i < (u32)numSlots) {
        u32 id = 4;
        id += i;
        NpcTexPatHeapPool_Get()->slots[i].assign(id);
    }
}

NpcTexPatHeapSlot *NpcTexPatHeapPool::getSlot(u32 i) {
    NpcTexPatHeapSlot *r = 0;
    if (i < (u32)numSlots) {
        r = &slots[i];
    }
    return r;
}

CharaFaceAnimWorkRef *NpcTexPatHeapPool::getHeapRef(u32 i) {
    CharaFaceAnimWorkRef *r = 0;
    if (i < (u32)numSlots) {
        NpcTexPatHeapSlot *e = &NpcTexPatHeapPool_Get()->slots[i];
        r = &e->workRef;
    }
    return r;
}

NpcHeldItemModelSlot::NpcHeldItemModelSlot() {}

NpcHeldItemModelSlot::~NpcHeldItemModelSlot() {}

void NpcHeldItemModelSlot::load(u32 id, u16 *p) {
    HeldItemModel_Setup(&model, id, 0, p, 0, 0);
    inUse = 1;
}

void NpcHeldItemModelSlot::unload() {
    HeldItemModel_Release(&model);
    inUse = 0;
}

NpcHeldItemModelPool::NpcHeldItemModelPool() : NpcResPool(5) {}

NpcHeldItemModelPool::~NpcHeldItemModelPool() {}

extern "C" NpcHeldItemModelPool *NpcHeldItemModelPool_Get() { return &sNpcHeldItemModelPool; }

void NpcHeldItemModelPool::occupySlot(u32 i) {
    u16 t = 0xfff1;
    loadItem(i, &t);
}

void NpcHeldItemModelPool::releaseSlot(u32 i) {
    NpcResPool::releaseSlot(i);
    if (i < (u32)numSlots) {
        NpcHeldItemModelPool_Get()->slots[i].unload();
    }
}

BOOL NpcHeldItemModelPool::loadItem(u32 i, u16 *p) {
    BOOL r = FALSE;
    if (i < (u32)numSlots) {
        u32 id = 4;
        id += i;
        NpcHeldItemModelPool_Get()->slots[i].load(id, p);
        r = TRUE;
    }
    return r;
}

NpcHeldItemModelSlot *NpcHeldItemModelPool::getSlot(u32 i) {
    NpcHeldItemModelSlot *r = 0;
    if (i < (u32)numSlots) {
        r = &slots[i];
    }
    return r;
}

HeldItemModel *NpcHeldItemModelPool::getModel(u32 i) {
    if (i < (u32)numSlots) {
        NpcHeldItemModelSlot *e = &NpcHeldItemModelPool_Get()->slots[i];
        return &e->model;
    }
    return 0;
}

NpcBodyAnimPool sNpcBodyAnimPool;
VillagerAnimHeapRefPool sVillagerAnimHeapRefPool;
SpNpcAnimHeapRefPool sSpNpcAnimHeapRefPool;
NpcClothTexPool sNpcClothTexPool;
NpcTexPatBufRefPool sNpcTexPatBufRefPool;
NpcFaceAnimPool sNpcFaceAnimPool;
NpcTexPatHeapPool sNpcTexPatHeapPool;
NpcHeldItemModelPool sNpcHeldItemModelPool;
