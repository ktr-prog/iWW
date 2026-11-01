#include "types.h"
#include "net/WfcConfigSlot.h"
#include "nitro/gxoam.h"
#include "nitro/io_access.h"
#include "net/WfcLoadFunc.h"
#include "net/WfcRect.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02213424.h"
#include "proto/ov001/unk_ov001_022140bc.h"
#include "proto/ov001/unk_ov001_022156e0.h"
#include "proto/ov001/unk_ov001_02218054.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221b44c.h"
#include "proto/ov001/unk_ov001_0221cd74.h"
#include "proto/ov001/unk_ov001_0221cfc0.h"
#include "proto/ov001/unk_ov001_0221dcec.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226c24.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

struct WfcManualSetupWork {
    void *flashTask;
    u8 toggleFlashTimers[4];
    void *bgMapFile;
    void *paletteFiles[2];
    WfcTextCanvas *textCanvas;
    GXOamAttr *rowButtons[7];
    GXOamAttr *statusIcon;
    void *scrollTask;
    void *bgScrollTask;
    u8 selectedItem;
    u8 dragRedrawDelay;
    u8 lastBottomItem;
    u8 savedAutoDns;
    u8 bgScrollPending;
    u8 isDragging;
    u8 scrollEndSoundPlayed;
    u8 errorSoundPlayed;
};

struct WfcManualSetupListMapPathCopy { u8 b[23]; };
struct WfcManualSetupPalettePathCopy { u8 b[21]; };
struct WfcManualSetupPalette2PathCopy { u8 b[22]; };

#define REGSET(a, v) do { u32 t = IO_R((volatile u16 *)(a)); t &= ~3; t |= (v); IO_W((volatile u16 *)(a), t); } while (0)

extern "C" {
extern const WfcRect gWfcScreenRect;

extern const u8 sWfcManualSetupButtonPalettes[3] = {6, 8, 7};
extern const s8 data_ov001_0222a0ac[6] = {-1, 0x23, 0x27, -1, 0x23, 0x2f};
extern const WfcPosSize data_ov001_0222a0b4 = {{0xcc, 0x34}, {0x1c, 0x18}};
extern const WfcPosSize data_ov001_0222a0bc = {{0x8f, 0x34}, {0x2c, 0x18}};
extern const WfcPosSize data_ov001_0222a0c4 = {{0xc0, 0x34}, {0x2c, 0x18}};
extern const u8 sWfcManualSetupRowItems[9] = {0, 1, 0xe, 4, 5, 6, 0xe, 9, 0xa};
extern const u8 data_ov001_0222a0d8[9] = {0, 5, 2, 7, 4, 1, 6, 3, 0};
extern const u8 sWfcManualSetupItemRows[11] = {0, 1, 2, 2, 3, 4, 5, 6, 6, 7, 8};
extern const u8 sWfcManualSetupRowButtonCells[15] = {0, 0x29, 0x2c, 0x52, 0x53, 0x30, 0, 0x2a, 0x30, 0x54, 0x55, 0, 0, 0x2b, 0};
extern const u16 sWfcManualSetupBgRowOffsets[10] = {0, 0x60, 0xe0, 0x140, 0x1c0, 0x240, 0x2a0, 0x320, 0x3a0, 0};
extern const WfcRect sWfcManualSetupButtonRects[3] = {{0x84, 0x1b, 0xfc, 0x2c}, {0x84, 0xac, 0xfc, 0xbd}, {0x04, 0xac, 0x7c, 0xbd}};
extern const WfcRect sWfcManualSetupCursorPos[6] = {{0xc8, 0x31, 0xe0, 0x4d}, {0xbc, 0x31, 0xe0, 0x4d}, {0x8b, 0x31, 0xaf, 0x4d}, {0x82, 0x18, 0xee, 0x2c}, {0x82, 0xa9, 0xee, 0xbd}, {0x02, 0xa9, 0x6e, 0xbd}};

u8 sWfcManualSetupToggleItems[4] = {2, 3, 7, 8};
u8 data_ov001_0222b050[14] = {0, 0, 1, 2, 0, 0, 0, 1, 2, 0, 0, 3, 4, 5};
char data_ov001_0222b060[] = "char/ybBgStep2.ncl.l";
char data_ov001_0222b078[] = "char/ybBgStep21.ncl.l";
char data_ov001_0222b090[] = "char/jb3ListBack.nsc.l";
u16 sWfcAddressFormat[16] = {0x25, 0x33, 0x64, 0x2e, 0x25, 0x33, 0x64, 0x2e, 0x25, 0x33, 0x64, 0x2e, 0x25, 0x33, 0x64, 0};

u8 sWfcManualSetupCursorItem;
u8 sWfcManualSetupMode;
u8 sWfcManualSetupCursorRow;
u16 sWfcManualSetupScroll;
WfcManualSetupWork *sWfcManualSetup;
}

extern "C" {
s32 FX_ModS32(u32, s32);
s32 FX_DivS32(u32, s32);
s32 DWC_BACKUPlCheckAddress(u8 *addr);
s32 DWC_BACKUPlCheckIp(u8 *ip, u8 *mask);
u8 DWCi_BACKUPlConvMaskCidr(u8 *mask);
void MI_CpuFill8(void *dst, u8 v, u32 size);
void swprintf(u16 *dst, s32 n, const u16 *fmt, ...);
}

static inline void Unk_ov001_02216474_GetPos(const GXOamAttr *p, u32 *x, u32 *y) {
    *x = (p->attr01 & 0x1ff0000) >> 16;
    *y = (p->attr01 & 0xff) >> 0;
}

