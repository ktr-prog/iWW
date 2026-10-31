#include "types.h"
#include "net/CommManager.h"
#include "gfx/TexVramSlot.h"
#include "gfx/TexVramTask.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205c66c.h"
#include "proto/main/unk_02063f3c.h"



struct PlayerBodyModelPool {
    void *buffers[4];
    TexVramSlot vramSlots[4];
    TexVramTask texTasks[4];

    PlayerBodyModelPool();
    ~PlayerBodyModelPool();
    TexVramTask *getTexTask(s32 i);
    void *getVramSlot(s32 i);
    void *getBuffer(s32 i);
    void freeBuffers();
    void allocBuffers();
};

extern "C" {
extern CommManager *gCommManager;
u8 *NNS_G3dGetTex(u8 *p);
}

extern "C" void PlayerBodyModelPool_Create(Heap *parent) {
    PlayerBodyModelHeap_Create(parent);
    sPlayerBodyModelPool.allocBuffers();
    if (gPlayerBodyModelHeap) static_cast<Heap *>(gPlayerBodyModelHeap)->adjust();
}

extern "C" void PlayerBodyModelPool_Destroy() {
    sPlayerBodyModelPool.freeBuffers();
    PlayerBodyModelHeap_Destroy();
}


extern "C" char *PlayerBodyModel_GetPath(u32 i) { return sPlayerBodyModelPaths[i]; }
extern "C" u32 PlayerBodyModel_GetBufferSize() { return 0x2380; }
extern "C" u32 PlayerBodyModel_GetTexVramSize() { return 0x440; }
extern "C" u32 PlayerBodyModel_GetTex4x4VramSize() { return 0; }
extern "C" u32 PlayerBodyModel_GetPlttVramSize() { return 0x60; }

PlayerBodyModelPool::PlayerBodyModelPool() {
}

PlayerBodyModelPool::~PlayerBodyModelPool() {
}

void PlayerBodyModelPool::allocBuffers() {
    u32 cnt = gCommManager->memberCount;
    u32 i;
    for (i = 0; i < cnt; i++) {
        u32 a = PlayerBodyModel_GetTexVramSize();
        u32 b = PlayerBodyModel_GetTex4x4VramSize();
        u32 c = PlayerBodyModel_GetPlttVramSize();
        vramSlots[i].alloc(a, b, c);
    }
    Heap *heap = static_cast<Heap *>(gPlayerBodyModelHeap);
    for (i = 0; i < cnt; i++) buffers[i] = Heap_AllocAligned(heap, PlayerBodyModel_GetBufferSize(), 4);
}

void PlayerBodyModelPool::freeBuffers() {
    for (s32 i = 0; i < 4; i++) vramSlots[i].clear();
    s32 j;
    for (j = 0; j < 4; j++) buffers[j] = NULL;
    if (gPlayerBodyModelHeap) static_cast<Heap *>(gPlayerBodyModelHeap)->freeAll();
}

void *PlayerBodyModelPool::getBuffer(s32 i) { return buffers[i]; }
void *PlayerBodyModelPool::getVramSlot(s32 i) { return &vramSlots[i]; }
TexVramTask *PlayerBodyModelPool::getTexTask(s32 i) { return &texTasks[i]; }

extern "C" void PlayerBodyModelRef_Init(u8 *p) { *p = 4; }
extern "C" void PlayerBodyModelRef_Destruct() {}
extern "C" void PlayerBodyModelRef_SetSlot(u8 *p, u32 v) { *p = v; }

extern "C" void PlayerBodyModelRef_CancelTexUpload(u8 *p) {
    u32 s = PlayerBodyModelRef_GetTexTask(p)->state;
    BOOL a = s == 1 ? TRUE : FALSE;
    if (a) PlayerBodyModelRef_GetTexTask(p)->cancel();
    else PlayerBodyModelRef_GetTexTask(p)->clear();
}

extern "C" s32 PlayerBodyModelRef_Load(u8 *p, u32 idx) {
    void *buf = PlayerBodyModelRef_GetBuffer(p);
    char *name = PlayerBodyModel_GetPath(idx);
    return File_LoadToBuffer(name, buf, PlayerBodyModel_GetBufferSize());
}

extern "C" void PlayerBodyModelRef_RelocateTexture(u8 *p) {
    u8 *tex = NNS_G3dGetTex(static_cast<u8 *>(PlayerBodyModelRef_GetBuffer(p)));
    static_cast<TexVramSlot *>(PlayerBodyModelRef_GetVramSlot(p))->relocateTexture(tex);
}

extern "C" s32 PlayerBodyModelRef_PollTexUpload(u8 *p) {
    TexVramTask *e = PlayerBodyModelRef_GetTexTask(p);
    u32 s = e->state;
    BOOL a = s == 2 ? TRUE : FALSE;
    if (a) return TRUE;
    BOOL b = s == 1 ? TRUE : FALSE;
    if (!b) {
        e->requestTexResource((u32 *)NNS_G3dGetTex(static_cast<u8 *>(PlayerBodyModelRef_GetBuffer(p))), 1);
    }
    return FALSE;
}

extern "C" void *PlayerBodyModelRef_GetBuffer(u8 *p) { return sPlayerBodyModelPool.getBuffer(*p); }
extern "C" void *PlayerBodyModelRef_GetVramSlot(u8 *p) { return sPlayerBodyModelPool.getVramSlot(*p); }
extern "C" TexVramTask *PlayerBodyModelRef_GetTexTask(u8 *p) { return sPlayerBodyModelPool.getTexTask(*p); }

PlayerBodyModelPool sPlayerBodyModelPool;

char *sPlayerBodyModelPaths[] = {"/PBody/boy.nsbmd", "/PBody/grl.nsbmd"};

