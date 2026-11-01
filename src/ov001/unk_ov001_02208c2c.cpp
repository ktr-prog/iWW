#include "types.h"
#include "host_tick.h"
#include "ui/WfcTextRect.h"
#include "ui/WfcTextKb.h"
#include "net/WfcRect.h"
#include "nitro/gxoam.h"
#include "net/WfcObjGroup.h"
#include "proto/ov001/unk_ov001_02208a24.h"
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

extern "C" const WfcPoint data_ov001_02229ce4[53] = {
    {0x2, 0x4f}, {0x14, 0x4f}, {0x26, 0x4f}, {0x38, 0x4f},
    {0x4a, 0x4f}, {0x5c, 0x4f}, {0x6e, 0x4f}, {0x80, 0x4f},
    {0x92, 0x4f}, {0xa4, 0x4f}, {0xb6, 0x4f}, {0xc8, 0x4f},
    {0x1e, 0x65}, {0x30, 0x65}, {0x42, 0x65}, {0x54, 0x65},
    {0x66, 0x65}, {0x78, 0x65}, {0x8a, 0x65}, {0x9c, 0x65},
    {0xae, 0x65}, {0xc0, 0x65}, {0xd2, 0x65}, {0xe4, 0x65},
    {0x23, 0x7b}, {0x35, 0x7b}, {0x47, 0x7b}, {0x59, 0x7b},
    {0x6b, 0x7b}, {0x7d, 0x7b}, {0x8f, 0x7b}, {0xa1, 0x7b},
    {0xb3, 0x7b}, {0xc5, 0x7b}, {0xd7, 0x7b}, {0xe9, 0x7b},
    {0x2b, 0x91}, {0x3d, 0x91}, {0x4f, 0x91}, {0x61, 0x91},
    {0x73, 0x91}, {0x85, 0x91}, {0x97, 0x91}, {0xa9, 0x91},
    {0xbb, 0x91}, {0xcd, 0x91}, {0xdf, 0x91}, {0x2, 0x65},
    {0x2, 0x7b}, {0x2, 0x91}, {0xda, 0x4f}, {0x2, 0xa8},
    {0x82, 0xa8},
};
extern "C" const s8 sWfcTextKbNavTable[53][4] = {
    {50, 51, 1, 47},
    {0, 51, 2, 12},
    {1, 51, 3, 13},
    {2, 51, 4, 14},
    {3, 51, 5, 15},
    {4, 51, 6, 16},
    {5, 52, 7, 17},
    {6, 52, 8, 18},
    {7, 52, 9, 19},
    {8, 52, 10, 20},
    {9, 52, 11, 21},
    {10, 52, 50, 22},
    {47, 1, 13, 24},
    {12, 2, 14, 25},
    {13, 3, 15, 26},
    {14, 4, 16, 27},
    {15, 5, 17, 28},
    {16, 6, 18, 29},
    {17, 7, 19, 30},
    {18, 8, 20, 31},
    {19, 9, 21, 32},
    {20, 10, 22, 33},
    {21, 11, 23, 34},
    {22, 50, 47, 35},
    {48, 12, 25, 36},
    {24, 13, 26, 37},
    {25, 14, 27, 38},
    {26, 15, 28, 39},
    {27, 16, 29, 40},
    {28, 17, 30, 41},
    {29, 18, 31, 42},
    {30, 19, 32, 43},
    {31, 20, 33, 44},
    {32, 21, 34, 45},
    {33, 22, 35, 46},
    {34, 23, 48, 46},
    {49, 24, 37, 51},
    {36, 25, 38, 51},
    {37, 26, 39, 51},
    {38, 27, 40, 51},
    {39, 28, 41, 51},
    {40, 29, 42, 52},
    {41, 30, 43, 52},
    {42, 31, 44, 52},
    {43, 32, 45, 52},
    {44, 33, 46, 52},
    {45, -1, 49, 52},
    {23, 0, 12, 48},
    {35, 47, 24, 49},
    {46, 48, 36, 51},
    {11, 52, 0, 23},
    {52, -2, 52, -4},
    {51, -3, 51, -5},
};
extern "C" const WfcPoint data_ov001_02229c28[47] = {
    {0x4, 0x51}, {0x16, 0x51}, {0x28, 0x51}, {0x3a, 0x51},
    {0x4c, 0x51}, {0x5e, 0x51}, {0x70, 0x51}, {0x82, 0x51},
    {0x94, 0x51}, {0xa6, 0x51}, {0xb8, 0x51}, {0xca, 0x51},
    {0x20, 0x67}, {0x32, 0x67}, {0x44, 0x67}, {0x56, 0x67},
    {0x68, 0x67}, {0x7a, 0x67}, {0x8c, 0x67}, {0x9e, 0x67},
    {0xb0, 0x67}, {0xc2, 0x67}, {0xd4, 0x67}, {0xe6, 0x67},
    {0x25, 0x7d}, {0x37, 0x7d}, {0x49, 0x7d}, {0x5b, 0x7d},
    {0x6d, 0x7d}, {0x7f, 0x7d}, {0x91, 0x7d}, {0xa3, 0x7d},
    {0xb5, 0x7d}, {0xc7, 0x7d}, {0xd9, 0x7d}, {0xeb, 0x7d},
    {0x2d, 0x93}, {0x3f, 0x93}, {0x51, 0x93}, {0x63, 0x93},
    {0x75, 0x93}, {0x87, 0x93}, {0x99, 0x93}, {0xab, 0x93},
    {0xbd, 0x93}, {0xcf, 0x93}, {0xe1, 0x93},
};
extern "C" u16 data_ov001_0222a914[50] = {
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30,
    0x2d, 0x3d, 0x71, 0x77, 0x65, 0x72, 0x74, 0x79, 0x75, 0x69,
    0x6f, 0x70, 0x5b, 0x5d, 0x61, 0x73, 0x64, 0x66, 0x67, 0x68,
    0x6a, 0x6b, 0x6c, 0x3b, 0x27, 0x60, 0x7a, 0x78, 0x63, 0x76,
    0x62, 0x6e, 0x6d, 0x2c, 0x2e, 0x2f, 0x5c, 0x20, 0x0, 0x0,
};
extern "C" u16 data_ov001_0222a978[50] = {
    0x21, 0x40, 0x23, 0x24, 0x25, 0x5e, 0x26, 0x2a, 0x28, 0x29,
    0x5f, 0x2b, 0x51, 0x57, 0x45, 0x52, 0x54, 0x59, 0x55, 0x49,
    0x4f, 0x50, 0x7b, 0x7d, 0x41, 0x53, 0x44, 0x46, 0x47, 0x48,
    0x4a, 0x4b, 0x4c, 0x3a, 0x22, 0x7e, 0x5a, 0x58, 0x43, 0x56,
    0x42, 0x4e, 0x4d, 0x3c, 0x3e, 0x3f, 0x7c, 0x20, 0x0, 0x0,
};
extern "C" u16 data_ov001_0222a9dc[50] = {
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30,
    0x2d, 0x3d, 0x51, 0x57, 0x45, 0x52, 0x54, 0x59, 0x55, 0x49,
    0x4f, 0x50, 0x5b, 0x5d, 0x41, 0x53, 0x44, 0x46, 0x47, 0x48,
    0x4a, 0x4b, 0x4c, 0x3b, 0x27, 0x60, 0x5a, 0x58, 0x43, 0x56,
    0x42, 0x4e, 0x4d, 0x2c, 0x2e, 0x2f, 0x5c, 0x20, 0x0, 0x0,
};
extern "C" char data_ov001_0222a884[0x30] = "!@#$%^&*()_+QWERTYUIOP{}ASDFGHJKL:\"~ZXCVBNM<>?|";
extern "C" char data_ov001_0222a8b4[0x30] = "1234567890-=QWERTYUIOP[]ASDFGHJKL;'`ZXCVBNM,./\\";
extern "C" char data_ov001_0222a8e4[0x30] = "1234567890-=qwertyuiop[]asdfghjkl;'`zxcvbnm,./\\";
extern "C" const WfcPoint data_ov001_02229c08[4] = {{0x4, 0x67}, {0x4, 0x7d}, {0x4, 0x93}, {0xdc, 0x51}};
extern "C" const WfcPoint data_ov001_02229c18[4] = {{0x1b, 0x12}, {0x20, 0x12}, {0x28, 0x12}, {0x20, 0x12}};
extern "C" u32 data_ov001_0222a874[4] = {0, 0, 0, 2};
extern "C" u16 *sWfcTextKbGlyphMaps[3] = {data_ov001_0222a914, data_ov001_0222a978, data_ov001_0222a9dc};
extern "C" u8 *sWfcTextKbCharMaps[3] = {(u8 *)data_ov001_0222a8e4, (u8 *)data_ov001_0222a884, (u8 *)data_ov001_0222a8b4};
extern "C" const u8 data_ov001_02229bf8[8] = {0xff, 0xff, 0x20, 0x80, 0, 0, 0, 0};
extern "C" const WfcPoint data_ov001_02229c00[2] = {{0x4, 0xaa}, {0x84, 0xaa}};
extern "C" u8 data_ov001_0222a844[5] = {0, 0, 0, 0, 2};
extern "C" u8 data_ov001_0222a84c[5] = {12, 12, 12, 11, 0};
extern "C" u8 data_ov001_0222a854[5] = {1, 1, 1, 1, 0};
extern "C" { WfcTextKb *sWfcTextKb; }
extern "C" const WfcPoint data_ov001_02229bf4 = {0x11, 0x12};
extern "C" const u8 data_ov001_02229be8[4] = {0x3a, 0x3b, 0x35, 0x39};
extern "C" const WfcPoint data_ov001_02229bf0 = {0x78, 0x12};
extern "C" const u16 data_ov001_02229bec[2] = {0x1c, 2};
extern "C" const u8 data_ov001_02229be4[2] = {0x82, 0x83};
extern "C" const u8 data_ov001_02229be0[2] = {0x3c, 0x3d};
extern "C" const u8 data_ov001_02229bdc[2] = {4, 5};
extern "C" const u8 data_ov001_02229bd8[2] = {2, 3};

