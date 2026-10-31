#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220de1c.h"
#include "proto/ov001/unk_ov001_0220e320.h"
#include "proto/ov001/unk_ov001_0220e61c.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

extern "C" {
s32 WfcInput_IsKeyPressed(s32);
void WfcUtil_LoadFileTo(void *, void *);
void GX_LoadBG2Scr();
void OS_SpinWait(u32);
void PM_ForceToPowerOff();
void WfcConfig_EraseAll();
void OS_GetMacAddress(void *);
void swprintf(void *, s32, void *, ...);
void DWCi_BM_GetWiFiInfo(u64 *);
}

extern "C" void WfcErased_Enter() {
    WfcErased_LoadBg();
    WfcUtil_ShowBottomMessage(0x57);
    WfcConfig_EraseAll();
    WfcUtil_SetScene(WfcErased_FadeIn);
}

extern "C" void WfcErased_LoadBg() {
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

extern "C" void WfcErased_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcErased_WaitFadeIn);
}

extern "C" void WfcErased_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(5);
    WfcUtil_SetScene(WfcErased_WaitButtonBar);
}

extern "C" void WfcErased_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcErased_Update);
}

extern "C" void WfcErased_Update() {
    WfcErased_HandleInput();
    WfcErased_Idle();
    WfcErased_HandleResult();
}

extern "C" void WfcErased_HandleInput() {
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(0);
    }
}

extern "C" void WfcErased_Idle() {}

extern "C" void WfcErased_HandleResult() {
    if (WfcButtonBar_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcUtil_SetScene(WfcErased_StartExit);
}

extern "C" void WfcErased_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcErased_FadeOut);
}

extern "C" void WfcErased_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcFade_Start(3, 1, 0x3f, 0x40);
    WfcFade_Start(3, 0, 0x3f, 0x40);
    WfcUtil_SetScene(WfcErased_PowerOff);
}

extern "C" void WfcErased_PowerOff() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    OS_SpinWait(0x1000000);
    PM_ForceToPowerOff();
}

