#include "types.h"
#include "host_tick.h"
#include "net/WfcRect.h"
#include "net/WfcObjGroup.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220cbd0.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_0222449c.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

struct WfcTask;
struct WfcBgTextCanvas;

struct WfcDialogWork {
    WfcObjGroup *frameObj;
    WfcObjGroup *textObj;
    WfcObjGroup *buttons[2];
    WfcTextCanvas *textCanvas;
    WfcTask *task;
    u16 autoCloseTimer;
    s8 brightness;
    s8 result;
    u8 style;
    u8 closeTimer;
    u8 dimBackground;
};

extern "C" {
void WfcObj_Free(WfcObjGroup *p);
void WfcTask_SetFunc(WfcTask *n, void *v);
void WfcUtil_RectFromPosSize(WfcPoint *a, WfcPoint *b, WfcRect *out);
void G2x_ChangeBlendBrightness_(u16 *p, s32 v);
void G2x_SetBlendBrightness_(u16 *p, u32 a, s32 v);

void WfcDialog_ClipObj(WfcObjGroup *a, s32 b);
}

#define REG_BLDCNT ((u16 *)0x4000050)

extern "C" const u8 sWfcDialogButtonCells[6][2];
extern "C" const WfcPoint data_ov001_0222a38c;
extern "C" const u8 sWfcDialogFrameCells[8];
extern "C" WfcDialogWork *sWfcDialog;
extern "C" const u8 sWfcDialogButtonCounts[8];
extern "C" const WfcRect data_ov001_0222a3a0;
extern "C" const u8 data_ov001_0222a3a8[6][2];
extern "C" const WfcPoint data_ov001_0222a3cc[5];
extern "C" const u16 data_ov001_0222a3e0[6][2];
extern "C" const WfcPoint data_ov001_0222a3f8[6];
extern "C" const s8 sWfcDialogKeyButtons[6][2];
extern "C" const WfcPoint data_ov001_0222a410[6];
extern "C" const WfcPoint sWfcDialogButtonPos[5][2];

extern "C" const u8 sWfcDialogButtonCells[6][2] = {{0x1b, 0x19}, {0x57, 0}, {0x23, 0x1d}, {0x59, 0}, {0x23, 0x1d}, {0, 0}};

