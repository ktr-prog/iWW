#include "types.h"
#include "host_mem.h"
#include "nitro/os_rtc.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_02115468.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221bee0.h"
#include "proto/ov001/unk_ov001_0221c180.h"
#include "proto/ov001/unk_ov001_0221c5fc.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221f6a0.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"

#pragma thumb off


typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
void MIi_CpuClear16(u16 v, void *dst, u32 n);
void MIi_CpuCopy16(const void *src, void *dst, u32 size);
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
}

extern "C" u8 sWfcUsbWaitResult = 0;

extern "C" s32 WfcUsbWait_IsLidClosed() {
    s32 t = *HW_SYSWORK(u16, buttonXY) & 0x8000;
    return (t >> 15) ? TRUE : FALSE;
}

extern "C" void WfcUsbWait_Enter() {
    volatile u16 z;
    u16 b[0xb];
    OSOwnerInfo s;
    sWfcUsbWaitResult = 0;
    WfcUsbWait_LoadBg();
    WfcHighlight_Set(8);
    WfcUtil_ShowStepIndicator(2);
    OS_GetOwnerInfo(&s);
    z = 0;
    MIi_CpuClear16(z, b, 0x16);
    MIi_CpuCopy16(s.nickName, b, s.nickNameLength << 1);
    WfcUtil_ShowBottomMessageNum(b, 0x6d);
    WfcBusyIcon_Create(0);
    WfcUsbScan_Start(WfcUsbWait_OnScanResult);
    WfcSound_Play(0xb);
    WfcUtil_SetScene(WfcUsbWait_FadeIn);
}

extern "C" void WfcUsbWait_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jbBgStep3.ncg.l", (WfcLoadFunc)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep3.ncl.l", (WfcLoadFunc)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/jb4Usb.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
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

extern "C" void WfcUsbWait_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcUsbWait_WaitFadeIn);
}

extern "C" void WfcUsbWait_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(2);
    WfcUtil_SetScene(WfcUsbWait_WaitButtonBar);
}

extern "C" void WfcUsbWait_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcUsbWait_Update);
}

extern "C" void WfcUsbWait_Update() {
    WfcUsbWait_HandleInput();
    WfcUsbWait_Idle();
    WfcUsbWait_HandleResult();
}

extern "C" void WfcUsbWait_HandleInput() {
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcUsbWait_IsLidClosed() == 0) return;
    WfcButtonBar_SetResult(0);
}

extern "C" void WfcUsbWait_Idle() {}

extern "C" void WfcUsbWait_HandleResult() {
    if (sWfcUsbWaitResult != 0) return;
    if (WfcButtonBar_GetResult() != 0) return;
    sWfcUsbWaitResult = 2;
    WfcSound_Stop();
    WfcSound_Play(7);
    WfcUtil_SetScene(WfcUsbWait_StartExit);
}

extern "C" void WfcUsbWait_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcUsbWait_FadeOut);
}

extern "C" void WfcUsbWait_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    if ((u8)(sWfcUsbWaitResult + 0xfe) <= 1) WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcUsbWait_Exit);
}

extern "C" void WfcUsbWait_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (sWfcUsbWaitResult == 2) {
        if (WfcFade_IsBusy(1) != 0) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcUsbScan_Stop();
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    if ((u8)(sWfcUsbWaitResult + 0xfe) <= 1) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcUsbWaitResult == 2) {
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcConnSelect_Enter);
    } else if (sWfcUsbWaitResult == 3) {
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcUsbIntro_Enter);
    } else {
        WfcUtil_SetScreenFlags(0, 0);
        WfcUtil_SetScene(WfcUsbDone_Enter);
    }
}

extern "C" void WfcUsbWait_OnScanResult(s32 a) {
    if (sWfcUsbWaitResult != 0) return;
    switch (a) {
    case 0:
        sWfcUsbWaitResult = 3;
        WfcSound_Stop();
        WfcSound_Play(0x12);
        WfcDialog_Open(0x45, 1, 1, -1, 0);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcUsbWait_NotFoundDialog);
        break;
    case 1:
        sWfcUsbWaitResult = 1;
        WfcSound_Stop();
        WfcUtil_SetScene(WfcUsbWait_StartExit);
        break;
    case 2:
        WfcSound_Stop();
        WfcUsbScan_SetCallback(0);
        WfcDialog_Open(0x47, 0, 1, -1, 0);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcUsbWait_GrantedDialog);
        break;
    case 3:
        sWfcUsbWaitResult = 2;
        WfcSound_Stop();
        WfcSound_Play(9);
        WfcUtil_SetScene(WfcUsbWait_StartExit);
        break;
    }
}

extern "C" void WfcUsbWait_NotFoundDialog() {
    if (WfcDialog_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcUsbWait_WaitNotFoundClosed);
}

extern "C" void WfcUsbWait_WaitNotFoundClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcUtil_SetScene(WfcUsbWait_StartExit);
}

extern "C" void WfcUsbWait_GrantedDialog() {
    s32 r = WfcDialog_GetResult();
    if (r != 0) {
        if (r != 1) return;
        sWfcUsbWaitResult = 3;
        WfcSound_Play(6);
    } else {
        sWfcUsbWaitResult = 1;
        WfcSound_Play(7);
    }
    WfcDialog_Close();
    WfcUtil_SetScene(WfcUsbWait_WaitGrantedClosed);
}

extern "C" void WfcUsbWait_WaitGrantedClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    if (sWfcUsbWaitResult == 1) {
        WfcUtil_SetScene(WfcUsbWait_StartExit);
        return;
    }
    WfcSound_Play(0xb);
    WfcButtonBar_EnableInput();
    sWfcUsbWaitResult = 0;
    WfcUsbScan_SetCallback(WfcUsbWait_OnScanResult);
    WfcUtil_SetScene(WfcUsbWait_Update);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221c5fc) {
    HOST_OVERLAY_VAR(sWfcUsbWaitResult),
    HOST_OVERLAY_VARS_END
};