extern "C" {
extern const WfcRect gWfcScreenRect;
void WfcTask_SetFunc(void *task, void *v);
void WfcObj_Free(WfcObjGroup *p);
void WfcUtil_RectFromPosSize(const WfcPoint *a, const WfcPoint *b, WfcRect *out);
s32 FX_ModS32(s32, s32);
void WfcTextKb_SlideOutStep1(void *a, void *work);
void WfcTextKb_SlideOutStep2(void *a, void *work);
void WfcTextKb_SlideOutStep3(void *a, void *work);
void WfcTextKb_SlideOutStep4(void *a, void *work);
}


struct WfcTextKbRowCounts {
    u8 b[5];
};




#define STATE_FN(NAME, OFF, IDX, NEXT) \
void NAME(void *a, void *work) { \
    volatile s32 xy[2]; \
    WfcTextKb *g = sWfcTextKb; \
    u32 *reg = (u32 *)g->charKeyOams[OFF]; \
    s32 t; \
    xy[0] = (*(volatile u32 *)reg & 0x1ff0000) >> 16; \
    t = *(volatile u32 *)reg & 0xff; \
    xy[1] = t; \
    t += 0xc; \
    xy[1] = t; \
    WfcTextKb_SetRowY(g->caseMode, IDX, t); \
    if (xy[1] < 0xc0) { \
        return; \
    } \
    WfcTask_SetFunc(a, (void *)NEXT); \
}

