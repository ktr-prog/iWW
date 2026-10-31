#include "types.h"
#include "ui/LabelString.h"
#include "menu/MenuTextButton.h"
#include "menu/GeneralMenuHeader.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02087e70.h"
#include "proto/ov124/unk_ov124_02296840.h"

#include "nitro/gxoam.h"

GeneralMenuHeader::GeneralMenuHeader() : titleLabel(), iconButton() {}

GeneralMenuHeader::~GeneralMenuHeader() {}

void GeneralMenuHeader::loadTitleBg(s32 a, s32 b) {
    loadBgGfx(a, 5);
    Gfx2d_LoadScreenFile("menu/han/b_bg.bsc", gCurrentHeap, b);
    switch (MenuCtrl_GetMode()) {
    case 4:
    case 7:
    case 10: String_Load2dMenu(&titleLabel[0], 0x3a); break;
    case 5: String_Load2dMenu(&titleLabel[0], 0x90); break;
    case 8:
    case 9: String_Load2dMenu(&titleLabel[0], 0x92); break;
    case 6: String_Load2dMenu(&titleLabel[0], 0x49); break;
    default: String_Load2dMenu(&titleLabel[0], 0x3a); break;
    }
    titleLabel[0].createLabel(a, 0x11, 0xd, 4, 1, 0);
    titleLabel[0].redrawAligned(1, 0);
}

void GeneralMenuHeader::loadBgGfxForStyle(s32 a) {
    loadBgGfx(a, GeneralMenuHeader_GetStyle());
}

void GeneralMenuHeader::placeTitleText() {
    s32 v;
    switch (GeneralMenuHeader_GetStyle()) {
    case 0: v = 0xd; break;
    case 1: v = 8; break;
    case 2: v = 0x14; break;
    case 3: v = 5; break;
    case 4: v = 10; break;
    }
    titleLabel[0].createLabel(3, 0x11, v, 4, 1, 0);
}

void GeneralMenuHeader::redrawTitle() {
    s32 v;
    switch (GeneralMenuHeader_GetStyle()) {
    case 0:
    case 1: v = 0; break;
    case 2:
    case 3:
    case 4: v = 0; break;
    }
    titleLabel[0].redrawAt(v);
}

void GeneralMenuHeader::setTitleText(void *s, s32 n) {
    String_FromEncodedBytes(&titleLabel[0], s, n);
}

void GeneralMenuHeader::setTitleHighlight(u8 a, u8 b, u32 c, u32 d) {
    titleLabel[0].setHighlight(a, b, c, d);
}

extern "C" s32 GeneralMenuHeader_GetStyle() {
    switch (MenuCtrl_GetMode()) {
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b: return 1;
    case 0x15: return 4;
    case 0x12: return 0;
    default: return 0;
    }
}

void GeneralMenuHeader::loadBgGfx(s32 a, s32 b) {
    Heap *heap = gCurrentHeap;
    char buf[0x20];
    Gfx2d_LoadCharFile("menu/han/bg.bch", heap, a, 0x10, 0x10, 0x169);
    Gfx2d_LoadPaletteFile("menu/han/bg.bpl", heap, a, 1, 1, 6);
    switch (MenuCtrl_GetMode()) {
    case 4:
    case 5:
    case 7:
    case 8: pictureIndex = 0; break;
    case 6:
    case 9: pictureIndex = 2; break;
    case 0xb: pictureIndex = 1; break;
    case 0xc: pictureIndex = 3; break;
    case 0xd: pictureIndex = 4; break;
    case 0xe: pictureIndex = 7; break;
    case 0xf:
    case 0x1a:
    case 0x1b: pictureIndex = 5; break;
    case 0x10:
    case 0x18:
    case 0x19: pictureIndex = 6; break;
    case 0x11: pictureIndex = 8; break;
    case 0x12: pictureIndex = 0xe; break;
    case 0x13: pictureIndex = 0xd; break;
    case 0x14: pictureIndex = 0xc; break;
    case 0x15: pictureIndex = 0xb; break;
    case 0x16: pictureIndex = 9; break;
    case 0x17: pictureIndex = 0xa; break;
    case 0xa: pictureIndex = 0xf; break;
    default: pictureIndex = 0; break;
    }
    if (pictureIndex == 0xb || pictureIndex == 0xe) {
        Str_SPrintf(buf, "menu/han/bg%dE.bch", pictureIndex);
    } else {
        Str_SPrintf(buf, "menu/han/bg%d.bch", pictureIndex);
    }
    Gfx2d_LoadCharFile(buf, heap, a, 0x113, 0x113, 0x126);
    Gfx2d_LoadPaletteFileSlot("menu/han/ten0_bg.bpl", heap, a, pictureIndex, 0xe);
    Gfx2d_LoadScreenFile(sGeneralHeaderScreens[b], heap, a);
}

