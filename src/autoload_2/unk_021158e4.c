#include "uptr.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_021158e4.h"
#include "proto/autoload_2/unk_02115bac.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef void (*MIDmaCallback)(void *arg);

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 mode);
extern void MIi_CheckDma0SourceAddress(u32 dmaNo, uptr src, u32 size, u32 flags);
extern void MI_WaitDma(u32 dmaNo);
extern void OSi_EnterDmaCallback(u32 dmaNo, MIDmaCallback cb, void *arg);
extern void MIi_DmaSetParams(u32 dmaNo, uptr src, uptr dest, u32 cnt);
extern void MIi_DmaSetParams_wait_noInt(u32 dmaNo, uptr src, uptr dest, u32 cnt);
extern void MIi_DmaSetParams_noInt(u32 dmaNo, uptr src, uptr dest, u32 cnt);
extern void MIi_DmaSetParams_wait(u32 dmaNo, uptr src, uptr dest, u32 cnt);

#include "nitro/mi_gxdma.h"
typedef MIGXDmaParams MIiGxDmaState;

extern MIiGxDmaState data_027e0414;

void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 mode);

void MI_DmaCopy32Async(u32 dmaNo, uptr src, uptr dest, u32 size, MIDmaCallback callback, void *arg) {
    MIi_CheckDma0SourceAddress(dmaNo, src, size, 0);
    if (size == 0) {
        if (callback) callback(arg);
        return;
    }
    MI_WaitDma(dmaNo);
    if (callback) {
        OSi_EnterDmaCallback(dmaNo, callback, arg);
        MIi_DmaSetParams(dmaNo, src, dest, (size >> 2) | 0xc4000000);
    } else {
        MIi_DmaSetParams(dmaNo, src, dest, (size >> 2) | 0x84000000);
    }
}

void MI_StopDma(u32 dmaNo) {
    vu16 *dmaCntp;
    u32 e = OS_DisableInterrupts();
    u32 tmp;
    dmaCntp = &((vu16 *)0x040000b0)[dmaNo * 6 + 5];
    IO_AND(dmaCntp, ~0x3a00);
    IO_AND(dmaCntp, ~0x8000);
    tmp = IO_R(dmaCntp);
    tmp = IO_R(dmaCntp);
    if (dmaNo == 0) {
        vu32 *p;
        p = (vu32 *)(uptr)(0x040000b0 + dmaNo * 12);
        IO_W(&((vu32 *)(uptr)(0x04000000 + dmaNo * 12))[0xb0 / 4], 0);
        IO_W(&p[1], 0);
        IO_W(&p[2], 0x81400001);
    }
    OS_RestoreInterrupts(e);
}

void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 mode) {
    int i;
    vu32 *p = (vu32 *)0x040000b8;
    for (i = 0; i < 3; i++, p += 3) {
        u32 cnt;
        u32 cur;
        if (i == dmaNo) continue;
        cnt = IO_R(p);
        if (!(cnt & 0x80000000)) continue;
        cur = cnt & 0x38000000;
        if (cur == mode) continue;
        if (cur == 0x08000000 && mode == 0x10000000) continue;
        if (cur == 0x10000000 && mode == 0x08000000) continue;
        if (cur == 0x18000000 || cur == 0x20000000 || cur == 0x28000000 || cur == 0x30000000 || cur == 0x38000000 ||
            cur == 0x08000000 || cur == 0x10000000) {
            Fatal_Trap();
        }
    }
}

void MI_SetWramBank(u32 v) {
    IO_W((vu8 *)0x04000247, (u8)v);
}
