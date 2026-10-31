#include "uptr.h"
#include "host_mem.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
#include "nitro/dma_host.h"
#include "uptr.h"
#include "proto/itcm/unk_01ffd784.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 enabled);
extern void DC_StoreAll(void);
extern void DC_InvalidateAll(void);
extern void IC_InvalidateAll(void);
extern void DC_WaitWriteBufferEmpty(void);
extern void OSi_DoBoot(void);
extern vu16 data_021fcf50;
void OSi_ReadCardRom32(u32 src, void *dst, s32 len);

void MIi_DmaSetParams_wait(u32 dmaNo, uptr src, uptr dest, u32 ctrl) {
    u32 enabled = OS_DisableInterrupts();
    vu32 *p = (vu32 *)(uptr)(0x040000b0 + dmaNo * 12);
    HostDma_Addresses(dmaNo, src, dest);
    IO_W(p, src);
    IO_W((p + 1), dest);
    IO_W((p + 2), ctrl);
    (void)IO_R((vu32 *)0x040000b0);
    (void)IO_R((vu32 *)0x040000b0);
    if (dmaNo == 0) {
        IO_W(p, 0);
        IO_W((p + 1), 0);
        IO_W((p + 2), 0x81400001);
    }
    (void)OS_RestoreInterrupts(enabled);
}

void MIi_DmaSetParams_noInt(u32 dmaNo, uptr src, uptr dest, u32 ctrl) {
    vu32 *p = (vu32 *)(uptr)(0x040000b0 + dmaNo * 12);
    HostDma_Addresses(dmaNo, src, dest);
    IO_W(p, src);
    IO_W((p + 1), dest);
    IO_W((p + 2), ctrl);
}

void MIi_DmaSetParams_wait_noInt(u32 dmaNo, uptr src, uptr dest, u32 ctrl) {
    vu32 *p = (vu32 *)(uptr)(0x040000b0 + dmaNo * 12);
    HostDma_Addresses(dmaNo, src, dest);
    IO_W(p, src);
    IO_W((p + 1), dest);
    IO_W((p + 2), ctrl);
    (void)IO_R((vu32 *)0x040000b0);
    (void)IO_R((vu32 *)0x040000b0);
    if (dmaNo == 0) {
        IO_W(p, 0);
        IO_W((p + 1), 0);
        IO_W((p + 2), 0x81400001);
    }
    (void)IO_R((vu32 *)0x040000b0);
    (void)IO_R((vu32 *)0x040000b0);
}

void OSi_DoResetSystem(void) {
    extern void host_reset_system(void);
    host_reset_system();
}

void OSi_ReloadRomData(void) {
    u32 base = *HW_SYSWORK(u32, romBaseOffset);
    u32 a, b, c, d, e, f;
    BOOL en;
    if (base >= 0x8000) {
        OSi_ReadCardRom32(base, HW_SYSWORK(void, romHeader), 0x160);
    }
    a = *HW_SYSWORK_AT(u32, romHeader, 0x20);
    b = *HW_SYSWORK_AT(u32, romHeader, 0x28);
    c = *HW_SYSWORK_AT(u32, romHeader, 0x2c);
    d = *HW_SYSWORK_AT(u32, romHeader, 0x30);
    e = *HW_SYSWORK_AT(u32, romHeader, 0x38);
    f = *HW_SYSWORK_AT(u32, romHeader, 0x3c);
    en = OS_DisableInterrupts();
    DC_StoreAll();
    DC_InvalidateAll();
    OS_RestoreInterrupts(en);
    IC_InvalidateAll();
    DC_WaitWriteBufferEmpty();
    a += base;
    d += base;
    if (a < 0x8000) {
        u32 diff = 0x8000 - a;
        b += diff;
        c -= diff;
        a = 0x8000;
    }
    OSi_ReadCardRom32(a, (void *)(uptr)b, c);
    OSi_ReadCardRom32(d, (void *)(uptr)e, f);
}

void OSi_ReadCardRom32(u32 src, void *dst, s32 len) {
    u32 ctrl = (*HW_SYSWORK_AT(vu32, romHeader, 0x60) & ~0x07000000) | 0xa1000000;
    s32 i = -(s32)(src & 0x1ff);
    while (IO_R((vu32 *)0x040001a4) & 0x80000000) {
    }
    IO_W((vu8 *)0x040001a1, 0x80);
    src += i;
    if (i >= len) {
        return;
    }
    do {
        u32 w;
        IO_W((vu8 *)0x040001a8, 0xb7);
        IO_W((vu8 *)0x040001a9, (u8)(src >> 24));
        IO_W((vu8 *)0x040001aa, (u8)(src >> 16));
        IO_W((vu8 *)0x040001ab, (u8)(src >> 8));
        IO_W((vu8 *)0x040001ac, (u8)src);
        IO_W((vu8 *)0x040001ad, 0);
        IO_W((vu8 *)0x040001ae, 0);
        IO_W((vu8 *)0x040001af, 0);
        IO_W((vu32 *)0x040001a4, ctrl);
        do {
            w = IO_R((vu32 *)0x040001a4);
            if (w & 0x00800000) {
                u32 d = IO_R((vu32 *)0x04100010);
                if (i >= 0 && i < len) {
                    *(u32 *)((u8 *)dst + i) = d;
                }
                i += 4;
            }
        } while (w & 0x80000000);
        src += 0x200;
    } while (i < len);
}

