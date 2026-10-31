#include "types.h"
#include "game/Random.h"
#include "gfx/DebugColor.h"
#include "nitro/io_access.h"
#include "sys/OSThread.h"

#include "sys/OverlayHandle.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_0206d5b8.h"

enum { OVERLAY_ID_WFC_UTIL = 1, OVERLAY_ID_DWC = 65 };

extern OverlayHandle gOverlayHandle;
extern "C" {
extern u8 data_021fccfc[];
extern u8 sFatalEntered;
u32 OS_DisableInterrupts(void);
void OS_Halt(void);
void OS_RestoreInterrupts(u32 v);
void OS_DisableIrqMask(s32 v);
void OS_ResetRequestIrqMask(s32 v);
void OverlayHandle_Load(OverlayHandle *p, s32 v);
void OverlayHandle_Unload(OverlayHandle *p);
void DwcNet_SetAllocator(void *(*alloc)(u32, u32, s32), void (*free)(u32, void *));
void WfcUtil_Run(void *work, s32 a, s32 b);
s32 PXI_SendWordByFifo(s32 a, s32 b, s32 c);
void WaitByLoop(s32 n);
}


extern "C" void *Main_DwcAlloc(u32 name, u32 size, s32 align) {
    return Mem_AllocAligned(size, align);
}

extern "C" void Main_DwcFree(u32 a, void *p) {
    Mem_Free(p);
}

extern "C" void Main_RunWifiUtility(void) {
    u32 ime = OS_DisableInterrupts();
    volatile u16 *reg = (volatile u16 *)0x4000208;
    u16 old = IO_R(reg);
    IO_W(reg, 0);
    OS_DisableIrqMask(7);
    OS_ResetRequestIrqMask(7);
    OverlayHandle_Load(&gOverlayHandle, OVERLAY_ID_DWC);
    DwcNet_SetAllocator(Main_DwcAlloc, Main_DwcFree);
    OverlayMgr_Acquire(OVERLAY_ID_WFC_UTIL);
    void *p = Mem_AllocAligned(0x40000, 0x20);
    WfcUtil_Run(p, 1, 0x20);
    Mem_Free(p);
    OverlayMgr_Release(OVERLAY_ID_WFC_UTIL);
    OverlayHandle_Unload(&gOverlayHandle);
    IO_R(reg);
    IO_W(reg, old);
    OS_RestoreInterrupts(ime);
}

extern "C" void Main_PxiSendWordRetry(s32 a, s32 b) {
    while (PXI_SendWordByFifo(0xe, a, 0) != 0) {
        WaitByLoop(b);
    }
}

extern "C" void Fatal_Handler(void *arg) {
    OS_DisableInterrupts();
    Main_PxiSendWordRetry(1, 1);
    if (sFatalEntered == 0) {
        sFatalEntered = 1;
        Fatal_ExceptionCallback(arg, data_021fccfc);
    }
    while (sFatalEntered != 0) {
        OS_DisableInterrupts();
        OS_Halt();
    }
}

DebugColor data_021cb3d8(31, 20, 20, 31);
u8 sFatalEntered;
DebugColor data_021cb3e0(20, 20, 31, 31);
s32 sVBlankCount;
DebugColor data_021cb3c8(31, 31, 20, 31);
OSThreadQueue gFrameWaitQueue;
DebugColor data_021cb3c4(20, 31, 20, 31);
DebugColor data_021cb3cc(20, 31, 31, 31);
DebugColor data_021cb3d0(20, 24, 24, 31);
OSThreadQueue gVBlankQueue;
Random data_021cb3d4;
u8 sVBlankReady;
u16 gMainWaitingFrame;
