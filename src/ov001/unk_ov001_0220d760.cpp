#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0220d760.h"
#include "proto/ov001/unk_ov001_0220e320.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221cd74.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221ea94.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"

#pragma thumb off

extern "C" const WfcRect data_ov001_02229f90[2] = {{0x08, 0x20, 0xac, 0xa0}, {0xb4, 0x20, 0xf8, 0xa0}};
extern "C" const WfcRect data_ov001_02229fa0[2] = {{0x0006, 0x001e, 0x009e, 0x0092}, {0x00b2, 0x001e, 0x00ea, 0x0092}};
extern "C" {
volatile u8 sWfcTopMenuSel;
void *sWfcTopMenuPalette;
}

typedef void (*WfcLoadFunc)(void *, s32, u32);
extern "C" {
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
}

#define WfcTopMenu_ShowCursor(i) \
    { const WfcRect *r = &data_ov001_02229fa0[i]; WfcCursor_ShowCorners(r->left, r->right, r->top, r->bottom); }

extern "C" void WfcTopMenu_Enter() {
    WfcTopMenu_LoadBg();
    WfcHighlight_Set(0);
    WfcUtil_ShowTopMessage(0x7a, -1, 0);
    WfcTop_LoadScreen(4);
    WfcTopMenu_ShowCursor(sWfcTopMenuSel)
    WfcUtil_SetScene(WfcTopMenu_FadeIn);
}

extern "C" void WfcTopMenu_LoadBg() {
    char l[22] = "char/ybBgStep11.ncl.l";
    WfcUtil_LoadFileTo((void *)"char/jbBgStep1.ncg.l", (WfcLoadFunc)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep1.ncl.l", (WfcLoadFunc)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/jb2Menu.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
    sWfcTopMenuPalette = WfcFs_LoadFile(WfcUtil_LocalizePath((u8 *)l), 0, 4);
    IO_W((volatile u16 *)0x4001008, (IO_R((volatile u16 *)0x4001008) & ~3) | 3);
    IO_W((volatile u16 *)0x400100a, (IO_R((volatile u16 *)0x400100a) & ~3) | 3);
    IO_W((volatile u16 *)0x400000a, (IO_R((volatile u16 *)0x400000a) & ~3) | 3);
    IO_W((volatile u16 *)0x400000c, (IO_R((volatile u16 *)0x400000c) & ~3) | 3);
}

extern "C" void WfcTopMenu_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x14, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x14);
    WfcUtil_SetScene(WfcTopMenu_WaitFadeIn);
}

extern "C" void WfcTopMenu_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(0);
    WfcUtil_SetScene(WfcTopMenu_WaitButtonBar);
}

extern "C" void WfcTopMenu_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcTopMenu_Update);
}

extern "C" void WfcTopMenu_Update() {
    WfcTopMenu_HandleInput();
    WfcTopMenu_Idle();
    WfcTopMenu_HandleResult();
}

extern "C" void WfcTopMenu_HandleInput() {
    u32 i = 0;
    do {
        if (WfcInput_IsTouchPressedIn((WfcRect *)&data_ov001_02229f90[i]) != 0) {
            WfcButtonBar_SetResult(1);
            sWfcTopMenuSel = i;
            WfcTopMenu_ShowCursor(sWfcTopMenuSel)
            return;
        }
        i++;
    } while (i < 2);
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(1);
        return;
    }
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x40) != 0) {
        WfcTopMenu_MoveCursor(1);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x80) != 0) {
        WfcTopMenu_MoveCursor(3);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x20) != 0) {
        WfcTopMenu_MoveCursor(0);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x10) == 0) return;
    WfcTopMenu_MoveCursor(2);
}

extern "C" void WfcTopMenu_Idle() {}

extern "C" void WfcTopMenu_HandleResult() {
    switch (WfcButtonBar_GetResult()) {
    case 0:
        WfcSound_Play(7);
        WfcUtil_SetScene(WfcUtil_QuitFadeOut);
        break;
    case 1:
        WfcSound_Play(6);
        WfcTopMenu_HighlightSelection();
        WfcUtil_SetScene(WfcTopMenu_StartExit);
        break;
    }
}

extern "C" void WfcTopMenu_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcTopMenu_FadeOut);
}

extern "C" void WfcTopMenu_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x14, 8);
    WfcUtil_SetScene(WfcTopMenu_Exit);
}

extern "C" void WfcTopMenu_Exit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcCursor_Clear();
    WfcUtil_HideTopMessage();
    WfcFs_FreeFile(sWfcTopMenuPalette);
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x14);
    switch (sWfcTopMenuSel) {
    case 0:
        WfcUtil_SetScreenFlags(1, 0);
        WfcUtil_SetScene(WfcConnSelect_Enter);
        break;
    case 1:
        WfcUtil_SetScreenFlags(0, 0);
        WfcUtil_SetScene(WfcOptions_Enter);
        break;
    }
}

extern "C" void WfcTopMenu_MoveCursor(s32 a) {
    if (a == 1) return;
    if (a == 3) return;
    sWfcTopMenuSel = sWfcTopMenuSel ^ 1;
    WfcSound_Play(8);
    WfcTopMenu_ShowCursor(sWfcTopMenuSel)
}

extern "C" void WfcTopMenu_HighlightSelection() {
    u8 t[2] = {1, 2};
    u32 v = t[sWfcTopMenuSel];
    WfcUtil_RequestPaletteLine(sWfcTopMenuPalette, v, v);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220d760) {
    HOST_OVERLAY_VAR(sWfcTopMenuSel),
    HOST_OVERLAY_VAR(sWfcTopMenuPalette),
    HOST_OVERLAY_VARS_END
};
