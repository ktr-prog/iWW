#include "types.h"
#include "net/WfcListNode.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02226994.h"


struct WfcVramBlock {
    WfcVramBlock *prev;
    WfcVramBlock *next;
    u16 blockStart;
    u16 blockSize;
};

struct WfcVramHeap {
    WfcVramBlock nodes[0x20];
    WfcVramBlock headNode;
    WfcVramBlock tailNode;
    WfcListNode *list;
    void *nodePool;
};

struct WfcVramWork {
    WfcVramHeap heaps[2];
};

extern "C" {
void *WfcHeap_AllocClear(s32, s32);
void *WfcPool_Get(void *);
void WfcPool_Put(void *, void *);
void WfcList_PushFront(WfcListNode *head, WfcListNode *node);
void WfcList_PushBack(WfcListNode *head, WfcListNode *node);
void WfcList_InsertBefore(WfcListNode *head, WfcListNode *node);
void WfcList_Remove(WfcListNode *node);
WfcListNode *WfcList_Create();
s32 OS_DisableIrqMask(s32);
s32 OS_EnableIrqMask(s32);
void WfcVram_FreeObjChar(WfcVramBlock *p);
}

extern "C" WfcVramWork *sWfcVram = 0;

#pragma thumb off

void WfcVram_Init()
{
    s32 i;
    sWfcVram = (WfcVramWork *)WfcHeap_AllocClear(sizeof(WfcVramWork), 4);
    for (i = 0; i < 2; i++) {
        WfcVramHeap *h = &sWfcVram->heaps[i];
        h->nodePool = WfcPool_CreateFrom(0x20, h->nodes, sizeof(WfcVramBlock));
        h->list = WfcList_Create();
        h->headNode.blockStart = 0x300;
        h->tailNode.blockStart = 0x400;
        WfcList_PushFront(h->list, (WfcListNode *)&h->headNode);
        WfcList_PushBack(h->list, (WfcListNode *)&h->tailNode);
    }
}

WfcVramBlock *WfcVram_AllocObjChar(s32 idx, s32 size, s32 flag, u32 *out)
{
    WfcVramBlock *blk;
    WfcVramBlock *cur;
    WfcVramBlock *end;
    WfcVramWork *base;
    s32 words;
    s32 old;
    s32 start;
    blk = (WfcVramBlock *)WfcPool_Get(sWfcVram->heaps[idx].nodePool);
    words = (size + 3) & ~3;
    words >>= 2;
    blk->blockSize = words;
    old = OS_DisableIrqMask(1);
    if (flag != 0) {
        base = sWfcVram;
        cur = &base->heaps[idx].headNode;
        if (cur != &base->heaps[idx].tailNode) {
            do {
                WfcVramBlock *nx = cur->next;
                start = cur->blockStart + cur->blockSize;
                if (start + words <= nx->blockStart) {
                    blk->blockStart = start;
                    WfcList_InsertBefore((WfcListNode *)nx, (WfcListNode *)blk);
                    break;
                }
                cur = nx;
            } while (cur != &base->heaps[idx].tailNode);
        }
        if (cur == &sWfcVram->heaps[idx].tailNode) Fatal_Trap();
    } else {
        base = sWfcVram;
        cur = &base->heaps[idx].tailNode;
        if (cur != &base->heaps[idx].headNode) {
            do {
                WfcVramBlock *nx = cur->prev;
                start = cur->blockStart - words;
                if (start >= nx->blockStart + nx->blockSize) {
                    blk->blockStart = start;
                    WfcList_InsertBefore((WfcListNode *)cur, (WfcListNode *)blk);
                    break;
                }
                cur = nx;
            } while (cur != &base->heaps[idx].headNode);
        }
        if (cur == &sWfcVram->heaps[idx].headNode) Fatal_Trap();
    }
    *out = blk->blockStart;
    OS_EnableIrqMask(old);
    return blk;
}

void WfcVram_FreeObjChar(WfcVramBlock *p)
{
    s32 z = 0;
    WfcList_Remove((WfcListNode *)p);
    WfcVramWork *b = sWfcVram;
    if (p >= b->heaps[1].nodes) z = 1;
    WfcPool_Put(b->heaps[z].nodePool, p);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02226994) {
    HOST_OVERLAY_VAR(sWfcVram),
    HOST_OVERLAY_VARS_END
};
