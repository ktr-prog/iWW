#include "types.h"
#include "nitro/io_access.h"
#include "net/WfcRect.h"
#include "net/WfcObjGroup.h"
#include "net/WfcConfigSlot.h"
#include "menu/WfcConnSelectWork.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0220d760.h"
#include "proto/ov001/unk_ov001_022111c8.h"
#include "proto/ov001/unk_ov001_022156e0.h"
#include "proto/ov001/unk_ov001_02219064.h"
#include "proto/ov001/unk_ov001_0221962c.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221c180.h"
#include "proto/ov001/unk_ov001_0221cd74.h"
#include "proto/ov001/unk_ov001_0221d744.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221eb38.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_0222449c.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"

#pragma thumb off

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {
void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
void GX_LoadOBJPltt(const void *src, u32 offset, u32 size);
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
u8 *WfcConfig_GetEdit();
u32 WfcConfig_GetSlotStatus(s32 idx);
void WfcConfig_BeginEdit(s32 idx);
void WfcConfig_EraseSlot(s32 idx);
void WfcObj_Free(WfcObjGroup *p);

extern const u8 sWfcConnSelectSlotCells[4];
extern const s8 data_ov001_0222a160[8];
extern const WfcPoint sWfcConnSelectButtonPos[6];
extern const WfcRect sWfcConnSelectRects[7];
extern const u16 sWfcConnSelectCursorPos[7][4];

u8 sWfcConnSelectCursor;
WfcConnSelectWork *sWfcConnSelect;
}

static inline WfcConfigSlot *WfcConnSelect_EditSlot() { return (WfcConfigSlot *)WfcConfig_GetEdit(); }

#define BGCNT(a, v) IO_W((volatile u16 *)(a), (IO_R((volatile u16 *)(a)) & ~3) | (v))

extern "C" {

void WfcConnSelect_Enter() {
    sWfcConnSelect = (WfcConnSelectWork *)WfcHeap_AllocClear(sizeof(WfcConnSelectWork), 4);
    sWfcConnSelect->exitAction = 0;
    WfcConnSelect_LoadBg();
    WfcHighlight_Set(1);
    WfcUtil_ShowTopMessage(0x7b, -1, 0);
    WfcUtil_ShowStepIndicator(0);
    WfcConnSelect_CreateSlotButtons();
    WfcConnSelect_DrawCursor();
    WfcUtil_SetScene(WfcConnSelect_FadeIn);
}

void WfcConnSelect_LoadBg() {
    u8 buf[22] = "char/ybBgStep11.ncl.l";
    WfcUtil_LoadFileTo((void *)"char/ybObjWay.ncl.l", (WfcLoadFunc)GX_LoadOBJPltt);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep1.ncg.l", (WfcLoadFunc)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep1.ncl.l", (WfcLoadFunc)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/jb2Ap.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
    sWfcConnSelect->paletteFile = WfcFs_LoadFile(WfcUtil_LocalizePath(buf), 0, 4);
    WfcGx_ShowPlanes(1, 0x10);
    BGCNT(0x4001008, 3);
    BGCNT(0x400100a, 3);
    BGCNT(0x400000a, 3);
    BGCNT(0x400000c, 3);
}

void WfcConnSelect_CreateSlotButtons() {
    u32 z[2];
    u32 a;
    s32 i;
    z[0] = 0;
    z[1] = 0;
    for (i = 0; i < 3; i++) {
        a = WfcConfig_GetSlotStatus(i);
        if (a == 0xff) {
            a = 3;
        } else {
            sWfcConnSelect->eraseButtons[i] = WfcObj_Create(z[0], 0x11, 1);
            WfcObj_SetPos(sWfcConnSelect->eraseButtons[i], -1, sWfcConnSelectButtonPos[i + 3].x, sWfcConnSelectButtonPos[i + 3].y);
            WfcObj_SetPriority(sWfcConnSelect->eraseButtons[i], -1, 3);
        }
        sWfcConnSelect->slotButtons[i] = WfcObj_Create(z[1], sWfcConnSelectSlotCells[a], 1);
        WfcObj_SetPos(sWfcConnSelect->slotButtons[i], -1, sWfcConnSelectButtonPos[i].x, sWfcConnSelectButtonPos[i].y);
        WfcObj_SetPriority(sWfcConnSelect->slotButtons[i], -1, 3);
    }
}

void WfcConnSelect_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x14, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x14);
    WfcUtil_SetScene(WfcConnSelect_WaitFadeIn);
}

