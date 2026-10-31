#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_02208a24.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0220d760.h"
#include "proto/ov001/unk_ov001_022156e0.h"
#include "proto/ov001/unk_ov001_0221b44c.h"
#include "proto/ov001/unk_ov001_0221b8f4.h"
#include "proto/ov001/unk_ov001_0221bc10.h"
#include "proto/ov001/unk_ov001_0221bee0.h"
#include "proto/ov001/unk_ov001_0221d744.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221eb38.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

extern "C" {
u8 sWfcTestSuccessTimer;
}



extern "C" {
void GX_LoadBG2Scr();
void WfcUtil_LoadFileTo(void *, void *);
void WfcTestSuccess_Enter() {
    sWfcTestSuccessTimer = 0;
    WfcTestSuccess_LoadBg();
    WfcUtil_ShowBottomMessage(0x77);
    WfcUtil_SetScene(WfcTestSuccess_FadeIn);
}

void WfcTestSuccess_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/xb4Multi.nsc.l", (void *)GX_LoadBG2Scr);
    volatile u16 *r1 = (volatile u16 *)0x4001008;
    volatile u16 *r2 = (volatile u16 *)0x400100a;
    volatile u16 *r3 = (volatile u16 *)0x400000a;
    volatile u16 *r4 = (volatile u16 *)0x400000c;
    IO_W(r1, (IO_R(r1) & ~3) | 3);
    IO_W(r2, (IO_R(r2) & ~3) | 3);
    IO_W(r3, (IO_R(r3) & ~3) | 3);
    IO_W(r4, (IO_R(r4) & ~3) | 3);
}

void WfcTestSuccess_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTestSuccess_WaitFadeIn);
}

void WfcTestSuccess_WaitFadeIn() {
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_SetScene(WfcTestSuccess_Update);
}

void WfcTestSuccess_Update() {
    WfcTestSuccess_CountDown();
    WfcTestSuccess_Idle();
}

void WfcTestSuccess_Idle() {
}

void WfcTestSuccess_FadeOut() {
    u32 x;
    WfcUtil_GetEditParams(0, &x);
    if (x != 0) WfcHeader_StartSlideOut();
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcTestSuccess_Exit);
}

void WfcTestSuccess_Exit() {
    u32 x;
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcHeader_IsSlideOutDone() == 0) return;
    WfcText_DestroyBgCanvas(0);
    WfcUtil_HideTopMessage();
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_SetScreenFlags(2, 1);
    WfcUtil_GetEditParams(0, &x);
    if (x == 0) {
        WfcUtil_SetEditParams(0, 0);
        WfcUtil_SetScene(WfcManualSetup_Enter);
    } else {
        WfcUtil_SetScene(WfcTopMenu_Enter);
    }
}

void WfcTestSuccess_CountDown() {
    u32 x;
    s32 r;
    sWfcTestSuccessTimer++;
    if (sWfcTestSuccessTimer < 0xb4) return;
    WfcUtil_GetEditParams(0, &x);
    r = WfcUtil_GetStartMode();
    switch (r) {
    case 0:
        break;
    case 1:
        if (x != 0) {
            WfcUtil_SetScene(WfcUtil_QuitFadeOut);
            return;
        }
        break;
    }
    WfcUtil_SetScene(WfcTestSuccess_FadeOut);
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221b8f4) {
    HOST_OVERLAY_VAR(sWfcTestSuccessTimer),
    HOST_OVERLAY_VARS_END
};
