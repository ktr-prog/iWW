#include "types.h"
#include "nitro/gxoam.h"
#include "ui/WfcTextKb.h"
#include "net/WfcRect.h"
#include "net/WfcObjGroup.h"
#include "proto/ov001/unk_ov001_02208c2c.h"
#include "proto/ov001/unk_ov001_0220aba4.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0222449c.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

extern "C" const u8 data_ov001_02229e94[2] = {0x3c, 0x3d};
extern "C" const u8 data_ov001_02229e8c[2] = {4, 5};
extern "C" const WfcPoint data_ov001_02229eac = {0x1c, 0x14};
extern "C" const u8 data_ov001_02229e9c[2] = {0x12, 0x13};
extern "C" const WfcPoint data_ov001_02229eb0 = {0x78, 0x12};
extern "C" const WfcPoint data_ov001_02229ebc[2] = {{0x4, 0xaa}, {0x84, 0xaa}};
extern "C" const char data_ov001_02229ec4[12] = "7894561230";
extern "C" const WfcPoint data_ov001_02229eb4[2] = {{0x72, 0x91}, {0x92, 0x91}};
extern "C" const WfcPoint data_ov001_02229ea4 = {0x1c, 0x14};
extern "C" const u16 data_ov001_02229ea8[2] = {0xc, 0x4};
extern "C" const u16 data_ov001_02229ed0[14] = {0x37, 0x38, 0x39, 0x34, 0x35, 0x36, 0x31, 0x32, 0x33, 0x30, 0x20, 0x20, 0, 0};
extern "C" const u8 data_ov001_02229e98[2] = {2, 3};
extern "C" const WfcPoint data_ov001_02229eec[10] = {
    {0x52, 0x4c}, {0x72, 0x4c}, {0x92, 0x4c}, {0x52, 0x63},
    {0x72, 0x63}, {0x92, 0x63}, {0x52, 0x7a}, {0x72, 0x7a},
    {0x92, 0x7a}, {0x52, 0x91},
};
extern "C" const u8 data_ov001_02229e90[2] = {0x37, 0x38};
extern "C" { WfcNumPad *sWfcNumPad; }
extern "C" const WfcPoint data_ov001_02229f14[14] = {
    {0x50, 0x4a}, {0x70, 0x4a}, {0x90, 0x4a}, {0x50, 0x61},
    {0x70, 0x61}, {0x90, 0x61}, {0x50, 0x78}, {0x70, 0x78},
    {0x90, 0x78}, {0x50, 0x8f}, {0x70, 0x8f}, {0x90, 0x8f},
    {0x2, 0xa8}, {0x82, 0xa8},
};
extern "C" const s8 sWfcNumPadNavTable[14][4] = {
    {2, 12, 1, 3},
    {0, 13, 2, 4},
    {1, 13, 0, 5},
    {5, 0, 4, 6},
    {3, 1, 5, 7},
    {4, 2, 3, 8},
    {8, 3, 7, 9},
    {6, 4, 8, 10},
    {7, 5, 6, 11},
    {11, 6, 10, 12},
    {9, 7, 11, 13},
    {10, 8, 9, 13},
    {13, 9, 13, 0},
    {12, -1, 12, -2},
};
extern "C" const u8 data_ov001_02229ea0[2] = {0x10, 0x11};
extern "C" WfcPosSize data_ov001_0222aa58 = {{0, 1}, {0, 0}};

extern "C" {
extern const WfcRect gWfcScreenRect;
void WfcTask_SetFunc(void *task, void *v);
void WfcObj_Free(WfcObjGroup *p);
void WfcUtil_RectFromPosSize(WfcPoint *a, WfcPoint *b, WfcRect *out);
}

