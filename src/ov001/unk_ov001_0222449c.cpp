#include "types.h"
#include "nitro/gxoam.h"
#include "net/WfcObjGroup.h"
#include "net/WfcPool.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_0222449c.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_022266b0.h"

#pragma thumb off

struct WfcObjList {
    WfcObjGroup nodes[0x20];
    WfcObjGroup headNode;
    WfcObjGroup tailNode;
    void *list;
    WfcPool *nodePool;
};

extern "C" {
WfcObjList *sWfcObj;
}

extern "C" {
s32 OS_DisableIrqMask(s32);
void OS_EnableIrqMask(s32);
void WfcPool_Put(WfcPool *, void *);
void *WfcPool_Get(WfcPool *);
void WfcHeap_FreeAndClear(void *);
void *WfcHeap_AllocClear(u32, u32);
void WfcList_PushFront(void *, void *);
void WfcList_PushBack(void *, void *);
void WfcList_InsertBefore(void *, void *);
void WfcList_Remove(void *);
void *WfcList_Create();
void WfcObj_GetPos(WfcObjGroup *self, s32 idx, u32 *o1, u32 *o2);
void WfcObj_SetPriority(WfcObjGroup *self, s32 idx, s32 v);
void WfcObj_SetPos(WfcObjGroup *self, s32 idx, s32 x, s32 y);
void WfcObj_SetModePalette(WfcObjGroup *p, s32 idx, u32 a, u32 b);
void WfcObj_SetAffineMode(WfcObjGroup *p, s32 idx, u32 v, u32 x);
u32 WfcObj_GetCount(WfcObjGroup *p);
GXOamAttr *WfcObj_GetOam(WfcObjGroup *p, s32 i);
void WfcObj_Free(WfcObjGroup *p);
WfcObjGroup *WfcObj_Alloc(s32 which, s32 n, s32 flag);
void WfcObj_Shutdown();
void WfcObj_Init();
}

static inline void Unk_ov001_02224558_GetPos(const GXOamAttr *e, u32 *x, u32 *y) {
    *x = (e->attr01 & 0x1ff0000) >> 16;
    *y = (e->attr01 & 0xff) >> 0;
}

static inline void Unk_ov001_02224558_SetPos(GXOamAttr *e, s32 x, s32 y) {
    e->attr01 = (e->attr01 & 0xfe00ff00) | (y & 0xff) | ((x & 0x1ff) << 16);
}

void WfcObj_Init() {
    sWfcObj = (WfcObjList *)WfcHeap_AllocClear(sizeof(WfcObjList[2]), 4);
    s32 i;
    for (i = 0; i < 2; i++) {
        sWfcObj[i].nodePool = WfcPool_CreateFrom(0x20, sWfcObj[i].nodes, sizeof(WfcObjGroup));
        sWfcObj[i].list = WfcList_Create();
        sWfcObj[i].headNode.oams = WfcOam_GetEntry(i, 0x40);
        sWfcObj[i].tailNode.oams = WfcOam_GetEntry(i, 0x7f) + 1;
        WfcList_PushFront(sWfcObj[i].list, &sWfcObj[i].headNode);
        WfcList_PushBack(sWfcObj[i].list, &sWfcObj[i].tailNode);
    }
}

void WfcObj_Shutdown() {
    s32 i;
    for (i = 0; i < 2; i++) {
        WfcList_Destroy(sWfcObj[i].list);
        WfcPool_Destroy(sWfcObj[i].nodePool);
    }
    WfcHeap_FreeAndClear(&sWfcObj);
}

WfcObjGroup *WfcObj_Alloc(s32 which, s32 n, s32 flag) {
    WfcObjGroup *r;
    WfcObjGroup *node;
    s32 irq;
    r = (WfcObjGroup *)WfcPool_Get(sWfcObj[which].nodePool);
    irq = OS_DisableIrqMask(1);
    if (flag != 0) {
        for (node = &sWfcObj[which].headNode; node != &sWfcObj[which].tailNode; node = node->next) {
            WfcObjGroup *next = node->next;
            GXOamAttr *end = node->oams + node->numOams;
            if (end + n <= next->oams) {
                r->oams = end;
                WfcList_InsertBefore(next, r);
                break;
            }
        }
        if (node == &sWfcObj[which].tailNode) Fatal_Trap();
    } else {
        for (node = &sWfcObj[which].tailNode; node != &sWfcObj[which].headNode; node = node->prev) {
            WfcObjGroup *prev = node->prev;
            GXOamAttr *start = node->oams - n;
            if (start >= prev->oams + prev->numOams) {
                r->oams = start;
                WfcList_InsertBefore(node, r);
                break;
            }
        }
        if (node == &sWfcObj[which].headNode) Fatal_Trap();
    }
    OS_EnableIrqMask(irq);
    r->numOams = n;
    return r;
}