static inline void Unk_ov001_02216474_SetPos(GXOamAttr *p, s32 x, s32 y) {
    p->attr01 = (p->attr01 & 0xfe00ff00) | (y & 0xff) | ((x & 0x1ff) << 16);
}

static inline void Unk_ov001_02216474_Hide(GXOamAttr *p) {
    p->attr01 = (p->attr01 & 0xfe00ff00) | 0x1000000;
}

extern "C" void WfcManualSetup_Enter() {
    WfcConfigSlot *p = WfcConfig_GetEdit();
    s32 i;
    BOOL z = FALSE;
    u32 b;
    sWfcManualSetup = (WfcManualSetupWork *)WfcHeap_AllocClear(sizeof(WfcManualSetupWork), 4);
    sWfcManualSetup->savedAutoDns = p->editAutoDns;
    sWfcManualSetup->lastBottomItem = 0xc;
    WfcManualSetup_ResetCursor();
    WfcManualSetup_LoadBg();
    if (sWfcManualSetupMode == 0) {
        WfcUtil_ShowTopMessage(0x7c, data_ov001_0222a0ac[WfcUtil_GetLanguage()], p->editSlotIndex + 1);
    } else {
        WfcUtil_ShowTopMessage(0x97, -1, 0);
    }
    WfcUtil_ShowStepIndicator(1);
    WfcHighlight_SetListEntry();
    WfcScrollBar_Create(2, 0x55, 0xf1, 0x41, (sWfcManualSetupScroll * 0x37) / 0x91);
    sWfcManualSetup->textCanvas = WfcText_CreateBgCanvas(0, 1);
    i = 0;
    b = sWfcManualSetupRowButtonCells[1];
    z = i;
    for (; i < 7; i++) {
        sWfcManualSetup->rowButtons[i] = WfcObj_CreateSingle(z, b);
    }
    switch (p->status) {
    case 1:
        sWfcManualSetup->statusIcon = WfcObj_CreateSingle(0, 0x50);
        sWfcManualSetup->statusIcon->attr2 = (sWfcManualSetup->statusIcon->attr2 & ~0xc00) | 0xc00;
        break;
    case 2:
        sWfcManualSetup->statusIcon = WfcObj_CreateSingle(0, 0x51);
        sWfcManualSetup->statusIcon->attr2 = (sWfcManualSetup->statusIcon->attr2 & ~0xc00) | 0xc00;
        break;
    }
    sWfcManualSetup->bgScrollTask = WfcTask_Add(1, (void *)WfcManualSetup_ScrollBgTask, 0, 0x6e);
    sWfcManualSetup->flashTask = WfcTask_Add(0, (void *)WfcManualSetup_ToggleFlashTask, 0, 0x78);
    WfcManualSetup_Redraw();
    WfcManualSetup_DrawCursor();
    WfcUtil_SetScene(WfcManualSetup_FadeIn);
}

extern "C" void WfcManualSetup_LoadBg() {
    WfcManualSetupListMapPathCopy lb;
    WfcManualSetupPalettePathCopy lc;
    WfcManualSetupPalette2PathCopy ld;
    lb = *(WfcManualSetupListMapPathCopy *)data_ov001_0222b090;
    lc = *(WfcManualSetupPalettePathCopy *)data_ov001_0222b060;
    ld = *(WfcManualSetupPalette2PathCopy *)data_ov001_0222b078;
    {
        u32 t = IO_R((volatile u16 *)0x400000c);
        t &= 0x43;
        t |= 0xe18;
        IO_W((volatile u16 *)0x400000c, t);
    }
    WfcUtil_LoadFileTo((void *)"char/ybObjKb.ncl.l", GX_LoadOBJPltt);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep2.ncg.l", GX_LoadBG3Char);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep21.ncg.l", GX_LoadBG2Char);
    WfcUtil_LoadFileTo(lc.b, GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/jb3List.nsc.l", GX_LoadBG3Scr);
    sWfcManualSetup->bgMapFile = WfcFs_LoadFile(WfcUtil_LocalizePath(lb.b), 0, 4);
    WfcBgMap_Create(sWfcManualSetup->bgMapFile);
    WfcBgMap_RequestTransfer();
    sWfcManualSetup->paletteFiles[0] = WfcFs_LoadFile(WfcUtil_LocalizePath(lc.b), 0, 4);
    sWfcManualSetup->paletteFiles[1] = WfcFs_LoadFile(WfcUtil_LocalizePath(ld.b), 0, 4);
    REGSET(0x4001008, 3);
    REGSET(0x400100a, 3);
    REGSET(0x4000008, 3);
    REGSET(0x400000a, 2);
    REGSET(0x400000c, 3);
    REGSET(0x400000e, 2);
}

extern "C" void WfcManualSetup_ResetCursor() {
    u32 l;
    WfcConfig_GetEdit();
    WfcUtil_GetEditParams(0, &l);
    if (l != 0) return;
    sWfcManualSetupScroll = 0;
    sWfcManualSetupCursorItem = 0;
    sWfcManualSetupCursorRow = 0;
}

extern "C" void WfcManualSetup_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x1d, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x1d);
    WfcUtil_SetScene(WfcManualSetup_WaitFadeIn);
}

extern "C" void WfcManualSetup_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_SetScene(WfcManualSetup_Update);
}

extern "C" void WfcManualSetup_Update() {
    WfcManualSetup_HandleKeys();
    WfcManualSetup_HandleScrollBar();
}

