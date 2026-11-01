#include "types.h"
#include "host_tick.h"
#include "host_mem.h"
#include "nitro/io_access.h"
#include "net/WfcLoadFunc.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c37c.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02210cc0.h"
#include "proto/ov001/unk_ov001_022111c8.h"
#include "proto/ov001/unk_ov001_022118a8.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221bc10.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

extern "C" {
volatile u8 sWfcAossSetupSucceeded;
volatile u16 sWfcAossSetupTimer;
void *sWfcAossSetupUiTask;
}

extern "C" {


BOOL WfcAossSetup_IsLidClosed() {
    s32 t = (s32)(*HW_SYSWORK(volatile u16, buttonXY) & 0x8000) >> 15;
    if (t != 0) return TRUE;
    return FALSE;
}

void WfcAossSetup_Enter() {
    sWfcAossSetupTimer = 0;
    WfcAossSetup_LoadBg();
    WfcHighlight_SetConnection();
    WfcUtil_ShowTopMessage(0x82, -1, 0);
    WfcUtil_ShowStepIndicator(2);
    WfcUtil_ShowBottomMessage(0x67);
    WfcBusyIcon_Create(0);
    WfcAoss_Begin();
    WfcSound_Play(0xb);
    WfcUtil_SetScene(WfcAossSetup_FadeIn);
}

void WfcAossSetup_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jbBgStep3.ncg.l", GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep3.ncl.l", GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/xb4Multi.nsc.l", GX_LoadBG2Scr);
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

void WfcAossSetup_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcAossSetup_WaitFadeIn);
}

void WfcAossSetup_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(1);
    WfcUtil_SetScene(WfcAossSetup_StartAoss);
}

void WfcAossSetup_StartAoss() {
    if (WfcButtonBar_GetResult() == -2) return;
    sWfcAossSetupUiTask = WfcTask_Add(1, (void *)WfcAossSetup_UiTask, 0, 0x78);
    WfcUtil_SetScene(WfcAossSetup_RunAoss);
}

void WfcAossSetup_RunAoss() {
    WfcAossSetup_HandleInput();
    WfcAossSetup_Idle();
    WfcAossSetup_HandleResult();
    s32 r = WfcAoss_Run();
    switch (r) {
    case 0: return;
    case 1: {
        void *t = sWfcAossSetupUiTask;
        sWfcAossSetupSucceeded = 1;
        WfcTask_Delete(1, t);
        sWfcAossSetupUiTask = 0;
        WfcUtil_SetScene(WfcAossSetup_WaitAfterSuccess);
        break;
    }
    case 2: {
        WfcSound_Stop();
        WfcDialog_Open(0x40, 1, 1, -1, 0);
        WfcSound_Play(9);
        WfcButtonBar_DisableInput();
        WfcTask_Delete(1, sWfcAossSetupUiTask);
        sWfcAossSetupUiTask = 0;
        WfcUtil_SetScene(WfcAossSetup_WaitErrorDialog);
        break;
    }
    }
}

void WfcAossSetup_HandleInput() {
    if (WfcInput_IsKeyHeld(2) != 0) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcAossSetup_IsLidClosed() == 0) return;
    WfcButtonBar_SetResult(0);
}

void WfcAossSetup_Idle() {
}

void WfcAossSetup_HandleResult() {
    if (WfcButtonBar_GetResult() != 0) return;
    WfcButtonBar_DisableInput();
    WfcUtil_SetScene(WfcAossSetup_Cancel);
}

void WfcAossSetup_StartExit() {
    WfcButtonBar_DisableInput();
    if (sWfcAossSetupUiTask != 0) {
        WfcTask_Delete(1, sWfcAossSetupUiTask);
    }
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcAossSetup_FadeOut);
}

void WfcAossSetup_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    if (sWfcAossSetupSucceeded == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcAossSetup_Exit);
}

void WfcAossSetup_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (sWfcAossSetupSucceeded == 0) {
        if (WfcFade_IsBusy(1) != 0) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcAoss_End(sWfcAossSetupSucceeded != 0 ? 1 : 0);
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    if (sWfcAossSetupSucceeded == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcAossSetupSucceeded == 0) {
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcSetupMethod_Enter);
        return;
    }
    WfcUtil_SetScreenFlags(0, 0);
    WfcUtil_SetScene(WfcAossDone_Enter);
}

void WfcAossSetup_UiTask() {
    WfcInput_Update();
    WfcTask_RunList(0);
    WfcAossSetup_HandleInput();
    WfcAossSetup_HandleResult();
}

void WfcAossSetup_WaitErrorDialog() {
    if (WfcDialog_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcAossSetup_WaitDialogClosed);
}

void WfcAossSetup_WaitDialogClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcUtil_SetScene(WfcAossSetup_StartExit);
}

void WfcAossSetup_WaitAfterSuccess() {
    WfcAossSetup_HandleInput();
    WfcAossSetup_Idle();
    WfcAossSetup_HandleResult();
    sWfcAossSetupTimer = sWfcAossSetupTimer + (TICK_STEP_ENDS() ? 1 : 0);
    if (sWfcAossSetupTimer < 0x438) return;
    WfcSound_Stop();
    WfcUtil_SetScene(WfcAossSetup_StartExit);
}

void WfcAossSetup_Cancel() {
    WfcSound_Stop();
    WfcSound_Play(7);
    sWfcAossSetupSucceeded = 0;
    WfcUtil_SetScene(WfcAossSetup_StartExit);
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_022111c8) {
    HOST_OVERLAY_VAR(sWfcAossSetupSucceeded),
    HOST_OVERLAY_VAR(sWfcAossSetupTimer),
    HOST_OVERLAY_VAR(sWfcAossSetupUiTask),
    HOST_OVERLAY_VARS_END
};
