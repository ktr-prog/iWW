#include "types.h"
#include "host_tick.h"
#include "menu/InventoryGridTypes.h"
#include "menu/InventoryBg.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "player/PlayerInventory.h"
#include "talk/MsgString.h"
#include "talk/MsgString9B.h"
#include "talk/MsgString9C.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020637e4.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov094/unk_ov094_02292360.h"

#define IN(x, lo, hi) ((x) >= (lo) && (x) <= (hi))

InventoryBg::InventoryBg() {}

InventoryBg::~InventoryBg() {}

#define data_ov094_02294888 "menu/inventory/itmp/m%d.bch"
#define data_ov094_022948a4 "menu/inventory/itmp/w%d.bch"
#define data_ov094_022948c0 "menu/inventory/b_obj_itm.bpl"
#define data_ov094_022948e0 "menu/icon/b_obj_itm.bpl"
#define data_ov094_022948f8 "menu/inventory/obj0.bch"
#define data_ov094_02294910 "menu/inventory/obj1.bch"
#define data_ov094_02294928 "menu/inventory/b_itm2.bch"
#define data_ov094_02294944 "menu/inventory/b_itm9.bpl"
#define data_ov094_02294960 "menu/inventory/b_itmb.bpl"
#define data_ov094_0229497c "menu/inventory/b_obj_itm6.bpl"
#define data_ov094_0229499c "menu/inventory/b_itm.bpl"
#define data_ov094_022949b8 "menu/inventory/b_itm_bg_a.bsc"
#define data_ov094_022949d8 "menu/inventory/b_itm_bg_c.bsc"
#define data_ov094_022949f8 "menu/inventory/b_itm0.bch"
#define data_ov094_02294a14 "menu/inventory/b_itm1.bch"