void GeneralMenuHeader::loadObjGfx(s32 v) {
    s32 st = pictureIndex;
    u32 loc;
    Heap *heap = gCurrentHeap;
    u8 *buf = (u8 *)File_LoadAlloc(sGeneralHeaderObjChars[st / 5], heap, -4, &loc);
    u8 *p = buf + (st % 5) * 0xc0;
    s32 i;
    s32 k = 0x15a;
    i = 0;
    do {
        Gfx2d_LoadCharRange(p, 8, k, k, k + 5);
        p += 0x400;
        k += 0x20;
        i++;
    } while (i < 6);
    Heap_Free(heap, buf);
    Gfx2d_LoadPaletteFileSlot("menu/han/ten0_obj.bpl", heap, 8, pictureIndex, v);
    objPalette = v;
    iconButton.setup((GXOamAttr *)data_ov124_02296f90, 14, 2);
    switch (MenuCtrl_GetMode()) {
    case 0xb: iconButton.setLabelNoShadow(0x3b); break;
    case 0xf: iconButton.setLabelNoShadow(0xe6); break;
    case 0x10: iconButton.setLabelNoShadow(0xe7); break;
    case 0x18:
    case 0x19: iconButton.setLabelNoShadow(0xe9); break;
    case 0x1a:
    case 0x1b: iconButton.setLabelNoShadow(0xe8); break;
    case 0xc: iconButton.setLabelNoShadow(0x42); break;
    case 0xd: iconButton.setLabelNoShadow(0x44); break;
    case 0xe: iconButton.setLabelNoShadow(0x48); break;
    case 0x12: iconButton.setLabelNoShadow(0x4e); break;
    case 0x13: iconButton.setLabelNoShadow(0x4d); break;
    case 0x14: iconButton.setLabelNoShadow(0x4f); break;
    case 0x15: iconButton.setLabelNoShadow(0x45); break;
    case 0x16: iconButton.setLabelNoShadow(0x46); break;
    case 0x11: iconButton.setLabelNoShadow(0x4c); break;
    case 0x17: iconButton.setLabelNoShadow(0x41); break;
    }
}

