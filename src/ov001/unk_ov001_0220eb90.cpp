#include "types.h"
#include "nitro/gxoam.h"
#include "nitro/io_access.h"
#include "net/DwcWiFiInfo.h"
#include "net/WfcLoadFunc.h"
#include "net/WfcRect.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d760.h"
#include "proto/ov001/unk_ov001_0220de1c.h"
#include "proto/ov001/unk_ov001_0220e61c.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_0220f9e4.h"
#include "proto/ov001/unk_ov001_0221cd74.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221ea94.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"
#include "proto/ov001/unk_ov001_022266b0.h"

#pragma thumb off

extern "C" const WfcPoint data_ov001_02229fc4;
extern "C" const WfcRect data_ov001_02229fc8[3];
extern "C" const WfcRect data_ov001_02229fe0[3];
extern "C" const u8 data_ov001_02229fc0[3];

#define WfcOptions_ShowCursor(i) \
    { const WfcRect *r = &data_ov001_02229fe0[i]; WfcCursor_ShowCorners(r->left, r->right, r->top, r->bottom); }

extern "C" {
u8 sWfcOptionsChosen;
void *sWfcOptionsPalette;
u8 sWfcOptionsSel;
GXOamAttr *sWfcOptionsSprite;
}

#define BGCNT(a) IO_W((volatile u16 *)(a), (IO_R((volatile u16 *)(a)) & ~3) | 3)

extern "C" {
s32 FX_ModS32(s32 numer, s32 denom);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
void DC_FlushRange(const void *p, u32 size);
}

extern "C" void WfcOptions_Enter() {
    sWfcOptionsChosen = 0;
    WfcOptions_LoadBg();
    WfcHighlight_Set(0x10);
    WfcTop_LoadScreen(3);
    WfcUtil_ShowTopMessage(0x88, -1, 0);
    sWfcOptionsSprite = WfcObj_CreateSingle(0, 0x5b);
    sWfcOptionsSprite->attr01 = (sWfcOptionsSprite->attr01 & 0xfe00ff00) | (data_ov001_02229fc4.y & 0xff) | ((data_ov001_02229fc4.x & 0x1ff) << 16);
    sWfcOptionsSprite->attr2 = (sWfcOptionsSprite->attr2 & ~0xc00) | 0xc00;
    WfcOptions_ShowCursor(sWfcOptionsSel)
    WfcUtil_SetScene(WfcOptions_FadeIn);
}

extern "C" void WfcOptions_LoadBg() {
    u8 palettePath[0x16] = "char/ybBgOption.ncl.l";
    u8 palette1Path[0x17] = "char/ybBgOption1.ncl.l";
    DwcWiFiInfo info;
    u8 *d, *s;
    s32 i;
    u8 *e;
    WfcUtil_LoadFileTo((void *)"char/jbBgOption.ncg.l", GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/jb5OptMenu.nsc.l", GX_LoadBG2Scr);
    sWfcOptionsPalette = WfcFs_LoadFile(WfcUtil_LocalizePath(palette1Path), 0, 4);
    e = (u8 *)WfcFs_LoadFile(WfcUtil_LocalizePath(palettePath), 0, 4);
    DWCi_BM_GetWiFiInfo(&info);
    if (info.userId == 0) {
        d = e + 0xc0;
        s = e + 0x40;
        for (i = 0; i < 2; i++) {
            MI_CpuCopy8(d, s, 0x20);
            d += 0x20;
            s += 0x20;
        }
    }
    DC_FlushRange(e, 0x200);
    GX_LoadBGPltt(e, 0, 0x200);
    WfcFs_FreeFile(e);
    BGCNT(0x4001008);
    BGCNT(0x400100a);
    BGCNT(0x400000a);
    BGCNT(0x400000c);
}

extern "C" void WfcOptions_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x14, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x14);
    WfcUtil_SetScene(WfcOptions_WaitFadeIn);
}

extern "C" void WfcOptions_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(0);
    WfcUtil_SetScene(WfcOptions_WaitButtonBar);
}

extern "C" void WfcOptions_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcOptions_Update);
}

extern "C" void WfcOptions_Update() {
    WfcOptions_HandleInput();
    WfcOptions_Idle();
    WfcOptions_HandleResult();
}

