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
#include "proto/ov001/unk_ov001_02218dc8.h"
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
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
}

extern "C" u8 sWfcSimpleStartRecvDone = 0;

extern "C" BOOL WfcSimpleStartRecv_IsLidClosed() {
    s32 t = (s32)(*HW_SYSWORK(volatile u16, buttonXY) & 0x8000) >> 15;
    if (t != 0) return TRUE;
    return FALSE;
}

extern "C" void WfcSimpleStartRecv_Enter() {
    sWfcSimpleStartRecvDone = 0;
    WfcSimpleStartRecv_LoadBg();
    WfcHighlight_SetConnection();
    WfcUtil_ShowBottomMessage(0x71);
    WfcBusyIcon_Create(2);
    WfcUtil_SetScene(WfcSimpleStartRecv_FadeIn);
}

extern "C" void WfcSimpleStartRecv_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/xb4Multi.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
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

extern "C" void WfcSimpleStartRecv_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcSimpleStartRecv_WaitFadeIn);
}

extern "C" void WfcSimpleStartRecv_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(1);
    WfcUtil_SetScene(WfcSimpleStartRecv_WaitButtonBar);
}

extern "C" void WfcSimpleStartRecv_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcSimpleStartRecv_Update);
}

extern "C" void WfcSimpleStartRecv_Update() {
    OS_Sleep(10);
    WfcSimpleStartRecv_CheckStatus();
    WfcSimpleStartRecv_HandleInput();
    WfcSimpleStartRecv_Idle();
    WfcSimpleStartRecv_HandleResult();
}

extern "C" void WfcSimpleStartRecv_HandleInput() {
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcSimpleStartRecv_IsLidClosed() == 0) return;
    WfcButtonBar_SetResult(0);
}

extern "C" void WfcSimpleStartRecv_Idle() {
}

extern "C" void WfcSimpleStartRecv_HandleResult() {
    if (WfcButtonBar_GetResult() != 0) return;
    WfcSound_Stop();
    WfcSound_Play(7);
    WfcUtil_SetScene(WfcSimpleStartRecv_StartExit);
}

extern "C" void WfcSimpleStartRecv_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcSimpleStartRecv_FadeOut);
}

extern "C" void WfcSimpleStartRecv_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    if (sWfcSimpleStartRecvDone == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcSimpleStartRecv_Exit);
}

extern "C" void WfcSimpleStartRecv_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (sWfcSimpleStartRecvDone == 0) {
        if (WfcFade_IsBusy(1) != 0) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    if (sWfcSimpleStartRecvDone == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcSimpleStart_End();
    if (sWfcSimpleStartRecvDone == 0) {
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcSetupMethod_Enter);
    } else {
        WfcUtil_SetScreenFlags(0, 0);
        WfcUtil_SetScene(WfcSimpleStartDone_Enter);
    }
}

extern "C" void WfcSimpleStartRecv_CheckStatus() {
    switch (WfcSimpleStart_GetState()) {
    case 3:
        sWfcSimpleStartRecvDone = 1;
        WfcSound_Stop();
        WfcSimpleStart_ApplyResult();
        WfcUtil_SetScene(WfcSimpleStartRecv_StartExit);
        break;
    case 4:
        sWfcSimpleStartRecvDone = 0;
        WfcSound_Stop();
        WfcSound_Play(9);
        WfcDialog_Open(0x41, 1, 1, -1, 0);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcSimpleStartRecv_FailDialog);
        break;
    case 5:
        sWfcSimpleStartRecvDone = 0;
        WfcSound_Stop();
        WfcSound_Play(0x12);
        WfcDialog_Open(0x42, 1, 1, -1, 0);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcSimpleStartRecv_FailDialog);
        break;
    }
}

extern "C" void WfcSimpleStartRecv_FailDialog() {
    if (WfcDialog_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcSimpleStartRecv_WaitDialogClosed);
}

extern "C" void WfcSimpleStartRecv_WaitDialogClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcUtil_SetScene(WfcSimpleStartRecv_StartExit);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02218844) {
    HOST_OVERLAY_VAR(sWfcSimpleStartRecvDone),
    HOST_OVERLAY_VARS_END
};
