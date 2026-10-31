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
#include "proto/ov001/unk_ov001_02218844.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"

#pragma thumb off

#define BGCNT(a, v) IO_W((volatile u16 *)(a), (IO_R((volatile u16 *)(a)) & ~3) | (v))

extern "C" {
u8 sWfcSimpleStartWaitNext;
}

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
void OS_Sleep(u32 msec);
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
}

extern "C" BOOL WfcSimpleStartWait_IsLidClosed() {
    s32 t = (s32)(*HW_SYSWORK(volatile u16, buttonXY) & 0x8000) >> 15;
    if (t != 0) return TRUE;
    return FALSE;
}

extern "C" void WfcSimpleStartWait_Enter() {
    sWfcSimpleStartWaitNext = 0;
    WfcSimpleStartWait_LoadBg();
    WfcHighlight_SetConnection();
    WfcUtil_ShowBottomMessage(0x6a);
    WfcBusyIcon_Create(1);
    WfcUtil_SetScene(WfcSimpleStartWait_FadeIn);
}

extern "C" void WfcSimpleStartWait_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/xb4Multi.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
    BGCNT(0x4001008, 3);
    BGCNT(0x400100a, 3);
    BGCNT(0x4000008, 3);
    BGCNT(0x400000a, 3);
    BGCNT(0x400000c, 3);
}

extern "C" void WfcSimpleStartWait_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcSimpleStartWait_WaitFadeIn);
}

extern "C" void WfcSimpleStartWait_WaitFadeIn() {
    if (WfcFade_IsBusy(0)) return;
    WfcUtil_OpenButtonBar(1);
    WfcUtil_SetScene(WfcSimpleStartWait_WaitButtonBar);
}

extern "C" void WfcSimpleStartWait_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcSimpleStartWait_Update);
}

extern "C" void WfcSimpleStartWait_Update() {
    OS_Sleep(10);
    WfcSimpleStartWait_CheckStatus();
    WfcSimpleStartWait_HandleInput();
    WfcSimpleStartWait_Idle();
    WfcSimpleStartWait_HandleResult();
}

extern "C" void WfcSimpleStartWait_HandleInput() {
    if (WfcInput_IsKeyPressed(2)) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcSimpleStartWait_IsLidClosed() == 0) return;
    WfcButtonBar_SetResult(0);
}

extern "C" void WfcSimpleStartWait_Idle() {}

extern "C" void WfcSimpleStartWait_HandleResult() {
    if (WfcButtonBar_GetResult()) return;
    WfcSound_Stop();
    WfcSound_Play(7);
    WfcUtil_SetScene(WfcSimpleStartWait_StartExit);
}

extern "C" void WfcSimpleStartWait_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcSimpleStartWait_FadeOut);
}

extern "C" void WfcSimpleStartWait_FadeOut() {
    if (WfcFade_IsBusy(1)) return;
    if (sWfcSimpleStartWaitNext == 0) {
        WfcButtonBar_Close();
    }
    if (sWfcSimpleStartWaitNext == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcSimpleStartWait_Exit);
}

extern "C" void WfcSimpleStartWait_Exit() {
    if (WfcFade_IsBusy(0)) return;
    if (sWfcSimpleStartWaitNext == 0) {
        if (WfcFade_IsBusy(1)) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    if (sWfcSimpleStartWaitNext == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcSimpleStartWaitNext == 0) {
        WfcSimpleStart_End();
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcSetupMethod_Enter);
        return;
    }
    WfcUtil_SetScreenFlags(0, 0);
    WfcUtil_SetScene(WfcSimpleStartRecv_Enter);
}

extern "C" void WfcSimpleStartWait_CheckStatus() {
    switch (WfcSimpleStart_GetState()) {
    case 2:
        sWfcSimpleStartWaitNext = 1;
        WfcUtil_SetScene(WfcSimpleStartWait_StartExit);
        break;
    case 4:
        sWfcSimpleStartWaitNext = 0;
        WfcSound_Stop();
        WfcSound_Play(9);
        WfcDialog_Open(0x41, 1, 1, -1, 0);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcSimpleStartWait_FailDialog);
        break;
    }
}

extern "C" void WfcSimpleStartWait_FailDialog() {
    if (WfcDialog_GetResult()) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcSimpleStartWait_WaitDialogClosed);
}

extern "C" void WfcSimpleStartWait_WaitDialogClosed() {
    if (WfcDialog_IsOpen()) return;
    WfcUtil_SetScene(WfcSimpleStartWait_StartExit);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02218300) {
    HOST_OVERLAY_VAR(sWfcSimpleStartWaitNext),
    HOST_OVERLAY_VARS_END
};
