#include "types.h"
#include "net/WfcRect.h"
#include "net/WfcObjGroup.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221ea94.h"
#include "proto/ov001/unk_ov001_0221eb38.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

struct WfcHeaderWork {
    WfcObjGroup *parts[5];
    void *task;
    u8 isSlidingOut;
};

extern "C" const u8 sWfcHeaderCells[16];
extern "C" const u8 sWfcHeaderPalettes[16];
extern "C" const WfcPoint sWfcHeaderPartPos[5];
extern "C" WfcHeaderWork *sWfcHeader;

extern "C" {

void WfcObj_GetPos(WfcObjGroup *, s32, s32 *, s32 *);
void WfcObj_SetPos(WfcObjGroup *, s32, s32, s32);
void WfcObj_SetPriority(WfcObjGroup *, s32, s32);
void WfcObj_SetModePalette(WfcObjGroup *, s32, s32, s32);
void WfcObj_Free(WfcObjGroup *);
GXOamAttr *WfcObj_GetOam(WfcObjGroup *, s32);
void WfcCell_Copy(s32, s32, void *);
WfcObjGroup *WfcObj_Create(s32, s32, s32);
void WfcHeap_FreeAndClear(void *);
void *WfcHeap_AllocClear(s32, s32);
void WfcTask_SetFunc(void *, void *);

}

void WfcHeader_Create(s32 n)
{
    s32 i;
    void *p = WfcHeap_AllocClear(sizeof(WfcHeaderWork), 4);
    sWfcHeader = (WfcHeaderWork *)p;
    const u8 *p9 = sWfcHeaderCells + n * 5;
    const u8 *p8 = sWfcHeaderPalettes + n * 5;
    s32 z = 0;
    for (i = 0; i < 5; i++) {
        sWfcHeader->parts[i] = WfcObj_Create(1, *p9, 1);
        WfcObj_SetPriority(sWfcHeader->parts[i], -1, z);
        WfcObj_SetPos(sWfcHeader->parts[i], -1, -0x2a, sWfcHeaderPartPos[i].y);
        WfcObj_SetModePalette(sWfcHeader->parts[i], -1, z, *p8);
        p9++;
        p8++;
    }
    sWfcHeader->task = WfcTask_Add(0, (void *)WfcHeader_SlideInTask0, 0, 0x78);
    WfcTop_LoadScreen(n);
    WfcSound_Play(0xd);
}

void WfcHeader_SlideInTask0(void *r)
{
    s32 a, b, i;
    WfcObj_GetPos(sWfcHeader->parts[0], 0, &a, &b);
    a += 8;
    if (a < sWfcHeaderPartPos[0].x || a > 0x100) {
        for (i = 0; i < 5; i++)
            WfcObj_SetPos(sWfcHeader->parts[i], -1, a, sWfcHeaderPartPos[i].y);
        return;
    }
    a = sWfcHeaderPartPos[0].x;
    for (i = 0; i < 5; i++)
        WfcObj_SetPos(sWfcHeader->parts[i], -1, a, sWfcHeaderPartPos[i].y);
    WfcTask_SetFunc(r, (void *)WfcHeader_SlideInTask1);
}

void WfcHeader_SlideInTask1(void *r)
{
    s32 a, b, i;
    WfcObj_GetPos(sWfcHeader->parts[1], 0, &a, &b);
    a += 8;
    if (a < sWfcHeaderPartPos[1].x || a > 0x100) {
        for (i = 1; i < 5; i++)
            WfcObj_SetPos(sWfcHeader->parts[i], -1, a, sWfcHeaderPartPos[i].y);
        return;
    }
    a = sWfcHeaderPartPos[1].x;
    for (i = 1; i < 5; i++)
        WfcObj_SetPos(sWfcHeader->parts[i], -1, a, sWfcHeaderPartPos[i].y);
    WfcTask_SetFunc(r, (void *)WfcHeader_SlideInTask2);
}

