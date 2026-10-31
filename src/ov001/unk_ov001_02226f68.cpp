#include "types.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226f68.h"

struct WfcTask {
    WfcTask *prev;
    WfcTask *next;
    void (*func)(WfcTask *, void *);
    void *work;
    u8 priority;
    u8 ownsWork;
};

struct WfcTaskList {
    void *nodePool;
    void *deleteQueue;
    void *list;
    WfcTask headNode;
    WfcTask tailNode;
    s32 capacity;
    u8 isActive;
    void *nodeBuffer;
};

extern "C" {
s32 OS_DisableIrqMask(s32);
void OS_EnableIrqMask(s32);
void WfcHeap_FreeAndClear(void *);
void WfcList_Remove(void *);
void WfcPool_Put(void *, void *);
void *WfcPool_Get(void *);
void WfcList_InsertBefore(void *, void *);
void *WfcHeap_Alloc(s32, s32);
void *WfcList_Create();
void WfcList_PushFront(void *, void *);
void WfcList_PushBack(void *, void *);
void WfcTask_SetFunc(void *task, void *v);
}

extern "C" const u8 sWfcTaskListSizes[2] = {0x80, 0x20};
extern "C" WfcTaskList *sWfcTaskLists = 0;

#pragma thumb off

void WfcTask_Init() {
    s32 i;
    const u8 *pa;
    sWfcTaskLists = (WfcTaskList *)WfcHeap_Alloc(sizeof(WfcTaskList[2]), 4);
    pa = sWfcTaskListSizes;
    for (i = 0; i < 2; i++) {
        sWfcTaskLists[i].capacity = *pa;
        sWfcTaskLists[i].nodeBuffer = WfcHeap_Alloc(*pa * sizeof(WfcTask), 4);
        sWfcTaskLists[i].nodePool = WfcPool_CreateFrom(*pa, sWfcTaskLists[i].nodeBuffer, sizeof(WfcTask));
        sWfcTaskLists[i].deleteQueue = WfcPool_Create(*pa);
        sWfcTaskLists[i].list = WfcList_Create();
        sWfcTaskLists[i].headNode.priority = 0;
        sWfcTaskLists[i].tailNode.priority = 0xff;
        WfcList_PushFront(sWfcTaskLists[i].list, &sWfcTaskLists[i].headNode);
        WfcList_PushBack(sWfcTaskLists[i].list, &sWfcTaskLists[i].tailNode);
        sWfcTaskLists[i].isActive = 1;
        pa++;
    }
}

void WfcTask_Shutdown() {
    s32 i = 0;
    do {
        WfcList_Destroy(sWfcTaskLists[i].list);
        WfcPool_Destroy(sWfcTaskLists[i].nodePool);
        i++;
    } while (i < 2);
    WfcHeap_FreeAndClear(&sWfcTaskLists);
}

void WfcTask_RunList(u32 i) {
    WfcTaskList *s = &sWfcTaskLists[i];
    if (s->isActive == 0) return;
    WfcTask *n = s->headNode.next;
    if (n != &s->tailNode) {
        do {
            n->func(n, n->work);
            n = n->next;
        } while (n != &sWfcTaskLists[i].tailNode);
    }
    s32 k = 0;
    if (sWfcTaskLists[i].capacity > 0) {
        do {
            void *e = WfcPool_Get(sWfcTaskLists[i].deleteQueue);
            if (e == 0) return;
            WfcTask_Release(i, e);
            k++;
        } while (k < sWfcTaskLists[i].capacity);
    }
}

void *WfcTask_Add(u32 i, void *a, void *b, u32 c) {
    return WfcTask_AddEx(i, a, b, c, 0);
}

void *WfcTask_AddEx(u32 i, void *a, void *b, u32 c, u8 d) {
    WfcTask *n = (WfcTask *)WfcPool_Get(sWfcTaskLists[i].nodePool);
    n->func = (void (*)(WfcTask *, void *))a;
    n->work = b;
    n->priority = c;
    n->ownsWork = d;
    s32 irq = OS_DisableIrqMask(1);
    WfcTask *q = sWfcTaskLists[i].headNode.next;
loop:
    if (c >= q->priority) goto next;
    WfcList_InsertBefore(q, n);
    goto done;
next:
    q = q->next;
    goto loop;
done:
    OS_EnableIrqMask(irq);
    return n;
}

void WfcTask_SetFunc(void *task, void *v) {
    WfcTask *n = (WfcTask *)task;
    n->func = (void (*)(WfcTask *, void *))v;
}

void WfcTask_RequestDelete(u32 i, void *p) {
    WfcPool_Put(sWfcTaskLists[i].deleteQueue, p);
}

void WfcTask_Delete(u32 i, void *p) {
    WfcTask_Release(i, p);
}

void WfcTask_Release(u32 i, void *p) {
    WfcTask *n = (WfcTask *)p;
    if (n->ownsWork != 0) {
        WfcHeap_FreeAndClear(&n->work);
    }
    WfcList_Remove(n);
    WfcPool_Put(sWfcTaskLists[i].nodePool, n);
}

void WfcTask_SetListActive(u32 i, u32 v) {
    sWfcTaskLists[i].isActive = v;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02226f68) {
    HOST_OVERLAY_VAR(sWfcTaskLists),
    HOST_OVERLAY_VARS_END
};