extern "C" {

void WfcDialog_Open(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    u8 buf[6] = {1, 1, 0, 0, 1, 1};
    WfcDialogWork *g;
    u16 *v;
    u32 out;
    s32 i;

    v = WfcMsg_GetStringWithDigit((WfcMsgBank *)gWfcMsgBank, a, d, e);
    g = (WfcDialogWork *)WfcHeap_AllocClear(sizeof(WfcDialogWork), 4);
    sWfcDialog = g;
    g->style = b;
    sWfcDialog->result = -2;
    sWfcDialog->dimBackground = c;
    G2x_SetBlendBrightness_(REG_BLDCNT, 0x1f, 0);
    sWfcDialog->frameObj = WfcObj_Create(0, sWfcDialogFrameCells[b], 0);
    WfcObj_SetPos(sWfcDialog->frameObj, -1, 0x100, 0);
    WfcObj_SetPriority(sWfcDialog->frameObj, -1, 0);
    for (i = 0; i < sWfcDialogButtonCounts[b]; i++) {
        sWfcDialog->buttons[i] = WfcObj_Create(0, sWfcDialogButtonCells[b][i], 0);
        WfcObj_SetPos(sWfcDialog->buttons[i], -1, 0x100, 0);
        WfcObj_SetPriority(sWfcDialog->buttons[i], -1, 0);
    }
    sWfcDialog->textCanvas = WfcText_CreateObjCanvas(0, 0x20, 0xc, 1, &out, 0);
    sWfcDialog->textObj = WfcObj_Alloc(0, out, 0);
    WfcText_DrawTextRect(sWfcDialog->textCanvas, 0, 0, data_ov001_0222a3e0[b][0], data_ov001_0222a3e0[b][1], 2, WfcUtil_GetTextFlags(), v);
    WfcText_ArrangeObj(sWfcDialog->textCanvas, 0x100, 0, sWfcDialog->textObj, 0);
    WfcGx_SetWindowPlanes(0, 0, 0x1f, 0);
    WfcGx_SetWindowPlanes(0, 1, 0x1f, buf[sWfcDialog->style]);
    WfcGx_SetWindowPlanes(0, 3, 0x1f, 1);
    WfcGx_SetWindowRect(0, 1, const_cast<WfcRect *>(&data_ov001_0222a3a0));
    WfcDialog_SetY(0xc0);
    {
        volatile u32 *reg = (volatile u32 *)0x4000000;
        IO_W(reg, (IO_R(reg) & ~0xe000) | 0x6000);
    }
    if (c != 0) {
        sWfcDialog->task = (WfcTask *)WfcTask_Add(1, (void *)WfcDialog_DimTask, 0, 0x78);
    } else {
        sWfcDialog->task = (WfcTask *)WfcTask_Add(1, (void *)WfcDialog_SlideInTask, 0, 0x78);
    }
}

void WfcDialog_Close()
{
    WfcTask_RequestDelete(0, sWfcDialog->task);
    sWfcDialog->task = (WfcTask *)WfcTask_Add(1, (void *)WfcDialog_CloseDelayTask, 0, 0x78);
}

s32 WfcDialog_GetResult()
{
    return sWfcDialog->result;
}

BOOL WfcDialog_IsOpen()
{
    if (sWfcDialog != 0) {
        return TRUE;
    }
    return FALSE;
}

void WfcDialog_DimTask(WfcTask *task)
{
    sWfcDialog->brightness = sWfcDialog->brightness - 1;
    G2x_ChangeBlendBrightness_(REG_BLDCNT, sWfcDialog->brightness);
    if (sWfcDialog->brightness > -12) {
        return;
    }
    WfcTask_SetFunc(task, (void *)WfcDialog_SlideInTask);
}

void WfcDialog_SlideInTask(WfcTask *task)
{
    u32 x, objY;
    s32 y;
    s32 k;
    WfcObj_GetPos(sWfcDialog->frameObj, 0, &x, &objY);
    y = objY - 12;
    k = data_ov001_0222a3f8[sWfcDialog->style].y;
    if (y > k) {
        WfcDialog_SetY(y);
        return;
    }
    WfcDialog_SetY(k);
    if (sWfcDialog->style == 5) {
        sWfcDialog->task = (WfcTask *)WfcTask_Add(0, (void *)WfcDialog_AutoCloseTask, 0, 0x78);
    } else {
        sWfcDialog->task = (WfcTask *)WfcTask_Add(0, (void *)WfcDialog_InputTask, 0, 0x78);
    }
    WfcTask_RequestDelete(1, task);
}

void WfcDialog_InputTask(WfcTask *task)
{
    s32 i;
    WfcRect loc;
    WfcDialogWork *g;

    for (i = 0; i < sWfcDialogButtonCounts[sWfcDialog->style]; i++) {
        u32 idx = data_ov001_0222a3a8[sWfcDialog->style][i];
        WfcUtil_RectFromPosSize(const_cast<WfcPoint *>(&sWfcDialogButtonPos[sWfcDialog->style][idx]),
                                const_cast<WfcPoint *>(&data_ov001_0222a3cc[sWfcDialog->style]), &loc);
        if (WfcInput_IsTouchPressedIn(&loc) != 0) {
            sWfcDialog->result = i;
            break;
        }
    }
    if (WfcInput_IsKeyPressed(1) != 0) {
        sWfcDialog->result = sWfcDialogKeyButtons[sWfcDialog->style][0];
    }
    if (WfcInput_IsKeyPressed(2) != 0) {
        sWfcDialog->result = sWfcDialogKeyButtons[sWfcDialog->style][1];
    }
    g = sWfcDialog;
    for (i = 0; i < sWfcDialogButtonCounts[*(volatile u8 *)&g->style]; i++) {
        if (i == g->result) {
            WfcDialog_PressButton(i);
            return;
        }
    }
    g->result = -1;
}

void WfcDialog_AutoCloseTask(WfcTask *task)
{
    WfcDialogWork *g = sWfcDialog;
    g->result = -1;
    sWfcDialog->autoCloseTimer = sWfcDialog->autoCloseTimer + (TICK_STEP_ENDS() ? 1 : 0);
    if (sWfcDialog->autoCloseTimer < 0x78) {
        return;
    }
    WfcTask_RequestDelete(0, task);
    sWfcDialog->task = (WfcTask *)WfcTask_Add(1, (void *)WfcDialog_CloseDelayTask, 0, 0x78);
}

void WfcDialog_SetY(s32 r)
{
    s32 k;
    s32 i;
    WfcDialogWork *g;

    g = sWfcDialog;
    WfcObj_SetPos(g->frameObj, -1, data_ov001_0222a3f8[g->style].x, r);
    g = sWfcDialog;
    WfcObj_SetPos(g->textObj, -1, data_ov001_0222a38c.x + data_ov001_0222a3f8[g->style].x, r + data_ov001_0222a38c.y);
    WfcDialog_ClipObj(sWfcDialog->frameObj, r);
    WfcDialog_ClipObj(sWfcDialog->textObj, r);
    for (i = 0; i < sWfcDialogButtonCounts[k = sWfcDialog->style]; i++) {
        g = sWfcDialog;
        u32 idx = data_ov001_0222a3a8[g->style][i];
        WfcObj_SetPos(g->buttons[i], -1, sWfcDialogButtonPos[g->style][idx].x,
                            r + sWfcDialogButtonPos[g->style][idx].y - data_ov001_0222a3f8[g->style].y);
        WfcDialog_ClipObj(sWfcDialog->buttons[i], r);
    }
    {
        s32 t = r & 0xff;
        s32 y1, y2;
        if (t >= 0xc0) {
            y2 = 0;
            y1 = 0;
        } else {
            y1 = t;
            y2 = t + data_ov001_0222a410[k].y;
        }
        WfcRect loc;
        if (y2 > 0xc0) {
            y2 = 0xc0;
        }
        WfcUtil_SetRect(data_ov001_0222a3f8[k].x, y1, data_ov001_0222a3f8[k].x + data_ov001_0222a410[k].x, y2, &loc);
        WfcGx_SetWindowRect(0, 0, &loc);
    }
}

void WfcDialog_ClipObj(WfcObjGroup *a, s32 b)
{
    s32 n = WfcObj_GetCount(a);
    s32 i;
    u32 x, objY;
    for (i = 0; i < n; i++) {
        WfcObj_GetPos(a, i, &x, &objY);
        s32 y = objY;
        s32 v;
        if (y >= b && y < 0xc0) {
            v = 0;
        } else {
            v = 0x200;
        }
        WfcObj_SetAffineMode(a, i, v, 0);
    }
}

void WfcDialog_PressButton(s32 i)
{
    GXOamAttr *o = WfcObj_GetOam(sWfcDialog->buttons[i], 0);
    WfcCell_Copy(0, sWfcDialogButtonCells[sWfcDialog->style][i] + 1, o);
    u32 t = sWfcDialog->style;
    WfcObjGroup *p = sWfcDialog->buttons[i];
    u32 idx = data_ov001_0222a3a8[t][i];
    WfcObj_SetPos(p, -1, sWfcDialogButtonPos[t][idx].x, sWfcDialogButtonPos[t][idx].y);
    WfcObj_SetPriority(sWfcDialog->buttons[i], -1, 0);
}

void WfcDialog_CloseDelayTask(WfcTask *task)
{
    sWfcDialog->closeTimer += TICK_STEP_ENDS() ? 1 : 0;
    if (sWfcDialog->closeTimer < 8) {
        return;
    }
    WfcTask_SetFunc(task, (void *)WfcDialog_SlideOutTask);
}

void WfcDialog_SlideOutTask(WfcTask *task)
{
    u32 x, objY;
    s32 y;
    WfcObj_GetPos(sWfcDialog->frameObj, 0, &x, &objY);
    y = objY + 0xc;
    WfcDialog_SetY(y);
    if (y < 0xc0) {
        return;
    }
    if (sWfcDialog->dimBackground != 0) {
        WfcTask_SetFunc(task, (void *)WfcDialog_UndimTask);
    } else {
        WfcTask_SetFunc(task, (void *)WfcDialog_DestroyTask);
    }
}

void WfcDialog_UndimTask(WfcTask *task)
{
    sWfcDialog->brightness++;
    G2x_ChangeBlendBrightness_(REG_BLDCNT, sWfcDialog->brightness);
    if (sWfcDialog->brightness < 0) {
        return;
    }
    WfcTask_SetFunc(task, (void *)WfcDialog_DestroyTask);
}

void WfcDialog_DestroyTask(WfcTask *task)
{
    s32 i;
    IO_AND((volatile u32 *)0x4000000, ~0xe000);
    WfcObj_Free(sWfcDialog->frameObj);
    WfcObj_Free(sWfcDialog->textObj);
    for (i = 0; i < sWfcDialogButtonCounts[sWfcDialog->style]; i++) {
        if (sWfcDialog->buttons[i] != NULL) {
            WfcObj_Free(sWfcDialog->buttons[i]);
        }
    }
    WfcText_DestroyObjCanvas(sWfcDialog->textCanvas);
    WfcTask_RequestDelete(1, task);
    WfcHeap_FreeAndClear((void **)&sWfcDialog);
}

}