void WfcConnSelect_WaitFadeIn() {
    if (WfcFade_IsBusy(1)) return;
    if (WfcFade_IsBusy(0)) return;
    WfcUtil_OpenButtonBar(0);
    WfcUtil_SetScene(WfcConnSelect_WaitButtonBar);
}

void WfcConnSelect_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    if (WfcHeader_IsAnimating() == 1) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcConnSelect_Update);
}

void WfcConnSelect_Update() {
    WfcConnSelect_HandleInput();
    WfcConnSelect_Idle();
    WfcConnSelect_HandleSelection();
}

void WfcConnSelect_HandleInput() {
    u32 i;
    for (i = 0; i < 7; i++) {
        if (WfcInput_IsTouchPressedIn(const_cast<WfcRect *>(&sWfcConnSelectRects[i]))) {
            WfcButtonBar_SetResult(1);
            sWfcConnSelectCursor = i;
            WfcConnSelect_DrawCursor();
            return;
        }
    }
    if (WfcInput_IsKeyPressed(1)) {
        WfcButtonBar_SetResult(1);
        return;
    }
    if (WfcInput_IsKeyPressed(2)) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x40)) {
        WfcConnSelect_MoveCursor(1);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x80)) {
        WfcConnSelect_MoveCursor(3);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x20)) {
        WfcConnSelect_MoveCursor(0);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x10) == 0) return;
    WfcConnSelect_MoveCursor(2);
}

void WfcConnSelect_Idle() {}

void WfcConnSelect_HandleSelection() {
    s32 r = WfcButtonBar_GetResult();
    switch (r) {
    case 0:
        switch (WfcUtil_GetStartMode()) {
        case 0:
            WfcSound_Play(7);
            sWfcConnSelect->exitAction = 2;
            break;
        case 1:
            WfcButtonBar_DisableInput();
            WfcUtil_SetScene(WfcUtil_QuitFadeOut);
            return;
        }
        break;
    case 1: {
        u32 t;
        sWfcConnSelect->exitAction = 1;
        t = sWfcConnSelectCursor;
        if (t >= 4) {
            u32 k = t - 4;
            if (WfcConfig_GetSlotStatus(k) == 0xff) {
                WfcSound_Play(9);
                WfcButtonBar_ForceResult(-1);
                return;
            }
            WfcSound_Play(6);
            WfcDialog_Open(0x98, 0, 1, data_ov001_0222a160[WfcUtil_GetLanguage()], k + 1);
            WfcConnSelect_PressEraseButton();
            WfcButtonBar_DisableInput();
            WfcUtil_SetScene(WfcConnSelect_EraseDialog);
            return;
        }
        if (t <= 2) {
            WfcConfig_BeginEdit(t);
        }
        WfcSound_Play(6);
        WfcConnSelect_HighlightSelection();
        break;
    }
    default:
        return;
    }
    WfcUtil_SetScene(WfcConnSelect_StartExit);
}

void WfcConnSelect_StartExit() {
    if (sWfcConnSelect->exitAction == 2) {
        WfcHeader_StartSlideOut();
    }
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcConnSelect_FadeOut);
}

void WfcConnSelect_FadeOut() {
    if (WfcFade_IsBusy(1)) return;
    if (sWfcConnSelect->exitAction == 1) {
        if (sWfcConnSelectCursor == 3 || WfcConnSelect_EditSlot()->status != 0xff) {
            WfcButtonBar_Close();
        }
    }
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x14, 8);
    WfcUtil_SetScene(WfcConnSelect_Exit);
}

