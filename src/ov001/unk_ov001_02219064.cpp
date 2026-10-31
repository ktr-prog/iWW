#include "types.h"
#include "host_mem.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_02218300.h"
#include "proto/ov001/unk_ov001_02219064.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"

#pragma thumb off

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {
void OS_Sleep(u32 msec);
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
}

extern "C" u8 sWfcSimpleStartInitReady = 0;

#define BGCNT(a, v) IO_W((volatile u16 *)(a), (IO_R((volatile u16 *)(a)) & ~3) | (v))

extern "C" s32 WfcSimpleStartInit_IsLidClosed() {
    s32 v = *HW_SYSWORK(volatile u16, buttonXY) & 0x8000;
    v >>= 15;
    if (v != 0) return TRUE;
    return FALSE;
}

extern "C" void WfcSimpleStartInit_Enter() {
    sWfcSimpleStartInitReady = 0;
    WfcSimpleStartInit_LoadBg();
    WfcHighlight_SetConnection();
    WfcUtil_ShowTopMessage(0x83, -1, 0);
    WfcUtil_ShowStepIndicator(2);
    WfcUtil_ShowBottomMessage(0x69);
    WfcBusyIcon_Create(0);
    WfcSound_Play(0xb);
    WfcUtil_SetScene(WfcSimpleStartInit_FadeIn);
}

extern "C" void WfcSimpleStartInit_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jbBgStep3.ncg.l", (WfcLoadFunc)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep3.ncl.l", (WfcLoadFunc)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/xb4Multi.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
    BGCNT(0x4001008, 3);
    BGCNT(0x400100a, 3);
    BGCNT(0x4000008, 3);
    BGCNT(0x400000a, 3);
    BGCNT(0x400000c, 3);
}

extern "C" void WfcSimpleStartInit_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcSimpleStartInit_WaitFadeIn);
}

extern "C" void WfcSimpleStartInit_WaitFadeIn() {
    if (WfcFade_IsBusy(1)) return;
    if (WfcFade_IsBusy(0)) return;
    WfcSimpleStart_Begin();
    WfcUtil_OpenButtonBar(1);
    WfcUtil_SetScene(WfcSimpleStartInit_WaitButtonBar);
}

extern "C" void WfcSimpleStartInit_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcSimpleStartInit_Update);
}

extern "C" void WfcSimpleStartInit_Update() {
    OS_Sleep(10);
    WfcSimpleStartInit_CheckStatus();
    WfcSimpleStartInit_HandleInput();
    WfcSimpleStartInit_Idle();
    WfcSimpleStartInit_HandleResult();
}

extern "C" void WfcSimpleStartInit_HandleInput() {
    if (WfcInput_IsKeyPressed(2)) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcSimpleStartInit_IsLidClosed() == 0) return;
    WfcButtonBar_SetResult(0);
}

extern "C" void WfcSimpleStartInit_Idle() {}

extern "C" void WfcSimpleStartInit_HandleResult() {
    if (WfcButtonBar_GetResult()) return;
    WfcSound_Stop();
    WfcSound_Play(7);
    WfcUtil_SetScene(WfcSimpleStartInit_StartExit);
}

extern "C" void WfcSimpleStartInit_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcSimpleStartInit_FadeOut);
}

extern "C" void WfcSimpleStartInit_FadeOut() {
    if (WfcFade_IsBusy(1)) return;
    if (sWfcSimpleStartInitReady == 0) {
        WfcButtonBar_Close();
    }
    if (sWfcSimpleStartInitReady == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x14, 8);
    WfcUtil_SetScene(WfcSimpleStartInit_Exit);
}

extern "C" void WfcSimpleStartInit_Exit() {
    if (WfcFade_IsBusy(0)) return;
    if (sWfcSimpleStartInitReady == 0) {
        if (WfcFade_IsBusy(1)) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    if (sWfcSimpleStartInitReady == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcSimpleStartInitReady == 0) {
        WfcSimpleStart_End();
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcSetupMethod_Enter);
        return;
    }
    WfcUtil_SetScreenFlags(0, 0);
    WfcUtil_SetScene(WfcSimpleStartWait_Enter);
}

extern "C" void WfcSimpleStartInit_CheckStatus() {
    switch (WfcSimpleStart_GetState()) {
    case 1:
        sWfcSimpleStartInitReady = 1;
        WfcUtil_SetScene(WfcSimpleStartInit_StartExit);
        break;
    case 4:
        sWfcSimpleStartInitReady = 0;
        WfcSound_Stop();
        WfcSound_Play(9);
        WfcDialog_Open(0x41, 1, 1, -1, 0);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcSimpleStartInit_FailDialog);
        break;
    }
}

extern "C" void WfcSimpleStartInit_FailDialog() {
    if (WfcDialog_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcSimpleStartInit_WaitDialogClosed);
}

extern "C" void WfcSimpleStartInit_WaitDialogClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcUtil_SetScene(WfcSimpleStartInit_StartExit);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02219064) {
    HOST_OVERLAY_VAR(sWfcSimpleStartInitReady),
    HOST_OVERLAY_VARS_END
};