extern "C" {
void WfcNumPad_Create() {
    WfcPosSize pos;
    u32 t;
    u16 v[2];
    s32 i, j, k;
    pos = data_ov001_0222aa58;
    pos.size = data_ov001_02229ea4;
    sWfcNumPad = (WfcNumPad *)WfcHeap_AllocClear(sizeof(WfcNumPad), 4);
    sWfcNumPad->inputKey = 0x1f;
    sWfcNumPad->cursorKey = 0;
    sWfcNumPad->deleteEnabled = 1;
    sWfcNumPad->insertEnabled = 1;
    sWfcNumPad->dotEnabled = 1;
    for (i = 0; i < 10; i++) {
        sWfcNumPad->digitKeyOams[i] = WfcObj_CreateSingle(0, 0x36);
        sWfcNumPad->digitKeyOams[i]->attr01 = (sWfcNumPad->digitKeyOams[i]->attr01 & 0xc1fffcff) | 0x200;
        sWfcNumPad->digitKeyOams[i]->attr2 = (sWfcNumPad->digitKeyOams[i]->attr2 & ~0xc00) | 0xc00;
    }
    const u8 *p = data_ov001_02229e90;
    for (i = 0; i < 2; i++) {
        sWfcNumPad->funcKeyOams[i] = WfcObj_CreateSingle(0, *p);
        p++;
        sWfcNumPad->funcKeyOams[i]->attr01 = (sWfcNumPad->funcKeyOams[i]->attr01 & 0xc1fffcff) | 0x200;
        sWfcNumPad->funcKeyOams[i]->attr2 = (sWfcNumPad->funcKeyOams[i]->attr2 & ~0xc00) | 0xc00;
    }
    for (i = 0; i < 2; i++) {
        sWfcNumPad->bottomButtons[i] = WfcObj_Create(0, data_ov001_02229e94[i], 1);
        WfcObj_SetAffineMode(sWfcNumPad->bottomButtons[i], -1, 0x200, 0);
        WfcObj_SetPriority(sWfcNumPad->bottomButtons[i], -1, 3);
    }
    u32 bh = data_ov001_02229ea8[1];
    u32 bw = data_ov001_02229ea8[0];
    s32 n;
    i = 0;
    n = i;
    v[1] = i;
    for (; i < 4; i++) {
        sWfcNumPad->rowCanvases[i] = WfcText_CreateObjCanvas(0, bw, bh, 0, &t, 0);
        pos.pos.x = 0;
        s32 idx = n;
        s32 kk;
        for (kk = 0; kk < 3; kk++, idx++, pos.pos.x += 0x20) {
            v[0] = data_ov001_02229ed0[idx];
            WfcText_DrawTextRect(sWfcNumPad->rowCanvases[i], pos.pos.x, pos.pos.y, pos.size.x, pos.size.y, 2, 0x480, v);
        }
        sWfcNumPad->rowTextObjs[i] = WfcObj_Alloc(0, t, 0);
        n += 3;
    }
    sWfcNumPad->cursorObj = WfcObj_Create(0, 0x44, 1);
    WfcObj_SetAffineMode(sWfcNumPad->cursorObj, -1, 0x200, 0);
    WfcObj_SetPriority(sWfcNumPad->cursorObj, -1, 2);
    sWfcNumPad->task = WfcTask_Add(0, (void *)WfcNumPad_SlideInStep0, 0, 0x78);
    WfcNumPad_SetRowY(0, 0xc0);
}
}

extern "C" {
void WfcNumPad_Close() {
    WfcObj_Free(sWfcNumPad->cursorObj);
    WfcTask_SetFunc(sWfcNumPad->task, (void *)WfcNumPad_SlideOutStep0);
}
}

extern "C" {
u32 WfcNumPad_GetKey() {
    return sWfcNumPad->inputKey;
}
}

extern "C" {
void WfcNumPad_SetDeleteEnabled(u32 v) {
    sWfcNumPad->deleteEnabled = v;
}
}

extern "C" {
void WfcNumPad_SetInsertEnabled(u32 v) {
    sWfcNumPad->insertEnabled = v;
}
}

extern "C" {
void WfcNumPad_SetDotEnabled(u32 v) {
    sWfcNumPad->dotEnabled = v;
}
}

