#include "nitro/io_access.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_02117e8c.h"
#include "proto/itcm/unk_01ffa4a0.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef void (*PXIFifoCallback)(u32 tag, u32 data, BOOL err);

typedef HostSysWork OSSystemWork;
#define OS_GetSystemWork() (&gHostSysWork)

extern u16 data_021fea64;
extern PXIFifoCallback data_027e0394[32];

#define REG_PXI_SUBPINTF (*(volatile u16 *)0x04000180)
#define REG_PXI_FIFO_CNT (*(volatile u16 *)0x04000184)

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
void OS_ResetRequestIrqMask(u32 mask);
void OS_SetIrqFunction(u32 mask, void (*handler)(void));
void OS_EnableIrqMask(u32 mask);

void PXI_InitFifo(void) {
    OSSystemWork *p = OS_GetSystemWork();
    u32 enabled = OS_DisableInterrupts();
    s32 i;
    if (data_021fea64 == 0) {
        data_021fea64 = 1;
        p->pxiHandleChecker[0] = 0;
        for (i = 0; i < 32; i++) {
            data_027e0394[i] = 0;
        }
        IO_W(&REG_PXI_FIFO_CNT, 0xc408);
        OS_ResetRequestIrqMask(0x40000);
        OS_SetIrqFunction(0x40000, PXIi_HandlerRecvFifoNotEmpty);
        OS_EnableIrqMask(0x40000);
        for (i = 0;; i++) {
            s32 timeout;
            s32 status;
            status = IO_R(&REG_PXI_SUBPINTF) & 0xf;
            IO_W(&REG_PXI_SUBPINTF, (u16)(status << 8));
            if (status == 0 && i > 4) {
                break;
            }
            for (timeout = 1000; (IO_R(&REG_PXI_SUBPINTF) & 0xf) == status; timeout--) {
                if (timeout <= 0) {
                    i = 0;
                    break;
                }
            }
        }
    }
    OS_RestoreInterrupts(enabled);
}

void PXI_SetFifoRecvCallback(s32 tag, PXIFifoCallback callback) {
    OSSystemWork *p = OS_GetSystemWork();
    u32 enabled = OS_DisableInterrupts();
    data_027e0394[tag] = callback;
    if (callback) {
        p->pxiHandleChecker[0] |= 1 << tag;
    } else {
        p->pxiHandleChecker[0] &= ~(1 << tag);
    }
    OS_RestoreInterrupts(enabled);
}

BOOL PXI_IsCallbackReady(s32 tag, s32 proc) {
    OSSystemWork *p = OS_GetSystemWork();
    return (p->pxiHandleChecker[proc] & (1 << tag)) ? 1 : 0;
}

u16 data_021fea64;
