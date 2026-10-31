#include "types.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d760.h"
#include "proto/ov001/unk_ov001_0220de1c.h"
#include "proto/ov001/unk_ov001_0220e320.h"
#include "proto/ov001/unk_ov001_0220e61c.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_0220f9e4.h"
#include "proto/ov001/unk_ov001_0221cd74.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221ea94.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

extern "C" u16 data_ov001_0222acd8[30] = {'%', '0', '2', 'X', '-', '%', '0', '2', 'X', '-', '%', '0', '2', 'X', '-', '%', '0', '2', 'X', '-', '%', '0', '2', 'X', '-', '%', '0', '2', 'X', 0};
extern "C" u16 data_ov001_0222ad14[40] = {'%', '0', '4', 'd', '-', '%', '0', '4', 'd', '-', '%', '0', '4', 'd', '-', '%', '0', '4', 'd', 0, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 0};
#define data_ov001_0222ad3c (data_ov001_0222ad14 + 20)
extern "C" const u16 data_ov001_02229fb0[4] = {0x0008, 0x0040, 0x00f0, 0x001c};
extern "C" const u16 data_ov001_02229fb8[4] = {0x0008, 0x0078, 0x00f0, 0x001c};

struct WfcSysInfoStackPad {
    u32 v[3];
    WfcSysInfoStackPad() {}
    ~WfcSysInfoStackPad() {}
};

#define BGCNT(a) (*(volatile u16 *)(a) = (*(volatile u16 *)(a) & ~3) | 3)

extern "C" {
s32 WfcInput_IsKeyPressed(s32);
void WfcUtil_LoadFileTo(void *, void *);
void GX_LoadBG2Scr();
void OS_SpinWait(u32);
void PM_ForceToPowerOff();
void WfcConfig_EraseAll();
void OS_GetMacAddress(void *);
void swprintf(void *, s32, void *, ...);
void DWCi_BM_GetWiFiInfo(void *);
s32 FX_ModS32(s32, s32);
s32 WfcInput_IsTouchPressedIn(void *);
s32 WfcInput_IsKeyRepeat(s32);
void MI_CpuCopy8(void *, void *, s32);
void DC_FlushRange(void *, s32);
void GX_LoadBGPltt(void *, s32, s32);
}

extern "C" void WfcSysInfo_Enter() {
    WfcSysInfo_LoadBg();
    WfcHighlight_Set(0x11);
    WfcUtil_ShowTopMessage(0x89, -1, 0);
    WfcSysInfo_DrawInfo();
    WfcUtil_SetScene(WfcSysInfo_FadeIn);
}

extern "C" void WfcSysInfo_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jb5Info.nsc.l", (void *)GX_LoadBG2Scr);
    BGCNT(0x4001008);
    BGCNT(0x400100a);
    BGCNT(0x4000008);
    BGCNT(0x400000a);
    BGCNT(0x400000c);
}

extern "C" void WfcSysInfo_DrawInfo() {
    WfcTextCanvas *obj = WfcText_CreateBgCanvas(0, 0);
    u8 dt[8];
    u64 tick;
    WfcSysInfoStackPad pad;
    u32 d[4];
    u16 buf[0x16];
    OS_GetMacAddress(dt);
    swprintf(buf, 0x14, data_ov001_0222acd8, dt[0], dt[1], dt[2], dt[3], dt[4], dt[5]);
    WfcText_DrawTextRect(obj, data_ov001_02229fb0[0], data_ov001_02229fb0[1], data_ov001_02229fb0[2], data_ov001_02229fb0[3], 2, 0x480, buf);
    DWCi_BM_GetWiFiInfo(&tick);
    u64 t = tick;
    if (t != 0) {
        s32 i;
        d[3] = (u32)((t % 10) * 1000);
        t = t / 10;
        for (i = 0; i < 3; i++) {
            d[2 - i] = (u32)(t % 10000);
            t = t / 10000;
        }
        swprintf(buf, 0x14, data_ov001_0222ad14, d[0], d[1], d[2], d[3]);
    } else {
        swprintf(buf, 0x14, data_ov001_0222ad3c);
    }
    WfcText_DrawTextRect(obj, data_ov001_02229fb8[0], data_ov001_02229fb8[1], data_ov001_02229fb8[2], data_ov001_02229fb8[3], 2, 0x480, buf);
    WfcText_RequestTransfer(obj);
}

extern "C" void WfcSysInfo_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcSysInfo_WaitFadeIn);
}

extern "C" void WfcSysInfo_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(2);
    WfcUtil_SetScene(WfcSysInfo_WaitButtonBar);
}

extern "C" void WfcSysInfo_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcSysInfo_Update);
}

extern "C" void WfcSysInfo_Update() {
    WfcSysInfo_HandleInput();
    WfcSysInfo_Idle();
    WfcSysInfo_HandleResult();
}

extern "C" void WfcSysInfo_HandleInput() {
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
    }
}

extern "C" void WfcSysInfo_Idle() {}

extern "C" void WfcSysInfo_HandleResult() {
    if (WfcButtonBar_GetResult() != 0) return;
    WfcSound_Play(7);
    WfcUtil_SetScene(WfcSysInfo_StartExit);
}

extern "C" void WfcSysInfo_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcSysInfo_FadeOut);
}

extern "C" void WfcSysInfo_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcSysInfo_Exit);
}

extern "C" void WfcSysInfo_Exit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcText_DestroyBgCanvas(0);
    WfcUtil_HideTopMessage();
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_SetScreenFlags(0, 1);
    WfcUtil_SetScene(WfcOptions_Enter);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220e61c) {
    HOST_OVERLAY_VAR(data_ov001_0222acd8),
    HOST_OVERLAY_VAR(data_ov001_0222ad14),
    HOST_OVERLAY_VARS_END
};
