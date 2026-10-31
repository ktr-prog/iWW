#include "types.h"
#include "net/CommManager.h"
#include "player/PlayerFaceTexRef.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205d340.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"

extern "C" {
extern CommManager *gCommManager;
}

struct PlayerFaceTexPool {
    void *ptr[4];
    PlayerFaceTexPool();
    ~PlayerFaceTexPool();
    void *getBuffer(u32 idx);
    void freeBuffers();
};


char sPlayerFaceTexPathBuf[0x14];
PlayerFaceTexPool sPlayerFaceTexPool;

extern "C" void PlayerFaceTexPool_Create(Heap *parent) {
    PlayerFaceTexHeap_Create(parent);
    PlayerFaceTexPool_AllocBuffers(sPlayerFaceTexPool.ptr);
    if (gPlayerFaceTexHeap) {
        static_cast<Heap *>(gPlayerFaceTexHeap)->adjust();
    }
}

extern "C" void PlayerFaceTexPool_Destroy() {
    sPlayerFaceTexPool.freeBuffers();
    PlayerFaceTexHeap_Destroy();
}

extern "C" char *PlayerFaceTex_GetPath(u32 x) {
    Str_SPrintf(sPlayerFaceTexPathBuf, "/PFcTx/%d/%d.nsbtx", x >> 5, x);
    return sPlayerFaceTexPathBuf;
}

extern "C" s32 PlayerFaceTex_GetBufferSize() { return 0x2e30; }

PlayerFaceTexPool::PlayerFaceTexPool() {}

PlayerFaceTexPool::~PlayerFaceTexPool() {}

extern "C" void PlayerFaceTexPool_AllocBuffers(void **arr) {
    Heap *heap = static_cast<Heap *>(gPlayerFaceTexHeap);
    u32 n = gCommManager->memberCount;
    u32 i;
    for (i = 0; i < n; i++) {
        arr[i] = Heap_AllocAligned(heap, PlayerFaceTex_GetBufferSize(), 4);
    }
}

void PlayerFaceTexPool::freeBuffers() {
    for (s32 i = 0; i < 4; i++) ptr[i] = NULL;
    if (gPlayerFaceTexHeap) static_cast<Heap *>(gPlayerFaceTexHeap)->freeAll();
}

void *PlayerFaceTexPool::getBuffer(u32 idx) { return ptr[idx]; }

PlayerFaceTexRef::PlayerFaceTexRef() { v = 4; }

PlayerFaceTexRef::~PlayerFaceTexRef() {}

void PlayerFaceTexRef::assign(u32 x) { setSlot(x); }

void PlayerFaceTexRef::setSlot(u32 x) { v = x; }

s32 PlayerFaceTexRef::load(u32 idx) {
    void *p = sPlayerFaceTexPool.getBuffer(v);
    char *name = PlayerFaceTex_GetPath(idx);
    return File_LoadToBuffer(name, p, PlayerFaceTex_GetBufferSize());
}

void *PlayerFaceTexRef::getBuffer() { return sPlayerFaceTexPool.getBuffer(v); }