extern "C" {
BOOL WfcNumPad_Exists() {
    return sWfcNumPad != NULL ? TRUE : FALSE;
}
}

extern "C" {
void WfcNumPad_SlideInStep0(void *self, void *work) {
    volatile s32 a, b;
    volatile u32 *ip = (volatile u32 *)sWfcNumPad->digitKeyOams[0];
    a = (*ip & 0x1ff0000) >> 16;
    s32 c = *ip & 0xff;
    b = c;
    c -= 12;
    b = c;
    u32 h = data_ov001_02229eec[0].y;
    if (c > (s32)h) {
        WfcNumPad_SetRowY(0, c);
        return;
    }
    WfcNumPad_SetRowY(0, h);
    WfcNumPad_SetRowY(1, 0xc0);
    WfcTask_SetFunc(self, (void *)WfcNumPad_SlideInStep1);
}
}

extern "C" {
void WfcNumPad_SlideInStep1(void *self, void *work) {
    volatile s32 a, b;
    volatile u32 *ip = (volatile u32 *)sWfcNumPad->digitKeyOams[3];
    a = (*ip & 0x1ff0000) >> 16;
    s32 c = *ip & 0xff;
    b = c;
    c -= 12;
    b = c;
    u32 h = data_ov001_02229eec[3].y;
    if (c > (s32)h) {
        WfcNumPad_SetRowY(1, c);
        return;
    }
    WfcNumPad_SetRowY(1, h);
    WfcNumPad_SetRowY(2, 0xc0);
    WfcTask_SetFunc(self, (void *)WfcNumPad_SlideInStep2);
}
}

extern "C" {
void WfcNumPad_SlideInStep2(void *self, void *work) {
    volatile s32 a, b;
    volatile u32 *ip = (volatile u32 *)sWfcNumPad->digitKeyOams[6];
    a = (*ip & 0x1ff0000) >> 16;
    s32 c = *ip & 0xff;
    b = c;
    c -= 12;
    b = c;
    u32 h = data_ov001_02229eec[6].y;
    if (c > (s32)h) {
        WfcNumPad_SetRowY(2, c);
        return;
    }
    WfcNumPad_SetRowY(2, h);
    WfcNumPad_SetRowY(3, 0xc0);
    WfcTask_SetFunc(self, (void *)WfcNumPad_SlideInStep3);
}
}

extern "C" {
void WfcNumPad_SlideInStep3(void *self, void *work) {
    volatile s32 a, b;
    volatile u32 *ip = (volatile u32 *)sWfcNumPad->digitKeyOams[9];
    a = (*ip & 0x1ff0000) >> 16;
    s32 c = *ip & 0xff;
    b = c;
    c -= 12;
    b = c;
    u32 h = data_ov001_02229eec[9].y;
    if (c > (s32)h) {
        WfcNumPad_SetRowY(3, c);
        return;
    }
    WfcNumPad_SetRowY(3, h);
    WfcNumPad_SetRowY(4, 0xc0);
    WfcTask_SetFunc(self, (void *)WfcNumPad_SlideInStep4);
}
}

extern "C" {
void WfcNumPad_SlideInStep4(void *self, void *work) {
    u32 a, b;
    WfcObj_GetPos(sWfcNumPad->bottomButtons[0], 0, &a, &b);
    b -= 12;
    u32 h = data_ov001_02229ebc[0].y;
    if ((s32)b > (s32)h) {
        WfcNumPad_SetRowY(4, b);
        return;
    }
    WfcNumPad_SetRowY(4, h);
    WfcNumPad_UpdateCursor();
    WfcTask_SetFunc(self, (void *)WfcNumPad_InputTask);
}
}

extern "C" {
void WfcNumPad_InputTask() {
    WfcNumPad_HandleTouchPress();
    WfcNumPad_HandleTouchRelease();
    WfcNumPad_HandleTouchHold();
    WfcNumPad_HandlePad();
}
}