void WfcConnSelect_Exit() {
    s32 i;
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcHeader_IsSlideOutDone() == 0) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    for (i = 0; (u32)i < 3; i++) {
        if (sWfcConnSelect->slotButtons[i] != 0) WfcObj_Free(sWfcConnSelect->slotButtons[i]);
    }
    for (i = 0; (u32)i < 3; i++) {
        if (sWfcConnSelect->eraseButtons[i] != 0) WfcObj_Free(sWfcConnSelect->eraseButtons[i]);
    }
    WfcCursor_Clear();
    WfcUtil_HideTopMessage();
    WfcFs_FreeFile(sWfcConnSelect->paletteFile);
    WfcUtil_LoadFileTo(data_ov001_0222b260, (WfcLoadFunc)GX_LoadOBJPltt);
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x14);
    if (sWfcConnSelect->exitAction == 2) {
        WfcUtil_SetScreenFlags(0, 0);
        WfcUtil_SetScene(WfcTopMenu_Enter);
    } else {
        switch (sWfcConnSelectCursor) {
        case 0: case 1: case 2:
            WfcUtil_SetScreenFlags(2, 0);
            if (WfcConnSelect_EditSlot()->status == 0xff) {
                WfcUtil_SetScene(WfcSetupMethod_Enter);
            } else {
                WfcUtil_SetEditParams(0, 0);
                WfcManualSetup_SetMode(0);
                WfcUtil_SetScene(WfcManualSetup_Enter);
            }
            break;
        case 3:
            WfcUtil_SetScreenFlags(2, 1);
            WfcUtil_SetScene(WfcUsbIntro_Enter);
            break;
        }
    }
    WfcHeap_FreeAndClear((void **)&sWfcConnSelect);
}

void WfcConnSelect_DrawCursor() {
    u32 i = sWfcConnSelectCursor;
    const u16 *box = sWfcConnSelectCursorPos[i];
    if (i < 4) {
        WfcCursor_ShowCorners(box[0], box[2], box[1], box[3]);
    } else {
        WfcCursor_ShowPair(0, box[0], box[2], box[1]);
    }
}

void WfcConnSelect_MoveCursor(u32 a) {
    u32 f = 1;
    switch (sWfcConnSelectCursor) {
    case 0:
        sWfcConnSelect->lastColumn = 0;
        if (a == 0) sWfcConnSelectCursor = 2;
        else if (a == 2) sWfcConnSelectCursor = 1;
        else if (a == 1) sWfcConnSelectCursor = 3;
        else sWfcConnSelectCursor = 4;
        break;
    case 1:
        sWfcConnSelect->lastColumn = 1;
        if (a == 0) sWfcConnSelectCursor = 0;
        else if (a == 2) sWfcConnSelectCursor = 2;
        else if (a == 1) sWfcConnSelectCursor = 3;
        else sWfcConnSelectCursor = 5;
        break;
    case 2:
        sWfcConnSelect->lastColumn = 2;
        if (a == 0) sWfcConnSelectCursor = 1;
        else if (a == 2) sWfcConnSelectCursor = 0;
        else if (a == 1) sWfcConnSelectCursor = 3;
        else sWfcConnSelectCursor = 6;
        break;
    case 3: {
        u32 t = sWfcConnSelect->lastColumn;
        u32 t4 = t + 4;
        if (a == 1) sWfcConnSelectCursor = t4;
        else if (a == 3) sWfcConnSelectCursor = t;
        else f = 0;
        break;
    }
    case 4:
        sWfcConnSelect->lastColumn = 0;
        if (a == 0) sWfcConnSelectCursor = 6;
        else if (a == 2) sWfcConnSelectCursor = 5;
        else if (a == 1) sWfcConnSelectCursor = 0;
        else sWfcConnSelectCursor = 3;
        break;
    case 5:
        sWfcConnSelect->lastColumn = 1;
        if (a == 0) sWfcConnSelectCursor = 4;
        else if (a == 2) sWfcConnSelectCursor = 6;
        else if (a == 1) sWfcConnSelectCursor = 1;
        else sWfcConnSelectCursor = 3;
        break;
    case 6:
        sWfcConnSelect->lastColumn = 2;
        if (a == 0) sWfcConnSelectCursor = 5;
        else if (a == 2) sWfcConnSelectCursor = 4;
        else if (a == 1) sWfcConnSelectCursor = 2;
        else sWfcConnSelectCursor = 3;
        break;
    }
    if (f == 0) return;
    WfcSound_Play(8);
    WfcConnSelect_DrawCursor();
}

void WfcConnSelect_PressEraseButton() {
    s32 i = sWfcConnSelectCursor - 4;
    WfcCell_Copy(0, 0x32, WfcObj_GetOam(sWfcConnSelect->eraseButtons[i], 0));
    WfcObj_SetPos(sWfcConnSelect->eraseButtons[i], -1, sWfcConnSelectButtonPos[i + 3].x, sWfcConnSelectButtonPos[i + 3].y);
    WfcObj_SetPriority(sWfcConnSelect->eraseButtons[i], -1, 3);
}

