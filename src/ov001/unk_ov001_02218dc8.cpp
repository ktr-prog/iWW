#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02218dc8.h"
#include "proto/ov001/unk_ov001_0221bc10.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"

#pragma thumb off

extern "C" {
s32 GX_LoadBG2Scr();
s32 WfcGx_HidePlanes(s32, s32);
s32 WfcGx_ShowPlanes(s32, s32);
void WfcUtil_LoadFileTo(void *, void *);
}

extern "C" u8 sWfcSimpleStartDoneTimer = 0;

extern "C" void WfcSimpleStartDone_Enter() {
    sWfcSimpleStartDoneTimer = 0;
    WfcSimpleStartDone_LoadBg();
    WfcHighlight_SetConnection();
    WfcUtil_ShowBottomMessage(0x6b);
    WfcSound_Play(0x10);
    WfcUtil_SetScene(WfcSimpleStartDone_FadeIn);
}

extern "C" void WfcSimpleStartDone_LoadBg() {
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

extern "C" void WfcSimpleStartDone_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcSimpleStartDone_WaitFadeIn);
}

extern "C" void WfcSimpleStartDone_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_SetScene(WfcSimpleStartDone_Update);
}

extern "C" void WfcSimpleStartDone_Update() {
    WfcSimpleStartDone_CountDown();
    WfcSimpleStartDone_Idle();
}

extern "C" void WfcSimpleStartDone_Idle() {
}

extern "C" void WfcSimpleStartDone_FadeOut() {
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcSimpleStartDone_Exit);
}

extern "C" void WfcSimpleStartDone_Exit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcText_DestroyBgCanvas(0);
    WfcUtil_HideTopMessage();
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_SetScreenFlags(0, 0);
    WfcUtil_SetEditParams(0, 1);
    WfcUtil_SetScene(WfcTestConfirm_Enter);
}

extern "C" void WfcSimpleStartDone_CountDown() {
    sWfcSimpleStartDoneTimer++;
    if (sWfcSimpleStartDoneTimer < 0x78) return;
    WfcUtil_SetScene(WfcSimpleStartDone_FadeOut);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02218dc8) {
    HOST_OVERLAY_VAR(sWfcSimpleStartDoneTimer),
    HOST_OVERLAY_VARS_END
};
