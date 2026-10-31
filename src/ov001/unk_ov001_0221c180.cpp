#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221c180.h"
#include "proto/ov001/unk_ov001_0221c5fc.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

extern "C" {
void GX_LoadBG2Scr();
void GX_LoadBG2Char();
void GX_LoadBGPltt();
void WfcUtil_LoadFileTo(void *, void *);
s32 WfcInput_IsKeyPressed(s32);

}

extern "C" u8 sWfcUsbIntroOk = 0;

extern "C" void WfcUsbIntro_Enter() {
    sWfcUsbIntroOk = 0;
    WfcUsbIntro_LoadBg();
    WfcHighlight_Set(8);
    WfcUtil_ShowTopMessage(0x85, -1, 0);
    WfcUtil_ShowStepIndicator(1);
    WfcUtil_ShowBottomMessage(0x6c);
    WfcUtil_SetScene(WfcUsbIntro_FadeIn);
}

extern "C" void WfcUsbIntro_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jbBgStep2.ncg.l", (void *)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep2.ncl.l", (void *)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/xb3Multi.nsc.l", (void *)GX_LoadBG2Scr);
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

extern "C" void WfcUsbIntro_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcUsbIntro_WaitFadeIn);
}

extern "C" void WfcUsbIntro_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(6);
    WfcUtil_SetScene(WfcUsbIntro_WaitButtonBar);
}

extern "C" void WfcUsbIntro_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcUsbIntro_Update);
}

extern "C" void WfcUsbIntro_Update() {
    WfcUsbIntro_HandleInput();
    WfcUsbIntro_Idle();
    WfcUsbIntro_HandleResult();
}

extern "C" void WfcUsbIntro_HandleInput() {
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(1);
    }
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
    }
}

extern "C" void WfcUsbIntro_Idle() {
}

extern "C" void WfcUsbIntro_HandleResult() {
    switch (WfcButtonBar_GetResult()) {
    case 0:
        WfcSound_Play(7);
        break;
    case 1:
        WfcSound_Play(6);
        sWfcUsbIntroOk = 1;
        break;
    default:
        return;
    }
    WfcUtil_SetScene(WfcUsbIntro_StartExit);
}

extern "C" void WfcUsbIntro_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcUsbIntro_FadeOut);
}

extern "C" void WfcUsbIntro_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    if (sWfcUsbIntroOk == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcUsbIntro_Exit);
}

extern "C" void WfcUsbIntro_Exit() {
    if (WfcFade_IsBusy(0) != 0) return;
    if (sWfcUsbIntroOk == 0) {
        if (WfcFade_IsBusy(1) != 0) return;
    }
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcText_DestroyBgCanvas(0);
    if (sWfcUsbIntroOk == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcUsbIntroOk == 0) {
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcConnSelect_Enter);
    } else {
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcUsbWait_Enter);
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221c180) {
    HOST_OVERLAY_VAR(sWfcUsbIntroOk),
    HOST_OVERLAY_VARS_END
};