extern "C" void WfcManualSetup_HandleKeys() {
    if (sWfcManualSetup->scrollTask != 0) return;
    if (sWfcManualSetup->isDragging != 0) return;
    if (WfcManualSetup_HandleTouch() != 0) return;
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcManualSetup_SelectItem(sWfcManualSetupCursorItem);
        return;
    }
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcSound_Play(7);
        sWfcManualSetup->selectedItem = 13;
        WfcUtil_SetScene(WfcManualSetup_StartExit);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x200) != 0) {
        if (sWfcManualSetupScroll == 0x91) {
            if (sWfcManualSetup->errorSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcManualSetup->errorSoundPlayed = 1;
            return;
        }
        WfcSound_Play(0x13);
        sWfcManualSetup->scrollTask = WfcTask_Add(0, (void *)WfcManualSetup_ScrollDownTask, 0, 0x78);
        return;
    }
    if (WfcInput_IsKeyReleased(0x200) != 0) {
        sWfcManualSetup->errorSoundPlayed = 0;
        return;
    }
    if (WfcInput_IsKeyRepeat(0x100) != 0) {
        if (sWfcManualSetupScroll == 0) {
            if (sWfcManualSetup->errorSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcManualSetup->errorSoundPlayed = 1;
            return;
        }
        WfcSound_Play(0x13);
        sWfcManualSetup->scrollTask = WfcTask_Add(0, (void *)WfcManualSetup_ScrollUpTask, 0, 0x78);
        return;
    }
    if (WfcInput_IsKeyReleased(0x100) != 0) {
        sWfcManualSetup->errorSoundPlayed = 0;
        return;
    }
    if (WfcInput_IsKeyRepeat(0x40) != 0) {
        WfcManualSetup_MoveCursor(1);
        return;
    }
    if (WfcInput_IsKeyReleased(0x40) != 0) {
        sWfcManualSetup->errorSoundPlayed = 0;
        return;
    }
    if (WfcInput_IsKeyRepeat(0x80) != 0) {
        WfcManualSetup_MoveCursor(3);
        return;
    }
    if (WfcInput_IsKeyReleased(0x80) != 0) {
        sWfcManualSetup->errorSoundPlayed = 0;
        return;
    }
    if (WfcInput_IsKeyRepeat(0x20) != 0) {
        WfcManualSetup_MoveCursor(0);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x10) == 0) return;
    WfcManualSetup_MoveCursor(2);
}

extern "C" BOOL WfcManualSetup_HandleTouch() {
    u32 r;
    WfcConfig_GetEdit();
    r = WfcManualSetup_HitTest();
    if (r == 14) return 0;
    if (WfcManualSetup_IsItemEnabled(r) == 0) {
        WfcSound_Play(9);
        return 1;
    }
    WfcManualSetup_SetCursor(r);
    switch (r) {
    case 0: case 1: case 4: case 5: case 6: break;
    case 2: case 3: case 7: case 8: WfcManualSetup_FlashToggle(); break;
    }
    WfcManualSetup_SelectItem(r);
    return 1;
}

extern "C" void WfcManualSetup_SelectItem(u32 a) {
    if (WfcManualSetup_IsItemEnabled(a) == 0) {
        WfcSound_Play(9);
        return;
    }
    switch (a) {
    case 0: case 1: break;
    case 2: case 3:
        WfcSound_Play(6);
        WfcManualSetup_SetAutoIp((a - 2) ^ 1 ? 1 : 0);
        return;
    case 4: case 5: case 6: break;
    case 7: case 8:
        WfcSound_Play(6);
        WfcManualSetup_SetAutoDns((a - 7) ^ 1 ? 1 : 0);
        return;
    }
    sWfcManualSetup->selectedItem = a;
    if (a - 11 <= 1) {
        WfcManualSetup_HighlightButton();
        if (WfcManualSetup_ValidateSettings() == 0) {
            WfcSound_Play(9);
            WfcDialog_Open(0x2f, 1, 1, -1, 0);
            WfcUtil_SetScene(WfcManualSetup_InvalidDialog);
            return;
        }
        if (a == 11) {
            WfcSound_Play(6);
        } else {
            WfcSound_Play(14);
        }
    } else if (a == 13) {
        WfcManualSetup_HighlightButton();
        WfcSound_Play(7);
    } else {
        WfcSound_Play(6);
        WfcManualSetup_SetRowButton(0, 1, WfcManualSetup_GetScreenRow(sWfcManualSetupItemRows[a]));
        WfcManualSetup_PlaceObjs();
    }
    WfcScrollBar_Disable();
    WfcUtil_SetScene(WfcManualSetup_StartExit);
}

extern "C" void WfcManualSetup_SetAutoIp(u32 a) {
    u32 r;
    WfcConfigSlot *o = WfcConfig_GetEdit();
    u32 c = o->editAutoIp;
    if (c == a) return;
    if (a != 0) {
        r = sWfcManualSetup->savedAutoDns != 0;
    } else {
        r = 0;
        sWfcManualSetup->savedAutoDns = o->editAutoDns;
    }
    WfcConfig_SetEditAutoIp(a);
    WfcConfig_SetEditAutoDns(r);
    WfcManualSetup_Redraw();
}

extern "C" void WfcManualSetup_SetAutoDns(u32 a) {
    u32 c = WfcConfig_GetEdit()->editAutoDns;
    if (c == a) return;
    sWfcManualSetup->savedAutoDns = a;
    WfcConfig_SetEditAutoDns(a);
    WfcManualSetup_Redraw();
}

