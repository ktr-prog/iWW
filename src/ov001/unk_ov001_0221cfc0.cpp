#include "types.h"
#include "proto/ov001/unk_ov001_0221cfc0.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_0222449c.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

struct WfcScrollBar {
    WfcObjGroup *thumbObj;
    u32 unk_04;
    u32 unk_08;
    void *task;
    u16 posX;
    u16 posY;
    u16 dragStartTouchX;
    u16 dragStartTouchY;
    u8 dragStartThumbPos;
    u8 trackLength;
    u8 thumbPos;
    u8 thumbSize;
    u8 state;
    u8 event;
    u8 isDisabled;
};

extern "C" {
extern u8 gWfcScreenRect[];
void WfcInput_GetTouchPos(void *);
s32 WfcInput_IsTouchHeldIn(void *);
s32 WfcInput_IsTouchRepeatIn(void *);
s32 WfcInput_IsTouchPressedIn(void *);
void WfcObj_Free(WfcObjGroup *);
void WfcHeap_FreeAndClear(void *);
void *WfcHeap_AllocClear(s32, s32);
void WfcUtil_SetPoint(s32, s32, void *);
s32 FX_DivS32(s32, s32);

}

extern "C" const u8 sWfcScrollBarThumbSizes[4] = { 0x55, 0x36, 0x1e, 0x00 };
extern "C" const u8 sWfcScrollBarThumbCells[4] = { 0x10, 0x0f, 0x0e, 0x00 };
WfcScrollBar *sWfcScrollBar;

void WfcScrollBar_Create(u32 a, u32 b, s32 c, s32 d, u32 e) {
    sWfcScrollBar = (WfcScrollBar *)WfcHeap_AllocClear(sizeof(WfcScrollBar), 4);
    sWfcScrollBar->thumbSize = a;
    sWfcScrollBar->trackLength = b;
    sWfcScrollBar->thumbPos = e;
    WfcUtil_SetPoint(c, d, &sWfcScrollBar->posX);
    sWfcScrollBar->thumbObj = WfcObj_Create(0, sWfcScrollBarThumbCells[a], 1);
    WfcObj_SetPos(sWfcScrollBar->thumbObj, -1, c, d + e);
    WfcObj_SetPriority(sWfcScrollBar->thumbObj, -1, 1);
    sWfcScrollBar->task = WfcTask_Add(0, (void *)WfcScrollBar_Task, 0, 0x80);
}

void WfcScrollBar_Destroy() {
    WfcTask_Delete(0, sWfcScrollBar->task);
    WfcObj_Free(sWfcScrollBar->thumbObj);
    WfcHeap_FreeAndClear(&sWfcScrollBar);
}

u32 WfcScrollBar_GetPos() {
    return sWfcScrollBar->thumbPos;
}

u32 WfcScrollBar_GetEvent() {
    return sWfcScrollBar->event;
}

void WfcScrollBar_SetPos(s32 a) {
    WfcScrollBar_SetThumbPos(a);
}

void WfcScrollBar_Enable() {
    sWfcScrollBar->isDisabled = 0;
}

void WfcScrollBar_Disable() {
    sWfcScrollBar->isDisabled = 1;
}

void WfcScrollBar_Task() {
    sWfcScrollBar->event = 0;
    WfcScrollBar *s = sWfcScrollBar;
    switch (s->state) {
    case 0:
        if (s->isDisabled != 0) return;
        switch (WfcScrollBar_HitTest()) {
        case 1:
            if (sWfcScrollBar->thumbSize == 0) return;
            WfcSound_Play(0x16);
            WfcSound_SetVolume(0);
            sWfcScrollBar->event = 1;
            WfcInput_GetTouchPos(&sWfcScrollBar->dragStartTouchX);
            {
                WfcScrollBar *t = sWfcScrollBar;
                t->dragStartThumbPos = t->thumbPos;
            }
            sWfcScrollBar->state = 1;
            break;
        case 2:
            WfcScrollBar_StartArrow(2);
            break;
        case 3:
            WfcScrollBar_StartArrow(3);
            break;
        case 4:
            WfcScrollBar_JumpToTouch();
            break;
        }
        break;
    case 1:
        WfcScrollBar_UpdateDrag();
        break;
    case 2:
        if (WfcScrollBar_HitTestArrowHeld(2) != 2) {
            sWfcScrollBar->event = 5;
            sWfcScrollBar->state = 0;
            return;
        }
        if (WfcScrollBar_HitTest() != 2) return;
        WfcScrollBar_StartArrow(2);
        break;
    case 3:
        if (WfcScrollBar_HitTestArrowHeld(3) != 3) {
            sWfcScrollBar->event = 7;
            sWfcScrollBar->state = 0;
            return;
        }
        if (WfcScrollBar_HitTest() != 3) return;
        WfcScrollBar_StartArrow(3);
        break;
    }
}