void WfcHeader_SlideInTask2(void *r)
{
    s32 a, b, i;
    WfcObj_GetPos(sWfcHeader->parts[2], 0, &a, &b);
    a += 8;
    if (a < sWfcHeaderPartPos[2].x || a > 0x100) {
        for (i = 2; i < 5; i++)
            WfcObj_SetPos(sWfcHeader->parts[i], -1, a, sWfcHeaderPartPos[i].y);
        return;
    }
    a = sWfcHeaderPartPos[2].x;
    for (i = 2; i < 5; i++)
        WfcObj_SetPos(sWfcHeader->parts[i], -1, a, sWfcHeaderPartPos[i].y);
    WfcTask_SetFunc(r, (void *)WfcHeader_SlideInTask3);
}

void WfcHeader_SlideInTask3(void *r)
{
    s32 a, b, i;
    WfcObj_GetPos(sWfcHeader->parts[3], 0, &a, &b);
    a += 8;
    if (a < sWfcHeaderPartPos[3].x || a > 0x100) {
        for (i = 3; i < 5; i++)
            WfcObj_SetPos(sWfcHeader->parts[i], -1, a, sWfcHeaderPartPos[i].y);
        return;
    }
    a = sWfcHeaderPartPos[3].x;
    for (i = 3; i < 5; i++)
        WfcObj_SetPos(sWfcHeader->parts[i], -1, a, sWfcHeaderPartPos[i].y);
    WfcTask_SetFunc(r, (void *)WfcHeader_SlideInTask4);
}

void WfcHeader_SlideInTask4(void *r)
{
    s32 a, b;
    WfcObj_GetPos(sWfcHeader->parts[4], 0, &a, &b);
    a += 8;
    if (a < sWfcHeaderPartPos[4].x || a > 0x100) {
        WfcObj_SetPos(sWfcHeader->parts[4], -1, a, sWfcHeaderPartPos[4].y);
        return;
    }
    a = sWfcHeaderPartPos[4].x;
    WfcObj_SetPos(sWfcHeader->parts[4], -1, a, sWfcHeaderPartPos[4].y);
    WfcTask_SetFunc(r, (void *)WfcHeader_SlideInDone);
}

void WfcHeader_SlideInDone(void *r)
{
    WfcTask_RequestDelete(0, r);
    sWfcHeader->task = 0;
}

void WfcHeader_StartSlideOut()
{
    sWfcHeader->isSlidingOut = 1;
    sWfcHeader->task = WfcTask_Add(0, (void *)WfcHeader_SlideOutTask4, 0, 0x78);
}

void WfcHeader_SetStep(s32 n)
{
    s32 i;
    const u8 *p9 = sWfcHeaderCells + n * 5;
    const u8 *p8 = sWfcHeaderPalettes + n * 5;
    s32 z = 0;
    for (i = 0; i < 5; i += 2) {
        GXOamAttr *t = WfcObj_GetOam(sWfcHeader->parts[i], z);
        WfcCell_Copy(1, *p9, t);
        WfcObj_SetPriority(sWfcHeader->parts[i], -1, z);
        WfcObj_SetPos(sWfcHeader->parts[i], -1, sWfcHeaderPartPos[i].x, sWfcHeaderPartPos[i].y);
        WfcObj_SetModePalette(sWfcHeader->parts[i], -1, z, *p8);
        p9 += 2;
        p8 += 2;
    }
    WfcTop_LoadScreen(n);
}

s32 WfcHeader_IsAnimating()
{
    if (sWfcHeader->task != 0) return TRUE;
    return FALSE;
}

void WfcHeader_SlideOutTask4(void *r)
{
    s32 a, b;
    WfcObj_GetPos(sWfcHeader->parts[4], 0, &a, &b);
    a -= 8;
    if (a > sWfcHeaderPartPos[3].x) {
        WfcObj_SetPos(sWfcHeader->parts[4], -1, a, sWfcHeaderPartPos[4].y);
        return;
    }
    a = sWfcHeaderPartPos[3].x;
    WfcObj_SetPos(sWfcHeader->parts[4], -1, a, sWfcHeaderPartPos[4].y);
    WfcTask_SetFunc(r, (void *)WfcHeader_SlideOutTask3);
}