extern "C" {
void WfcTextKb_Create() {
    struct { WfcTextRect ps[1]; u32 t; u16 v; u16 d; } l;
    const u8 *p, *q;
    s32 m;
    s32 i, idx, j, k;
    l.ps[0].width = data_ov001_02229bf4.x;
    l.ps[0].height = data_ov001_02229bf4.y;
    sWfcTextKb = (WfcTextKb *)WfcHeap_AllocClear(sizeof(WfcTextKb), 4);
    sWfcTextKb->inputKey = 0xff;
    sWfcTextKb->cursorKey = 0;
    sWfcTextKb->deleteEnabled = 1;
    sWfcTextKb->insertEnabled = 1;
    for (i = 0; i < 0x2f; i++) {
        sWfcTextKb->charKeyOams[i] = WfcObj_CreateSingle(0, 0x34);
        sWfcTextKb->charKeyOams[i]->attr01 = (sWfcTextKb->charKeyOams[i]->attr01 & 0xc1fffcff) | 0x200;
        sWfcTextKb->charKeyOams[i]->attr2 = (sWfcTextKb->charKeyOams[i]->attr2 & ~0xc00) | 0xc00;
    }
    p = data_ov001_02229be8;
    for (i = 0; i < 4; i++) {
        sWfcTextKb->funcKeyOams[i] = WfcObj_CreateSingle(0, *p);
        p++;
        sWfcTextKb->funcKeyOams[i]->attr01 = (sWfcTextKb->funcKeyOams[i]->attr01 & 0xc1fffcff) | 0x200;
        sWfcTextKb->funcKeyOams[i]->attr2 = (sWfcTextKb->funcKeyOams[i]->attr2 & ~0xc00) | 0xc00;
    }
    q = data_ov001_02229be0;
    for (m = 0; m < 2; m++) {
        sWfcTextKb->bottomButtons[m] = WfcObj_Create(0, *q, 1);
        WfcObj_SetAffineMode(sWfcTextKb->bottomButtons[m], -1, 0x200, 0);
        WfcObj_SetPriority(sWfcTextKb->bottomButtons[m], -1, 3);
        q++;
    }
    l.d = 0;
    u32 bh = data_ov001_02229bec[1];
    u32 bw = data_ov001_02229bec[0];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            sWfcTextKb->rowCanvases[i][j] = WfcText_CreateObjCanvas(0, bw, bh, 0, &l.t, 0);
            idx = j * 12;
            l.ps[0].x = 0;
            for (k = 0; k < 12; k++, l.ps[0].x += 0x12, idx++) {
                l.v = sWfcTextKbGlyphMaps[i][idx];
                WfcText_DrawTextRect(sWfcTextKb->rowCanvases[i][j], l.ps[0].x, l.ps[0].y, l.ps[0].width, l.ps[0].height, 2, 0x480, &l.v);
            }
            if (i == 0) {
                sWfcTextKb->rowTextObjs[j] = WfcObj_Alloc(0, l.t, 1);
            }
        }
    }
    sWfcTextKb->cursorObj = WfcObj_Create(0, 0x40, 1);
    WfcObj_SetAffineMode(sWfcTextKb->cursorObj, -1, 0x200, 0);
    WfcObj_SetPriority(sWfcTextKb->cursorObj, -1, 2);
    sWfcTextKb->task = WfcTask_Add(0, (void *)WfcTextKb_SlideInStep0, 0, 0x78);
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 0, 0xc0);
}
}

extern "C" {
void WfcTextKb_Close() {
    WfcObj_Free(sWfcTextKb->cursorObj);
    WfcTask_SetFunc(sWfcTextKb->task, (void *)WfcTextKb_SlideOutStep0);
}
}

