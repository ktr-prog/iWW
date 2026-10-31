#include "types.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
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
#include "proto/ov001/unk_ov001_02225924.h"

extern "C" {
extern u8 GX_LoadBG2Scr[];
void OS_SpinWait(u32 a);
u32 PM_ForceToPowerOff();
void WfcUtil_LoadFileTo(void *a, void *b);
void WfcTransfer_SetCallback(void (*f)(u32));
void WfcConfig_EraseAll();
s32 WfcInput_IsKeyPressed(u32 a);

u8 sWfcTransferSendResult;

#pragma thumb off

#define BGCNT_SET(a) *(volatile u16 *)(a) = (*(volatile u16 *)(a) & ~3) | 3

static inline void Unk_ov001_0220f62c_Bg() {
    BGCNT_SET(0x4001008);
    BGCNT_SET(0x400100a);
    BGCNT_SET(0x4000008);
    BGCNT_SET(0x400000a);
    BGCNT_SET(0x400000c);
}

void WfcTransferDone_Enter() {
    WfcTransferDone_SetupBg();
    WfcUtil_ShowBottomMessage(0x61);
    WfcUtil_SetScene(WfcTransferDone_FadeIn);
}

void WfcTransferDone_SetupBg() {
    BGCNT_SET(0x4001008);
    BGCNT_SET(0x400100a);
    BGCNT_SET(0x4000008);
    BGCNT_SET(0x400000a);
    BGCNT_SET(0x400000c);
}

void WfcTransferDone_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTransferDone_WaitFadeIn);
}

void WfcTransferDone_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(5);
    WfcUtil_SetScene(WfcTransferDone_WaitButtonBar);
}

void WfcTransferDone_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcTransferDone_Update);
}

void WfcTransferDone_Update() {
    WfcTransferDone_HandleInput();
    WfcTransferDone_Idle();
    WfcTransferDone_HandleResult();
}

void WfcTransferDone_HandleInput() {
    if (WfcInput_IsKeyPressed(1) == 0) return;
    WfcButtonBar_SetResult(0);
}

void WfcTransferDone_Idle() {}

void WfcTransferDone_HandleResult() {
    if (WfcButtonBar_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcUtil_SetScene(WfcTransferDone_StartExit);
}

void WfcTransferDone_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcTransferDone_FadeOut);
}

void WfcTransferDone_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcFade_Start(3, 1, 0x3f, 0x40);
    WfcFade_Start(3, 0, 0x3f, 0x40);
    WfcUtil_SetScene(WfcTransferDone_PowerOff);
}

void WfcTransferDone_PowerOff() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    OS_SpinWait(0x1000000);
    PM_ForceToPowerOff();
}

void WfcTransferSend_Enter() {
    WfcTransferSend_LoadBg();
    WfcUtil_ShowBottomMessage(0x60);
    WfcBusyIcon_Create(0);
    WfcLinkIcon_Create(1);
    WfcSound_Play(0xb);
    WfcUtil_SetScene(WfcTransferSend_FadeIn);
}

void WfcTransferSend_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/yb5Multi.nsc.l", GX_LoadBG2Scr);
    Unk_ov001_0220f62c_Bg();
}

void WfcTransferSend_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTransferSend_WaitFadeIn);
}

void WfcTransferSend_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcTransfer_SetCallback(WfcTransferSend_OnResult);
    WfcUtil_SetScene(WfcTransferSend_Update);
}

void WfcTransferSend_Update() {
    WfcTransferSend_Nop1();
    WfcTransferSend_Nop2();
}

void WfcTransferSend_Nop1() {}

void WfcTransferSend_Nop2() {}

void WfcTransferSend_FadeOut() {
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcTransferSend_Exit);
}

void WfcTransferSend_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcTransfer_IsFinished() == 0) return;
    WfcLinkIcon_Delete();
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_SetScreenFlags(0, 1);
    if (sWfcTransferSendResult == 0) {
        WfcUtil_SetScene(WfcTransferFailed_Enter);
    } else if (sWfcTransferSendResult == 2) {
        WfcUtil_SetScene(WfcTransferCancelled_Enter);
    } else {
        WfcUtil_SetScene(WfcTransferDone_Enter);
    }
}

void WfcTransferSend_OnResult(u32 a) {
    if (a == 2) {
        WfcConfig_EraseAll();
        sWfcTransferSendResult = 1;
        WfcSound_Stop();
        WfcSound_Play(0x10);
    } else if (a == 3) {
        sWfcTransferSendResult = 2;
        WfcSound_Stop();
        WfcSound_Play(0x12);
    } else {
        sWfcTransferSendResult = 0;
        WfcSound_Stop();
        WfcSound_Play(0x12);
    }
    WfcTransfer_SetCallback(0);
    WfcTransfer_RequestEnd();
    WfcUtil_SetScene(WfcTransferSend_FadeOut);
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220f3fc) {
    HOST_OVERLAY_VAR(sWfcTransferSendResult),
    HOST_OVERLAY_VARS_END
};
