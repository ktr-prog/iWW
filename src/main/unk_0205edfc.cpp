#include "types.h"
#include "net/CommManager.h"
#include "player/PlayerBodyWorkRef.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205edfc.h"


struct PlayerBodyWorkPool {
    Heap *heaps[4];
    PlayerBodyWorkPool();
    ~PlayerBodyWorkPool();
};


extern "C" {
extern CommManager *gCommManager;
}

PlayerBodyWorkPool sPlayerBodyWorkPool;

extern "C" void PlayerBodyWorkPool_Create(Heap *parent) {
    PlayerBodyAnimHeap_Create(parent);
    PlayerBodyWorkPool_CreateHeaps(sPlayerBodyWorkPool.heaps);
    if (gPlayerBodyAnimHeap) {
        ((Heap *)(gPlayerBodyAnimHeap))->adjust();
    }
}

extern "C" void PlayerBodyWorkPool_Destroy(void) {
    PlayerBodyWorkPool_DestroyHeaps(sPlayerBodyWorkPool.heaps);
    PlayerBodyAnimHeap_Destroy();
}

extern "C" u32 PlayerBodyWork_GetHeapSize(void) { return 0x768; }

PlayerBodyWorkPool::PlayerBodyWorkPool() {}

PlayerBodyWorkPool::~PlayerBodyWorkPool() {}

extern "C" void PlayerBodyWorkPool_CreateHeaps(Heap **tbl) {
    Heap *heap = (Heap *)gPlayerBodyAnimHeap;
    u32 n = gCommManager->memberCount;
    u32 i;
    for (i = 0; i < n; i++) {
        tbl[i] = (Heap *)FrameHeap_Create(PlayerBodyWork_GetHeapSize(), heap);
    }
}

extern "C" void PlayerBodyWorkPool_DestroyHeaps(Heap **tbl) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (tbl[i]) {
            tbl[i]->freeAll();
            tbl[i] = 0;
        }
    }
    if (gPlayerBodyAnimHeap) {
        ((Heap *)(gPlayerBodyAnimHeap))->freeAll();
    }
}

extern "C" Heap *PlayerBodyWorkPool_GetHeap(Heap **base, u32 idx) {
    return base[idx];
}

PlayerBodyWorkRef::PlayerBodyWorkRef() { slot = 4; }

extern "C" void PlayerBodyWorkRef_Destruct(void) {}

extern "C" void PlayerBodyWorkRef_Assign(u8 *p, u8 v) {
    PlayerBodyWorkPool_GetHeap(sPlayerBodyWorkPool.heaps, v)->freeAll();
    *p = v;
}

extern "C" Heap *PlayerBodyWorkRef_GetHeap(u8 *p) {
    return PlayerBodyWorkPool_GetHeap(sPlayerBodyWorkPool.heaps, *p);
}