extern "C" {
u32 WfcTextKb_GetKey() {
    return sWfcTextKb->inputKey;
}
}

extern "C" {
void WfcTextKb_SetDeleteEnabled(u32 v) {
    sWfcTextKb->deleteEnabled = v;
}
}

extern "C" {
void WfcTextKb_SetInsertEnabled(u32 v) {
    sWfcTextKb->insertEnabled = v;
}
}

extern "C" {
BOOL WfcTextKb_Exists() {
    return sWfcTextKb != NULL ? TRUE : FALSE;
}
}

extern "C" {
void WfcTextKb_SlideInStep0(void *self, void *work) {
    volatile s32 a, b;
    volatile u32 *ip = (volatile u32 *)sWfcTextKb->charKeyOams[0];
    a = (*ip & 0x1ff0000) >> 16;
    s32 t = *ip & 0xff;
    b = t;
    t -= 12;
    b = t;
    u32 h = data_ov001_02229c28[0].y;
    if (t > (s32)h) {
        WfcTextKb_SetRowY(sWfcTextKb->caseMode, 0, t);
        return;
    }
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 0, h);
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 1, 0xc0);
    WfcTask_SetFunc(self, (void *)WfcTextKb_SlideInStep1);
}
}

extern "C" {
void WfcTextKb_SlideInStep1(void *self, void *work) {
    volatile s32 a, b;
    volatile u32 *ip = (volatile u32 *)sWfcTextKb->charKeyOams[12];
    a = (*ip & 0x1ff0000) >> 16;
    s32 t = *ip & 0xff;
    b = t;
    t -= 12;
    b = t;
    u32 h = data_ov001_02229c28[12].y;
    if (t > (s32)h) {
        WfcTextKb_SetRowY(sWfcTextKb->caseMode, 1, t);
        return;
    }
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 1, h);
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 2, 0xc0);
    WfcTask_SetFunc(self, (void *)WfcTextKb_SlideInStep2);
}
}

extern "C" {
void WfcTextKb_SlideInStep2(void *self, void *work) {
    volatile s32 a, b;
    volatile u32 *ip = (volatile u32 *)sWfcTextKb->charKeyOams[24];
    a = (*ip & 0x1ff0000) >> 16;
    s32 t = *ip & 0xff;
    b = t;
    t -= 12;
    b = t;
    u32 h = data_ov001_02229c28[24].y;
    if (t > (s32)h) {
        WfcTextKb_SetRowY(sWfcTextKb->caseMode, 2, t);
        return;
    }
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 2, h);
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 3, 0xc0);
    WfcTask_SetFunc(self, (void *)WfcTextKb_SlideInStep3);
}
}

extern "C" {
void WfcTextKb_SlideInStep3(void *self, void *work) {
    volatile s32 a, b;
    volatile u32 *ip = (volatile u32 *)sWfcTextKb->charKeyOams[36];
    a = (*ip & 0x1ff0000) >> 16;
    s32 t = *ip & 0xff;
    b = t;
    t -= 12;
    b = t;
    u32 h = data_ov001_02229c28[36].y;
    if (t > (s32)h) {
        WfcTextKb_SetRowY(sWfcTextKb->caseMode, 3, t);
        return;
    }
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 3, h);
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 4, 0xc0);
    WfcTask_SetFunc(self, (void *)WfcTextKb_SlideInStep4);
}
}

extern "C" {
void WfcTextKb_SlideInStep4(void *self, void *work) {
    u32 a, b;
    WfcObj_GetPos(sWfcTextKb->bottomButtons[0], 0, &a, &b);
    b -= 12;
    if ((s32)b > (s32)data_ov001_02229c00[0].y) {
        WfcTextKb_SetRowY(sWfcTextKb->caseMode, 4, b);
        return;
    }
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 4, data_ov001_02229c00[0].y);
    WfcTextKb_UpdateCursor();
    WfcTask_SetFunc(self, (void *)WfcTextKb_InputTask);
}
}

extern "C" {
void WfcTextKb_InputTask() {
    WfcTextKb_HandleTouchPress();
    WfcTextKb_HandleTouchRelease();
    WfcTextKb_HandleTouchHold();
    WfcTextKb_HandlePad();
}
}

