#include "uptr.h"
#include "nitro/io_access.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef volatile u32 vu32;
typedef void (*MIDmaCallback)(void *arg);

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 mode);
extern void MI_WaitDma(u32 dmaNo);
extern void OSi_EnterDmaCallback(u32 dmaNo, MIDmaCallback cb, void *arg);
extern void MIi_DmaSetParams_noInt(u32 dmaNo, uptr src, uptr dest, u32 ctrl);

#define MIi_DMA_CLEAR_DATA(dmaNo) (((vu32 *)0x040000e0)[dmaNo])

static inline void MIi_CallCallback(MIDmaCallback callback, void *arg) {
    if (callback) {
        callback(arg);
    }
}

static inline void MIi_DmaSetParams_src32(u32 dmaNo, u32 data, uptr dest, u32 ctrl) {
    u32 enabled = OS_DisableInterrupts();
    vu32 *p = &MIi_DMA_CLEAR_DATA(dmaNo);
    IO_W(p, data);
    MIi_DmaSetParams_noInt(dmaNo, (uptr)p, dest, ctrl);
    OS_RestoreInterrupts(enabled);
}

void MI_DmaFill32Async(u32 dmaNo, void *dest, u32 data, u32 size, MIDmaCallback callback, void *arg) {
    if (size == 0) {
        MIi_CallCallback(callback, arg);
    } else {
        MI_WaitDma(dmaNo);
        if (callback) {
            OSi_EnterDmaCallback(dmaNo, callback, arg);
            MIi_DmaSetParams_src32(dmaNo, data, (uptr)dest, (size >> 2) | 0xc5000000);
        } else {
            MIi_DmaSetParams_src32(dmaNo, data, (uptr)dest, (size >> 2) | 0x85000000);
        }
    }
}