void WfcObj_Free(WfcObjGroup *p) {
    s32 t = 0;
    GXOamAttr *e = p->oams;
    s32 i;
    for (i = t; i < p->numOams; i++, e++) {
        e->attr01 = (e->attr01 & 0xc1fffcff) | 0x200;
    }
    WfcList_Remove(p);
    WfcObjList *g = sWfcObj;
    if (p >= g[1].nodes) t = 1;
    WfcPool_Put(g[t].nodePool, p);
}

GXOamAttr *WfcObj_GetOam(WfcObjGroup *p, s32 i) {
    return p->oams + i;
}

u32 WfcObj_GetCount(WfcObjGroup *p) {
    return p->numOams;
}

void WfcObj_SetAffineMode(WfcObjGroup *p, s32 idx, u32 v, u32 x) {
    GXOamAttr *e = p->oams;
    if (idx >= 0) {
        if (v != 0x100 && v != 0x300) {
            u32 w = e[idx].attr01; w &= 0xc1fffcff; w |= v; e[idx].attr01 = w;
        } else {
            u32 w = e[idx].attr01; w &= 0xc1fffcff; w |= v; w |= x << 25; e[idx].attr01 = w;
        }
    } else {
        s32 i;
        for (i = 0; i < p->numOams; i++) {
            if (v != 0x100 && v != 0x300) {
                u32 w = e[i].attr01; w &= 0xc1fffcff; w |= v; e[i].attr01 = w;
            } else {
                u32 w = e[i].attr01; w &= 0xc1fffcff; w = (x << 25) | (w | v); e[i].attr01 = w;
            }
        }
    }
}

void WfcObj_SetModePalette(WfcObjGroup *p, s32 idx, u32 a, u32 b) {
    GXOamAttr *e = p->oams;
    if (idx >= 0) {
        e[idx].attr01 = (e[idx].attr01 & ~0xc00) | (a << 10);
        e[idx].attr2 = (e[idx].attr2 & ~0xf000) | (b << 12);
    } else {
        s32 i;
        for (i = 0; i < p->numOams; i++) {
            u32 w = e[i].attr01; w &= ~0xc00; w |= a << 10; e[i].attr01 = w;
            u32 h = e[i].attr2; h &= ~0xf000; h |= b << 12; e[i].attr2 = h;
        }
    }
}

void WfcObj_SetPos(WfcObjGroup *self, s32 idx, s32 x, s32 y) {
    GXOamAttr *p = self->oams;
    if (idx >= 0) {
        Unk_ov001_02224558_SetPos(&p[idx], x, y);
    } else {
        s32 ox, oy;
        s32 i;
        Unk_ov001_02224558_GetPos(&p[0], (u32 *)&ox, (u32 *)&oy);
        Unk_ov001_02224558_SetPos(&p[0], x, y);
        s32 dx = x - ox;
        s32 dy = y - oy;
        for (i = 1; i < self->numOams; i++) {
            s32 ex, ey;
            Unk_ov001_02224558_GetPos(&p[i], (u32 *)&ex, (u32 *)&ey);
            Unk_ov001_02224558_SetPos(&p[i], ex + dx, ey + dy);
        }
    }
}

void WfcObj_SetPriority(WfcObjGroup *self, s32 idx, s32 v) {
    GXOamAttr *p = self->oams;
    if (idx >= 0) {
        GXOamAttr *e = &p[idx];
        e->attr2 = (e->attr2 & ~0xc00) | (v << 10);
    } else {
        s32 i;
        for (i = 0; i < self->numOams; i++) {
            u32 t = p[i].attr2 & ~0xc00;
            p[i].attr2 = t | (v << 10);
        }
    }
}

void WfcObj_GetPos(WfcObjGroup *self, s32 idx, u32 *o1, u32 *o2) {
    GXOamAttr *p = self->oams;
    *o1 = (p[idx].attr01 & 0x1ff0000) >> 16;
    *o2 = p[idx].attr01 & 0xff;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0222449c) {
    HOST_OVERLAY_VAR(sWfcObj),
    HOST_OVERLAY_VARS_END
};