extern "C" {

OamObjTemplate sInventoryBgSprite = {{0xf8, 0x00, 0xc3, 0x01, 0xfa, 0x61, 0xff, 0xff}};

void InventoryBg_Init(InventoryBg *p, u32 v) {
    p->bgId = v;
    p->dirtyFlags = 0;
    InventoryBg_ResetBells(p);
    p->paintedHighlight = 2;
    p->highlight = 2;
    p->pictureIndex = 8;
}

void InventoryBg_Load(InventoryBg *p, s32 flag) {
    InventoryBg_LoadBg(p, flag);
    InventoryBg_LoadGraphics(p);
}

void InventoryBg_LoadBg(InventoryBg *p, s32 flag) {
    void *h = gCurrentHeap;
    Gfx2d_LoadPaletteFile(data_ov094_0229499c, h, p->bgId, 0, 1, 0xd);
    File_LoadToBuffer(flag ? data_ov094_022949b8 : data_ov094_022949d8, p->screen, 0x800);
    Gfx2d_LoadScreen((u8 *)p->screen, p->bgId, 0x800, 0);
    Gfx2d_LoadCharFile(data_ov094_022949f8, h, p->bgId, 0, 0x10, 0xff);
    Gfx2d_LoadCharFile(data_ov094_02294a14, h, p->bgId, 0x100, 0x100, 0x1ff);
}

void InventoryBg_LoadGraphics(InventoryBg *p)
{
    Gfx2d_LoadCharFile(data_ov094_02294928, gCurrentHeap, p->bgId, 0x200, 0x200, 0x2ff);
    InventoryBg_SetupTextWindows(p);
    InventoryBg_ResetBells(p);
    InventoryBg_LoadPictureForHeldItem(p);
    File_LoadToBuffer(data_ov094_02294944, p->palette, 0x20);
    p->bellsColorA = p->bellsColor;
    File_LoadToBuffer(data_ov094_02294960, p->palette, 0x20);
    p->bellsColorB = p->bellsColor;
    File_LoadToBuffer(data_ov094_0229497c, p->palette, 0x20);
}

void InventoryBg_SetupTextWindows(InventoryBg *p)
{
    PlayerId *r = PlayerData_GetCurrent()->getPlayerId();
    MsgString9C townName;
    TownId_GetNameString(PlayerId_GetTownId(r), &townName);
    String_SetSlot(0, &townName);
    p->textWindows[0].createLabel(p->bgId, 0x11, 0xa, 0xf, 0xc, 0);
    String_Load2dMenu(&p->textWindows[0], 0x66);
    p->textWindows[0].redrawAligned(1, 0);
    MsgString9B playerName;
    r->getNameString(&playerName);
    p->textWindows[1].createLabel(p->bgId, 0x25, 8, 0xf, 0xc, 0);
    p->textWindows[1].copy(&playerName);
    p->textWindows[1].redrawAligned(1, 0);
}

void InventoryBg_LoadObjGraphics()
{
    void *g = gCurrentHeap;
    Gfx2d_LoadPaletteFile(data_ov094_022948c0, g, 8, 4, 4, 6);
    Gfx2d_LoadPaletteFile(data_ov094_022948e0, g, 8, 7, 7, 0xe);
    Gfx2d_LoadCharFile(data_ov094_022948f8, g, 8, 0xc0, 0xc0, 0x15f);
    Gfx2d_LoadCharFile(data_ov094_02294910, g, 8, 0x160, 0x160, 0x1ff);
}

void InventoryBg_PreUpdate(InventoryBg *p)
{
    InventoryBg_CancelUploads(p);
    InventoryBg_ClearTextWindows(p);
}

void InventoryBg_Update(InventoryBg *p)
{
    InventoryBg_UpdateBells(p);
    InventoryBg_UpdateHighlight(p);
    InventoryBg_UploadScreen(p);
    InventoryBg_UploadPicture(p);
    InventoryBg_UploadPalette(p);
}

void InventoryBg_Exit(InventoryBg *p)
{
    InventoryBg_CancelUploads(p);
    InventoryBg_ClearTextWindows(p);
    if (p->bellRollTimer != 0) {
        Snd_StopSe(0x2d, 1);
    }
}

void InventoryBg_CancelUploads(InventoryBg *p)
{
    for (s32 i = 0; i < 3; i++) {
        p->vramTasks[i].cancel();
    }
}

void InventoryBg_ClearTextWindows(InventoryBg *p)
{
    for (s32 i = 0; i < 2; i++) {
        p->textWindows[i].destroyLabel();
    }
}

void InventoryBg_UploadScreen(InventoryBg *p)
{
    if (InventoryBg_IsDirty(p, 1)) {
        if (p->vramTasks[0].requestScreen(p->screen, p->bgId, 0x800, 0)) {
            InventoryBg_ClearDirty(p, 1);
        }
    }
}

void InventoryBg_PaintNormal(InventoryBg *p)
{
    BgScreen_SetRectPalette(p->screen, 0xe, 3, 0x17, 0xc, 2);
    InventoryBg_SetDirty(p, 1);
}

void InventoryBg_PaintHighlight0(InventoryBg *p)
{
    BgScreen_SetRectPalette(p->screen, 0xe, 3, 0x17, 0xc, 7);
}

void InventoryBg_PaintHighlight1(InventoryBg *p)
{
    BgScreen_SetRectPalette(p->screen, 0xe, 3, 0x17, 0xc, 6);
}

void InventoryBg_LoadPictureForHeldItem(InventoryBg *p)
{
    PlayerData *a = PlayerData_GetCurrent();
    s32 b = ((PlayerId *)(a->getPlayerId()))->getGender();
    u16 *pv = a->getHeldItem();
    s32 idx = 0;
    BOOL fl = FALSE;
    u32 v = *pv;
    if (IN(v, 0x1369, 0x1369)) {
        fl = TRUE;
    }
    if (fl || IN(v, 0x136a, 0x136a)) {
        idx = 1;
    } else if (IN(v, 0x136b, 0x1372) || IN(v, 0x1373, 0x1373)) {
        idx = 2;
    } else if (IN(v, 0x1374, 0x1374) || IN(v, 0x1375, 0x1375)) {
        idx = 3;
    } else if (IN(v, 0x1380, 0x139f) || IN(v, 0x13a0, 0x13a7)) {
        idx = 4;
    } else if (IN(v, 0x1377, 0x1377) || IN(v, 0x1376, 0x1376)) {
        idx = 5;
    } else if (IN(v, 0x1379, 0x1379) || IN(v, 0x1378, 0x1378)) {
        idx = 6;
    } else if (IN(v, 0x137a, 0x137a) || IN(v, 0x137b, 0x137b)) {
        idx = 7;
    }
    InventoryBg_LoadPicture(p, idx, b);
}

void InventoryBg_LoadPicture(InventoryBg *p, s32 a, s32 b)
{
    char buf[0x2c];
    if (b == 0) {
        Str_SPrintf(buf, data_ov094_02294888, a);
    } else {
        Str_SPrintf(buf, data_ov094_022948a4, a);
    }
    File_LoadToBuffer(buf, p->picture, 0xc80);
    p->pictureIndex = a;
    InventoryBg_SetDirty(p, 4);
}

void InventoryBg_UploadPicture(InventoryBg *p)
{
    if (InventoryBg_IsDirty(p, 4)) {
        if (p->vramTasks[1].requestChars(p->picture, p->bgId, 0x35, 0x35, 0x98)) {
            InventoryBg_ClearDirty(p, 4);
        }
    }
}

void InventoryBg_UploadPalette(InventoryBg *p)
{
    if (InventoryBg_IsDirty(p, 8)) {
        if (p->vramTasks[2].requestPalette(p->palette, 8, 6)) {
            InventoryBg_ClearDirty(p, 8);
        }
    }
}

void InventoryBg_DrawSprite(InventoryBg *p, s32 y)
{
    Oam_DrawObj(1, &sInventoryBgSprite, 0x80, y + 0x60, -1, 2, NULL);
}

void InventoryBg_StartBlink(InventoryBg *p, u32 v)
{
    p->blinkHighlight = v;
    p->blinkTimer = 14;
}

BOOL InventoryBg_UpdateBlink(InventoryBg *p)
{
    if (p->blinkTimer != 0) {
        p->blinkTimer = p->blinkTimer - (TICK_STEP_ENDS() ? 1 : 0);
        switch (p->blinkTimer % 5) {
        case 3:
            InventoryBg_SetHighlight(p, p->blinkHighlight);
            break;
        case 0:
            InventoryBg_ResetHighlight(p);
            break;
        }
        goto zero;
    }
    return TRUE;
zero:
    return FALSE;
}

void InventoryBg_StopBlink(InventoryBg *p)
{
    p->blinkTimer = 0;
    InventoryBg_ResetHighlight(p);
}

void InventoryBg_StartBellRoll(InventoryBg *p, u32 v)
{
    s32 t = InventoryBg_GetTotalBells();
    s32 c = p->shownBells;
    if (t != c) {
        s32 d;
        if (t > c) {
            d = t - c;
        } else {
            d = c - t;
        }
        if (d < 30) {
            p->bellRollTimer = 1;
        } else {
            p->bellRollTimer = 14;
            p->bellStep = d / 13;
            if (p->bellStep % 5 == 0) {
                p->bellStep = p->bellStep - 1;
            }
            if (p->bellStep <= 1) {
                p->bellRollTimer = 1;
            }
            InventoryBg_SetBellsPanelMode(p, v);
            Snd_PlaySeOnHandle(0x2d);
        }
    }
}

void InventoryBg_SetBellsPanelMode(InventoryBg *p, u32 n)
{
    s32 x = 7;
    s32 y = 9;
    s32 z = 9;
    switch (n) {
    case 0:
        break;
    case 1:
        z = 8;
        x = y;
        break;
    case 2:
        z = 8;
        x = z;
        break;
    case 3:
        z = 8;
        break;
    }
    BgScreen_SetRectPalette(p->screen, x, 10, 11, 11, z);
    InventoryBg_SetDirty(p, 8);
    switch (n) {
    case 0:
    case 1:
        p->bellsColor = p->bellsColorA;
        break;
    case 2:
    case 3:
        p->bellsColor = p->bellsColorB;
        break;
    }
    InventoryBg_SetDirty(p, 1);
}

s32 InventoryBg_GetTotalBells()
{
    return ((PlayerInventory *)(PlayerData_GetCurrent()->getInventory()))->getTotalBells(0);
}

void InventoryBg_ResetBells(InventoryBg *p)
{
    p->shownBells = InventoryBg_GetTotalBells();
    p->bellRollTimer = 0;
    InventoryBg_SetDirty(p, 2);
}

void InventoryBg_UpdateBells(InventoryBg *p)
{
    s32 t = InventoryBg_GetTotalBells();
    if (p->bellRollTimer != 0) {
        p->bellRollTimer = p->bellRollTimer - (TICK_STEP_ENDS() ? 1 : 0);
        if (p->bellRollTimer == 0) {
            p->shownBells = t;
            InventoryBg_SetBellsPanelMode(p, 0);
            Snd_StopSe(0x2d, 1);
            Snd_PlaySe(0x3e);
        } else {
            s32 c = p->shownBells;
            if (c < t) {
                p->shownBells = c + p->bellStep;
            } else {
                p->shownBells = c - p->bellStep;
            }
        }
        InventoryBg_SetDirty(p, 2);
    }
    if (InventoryBg_IsDirty(p, 2)) {
        s32 v = p->shownBells;
        InventoryBg_SetDirty(p, 1);
        u16 *q = &p->screen[0x14b];
        s32 i;
        for (i = 0; i < 5; i++) {
            s32 base;
            if (i < 3) {
                base = 0x2ec;
            } else {
                base = 0x2d8;
            }
            s32 d = v % 10 * 2;
            d += base;
            *q = (*q & 0xfc00) | d;
            q[0x20] = (q[0x20] & 0xfc00) | (d + 1);
            q--;
            v = v / 10;
        }
        InventoryBg_ClearDirty(p, 2);
    }
}

BOOL InvItem_IsTurnipFishOrInsect(u32 v)
{
    if (IN(v, 0x1531, 0x153a) || IN(v, 0x153b, 0x1541) || IN(v, 0x154a, 0x1553) ||
        IN(v, 0x12e8, 0x131f) || IN(v, 0x12b0, 0x12e7)) {
        return TRUE;
    }
    return FALSE;
}

void InventoryBg_UpdateHighlight(InventoryBg *p)
{
    u32 a = p->highlight;
    if (a != p->paintedHighlight) {
        p->paintedHighlight = a;
        InventoryBg_PaintNormal(p);
        u32 b = p->paintedHighlight;
        switch (b) {
        case 0:
            InventoryBg_PaintHighlight0(p);
            break;
        case 1:
            InventoryBg_PaintHighlight1(p);
            break;
        }
    }
}

void InventoryBg_SetHighlight(InventoryBg *p, u32 v)
{
    p->highlight = v;
}

void InventoryBg_ResetHighlight(InventoryBg *p)
{
    p->highlight = 2;
}

BOOL InvItem_IsDeliveryItem(u32 v)
{
    if (IN(v, 0x155f, 0x1560) || IN(v, 0x1561, 0x1564)) {
        return TRUE;
    }
    return FALSE;
}

BOOL InvItem_IsDeliveryParcel(u32 v)
{
    if (IN(v, 0x155f, 0x1560)) {
        return TRUE;
    }
    return FALSE;
}

BOOL InvItem_IsNonTransferable(u32 v)
{
    if (IN(v, 0x155d, 0x155d)) {
        return TRUE;
    }
    return FALSE;
}

BOOL InvItem_IsNotFishInsectOrFlower(u32 v)
{
    if (IN(v, 0x12e8, 0x131f) || IN(v, 0x12b0, 0x12e7)) {
        return FALSE;
    }
    if (IN(v, 0x137c, 0x137c) || IN(v, 0x1408, 0x1428) || IN(v, 0x1471, 0x1491)) {
        return FALSE;
    }
    return TRUE;
}

void Inventory_PlayPutDownSe()
{
    Snd_PlaySe(14);
}

void Inventory_PlayTouchSe()
{
    Snd_PlaySe(12);
}

void Inventory_PlayPickUpSe()
{
    Snd_PlaySe(13);
}

s32 InventoryBg_IsDirty(InventoryBg *p, u32 m)
{
    if (p->dirtyFlags & m) {
        return TRUE;
    }
    return FALSE;
}

void InventoryBg_SetDirty(InventoryBg *p, u32 m)
{
    p->dirtyFlags = p->dirtyFlags | m;
}

void InventoryBg_ClearDirty(InventoryBg *p, u32 m)
{
    p->dirtyFlags = p->dirtyFlags & ~m;
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov094_02292360) {
    HOST_OVERLAY_VAR(sInventoryBgSprite),
    HOST_OVERLAY_VARS_END
};
