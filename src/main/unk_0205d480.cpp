#include "types.h"
#include "net/CommManager.h"
#include "sys/PrioListNode.h"
#include "gfx/TexVramSlot.h"
#include "gfx/TexTransfer.h"
#include "gfx/VramTask.h"
#include "gfx/TexVramTask.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205d480.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"

extern "C" {
void *NNS_G3dGetTex(void *h);
extern CommManager *gCommManager;
}

static inline BOOL Unk_0205d4e4_IsTwo(u8 v) {
    return v == 2 ? TRUE : FALSE;
}

static inline BOOL Unk_0205d4e4_IsOne(u8 v) {
    return v == 1 ? TRUE : FALSE;
}

class PlayerGlassesModelPool {
public:
    void *buffers[4];
    TexVramSlot vramSlots[4];
    TexVramTask texTasks[4];
    u8 modelIds[4];

    PlayerGlassesModelPool();
    ~PlayerGlassesModelPool();
    void setModelId(u32 i, u32 v);
    u8 getModelId(u32 i);
    TexVramTask *getTexTask(u32 i);
    TexVramSlot *getVramSlot(u32 i);
    void *getBuffer(u32 i);
    void freeBuffers(void);
    void allocBuffers(void);
};

extern "C" {
extern const u8 sPlayerGlassesFlowerModelIds[0xc];
extern const u8 sPlayerGlassesAccessoryModelIds[0x40];

}

const u8 sPlayerGlassesFlowerModelIds[0xc] = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x00};
const u8 sPlayerGlassesAccessoryModelIds[0x40] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};

char sPlayerGlassesModelPathBuf[0x14];
PlayerGlassesModelPool sPlayerGlassesModelPool;

extern "C" void PlayerGlassesModelPool_Create(Heap *parent) {
    PlayerGlassesModelHeap_Create(parent);
    sPlayerGlassesModelPool.allocBuffers();
    if (gPlayerGlassesModelHeap) {
        static_cast<Heap *>(gPlayerGlassesModelHeap)->adjust();
    }
}

extern "C" void PlayerGlassesModelPool_Destroy() {
    sPlayerGlassesModelPool.freeBuffers();
    PlayerGlassesModelHeap_Destroy();
}

extern "C" char *PlayerGlassesModel_GetPath(s32 x) {
    Str_SPrintf(sPlayerGlassesModelPathBuf, "/PGls/%d/%d.nsbmd", (u32)x >> 5, x);
    return sPlayerGlassesModelPathBuf;
}

extern "C" s32 PlayerGlassesModel_GetBufferSize() { return 0xc74; }

extern "C" u8 PlayerGlassesModel_GetAccessoryModelId(u32 i) {
    return sPlayerGlassesAccessoryModelIds[i];
}

extern "C" u8 PlayerGlassesModel_GetFlowerModelId(u32 i) {
    return sPlayerGlassesFlowerModelIds[i];
}

extern "C" s32 PlayerGlassesModel_GetTexVramSize() { return 0x600; }
extern "C" s32 PlayerGlassesModel_GetTex4x4VramSize() { return 0; }
extern "C" s32 PlayerGlassesModel_GetPlttVramSize() { return 0x60; }

PlayerGlassesModelPool::PlayerGlassesModelPool() {
    s32 i;
    for (i = 0; i < 4; i++) {
        buffers[i] = NULL;
        modelIds[i] = 0x4b;
    }
}

PlayerGlassesModelPool::~PlayerGlassesModelPool() {}

void PlayerGlassesModelPool::allocBuffers(void) {
    u32 n = gCommManager->memberCount;
    u32 i;
    for (i = 0; i < n; i++) {
        vramSlots[i].alloc(PlayerGlassesModel_GetTexVramSize(), PlayerGlassesModel_GetTex4x4VramSize(), PlayerGlassesModel_GetPlttVramSize());
    }
    Heap *heap = static_cast<Heap *>(gPlayerGlassesModelHeap);
    for (i = 0; i < n; i++) {
        buffers[i] = Heap_AllocAligned(heap, PlayerGlassesModel_GetBufferSize(), 4);
    }
}

