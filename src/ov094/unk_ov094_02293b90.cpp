#include "types.h"
#include "host_tick.h"
#include "menu/InventoryGridTypes.h"
#include "menu/LetterGrid.h"
#include "item/LetterView.h"
#include "player/PlayerData.h"
#include "player/PlayerInventory.h"
#include "talk/LabelBalloonText.h"
#include "talk/MsgString9B.h"
#include "ui/LabelBalloon.h"
#include "ui/LabelString.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"

extern "C" {

extern "C" const u8 sLetterPopScales[4] = {0x02, 0x04, 0x06, 0x08};
extern "C" const u32 sLetterCursorLift[3] = {0xfffffffe, 0xfffffffd, 0xfffffffb};
extern "C" const u8 sLetterKindMsgIds[20] = {0x00, 0x3e, 0x3f, 0x9e, 0x9f, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xb9, 0xba, 0xbb, 0x9b, 0x4b, 0xa4, 0x00};
extern "C" u8 sLetterGridColumnX[5] = {0x2c, 0x44, 0x5c, 0x74, 0x8c};
extern "C" OamObjTemplate sLetterIconSprite = {{0x00, 0x00, 0x00, 0x40, 0x5a, 0x61, 0xff, 0xff}};
extern "C" u8 sLetterIconPalettes[16] = {0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06};
extern "C" OamObjTemplate sLetterMarkSprites[3] = {{{0x00, 0x00, 0x00, 0x80, 0x48, 0x41, 0x00, 0x00}}, {{0x02, 0x00, 0x02, 0x80, 0x48, 0x11, 0xff, 0xff}}, {{0x00, 0x00, 0x00, 0x80, 0x50, 0x61, 0xff, 0xff}}};
extern "C" u16 sLetterIconChars[16] = {0x140, 0x142, 0x140, 0x142, 0x180, 0x182, 0x1d2, 0x1d6, 0x1d2, 0x1d6, 0x1d4, 0x1d8, 0x140, 0x142, 0x180, 0x182};
extern "C" char data_ov094_02294c14[] = "menu/inventory/b_itm_ten0_obj.bpl";

LetterGrid::LetterGrid() {
}

LetterGrid::~LetterGrid() {
}

void LetterGrid::init(s32 x) {
    LetterGrid_ClearBits(occupiedBits.words);
    LetterGrid_ClearBits(markedBits.words);
    LetterGrid_ClearBits(highlightedBits.words);
    cursorSlot = 0x37;
    cursorLiftTimer = 0;
    objPriority = x;
    letterArray = NULL;
    heldScale = 10;
}

void LetterGrid::updateCursorLift() {
    if (cursorLiftTimer != 0) {
        cursorLiftTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
}

u32 LetterGrid::findPocketLetterAt(s32 a, s32 b) {
    if (a < 0xc0) {
        return 0x37;
    }
    return findLetterInRange(a, b, 0, 9);
}

u32 LetterGrid::findLetterAt2D(s32 a, s32 b) {
    if (a > 0xa0 || a < 0x60) {
        return 0x37;
    }
    return findLetterInRange(a, b, 0x2d, 0x36);
}

u32 LetterGrid::findLetterAt0A(s32 a, s32 b) {
    return findLetterInRange(a, b, 0xa, 0x22);
}

u32 LetterGrid::findLetterAt23(s32 a, s32 b) {
    return findLetterInRange(a, b, 0x23, 0x2c);
}

u32 LetterGrid::findLetterInRange(s32 a, s32 b, s32 start, u8 end) {
    s32 i;
    s32 x0 = a - 0x14;
    s32 x1 = a + 4;
    s32 y0 = b - 0x14;
    s32 y1 = b + 4;
    for (i = start; i <= end; i++) {
        s32 x = LetterGrid_GetSlotX(this, i);
        if (x0 < x && x < x1) {
            s32 y = LetterGrid_GetSlotY(this, i);
            if (y0 < y && y < y1) {
                return (u8)i;
            }
        }
    }
    return 0x37;
}

void LetterGrid::setBalloonLetterText(LabelBalloon *out, LetterView *o) {
    LabelString text;
    MsgString9B name;
    LabelBalloonText toText;
    LabelBalloonText fromText;
    s32 t = o->getState();
    s32 k = Letter_GetKind(o);
    if (k == 0x11) {
        Letter_GetSenderName(o, &name);
        String_SetSlot(1, &name);
        String_Load2dMenu(&text, 0x4b);
    } else if (k == 0) {
        Letter_GetSenderName(o, &name);
        String_SetSlot(1, &name);
        if (t == 4) {
            String_Load2dMenu(&text, 0x4b);
        } else {
            String_Load2dMenu(&text, 0x3d);
        }
    } else {
        String_Load2dMenu(&text, sLetterKindMsgIds[k]);
    }
    StrBuf_Copy((StrBuf *)&fromText, (StrBuf *)&text);
    if (Letter_IsBottle(o) != 0) {
        LabelString bottle;
        String_Load2dMenu(&bottle, 0x43);
        String_SetSlot(0, &bottle);
    } else {
        Letter_GetRecipientName(o, &name);
        String_SetSlot(0, &name);
    }
    String_Load2dMenu(&text, 0x3c);
    StrBuf_Copy((StrBuf *)&toText, (StrBuf *)&text);
    switch (t) {
    case 1:
    case 4:
    case 7:
    case 8:
        out->setText((StrBuf *)&toText);
        break;
    default:
        out->setText((StrBuf *)&fromText);
        break;
    }
}

void LetterGrid::showLetterName(LabelBalloon *out, s32 idx) {
    setBalloonLetterText(out, getLetter(idx));
}

BOOL LetterGrid::isCursorSlot(s32 v) {
    if (v == cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

u32 LetterGrid::getCursorLift() {
    return sLetterCursorLift[cursorLiftTimer];
}

void LetterGrid::clearCursorSlot() {
    cursorSlot = 0x37;
}

void LetterGrid::setCursorSlot(u32 v) {
    if (isHighlighted((u8)v)) {
        clearCursorSlot();
    } else if (cursorSlot != v) {
        cursorSlot = v;
        cursorLiftTimer = 2;
    }
}

void LetterGrid::clearMarks() {
    LetterGrid_ClearBits(markedBits.words);
}

void LetterGrid::markSlot(s32 i) {
    LetterGrid_SetBit(markedBits.words, i);
}

LetterView *LetterGrid::getLetter(s32 i) {
    PlayerInventory *inv = (PlayerInventory *)PlayerData_GetCurrent()->getInventory();
    if (i >= 0 && i <= 9) {
        return (LetterView *)inv->getLetter(i);
    }
    if (i >= 10 && i <= 0x22) {
        return letterArray + (i - 10);
    }
    if (i >= 0x23 && i <= 0x2c) {
        return letterArray + (i - 0x23);
    }
    if (i >= 0x2d && i <= 0x36) {
        return letterArray + (i - 0x2d);
    }
    return NULL;
}

void LetterGrid::setLetter(s32 i, const void *letter) {
    Letter_Copy(getLetter(i), (const LetterView *)letter);
    LetterGrid_SetBit(occupiedBits.words, i);
}

void LetterGrid::clearLetter(s32 i) {
    Letter_Clear(getLetter(i));
    LetterGrid_ClearBit(occupiedBits.words, i);
}

void LetterGrid::highlightLetterKinds(u32 flags) {
    u8 i;
    u32 f1, f8, f2, f4;
    LetterGrid_ClearBits(highlightedBits.words);
    i = 0;
    f1 = flags & 1;
    f8 = flags & 8;
    f2 = flags & 2;
    f4 = flags & 4;
    do {
        s32 t = getLetter(i)->getState();
        switch (t) {
        case 1:
            if (f1 != 0) {
                setHighlighted(i);
            }
            break;
        case 4:
            if (f8 != 0 || f1 != 0) {
                setHighlighted(i);
            }
            break;
        case 2:
        case 3:
        case 5:
        case 6:
            if (f2 != 0) {
                setHighlighted(i);
            }
            break;
        case 7:
        case 8:
            if (f4 != 0) {
                setHighlighted(i);
            }
            break;
        }
        i++;
    } while (i <= 9);
    Heap *g = gCurrentHeap;
    if (f1 != 0) {
        Gfx2d_LoadPaletteFile(data_ov094_02294c14, g, 8, 4, 4, 4);
    }
    if (f2 != 0) {
        Gfx2d_LoadPaletteFile(data_ov094_02294c14, g, 8, 4, 5, 5);
    }
    if (f4 != 0) {
        Gfx2d_LoadPaletteFile(data_ov094_02294c14, g, 8, 4, 6, 6);
    }
}

BOOL LetterGrid::isHighlighted(s32 i) {
    return LetterGrid_TestBit(highlightedBits.words, i);
}

void LetterGrid::setHighlighted(s32 i) {
    LetterGrid_SetBit(highlightedBits.words, i);
}

void LetterGrid::drawPocketLetters(s32 a, s32 b) {
    LetterView *rec = (LetterView *)((PlayerInventory *)PlayerData_GetCurrent()->getInventory())->getLetter(0);
    s32 idx = 0;
    for (s32 i = 0; i < 10; i++) {
        LetterGrid_DrawSlot(this, rec, idx, a, b);
        rec++;
        idx++;
    }
}

void LetterGrid::drawLetters0A(s32 a, s32 b) {
    LetterView *rec = letterArray;
    s32 idx = 10;
    s32 i = 0;
    for (; i < 0x19; i++) {
        LetterGrid_DrawSlot(this, rec, idx, a, b);
        rec++;
        idx++;
    }
}

void LetterGrid::drawLetters23(s32 a, s32 b) {
    LetterView *rec = letterArray;
    s32 idx = 0x23;
    s32 i = 0;
    for (; i < 10; i++) {
        LetterGrid_DrawSlot(this, rec, idx, a, b);
        rec++;
        idx++;
    }
}

void LetterGrid::drawLetters2D(s32 a, s32 b) {
    LetterView *rec = letterArray;
    s32 idx = 0x2d;
    s32 i = 0;
    for (; i < 10; i++) {
        LetterGrid_DrawSlot(this, rec, idx, a, b);
        rec++;
        idx++;
    }
}

void LetterGrid::drawHeldLetter(s32 a, s32 b, void *letter) {
    LetterView *o = (LetterView *)letter;
    if (heldScale != 0) {
        s32 t = InventoryItemGrid_GetScale(heldScale);
        if (t == 0x1000) {
            drawLetterIcon(a, b, getLetterPalette(o), o, NULL);
            drawUnderlay(a, b, getLetterPalette(o), NULL);
            drawFocus(a, b, NULL);
        } else {
            s32 v[4];
            v[0] = t;
            v[1] = 0;
            v[2] = 0;
            v[3] = t;
            drawLetterIcon(a, b, getLetterPalette(o), o, v);
            drawUnderlay(a, b, getLetterPalette(o), v);
        }
    }
}

s32 LetterGrid::getLetterPalette(LetterView *o) {
    s32 t = LetterGrid_GetIconIndex(this, o);
    s32 r = -1;
    if (t != r) {
        r = sLetterIconPalettes[t];
    }
    return r;
}

void LetterGrid::drawLetterIcon(s32 a, s32 b, u32 c, LetterView *e, s32 *mtx) {
    s32 idx = LetterGrid_GetIconIndex(this, e);
    if (idx != -1) {
        sLetterIconSprite.setPalette((u8)c);
        sLetterIconSprite.setCharName(sLetterIconChars[idx]);
        Oam_DrawObj(1, &sLetterIconSprite, a, b, -1, objPriority, mtx);
    }
}

void LetterGrid::drawMark(s32 a, s32 b) {
    Oam_DrawObj(1, &sLetterMarkSprites[2], a - 8, b - 8, -1, objPriority, NULL);
}

void LetterGrid::drawUnderlay(s32 a, s32 b, s32 c, s32 *mtx) {
    Oam_DrawObj(1, &sLetterMarkSprites[0], a - 8, b - 8, c, objPriority, mtx);
}

void LetterGrid::drawFocus(s32 a, s32 b, s32 *mtx) {
    Oam_DrawObj(1, &sLetterMarkSprites[1], a - 8, b - 8, -1, objPriority, mtx);
}

void LetterGrid_DrawSlot(LetterGrid *o, LetterView *letter, s32 idx, s32 x, s32 y0)
{
    s32 t;
    s32 y;
    x += LetterGrid_GetSlotX(o, idx);
    y = y0 + LetterGrid_GetSlotY(o, idx);
    if (x >= -0x18) {
        if (LetterGrid_TestBit(o->markedBits.words, idx) != 0) {
            o->drawMark(x, y);
        }
        if (LetterGrid_TestBit(o->occupiedBits.words, idx) != 0) {
            if (o->isCursorSlot(idx) != 0) {
                s32 w = o->getCursorLift();
                x += w;
                y += w;
            }
            if (o->isHighlighted((u8)idx) != 0 && letter->getState() == 4) {
                t = 0xe;
            } else {
                t = o->getLetterPalette(letter);
            }
            o->drawLetterIcon(x, y, t, letter, NULL);
            o->drawUnderlay(x, y, t, NULL);
            if (o->isCursorSlot(idx) != 0) {
                o->drawFocus(x, y, NULL);
            }
        }
    }
}

s32 LetterGrid_GetSlotX(LetterGrid *o, s32 i)
{
    if (i >= 0 && i <= 9) {
        if (i & 1) {
            return 0xe4;
        }
        return 0xcc;
    }
    if (i >= 0xa && i <= 0x22) {
        i -= 0xa;
        while (i >= 5) {
            i -= 5;
        }
        return sLetterGridColumnX[i];
    }
    if (i >= 0x23 && i <= 0x2c) {
        i -= 0x23;
        if (i & 1) {
            return 0x84;
        }
        return 0x6c;
    }
    if (i >= 0x2d && i <= 0x36) {
        i -= 0x2d;
        if (i & 1) {
            return 0x84;
        }
        return 0x6c;
    }
    return 0;
}

s32 LetterGrid_GetSlotY(LetterGrid *o, s32 i)
{
    if (i >= 0 && i <= 9) {
        return (i >> 1) * 0x18 + 0x3c;
    }
    if (i >= 0xa && i <= 0x22) {
        s32 n;
        i -= 0xa;
        n = 0;
        while (i >= 5) {
            i -= 5;
            n++;
        }
        return n * 0x18 + 0x3c;
    }
    if (i >= 0x23 && i <= 0x2c) {
        i -= 0x23;
        return (i >> 1) * 0x18 + 0x3c;
    }
    if (i >= 0x2d && i <= 0x36) {
        i -= 0x2d;
        return (i >> 1) * 0x18 + 0x3c;
    }
    return 0;
}

BOOL LetterGrid_IsSlotEmpty(LetterGrid *o, s32 i)
{
    if (LetterGrid_TestBit(o->occupiedBits.words, i) == 0) {
        return TRUE;
    }
    return FALSE;
}

void LetterGrid_LoadPocketLetters(LetterGrid *o)
{
    LetterView *q = (LetterView *)((PlayerInventory *)PlayerData_GetCurrent()->getInventory())->getLetter(0);
    s32 k = 0;
    s32 i = 0;
    do {
        if (LetterGrid_GetIconIndex(o, q) != -1) {
            LetterGrid_SetBit(o->occupiedBits.words, k);
        } else {
            LetterGrid_ClearBit(o->occupiedBits.words, k);
        }
        q++;
        k++;
        i++;
    } while (i < 10);
}

void LetterGrid_SetLetters2D(LetterGrid *o, void *letters)
{
    LetterGrid_SetLetterArray(o, (LetterView *)letters, 0x2d, 0xa);
}

void LetterGrid_SetLetters0A(LetterGrid *o, void *letters)
{
    LetterGrid_SetLetterArray(o, (LetterView *)letters, 0xa, 0x19);
}

void LetterGrid_SetLetters23(LetterGrid *o, void *letters)
{
    LetterGrid_SetLetterArray(o, (LetterView *)letters, 0x23, 0xa);
}

void LetterGrid_SetLetterArray(LetterGrid *o, LetterView *p, s32 m, s32 n)
{
    s32 i;
    o->letterArray = p;
    LetterView *q = p;
    for (i = 0; i < n; i++) {
        if (LetterGrid_GetIconIndex(o, q) != -1) {
            LetterGrid_SetBit(o->occupiedBits.words, m);
        } else {
            LetterGrid_ClearBit(o->occupiedBits.words, m);
        }
        q++;
        m++;
    }
}

s32 LetterGrid_GetIconIndex(LetterGrid *o, LetterView *h)
{
    s32 r = h->getState();
    if (r == 0) {
        return -1;
    }
    s32 t = (r - 1) * 2;
    if (h->getPresent() != 0xfff1) {
        t = t + 1;
    }
    return t;
}

void LetterGrid_StartPopAnim(LetterGrid *o)
{
    o->popTimer = 4;
    o->heldScale = 10;
}

void LetterGrid_ResetScale(LetterGrid *o)
{
    o->heldScale = 10;
}

BOOL LetterGrid_UpdatePopAnim(LetterGrid *o)
{
    if (o->popTimer != 0) {
        o->popTimer -= TICK_STEP_ENDS() ? 1 : 0;
        o->heldScale = LetterGrid_GetPopScale(o);
        return FALSE;
    }
    LetterGrid_ResetScale(o);
    return TRUE;
}

u8 LetterGrid_GetPopScale(LetterGrid *o)
{
    u32 v = o->popTimer;
    if (v >= 4) {
        return 10;
    }
    return sLetterPopScales[v];
}

void LetterGrid_ClearBits(u32 *bits)
{
    s32 i;
    for (i = 0; i < 2; i++) {
        bits[i] = 0;
    }
}

void LetterGrid_SetBit(u32 *bits, s32 i)
{
    bits[i >> 5] |= (1 << (i & 0x1f));
}

void LetterGrid_ClearBit(u32 *bits, s32 i)
{
    bits[i >> 5] &= ~(1 << (i & 0x1f));
}

BOOL LetterGrid_TestBit(u32 *bits, s32 i)
{
    BOOL r = TRUE;
    if (((1 << (i & 0x1f)) & bits[i >> 5]) == 0) {
        r = FALSE;
    }
    return r;
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov094_02293b90) {
    HOST_OVERLAY_VAR(sLetterGridColumnX),
    HOST_OVERLAY_VAR(sLetterIconSprite),
    HOST_OVERLAY_VAR(sLetterIconPalettes),
    HOST_OVERLAY_VAR(sLetterMarkSprites),
    HOST_OVERLAY_VAR(sLetterIconChars),
    HOST_OVERLAY_VAR(data_ov094_02294c14),
    HOST_OVERLAY_VARS_END
};
