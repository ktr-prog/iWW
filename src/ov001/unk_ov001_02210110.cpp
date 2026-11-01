#include "types.h"
#include "host_tick.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220cd24.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_0220f9e4.h"
#include "proto/ov001/unk_ov001_02210110.h"
#include "proto/ov001/unk_ov001_02210390.h"
#include "proto/ov001/unk_ov001_02210cc0.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"

extern "C" {
void GX_LoadBG2Scr(void *, s32, u32);
void WfcUtil_LoadFileTo(void *a, void (*fn)(void *, s32, u32));
s32 WfcGx_HidePlanes(u32 a, u32 b);
s32 WfcGx_ShowPlanes(u32 a, u32 b);
s32 WfcInput_IsKeyPressed(u32 a);

u8 sWfcTransferCancelledTimer;

#pragma thumb off


void WfcTransferCancelled_Enter() {
    sWfcTransferCancelledTimer = 0;
    WfcTransferCancelled_LoadBg();
    WfcUtil_ShowBottomMessage(0x63);
    WfcUtil_SetScene(WfcTransferCancelled_FadeIn);
}

void WfcTransferCancelled_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/yb5Multi.nsc.l", GX_LoadBG2Scr);
    volatile u16 *r1 = (volatile u16 *)0x4001008;
    volatile u16 *r2 = (volatile u16 *)0x400100a;
    volatile u16 *r3 = (volatile u16 *)0x400000a;
    volatile u16 *r4 = (volatile u16 *)0x400000c;
    IO_W(r1, (IO_R(r1) & ~3) | 3);
    IO_W(r2, (IO_R(r2) & ~3) | 3);
    IO_W(r3, (IO_R(r3) & ~3) | 3);
    IO_W(r4, (IO_R(r4) & ~3) | 3);
}

void WfcTransferCancelled_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTransferCancelled_WaitFadeIn);
}

void WfcTransferCancelled_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcTransfer_IsFinished() == 0) return;
    WfcUtil_SetScene(WfcTransferCancelled_Update);
}

void WfcTransferCancelled_Update() {
    WfcTransferCancelled_WaitTimer();
    WfcTransferCancelled_Idle();
}

void WfcTransferCancelled_Idle() {
}

void WfcTransferCancelled_FadeOut() {
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcTransferCancelled_Exit);
}

void WfcTransferCancelled_Exit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcText_DestroyBgCanvas(0);
    WfcUtil_HideTopMessage();
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_SetScreenFlags(0, 1);
    WfcUtil_SetScene(WfcOptions_Enter);
}

void WfcTransferCancelled_WaitTimer() {
    sWfcTransferCancelledTimer = sWfcTransferCancelledTimer + (TICK_STEP_ENDS() ? 1 : 0);
    if (sWfcTransferCancelledTimer < 0x78) return;
    WfcUtil_SetScene(WfcTransferCancelled_FadeOut);
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02210110) {
    HOST_OVERLAY_VAR(sWfcTransferCancelledTimer),
    HOST_OVERLAY_VARS_END
};