extern "C" {
void WfcTextKb_HandleTouchPress() {
    WfcRect buf;
    const WfcPoint *p;
    s32 i;

    if (WfcInput_IsTouchPressedIn((WfcRect *)&gWfcScreenRect) == 0) return;
    sWfcTextKb->touchKey = -1;
    p = data_ov001_02229c28;
    for (i = 0; i < 0x2f; i++, p++) {
        WfcUtil_RectFromPosSize(p, &data_ov001_02229bf4, &buf);
        if (WfcInput_IsTouchPressedIn(&buf) != 0) {
            if (sWfcTextKb->insertEnabled == 0) {
                WfcSound_Play(9);
                return;
            }
            WfcSound_Play(0);
            sWfcTextKb->touchKey = i;
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        WfcUtil_RectFromPosSize(&data_ov001_02229c08[i], &data_ov001_02229c18[i], &buf);
        if (WfcInput_IsTouchPressedIn(&buf) != 0) {
            if ((i == 3 && sWfcTextKb->deleteEnabled == 0) ||
                (i == 2 && sWfcTextKb->insertEnabled == 0)) {
                WfcSound_Play(9);
                return;
            }
            WfcSound_Play(data_ov001_0222a874[i]);
            sWfcTextKb->touchKey = i + 0x2f;
            return;
        }
    }
    p = data_ov001_02229c00;
    for (i = 0; i < 2; i++, p++) {
        WfcUtil_RectFromPosSize(p, &data_ov001_02229bf0, &buf);
        if (WfcInput_IsTouchPressedIn(&buf) != 0) {
            WfcSound_Play(0);
            sWfcTextKb->touchKey = i + 0x33;
            return;
        }
    }
    return;
}
}

extern "C" {
void WfcTextKb_HandleTouchRelease() {
    WfcRect buf;
    const WfcPoint *p;
    s32 i;

    sWfcTextKb->inputKey = 0;
    if (WfcInput_IsTouchReleasedIn((WfcRect *)&gWfcScreenRect) == 0) return;
    p = data_ov001_02229c28;
    for (i = 0; i < 0x2f; i++, p++) {
        WfcUtil_RectFromPosSize(p, &data_ov001_02229bf4, &buf);
        if (WfcInput_IsTouchReleasedIn(&buf) != 0) {
            WfcTextKb *g = sWfcTextKb;
            if (g->touchKey != i) return;
            g->inputKey = sWfcTextKbCharMaps[g->caseMode][i];
            if (sWfcTextKb->caseMode == 1) WfcTextKb_SetMode(0);
            sWfcTextKb->cursorKey = i;
            WfcTextKb_UpdateCursor();
            return;
        }
    }
    for (i = 2; i < 4; i++) {
        WfcUtil_RectFromPosSize(&data_ov001_02229c08[i], &data_ov001_02229c18[i], &buf);
        if (WfcInput_IsTouchReleasedIn(&buf) != 0) {
            WfcTextKb *g = sWfcTextKb;
            if (g->touchKey != i + 0x2f) return;
            g->inputKey = data_ov001_02229bf8[i];
            if (sWfcTextKb->caseMode == 1) WfcTextKb_SetMode(0);
            sWfcTextKb->cursorKey = i + 0x2f;
            WfcTextKb_UpdateCursor();
            return;
        }
    }
    p = data_ov001_02229c00;
    for (i = 0; i < 2; i++, p++) {
        WfcUtil_RectFromPosSize(p, &data_ov001_02229bf0, &buf);
        if (WfcInput_IsTouchReleasedIn(&buf) != 0) {
            WfcTextKb *g = sWfcTextKb;
            if (g->touchKey != i + 0x33) return;
            g->inputKey = data_ov001_02229be4[i];
            sWfcTextKb->cursorKey = i + 0x33;
            WfcTextKb_UpdateCursor();
            return;
        }
    }
    WfcUtil_RectFromPosSize(&data_ov001_02229c08[0], &data_ov001_02229c18[0], &buf);
    if (WfcInput_IsTouchReleasedIn(&buf) != 0) {
        if (sWfcTextKb->touchKey != 0x2f) return;
        WfcTextKb_ToggleCapsLock();
        sWfcTextKb->cursorKey = 0x2f;
        WfcTextKb_UpdateCursor();
        return;
    }
    WfcUtil_RectFromPosSize(&data_ov001_02229c08[1], &data_ov001_02229c18[1], &buf);
    if (WfcInput_IsTouchReleasedIn(&buf) == 0) return;
    if (sWfcTextKb->touchKey != 0x30) return;
    WfcTextKb_ToggleShift();
    sWfcTextKb->cursorKey = 0x30;
    WfcTextKb_UpdateCursor();
    return;
}
}

extern "C" {
s32 WfcTextKb_ToggleCapsLock() {
    WfcTextKb_SetMode(sWfcTextKb->caseMode == 2 ? 0 : 2);
    return WfcSound_Play(1);
}
}

extern "C" {
s32 WfcTextKb_ToggleShift() {
    WfcTextKb_SetMode(sWfcTextKb->caseMode != 1 ? 1 : 0);
    return WfcSound_Play(1);
}
}

extern "C" {
void WfcTextKb_HandleTouchHold() {
    WfcRect buf;
    s32 i;
    if (WfcInput_IsTouchHeldIn((WfcRect *)&gWfcScreenRect)) {
        const WfcPoint *p = data_ov001_02229c28;
        i = 0;
        do {
            WfcUtil_RectFromPosSize(p, &data_ov001_02229bf4, &buf);
            if (WfcInput_IsTouchHeldIn(&buf)) {
                if (sWfcTextKb->touchKey != i) goto fail;
                WfcTextKb_SetPressedKey(i);
                goto done;
            }
            i++;
            p++;
        } while (i < 0x2f);
        const WfcPoint *q = &data_ov001_02229c18[2];
        const WfcPoint *pp = &data_ov001_02229c08[2];
        i = 2;
        do {
            WfcUtil_RectFromPosSize(pp, q, &buf);
            if (WfcInput_IsTouchHeldIn(&buf)) {
                if (sWfcTextKb->touchKey != i + 0x2f) goto fail;
                WfcTextKb_SetPressedKey(i + 0x2f);
                if (i != 3) return;
                sWfcTextKb->deleteHoldTimer = sWfcTextKb->deleteHoldTimer + (TICK_STEP_ENDS() ? 1 : 0);
                WfcTextKb *gg = sWfcTextKb;
                if (gg->deleteHoldTimer < 0x28) return;
                if (gg->deleteEnabled == 0) {
                    WfcSound_Play(9);
                    sWfcTextKb->touchKey = -1;
                    return;
                }
                gg->inputKey = 0x80;
                sWfcTextKb->deleteHoldTimer = sWfcTextKb->deleteHoldTimer - 7;
                return;
            }
            i++;
            q++;
            pp++;
        } while (i < 4);
        const WfcPoint *p3 = data_ov001_02229c00;
        i = 0;
        do {
            WfcUtil_RectFromPosSize(p3, &data_ov001_02229bf0, &buf);
            if (WfcInput_IsTouchHeldIn(&buf)) {
                if (sWfcTextKb->touchKey != i + 0x33) goto fail;
                WfcTextKb_SetPressedKey(i + 0x33);
                goto done;
            }
            i++;
            p3++;
        } while (i < 2);
    }
fail:
    WfcTextKb_SetPressedKey(-1);
done:
    sWfcTextKb->deleteHoldTimer = 0;
}
}

extern "C" {
void WfcTextKb_SetPressedKey(s32 a) {
    if (a == sWfcTextKb->highlightKey) return;
    WfcTextKb_SetKeyHighlight(a, 1);
    WfcTextKb_SetKeyHighlight(sWfcTextKb->highlightKey, 0);
    sWfcTextKb->highlightKey = a;
}
}

extern "C" {
void WfcTextKb_HandlePad() {
    if (WfcInput_IsKeyRepeat(0x20)) WfcTextKb_MoveCursor(0);
    if (WfcInput_IsKeyRepeat(0x40)) WfcTextKb_MoveCursor(1);
    if (WfcInput_IsKeyRepeat(0x10)) WfcTextKb_MoveCursor(2);
    if (WfcInput_IsKeyRepeat(0x80)) WfcTextKb_MoveCursor(3);
    if (WfcInput_IsKeyPressed(1)) {
        WfcTextKb *g = sWfcTextKb;
        s32 cur = g->cursorKey;
        if (cur < 0x2f) {
            if (g->insertEnabled == 0) {
                WfcSound_Play(9);
                return;
            }
            g->inputKey = sWfcTextKbCharMaps[g->caseMode][cur];
            if (sWfcTextKb->caseMode != 1) return;
            WfcTextKb_SetMode(0);
            return;
        }
        s32 r = cur - 0x2f;
        if (r < 4) {
            switch (r) {
            case 0:
                WfcTextKb_ToggleCapsLock();
                return;
            case 1:
                WfcTextKb_ToggleShift();
                return;
            case 2:
                if (g->insertEnabled == 0) {
                    WfcSound_Play(9);
                    return;
                }
                break;
            case 3:
                if (g->deleteEnabled == 0) {
                    WfcSound_Play(9);
                    return;
                }
                break;
            }
            if (g->caseMode == 1) {
                WfcTextKb_SetMode(0);
            }
            sWfcTextKb->inputKey = data_ov001_02229bf8[cur - 0x2f];
            return;
        }
        g->inputKey = data_ov001_02229be4[cur - 0x33];
    }
    if (WfcInput_IsKeyRepeat(2)) {
        WfcTextKb *g = sWfcTextKb;
        if (g->deleteEnabled == 0) {
            if (g->errorSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcTextKb->errorSoundPlayed = 1;
            return;
        }
        g->inputKey = 0x80;
    } else {
        if (WfcInput_IsKeyReleased(2)) {
            sWfcTextKb->errorSoundPlayed = 0;
        }
    }
    if (WfcInput_IsKeyPressed(0x400)) WfcTextKb_ToggleCapsLock();
    if (WfcInput_IsKeyPressed(0x800)) WfcTextKb_ToggleShift();
}
}

extern "C" {
void WfcTextKb_SetRowY(s32 a, s32 b, u32 c) {
    WfcTextKbRowCounts x = *(WfcTextKbRowCounts *)data_ov001_0222a84c;
    WfcTextKbRowCounts y = *(WfcTextKbRowCounts *)data_ov001_0222a854;
    WfcTextKbRowCounts z = *(WfcTextKbRowCounts *)data_ov001_0222a844;
    s32 idx = b * 12;
    s32 i;
    for (i = 0; i < x.b[b]; i++) {
        GXOamAttr *r = sWfcTextKb->charKeyOams[idx];
        r->attr01 = r->attr01 & 0xc1fffcff;
        u32 t = data_ov001_02229c28[idx].x;
        r = sWfcTextKb->charKeyOams[idx];
        r->attr01 = ((r->attr01 & 0xfe00ff00) | (u8)c) | ((t & 0x1ff) << 16);
        idx++;
    }
    if (b < 4) {
        WfcTextKb *g = sWfcTextKb;
        WfcText_ArrangeObj(g->rowCanvases[a][b], data_ov001_02229c28[b * 12].x, c, g->rowTextObjs[b], 2);
    }
    s32 n = FX_ModS32(b + 3, 4);
    for (i = 0; i < y.b[b]; i++) {
        GXOamAttr *r = sWfcTextKb->funcKeyOams[n];
        r->attr01 = r->attr01 & 0xc1fffcff;
        r = sWfcTextKb->funcKeyOams[n];
        r->attr01 = ((data_ov001_02229c08[n].x & 0x1ff) << 16) | ((r->attr01 & 0xfe00ff00) | (u8)c);
    }
    for (i = 0; i < z.b[b]; i++) {
        WfcObj_SetAffineMode(sWfcTextKb->bottomButtons[i], -1, 0, 0);
        WfcObj_SetPos(sWfcTextKb->bottomButtons[i], -1, data_ov001_02229c00[i].x, c);
    }
}
}

extern "C" {
void WfcTextKb_SetMode(s32 mode) {
    s32 i, f0, f1, k;
    f0 = 0;
    f1 = 0;
    i = 0;
    k = 0;
    sWfcTextKb->caseMode = mode;
    do {
        WfcTextKb_SetRowY(mode, i, data_ov001_02229c28[k].y);
        i++;
        k += 12;
    } while (i < 4);
    if (mode == 2) {
        f0 = 1;
    } else if (mode == 1) {
        f1 = 1;
    }
    WfcTextKb_SetKeyHighlight(0x2f, f0);
    WfcTextKb_SetKeyHighlight(0x30, f1);
}
}

extern "C" {
void WfcTextKb_SetKeyHighlight(s32 idx, s32 v) {
    if (idx < 0) {
        return;
    }
    if (idx < 0x2f) {
        GXOamAttr *r = sWfcTextKb->charKeyOams[idx];
        r->attr01 = r->attr01 & ~0xc00;
        r->attr2 = (r->attr2 & ~0xf000) | (data_ov001_02229bd8[v] << 12);
    } else if (idx - 0x2f < 4) {
        GXOamAttr *r = sWfcTextKb->funcKeyOams[idx - 0x2f];
        r->attr01 = r->attr01 & ~0xc00;
        r->attr2 = (r->attr2 & ~0xf000) | (data_ov001_02229bd8[v] << 12);
    } else {
        WfcObj_SetModePalette(sWfcTextKb->bottomButtons[idx - 0x33], -1, 0, data_ov001_02229bdc[v]);
    }
}
}

extern "C" {
void WfcTextKb_UpdateCursor() {
    WfcTextKb *g = sWfcTextKb;
    s32 k;
    switch (g->cursorKey) {
    case 0x2f:
        k = 0x42;
        break;
    case 0x30:
        k = 0x41;
        break;
    case 0x31:
        k = 0x43;
        break;
    case 0x32:
        k = 0x41;
        break;
    case 0x33:
    case 0x34:
        k = 0x45;
        break;
    default:
        k = 0x40;
        break;
    }
    WfcCell_Copy(0, k, WfcObj_GetOam(g->cursorObj, 0));
    WfcObj_SetPriority(sWfcTextKb->cursorObj, -1, 2);
    g = sWfcTextKb;
    WfcObj_SetPos(g->cursorObj, -1, data_ov001_02229ce4[g->cursorKey].x, data_ov001_02229ce4[g->cursorKey].y);
}
}

extern "C" {
void WfcTextKb_MoveCursor(s32 a) {
    WfcTextKb *g = sWfcTextKb;
    s32 prev = g->cursorKey;
    s32 cur;
    g->cursorKey = sWfcTextKbNavTable[prev][a];
    g = sWfcTextKb;
    cur = g->cursorKey;
    if (cur == 0x2e && a == 3) {
        g->prevCursorKey = prev;
        goto end;
    }
    if (cur == 0x33 && (a == 1 || a == 3)) {
        g->prevCursorKey = prev;
        goto end;
    }
    if (cur == 0x34 && (a == 1 || a == 3)) {
        if (prev != 0x2e) {
            g->prevCursorKey = prev;
        }
        goto end;
    }
    if (cur == -1) {
        s32 v = g->prevCursorKey;
        if (v == 0x23 || v == 0x32) {
            g->cursorKey = 0x23;
        } else {
            g->cursorKey = 0x22;
        }
    } else if (cur == -2) {
        switch (g->prevCursorKey) {
        case 0:
        case 0x31:
            g->cursorKey = 0x31;
            break;
        case 1:
        case 0x24:
            g->cursorKey = 0x24;
            break;
        case 3:
        case 0x26:
            g->cursorKey = 0x26;
            break;
        case 4:
        case 0x27:
            g->cursorKey = 0x27;
            break;
        case 5:
        case 0x28:
            g->cursorKey = 0x28;
            break;
        default:
            g->cursorKey = 0x25;
            break;
        }
    } else if (cur == -3) {
        switch (g->prevCursorKey) {
        case 6:
        case 0x29:
            g->cursorKey = 0x29;
            break;
        case 7:
        case 0x2a:
            g->cursorKey = 0x2a;
            break;
        case 9:
        case 0x2c:
            g->cursorKey = 0x2c;
            break;
        case 10:
        case 0x2d:
            g->cursorKey = 0x2d;
            break;
        case 0xb:
        case 0x22:
        case 0x23:
        case 0x32:
            g->cursorKey = 0x2e;
            break;
        default:
            g->cursorKey = 0x2b;
            break;
        }
    } else if (cur == -4) {
        switch (g->prevCursorKey) {
        case 0:
        case 0x31:
            g->cursorKey = 0;
            break;
        case 1:
        case 0x24:
            g->cursorKey = 1;
            break;
        case 3:
        case 0x26:
            g->cursorKey = 3;
            break;
        case 4:
        case 0x27:
            g->cursorKey = 4;
            break;
        case 5:
        case 0x28:
            g->cursorKey = 5;
            break;
        default:
            g->cursorKey = 2;
            break;
        }
    } else if (cur == -5) {
        switch (g->prevCursorKey) {
        case 6:
        case 0x29:
            g->cursorKey = 6;
            break;
        case 7:
        case 0x2a:
            g->cursorKey = 7;
            break;
        case 9:
        case 0x2c:
            g->cursorKey = 9;
            break;
        case 10:
        case 0x2d:
            g->cursorKey = 10;
            break;
        case 0xb:
        case 0x22:
            g->cursorKey = 0xb;
            break;
        case 0x23:
        case 0x32:
            g->cursorKey = 0x32;
            break;
        default:
            g->cursorKey = 8;
            break;
        }
    }
end:
    WfcTextKb_UpdateCursor();
    WfcSound_Play(8);
}
}

extern "C" {
void WfcTextKb_SlideOutStep0(void *a, void *work) {
    volatile s32 xy[2];
    u32 *reg = (u32 *)WfcObj_GetOam(sWfcTextKb->bottomButtons[0], 0);
    s32 t;
    xy[0] = (*(volatile u32 *)reg & 0x1ff0000) >> 16;
    t = *(volatile u32 *)reg & 0xff;
    xy[1] = t;
    t += 0xc;
    xy[1] = t;
    WfcTextKb_SetRowY(sWfcTextKb->caseMode, 4, t);
    if (xy[1] < 0xc0) {
        return;
    }
    WfcTask_SetFunc(a, (void *)WfcTextKb_SlideOutStep1);
}
}

extern "C" {
STATE_FN(WfcTextKb_SlideOutStep1, 0x24, 3, WfcTextKb_SlideOutStep2)
}

extern "C" {
STATE_FN(WfcTextKb_SlideOutStep2, 0x18, 2, WfcTextKb_SlideOutStep3)
}

extern "C" {
STATE_FN(WfcTextKb_SlideOutStep3, 0xc, 1, WfcTextKb_SlideOutStep4)
}

extern "C" {
STATE_FN(WfcTextKb_SlideOutStep4, 0, 0, WfcTextKb_Destroy)
}

extern "C" {
void WfcTextKb_Destroy(void *a, void *work) {
    s32 i, j;
    WfcTask_RequestDelete(0, a);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            WfcText_DestroyObjCanvas(sWfcTextKb->rowCanvases[i][j]);
            if (i == 0) {
                WfcObj_Free(sWfcTextKb->rowTextObjs[j]);
            }
        }
    }
    for (i = 0; i < 2; i++) {
        WfcObj_Free(sWfcTextKb->bottomButtons[i]);
    }
    for (i = 0; i < 4; i++) {
        WfcOam_FreeEntry(sWfcTextKb->funcKeyOams[i]);
    }
    for (i = 0; i < 0x2f; i++) {
        WfcOam_FreeEntry(sWfcTextKb->charKeyOams[i]);
    }
    WfcHeap_FreeAndClear((void **)&sWfcTextKb);
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02208c2c) {
    HOST_OVERLAY_VAR(data_ov001_0222a914),
    HOST_OVERLAY_VAR(data_ov001_0222a978),
    HOST_OVERLAY_VAR(data_ov001_0222a9dc),
    HOST_OVERLAY_VAR(data_ov001_0222a884),
    HOST_OVERLAY_VAR(data_ov001_0222a8b4),
    HOST_OVERLAY_VAR(data_ov001_0222a8e4),
    HOST_OVERLAY_VAR(data_ov001_0222a874),
    HOST_OVERLAY_VAR(sWfcTextKbGlyphMaps),
    HOST_OVERLAY_VAR(sWfcTextKbCharMaps),
    HOST_OVERLAY_VAR(data_ov001_0222a844),
    HOST_OVERLAY_VAR(data_ov001_0222a84c),
    HOST_OVERLAY_VAR(data_ov001_0222a854),
    HOST_OVERLAY_VAR(sWfcTextKb),
    HOST_OVERLAY_VARS_END
};