extern "C" {
void WfcNumPad_HandleTouchPress() {
    WfcRect out;
    s32 i;
    if (WfcInput_IsTouchPressedIn((WfcRect *)&gWfcScreenRect) == 0) return;
    sWfcNumPad->touchKey = -1;
    for (i = 0; i < 10; i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)&data_ov001_02229eec[i], (WfcPoint *)&data_ov001_02229ea4, &out);
        if (WfcInput_IsTouchPressedIn(&out) != 0) {
            if (sWfcNumPad->insertEnabled == 0) {
                WfcSound_Play(9);
                return;
            }
            WfcSound_Play(0);
            sWfcNumPad->touchKey = i;
            return;
        }
    }
    for (i = 0; i < 2; i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)&data_ov001_02229eb4[i], (WfcPoint *)&data_ov001_02229eac, &out);
        if (WfcInput_IsTouchPressedIn(&out) != 0) {
            if (i == 0 && sWfcNumPad->deleteEnabled == 0) goto fail;
            if (i == 1 && sWfcNumPad->dotEnabled == 0) {
            fail:
                WfcSound_Play(9);
                return;
            }
            WfcSound_Play(0);
            sWfcNumPad->touchKey = i + 10;
            return;
        }
    }
    for (i = 0; i < 2; i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)&data_ov001_02229ebc[i], (WfcPoint *)&data_ov001_02229eb0, &out);
        if (WfcInput_IsTouchPressedIn(&out) != 0) {
            WfcSound_Play(0);
            sWfcNumPad->touchKey = i + 12;
            return;
        }
    }
}
}

extern "C" {
void WfcNumPad_HandleTouchRelease() {
    const WfcPoint *p;
    s32 i;
    WfcRect buf;
    sWfcNumPad->inputKey = 0;
    if (!WfcInput_IsTouchReleasedIn((WfcRect *)&gWfcScreenRect)) return;
    for (p = data_ov001_02229eec, i = 0; i < 10; p++, i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)p, (WfcPoint *)&data_ov001_02229ea4, &buf);
        if (WfcInput_IsTouchReleasedIn(&buf)) {
            if (sWfcNumPad->touchKey != i) return;
            sWfcNumPad->inputKey = data_ov001_02229ec4[i];
            sWfcNumPad->cursorKey = i;
            WfcNumPad_UpdateCursor();
            return;
        }
    }
    for (p = data_ov001_02229eb4, i = 0; i < 2; p++, i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)p, (WfcPoint *)&data_ov001_02229eac, &buf);
        if (WfcInput_IsTouchReleasedIn(&buf)) {
            if (sWfcNumPad->touchKey != i + 10) return;
            sWfcNumPad->inputKey = data_ov001_02229ea0[i];
            sWfcNumPad->cursorKey = i + 10;
            WfcNumPad_UpdateCursor();
            return;
        }
    }
    for (p = data_ov001_02229ebc, i = 0; i < 2; p++, i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)p, (WfcPoint *)&data_ov001_02229eb0, &buf);
        if (WfcInput_IsTouchReleasedIn(&buf)) {
            if (sWfcNumPad->touchKey != i + 12) return;
            sWfcNumPad->inputKey = data_ov001_02229e9c[i];
            sWfcNumPad->cursorKey = i + 12;
            WfcNumPad_UpdateCursor();
            return;
        }
    }
}
}

