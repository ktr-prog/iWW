#include "types.h"
#include "net/CommManager.h"
#include "net/NetStateBlockHeader.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_020a6564.h"



extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
s32 Scene_GetCurrent();
}

extern CommManager *gCommManager;


typedef void (*NetStateAReader)(u8 *, u32);

extern "C" {
extern const NetStateAReader sNetStateAReaders[2];
}

extern "C" const NetStateAReader sNetStateAReaders[2] = {
    (NetStateAReader)NetArea_ReadStateAPart0,
    (NetStateAReader)NetArea_ReadStateANpcTalk,
};

extern "C" void NetArea_ReadStateAPart0() {}

extern "C" void NetArea_ReadStateANpcTalk(u8 *p) {
    u8 v = 0;
    Scene_GetCurrent();
    MI_CpuCopy8(p, &v, 1);
    if (v != 0) {
        NpcNetRecord_ResetTalkSlots();
    }
}

extern "C" void NetArea_ParseStateA() {
    CommManager *g = gCommManager;
    CommManager *sg = g;
    u8 *p = (u8 *)g->getAuxBufA();
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
        sNetStateAReaders[id](p, len);
        p += len;
        n += len;
    }
    sg->clearAuxLenA();
}
