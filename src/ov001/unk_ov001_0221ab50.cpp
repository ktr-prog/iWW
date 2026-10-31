#include "types.h"
#include "nitro/io_access.h"
#include "net/WfcRect.h"
#include "net/WfcConfigSlot.h"
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
#include "proto/ov001/unk_ov001_022111c8.h"
#include "proto/ov001/unk_ov001_02214f50.h"
#include "proto/ov001/unk_ov001_022156e0.h"
#include "proto/ov001/unk_ov001_02219064.h"
#include "proto/ov001/unk_ov001_0221962c.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221b44c.h"
#include "proto/ov001/unk_ov001_0221b8f4.h"
#include "proto/ov001/unk_ov001_0221cd74.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221eb38.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"
#include "proto/ov001/unk_ov001_02226f68.h"
#include "proto/ov065/unk_ov065_0226ad84.h"

#pragma thumb off

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {
void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
u8 *WfcConfig_GetEdit();

extern const s8 data_ov001_0222a1f0[8];
extern const s8 sWfcSetupMethodNav[2][4][4];
extern const WfcRect sWfcSetupMethodRects[2][4];
extern const u16 sWfcSetupMethodCursorPos[2][4][4];

s8 sWfcSetupMethodColumn;
u8 sWfcSetupMethodChosen;
s8 sWfcSetupMethodCursor;
void *sWfcSetupMethodPalette;
}

#define REGSET(a, v) do { u32 t = IO_R((volatile u16 *)(a)); t &= ~3; t |= (v); IO_W((volatile u16 *)(a), t); } while (0)

extern "C" {

void WfcSetupMethod_Enter() {
    WfcConfigSlot *o = (WfcConfigSlot *)WfcConfig_GetEdit();
    s32 t = sWfcSetupMethodColumn;
    sWfcSetupMethodChosen = 0;
    if (t == 0) sWfcSetupMethodColumn = 1;
    if (WfcUtil_GetLanguage() != 0) {
        if (sWfcSetupMethodCursor == 2) sWfcSetupMethodCursor = 0;
        if (sWfcSetupMethodColumn == 2) sWfcSetupMethodColumn = 1;
    }
    WfcSetupMethod_LoadBg();
    WfcHighlight_SetConnection();
    WfcUtil_ShowTopMessage(0x7e, data_ov001_0222a1f0[WfcUtil_GetLanguage()], o->editSlotIndex + 1);
    WfcUtil_ShowStepIndicator(1);
    WfcCursor_ShowCorners(sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][0],
                          sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][2],
                          sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][1],
                          sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][3]);
    WfcUtil_SetScene(WfcSetupMethod_FadeIn);
}

void WfcSetupMethod_LoadBg() {
    u8 l[22] = "char/ybBgStep21.ncl.l";
    WfcUtil_LoadFileTo(data_ov001_0222b2ec, (WfcLoadFunc)GX_LoadBG2Char);
    WfcUtil_LoadFileTo(data_ov001_0222b304, (WfcLoadFunc)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/jb3Way.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
    sWfcSetupMethodPalette = WfcFs_LoadFile(WfcUtil_LocalizePath(l), 0, 4);
    REGSET(0x4001008, 3);
    REGSET(0x400100a, 3);
    REGSET(0x400000a, 3);
    REGSET(0x400000c, 3);
}

void WfcSetupMethod_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x14, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x14);
    WfcUtil_SetScene(WfcSetupMethod_WaitFadeIn);
}

void WfcSetupMethod_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(0);
    WfcUtil_SetScene(WfcSetupMethod_WaitButtonBar);
}

void WfcSetupMethod_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcSetupMethod_Update);
}

void WfcSetupMethod_Update() {
    WfcSetupMethod_HandleInput();
    WfcSetupMethod_Idle();
    WfcSetupMethod_HandleResult();
}

void WfcSetupMethod_HandleInput() {
    u32 i;
    for (i = 0; i < 4; i++) {
        if (WfcInput_IsTouchPressedIn(const_cast<WfcRect *>(&sWfcSetupMethodRects[WfcUtil_TestOptionFlag(1)][i])) != 0) {
            WfcButtonBar_SetResult(1);
            sWfcSetupMethodCursor = i;
            WfcCursor_ShowCorners(sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][0],
                                  sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][2],
                                  sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][1],
                                  sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][3]);
            return;
        }
    }
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(1);
        return;
    }
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x40) != 0) {
        WfcSetupMethod_MoveCursor(1);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x80) != 0) {
        WfcSetupMethod_MoveCursor(3);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x20) != 0) {
        WfcSetupMethod_MoveCursor(0);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x10) != 0) {
        WfcSetupMethod_MoveCursor(2);
    }
}

void WfcSetupMethod_Idle() {
}

