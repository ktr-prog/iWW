#include "ds_div.h"
#include "host_overlay_vars.h"
#include "types.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "ui/UiWidget.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "talk/EncodedString.h"
#include "ui/LabelString.h"
#include "ui/LabelBalloon.h"
#include "gfx/BgVramTask.h"
#include "talk/EncodedString8B.h"
#include "menu/MenuTitleBalloon.h"
#include "menu/MenuTownListPanel.h"
#include "talk/MsgString9C.h"
#include "nitro/gxoam.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov139/unk_ov139_02291f60.h"





extern "C" {
BOOL EncodedString_SetRaw(void *, const void *, s32);
void MIi_CpuCopy16(const void *src, void *dst, u32 n);
}

extern "C" GXOamAttr data_ov139_022925c0[4];
extern "C" GXOamAttr data_ov139_022925e0[4];
extern "C" GXOamAttr data_ov139_02292600[4];
extern "C" GXOamAttr data_ov139_02292620[4];
extern "C" GXOamAttr data_ov139_02292640[4];
extern "C" GXOamAttr data_ov139_02292660[4];
extern "C" GXOamAttr data_ov139_022926a0[6];
extern "C" GXOamAttr data_ov139_022926d0[42];


extern "C" GXOamAttr *sTownListCellLists[8] = {data_ov139_022926d0, data_ov139_022926a0, data_ov139_022925c0, data_ov139_022925e0, data_ov139_02292620, data_ov139_02292640, data_ov139_02292600, data_ov139_02292660};
extern "C" GXOamAttr data_ov139_022925c0[4] = {{0x81bf4047, 0x93, 2, 0x8, 0x0}, {0x41df0047, 0x97, 2, 0x8, 0x0}, {0x81d50040, 0x82, 2, 0x8, 0x0}, {0x81b90040, 0x80, 2, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov139_022925e0[4] = {{0x80114047, 0x8d, 2, 0x8, 0x0}, {0x40310047, 0x91, 2, 0x8, 0x0}, {0x80270040, 0x82, 2, 0x8, 0x0}, {0x800b0040, 0x80, 2, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov139_02292600[4] = {{0x81e44048, 0x93, 2, 0x8, 0x0}, {0x40040048, 0x97, 2, 0x8, 0x0}, {0x81fa0041, 0x82, 2, 0x8, 0x0}, {0x81de0041, 0x80, 2, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov139_02292620[4] = {{0x81e84023, 0x8d, 0, 0xa, 0x0}, {0x40080023, 0x91, 0, 0xa, 0x0}, {0x81fe001c, 0x82, 0, 0xa, 0x0}, {0x81e2001c, 0x80, 0, 0xa, 0xffff}};
extern "C" GXOamAttr data_ov139_02292640[4] = {{0x81a34048, 0x99, 2, 0x8, 0x0}, {0x41c30048, 0x9d, 2, 0x8, 0x0}, {0x81b90041, 0x82, 2, 0x8, 0x0}, {0x819d0041, 0x80, 2, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov139_022926d0[42] = {{0x81a800a8, 0x17b, 0, 0xb, 0x0}, {0x41c880a8, 0x17f, 0, 0xb, 0x0}, {0x41a840c8, 0x1fb, 0, 0xb, 0x0}, {0x1c800c8, 0x1ff, 0, 0xb, 0x0}, {0x4030403e, 0xe6, 2, 0x4, 0x0}, {0x4010403e, 0xe6, 2, 0x4, 0x0}, {0x41e8403e, 0xe6, 2, 0x4, 0x0}, {0x41c8403e, 0xe6, 2, 0x4, 0x0}, {0x41a8403e, 0xe6, 2, 0x4, 0x0}, {0x4030402e, 0xe6, 2, 0x4, 0x0}, {0x4010402e, 0xe6, 2, 0x4, 0x0}, {0x41e8402e, 0xe6, 2, 0x4, 0x0}, {0x41c8402e, 0xe6, 2, 0x4, 0x0}, {0x41a8402e, 0xe6, 2, 0x4, 0x0}, {0x4030401e, 0xe6, 2, 0x4, 0x0}, {0x4010401e, 0xe6, 2, 0x4, 0x0}, {0x41e8401e, 0xe6, 2, 0x4, 0x0}, {0x41c8401e, 0xe6, 2, 0x4, 0x0}, {0x41a8401e, 0xe6, 2, 0x4, 0x0}, {0x4030400e, 0xe6, 2, 0x4, 0x0}, {0x4010400e, 0xe6, 2, 0x4, 0x0}, {0x41e8400e, 0xe6, 2, 0x4, 0x0}, {0x41c8400e, 0xe6, 2, 0x4, 0x0}, {0x41a8400e, 0xe6, 2, 0x4, 0x0}, {0x403040fe, 0xe6, 2, 0x4, 0x0}, {0x401040fe, 0xe6, 2, 0x4, 0x0}, {0x41e840fe, 0xe6, 2, 0x4, 0x0}, {0x41c840fe, 0xe6, 2, 0x4, 0x0}, {0x41a840fe, 0xe6, 2, 0x4, 0x0}, {0x403040ee, 0xe6, 2, 0x4, 0x0}, {0x401040ee, 0xe6, 2, 0x4, 0x0}, {0x41e840ee, 0xe6, 2, 0x4, 0x0}, {0x41c840ee, 0xe6, 2, 0x4, 0x0}, {0x41a840ee, 0xe6, 2, 0x4, 0x0}, {0x41bc40d6, 0xcd, 2, 0x5, 0x0}, {0x1dc40d6, 0xd1, 2, 0x5, 0x0}, {0x401440d6, 0xed, 2, 0x5, 0x0}, {0x3440d6, 0xf1, 2, 0x5, 0x0}, {0x902840d5, 0x88, 2, 0x5, 0x0}, {0x801040d5, 0x88, 2, 0x5, 0x0}, {0x91d040d5, 0x88, 2, 0x5, 0x0}, {0x81b840d5, 0x88, 2, 0x5, 0xffff}};
extern "C" GXOamAttr data_ov139_022926a0[6] = {{0x403040ee, 0xc6, 2, 0x5, 0x0}, {0x41a400df, 0x86, 2, 0x5, 0x0}, {0x401040ee, 0xc6, 2, 0x5, 0x0}, {0x41e840ee, 0xc6, 2, 0x5, 0x0}, {0x41c840ee, 0xc6, 2, 0x5, 0x0}, {0x41a840ee, 0xc6, 2, 0x5, 0xffff}};


MenuTownListPanel::MenuTownListPanel() {}

MenuTownListPanel::~MenuTownListPanel() {}

void MenuTownListPanel::init(u8 id, u8 v) {
    bgLayer = id;
    flags = 0;
    titleBalloon.hideNow();
    titleBalloon.showText(v, 0x90, 0x18);
    titleBalloon.showLayer2();
}

void MenuTownListPanel::release() {
    resetTextLabels();
    paletteTask.cancel();
}

void MenuTownListPanel::preStateUpdate() {
    resetTextLabels();
    paletteTask.cancel();
}

void MenuTownListPanel::flushPalette() {
    if (testFlags(1)) {
        if (paletteTask.requestPalette(workPalette, bgLayer, 7)) {
            clearFlags(1);
        }
    }
}

void MenuTownListPanel::drawTitle(s32 a, s32 b) {
    titleBalloon.setPos(a, b);
    titleBalloon.draw();
}

void MenuTownListPanel::loadBgGfx() {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/res/bg.bch", h, bgLayer, 0x11, 0x11, 0x36);
    Gfx2d_LoadPaletteFile("menu/res/bg.bpl", h, bgLayer, 1, 1, 8);
    File_LoadToBuffer("menu/res/bg7.bpl", basePalette, 0x20);
    MIi_CpuCopy16(basePalette, workPalette, 0x20);
}

void MenuTownListPanel::clearAllRows() {
    s32 i;
    for (i = 0; i < 6; i++) {
        setRowTownName(i, NULL, 0xe);
        setRowPlayerName(i, NULL, 0xe);
    }
}

void MenuTownListPanel::loadObjGfx() {
    Heap *h = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/res/obj0.bch", h, 8, 0x80, 0x80, 0xff);
    Gfx2d_LoadCharFile("menu/res/obj1.bch", h, 8, 0x160, 0x160, 0x1ff);
    Gfx2d_LoadPaletteFile("menu/res/obj.bpl", h, 8, 4, 4, 0xd);
}

void MenuTownListPanel::setRowFadeColor(s32 a, s32 x, s32 n, s32 e) {
    u16 c1 = basePalette[15];
    u8 r = c1 & 0x1f;
    u8 g = (c1 & 0x3e0) >> 5;
    u8 b = (c1 & 0x7c00) >> 10;
    s32 d = n - x;
    u16 c2 = basePalette[e];
    r = DS_DIV(((u8)(c2 & 0x1f) * x + r * d), n);
    g = DS_DIV(((u8)((c2 & 0x3e0) >> 5) * x + g * d), n);
    b = DS_DIV(((u8)((c2 & 0x7c00) >> 10) * x + b * d), n);
    workPalette[(u8)(0xe - a)] = r | (g << 5) | (b << 10);
    setFlags(1);
}

void MenuTownListPanel::createLabels() {
    LabelString *t;
    t = allocTextLabel();
    String_Load2dMenu(t, 0x65);
    t->createLabel(8, 0x93, 6, 0xf, 0, 0);
    t->redrawAligned(1, 0);
    t = allocTextLabel();
    String_Load2dMenu(t, 0xc2);
    t->createLabel(8, 0x8d, 6, 0xf, 0, 0);
    t->redrawAligned(1, 0);
    t = allocTextLabel();
    String_Load2dMenu(t, 0xc1);
    t->createLabel(8, 0x99, 6, 0xf, 0, 0);
    t->redrawAligned(1, 0);
    t = allocTextLabel();
    String_Load2dMenu(t, 0xbc);
    t->createSmallLabel(8, 0xcd, 6, 0xe, 0, 0);
    t->redrawAligned(1, 0);
    t = allocTextLabel();
    String_Load2dMenu(t, 0xbd);
    t->createSmallLabel(8, 0xed, 6, 0xe, 0, 0);
    t->redrawAligned(1, 0);
}

void MenuTownListPanel::setRow(s32 i, u8 *str) {
    u8 t = 0xe - i;
    setRowTownName(i, str, t);
    setRowPlayerName(i, str + 8, t);
}

void MenuTownListPanel::clearRow(s32 i) {
    u8 t = 0xe - i;
    setRowTownName(i, NULL, t);
    setRowPlayerName(i, NULL, t);
}

void MenuTownListPanel::resetTextLabels() {
    s32 i;
    labelCount = 0;
    for (i = 0; i < 0x14; i++) {
        textLabels[i].destroyLabel();
    }
}

LabelString *MenuTownListPanel::allocTextLabel() {
    if (labelCount >= 0x14) {
        return &textLabels[19];
    }
    labelCount++;
    return &textLabels[labelCount - 1];
}




EncodedString8B MenuTownListPanel_setRowTownName_sA;
u8 MenuTownListPanel_setRowTownName_sA_init;
MsgString9C MenuTownListPanel_setRowTownName_sB;
u8 MenuTownListPanel_setRowTownName_sB_init;
void MenuTownListPanel::setRowTownName(s32 i, u8 *str, u8 pal) {
    LabelString *t = allocTextLabel();
    if (!MenuTownListPanel_setRowTownName_sA_init) {
        HOST_STATIC_CONSTRUCT(MenuTownListPanel_setRowTownName_sA);
        MenuTownListPanel_setRowTownName_sA_init = 1;
    }
    if (!MenuTownListPanel_setRowTownName_sB_init) {
        HOST_STATIC_CONSTRUCT(MenuTownListPanel_setRowTownName_sB);
        MenuTownListPanel_setRowTownName_sB_init = 1;
    }
    if (str == NULL) {
        t->clear();
    } else {
        EncodedString_SetRaw(&MenuTownListPanel_setRowTownName_sA, str, 8);
        MenuTownListPanel_setRowTownName_sB.fromEncoded(&MenuTownListPanel_setRowTownName_sA, 0, 0);
        String_SetSlot(0, &MenuTownListPanel_setRowTownName_sB);
        String_Load2dMenu(t, 0x66);
    }
    u32 a = i * 0x14 + 0x11e;
    u8 x = 0xf;
    u8 y = 0xe;
    if (pal != 0xff) {
        x = pal;
        y = 0xf;
    }
    t->createLabel(bgLayer, a, 0xa, x, y, 0);
    t->redrawAligned(1, 0);
}



extern "C" GXOamAttr data_ov139_02292660[4] = {{0x80254048, 0x8d, 2, 0x8, 0x0}, {0x40450048, 0x91, 2, 0x8, 0x0}, {0x803b0041, 0x82, 2, 0x8, 0x0}, {0x801f0041, 0x80, 2, 0x8, 0xffff}};

void MenuTownListPanel::setRowPlayerName(s32 i, u8 *str, u8 pal) {
    LabelString *t = allocTextLabel();
    if (str == NULL) {
        t->clear();
    } else {
        String_FromEncodedBytes(t, str, 8);
    }
    u32 a = i * 16 + 0x1d2;
    u8 x = 0xf;
    u8 y = 0xe;
    if (pal != 0xff) {
        x = pal;
        y = 0xf;
    }
    t->createLabel(bgLayer, a, 8, x, y, 0);
    t->redrawAligned(1, 0);
}

GXOamAttr *MenuTownListPanel::getCellList(s32 i) { return sTownListCellLists[i]; }

BOOL MenuTownListPanel::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void MenuTownListPanel::setFlags(u32 m) { flags |= m; }

void MenuTownListPanel::clearFlags(u32 m) { flags &= ~m; }





#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov139_02291f60) {
    HOST_OVERLAY_VAR(sTownListCellLists),
    HOST_OVERLAY_VAR(data_ov139_022925c0),
    HOST_OVERLAY_VAR(data_ov139_022925e0),
    HOST_OVERLAY_VAR(data_ov139_02292600),
    HOST_OVERLAY_VAR(data_ov139_02292620),
    HOST_OVERLAY_VAR(data_ov139_02292640),
    HOST_OVERLAY_VAR(data_ov139_022926d0),
    HOST_OVERLAY_VAR(data_ov139_022926a0),
    HOST_OVERLAY_VAR(MenuTownListPanel_setRowTownName_sA),
    HOST_OVERLAY_VAR(MenuTownListPanel_setRowTownName_sA_init),
    HOST_OVERLAY_VAR(MenuTownListPanel_setRowTownName_sB),
    HOST_OVERLAY_VAR(MenuTownListPanel_setRowTownName_sB_init),
    HOST_OVERLAY_VAR(data_ov139_02292660),
    HOST_OVERLAY_VARS_END
};