extern "C" void WfcManualSetup_HandleScrollBar() {
    if (sWfcManualSetup->scrollTask != 0) return;
    if (sWfcManualSetup->dragRedrawDelay != 0) sWfcManualSetup->dragRedrawDelay--;
    switch (WfcScrollBar_GetEvent()) {
    case 0:
        break;
    case 1:
        sWfcManualSetup->isDragging = 1;
        break;
    case 2:
        if (sWfcManualSetup->dragRedrawDelay != 0) return;
        WfcCursor_Clear();
        sWfcManualSetupScroll = WfcScrollBar_GetPos() * 0x91 / 0x37;
        WfcManualSetup_Redraw();
        sWfcManualSetup->dragRedrawDelay = 4;
        break;
    case 3: {
        sWfcManualSetup->isDragging = 0;
        sWfcManualSetupScroll = WfcScrollBar_GetPos() * 0x91 / 0x37;
        WfcSound_Play(0x13);
        WfcManualSetup_Redraw();
        s32 r = FX_ModS32(sWfcManualSetupScroll, 0x1d);
        if (r == 0) {
            WfcManualSetup_UpdateCursorItem();
            return;
        }
        if (r < 0x10) sWfcManualSetup->scrollTask = WfcTask_Add(0, (void *)WfcManualSetup_ScrollUpTask, 0, 0x78);
        else sWfcManualSetup->scrollTask = WfcTask_Add(0, (void *)WfcManualSetup_ScrollDownTask, 0, 0x78);
        break;
    }
    case 4:
        if (sWfcManualSetupScroll == 0) {
            if (sWfcManualSetup->scrollEndSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcManualSetup->scrollEndSoundPlayed = 1;
        } else {
            WfcSound_Play(0x13);
            sWfcManualSetup->scrollTask = WfcTask_Add(0, (void *)WfcManualSetup_ScrollUpTask, 0, 0x78);
        }
        break;
    case 6:
        if (sWfcManualSetupScroll == 0x91) {
            if (sWfcManualSetup->scrollEndSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcManualSetup->scrollEndSoundPlayed = 1;
        } else {
            WfcSound_Play(0x13);
            sWfcManualSetup->scrollTask = WfcTask_Add(0, (void *)WfcManualSetup_ScrollDownTask, 0, 0x78);
        }
        break;
    case 5:
    case 7:
        sWfcManualSetup->scrollEndSoundPlayed = 0;
        break;
    }
}

extern "C" void WfcManualSetup_StartExit() {
    WfcScrollBar_Disable();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcManualSetup_FadeOut);
}

extern "C" void WfcManualSetup_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x1d, 8);
    WfcUtil_SetScene(WfcManualSetup_Exit);
}

extern "C" void WfcManualSetup_Exit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcTask_Delete(0, sWfcManualSetup->flashTask);
    WfcTask_Delete(1, sWfcManualSetup->bgScrollTask);
    s32 i;
    for (i = 0; i < 7; i++) WfcOam_FreeEntry((GXOamAttr *)sWfcManualSetup->rowButtons[i]);
    if (sWfcManualSetup->statusIcon != 0) WfcOam_FreeEntry((GXOamAttr *)sWfcManualSetup->statusIcon);
    WfcScrollBar_Destroy();
    WfcText_DestroyBgCanvas(0);
    WfcCursor_Clear();
    if (sWfcManualSetup->selectedItem != 0xc) WfcUtil_HideTopMessage();
    WfcBgMap_Destroy();
    WfcFs_FreeFile(sWfcManualSetup->bgMapFile);
    for (i = 0; i < 2; i++) WfcFs_FreeFile(sWfcManualSetup->paletteFiles[i]);
    WfcUtil_LoadFileTo((void *)"char/ybObjMain.ncl.l", GX_LoadOBJPltt);
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x1d);
    IO_W((volatile u32 *)0x4000010, 0);
    IO_W((volatile u32 *)0x4000018, 0);
    IO_W((volatile u16 *)0x400000c, (IO_R((volatile u16 *)0x400000c) & 0x43) | 0xe10);
    u32 t = sWfcManualSetup->selectedItem;
    switch (t) {
    case 0:
    case 1:
        WfcUtil_SetEditParams(t, 0);
        WfcUtil_SetScreenFlags(2, 0);
        WfcUtil_SetScene(WfcTextEdit_Enter);
        break;
    case 4:
    case 5:
    case 6:
    case 9:
    case 10: {
        s32 r = t - 4;
        if (t >= 9) r -= 2;
        WfcUtil_SetScreenFlags(2, 0);
        WfcUtil_SetEditParams(r, 0);
        WfcUtil_SetScene(WfcAddrEdit_Enter);
        break;
    }
    case 11: {
        WfcConfigSlot *p = WfcConfig_GetEdit();
        p->subnetPrefixLen = DWCi_BACKUPlConvMaskCidr(p->editSubnetMask);
        if (p->editAutoIp != 0) {
            MI_CpuFill8(p->ipAddress, 0, 4);
            MI_CpuFill8(p->gateway, 0, 4);
            MI_CpuFill8(p->editSubnetMask, 0, 4);
            p->subnetPrefixLen = 0;
        }
        if (p->editAutoDns != 0) MI_CpuFill8(p->dnsServers, 0, 8);
        WfcUtil_SetScreenFlags(2, 0);
        WfcUtil_SetEditParams(0, 0);
        WfcUtil_SetScene(WfcConnTest_Enter);
        break;
    }
    case 12:
        WfcUtil_SetScreenFlags(0, 0);
        WfcUtil_SetScene(WfcSaveSettings_Enter);
        break;
    case 13:
        if (sWfcManualSetupMode == 0) {
            WfcUtil_SetScreenFlags(2, 1);
            WfcUtil_SetScene(WfcConnSelect_Enter);
        } else {
            WfcConfig_BeginEdit(WfcConfig_GetEdit()->editSlotIndex);
            WfcUtil_SetScreenFlags(0, 1);
            WfcUtil_SetScene(WfcSetupMethod_Enter);
        }
        break;
    }
    WfcHeap_FreeAndClear((void **)&sWfcManualSetup);
}

