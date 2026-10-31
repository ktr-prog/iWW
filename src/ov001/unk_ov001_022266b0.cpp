#include "types.h"
#include "nitro/gxoam.h"
#include "net/WfcListNode.h"
#include "nitro/gxoam.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226f68.h"


struct WfcOamBuffer {
    GXOamAttr oam[2][0x80];
    void *entryPools[2];
    void *transferTask;
};

extern "C" {
void WfcHeap_FreeAndClear(void *);
void *WfcHeap_Alloc(s32, s32);
void *WfcPool_Get(void *);
void WfcPool_Put(void *, void *);
s32 OS_DisableIrqMask(s32);
s32 OS_EnableIrqMask(s32);
void DC_FlushRange(void *, u32);
void GX_LoadOAM(void *, s32, u32);
void GXS_LoadOAM(void *, s32, u32);
void MIi_CpuCopy32(void *, void *, u32);
void MIi_CpuClearFast(u32, void *, u32);
void WfcList_PushFront(WfcListNode *head, WfcListNode *node);
void WfcList_PushBack(WfcListNode *head, WfcListNode *node);
void WfcList_InsertBefore(WfcListNode *head, WfcListNode *node);
void WfcList_Remove(WfcListNode *node);
WfcListNode *WfcList_Create();
}

extern "C" WfcOamBuffer *sWfcOamBuf = 0;

#pragma thumb off

void WfcOam_Init()
{
    volatile u32 v;
    WfcOamBuffer *b = (WfcOamBuffer *)WfcHeap_Alloc(sizeof(WfcOamBuffer), 4);
    s32 i;
    sWfcOamBuf = b;
    v = 0x200;
    MIi_CpuClearFast(v, b->oam, sizeof(b->oam));
    for (i = 0; i < 2; i++) {
        sWfcOamBuf->entryPools[i] = WfcPool_CreateFrom(0x40, sWfcOamBuf->oam[i], sizeof(GXOamAttr));
    }
    sWfcOamBuf->transferTask = WfcTask_Add(1, (void *)WfcOam_TransferTask, 0, 0xc8);
}

void WfcOam_TransferTask()
{
    DC_FlushRange(sWfcOamBuf->oam, sizeof(sWfcOamBuf->oam));
    GX_LoadOAM(sWfcOamBuf->oam[0], 0, sizeof(sWfcOamBuf->oam[0]));
    GXS_LoadOAM(sWfcOamBuf->oam[1], 0, sizeof(sWfcOamBuf->oam[1]));
}

void WfcOam_Shutdown()
{
    WfcTask_Delete(1, sWfcOamBuf->transferTask);
    WfcHeap_FreeAndClear(&sWfcOamBuf);
}

GXOamAttr *WfcOam_AllocEntry(s32 idx, void *dst)
{
    GXOamAttr *r = (GXOamAttr *)WfcPool_Get(sWfcOamBuf->entryPools[idx]);
    MIi_CpuCopy32(dst, r, 8);
    return r;
}

void WfcOam_FreeEntry(GXOamAttr *p)
{
    s32 z = 0;
    p->attr01 = (p->attr01 & 0xc1fffcff) | 0x200;
    if (p >= sWfcOamBuf->oam[1]) z = 1;
    WfcPool_Put(sWfcOamBuf->entryPools[z], p);
}

GXOamAttr *WfcOam_GetEntry(s32 a, s32 b)
{
    return &sWfcOamBuf->oam[a][b];
}

WfcListNode *WfcList_Create()
{
    WfcListNode *n = (WfcListNode *)WfcHeap_Alloc(sizeof(WfcListNode[2]), 4);
    n[0].prev = 0;
    n[0].next = &n[1];
    n[1].prev = n;
    n[1].next = 0;
    return n;
}

void WfcList_Destroy(void *a, ...)
{
    WfcHeap_FreeAndClear(&a);
}

void WfcList_Remove(WfcListNode *node)
{
    s32 old = OS_DisableIrqMask(1);
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = node->next = 0;
    OS_EnableIrqMask(old);
}

void WfcList_InsertBefore(WfcListNode *head, WfcListNode *node)
{
    s32 old = OS_DisableIrqMask(1);
    head->prev->next = node;
    node->prev = head->prev;
    node->next = head;
    head->prev = node;
    OS_EnableIrqMask(old);
}

void WfcList_PushBack(WfcListNode *head, WfcListNode *node)
{
    WfcList_InsertBefore(head + 1, node);
}

void WfcList_PushFront(WfcListNode *head, WfcListNode *node)
{
    WfcList_InsertBefore(head->next, node);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_022266b0) {
    HOST_OVERLAY_VAR(sWfcOamBuf),
    HOST_OVERLAY_VARS_END
};