extern "C" {
void WfcNumPad_HandleTouchHold() {
    s32 i;
    const WfcPoint *p;
    WfcRect buf;
    if (!WfcInput_IsTouchHeldIn((WfcRect *)&gWfcScreenRect)) goto fail;
    for (p = data_ov001_02229eec, i = 0; i < 10; p++, i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)p, (WfcPoint *)&data_ov001_02229ea4, &buf);
        if (WfcInput_IsTouchHeldIn(&buf)) {
            if (sWfcNumPad->touchKey != i) goto fail;
            WfcNumPad_SetPressedKey(i);
            goto end;
        }
    }
    for (p = data_ov001_02229eb4, i = 0; i < 2; p++, i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)p, (WfcPoint *)&data_ov001_02229eac, &buf);
        if (WfcInput_IsTouchHeldIn(&buf)) {
            if (sWfcNumPad->touchKey != i + 10) goto fail;
            WfcNumPad_SetPressedKey(i + 10);
            if (i != 0) goto end;
            sWfcNumPad->deleteHoldTimer++;
            if (sWfcNumPad->deleteHoldTimer < 0x28) return;
            if (sWfcNumPad->deleteEnabled == 0) {
                WfcSound_Play(9);
                sWfcNumPad->touchKey = -1;
                return;
            }
            sWfcNumPad->inputKey = 0x10;
            sWfcNumPad->deleteHoldTimer -= 7;
            return;
        }
    }
    for (p = data_ov001_02229ebc, i = 0; i < 2; p++, i++) {
        WfcUtil_RectFromPosSize((WfcPoint *)p, (WfcPoint *)&data_ov001_02229eb0, &buf);
        if (WfcInput_IsTouchHeldIn(&buf)) {
            if (sWfcNumPad->touchKey != i + 12) goto fail;
            WfcNumPad_SetPressedKey(i + 12);
            goto end;
        }
    }
fail:
    WfcNumPad_SetPressedKey(-1);
end:
    sWfcNumPad->deleteHoldTimer = 0;
}
}

extern "C" {
void WfcNumPad_SetPressedKey(s32 a) {
    if (a == sWfcNumPad->highlightKey) return;
    WfcNumPad_SetKeyHighlight(a, 1);
    WfcNumPad_SetKeyHighlight(sWfcNumPad->highlightKey, 0);
    sWfcNumPad->highlightKey = a;
}
}

