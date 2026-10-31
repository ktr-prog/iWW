#include "types.h"
#include "proto/ov001/unk_ov001_0220cbd0.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"

struct WfcMsgBank {
    u32 *offsets;
    u8 *strings;
    void *file;
};

struct WfcMsgPool {
    WfcMsgBank banks[8];
    void *pool;
};

extern "C" {
WfcMsgPool *sWfcMsgPool;

extern void *WfcPool_Get(void *);
extern void WfcPool_Put(void *, void *);
extern void WfcHeap_FreeAndClear(void *);
extern void *WfcHeap_Alloc(s32, s32);

#pragma thumb off

void WfcMsg_InitPool() {
    WfcMsgPool *m = (WfcMsgPool *)WfcHeap_Alloc(sizeof(WfcMsgPool), 4);
    sWfcMsgPool = m;
    sWfcMsgPool->pool = WfcPool_CreateFrom(8, m->banks, sizeof(WfcMsgBank));
}

void WfcMsg_FreePool() {
    WfcHeap_FreeAndClear(&sWfcMsgPool);
}

WfcMsgBank *WfcMsg_Load(void *a) {
    u32 sz;
    WfcMsgBank *e = (WfcMsgBank *)WfcPool_Get(sWfcMsgPool->pool);
    e->file = WfcFs_LoadFile(a, &sz, 4);
    u8 *b = (u8 *)e->file + 0x20;
    e->offsets = (u32 *)(b + 0x10);
    e->strings = b + *(u32 *)(b + 4) + 8;
    return e;
}

void WfcMsg_Unload(WfcMsgBank *e) {
    WfcFs_FreeFile(e->file);
    WfcPool_Put(sWfcMsgPool->pool, e);
}

u8 *WfcMsg_GetString(WfcMsgBank *t, u32 i) {
    return t->strings + t->offsets[i & 0xffff];
}

u16 *WfcMsg_GetStringWithDigit(WfcMsgBank *t, u32 i, s32 j, u32 v) {
    u16 *p = (u16 *)(t->strings + t->offsets[i & 0xffff]);
    if (j >= 0) p[j] = v + 0x30;
    return p;
}
}
#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220cbd0) {
    HOST_OVERLAY_VAR(sWfcMsgPool),
    HOST_OVERLAY_VARS_END
};