void PlayerGlassesModelPool::freeBuffers(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        vramSlots[i].clear();
    }
    for (i = 0; i < 4; i++) {
        buffers[i] = NULL;
    }
    if (gPlayerGlassesModelHeap) {
        static_cast<Heap *>(gPlayerGlassesModelHeap)->freeAll();
    }
    for (i = 0; i < 4; i++) {
        modelIds[i] = 0x4b;
    }
}

void *PlayerGlassesModelPool::getBuffer(u32 i) { return buffers[i]; }
TexVramSlot *PlayerGlassesModelPool::getVramSlot(u32 i) { return &vramSlots[i]; }
TexVramTask *PlayerGlassesModelPool::getTexTask(u32 i) { return &texTasks[i]; }
u8 PlayerGlassesModelPool::getModelId(u32 i) { return modelIds[i]; }
void PlayerGlassesModelPool::setModelId(u32 i, u32 v) { modelIds[i] = v; }

extern "C" void PlayerGlassesModelRef_Init(u8 *p) {
    *p = 4;
}
extern "C" void PlayerGlassesModelRef_Destruct() {}
extern "C" void PlayerGlassesModelRef_SetSlot(u8 *p, u8 v) {
    *p = v;
}

extern "C" void PlayerGlassesModelRef_Release(u8 *p) {
    PlayerGlassesModelRef_CancelTexUpload(p);
    PlayerGlassesModelRef_SetModelId(p, 0x4b);
}

extern "C" void PlayerGlassesModelRef_CancelTexUpload(u8 *p) {
    if (Unk_0205d4e4_IsOne(PlayerGlassesModelRef_GetTexTask(p)->state)) {
        PlayerGlassesModelRef_GetTexTask(p)->cancel();
    } else {
        PlayerGlassesModelRef_GetTexTask(p)->clear();
    }
}

extern "C" void PlayerGlassesModelRef_Load(u8 *p, s32 idx) {
    void *r6 = PlayerGlassesModelRef_GetBuffer(p);
    PlayerGlassesModelRef_SetModelId(p, idx);
    if (idx < 0x4b) {
        char *path = PlayerGlassesModel_GetPath(idx);
        File_LoadToBuffer(path, r6, PlayerGlassesModel_GetBufferSize());
    }
}

extern "C" void PlayerGlassesModelRef_RelocateTexture(u8 *p) {
    void *q = NNS_G3dGetTex(PlayerGlassesModelRef_GetBuffer(p));
    PlayerGlassesModelRef_GetVramSlot(p)->relocateTexture(q);
}

extern "C" BOOL PlayerGlassesModelRef_PollTexUpload(u8 *p) {
    TexVramTask *o = PlayerGlassesModelRef_GetTexTask(p);
    u8 st = o->state;
    if (Unk_0205d4e4_IsTwo(st)) {
        return TRUE;
    }
    if (!Unk_0205d4e4_IsOne(st)) {
        o->requestTexResource((u32 *)NNS_G3dGetTex(PlayerGlassesModelRef_GetBuffer(p)), 1);
    }
    return FALSE;
}

extern "C" void *PlayerGlassesModelRef_GetBuffer(u8 *p) {
    return sPlayerGlassesModelPool.getBuffer(*p);
}
extern "C" TexVramSlot *PlayerGlassesModelRef_GetVramSlot(u8 *p) {
    return sPlayerGlassesModelPool.getVramSlot(*p);
}
extern "C" TexVramTask *PlayerGlassesModelRef_GetTexTask(u8 *p) {
    return sPlayerGlassesModelPool.getTexTask(*p);
}
extern "C" u8 PlayerGlassesModelRef_GetModelId(u8 *p) {
    return sPlayerGlassesModelPool.getModelId(*p);
}
extern "C" void PlayerGlassesModelRef_SetModelId(u8 *p, s32 v) {
    sPlayerGlassesModelPool.setModelId(*p, v);
}