extern "C" void WfcManualSetup_Redraw() {
    s32 base = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    WfcText_Clear(sWfcManualSetup->textCanvas, 0);
    s32 p, i;
    for (i = 0, p = base; i < 5; i++, p++) WfcManualSetup_DrawRowValue(p, i);
    WfcBgMap_Blit((u8 *)sWfcManualSetup->bgMapFile + sWfcManualSetupBgRowOffsets[base] * 2, 0, 0x1e, 0x13);
    for (i = 0; i < 5; i++, base++) WfcManualSetup_DrawRowButtons(base, i);
    WfcBgMap_RequestTransfer();
    WfcText_RequestTransfer(sWfcManualSetup->textCanvas);
    WfcManualSetup_PlaceObjs();
}

extern "C" void WfcManualSetup_DrawRowValue(s32 idx, s32 arg) {
    u8 buf[0x28];
    WfcConfigSlot *p = WfcConfig_GetEdit();
    s32 n;
    switch (idx) {
    case 0:
        WfcManualSetup_DrawString(p->ssid, arg);
        return;
    case 1: {
        WfcConfigSlot *slot = p;
        switch (slot->wepMode.wepKeySize) {
        case 0:
            return;
        case 1:
            n = 10;
            break;
        case 2:
            n = 0x1a;
            break;
        case 3:
            n = 0x20;
            break;
        }
        if (slot->wepMode.wepAscii == 1) n = n / 2;
        MI_CpuFill8(buf, 0, 0x21);
        memset(buf, 0x2a, n);
        WfcManualSetup_DrawString(buf, arg);
        return;
    }
    case 3:
        if (p->editAutoIp != 0) return;
        WfcManualSetup_DrawAddress(p->ipAddress, arg);
        return;
    case 4:
        if (p->editAutoIp != 0) return;
        WfcManualSetup_DrawAddress(p->editSubnetMask, arg);
        return;
    case 5:
        if (p->editAutoIp != 0) return;
        WfcManualSetup_DrawAddress(p->gateway, arg);
        return;
    case 7:
        if (p->editAutoDns != 0) return;
        WfcManualSetup_DrawAddress(p->dnsServers, arg);
        return;
    case 8:
        if (p->editAutoDns != 0) return;
        WfcManualSetup_DrawAddress(&p->dnsServers[4], arg);
        break;
    }
}

extern "C" void WfcManualSetup_DrawRowButtons(s32 idx, s32 arg) {
    WfcConfigSlot *p = WfcConfig_GetEdit();
    s32 a, b, c, k;
    switch (idx) {
    case 0:
    case 1:
        a = 0;
        b = a;
        if (WfcManualSetup_IsItemEnabled(a) == 0) b = 2;
        break;
    case 2:
        b = c = 0;
        if (p->editAutoIp != 0) { a = 1; k = 4; }
        else { a = 2; k = 3; }
        if (sWfcManualSetup->toggleFlashTimers[0] != 0) b = 1;
        if (sWfcManualSetup->toggleFlashTimers[1] != 0) c = 1;
        WfcManualSetup_SetRowButton(k, c, arg);
        break;
    case 3:
    case 4:
    case 5:
        a = 0;
        if (p->editAutoIp != 0) b = 2;
        else b = a;
        break;
    case 6:
        c = 0;
        b = c;
        if (p->editAutoDns != 0) { a = 1; k = 4; }
        else {
            if (p->editAutoIp == 0) b = 2;
            a = 2;
            k = 3;
        }
        if (sWfcManualSetup->toggleFlashTimers[2] != 0) b = 1;
        if (sWfcManualSetup->toggleFlashTimers[3] != 0) c = 1;
        WfcManualSetup_SetRowButton(k, c, arg);
        break;
    case 7:
    case 8:
        a = 0;
        if (p->editAutoDns != 0) b = 2;
        else b = a;
        break;
    default:
        a = 0;
        b = 2;
        break;
    }
    WfcManualSetup_SetRowButton(a, b, arg);
}

extern "C" s32 WfcManualSetup_IsItemEnabled(s32 idx) {
    WfcConfigSlot *p = WfcConfig_GetEdit();
    s32 r = 1;
    switch (idx) {
    case 7:
        if (p->editAutoIp == 0) r = 0;
        break;
    case 0:
    case 1:
        if ((u8)(p->status + 0xff) <= 1) r = 0;
        break;
    case 4:
    case 5:
    case 6:
        if (p->editAutoIp != 0) r = 0;
        break;
    case 2:
    case 3:
    case 8:
        break;
    case 9:
    case 10:
        if (p->editAutoDns != 0) r = 0;
        break;
    }
    return r;
}

extern "C" void WfcManualSetup_SetRowButton(s32 a, s32 b, s32 c) {
    u16 v[5];
    GXOamAttr **q;
    v[0] = data_ov001_0222a0b4.pos.x;
    v[1] = data_ov001_0222a0c4.pos.x;
    v[2] = data_ov001_0222a0c4.pos.x;
    v[3] = data_ov001_0222a0bc.pos.x;
    v[4] = data_ov001_0222a0bc.pos.x;
    q = &sWfcManualSetup->rowButtons[c];
    if ((u32)(a - 1) <= 1) {
        if (WfcManualSetup_GetListRow(c) == 2) q = &sWfcManualSetup->rowButtons[5];
        else q = &sWfcManualSetup->rowButtons[6];
    }
    const u8 *row = sWfcManualSetupRowButtonCells + a * 3;
    u8 f = row[b];
    if (f != 0) {
        WfcCell_Copy(0, f, *q);
        GXOamAttr *p = *q;
        u32 t = (v[a] & 0x1ff) << 16;
        p->attr01 = t | (p->attr01 & 0xfe00ff00);
        GXOamAttr *h = *q;
        h->attr2 = (h->attr2 & ~0xc00) | 0xc00;
    } else {
        Unk_ov001_02216474_Hide(*q);
    }
}