extern "C" {
void WfcNumPad_HandlePad() {
    if (WfcInput_IsKeyRepeat(0x20)) WfcNumPad_MoveCursor(0);
    if (WfcInput_IsKeyRepeat(0x40)) WfcNumPad_MoveCursor(1);
    if (WfcInput_IsKeyRepeat(0x10)) WfcNumPad_MoveCursor(2);
    if (WfcInput_IsKeyRepeat(0x80)) WfcNumPad_MoveCursor(3);
    if (WfcInput_IsKeyPressed(1)) {
        WfcNumPad *o = sWfcNumPad;
        s32 c = o->cursorKey;
        if (c < 10) {
            if (o->insertEnabled != 0) {
                o->inputKey = data_ov001_02229ec4[c];
                return;
            }
            WfcSound_Play(9);
            return;
        } else if (c - 10 < 2) {
            if ((c - 10 == 0 && o->deleteEnabled == 0) || (c - 10 == 1 && o->dotEnabled == 0)) {
                WfcSound_Play(9);
                return;
            }
            o->inputKey = data_ov001_02229ea0[c - 10];
            return;
        } else {
            o->inputKey = data_ov001_02229e9c[c - 12];
        }
    }
    if (WfcInput_IsKeyRepeat(2)) {
        WfcNumPad *o = sWfcNumPad;
        if (o->deleteEnabled == 0) {
            if (o->errorSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcNumPad->errorSoundPlayed = 1;
            return;
        }
        o->inputKey = 0x10;
        return;
    }
    if (WfcInput_IsKeyReleased(2)) {
        sWfcNumPad->errorSoundPlayed = 0;
    }
}
}

extern "C" {
void WfcNumPad_SetRowY(s32 a, s32 b) {
    u8 x[5] = {3, 3, 3, 1, 0};
    u8 y[5] = {0, 0, 0, 2, 0};
    u8 z[5] = {0, 0, 0, 0, 2};
    s32 k = a * 3;
    s32 i;
    for (i = 0; i < x[a]; i++) {
        GXOamAttr *r = sWfcNumPad->digitKeyOams[k];
        r->attr01 &= 0xc1fffcff;
        u32 t = data_ov001_02229eec[k].x;
        r = sWfcNumPad->digitKeyOams[k];
        r->attr01 = (r->attr01 & 0xfe00ff00) | (u8)b | ((t & 0x1ff) << 16);
        k++;
    }
    if (a < 4) {
        WfcText_ArrangeObj(sWfcNumPad->rowCanvases[a], data_ov001_02229eec[a * 3].x, b, sWfcNumPad->rowTextObjs[a], 2);
    }
    for (i = 0; i < y[a]; i++) {
        GXOamAttr *r = sWfcNumPad->funcKeyOams[i];
        r->attr01 &= 0xc1fffcff;
        u32 t = data_ov001_02229eb4[i].x;
        r = sWfcNumPad->funcKeyOams[i];
        r->attr01 = (r->attr01 & 0xfe00ff00) | (u8)b | ((t & 0x1ff) << 16);
    }
    for (i = 0; i < z[a]; i++) {
        WfcObj_SetAffineMode(sWfcNumPad->bottomButtons[i], -1, 0, 0);
        WfcObj_SetPos(sWfcNumPad->bottomButtons[i], -1, data_ov001_02229ebc[i].x, b);
    }
}
}

extern "C" {
void WfcNumPad_SetKeyHighlight(s32 a, u32 b) {
    if (a < 0) return;
    if (a < 10) {
        GXOamAttr *r = sWfcNumPad->digitKeyOams[a];
        r->attr01 = r->attr01 & ~0xc00;
        r->attr2 = (r->attr2 & ~0xf000) | (data_ov001_02229e98[b] << 12);
    } else if (a - 10 < 2) {
        GXOamAttr *r = sWfcNumPad->funcKeyOams[a - 10];
        r->attr01 = r->attr01 & ~0xc00;
        r->attr2 = (r->attr2 & ~0xf000) | (data_ov001_02229e98[b] << 12);
    } else {
        WfcObj_SetModePalette(sWfcNumPad->bottomButtons[a - 12], -1, 0, data_ov001_02229e8c[b]);
    }
}
}

extern "C" {
void WfcNumPad_UpdateCursor() {
    s32 t;
    s32 idx = sWfcNumPad->cursorKey;
    if (idx <= 0xb) t = 0x44;
    else t = 0x45;
    GXOamAttr *r = WfcObj_GetOam(sWfcNumPad->cursorObj, 0);
    WfcCell_Copy(0, t, r);
    WfcObj_SetPriority(sWfcNumPad->cursorObj, -1, 2);
    const WfcPoint *pos = &data_ov001_02229f14[sWfcNumPad->cursorKey];
    WfcObj_SetPos(sWfcNumPad->cursorObj, -1, pos->x, pos->y);
}
}

extern "C" {
void WfcNumPad_MoveCursor(s32 a) {
    WfcNumPad *g = sWfcNumPad;
    s32 old = g->cursorKey;
    g->cursorKey = sWfcNumPadNavTable[old][a];
    g = sWfcNumPad;
    s32 n = g->cursorKey;
    if (n == 0xd && (a == 1 || a == 3)) {
        g->prevCursorKey = old;
    } else if (n == -1) {
        if (g->prevCursorKey == 1 || g->prevCursorKey == 0xa) {
            g->cursorKey = 0xa;
        } else {
            g->cursorKey = 0xb;
        }
    } else if (n == -2) {
        if (g->prevCursorKey == 1 || g->prevCursorKey == 0xa) {
            g->cursorKey = 1;
        } else {
            g->cursorKey = 2;
        }
    }
    WfcNumPad_UpdateCursor();
    WfcSound_Play(8);
}
}

extern "C" {
void WfcNumPad_SlideOutStep0(void *a, void *work) {
    volatile s32 s[2];
    GXOamAttr *r = WfcObj_GetOam(sWfcNumPad->bottomButtons[0], 0);
    s32 t;
    s[0] = (*(volatile u32 *)&r->attr01 & 0x1ff0000) >> 16;
    t = *(volatile u32 *)&r->attr01 & 0xff;
    s[1] = t;
    t += 0xc;
    s[1] = t;
    WfcNumPad_SetRowY(4, t);
    if (s[1] < 0xc0) return;
    WfcTask_SetFunc(a, (void *)WfcNumPad_SlideOutStep1);
}
}

extern "C" {
void WfcNumPad_SlideOutStep1(void *a, void *work) {
    volatile s32 s[2];
    GXOamAttr *r = sWfcNumPad->digitKeyOams[9];
    s32 t;
    s[0] = (*(volatile u32 *)&r->attr01 & 0x1ff0000) >> 16;
    t = *(volatile u32 *)&r->attr01 & 0xff;
    s[1] = t;
    t += 0xc;
    s[1] = t;
    WfcNumPad_SetRowY(3, t);
    if (s[1] < 0xc0) return;
    WfcTask_SetFunc(a, (void *)WfcNumPad_SlideOutStep2);
}
}

extern "C" {
void WfcNumPad_SlideOutStep2(void *a, void *work) {
    volatile s32 s[2];
    GXOamAttr *r = sWfcNumPad->digitKeyOams[6];
    s32 t;
    s[0] = (*(volatile u32 *)&r->attr01 & 0x1ff0000) >> 16;
    t = *(volatile u32 *)&r->attr01 & 0xff;
    s[1] = t;
    t += 0xc;
    s[1] = t;
    WfcNumPad_SetRowY(2, t);
    if (s[1] < 0xc0) return;
    WfcTask_SetFunc(a, (void *)WfcNumPad_SlideOutStep3);
}
}

extern "C" {
void WfcNumPad_SlideOutStep3(void *a, void *work) {
    volatile s32 s[2];
    GXOamAttr *r = sWfcNumPad->digitKeyOams[3];
    s32 t;
    s[0] = (*(volatile u32 *)&r->attr01 & 0x1ff0000) >> 16;
    t = *(volatile u32 *)&r->attr01 & 0xff;
    s[1] = t;
    t += 0xc;
    s[1] = t;
    WfcNumPad_SetRowY(1, t);
    if (s[1] < 0xc0) return;
    WfcTask_SetFunc(a, (void *)WfcNumPad_SlideOutStep4);
}
}

extern "C" {
void WfcNumPad_SlideOutStep4(void *a, void *work) {
    volatile s32 s[2];
    GXOamAttr *r = sWfcNumPad->digitKeyOams[0];
    s32 t;
    s[0] = (*(volatile u32 *)&r->attr01 & 0x1ff0000) >> 16;
    t = *(volatile u32 *)&r->attr01 & 0xff;
    s[1] = t;
    t += 0xc;
    s[1] = t;
    WfcNumPad_SetRowY(0, t);
    if (s[1] < 0xc0) return;
    WfcTask_SetFunc(a, (void *)WfcNumPad_Destroy);
}
}

extern "C" {
void WfcNumPad_Destroy(void *a, void *work) {
    s32 i;
    WfcTask_RequestDelete(0, a);
    for (i = 0; i < 4; i++) {
        WfcObj_Free(sWfcNumPad->rowTextObjs[i]);
        WfcText_DestroyObjCanvas(sWfcNumPad->rowCanvases[i]);
    }
    for (i = 0; i < 2; i++) {
        WfcObj_Free(sWfcNumPad->bottomButtons[i]);
    }
    for (i = 0; i < 2; i++) {
        WfcOam_FreeEntry(sWfcNumPad->funcKeyOams[i]);
    }
    for (i = 0; i < 10; i++) {
        WfcOam_FreeEntry(sWfcNumPad->digitKeyOams[i]);
    }
    WfcHeap_FreeAndClear((void **)&sWfcNumPad);
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220aba4) {
    HOST_OVERLAY_VAR(sWfcNumPad),
    HOST_OVERLAY_VAR(data_ov001_0222aa58),
    HOST_OVERLAY_VARS_END
};
