#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0221b44c.h"
#include "proto/ov001/unk_ov001_0221bc10.h"
#include "proto/ov001/unk_ov001_0221d744.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

extern "C" {
void GX_LoadBG2Scr();
void WfcUtil_LoadFileTo(void *, void *);
void WfcConfig_CommitEdit();

}

struct WfcTestConfirmMessagesCopy { s32 v[3]; };

extern "C" s32 sWfcTestConfirmMessages[3] = {0x75, 0x75, 0x9d};

extern "C" void WfcTestConfirm_Enter() {
    u32 x;
    WfcApScan_Free();
    WfcUtil_GetEditParams(0, &x);
    WfcTestConfirm_LoadBg();
    WfcUtil_ShowTopMessage(0x7d, -1, 0);
    if (x != 2) WfcHighlight_SetConnection();
    if (x == 1) WfcConfig_CommitEdit();
    WfcUtil_SetScene(WfcTestConfirm_FadeIn);
}

extern "C" void WfcTestConfirm_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/xb4None.nsc.l", (void *)GX_LoadBG2Scr);
    volatile u16 *r1 = (volatile u16 *)0x4001008;
    volatile u16 *r2 = (volatile u16 *)0x400100a;
    volatile u16 *r3 = (volatile u16 *)0x400000a;
    volatile u16 *r4 = (volatile u16 *)0x400000c;
    IO_W(r1, (IO_R(r1) & ~3) | 3);
    IO_W(r2, (IO_R(r2) & ~3) | 3);
    IO_W(r3, (IO_R(r3) & ~3) | 3);
    IO_W(r4, (IO_R(r4) & ~3) | 3);
}

extern "C" void WfcTestConfirm_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x14, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x14);
    WfcUtil_SetScene(WfcTestConfirm_ShowDialog);
}

extern "C" void WfcTestConfirm_ShowDialog() {
    u32 x;
    WfcTestConfirmMessagesCopy a = *(WfcTestConfirmMessagesCopy *)sWfcTestConfirmMessages;
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_GetEditParams(0, &x);
    WfcDialog_Open(a.v[x], 1, 1, -1, 0);
    WfcUtil_SetScene(WfcTestConfirm_WaitDialog);
}

extern "C" void WfcTestConfirm_WaitDialog() {
    func_ov001_0221bcac();
    func_ov001_0221bca8();
    if (WfcDialog_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcSound_Play(6);
    WfcUtil_SetScene(WfcTestConfirm_FadeOut);
}

extern "C" void func_ov001_0221bcac() {
}

extern "C" void func_ov001_0221bca8() {
}

extern "C" void WfcTestConfirm_FadeOut() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcFade_Start(3, 0, 0x14, 8);
    WfcUtil_SetScene(WfcTestConfirm_Exit);
}

extern "C" void WfcTestConfirm_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcGx_HidePlanes(0, 0x14);
    WfcUtil_SetScreenFlags(0, 1);
    WfcUtil_SetScene(WfcConnTest_Enter);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221bc10) {
    HOST_OVERLAY_VAR(sWfcTestConfirmMessages),
    HOST_OVERLAY_VARS_END
};
