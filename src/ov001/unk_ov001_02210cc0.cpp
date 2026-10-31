#include "types.h"
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
#include "proto/ov001/unk_ov001_0220cd24.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_0220f3fc.h"
#include "proto/ov001/unk_ov001_02210390.h"
#include "proto/ov001/unk_ov001_022107f0.h"
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
u8 sWfcTransferWaitResult;
}

extern "C" {


BOOL WfcTransferWait_IsLidClosed() {
    s32 t = (s32)(*HW_SYSWORK(volatile u16, buttonXY) & 0x8000) >> 15;
    if (t != 0) return TRUE;
    return FALSE;
}

void WfcTransferWait_Enter() {
    WfcTransfer_Start(WfcTransferWait_OnTransferEvent);
    sWfcTransferWaitResult = 0;
    WfcTransferWait_LoadBg();
    WfcUtil_ShowBottomMessage(0x5e);
    WfcBusyIcon_Create(0);
    WfcSound_Play(0xb);
    WfcUtil_SetScene(WfcTransferWait_FadeIn);
}

void WfcTransferWait_LoadBg() {
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

void WfcTransferWait_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTransferWait_WaitFadeIn);
}

void WfcTransferWait_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(1);
    WfcUtil_SetScene(WfcTransferWait_WaitButtonBar);
}


void WfcTransferWait_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcUtil_SetScene(WfcTransferWait_Update);
}

void WfcTransferWait_Update() {
    WfcTransferWait_HandleInput();
    WfcTransferWait_Idle();
    WfcTransferWait_HandleResult();
}

void WfcTransferWait_HandleInput() {
    if (WfcInput_IsKeyPressed(2)) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcTransferWait_IsLidClosed() == 0) return;
    WfcButtonBar_SetResult(0);
}

void WfcTransferWait_Idle() {
}

void WfcTransferWait_HandleResult() {
    if (WfcButtonBar_GetResult()) return;
    WfcSound_Stop();
    WfcSound_Play(7);
    WfcUtil_SetScene(WfcTransferWait_StartExit);
}

void WfcTransferWait_StartExit() {
    if (sWfcTransferWaitResult == 0) {
        WfcTransfer_RequestEnd();
    }
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcTransferWait_FadeOut);
}

void WfcTransferWait_FadeOut() {
    if (WfcFade_IsBusy(1)) return;
    if (sWfcTransferWaitResult == 0) {
        if (WfcTransfer_IsFinished() == 0) return;
    }
    WfcButtonBar_Close();
    if (sWfcTransferWaitResult == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcTransferWait_Exit);
}

void WfcTransferWait_Exit() {
    if (WfcFade_IsBusy(0)) return;
    if (sWfcTransferWaitResult == 0) {
        if (WfcFade_IsBusy(1)) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    if (sWfcTransferWaitResult == 0) {
        if (WfcTransfer_IsFinished() == 0) return;
    }
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    if (sWfcTransferWaitResult == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcTransferWaitResult == 0) {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcOptions_Enter);
    } else if (sWfcTransferWaitResult == 2) {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcTransferFailed_Enter);
    } else {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcTransferConfirm_Enter);
    }
}

void WfcTransferWait_OnTransferEvent(u32 a) {
    WfcSound_Stop();
    if (a == 0) {
        sWfcTransferWaitResult = 1;
        WfcSound_Play(0x10);
    } else {
        sWfcTransferWaitResult = 2;
        WfcSound_Play(0x12);
    }
    WfcTransfer_SetCallback(0);
    WfcUtil_SetScene(WfcTransferWait_StartExit);
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02210cc0) {
    HOST_OVERLAY_VAR(sWfcTransferWaitResult),
    HOST_OVERLAY_VARS_END
};