extern "C" void WfcManualSetup_DrawString(u8 *a, s32 b) {
    u16 buf[17];
    s32 n;
    u32 r4;
    s32 i;
    s32 cnt;
    MI_CpuFill8(buf, 0, 0x22);
    n = WfcUtil_StrNLen(a, 0x20);
    cnt = n <= 0x10 ? n : 0x10;
    for (i = 0; i < cnt; i++) {
        u32 c = a[i];
        if (c == 0x20) buf[i] = 0xe01d;
        else buf[i] = c;
    }
    r4 = b * 0x1d + 2;
    if (n <= 0x10) r4 += 5;
    WfcText_DrawMonospace(sWfcManualSetup->textCanvas, 0x48, r4, 2, 8, buf, 1);
    if (n <= 0x10) return;
    MI_CpuFill8(buf, 0, 0x22);
    s32 rem = n - 0x10;
    for (n = 0; n < rem; n++) {
        u32 c = a[n + 0x10];
        if (c == 0x20) buf[n] = 0xe01d;
        else buf[n] = c;
    }
    WfcText_DrawMonospace(sWfcManualSetup->textCanvas, 0x48, r4 + 0xc, 2, 8, buf, 1);
}

extern "C" void WfcManualSetup_DrawAddress(u8 *a, s32 b) {
    u16 buf[17];
    swprintf(buf, 0x10, sWfcAddressFormat, a[0], a[1], a[2], a[3]);
    WfcText_DrawMonospace(sWfcManualSetup->textCanvas, 0x5f, b * 0x1d + 8, 2, 7, buf, 1);
}

extern "C" void WfcManualSetup_PlaceObjs() {
    s32 x, y;
    s32 n;
    s32 ip;
    s32 yy;
    s32 i;
    n = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    ip = 0x34 - FX_ModS32(sWfcManualSetupScroll, 0x1d);
    if (sWfcManualSetup->statusIcon != 0) {
        if (n == 0) x = 0x26;
        else x = 0x100;
        Unk_ov001_02216474_SetPos(sWfcManualSetup->statusIcon, x, ip);
    }
    yy = ip;
    for (i = 0; i < 5; i++) {
        Unk_ov001_02216474_GetPos(sWfcManualSetup->rowButtons[i], (u32 *)&x, (u32 *)&y);
        Unk_ov001_02216474_SetPos(sWfcManualSetup->rowButtons[i], x, yy);
        yy += 0x1d;
    }
    if (n <= 2) {
        Unk_ov001_02216474_GetPos(sWfcManualSetup->rowButtons[5], (u32 *)&x, (u32 *)&y);
        Unk_ov001_02216474_SetPos(sWfcManualSetup->rowButtons[5], x, ip + (2 - n) * 0x1d);
    } else {
        Unk_ov001_02216474_Hide(sWfcManualSetup->rowButtons[5]);
    }
    if (n >= 2 && n <= 6) {
        Unk_ov001_02216474_GetPos(sWfcManualSetup->rowButtons[6], (u32 *)&x, (u32 *)&y);
        Unk_ov001_02216474_SetPos(sWfcManualSetup->rowButtons[6], x, ip + (6 - n) * 0x1d);
    } else {
        Unk_ov001_02216474_Hide(sWfcManualSetup->rowButtons[6]);
    }
    sWfcManualSetup->bgScrollPending = 1;
}

extern "C" s32 WfcManualSetup_HitTest() {
    WfcPosSize v;
    s32 i;
    s32 n;
    s32 r;
    const WfcRect *p;
    if (WfcInput_IsTouchPressedIn((WfcRect *)&gWfcScreenRect) == 0) return 0xe;
    r = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    v = data_ov001_0222a0b4;
    for (i = 0; i < 4; i++, r++) {
        if (r != 2 && r != 6) {
            if (WfcInput_IsTouchPressedInBox(&v) != 0) return sWfcManualSetupRowItems[r];
        }
        v.pos.y = v.pos.y + 0x1d;
    }
    n = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    for (i = 0; i < 4; i++, n++) {
        if (n == 2) {
            s32 off = i * 0x1d;
            v = data_ov001_0222a0c4;
            v.pos.y = v.pos.y + off;
            if (WfcInput_IsTouchPressedInBox(&v) != 0) return 2;
            v = data_ov001_0222a0bc;
            v.pos.y = v.pos.y + off;
            if (WfcInput_IsTouchPressedInBox(&v) != 0) return 3;
            break;
        }
    }
    n = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    for (i = 0; i < 4; i++, n++) {
        if (n == 6) {
            s32 off = i * 0x1d;
            v = data_ov001_0222a0c4;
            v.pos.y = v.pos.y + off;
            if (WfcInput_IsTouchPressedInBox(&v) != 0) return 7;
            v = data_ov001_0222a0bc;
            v.pos.y = v.pos.y + off;
            if (WfcInput_IsTouchPressedInBox(&v) != 0) return 8;
            break;
        }
    }
    p = sWfcManualSetupButtonRects;
    for (i = 0; i < 3; i++, p++) {
        if (WfcInput_IsTouchPressedIn((WfcRect *)p) != 0) return i + 0xb;
    }
    return 0xe;
}

extern "C" s32 WfcManualSetup_GetScreenRow(s32 a) {
    s32 base = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    s32 i;
    for (i = 0; i < 4; i++, base++) {
        if (base == a) return i;
    }
    return -1;
}

extern "C" s32 WfcManualSetup_GetListRow(s32 a) {
    s32 r = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    r += a;
    return r;
}

