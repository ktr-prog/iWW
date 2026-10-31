#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_02208a24.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220cd24.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_0220f3fc.h"
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

u8 sWfcTransferIntroAccepted;

#pragma thumb off

#define BGCNT_SET(a) IO_W((volatile u16 *)(a), (IO_R((volatile u16 *)(a)) & ~3) | 3)

void WfcTransferIntro_Enter() {
    sWfcTransferIntroAccepted = 0;
    WfcTransferIntro_LoadBg();
    WfcHighlight_Set(0x13);
    WfcUtil_ShowTopMessage(0x8d, -1, 0);
    WfcUtil_ShowBottomMessage(0x5d);
    WfcUtil_SetScene(WfcTransferIntro_FadeIn);
}

void WfcTransferIntro_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/yb5Multi.nsc.l", GX_LoadBG2Scr);
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

void WfcTransferIntro_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTransferIntro_WaitFadeIn);
}

void WfcTransferIntro_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(3);
    WfcUtil_SetScene(WfcTransferIntro_WaitButtonBar);
}

void WfcTransferIntro_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcTransferIntro_Update);
}

void WfcTransferIntro_Update() {
    WfcTransferIntro_HandleInput();
    WfcTransferIntro_Idle();
    WfcTransferIntro_HandleResult();
}

void WfcTransferIntro_HandleInput() {
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(1);
    }
    if (WfcInput_IsKeyPressed(2) == 0) return;
    WfcButtonBar_SetResult(0);
}

void WfcTransferIntro_Idle() {
}

void WfcTransferIntro_HandleResult() {
    switch (WfcButtonBar_GetResult()) {
    case 0:
        WfcSound_Play(7);
        break;
    case 1:
        WfcSound_Play(6);
        sWfcTransferIntroAccepted = 1;
        break;
    default:
        return;
    }
    WfcUtil_SetScene(WfcTransferIntro_StartExit);
}

void WfcTransferIntro_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcTransferIntro_FadeOut);
}

void WfcTransferIntro_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    if (sWfcTransferIntroAccepted == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcTransferIntro_Exit);
}

void WfcTransferIntro_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (sWfcTransferIntroAccepted == 0) {
        if (WfcFade_IsBusy(1) != 0) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcText_DestroyBgCanvas(0);
    if (sWfcTransferIntroAccepted == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcTransferIntroAccepted == 0) {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcOptions_Enter);
    } else {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcTransferNotice_Enter);
    }
}

void WfcTransferNotice_Enter() {
    WfcTransferNotice_SetupBg();
    WfcUtil_ShowBottomMessage(0x5c);
    WfcUtil_SetScene(WfcTransferNotice_FadeIn);
}

void WfcTransferNotice_SetupBg() {
    BGCNT_SET(0x4001008);
    BGCNT_SET(0x400100a);
    BGCNT_SET(0x4000008);
    BGCNT_SET(0x400000a);
    BGCNT_SET(0x400000c);
}

void WfcTransferNotice_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTransferNotice_WaitFadeIn);
}

void WfcTransferNotice_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(4);
    WfcUtil_SetScene(WfcTransferNotice_WaitButtonBar);
}

void WfcTransferNotice_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcTransferNotice_Update);
}

void WfcTransferNotice_Update() {
    WfcTransferNotice_HandleInput();
    WfcTransferNotice_Idle();
    WfcTransferNotice_HandleResult();
}

void WfcTransferNotice_HandleInput() {
    if (WfcInput_IsKeyPressed(1) == 0) return;
    WfcButtonBar_SetResult(0);
}

void WfcTransferNotice_Idle() {}

void WfcTransferNotice_HandleResult() {
    if (WfcButtonBar_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcUtil_SetScene(WfcTransferNotice_StartExit);
}

void WfcTransferNotice_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcTransferNotice_FadeOut);
}

void WfcTransferNotice_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcTransferNotice_Exit);
}

void WfcTransferNotice_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcText_DestroyBgCanvas(0);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_SetScreenFlags(0, 1);
    WfcUtil_SetScene(WfcTransferWait_Enter);
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220f9e4) {
    HOST_OVERLAY_VAR(sWfcTransferIntroAccepted),
    HOST_OVERLAY_VARS_END
};