extern "C" void WfcOptions_HandleInput() {
    u32 i;
    const WfcRect *q = data_ov001_02229fc8;
    for (i = 0; i < 3; i++, q++) {
        if (WfcInput_IsTouchPressedIn((WfcRect *)q) != 0) {
            WfcButtonBar_SetResult(1);
            sWfcOptionsSel = i;
            WfcOptions_ShowCursor(sWfcOptionsSel)
            return;
        }
    }
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(1);
    } else if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
    } else if (WfcInput_IsKeyRepeat(0x40) != 0) {
        WfcOptions_MoveCursor(1);
    } else if (WfcInput_IsKeyRepeat(0x80) != 0) {
        WfcOptions_MoveCursor(3);
    }
}

extern "C" void WfcOptions_Idle() {}

extern "C" void WfcOptions_HandleResult() {
    DwcWiFiInfo info;
    switch (WfcButtonBar_GetResult()) {
    case 0:
        WfcSound_Play(7);
        break;
    case 1:
        DWCi_BM_GetWiFiInfo(&info);
        if (sWfcOptionsSel != 0 && info.userId == 0) {
            WfcSound_Play(9);
            WfcButtonBar_ForceResult(-1);
            return;
        }
        WfcSound_Play(6);
        WfcOptions_HighlightSelection();
        sWfcOptionsChosen = 1;
        break;
    default:
        return;
    }
    WfcUtil_SetScene(WfcOptions_StartExit);
}

extern "C" void WfcOptions_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcOptions_FadeOut);
}

extern "C" void WfcOptions_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (sWfcOptionsChosen != 0) {
        WfcButtonBar_Close();
    }
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x14, 8);
    WfcUtil_SetScene(WfcOptions_Exit);
}

extern "C" const WfcPoint data_ov001_02229fc4 = {0x00e0, 0x0084};

extern "C" const WfcRect data_ov001_02229fc8[3] = {{0x0008, 0x0024, 0x00f8, 0x0044}, {0x0008, 0x0050, 0x00f8, 0x0070}, {0x0008, 0x007c, 0x00f8, 0x009c}};

extern "C" const WfcRect data_ov001_02229fe0[3] = {{0x06, 0x22, 0xea, 0x36}, {0x06, 0x4e, 0xea, 0x62}, {0x06, 0x7a, 0xea, 0x8e}};

extern "C" void WfcOptions_Exit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcOam_FreeEntry(sWfcOptionsSprite);
    WfcCursor_Clear();
    WfcUtil_HideTopMessage();
    WfcFs_FreeFile(sWfcOptionsPalette);
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x14);
    if (sWfcOptionsChosen == 0) {
        WfcUtil_SetScreenFlags(0, 0);
        WfcUtil_SetScene(WfcTopMenu_Enter);
        return;
    }
    switch (sWfcOptionsSel) {
    case 0:
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcSysInfo_Enter);
        return;
    case 1:
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcErase_Enter);
        return;
    case 2:
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcTransferIntro_Enter);
        return;
    }
}

extern "C" void WfcOptions_MoveCursor(s32 a) {
    if (a == 1) {
        sWfcOptionsSel = FX_ModS32(sWfcOptionsSel + 2, 3);
    } else {
        sWfcOptionsSel = FX_ModS32(sWfcOptionsSel + 1, 3);
    }
    WfcSound_Play(8);
    WfcOptions_ShowCursor(sWfcOptionsSel)
}

extern "C" void WfcOptions_HighlightSelection() {
    u32 b = data_ov001_02229fc0[sWfcOptionsSel];
    WfcUtil_RequestPaletteLine(sWfcOptionsPalette, b, b);
}

extern "C" const u8 data_ov001_02229fc0[3] = {1, 2, 3};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220eb90) {
    HOST_OVERLAY_VAR(sWfcOptionsChosen),
    HOST_OVERLAY_VAR(sWfcOptionsPalette),
    HOST_OVERLAY_VAR(sWfcOptionsSel),
    HOST_OVERLAY_VAR(sWfcOptionsSprite),
    HOST_OVERLAY_VARS_END
};
