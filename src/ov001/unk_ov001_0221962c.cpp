#include "types.h"
#include "nitro/io_access.h"
#include "net/WfcApScanEntry.h"
#include "net/WfcConfigSlot.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02211b2c.h"
#include "proto/ov001/unk_ov001_0221962c.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221d744.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"

#pragma thumb off

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
u8 *WfcConfig_GetEdit();
void WfcConfig_BeginEdit(s32 idx);
}

extern "C" u8 sWfcApSearchResult = 0;
extern "C" volatile u16 sWfcApSearchTimer = 0;

#define REGSET(a, v) do { u32 t = IO_R((volatile u16 *)(a)); t &= ~3; t |= (v); IO_W((volatile u16 *)(a), t); } while (0)

extern "C" void WfcApSearch_Enter() {
    sWfcApSearchTimer = 0;
    sWfcApSearchResult = 0;
    WfcApSearch_LoadBg();
    WfcUtil_ShowTopMessage(0x7f, -1, 0);
    WfcHighlight_SetConnection();
    WfcUtil_ShowStepIndicator(2);
    WfcUtil_ShowBottomMessage(0x7f);
    WfcBusyIcon_Create(0);
    WfcApScan_Alloc();
    WfcApScan_Start();
    WfcSound_Play(10);
    WfcUtil_SetScene(WfcApSearch_FadeIn);
}

extern "C" void WfcApSearch_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jbBgStep3.ncg.l", (WfcLoadFunc)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep3.ncl.l", (WfcLoadFunc)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/xb4Multi.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
    REGSET(0x4001008, 3);
    REGSET(0x400100a, 3);
    REGSET(0x4000008, 3);
    REGSET(0x400000a, 3);
    REGSET(0x400000c, 3);
}

extern "C" void WfcApSearch_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcApSearch_WaitFadeIn);
}

extern "C" void WfcApSearch_WaitFadeIn() {
    if (WfcFade_IsBusy(1)) return;
    if (WfcFade_IsBusy(0)) return;
    WfcUtil_OpenButtonBar(1);
    WfcUtil_SetScene(WfcApSearch_WaitButtonBar);
}

extern "C" void WfcApSearch_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcApSearch_Update);
}

extern "C" void WfcApSearch_Update() {
    WfcApSearch_HandleInput();
    WfcApSearch_Idle();
    WfcApSearch_HandleResult();
    WfcApSearch_CheckResults();
}

extern "C" void WfcApSearch_CheckResults() {
    WfcApScanEntry *buf;
    s32 n, i;
    sWfcApSearchTimer = sWfcApSearchTimer + 1;
    if (sWfcApSearchTimer < 0x12c) return;
    WfcSound_Stop();
    n = WfcApScan_GetResults(&buf);
    if (n == 0) {
        sWfcApSearchResult = 2;
        WfcDialog_Open(0x43, 1, 1, -1, 0);
        WfcSound_Play(0x12);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcApSearch_ResultDialog);
        return;
    }
    for (i = 0; i < n; i++) {
        if (buf[i].security != 2) break;
    }
    if (i == n) {
        sWfcApSearchResult = 3;
        WfcDialog_Open(0x42, 1, 1, -1, 0);
        WfcSound_Play(0x12);
        WfcButtonBar_DisableInput();
        WfcUtil_SetScene(WfcApSearch_ResultDialog);
        return;
    }
    sWfcApSearchResult = 1;
    WfcSound_Play(0xf);
    WfcUtil_SetScene(WfcApSearch_StartExit);
}

extern "C" void WfcApSearch_HandleInput() {
    if (WfcInput_IsKeyPressed(2) == 0) return;
    WfcSound_Stop();
    WfcButtonBar_SetResult(0);
}

extern "C" void WfcApSearch_Idle() {}

extern "C" void WfcApSearch_HandleResult() {
    if (WfcButtonBar_GetResult()) return;
    WfcSound_Stop();
    WfcSound_Play(7);
    WfcUtil_SetScene(WfcApSearch_StartExit);
}

extern "C" void WfcApSearch_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcApSearch_FadeOut);
}

extern "C" void WfcApSearch_FadeOut() {
    if (WfcFade_IsBusy(1)) return;
    WfcButtonBar_Close();
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcApSearch_Exit);
}

extern "C" void WfcApSearch_Exit() {
    if (WfcFade_IsBusy(1)) return;
    if (WfcFade_IsBusy(0)) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    while (WfcApScan_Stop() == 0) {}
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    WfcUtil_HideTopMessage();
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcApSearchResult != 1) {
        WfcApScan_Free();
        WfcConfig_BeginEdit(((WfcConfigSlot *)WfcConfig_GetEdit())->editSlotIndex);
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcSetupMethod_Enter);
        return;
    }
    WfcUtil_SetScreenFlags(0, 1);
    WfcUtil_SetEditParams(0, 0);
    WfcUtil_SetScene(WfcApList_Enter);
}

extern "C" void WfcApSearch_ResultDialog() {
    if (WfcDialog_GetResult()) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcApSearch_WaitDialogClosed);
}

extern "C" void WfcApSearch_WaitDialogClosed() {
    if (WfcDialog_IsOpen()) return;
    WfcUtil_SetScene(WfcApSearch_StartExit);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221962c) {
    HOST_OVERLAY_VAR(sWfcApSearchResult),
    HOST_OVERLAY_VAR(sWfcApSearchTimer),
    HOST_OVERLAY_VARS_END
};