void WfcSetupMethod_HandleResult() {
    switch (WfcButtonBar_GetResult()) {
    case 0:
        WfcSound_Play(7);
        break;
    case 1:
        WfcSound_Play(6);
        WfcSetupMethod_HighlightOption();
        sWfcSetupMethodChosen = 1;
        break;
    default:
        return;
    }
    WfcUtil_SetScene(WfcSetupMethod_StartExit);
}

void WfcSetupMethod_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcSetupMethod_FadeOut);
}

void WfcSetupMethod_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (sWfcSetupMethodChosen != 0) WfcButtonBar_Close();
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x14, 8);
    WfcUtil_SetScene(WfcSetupMethod_Exit);
}

void WfcSetupMethod_Exit() {
    if (WfcFade_IsBusy(1)) return;
    if (WfcFade_IsBusy(0)) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcCursor_Clear();
    WfcUtil_HideTopMessage();
    WfcFs_FreeFile(sWfcSetupMethodPalette);
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x14);
    if (sWfcSetupMethodChosen == 0) {
        WfcUtil_SetScreenFlags(2, 0);
        WfcUtil_SetScene(WfcConnSelect_Enter);
        return;
    }
    switch (sWfcSetupMethodCursor) {
    case 0:
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcApSearch_Enter);
        return;
    case 1:
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcAossSetup_Enter);
        return;
    case 2:
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcSimpleStartInit_Enter);
        return;
    case 3:
        WfcUtil_SetScreenFlags(2, 0);
        WfcUtil_SetEditParams(0, 0);
        WfcManualSetup_SetMode(1);
        WfcUtil_SetScene(WfcManualSetup_Enter);
        break;
    }
}

void WfcSetupMethod_MoveCursor(s32 p) {
    s32 s = sWfcSetupMethodCursor;
    s32 c = WfcUtil_TestOptionFlag(1);
    s32 v = sWfcSetupMethodNav[c][s][p];
    if (v == -1) return;
    if (v == 0) {
        sWfcSetupMethodColumn = s;
    }
    if (v == -2) {
        sWfcSetupMethodCursor = sWfcSetupMethodColumn;
    } else {
        sWfcSetupMethodCursor = v;
    }
    WfcSound_Play(8);
    WfcCursor_ShowCorners(sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][0],
                          sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][2],
                          sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][1],
                          sWfcSetupMethodCursorPos[WfcUtil_TestOptionFlag(1)][sWfcSetupMethodCursor][3]);
}

void WfcSetupMethod_HighlightOption() {
    u32 v = data_ov001_0222b2d0[sWfcSetupMethodCursor];
    WfcUtil_RequestPaletteLine(sWfcSetupMethodPalette, v, v);
}

}

extern "C" const s8 data_ov001_0222a1f0[8] = {3, -1, -1, -1, -1, -1, 0, 0};

extern "C" u8 data_ov001_0222b2d0[4] = {1, 2, 3, 4};

extern "C" const s8 sWfcSetupMethodNav[2][4][4] = {
    {{-1, -2, -1, -2}, {3, 0, 3, 0}, {-1, -1, -1, -1}, {1, 0, 1, 0}},
    {{-1, -2, -1, -2}, {3, 0, 2, 0}, {1, 0, 3, 0}, {2, 0, 1, 0}},
};

extern "C" const u16 sWfcSetupMethodCursorPos[2][4][4] = {
    {{6, 0x1e, 0xea, 0x4e}, {6, 0x62, 0x70, 0x92}, {0, 0, 0, 0}, {0x80, 0x62, 0xea, 0x92}},
    {{6, 0x1e, 0xea, 0x4e}, {6, 0x62, 0x56, 0x92}, {0x66, 0x62, 0xb6, 0x92}, {0xc6, 0x62, 0xea, 0x92}},
};

extern "C" const WfcRect sWfcSetupMethodRects[2][4] = {
    {{8, 0x20, 0xf8, 0x5c}, {8, 0x64, 0x7e, 0xa0}, {0, 0, 0, 0}, {0x83, 0x64, 0xf8, 0xa0}},
    {{8, 0x20, 0xf8, 0x5c}, {8, 0x64, 0x64, 0xa0}, {0x68, 0x64, 0xc4, 0xa0}, {0xc8, 0x64, 0xf8, 0xa0}},
};

extern "C" char data_ov001_0222b304[24] = "char/ybBgStep2.ncl.l";

extern "C" char data_ov001_0222b2ec[24] = "char/jbBgStep2.ncg.l";

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221ab50) {
    HOST_OVERLAY_VAR(sWfcSetupMethodColumn),
    HOST_OVERLAY_VAR(sWfcSetupMethodChosen),
    HOST_OVERLAY_VAR(sWfcSetupMethodCursor),
    HOST_OVERLAY_VAR(sWfcSetupMethodPalette),
    HOST_OVERLAY_VAR(data_ov001_0222b2d0),
    HOST_OVERLAY_VAR(data_ov001_0222b304),
    HOST_OVERLAY_VAR(data_ov001_0222b2ec),
    HOST_OVERLAY_VARS_END
};
