#include "types.h"
#include "net/CommManager.h"
#include "net/NetStateBlockHeader.h"
#include "proto/main/unk_020a647c.h"


extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
s32 Scene_GetCurrent();
}

extern CommManager *gCommManager;

extern void (*const sNetStateBWriters[1])(s32);
extern void (*const sNetStateBReaders[1])(u8 *, u32);

void (*const sNetStateBWriters[1])(s32) = {(void (*)(s32))NetArea_WriteStateBPart0};
void (*const sNetStateBReaders[1])(u8 *, u32) = {(void (*)(u8 *, u32))NetArea_ReadStateBPart0};


extern "C" void NetArea_WriteStateBPart0() {}

extern "C" void NetArea_BuildStateB() {
    CommManager *g = gCommManager;
    g->clearAuxLenB();
    u8 *base = (u8 *)g->getAuxBufB();
    u8 *p = base + 2;
    s32 m = Scene_GetCurrent();
    g->auxWritePtrB = p + 4;
    u8 *start = g->auxWritePtrB;
    sNetStateBWriters[0](m);
    u8 *cur = g->auxWritePtrB;
    NetStateBlockHeader b;
    s32 diff = cur - start;
    if (diff != 0) {
        b.len = diff;
        b.id = 0;
        MI_CpuCopy8(&b.len, p, 4);
        p = cur;
    }
    s32 tot = p - base;
    b.total = tot - 2;
    MI_CpuCopy8(&b.total, base, 2);
    g->setAuxLenB(tot);
}

extern "C" void NetArea_ReadStateBPart0() {}

extern "C" void NetArea_ParseStateB() {
    CommManager *g = gCommManager;
    CommManager *sg = g;
    u8 *p = (u8 *)g->getAuxBufB();
    NetStateBlockHeader b;
    u32 n;
    MI_CpuCopy8(p, &b.total, 2);
    u32 total = b.total;
    n = 0;
    p += 2;
    n += 2;
    while (n < total) {
        MI_CpuCopy8(p, &b.len, 4);
        p += 4;
        n += 4;
        u32 len = b.len;
        u32 id = *(volatile u8 *)&b.id;
        sNetStateBReaders[id](p, len);
        p += len;
        n += len;
    }
    sg->clearAuxLenB();
}