extern "C" void WfcManualSetup_ScrollUpTask(void *task) {
    WfcScrollBar_Disable();
    WfcCursor_Clear();
    if (sWfcManualSetupScroll > 6) sWfcManualSetupScroll = sWfcManualSetupScroll - 6;
    else sWfcManualSetupScroll = 0;
    s32 n = FX_ModS32(sWfcManualSetupScroll, 0x1d);
    if (n == 0x17) {
        WfcManualSetup_Redraw();
        return;
    }
    if (n > 0x17) {
        sWfcManualSetupScroll = sWfcManualSetupScroll + (0x1d - n);
        n = 0;
    }
    WfcManualSetup_PlaceObjs();
    if (n != 0) return;
    WfcScrollBar_SetPos((sWfcManualSetupScroll * 0x37) / 0x91);
    WfcScrollBar_Enable();
    WfcManualSetup_UpdateCursorItem();
    sWfcManualSetup->scrollTask = 0;
    WfcTask_RequestDelete(0, task);
}

extern "C" void WfcManualSetup_ScrollDownTask(void *task) {
    WfcScrollBar_Disable();
    WfcCursor_Clear();
    sWfcManualSetupScroll += 6;
    s32 n = FX_ModS32(sWfcManualSetupScroll, 0x1d);
    if (n >= 6) {
        WfcManualSetup_PlaceObjs();
        return;
    }
    sWfcManualSetupScroll = sWfcManualSetupScroll - n;
    WfcManualSetup_Redraw();
    WfcScrollBar_SetPos((sWfcManualSetupScroll * 0x37) / 0x91);
    WfcScrollBar_Enable();
    WfcManualSetup_UpdateCursorItem();
    sWfcManualSetup->scrollTask = 0;
    WfcTask_RequestDelete(0, task);
}

extern "C" void WfcManualSetup_ScrollBgTask() {
    u32 q;
    s32 r;
    s32 ip;
    if (sWfcManualSetup->bgScrollPending == 0) return;
    q = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    r = FX_ModS32(sWfcManualSetupScroll, 0x1d);
    ip = r - 0x33;
    IO_W((volatile u32 *)0x4000010, 0x1ff0000 & (ip << 16));
    IO_W((volatile u32 *)0x4000018, 0x1ff0000 & ((ip + data_ov001_0222a0d8[q]) << 16));
    sWfcManualSetup->bgScrollPending = 0;
}

extern "C" void WfcManualSetup_DrawCursor() {
    s32 v;
    v = data_ov001_0222b050[sWfcManualSetupCursorItem];
    if (v >= 3) {
        WfcCursor_ShowPair(3, sWfcManualSetupCursorPos[v].left, sWfcManualSetupCursorPos[v].right, sWfcManualSetupCursorPos[v].top);
        return;
    }
    {
        WfcRect e = sWfcManualSetupCursorPos[v];
        e.top += sWfcManualSetupCursorRow * 0x1d;
        WfcCursor_ShowPair(1, e.left, e.right, e.top);
    }
}

extern "C" void WfcManualSetup_UpdateCursorItem() {
    WfcConfigSlot *o;
    s32 q;
    s32 r;
    if ((u8)(sWfcManualSetupCursorItem + 0xf5) <= 2) {
        WfcManualSetup_DrawCursor();
        return;
    }
    o = WfcConfig_GetEdit();
    q = FX_DivS32(sWfcManualSetupScroll, 0x1d);
    r = sWfcManualSetupCursorRow + q;
    switch (r) {
    case 2:
        if (o->editAutoIp != 0) {
            sWfcManualSetupCursorItem = 2;
        } else {
            sWfcManualSetupCursorItem = 3;
        }
        break;
    case 6:
        if (o->editAutoDns != 0) {
            sWfcManualSetupCursorItem = 7;
        } else {
            sWfcManualSetupCursorItem = 8;
        }
        break;
    default:
        sWfcManualSetupCursorItem = sWfcManualSetupRowItems[r];
        break;
    }
    WfcManualSetup_DrawCursor();
}

extern "C" void WfcManualSetup_SetCursor(u32 a) {
    sWfcManualSetupCursorItem = a;
    sWfcManualSetupCursorRow = WfcManualSetup_GetScreenRow(sWfcManualSetupItemRows[a]);
    WfcManualSetup_DrawCursor();
}

