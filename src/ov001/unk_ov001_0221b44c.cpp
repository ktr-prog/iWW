#include "types.h"
#include "net/WifiApConfig.h"
#include "net/WfcConfigSlot.h"
#include "nitro/io_access.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_02208a24.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0220d760.h"
#include "proto/ov001/unk_ov001_02214f50.h"
#include "proto/ov001/unk_ov001_022156e0.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221b44c.h"
#include "proto/ov001/unk_ov001_0221b8f4.h"
#include "proto/ov001/unk_ov001_0221bc10.h"
#include "proto/ov001/unk_ov001_0221bee0.h"
#include "proto/ov001/unk_ov001_0221d744.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221eb38.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02226f68.h"
#include "proto/ov065/unk_ov065_0226ad84.h"

#pragma thumb off

extern "C" const WifiApConfig sWfcConnTestParam;
extern "C" const WifiApConfig sWfcConnTestParam = {WfcConnTest_Alloc, WfcConnTest_Free, 3, 1, 0, 0};
extern "C" {
u8 sWfcConnTestSucceeded;
}

namespace F0221b794 {


extern "C" {

void GX_LoadBG2Char();
void GX_LoadBGPltt();
void GX_LoadBG2Scr();
void WfcUtil_LoadFileTo(void *, void *);



void WfcConnTest_Enter() {
    u32 x;
    sWfcConnTestSucceeded = 0;
    WfcConnTest_LoadBg();
    WfcUtil_GetEditParams(0, &x);
    if (x == 0) WfcUtil_ShowTopMessage(0x7d, -1, 0);
    WfcUtil_ShowStepIndicator(2);
    if (x == 0) WfcHighlight_SetConnection();
    WfcUtil_ShowBottomMessage(0x76);
    WfcBusyIcon_Create(0);
    WfcConnTest_Start();
    WfcLinkIcon_Create(0);
    WfcSound_Play(0xc);
    WfcUtil_SetScene(WfcConnTest_FadeIn);
}

void WfcConnTest_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jbBgStep3.ncg.l", (void *)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep3.ncl.l", (void *)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/xb4Multi.nsc.l", (void *)GX_LoadBG2Scr);
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

}
}

namespace F0221ae34 {


extern "C" {
extern u8 *WfcConfig_GetEdit();
extern WfcConfigData *WfcConfig_Get();
extern void *DWCi_BACKUPlGetWifi();
extern void MI_CpuCopy8(void *, void *, s32);


#define REGSET(a, v) do { u32 t = *(volatile u16 *)(a); t &= ~3; t |= (v); *(volatile u16 *)(a) = t; } while (0)


void WfcConnTest_Start() {
    u32 l;
    WifiApConfig m;
    u8 *o = WfcConfig_GetEdit();
    m = sWfcConnTestParam;
    WfcUtil_GetEditParams(0, &l);
    if (l == 2) m.apFilter = 4;
    else m.apFilter = o[0xf4] + 1;
    if (WifiAp_Init(&m) == 0) Fatal_Trap();
    if (l == 0) WifiAp_SetApEntry(o[0xf4], o);
    WfcTask_Add(0, (void *)WfcConnTest_PollTask, 0, 0x78);
}

void WfcConnTest_FadeIn() {
    u32 l;
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_GetEditParams(0, &l);
    if (l == 0) {
        WfcFade_Start(2, 1, 1, 8);
        WfcGx_ShowPlanes(1, 1);
    }
    WfcUtil_SetScene(WfcConnTest_WaitFadeIn);
}

void WfcConnTest_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_SetScene(WfcConnTest_Idle);
}

void WfcConnTest_Idle() {
    func_ov001_0221b60c();
    func_ov001_0221b608();
    func_ov001_0221b604();
}

void func_ov001_0221b60c() {
}

void func_ov001_0221b608() {
}

void func_ov001_0221b604() {
}

void WfcConnTest_FadeOut() {
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcConnTest_WaitFadeOut);
}

void WfcConnTest_WaitFadeOut() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_SetScene(WfcConnTest_Exit);
}

void WfcConnTest_Exit() {
    WfcConfigData *o = WfcConfig_Get();
    if (WifiAp_RequestCleanup() == 0) return;
    MI_CpuCopy8(DWCi_BACKUPlGetWifi(), o->slots[0].editSubnetMask, 0xe);
    MI_CpuCopy8(DWCi_BACKUPlGetWifi(), o->slots[1].editSubnetMask, 0xe);
    WfcBusyIcon_Delete();
    WfcText_DestroyBgCanvas(0);
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcConnTestSucceeded == 0) {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcError_Enter);
    } else {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcTestSuccess_Enter);
    }
}

void WfcConnTest_PollTask(void *task, void *work) {
    s32 r = WifiAp_Process();
    if (r == 0) return;
    WfcLinkIcon_Delete();
    WfcSound_Stop();
    if (r > 0) {
        sWfcConnTestSucceeded = 1;
        WfcSound_Play(0x11);
    } else {
        WfcError_SetCode(WifiAp_GetStatus());
        WfcSound_Play(0x12);
    }
    WfcUtil_SetScene(WfcConnTest_FadeOut);
    WfcTask_RequestDelete(0, task);
}

void *WfcConnTest_Alloc(u32 name, u32 size) {
    return WfcHeap_Alloc(size, 0x20);
}

void WfcConnTest_Free(u32 name, void *p, u32 size) {
    WfcHeap_Free(p);
}

}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221b44c) {
    HOST_OVERLAY_VAR(sWfcConnTestSucceeded),
    HOST_OVERLAY_VARS_END
};
