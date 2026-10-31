#ifndef NPC_NPCRESHANDLE_H
#define NPC_NPCRESHANDLE_H

#include "types.h"

class NpcResPool;
class AnimSlotRef;
class HeldItemModel;
struct NpcTexPatBufRef;
struct CharaFaceAnimWorkRef;
struct CharaFaceAnimRef;
struct CharaClothTexRef;
struct SpNpcAnimHeapRef;
struct VillagerAnimHeapRef;

struct NpcResHandle {
    /* 0x04 */ s8 slot;
    NpcResHandle();
    virtual ~NpcResHandle();
    virtual NpcResPool *getPool() = 0;
    void release();
    BOOL acquire();
};

struct NpcTexPatBufRefHandle : NpcResHandle {
    NpcTexPatBufRefHandle();
    virtual ~NpcTexPatBufRefHandle();
    virtual NpcResPool *getPool();
    NpcTexPatBufRef *getTexPatBufRef();
};

struct NpcTexPatHeapHandle : NpcResHandle {
    NpcTexPatHeapHandle();
    virtual ~NpcTexPatHeapHandle();
    virtual NpcResPool *getPool();
    CharaFaceAnimWorkRef *getTexPatHeapRef();
};

struct SpNpcAnimHeapHandle : NpcResHandle {
    SpNpcAnimHeapHandle();
    virtual ~SpNpcAnimHeapHandle();
    virtual NpcResPool *getPool();
    SpNpcAnimHeapRef *getSpNpcAnimHeapRef();
};

struct VillagerAnimHeapHandle : NpcResHandle {
    VillagerAnimHeapHandle();
    virtual ~VillagerAnimHeapHandle();
    virtual NpcResPool *getPool();
    VillagerAnimHeapRef *getVillagerAnimHeapRef();
};

struct NpcBodyAnimHandle : NpcResHandle {
    NpcBodyAnimHandle();
    virtual ~NpcBodyAnimHandle();
    virtual NpcResPool *getPool();
    AnimSlotRef *getBodyAnimLayer(u32 off);
};

struct NpcHeldItemModelHandle : NpcResHandle {
    NpcHeldItemModelHandle();
    virtual ~NpcHeldItemModelHandle();
    virtual NpcResPool *getPool();
    HeldItemModel *getHeldItemModel();
    BOOL loadHeldItem(u16 *item);
};

struct NpcClothTexHandle : NpcResHandle {
    NpcClothTexHandle();
    virtual ~NpcClothTexHandle();
    virtual NpcResPool *getPool();
    CharaClothTexRef *getClothTex();
};

struct NpcFaceAnimHandle : NpcResHandle {
    NpcFaceAnimHandle();
    virtual ~NpcFaceAnimHandle();
    virtual NpcResPool *getPool();
    CharaFaceAnimRef *getFaceAnim();
};

#endif
