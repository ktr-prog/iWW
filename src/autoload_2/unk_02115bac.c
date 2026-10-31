#include "uptr.h"
#include "nitro/io_access.h"
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

void MI_SendGXCommandAsyncFast(u32 dmaNo, uptr src, u32 size, MIDmaCallback callback, void *arg) {
    if (size == 0) {
        if (callback) callback(arg);
        return;
    }
    while (((volatile MIiGxDmaState *)&data_027e0414)->isBusy)
        ;
    data_027e0414.isBusy = 1;
    data_027e0414.dmaNo = dmaNo;
    data_027e0414.callback = callback;
    data_027e0414.arg = arg;
    MIi_CheckAnotherAutoDMA(dmaNo, 0x38000000);
    MIi_CheckDma0SourceAddress(dmaNo, src, size, 0);
    MI_WaitDma(dmaNo);
    OSi_EnterDmaCallback(dmaNo, (MIDmaCallback)MIi_DMAFastCallback, 0);
    MIi_DmaSetParams(dmaNo, src, 0x04000400, (size >> 2) | 0xfc400000);
}

void MIi_DMAFastCallback(void) {
    void *arg;
    data_027e0414.isBusy = 0;
    arg = data_027e0414.arg;
    if (data_027e0414.callback) data_027e0414.callback(arg);
}

void MI_DmaFill32(u32 dmaNo, uptr dest, u32 data, u32 size) {
    vu32 *dmaCntp;
    u32 e;
    if (size == 0) return;
    dmaCntp = &((vu32 *)0x040000b0)[dmaNo * 3 + 2];
    while (IO_R(dmaCntp) & 0x80000000)
        ;
    e = OS_DisableInterrupts();
    IO_W(&((vu32 *)0x040000e0)[dmaNo], data);
    MIi_DmaSetParams_wait_noInt(dmaNo, (uptr)&((vu32 *)0x040000e0)[dmaNo], dest, (size >> 2) | 0x85000000);
    OS_RestoreInterrupts(e);
    while (IO_R(dmaCntp) & 0x80000000)
        ;
}

void MI_DmaCopy32(u32 dmaNo, uptr src, uptr dest, u32 size) {
    vu32 *dmaCntp;
    MIi_CheckDma0SourceAddress(dmaNo, src, size, 0);
    if (size == 0) return;
    dmaCntp = &((vu32 *)0x040000b0)[dmaNo * 3 + 2];
    while (IO_R(dmaCntp) & 0x80000000)
        ;
    MIi_DmaSetParams_wait(dmaNo, src, dest, (size >> 2) | 0x84000000);
    while (IO_R(dmaCntp) & 0x80000000)
        ;
}

void MI_DmaCopy16(u32 dmaNo, uptr src, uptr dest, u32 size) {
    vu32 *dmaCntp;
    if (size == 0) return;
    MIi_CheckDma0SourceAddress(dmaNo, src, size, 0);
    dmaCntp = &((vu32 *)0x040000b0)[dmaNo * 3 + 2];
    while (IO_R(dmaCntp) & 0x80000000)
        ;
    MIi_DmaSetParams_wait(dmaNo, src, dest, (size >> 1) | 0x80000000);
    while (IO_R(dmaCntp) & 0x80000000)
        ;
}