extern "C" const WfcPoint data_ov001_0222a38c = {8, 8};

extern "C" const u8 sWfcDialogFrameCells[8] = {0, 0, 0x46, 0x46, 0x4f, 0x2f, 0, 0};

extern "C" WfcDialogWork *sWfcDialog = 0;

extern "C" const u8 sWfcDialogButtonCounts[8] = {2, 1, 2, 1, 2, 0, 0, 0};

extern "C" const WfcRect data_ov001_0222a3a0 = {4, 0x1d, 0xfc, 0x44};

extern "C" const u8 data_ov001_0222a3a8[6][2] = {{0, 1}, {1, 0}, {0, 1}, {1, 0}, {0, 1}, {0, 0}};

extern "C" const WfcPoint data_ov001_0222a3cc[5] = {{0x6c, 0x10}, {0x6c, 0x10}, {0x78, 0x10}, {0x78, 0x10}, {0x78, 0x10}};

extern "C" const u16 data_ov001_0222a3e0[6][2] = {{0xd8, 0x50}, {0xd8, 0x50}, {0xe6, 0x4f}, {0xe6, 0x4f}, {0xe6, 0x48}, {0xda, 0x5c}};

extern "C" const WfcPoint data_ov001_0222a3f8[6] = {{0xb, 0x27}, {0xb, 0x27}, {4, 0x4c}, {4, 0x4c}, {4, 0x54}, {0xb, 0x27}};

extern "C" const s8 sWfcDialogKeyButtons[6][2] = {{1, 0}, {0, -1}, {1, 0}, {0, -1}, {1, 0}, {0, 0}};

extern "C" const WfcPoint data_ov001_0222a410[6] = {{0xea, 0x72}, {0xea, 0x72}, {0xf8, 0x70}, {0xf8, 0x70}, {0x64, 0x70}, {0xea, 0x72}};

extern "C" const WfcPoint sWfcDialogButtonPos[5][2] = {{{0x10, 0x84}, {0x84, 0x84}}, {{0x10, 0x84}, {0x84, 0x84}}, {{9, 0xa7}, {0x83, 0xa7}}, {{9, 0xa7}, {0x83, 0xa7}}, {{9, 0xa7}, {0x83, 0xa7}}};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0221feac) {
    HOST_OVERLAY_VAR(sWfcDialog),
    HOST_OVERLAY_VARS_END
};
