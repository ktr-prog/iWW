#include "types.h"
#include "host_tick.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/NumberPad.h"
#include "nitro/gxoam.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov130/unk_ov130_02292360.h"

extern "C" const u8 sTitleTextIds[8];
extern "C" const u8 sValueLabelTextIds[8];
extern "C" const u8 sBalanceLabelTextIds[8];
extern "C" const u8 sNumberPadTouchKeyMap[12];
extern "C" const u8 sNumberPadCursorRightTable[16];
extern "C" const u8 sNumberPadCursorLeftTable[16];
extern "C" const u8 sNumberPadCursorUpTable[16];
extern "C" const u8 sNumberPadCursorDownTable[16];
extern "C" const u32 sDigitColumnTable[6];
extern "C" const u32 sDigitRowTable[6];
extern "C" const u32 sKeyX0Table[11];
extern "C" const u32 sKeyX1Table[11];
extern "C" const u32 sKeyRowTable[11];
extern "C" const u32 sNumberPadCursorYTable[13];
extern "C" const u32 sNumberPadCursorXTable[13];
extern "C" char *sTitleObjCharFiles[2];
extern "C" char data_ov130_02293368[20];
extern "C" char data_ov130_0229337c[20];
extern "C" u16 sNumberPadKeySeIds[10];
extern "C" char data_ov130_022933a4[20];
extern "C" char data_ov130_022933b8[20];
extern "C" char data_ov130_022933cc[20];
extern "C" char data_ov130_022933e0[20];
extern "C" char data_ov130_022933f4[20];
extern "C" char data_ov130_02293408[20];
extern "C" char data_ov130_0229341c[20];
extern "C" char data_ov130_02293430[20];
extern "C" char data_ov130_02293444[20];
extern "C" char data_ov130_02293458[23];
extern "C" const char *sKeyScreenFiles[6];
extern "C" const char *sMainScreenFiles[6];
extern "C" char data_ov130_022934a0[25];
extern "C" char data_ov130_022934bc[25];
extern "C" GXOamAttr data_ov130_022934d8[4];
extern "C" GXOamAttr sSeparatorCells[4];
extern "C" GXOamAttr data_ov130_02293518[4];
extern "C" GXOamAttr sSeparatorCellsWide[6];
extern "C" GXOamAttr data_ov130_02293568[8];
extern "C" GXOamAttr data_ov130_022935a8[8];
extern "C" GXOamAttr data_ov130_022935e8[8];

