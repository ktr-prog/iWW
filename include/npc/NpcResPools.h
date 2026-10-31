#ifndef NPC_NPCRESPOOLS_H
#define NPC_NPCRESPOOLS_H

#include "types.h"
#include "npc/NpcResPool.h"
#include "npc/NpcResSlot.h"
#include "npc/SpNpcAnimHeapRefSlot.h"
#include "actor/CharaClothTexRef.h"
#include "actor/CharaFaceAnimRef.h"
#include "actor/CharaFaceAnimWorkRef.h"
#include "player/HeldItemModel.h"


extern "C" void NpcTexPatBufRef_Init(s32 *p);
extern "C" void NpcTexPatBufRef_Deinit();
struct NpcTexPatBufRef {
    u32 pad;
    NpcTexPatBufRef() { NpcTexPatBufRef_Init((s32 *)&pad); }
    ~NpcTexPatBufRef() { NpcTexPatBufRef_Deinit(); }
};

struct NpcFaceAnimSlot : NpcResSlot {
    NpcFaceAnimSlot();
    ~NpcFaceAnimSlot();
    CharaFaceAnimRef faceAnim;
    void assign(u32 id);
};

struct NpcFaceAnimPool : NpcResPool {
    NpcFaceAnimSlot slots[5];
    NpcFaceAnimPool();
    virtual ~NpcFaceAnimPool();
    virtual void occupySlot(u32 i);
    virtual NpcFaceAnimSlot *getSlot(u32 i);
    CharaFaceAnimRef *getFaceAnim(u32 i);
};

struct NpcTexPatBufRefSlot : NpcResSlot {
    NpcTexPatBufRefSlot();
    ~NpcTexPatBufRefSlot();
    NpcTexPatBufRef bufRef;
    void assign(u32 id);
};

struct NpcTexPatBufRefPool : NpcResPool {
    NpcTexPatBufRefSlot slots[5];
    NpcTexPatBufRefPool();
    virtual ~NpcTexPatBufRefPool();
    virtual void occupySlot(u32 i);
    virtual NpcTexPatBufRefSlot *getSlot(u32 i);
    NpcTexPatBufRef *getBufRef(u32 i);
};

struct NpcClothTexSlot : NpcResSlot {
    NpcClothTexSlot();
    ~NpcClothTexSlot();
    CharaClothTexRef clothTex;
    void assign(u32 id);
    void release();
};

struct NpcClothTexPool : NpcResPool {
    NpcClothTexSlot slots[5];
    NpcClothTexPool();
    virtual ~NpcClothTexPool();
    virtual void occupySlot(u32 i);
    virtual void releaseSlot(u32 i);
    virtual NpcClothTexSlot *getSlot(u32 i);
    CharaClothTexRef *getClothTex(u32 i);
};

struct NpcHeldItemModelSlot : NpcResSlot {
    NpcHeldItemModelSlot();
    ~NpcHeldItemModelSlot();
    HeldItemModel model;
    void unload();
    void load(u32 id, u16 *p);
};

struct NpcHeldItemModelPool : NpcResPool {
    NpcHeldItemModelSlot slots[5];
    NpcHeldItemModelPool();
    virtual ~NpcHeldItemModelPool();
    virtual void occupySlot(u32 i);
    virtual void releaseSlot(u32 i);
    virtual NpcHeldItemModelSlot *getSlot(u32 i);
    HeldItemModel *getModel(u32 i);
    BOOL loadItem(u32 i, u16 *p);
};

struct SpNpcAnimHeapRefPool : NpcResPool {
    SpNpcAnimHeapRefSlot slots[4];
    SpNpcAnimHeapRefPool();
    virtual ~SpNpcAnimHeapRefPool();
    virtual void occupySlot(u32 i);
    virtual SpNpcAnimHeapRefSlot *getSlot(u32 i);
    SpNpcAnimHeapRef *getHeapRef(u32 i);
};

struct NpcTexPatHeapSlot : NpcResSlot {
    NpcTexPatHeapSlot();
    ~NpcTexPatHeapSlot();
    CharaFaceAnimWorkRef workRef;
    void assign(u32 id);
};

struct NpcTexPatHeapPool : NpcResPool {
    NpcTexPatHeapSlot slots[5];
    NpcTexPatHeapPool();
    virtual ~NpcTexPatHeapPool();
    virtual void occupySlot(u32 i);
    virtual NpcTexPatHeapSlot *getSlot(u32 i);
    CharaFaceAnimWorkRef *getHeapRef(u32 i);
};

#endif