void GeneralMenuHeader::drawPlain(s32 x, s32 y) {
    Oam_DrawCell(1, (GXOamAttr *)data_ov124_02296f50, x + 0x80, y + 0x60, objPalette, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void GeneralMenuHeader::drawWithIcon(s32 x, s32 y) {
    iconButton.drawAt(x, y, -1);
    Oam_DrawCell(1, (GXOamAttr *)data_ov124_02296f70, x + 0x80, y + 0x60, objPalette, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void GeneralMenuHeader::resetFrame() {
    titleLabel[0].destroyLabel();
    iconButton.freeText();
}

extern "C" char *sGeneralHeaderScreens[6] = {data_ov124_02296eac, data_ov124_02296f10, data_ov124_02296efc, data_ov124_02296ee8, data_ov124_02296e84, data_ov124_02296ec0};
extern "C" char data_ov124_02296ec0[20] = "menu/han/e_bg.bsc";
extern "C" char data_ov124_02296e70[20] = "menu/han/obj2.bch";
extern "C" char data_ov124_02296f24[20] = "menu/han/obj3.bch";
extern "C" char *sGeneralHeaderObjChars[4] = {data_ov124_02296e98, data_ov124_02296ed4, data_ov124_02296e70, data_ov124_02296f24};
extern "C" u8 data_ov124_02296f90[64] = {0xb0, 0x40, 0xdb, 0x81, 0x4c, 0xc1, 0x0, 0x0, 0xb0, 0x40, 0xfb, 0x81, 0x50, 0xc1, 0x0, 0x0, 0xb0, 0x40, 0x1b, 0x80, 0x54, 0xc1, 0x0, 0x0, 0xb0, 0x0, 0x3b, 0x40, 0x58, 0xc1, 0x0, 0x0, 0xb0, 0x40, 0x13, 0x80, 0xd0, 0xb0, 0x0, 0x0, 0xb0, 0x40, 0xf3, 0x81, 0xd0, 0xb0, 0x0, 0x0, 0xb0, 0x40, 0x33, 0x90, 0xcf, 0xb0, 0x0, 0x0, 0xb0, 0x40, 0xd3, 0x81, 0xcf, 0xb0, 0xff, 0xff};
extern "C" char data_ov124_02296ee8[20] = "menu/han/f_bg.bsc";
extern "C" char data_ov124_02296e84[20] = "menu/han/g_bg.bsc";
extern "C" char data_ov124_02296f10[20] = "menu/han/c_bg.bsc";
extern "C" char data_ov124_02296eac[20] = "menu/han/a_bg.bsc";
extern "C" char data_ov124_02296efc[20] = "menu/han/d_bg.bsc";
extern "C" char data_ov124_02296ed4[20] = "menu/han/obj1.bch";
extern "C" u8 data_ov124_02296f50[32] = {0xa8, 0x0, 0xe8, 0x81, 0x5a, 0x41, 0x0, 0x0, 0xa8, 0x80, 0x8, 0x80, 0x5e, 0x41, 0x0, 0x0, 0xc8, 0x40, 0xe8, 0x81, 0xda, 0x41, 0x0, 0x0, 0xc8, 0x0, 0x8, 0x40, 0xde, 0x41, 0xff, 0xff};
extern "C" char data_ov124_02296e98[20] = "menu/han/obj0.bch";
extern "C" u8 data_ov124_02296f70[32] = {0xa1, 0x0, 0xa0, 0x81, 0x5a, 0x41, 0x0, 0x0, 0xa1, 0x80, 0xc0, 0x81, 0x5e, 0x41, 0x0, 0x0, 0xc1, 0x40, 0xa0, 0x81, 0xda, 0x41, 0x0, 0x0, 0xc1, 0x0, 0xc0, 0x41, 0xde, 0x41, 0xff, 0xff};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov124_02296840) {
    HOST_OVERLAY_VAR(sGeneralHeaderScreens),
    HOST_OVERLAY_VAR(data_ov124_02296ec0),
    HOST_OVERLAY_VAR(data_ov124_02296e70),
    HOST_OVERLAY_VAR(data_ov124_02296f24),
    HOST_OVERLAY_VAR(sGeneralHeaderObjChars),
    HOST_OVERLAY_VAR(data_ov124_02296f90),
    HOST_OVERLAY_VAR(data_ov124_02296ee8),
    HOST_OVERLAY_VAR(data_ov124_02296e84),
    HOST_OVERLAY_VAR(data_ov124_02296f10),
    HOST_OVERLAY_VAR(data_ov124_02296eac),
    HOST_OVERLAY_VAR(data_ov124_02296efc),
    HOST_OVERLAY_VAR(data_ov124_02296ed4),
    HOST_OVERLAY_VAR(data_ov124_02296f50),
    HOST_OVERLAY_VAR(data_ov124_02296e98),
    HOST_OVERLAY_VAR(data_ov124_02296f70),
    HOST_OVERLAY_VARS_END
};