extern "C" GXOamAttr data_ov130_02293568[8] = {{0x81d840b0, 0x14c, 0, 0xc, 0x0}, {0x81f840b0, 0x150, 0, 0xc, 0x0}, {0x801840b0, 0x154, 0, 0xc, 0x0}, {0x403800b0, 0x158, 0, 0xc, 0x0}, {0x903040b0, 0xcf, 0, 0xb, 0x0}, {0x801040b0, 0xd0, 0, 0xb, 0x0}, {0x81f040b0, 0xd0, 0, 0xb, 0x0}, {0x81d040b0, 0xcf, 0, 0xb, 0xffff}};
extern "C" GXOamAttr data_ov130_022935a8[8] = {{0x81d440b4, 0x14c, 0, 0xc, 0x0}, {0x81f440b4, 0x150, 0, 0xc, 0x0}, {0x801440b4, 0x154, 0, 0xc, 0x0}, {0x403400b4, 0x158, 0, 0xc, 0x0}, {0x902c40b4, 0xcf, 0, 0xb, 0x0}, {0x800c40b4, 0xd0, 0, 0xb, 0x0}, {0x81ec40b4, 0xd0, 0, 0xb, 0x0}, {0x81cc40b4, 0xcf, 0, 0xb, 0xffff}};
extern "C" GXOamAttr data_ov130_022935e8[8] = {{0x81904022, 0x14c, 0, 0xc, 0x0}, {0x81b04022, 0x150, 0, 0xc, 0x0}, {0x81d04022, 0x154, 0, 0xc, 0x0}, {0x41f00022, 0x158, 0, 0xc, 0x0}, {0x91e84022, 0xcf, 0, 0xb, 0x0}, {0x81c84022, 0xd0, 0, 0xb, 0x0}, {0x81a84022, 0xd0, 0, 0xb, 0x0}, {0x81884022, 0xcf, 0, 0xb, 0xffff}};
extern "C" const u32 sNumberPadCursorYTable[13] = {0x98, 0x88, 0x88, 0x88, 0x78, 0x78, 0x78, 0x68, 0x68, 0x68, 0x98, 0xb6, 0xb6};
extern "C" const u32 sNumberPadCursorXTable[13] = {0x70, 0x60, 0x80, 0xa0, 0x60, 0x80, 0xa0, 0x60, 0x80, 0xa0, 0xa0, 0xc4, 0x7c};
extern "C" GXOamAttr sSeparatorCellsWide[6] = {{0x2800d0, 0x180, 0, 0x5, 0x0}, {0x1000d0, 0x180, 0, 0x5, 0x0}, {0x2800b8, 0x180, 0, 0x5, 0x0}, {0x1000b8, 0x180, 0, 0x5, 0x0}, {0x2800e8, 0x180, 0, 0x5, 0x0}, {0x1000e8, 0x180, 0, 0x5, 0xffff}};
extern "C" const u32 sKeyX0Table[11] = {0x9, 0x9, 0xe, 0x12, 0x9, 0xe, 0x12, 0x9, 0xe, 0x12, 0x12};
extern "C" const u32 sKeyX1Table[11] = {0x11, 0xd, 0x11, 0x15, 0xd, 0x11, 0x15, 0xd, 0x11, 0x15, 0x15};
extern "C" const u32 sKeyRowTable[11] = {0x12, 0x10, 0x10, 0x10, 0xe, 0xe, 0xe, 0xc, 0xc, 0xc, 0x12};
extern "C" GXOamAttr data_ov130_022934d8[4] = {{0x81aa00f2, 0x15a, 0, 0x4, 0x0}, {0x81ca80f2, 0x15e, 0, 0x4, 0x0}, {0x81aa4012, 0x1da, 0, 0x4, 0x0}, {0x41ca0012, 0x1de, 0, 0x4, 0xffff}};
extern "C" GXOamAttr sSeparatorCells[4] = {{0x2800d8, 0x180, 0, 0x5, 0x0}, {0x1000d8, 0x180, 0, 0x5, 0x0}, {0x2800f0, 0x180, 0, 0x5, 0x0}, {0x1000f0, 0x180, 0, 0x5, 0xffff}};
extern "C" GXOamAttr data_ov130_02293518[4] = {{0x819c009c, 0x15a, 0, 0x4, 0x0}, {0x81bc809c, 0x15e, 0, 0x4, 0x0}, {0x819c40bc, 0x1da, 0, 0x4, 0x0}, {0x41bc00bc, 0x1de, 0, 0x4, 0xffff}};
extern "C" char data_ov130_022934a0[] = "menu/bank/ten0_0_obj.bch";
extern "C" char data_ov130_022934bc[] = "menu/bank/ten0_1_obj.bch";
extern "C" const char *sKeyScreenFiles[6] = {data_ov130_02293430, data_ov130_02293444, data_ov130_022933cc, data_ov130_022933b8, data_ov130_02293458, data_ov130_022933a4};
extern "C" const char *sMainScreenFiles[6] = {data_ov130_022933e0, data_ov130_02293368, data_ov130_022933f4, data_ov130_0229337c, data_ov130_02293408, data_ov130_0229341c};
extern "C" const u32 sDigitColumnTable[6] = {0x16, 0x16, 0x17, 0x17, 0x14, 0x17};
extern "C" const u32 sDigitRowTable[6] = {0x2, 0x6, 0x2, 0x6, 0x7, 0x8};
extern "C" char data_ov130_02293458[] = "menu/bank/f1_bg_us.bsc";
extern "C" char data_ov130_02293430[] = "menu/bank/a1_bg.bsc";
extern "C" char data_ov130_0229341c[] = "menu/bank/h0_bg.bsc";
extern "C" char data_ov130_022933e0[] = "menu/bank/a0_bg.bsc";
extern "C" char data_ov130_022933f4[] = "menu/bank/d0_bg.bsc";
extern "C" char data_ov130_02293408[] = "menu/bank/f0_bg.bsc";
extern "C" char data_ov130_02293444[] = "menu/bank/b1_bg.bsc";
extern "C" char data_ov130_022933b8[] = "menu/bank/e1_bg.bsc";
extern "C" char data_ov130_02293368[] = "menu/bank/b0_bg.bsc";
extern "C" char data_ov130_022933cc[] = "menu/bank/d1_bg.bsc";
extern "C" char data_ov130_0229337c[] = "menu/bank/e0_bg.bsc";
extern "C" u16 sNumberPadKeySeIds[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
extern "C" char data_ov130_022933a4[] = "menu/bank/h1_bg.bsc";
extern "C" const u8 sNumberPadCursorUpTable[16] = {0x01, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x07, 0x08, 0x09, 0x03, 0x0a, 0x00, 0x00, 0x00, 0x00};
extern "C" const u8 sNumberPadCursorDownTable[16] = {0x0b, 0x00, 0x00, 0x0a, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0b, 0x0b, 0x0c, 0x00, 0x00, 0x00};
extern "C" const u8 sNumberPadCursorLeftTable[16] = {0x00, 0x01, 0x01, 0x02, 0x04, 0x04, 0x05, 0x07, 0x07, 0x08, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00};
extern "C" const u8 sNumberPadCursorRightTable[16] = {0x0a, 0x02, 0x03, 0x03, 0x05, 0x06, 0x06, 0x08, 0x09, 0x09, 0x0a, 0x0b, 0x0b, 0x00, 0x00, 0x00};
extern "C" const u8 sNumberPadTouchKeyMap[12] = {0x07, 0x08, 0x09, 0x04, 0x05, 0x06, 0x01, 0x02, 0x03, 0x00, 0x00, 0x0a};
extern "C" const u8 sValueLabelTextIds[8] = {0x55, 0x58, 0x61, 0x5a, 0x5b, 0x5d, 0x52, 0x00};
extern "C" const u8 sBalanceLabelTextIds[8] = {0x56, 0x59, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00};
extern "C" const u8 sTitleTextIds[8] = {0x57, 0x57, 0x57, 0x5e, 0x5b, 0x5c, 0x62, 0x00};
extern "C" char *sTitleObjCharFiles[2] = {data_ov130_022934a0, data_ov130_022934bc};

NumberPad::NumberPad() {}

NumberPad::~NumberPad() {}

void NumberPad::init(u32 mode, u32 a, u32 b) {
    flags = 0;
    entryMode = mode;
    switch (entryMode) {
    case 0:
        layout = 2;
        objVariant = 0;
        break;
    case 1:
        layout = 2;
        objVariant = 5;
        break;
    case 2:
        layout = 2;
        objVariant = 1;
        break;
    case 3:
        layout = 3;
        objVariant = 2;
        break;
    case 4:
        layout = 5;
        objVariant = 3;
        break;
    case 5:
        layout = 3;
        objVariant = 4;
        break;
    case 6:
        layout = 4;
        objVariant = 6;
        break;
    }
    mainLayer = a;
    keyLayer = b;
    NumberPad_ReleaseLabels(this);
    cursorKey = 0xa;
    pressedKey = 0xd;
    highlightTimer = 0;
    repeatTimer = 0;
    value = 0;
    maxValue = 0;
    topAmount = 0;
    bottomAmount = 0;
    PlayerData *c = PlayerData_GetCurrent();
    if (c != NULL) {
        if (c->getPlayerId()->getGender() == 0) {
            Snd_SetKeySeMode(0);
            return;
        }
    }
    Snd_SetKeySeMode(1);
}

void NumberPad_LoadBgGraphics(s32 x) {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/bank/bg0.bch", h, x, 0x10, 0x10, 0xff);
    Gfx2d_LoadCharFile("menu/bank/bg1.bch", h, x, 0x100, 0x100, 0x1a9);
    Gfx2d_LoadPaletteFile("menu/bank/bg.bpl", h, x, 1, 1, 0xd);
}

void NumberPad::loadBg() {
    NumberPad_LoadBgGraphics(mainLayer);
    File_LoadToBuffer(sMainScreenFiles[layout], mainScreen, 0x800);
    switch (entryMode) {
    case 0:
    case 1:
        BgScreen_SetRectPalette(mainScreen, 2, 8, 0xd, 9, 0xa);
        break;
    case 2:
        BgScreen_SetRectPalette(mainScreen, 2, 2, 0xd, 3, 0xa);
        break;
    }
    Gfx2d_LoadScreen((u8 *)mainScreen, mainLayer, 0x800, 0);
    File_LoadToBuffer(sKeyScreenFiles[layout], keyScreen, 0x800);
    Gfx2d_LoadScreen((u8 *)keyScreen, keyLayer, 0x800, 0);
    LabelString *o = NumberPad_AllocLabel(this);
    if (entryMode == 6) {
        String_Load2dMenu(o, 0x51);
    } else {
        String_Load2dMenu(o, 0xb8);
    }
    u32 a = 0xec;
    u32 b = 4;
    if (entryMode == 6) {
        a = 0x14c;
        b = 6;
    }
    o->createLabel(keyLayer, a, b, 0xf, 0, 0);
    o->redrawAligned(1, 0);
    o = NumberPad_AllocLabel(this);
    switch (entryMode) {
    case 2:
        String_Load2dMenu(o, 0x59);
        break;
    case 4:
        String_Load2dMenu(o, 0x50);
        break;
    default:
        String_Load2dMenu(o, 0x54);
        break;
    }
    o->createLabel(keyLayer, 0xb0, 0xa, 0xf, 0, 0);
    o->redrawAligned(1, 0);
    o = NumberPad_AllocLabel(this);
    String_Load2dMenu(o, sValueLabelTextIds[entryMode]);
    o->createLabel(keyLayer, 0xc4, 0xa, 0xf, 0, 0);
    o->redrawAligned(1, 0);
    if (layout == 0 || layout == 2) {
        o = NumberPad_AllocLabel(this);
        String_Load2dMenu(o, sBalanceLabelTextIds[entryMode]);
        o->createLabel(keyLayer, 0xd8, 0xa, 0xf, 0, 0);
        o->redrawAligned(1, 0);
    }
    NumberPad_ResetKeyPalettes(this);
    NumberPad_RedrawValues(this);
}

void NumberPad_LoadObjGraphics(s32 n) {
    Heap *h = gCurrentHeap;
    u32 local;
    Gfx2d_LoadPaletteFile("menu/bank/obj.bpl", h, 8, 4, 4, 0xe);
    Gfx2d_LoadCharFile("menu/bank/obj0.bch", h, 8, 0xc0, 0xc0, 0x15f);
    Gfx2d_LoadCharFile("menu/bank/obj1.bch", h, 8, 0x160, 0x160, 0x1ff);
    u8 *res = (u8 *)File_LoadAlloc(sTitleObjCharFiles[n / 5], h, -4, &local);
    u8 *p = res + (n % 5) * 0xc0;
    s32 c = 0x15a;
    s32 i;
    for (i = 0; i < 6; i++) {
        Gfx2d_LoadCharRange(p, 8, c, c, c + 5);
        p += 0x400;
        c += 0x20;
    }
    Heap_Free(h, res);
    Gfx2d_LoadPaletteFileSlot("menu/bank/ten0.bpl", h, 8, n, 4);
}

void NumberPad::loadObj() {
    NumberPad_LoadObjGraphics(objVariant);
    LabelString *o = NumberPad_AllocLabel(this);
    String_Load2dMenu(o, sTitleTextIds[entryMode]);
    o->createLabel(8, 0x14c, 0xe, 0xf, 0, 0);
    o->redrawAligned(1, 0);
}

void NumberPad::shutdown() {
    NumberPad_ReleaseLabels(this);
    screenTasks[0].cancel();
    screenTasks[1].cancel();
}

void NumberPad::update() {
    NumberPad_ReleaseLabels(this);
    screenTasks[0].cancel();
    screenTasks[1].cancel();
    if (highlightTimer != 0) {
        highlightTimer = highlightTimer - (TICK_STEP_ENDS() ? 1 : 0);
        if (*(volatile u8 *)&highlightTimer == 0) {
            if (repeatTimer != 0) {
                highlightTimer = 1;
            } else {
                NumberPad_UnhighlightKey(this, pressedKey);
            }
        }
    }
}

void NumberPad::flushScreens() {
    if (NumberPad_TestFlags(this, 1)) {
        if (screenTasks[0].requestScreen(mainScreen, mainLayer, 0x800, 0)) {
            NumberPad_ClearFlags(this, 1);
        }
    }
    if (NumberPad_TestFlags(this, 2)) {
        if (screenTasks[1].requestScreen(keyScreen, keyLayer, 0x800, 0)) {
            NumberPad_ClearFlags(this, 2);
        }
    }
}

extern "C" u32 NumberPad_HitTestKey(NumberPad *s, s32 x, s32 y) {
    s32 yy;
    x -= 0x50;
    yy = y - 0x60;
    y = yy;
    if (s->layout == 0 || s->layout == 2) x -= 0x40;
    if (x >= 0 && x < 0x60 && y >= 0 && y < 0x40) {
        s->pressedKey = sNumberPadTouchKeyMap[(x >> 5) + (y >> 4) * 3];
        return s->pressedKey;
    }
    return 13;
}

extern "C" void NumberPad_PressKey(NumberPad *s) {
    NumberPad_ResetKeyPalettes(s);
    NumberPad_HighlightKey(s, s->pressedKey);
    s->repeatTimer = 0xd;
    s->highlightTimer = 5;
    NumberPad_ApplyKey(s);
}

extern "C" void NumberPad_StopKeyRepeat(NumberPad *s) {
    s->repeatTimer = 0;
}

extern "C" BOOL NumberPad_TickKeyRepeat(NumberPad *s) {
    if (s->repeatTimer != 0) {
        s->repeatTimer -= TICK_STEP_ENDS() ? 1 : 0;
        if (s->repeatTimer == 0) {
            s->repeatTimer = 2;
            NumberPad_ApplyKey(s);
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void NumberPad_ResetKeyPalettes(NumberPad *s) {
    s32 x;
    if (s->layout == 0 || s->layout == 2) x = 0x12;
    else x = 0xa;
    BgScreen_SetRectPalette(s->keyScreen, x, 0xc, x + 0xc, 0x13, 2);
    NumberPad_UnhighlightKey(s, 10);
    NumberPad_SetFlags(s, 2);
}

extern "C" void NumberPad_SetKeyPalette(NumberPad *s, u32 idx, s32 n) {
    s32 a = sKeyX0Table[idx];
    s32 b = sKeyX1Table[idx];
    s32 c = sKeyRowTable[idx];
    s32 d = c + 1;
    if (s->layout == 0 || s->layout == 2) {
        a += 8;
        b += 8;
    }
    BgScreen_SetRectPalette(s->keyScreen, a, c, b, d, n);
    NumberPad_SetFlags(s, 2);
}

extern "C" void NumberPad_HighlightKey(NumberPad *s, u32 idx) {
    NumberPad_SetKeyPalette(s, idx, 3);
}

extern "C" void NumberPad_UnhighlightKey(NumberPad *s, u32 idx) {
    s32 n;
    if (idx == 10) n = 1;
    else n = 2;
    NumberPad_SetKeyPalette(s, idx, n);
}

extern "C" u32 NumberPad_GetCursorX(NumberPad *s) {
    u32 t = s->cursorKey;
    u32 v = sNumberPadCursorXTable[t];
    if (s->layout == 0 || s->layout == 2) {
        if (t <= 10) v += 0x40;
    }
    return v;
}

extern "C" u32 NumberPad_GetCursorY(NumberPad *s) {
    return sNumberPadCursorYTable[s->cursorKey];
}

extern "C" BOOL NumberPad_IsCursorOnButton(NumberPad *s) {
    BOOL r = TRUE;
    u32 t = s->cursorKey;
    if (t != 0xb && t != 0xc) r = FALSE;
    return r;
}

extern "C" BOOL NumberPad_MoveCursor(NumberPad *s, u32 p) {
    u32 old;
    if (p == 0) return FALSE;
    old = s->cursorKey;
    if (MenuKeys_HasUp(p)) s->cursorKey = sNumberPadCursorUpTable[s->cursorKey];
    else if (MenuKeys_HasDown(p)) s->cursorKey = sNumberPadCursorDownTable[s->cursorKey];
    if (MenuKeys_HasLeft(p)) s->cursorKey = sNumberPadCursorLeftTable[s->cursorKey];
    else if (MenuKeys_HasRight(p)) s->cursorKey = sNumberPadCursorRightTable[s->cursorKey];
    if (old != s->cursorKey) return TRUE;
    return FALSE;
}

extern "C" BOOL NumberPad_PressCursorKey(NumberPad *s) {
    u32 t = s->cursorKey;
    if ((u8)(t + 0xf5) <= 1) return FALSE;
    s->pressedKey = t;
    NumberPad_PressKey(s);
    return TRUE;
}

extern "C" BOOL NumberPad_IsCursorOnOk(NumberPad *s) {
    if (s->cursorKey == 0xb) return TRUE;
    return FALSE;
}

extern "C" void NumberPad_DrawKeypadFrame(s32 y) {
    y += 0x60;
    Oam_DrawCell(1, data_ov130_02293518, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, data_ov130_02293568, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

extern "C" void NumberPad_Draw(NumberPad *s, s32 y) {
    s32 r4 = y;
    s32 r6 = r4 + 0x60;
    GXOamAttr *t1;
    GXOamAttr *t2;
    if (s->layout == 0 || s->layout == 2) {
        t1 = data_ov130_022934d8;
        t2 = data_ov130_022935e8;
    } else if (s->layout == 4) {
        t1 = data_ov130_02293518;
        t2 = data_ov130_022935a8;
    } else {
        t1 = data_ov130_02293518;
        t2 = data_ov130_02293568;
    }
    if (s->objVariant == 3) r6 += 10;
    Oam_DrawCell(1, t1, 0x80, r6, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, t2, 0x80, r6, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    r4 += 0x60;
    if (s->layout == 4) return;
    if (s->layout == 0 || s->layout == 2) {
        if (s->value >= 1000) Oam_DrawObj(1, sSeparatorCellsWide, 0x80, r4, -1, 2, 0);
        if (s->value >= 1000000) Oam_DrawObj(1, &sSeparatorCellsWide[1], 0x80, r4, -1, 2, 0);
        if (s->shownTopAmount >= 1000) Oam_DrawObj(1, &sSeparatorCellsWide[2], 0x80, r4, -1, 2, 0);
        if (s->shownTopAmount >= 1000000) Oam_DrawObj(1, &sSeparatorCellsWide[3], 0x80, r4, -1, 2, 0);
        if (s->shownBottomAmount >= 1000) Oam_DrawObj(1, &sSeparatorCellsWide[4], 0x80, r4, -1, 2, 0);
        if (s->shownBottomAmount >= 1000000) Oam_DrawObj(1, &sSeparatorCellsWide[5], 0x80, r4, -1, 2, 0);
    } else {
        if (s->layout == 5) r4 -= 8;
        if (s->value >= 1000) Oam_DrawObj(1, &sSeparatorCells[2], 0x80, r4, -1, 2, 0);
        if (s->value >= 1000000) Oam_DrawObj(1, &sSeparatorCells[3], 0x80, r4, -1, 2, 0);
        if (s->shownTopAmount >= 1000) Oam_DrawObj(1, sSeparatorCells, 0x80, r4, -1, 2, 0);
        if (s->shownTopAmount >= 1000000) Oam_DrawObj(1, &sSeparatorCells[1], 0x80, r4, -1, 2, 0);
    }
}

extern "C" void NumberPad_SetAmounts(NumberPad *s, s32 a, s32 b, s32 c) {
    s->maxValue = a;
    s->topAmount = b;
    s->bottomAmount = c;
}

extern "C" s32 NumberPad_GetValue(NumberPad *s) {
    return s->value;
}

extern "C" s32 NumberPad_GetTopAmount(NumberPad *s) {
    return s->topAmount;
}

extern "C" s32 NumberPad_GetBottomAmount(NumberPad *s) {
    return s->bottomAmount;
}

extern "C" void NumberPad_PlayKeySe(u32 idx) {
    Snd_PlayKeySe(sNumberPadKeySeIds[idx]);
}

extern "C" void NumberPad_PlayCancelSe() {
    Snd_PlaySe(0x2a);
}

extern "C" BOOL NumberPad_ClearValue(NumberPad *s) {
    if (s->value == 0) return FALSE;
    s->value = 0;
    NumberPad_PlayCancelSe();
    NumberPad_RedrawValues(s);
    return TRUE;
}

extern "C" void NumberPad_ApplyKey(NumberPad *s) {
    s32 n;
    s32 v = s->value;
    u32 k = s->pressedKey;
    if (k == 10) {
        if (!NumberPad_ClearValue(s)) Snd_PlaySe(0x34);
    } else {
        n = k + v * 10;
        if (n > s->maxValue) n = s->maxValue;
        if (n == v) {
            Snd_PlaySe(0x34);
        } else {
            NumberPad_PlayKeySe(k);
            s->value = n;
            NumberPad_RedrawValues(s);
        }
    }
}

extern "C" void NumberPad_RedrawValues(NumberPad *s) {
    u32 m = s->layout;
    u32 a = sDigitColumnTable[m];
    u32 b = sDigitRowTable[m];
    switch (m) {
    case 4:
        if (s->value == 0) NumberPad_FillSmallDigits(s, 10, a, b, 2);
        else NumberPad_PrintSmallNumber(s, s->value, a, b, 2);
        break;
    case 5:
        if (s->value == 0) {
            NumberPad_PrintSmallNumber(s, 0, a, b, 9);
            NumberPad_FillSmallDigits(s, 10, a, b, 7);
        } else {
            NumberPad_PrintSmallNumber(s, s->value, a, b, 7);
        }
        break;
    default:
        s->shownTopAmount = s->topAmount;
        if (s->layout >= 2) NumberPad_PrintSmallNumber(s, s->shownTopAmount, a, b, 9);
        else NumberPad_PrintLargeNumber(s, s->shownTopAmount, a, b, 6);
        if (s->value == 0) {
            if (s->layout >= 2) NumberPad_FillSmallDigits(s, 10, a, b + 3, 9);
            else NumberPad_FillLargeDigits(s, 10, a, b + 3, 6);
        } else {
            if (s->layout >= 2) NumberPad_PrintSmallNumber(s, s->value, a, b + 3, 9);
            else NumberPad_PrintLargeNumber(s, s->value, a, b + 3, 6);
        }
        if (s->layout == 0 || s->layout == 2) {
            s32 t = s->bottomAmount;
            if (s->entryMode != 0) t += s->value;
            s->shownBottomAmount = t;
            if (s->layout >= 2) NumberPad_PrintSmallNumber(s, s->shownBottomAmount, a, b + 6, 9);
            else NumberPad_PrintLargeNumber(s, s->shownBottomAmount, a, b + 6, 6);
        }
    }
}

extern "C" void NumberPad_FillLargeDigits(NumberPad *s, s32 idx, s32 x, s32 y, s32 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        NumberPad_PutLargeDigit(s, idx, x, y);
        x -= 2;
    }
}

extern "C" void NumberPad_PrintLargeNumber(NumberPad *s, s32 val, s32 x, s32 y, s32 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        if (val == 0) {
            NumberPad_PutLargeDigit(s, 11, x, y);
        } else {
            NumberPad_PutLargeDigit(s, val % 10, x, y);
            val = val / 10;
        }
        x -= 2;
    }
}

extern "C" void NumberPad_PutLargeDigit(NumberPad *s, s32 idx, s32 x, s32 y) {
    u16 b;
    s32 p;
    if (idx != 11) b = (u16)(idx * 4 + 0x84);
    else b = 0x176;
    p = x + y * 32;
    s->mainScreen[p] = (s->mainScreen[p] & 0xfc00) | b;
    s->mainScreen[p + 1] = (s->mainScreen[p + 1] & 0xfc00) | (u16)(b + 1);
    b += 2;
    if (idx == 11) b = 0x176;
    s->mainScreen[p + 0x20] = (s->mainScreen[p + 0x20] & 0xfc00) | b;
    s->mainScreen[p + 0x21] = (s->mainScreen[p + 0x21] & 0xfc00) | (u16)(b + 1);
    NumberPad_SetFlags(s, 1);
}

extern "C" void NumberPad_FillSmallDigits(NumberPad *s, s32 idx, s32 x, s32 y, s32 n) {
    s32 i;
    for (i = 0; i < n; i++) {
        NumberPad_PutSmallDigit(s, idx, x, y);
        x--;
    }
}

extern "C" void NumberPad_PrintSmallNumber(NumberPad *s, s32 val, s32 x, s32 y, s32 n) {
    s32 z = 0;
    s32 i;
    for (i = 0; i < n; i++) {
        if (val == 0) {
            if (i == 0) NumberPad_PutSmallDigit(s, z, x, y);
            else NumberPad_PutSmallDigit(s, 11, x, y);
        } else {
            NumberPad_PutSmallDigit(s, val % 10, x, y);
            val = val / 10;
        }
        x--;
    }
}

extern "C" void NumberPad_PutSmallDigit(NumberPad *s, s32 idx, s32 x, s32 y) {
    s32 p;
    u16 *m;
    u16 t = (u16)(idx * 2 + 0x160);
    p = x + y * 32;
    m = s->mainScreen;
    m[p] = (m[p] & 0xfc00) | t;
    p += 0x20;
    t = (u16)(t + 1);
    m[p] = (m[p] & 0xfc00) | t;
    NumberPad_SetFlags(s, 1);
}

extern "C" void NumberPad_ReleaseLabels(NumberPad *s) {
    s32 i;
    s->labelCount = 0;
    for (i = 0; i < 5; i++) s->labels[i].destroyLabel();
}

extern "C" LabelString *NumberPad_AllocLabel(NumberPad *s) {
    if (s->labelCount >= 5) return &s->labels[4];
    s->labelCount++;
    return &s->labels[s->labelCount - 1];
}

extern "C" BOOL NumberPad_TestFlags(NumberPad *s, u32 m) {
    if ((s->flags & m) != 0) return TRUE;
    return FALSE;
}

extern "C" void NumberPad_SetFlags(NumberPad *s, u32 m) {
    s->flags |= m;
}

extern "C" void NumberPad_ClearFlags(NumberPad *s, u32 m) {
    s->flags &= ~m;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov130_02292360) {
    HOST_OVERLAY_VAR(data_ov130_02293568),
    HOST_OVERLAY_VAR(data_ov130_022935a8),
    HOST_OVERLAY_VAR(data_ov130_022935e8),
    HOST_OVERLAY_VAR(sSeparatorCellsWide),
    HOST_OVERLAY_VAR(data_ov130_022934d8),
    HOST_OVERLAY_VAR(sSeparatorCells),
    HOST_OVERLAY_VAR(data_ov130_02293518),
    HOST_OVERLAY_VAR(data_ov130_022934a0),
    HOST_OVERLAY_VAR(data_ov130_022934bc),
    HOST_OVERLAY_VAR(sKeyScreenFiles),
    HOST_OVERLAY_VAR(sMainScreenFiles),
    HOST_OVERLAY_VAR(data_ov130_02293458),
    HOST_OVERLAY_VAR(data_ov130_02293430),
    HOST_OVERLAY_VAR(data_ov130_0229341c),
    HOST_OVERLAY_VAR(data_ov130_022933e0),
    HOST_OVERLAY_VAR(data_ov130_022933f4),
    HOST_OVERLAY_VAR(data_ov130_02293408),
    HOST_OVERLAY_VAR(data_ov130_02293444),
    HOST_OVERLAY_VAR(data_ov130_022933b8),
    HOST_OVERLAY_VAR(data_ov130_02293368),
    HOST_OVERLAY_VAR(data_ov130_022933cc),
    HOST_OVERLAY_VAR(data_ov130_0229337c),
    HOST_OVERLAY_VAR(sNumberPadKeySeIds),
    HOST_OVERLAY_VAR(data_ov130_022933a4),
    HOST_OVERLAY_VAR(sTitleObjCharFiles),
    HOST_OVERLAY_VARS_END
};
