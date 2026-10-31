#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220cd24.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_0220f3fc.h"
#include "proto/ov001/unk_ov001_0220f9e4.h"
#include "proto/ov001/unk_ov001_02210110.h"
#include "proto/ov001/unk_ov001_02210390.h"
#include "proto/ov001/unk_ov001_022107f0.h"
#include "proto/ov001/unk_ov001_02210cc0.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"

extern "C" {
extern u8 GX_LoadBG2Scr[];
void MIi_CpuClear16(u32 a, void *b, u32 c);
void MIi_CpuCopy16(void *a, void *b, u32 c);
void WfcUtil_LoadFileTo(void *a, void *b);
s32 WfcInput_IsKeyPressed(u32 a);

u8 sWfcTransferFailedTopShown;
u8 sWfcTransferFailedRetry;

#pragma thumb off


void WfcTransferFailed_Enter() {
    WfcTransferFailed_LoadBg();
    WfcUtil_ShowBottomMessage(0x62);
    sWfcTransferFailedTopShown = WfcUtil_ShowTopMessage(0x8d, -1, 0);
    WfcUtil_SetScene(WfcTransferFailed_FadeIn);
}

void WfcTransferFailed_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/yb5Multi.nsc.l", (void *)GX_LoadBG2Scr);
    volatile u16 *r1 = (volatile u16 *)0x4001008;
    volatile u16 *r2 = (volatile u16 *)0x400100a;
    volatile u16 *r3 = (volatile u16 *)0x4000008;
    volatile u16 *r4 = (volatile u16 *)0x400000a;
    volatile u16 *r5 = (volatile u16 *)0x400000c;
    IO_W(r1, (IO_R(r1) & ~3) | 3);
    IO_W(r2, (IO_R(r2) & ~3) | 3);
    IO_W(r3, (IO_R(r3) & ~3) | 3);
    IO_W(r4, (IO_R(r4) & ~3) | 3);
    IO_W(r5, (IO_R(r5) & ~3) | 3);
}

void WfcTransferFailed_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    if (sWfcTransferFailedTopShown != 0) {
        WfcFade_Start(2, 1, 1, 8);
        WfcGx_ShowPlanes(1, 1);
    }
    WfcUtil_SetScene(WfcTransferFailed_WaitFadeIn);
}

void WfcTransferFailed_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(3);
    WfcUtil_SetScene(WfcTransferFailed_WaitButtonBar);
}

void WfcTransferFailed_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    if (WfcTransfer_IsFinished() == 0) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcTransferFailed_Update);
}

void WfcTransferFailed_Update() {
    WfcTransferFailed_HandleInput();
    WfcTransferFailed_Idle();
    WfcTransferFailed_HandleResult();
}

void WfcTransferFailed_HandleInput() {
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(1);
    }
    if (WfcInput_IsKeyPressed(2) == 0) return;
    WfcButtonBar_SetResult(0);
}

void WfcTransferFailed_Idle() {
}

void WfcTransferFailed_HandleResult() {
    s32 r = WfcButtonBar_GetResult();
    if (r != 0) {
        if (r != 1) return;
        sWfcTransferFailedRetry = 1;
        WfcSound_Play(6);
    } else {
        sWfcTransferFailedRetry = 0;
        WfcSound_Play(7);
    }
    WfcUtil_SetScene(WfcTransferFailed_StartExit);
}

void WfcTransferFailed_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcTransferFailed_FadeOut);
}

void WfcTransferFailed_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    if (sWfcTransferFailedRetry == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcTransferFailed_Exit);
}

void WfcTransferFailed_Exit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcText_DestroyBgCanvas(0);
    if (sWfcTransferFailedRetry == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcTransferFailedRetry == 0) {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcOptions_Enter);
    } else {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcTransferWait_Enter);
    }
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02210390) {
    HOST_OVERLAY_VAR(sWfcTransferFailedTopShown),
    HOST_OVERLAY_VAR(sWfcTransferFailedRetry),
    HOST_OVERLAY_VARS_END
};