void WfcHeader_SlideOutTask3(void *a)
{
    s32 xy[2];
    s32 i;
    WfcObj_GetPos(sWfcHeader->parts[3], 0, &xy[0], &xy[1]);
    xy[0] -= 8;
    if (xy[0] > sWfcHeaderPartPos[2].x) {
        for (i = 3; i < 5; i++) {
            WfcObj_SetPos(sWfcHeader->parts[i], -1, xy[0], sWfcHeaderPartPos[i].y);
        }
        return;
    }
    xy[0] = sWfcHeaderPartPos[2].x;
    for (i = 3; i < 5; i++) {
        WfcObj_SetPos(sWfcHeader->parts[i], -1, xy[0], sWfcHeaderPartPos[i].y);
    }
    WfcTask_SetFunc(a, (void *)WfcHeader_SlideOutTask2);
}

void WfcHeader_SlideOutTask2(void *a)
{
    s32 xy[2];
    s32 i;
    WfcObj_GetPos(sWfcHeader->parts[2], 0, &xy[0], &xy[1]);
    xy[0] -= 8;
    if (xy[0] > sWfcHeaderPartPos[1].x) {
        for (i = 2; i < 5; i++) {
            WfcObj_SetPos(sWfcHeader->parts[i], -1, xy[0], sWfcHeaderPartPos[i].y);
        }
        return;
    }
    xy[0] = sWfcHeaderPartPos[1].x;
    for (i = 2; i < 5; i++) {
        WfcObj_SetPos(sWfcHeader->parts[i], -1, xy[0], sWfcHeaderPartPos[i].y);
    }
    WfcTask_SetFunc(a, (void *)WfcHeader_SlideOutTask1);
}

void WfcHeader_SlideOutTask1(void *a)
{
    s32 xy[2];
    s32 i;
    WfcObj_GetPos(sWfcHeader->parts[1], 0, &xy[0], &xy[1]);
    xy[0] -= 8;
    if (xy[0] > sWfcHeaderPartPos[0].x) {
        for (i = 1; i < 5; i++) {
            WfcObj_SetPos(sWfcHeader->parts[i], -1, xy[0], sWfcHeaderPartPos[i].y);
        }
        return;
    }
    xy[0] = sWfcHeaderPartPos[0].x;
    for (i = 1; i < 5; i++) {
        WfcObj_SetPos(sWfcHeader->parts[i], -1, xy[0], sWfcHeaderPartPos[i].y);
    }
    WfcTask_SetFunc(a, (void *)WfcHeader_SlideOutTask0);
}

void WfcHeader_SlideOutTask0(void *a)
{
    s32 xy[2];
    s32 i;
    WfcObj_GetPos(sWfcHeader->parts[0], 0, &xy[0], &xy[1]);
    xy[0] -= 8;
    for (i = 0; i < 5; i++) {
        WfcObj_SetPos(sWfcHeader->parts[i], -1, xy[0], sWfcHeaderPartPos[i].y);
    }
    if (xy[0] > 0x1d6) return;
    if (xy[0] < 0x100) return;
    WfcTask_RequestDelete(0, a);
    for (i = 0; i < 5; i++) {
        WfcObj_Free(sWfcHeader->parts[i]);
    }
    WfcHeap_FreeAndClear(&sWfcHeader);
}

BOOL WfcHeader_IsSlideOutDone()
{
    WfcHeaderWork *g = sWfcHeader;
    if (g == 0) return TRUE;
    return g->isSlidingOut == 0 ? TRUE : FALSE;
}

extern "C" const u8 sWfcHeaderPalettes[16];
extern "C" const u8 sWfcHeaderCells[16];
extern "C" const WfcPoint sWfcHeaderPartPos[5];

extern "C" const u8 sWfcHeaderPalettes[16] = {2, 1, 3, 1, 3, 5, 1, 4, 1, 5, 7, 1, 7, 1, 6, 0};

extern "C" const u8 sWfcHeaderCells[16] = {1, 0, 5, 0, 6, 4, 0, 2, 0, 6, 4, 0, 5, 0, 3, 0};

extern "C" const WfcPoint sWfcHeaderPartPos[5] = {{0x20, 0x21}, {0x50, 0x30}, {0x68, 0x21}, {0x98, 0x30}, {0xb0, 0x21}};

extern "C" WfcHeaderWork *sWfcHeader = 0;

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221eb38) {
    HOST_OVERLAY_VAR(sWfcHeader),
    HOST_OVERLAY_VARS_END
};