void WfcScrollBar_UpdateDrag() {
    u16 pt[2];
    if (WfcInput_IsTouchHeldIn(gWfcScreenRect) != 0) {
        WfcInput_GetTouchPos(pt);
        WfcScrollBar *s = sWfcScrollBar;
        if ((s32)pt[0] >= (s32)s->posX - 0x1e) {
            s32 v = s->dragStartThumbPos + ((s32)pt[1] - (s32)s->dragStartTouchY);
            if (v < 0) {
                v = 0;
            } else {
                s32 m = s->trackLength - sWfcScrollBarThumbSizes[s->thumbSize];
                if (v >= m) v = m;
            }
            WfcScrollBar_UpdateDragSound(v);
            WfcScrollBar_SetThumbPos(v);
            sWfcScrollBar->event = 2;
            return;
        }
    }
    WfcSound_Stop();
    sWfcScrollBar->state = 0;
    sWfcScrollBar->event = 3;
}

void WfcScrollBar_UpdateDragSound(s32 a) {
    s32 r4 = sWfcScrollBar->thumbPos - a;
    s32 r0, r1;
    if (r4 < 0) r4 = -r4;
    if (r4 < 2) {
        r0 = 0;
    } else if (r4 >= 6) {
        r0 = 0x7f;
    } else {
        r0 = FX_DivS32(0x7f, 6 - r4);
    }
    WfcSound_SetVolume(r0);
    if (r4 < 2) {
        r1 = -0x100;
    } else if (r4 >= 6) {
        r1 = 0x100;
    } else {
        r1 = FX_DivS32(0x200, 6 - r4) - 0x100;
    }
    WfcSound_SetTrackPitch(0xffff, r1);
}

void WfcScrollBar_StartArrow(s32 a) {
    sWfcScrollBar->state = a;
    sWfcScrollBar->event = (a == 2) ? 4 : 6;
}

void WfcScrollBar_JumpToTouch() {
    u16 buf[2];
    s32 v;
    WfcInput_GetTouchPos(buf);
    u32 t = sWfcScrollBarThumbSizes[sWfcScrollBar->thumbSize];
    v = buf[1] - sWfcScrollBar->posY - (t >> 1);
    if (v < 0) {
        v = 0;
    } else {
        s32 m = sWfcScrollBar->trackLength - t;
        if (v >= m) v = m;
    }
    WfcScrollBar_SetThumbPos(v);
    sWfcScrollBar->event = 3;
}

s32 WfcScrollBar_HitTest() {
    u16 buf[6];
    s32 i;
    WfcScrollBar_GetPartRect(1, buf);
    if (WfcInput_IsTouchRepeatIn(buf) != 0) return 1;
    for (i = 2; i <= 3; i++) {
        WfcScrollBar_GetPartRect(i, buf);
        if (WfcInput_IsTouchRepeatIn(buf) != 0) return i;
    }
    WfcScrollBar_GetPartRect(4, buf);
    if (WfcInput_IsTouchPressedIn(buf) != 0) return 4;
    return 0;
}

s32 WfcScrollBar_HitTestArrowHeld(s32 unused) {
    u16 buf[6];
    s32 i;
    for (i = 2; i <= 3; i++) {
        WfcScrollBar_GetPartRect(i, buf);
        if (WfcInput_IsTouchHeldIn(buf) != 0) return i;
    }
    return 0;
}

void WfcScrollBar_GetPartRect(s32 a, u16 *out) {
    out[0] = sWfcScrollBar->posX;
    out[2] = out[0] + 0xc;
    switch (a) {
    case 0:
        break;
    case 1:
        out[1] = sWfcScrollBar->posY + sWfcScrollBar->thumbPos;
        out[3] = out[1] + sWfcScrollBarThumbSizes[sWfcScrollBar->thumbSize];
        break;
    case 2:
        out[1] = sWfcScrollBar->posY - 0xd;
        out[3] = sWfcScrollBar->posY;
        break;
    case 3:
        out[1] = sWfcScrollBar->posY + sWfcScrollBar->trackLength;
        out[3] = out[1] + 0xd;
        break;
    case 4:
        out[1] = sWfcScrollBar->posY;
        out[3] = out[1] + sWfcScrollBar->trackLength;
        break;
    }
}

void WfcScrollBar_SetThumbPos(u32 a) {
    WfcObj_SetPos(sWfcScrollBar->thumbObj, -1, sWfcScrollBar->posX, a + sWfcScrollBar->posY);
    sWfcScrollBar->thumbPos = a;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221cfc0) {
    HOST_OVERLAY_VAR(sWfcScrollBar),
    HOST_OVERLAY_VARS_END
};