void WfcConnSelect_EraseDialog() {
    s32 i = sWfcConnSelectCursor - 4;
    s32 r = WfcDialog_GetResult();
    switch (r) {
    case 1:
        WfcSound_Play(14);
        WfcConfig_EraseSlot(i);
        WfcCell_Copy(0, sWfcConnSelectSlotCells[3], WfcObj_GetOam(sWfcConnSelect->slotButtons[i], 0));
        WfcObj_SetPos(sWfcConnSelect->slotButtons[i], -1, sWfcConnSelectButtonPos[i].x, sWfcConnSelectButtonPos[i].y);
        WfcObj_SetPriority(sWfcConnSelect->slotButtons[i], -1, 3);
        WfcObj_Free(sWfcConnSelect->eraseButtons[i]);
        sWfcConnSelect->eraseButtons[i] = 0;
        break;
    case 0:
        WfcSound_Play(7);
        WfcCell_Copy(0, 0x11, WfcObj_GetOam(sWfcConnSelect->eraseButtons[i], 0));
        WfcObj_SetPos(sWfcConnSelect->eraseButtons[i], -1, sWfcConnSelectButtonPos[i + 3].x, sWfcConnSelectButtonPos[i + 3].y);
        WfcObj_SetPriority(sWfcConnSelect->eraseButtons[i], -1, 3);
        break;
    default:
        return;
    }
    WfcDialog_Close();
    WfcUtil_SetScene(WfcConnSelect_WaitDialogClosed);
}

void WfcConnSelect_WaitDialogClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcConnSelect_Update);
}

void WfcConnSelect_HighlightSelection() {
    if (sWfcConnSelectCursor > 3) return;
    u32 v = data_ov001_0222b240[sWfcConnSelectCursor];
    WfcUtil_RequestPaletteLine(sWfcConnSelect->paletteFile, v, v);
    if (sWfcConnSelectCursor == 3) return;
    s32 r = WfcConfig_GetSlotStatus(sWfcConnSelectCursor);
    if (r > 2) r = 3;
    WfcObj_SetModePalette(sWfcConnSelect->slotButtons[sWfcConnSelectCursor], -1, 0, data_ov001_0222b244[r]);
}

}

extern "C" u8 data_ov001_0222b244[4] = {0xa, 9, 0xb, 6};

extern "C" const s8 data_ov001_0222a160[8] = {0x03, 0x2d, 0x27, 0x1d, 0x32, 0x30, 0, 0};

extern "C" const WfcPoint sWfcConnSelectButtonPos[6] = {{8, 0x30}, {0x5a, 0x30}, {0xac, 0x30}, {0xc, 0x58}, {0x5e, 0x58}, {0xb0, 0x58}};

extern "C" const u8 sWfcConnSelectSlotCells[4] = {0x13, 0x14, 0x12, 0x56};

extern "C" const u16 sWfcConnSelectCursorPos[7][4] = {
    {6, 0x1e, 0x46, 0x48}, {0x58, 0x1e, 0x98, 0x48}, {0xaa, 0x1e, 0xea, 0x48}, {6, 0x76, 0xea, 0x92},
    {9, 0x54, 0x43, 0x70}, {0x5b, 0x54, 0x95, 0x70}, {0xad, 0x54, 0xe7, 0x70},
};

extern "C" const WfcRect sWfcConnSelectRects[7] = {
    {8, 0x20, 0x54, 0x56}, {0x5a, 0x20, 0xa6, 0x56}, {0xac, 0x20, 0xf8, 0x56}, {8, 0x78, 0xf8, 0xa0},
    {8, 0x54, 0x54, 0x70}, {0x5a, 0x54, 0xa6, 0x70}, {0xac, 0x54, 0xf8, 0x70},
};

extern "C" u8 data_ov001_0222b240[4] = {3, 4, 5, 7};

extern "C" char data_ov001_0222b260[22] = "char/ybObjMain.ncl.l";

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02219c3c) {
    HOST_OVERLAY_VAR(sWfcConnSelectCursor),
    HOST_OVERLAY_VAR(sWfcConnSelect),
    HOST_OVERLAY_VAR(data_ov001_0222b244),
    HOST_OVERLAY_VAR(data_ov001_0222b240),
    HOST_OVERLAY_VAR(data_ov001_0222b260),
    HOST_OVERLAY_VARS_END
};
