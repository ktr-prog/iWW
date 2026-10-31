#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0220d760.h"
#include "proto/ov001/unk_ov001_0220de1c.h"
#include "proto/ov001/unk_ov001_0220e320.h"
#include "proto/ov001/unk_ov001_0220e61c.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221cd74.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221ea94.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

extern "C" {
volatile u8 sWfcEraseConfirmed;
}

extern "C" {
s32 WfcInput_IsTouchPressedIn(void *);
s32 WfcInput_IsKeyPressed(s32);
s32 WfcInput_IsKeyRepeat(s32);
void WfcUtil_LoadFileTo(void *, void *);
void GX_LoadBG2Scr();
void OS_SpinWait(u32);
void PM_ForceToPowerOff();
void WfcConfig_EraseAll();
void OS_GetMacAddress(void *);
void swprintf(void *, s32, void *, ...);
void DWCi_BM_GetWiFiInfo(u64 *);
}

extern "C" void WfcErase_Enter() {
    sWfcEraseConfirmed = 0;
    WfcErase_LoadBg();
    WfcHighlight_Set(0x12);
    WfcUtil_ShowTopMessage(0x8c, -1, 0);
    WfcUtil_ShowBottomMessage(0x55);
    WfcUtil_SetScene(WfcErase_FadeIn);
}

extern "C" void WfcErase_LoadBg() {
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

extern "C" void WfcErase_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcErase_WaitFadeIn);
}

extern "C" void WfcErase_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(3);
    WfcUtil_SetScene(WfcErase_WaitButtonBar);
}

extern "C" void WfcErase_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcErase_Update);
}

extern "C" void WfcErase_Update() {
    WfcErase_HandleInput();
    WfcErase_Idle();
    WfcErase_HandleResult();
}

extern "C" void WfcErase_HandleInput() {
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(1);
    }
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
    }
}

extern "C" void WfcErase_Idle() {}

extern "C" void WfcErase_HandleResult() {
    switch (WfcButtonBar_GetResult()) {
    case 0:
        WfcSound_Play(7);
        WfcUtil_SetScene(WfcErase_StartExit);
        break;
    case 1:
        WfcSound_Play(6);
        WfcDialog_Open(0x56, 0, 1, -1, 0);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcErase_WaitConfirmDialog);
        break;
    }
}

extern "C" void WfcErase_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcErase_FadeOut);
}

extern "C" void WfcErase_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    if (sWfcEraseConfirmed == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcErase_Exit);
}

extern "C" void WfcErase_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (sWfcEraseConfirmed == 0) {
        if (WfcFade_IsBusy(1) != 0) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcText_DestroyBgCanvas(0);
    if (sWfcEraseConfirmed == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcEraseConfirmed == 0) {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcOptions_Enter);
    } else {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcErased_Enter);
    }
}

extern "C" void WfcErase_WaitConfirmDialog() {
    s32 r = WfcDialog_GetResult();
    if (r != 0) {
        if (r != 1) return;
        WfcSound_Play(0xe);
        sWfcEraseConfirmed = 1;
    } else {
        WfcSound_Play(7);
    }
    WfcDialog_Close();
    WfcUtil_SetScene(WfcErase_WaitDialogClosed);
}

extern "C" void WfcErase_WaitDialogClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcUtil_SetScene(WfcErase_StartExit);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220de1c) {
    HOST_OVERLAY_VAR(sWfcEraseConfirmed),
    HOST_OVERLAY_VARS_END
};