extern "C" void WfcManualSetup_MoveCursor(s32 a) {
    WfcConfigSlot *o;
    s32 r4;
    s32 s;
    o = WfcConfig_GetEdit();
    r4 = 0;
    s = sWfcManualSetupCursorItem;
    if (s == 8 && o->editAutoIp == 0) {
        if (a == 0) return;
        if (a == 2) return;
    }
    switch (s) {
    case 0:
        if (a == 1) {
            sWfcManualSetupCursorItem = 0xb;
        } else if (a == 3) {
            sWfcManualSetupCursorRow = sWfcManualSetupCursorRow + 1;
        } else {
            r4 = 2;
        }
        break;
    case 10:
        if (a == 1) {
            sWfcManualSetupCursorRow = sWfcManualSetupCursorRow - 1;
        } else if (a != 3) {
            r4 = 2;
        } else {
            sWfcManualSetupCursorItem = sWfcManualSetup->lastBottomItem;
        }
        break;
    case 11:
        if (a == 1) {
            if (sWfcManualSetup->errorSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcManualSetup->errorSoundPlayed = 1;
            return;
        } else if (a != 3) {
            r4 = 2;
        } else {
            sWfcManualSetupCursorItem = 0;
            sWfcManualSetupCursorRow = 0;
            sWfcManualSetupScroll = 0;
            WfcManualSetup_Redraw();
            WfcScrollBar_SetPos(0);
        }
        break;
    case 12:
    case 13:
        sWfcManualSetup->lastBottomItem = s;
        if (a == 1) {
            sWfcManualSetupCursorItem = 10;
            sWfcManualSetupCursorRow = 3;
            sWfcManualSetupScroll = 0x91;
            WfcManualSetup_Redraw();
            WfcScrollBar_SetPos(0x37);
        } else if (a == 3) {
            if (sWfcManualSetup->errorSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcManualSetup->errorSoundPlayed = 1;
            return;
        } else if (s == 12) {
            sWfcManualSetupCursorItem = 13;
        } else {
            sWfcManualSetupCursorItem = 12;
        }
        break;
    default:
        if (a == 1) {
            if (sWfcManualSetupCursorRow != 0) {
                sWfcManualSetupCursorRow = sWfcManualSetupCursorRow - 1;
            } else {
                WfcSound_Play(0x13);
                sWfcManualSetup->scrollTask = WfcTask_Add(0, (void *)WfcManualSetup_ScrollUpTask, 0, 0x78);
                return;
            }
        } else if (a == 3) {
            if (sWfcManualSetupCursorRow < 3) {
                sWfcManualSetupCursorRow = sWfcManualSetupCursorRow + 1;
            } else {
                WfcSound_Play(0x13);
                sWfcManualSetup->scrollTask = WfcTask_Add(0, (void *)WfcManualSetup_ScrollDownTask, 0, 0x78);
                return;
            }
        } else {
            r4 = 2;
            if (s == 2) {
                sWfcManualSetupCursorItem = 3;
                goto redo;
            }
            if (s == 3) {
                sWfcManualSetupCursorItem = 2;
                goto redo;
            }
            if (s == 7) {
                sWfcManualSetupCursorItem = 8;
                goto redo;
            }
            if (s == 8) {
                sWfcManualSetupCursorItem = 7;
            redo:
                WfcSound_Play(8);
                WfcManualSetup_DrawCursor();
            }
        }
        break;
    }
    if (r4 == 2) return;
    WfcSound_Play(8);
    if (r4 != 0) return;
    WfcManualSetup_UpdateCursorItem();
}

extern "C" void WfcManualSetup_HighlightButton() {
    u32 t = sWfcManualSetupButtonPalettes[sWfcManualSetupCursorItem - 0xb];
    WfcUtil_RequestPaletteLine(sWfcManualSetup->paletteFiles[1], t, t);
}

extern "C" void WfcManualSetup_ToggleFlashTask() {
    s32 i;
    for (i = 0; i < 4; i++) {
        u8 *p = &sWfcManualSetup->toggleFlashTimers[i];
        if (*p != 0) {
            *p = *p - 1;
            if (sWfcManualSetup->toggleFlashTimers[i] == 0) {
                WfcManualSetup_Redraw();
            }
        }
    }
}

extern "C" void WfcManualSetup_FlashToggle() {
    const u8 *q;
    s32 i;
    u8 s;
    s = sWfcManualSetupCursorItem;
    for (i = 0, q = sWfcManualSetupToggleItems; i < 4; i++, q++) {
        if (s == *q) {
            WfcManualSetupWork *g = sWfcManualSetup;
            g->toggleFlashTimers[i] = 0x14;
            if ((i & 1) != 0) {
                sWfcManualSetup->toggleFlashTimers[i - 1] = 0;
                return;
            }
            sWfcManualSetup->toggleFlashTimers[i + 1] = 0;
            return;
        }
    }
}

extern "C" BOOL WfcManualSetup_ValidateSettings() {
    WfcConfigSlot *o = WfcConfig_GetEdit();
    if (o->ssid[0] == 0) return FALSE;
    if (o->editAutoDns == 0 && DWC_BACKUPlCheckAddress(o->dnsServers) == 0 && DWC_BACKUPlCheckAddress(&o->dnsServers[4]) == 0) return FALSE;
    if (o->editAutoIp == 0) {
        if (DWC_BACKUPlCheckAddress(o->ipAddress) == 0) return FALSE;
        if (DWC_BACKUPlCheckAddress(o->gateway) == 0) return FALSE;
        if (DWC_BACKUPlCheckIp(o->ipAddress, o->editSubnetMask) == 0) return FALSE;
    }
    return TRUE;
}

extern "C" void WfcManualSetup_InvalidDialog() {
    if (WfcDialog_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_RequestBgPalette(sWfcManualSetup->paletteFiles[0]);
    WfcUtil_SetScene(WfcManualSetup_WaitDialogClosed);
}

extern "C" void WfcManualSetup_WaitDialogClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcUtil_SetScene(WfcManualSetup_Update);
}

extern "C" void WfcManualSetup_SetMode(u32 v) {
    sWfcManualSetupMode = v;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_022156e0) {
    HOST_OVERLAY_VAR(sWfcManualSetupToggleItems),
    HOST_OVERLAY_VAR(data_ov001_0222b050),
    HOST_OVERLAY_VAR(data_ov001_0222b060),
    HOST_OVERLAY_VAR(data_ov001_0222b078),
    HOST_OVERLAY_VAR(data_ov001_0222b090),
    HOST_OVERLAY_VAR(sWfcAddressFormat),
    HOST_OVERLAY_VAR(sWfcManualSetupCursorItem),
    HOST_OVERLAY_VAR(sWfcManualSetupMode),
    HOST_OVERLAY_VAR(sWfcManualSetupCursorRow),
    HOST_OVERLAY_VAR(sWfcManualSetupScroll),
    HOST_OVERLAY_VAR(sWfcManualSetup),
    HOST_OVERLAY_VARS_END
};
