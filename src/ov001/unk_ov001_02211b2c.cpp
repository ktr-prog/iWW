#include "types.h"
#include "host_tick.h"
#include "nitro/gxoam.h"
#include "ui/WfcApList.h"
#include "ui/WfcTextEdit.h"
#include "nitro/io_access.h"
#include "net/WfcLoadFunc.h"
#include "net/WfcRect.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_022118a8.h"
#include "proto/ov001/unk_ov001_02211b2c.h"
#include "proto/ov001/unk_ov001_02213424.h"
#include "proto/ov001/unk_ov001_0221962c.h"
#include "proto/ov001/unk_ov001_0221ab50.h"
#include "proto/ov001/unk_ov001_0221bc10.h"
#include "proto/ov001/unk_ov001_0221cd74.h"
#include "proto/ov001/unk_ov001_0221cfc0.h"
#include "proto/ov001/unk_ov001_0221d744.h"
#include "proto/ov001/unk_ov001_0221dcec.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226c24.h"
#include "proto/ov001/unk_ov001_02226f68.h"

#pragma thumb off

extern "C" {
extern const u8 data_ov001_0222a000[4];
extern const u8 data_ov001_0222a004[4];
extern const WfcRect data_ov001_0222a008[5];
extern const WfcRect data_ov001_0222a030[5];
const u8 data_ov001_0222a000[4] = {0x2e, 0x2d, 0x33, 0};
const u8 data_ov001_0222a004[4] = {0x18, 0x17, 0x16, 0x15};
const WfcRect data_ov001_0222a030[5] = {{4, 0x2e, 0xdb, 0x3f}, {4, 0x4a, 0xdb, 0x5b}, {4, 0x66, 0xdb, 0x77}, {4, 0x82, 0xdb, 0x93}, {0x82, 0x18, 0xf0, 0x2c}};
const WfcRect data_ov001_0222a008[5] = {{7, 0x32, 0xd0, 0x4c}, {7, 0x4e, 0xd0, 0x68}, {7, 0x6a, 0xd0, 0x84}, {7, 0x86, 0xd0, 0xa0}, {0x85, 0x1b, 0xfd, 0x2c}};
u8 data_ov001_0222aea8 = 2;
u8 sWfcApListCursor;
u16 sWfcApListScroll;
WfcApList *sWfcApList;
}


#define BGCNT(a, v) IO_W((volatile u16 *)(a), (IO_R((volatile u16 *)(a)) & ~3) | (v))

extern "C" {
s32 FX_DivS32(s32 numer, s32 denom);
s32 FX_ModS32(s32 numer, s32 denom);
void MI_CpuFill8(void *dst, u8 v, u32 size);
void WfcText_ReleaseBgCanvas(WfcTextCanvas *o);
extern const WfcRect gWfcScreenRect;

void WfcApList_Enter() {
    u32 x;
    sWfcApList = (WfcApList *)WfcHeap_AllocClear(sizeof(WfcApList), 4);
    WfcUtil_GetEditParams(&x, 0);
    if (x == 0) {
        sWfcApListCursor = 0;
        sWfcApListScroll = 0;
    }
    sWfcApList->apCount = WfcApScan_GetResults(&sWfcApList->apEntries);
    WfcApList_LoadBg();
    WfcHighlight_SetConnection();
    WfcUtil_ShowTopMessage(0x80, -1, 0);
    WfcUtil_ShowStepIndicator(2);
    WfcApList_InitScrollBar();
    WfcApList_CreateRowIcons();
    sWfcApList->textCanvas = WfcText_CreateBgCanvas(0, 0);
    sWfcApList->bgScrollTask = WfcTask_Add(1, (void *)WfcApList_ApplyBgScrollTask, 0, 0x6e);
    WfcApList_Redraw();
    WfcApList_UpdateCursor();
    WfcUtil_SetScene(WfcApList_FadeIn);
}

void WfcApList_LoadBg() {
    u8 a[25] = "char/xb4ApListBack.nsc.l";
    u8 b[22] = "char/ybBgStep31.ncl.l";
    WfcUtil_LoadFileTo((void *)"char/jb4ApList.nsc.l", GX_LoadBG3Scr);
    sWfcApList->bgMapFile = WfcFs_LoadFile(WfcUtil_LocalizePath(a), 0, 4);
    WfcBgMap_Create(sWfcApList->bgMapFile);
    WfcBgMap_RequestTransfer();
    sWfcApList->paletteFile = WfcFs_LoadFile(WfcUtil_LocalizePath(b), 0, 4);
    BGCNT(0x4001008, 3);
    BGCNT(0x400100a, 3);
    BGCNT(0x4000008, 3);
    BGCNT(0x400000a, 2);
    BGCNT(0x400000c, 3);
    BGCNT(0x400000e, 2);
}

void WfcApList_InitScrollBar() {
    s32 r = 0;
    s32 m;
    sWfcApList->maxScroll = (sWfcApList->apCount - 4) * 0x1c;
    if (sWfcApList->apCount <= 4) {
        m = r;
        sWfcApList->scrollBarRange = 0;
    } else if (sWfcApList->apCount <= 8) {
        sWfcApList->scrollBarRange = 0x1f;
        m = 1;
    } else {
        sWfcApList->scrollBarRange = 0x37;
        m = 2;
    }
    if (m != 0) {
        r = FX_DivS32(sWfcApListScroll * sWfcApList->scrollBarRange, sWfcApList->maxScroll);
    }
    WfcScrollBar_Create(m, 0x55, 0xec, 0x3f, r);
}

void WfcApList_CreateRowIcons() {
    s32 n, i;
    n = sWfcApList->apCount;
    if (n > 5) n = 5;
    i = 0;
    if (n > 0) {
        u32 a = data_ov001_0222a000[0];
        u32 b = data_ov001_0222a004[0];
        do {
            sWfcApList->securityIcons[i] = WfcObj_CreateSingle(0, a);
            sWfcApList->signalIcons[i] = WfcObj_CreateSingle(0, b);
            i++;
        } while (i < n);
    }
    {
        const u8 *p = data_ov001_0222a000;
        u32 j;
        for (j = 0; j < 3; j++, p++) {
            WfcCell_Copy(0, *p, sWfcApList->securityIcons[0]);
            sWfcApList->securityIconTiles[j] = sWfcApList->securityIcons[0]->attr2 & 0x3ff;
        }
    }
    {
        const u8 *p = data_ov001_0222a004;
        u32 j;
        for (j = 0; j < 4; j++, p++) {
            WfcCell_Copy(0, *p, sWfcApList->signalIcons[0]);
            sWfcApList->signalIconTiles[j] = sWfcApList->signalIcons[0]->attr2 & 0x3ff;
        }
    }
    for (i = 0; i < n; i++) {
        GXOamAttr *r = sWfcApList->securityIcons[i];
        r->attr2 = (r->attr2 & ~0xc00) | 0xc00;
        r = sWfcApList->signalIcons[i];
        r->attr2 = (r->attr2 & ~0xc00) | 0xc00;
    }
}

void WfcApList_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x1d, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x1d);
    WfcUtil_SetScene(WfcApList_WaitFadeIn);
}

void WfcApList_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(0);
    WfcUtil_SetScene(WfcApList_WaitButtonBar);
}

void WfcApList_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcApList_Update);
}

void WfcApList_Update() {
    WfcApList_HandleInput();
    WfcApList_HandleScrollBar();
    WfcApList_HandleResult();
}

void WfcApList_HandleInput() {
    if (sWfcApList->scrollTask != 0) return;
    if (sWfcApList->isDragging != 0) return;
    if (WfcInput_IsTouchPressedIn((WfcRect *)&gWfcScreenRect) != 0) {
        sWfcApList->touchRow = -1;
        u32 i;
        const WfcRect *p = data_ov001_0222a008;
        for (i = 0; i < 5; i++, p++) {
            if (WfcInput_IsTouchPressedIn((WfcRect *)p) != 0) {
                if ((s32)i < 4) {
                    sWfcApList->touchRow = i;
                    break;
                }
                WfcButtonBar_SetResult(1);
                sWfcApListCursor = i;
                WfcApList_UpdateCursor();
                return;
            }
        }
    }
    if (WfcInput_IsTouchReleasedIn((WfcRect *)&gWfcScreenRect) != 0) {
        const WfcRect *p = data_ov001_0222a008;
        s32 i;
        for (i = 0; i < 4; i++, p++) {
            if (WfcInput_IsTouchReleasedIn((WfcRect *)p) != 0) {
                if (sWfcApList->touchRow != i) break;
                if (i >= sWfcApList->apCount) {
                    WfcSound_Play(9);
                    break;
                }
                WfcButtonBar_SetResult(1);
                sWfcApListCursor = i;
                WfcApList_UpdateCursor();
                return;
            }
        }
    }
    if (WfcInput_IsKeyPressed(1) != 0) {
        WfcButtonBar_SetResult(1);
        WfcScrollBar_Disable();
        return;
    }
    if (WfcInput_IsKeyPressed(2) != 0) {
        WfcButtonBar_SetResult(0);
        return;
    }
    if (WfcInput_IsKeyRepeat(0x200) != 0) {
        WfcApList_ScrollDown();
        return;
    }
    if (WfcInput_IsKeyReleased(0x200) != 0) {
        sWfcApList->errorSoundPlayed = 0;
        return;
    }
    if (WfcInput_IsKeyRepeat(0x100) != 0) {
        WfcApList_ScrollUp();
        return;
    }
    if (WfcInput_IsKeyReleased(0x100) != 0) {
        sWfcApList->errorSoundPlayed = 0;
        return;
    }
    if (WfcInput_IsKeyRepeat(0x40) != 0) {
        WfcApList_MoveCursor(1);
        return;
    }
    if (WfcInput_IsKeyReleased(0x40) != 0) {
        sWfcApList->errorSoundPlayed = 0;
        return;
    }
    if (WfcInput_IsKeyRepeat(0x80) != 0) {
        WfcApList_MoveCursor(3);
        return;
    }
    if (WfcInput_IsKeyReleased(0x80) != 0) sWfcApList->errorSoundPlayed = 0;
}

void WfcApList_HandleScrollBar() {
    if (sWfcApList->scrollTask != 0) return;
    if (sWfcApList->dragRedrawDelay != 0) sWfcApList->dragRedrawDelay -= TICK_STEP_ENDS() ? 1 : 0;
    switch (WfcScrollBar_GetEvent()) {
    case 0:
        break;
    case 1:
        sWfcApList->isDragging = 1;
        WfcButtonBar_DisableInput();
        break;
    case 2:
        if (sWfcApList->dragRedrawDelay != 0) return;
        WfcCursor_Clear();
        sWfcApListScroll = FX_DivS32(sWfcApList->maxScroll * WfcScrollBar_GetPos(), sWfcApList->scrollBarRange);
        WfcApList_Redraw();
        sWfcApList->dragRedrawDelay = 4;
        break;
    case 3: {
        sWfcApList->isDragging = 0;
        WfcButtonBar_EnableInput();
        sWfcApListScroll = FX_DivS32(sWfcApList->maxScroll * WfcScrollBar_GetPos(), sWfcApList->scrollBarRange);
        WfcSound_Play(0x13);
        WfcApList_Redraw();
        s32 r = FX_ModS32(sWfcApListScroll, 0x1c);
        if (r == 0) {
            WfcApList_UpdateCursor();
            return;
        }
        if (r < 0xe) sWfcApList->scrollTask = WfcTask_Add(0, (void *)WfcApList_ScrollUpTask, 0, 0x78);
        else sWfcApList->scrollTask = WfcTask_Add(0, (void *)WfcApList_ScrollDownTask, 0, 0x78);
        break;
    }
    case 4:
        if (sWfcApListScroll == 0) {
            if (sWfcApList->scrollEndSoundPlayed != 0) return;
            WfcSound_Play(9);
            sWfcApList->scrollEndSoundPlayed = 1;
        } else {
            WfcSound_Play(0x13);
            sWfcApList->scrollTask = WfcTask_Add(0, (void *)WfcApList_ScrollUpTask, 0, 0x78);
        }
        break;
    case 6:
        if (sWfcApList->apCount > 4) {
            if (sWfcApListScroll != sWfcApList->maxScroll) goto c6b;
        }
        if (sWfcApList->scrollEndSoundPlayed != 0) return;
        WfcSound_Play(9);
        sWfcApList->scrollEndSoundPlayed = 1;
        break;
    c6b:
        WfcSound_Play(0x13);
        sWfcApList->scrollTask = WfcTask_Add(0, (void *)WfcApList_ScrollDownTask, 0, 0x78);
        break;
    case 5:
    case 7:
        sWfcApList->scrollEndSoundPlayed = 0;
        break;
    }
}

void WfcApList_HandleResult() {
    if (sWfcApList->scrollTask != 0) return;
    if (sWfcApList->isDragging != 0) return;
    switch (WfcButtonBar_GetResult()) {
    case 0:
        WfcSound_Play(7);
        break;
    case 1:
        if (sWfcApListCursor == 4) {
            sWfcApList->isConfirmed = 1;
            WfcSound_Play(6);
            WfcApList_HighlightSearchButton();
        } else {
            s32 t = sWfcApListCursor + FX_DivS32(sWfcApListScroll, 0x1c);
            if (sWfcApList->apEntries[t].security == 2) {
                WfcSound_Play(9);
                WfcScrollBar_Disable();
                WfcButtonBar_DisableInput();
                WfcDialog_Open(0x42, 1, 1, -1, 0);
                WfcUtil_SetScene(WfcApList_WaitErrorDialog);
                return;
            }
            sWfcApList->isConfirmed = 1;
            sWfcApList->selectedAp = t;
            WfcSound_Play(6);
        }
        break;
    default:
        return;
    }
    WfcUtil_SetScene(WfcApList_StartExit);
}

void WfcApList_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcApList_FadeOut);
}

void WfcApList_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (sWfcApList->isConfirmed != 0) WfcButtonBar_Close();
    else WfcButtonBar_DisableInput();
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x1d, 8);
    WfcUtil_SetScene(WfcApList_Exit);
}

void WfcApList_Exit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcTask_Delete(1, sWfcApList->bgScrollTask);
    s32 i;
    for (i = 0; i < 5; i++) {
        if (sWfcApList->securityIcons[i] != 0) WfcOam_FreeEntry(sWfcApList->securityIcons[i]);
        if (sWfcApList->signalIcons[i] != 0) WfcOam_FreeEntry(sWfcApList->signalIcons[i]);
    }
    WfcText_ReleaseBgCanvas(sWfcApList->textCanvas);
    WfcScrollBar_Destroy();
    WfcCursor_Clear();
    WfcUtil_HideTopMessage();
    WfcBgMap_Destroy();
    WfcFs_FreeFile(sWfcApList->bgMapFile);
    WfcFs_FreeFile(sWfcApList->paletteFile);
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x1d);
    IO_W((volatile u32 *)0x4000010, 0);
    IO_W((volatile u32 *)0x4000018, 0);
    if (sWfcApList->isConfirmed == 0) {
        WfcApScan_Free();
        WfcConfig_BeginEdit(WfcConfig_GetEdit()->editSlotIndex);
        WfcUtil_SetScreenFlags(2, 0);
        WfcUtil_SetScene(WfcSetupMethod_Enter);
    } else if (sWfcApListCursor == 4) {
        WfcApScan_Free();
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcApSearch_Enter);
    } else {
        WfcConfig_SetEditSsid(sWfcApList->apEntries[sWfcApList->selectedAp].ssid);
        WfcUtil_SetScreenFlags(0, 0);
        if (sWfcApList->apEntries[sWfcApList->selectedAp].security != 0) {
            WfcUtil_SetScreenFlags(0, 1);
            WfcUtil_SetEditParams(1, 1);
            WfcUtil_SetScene(WfcTextEdit_Enter);
        } else {
            WfcUtil_SetScreenFlags(0, 1);
            WfcUtil_SetEditParams(0, 1);
            WfcUtil_SetScene(WfcTestConfirm_Enter);
        }
    }
    WfcHeap_FreeAndClear((void **)&sWfcApList);
}

void WfcApList_Redraw() {
    s32 base = FX_DivS32(sWfcApListScroll, 0x1c);
    s32 n = sWfcApList->apCount;
    WfcText_Clear(sWfcApList->textCanvas, 0);
    if (n > 5) n = 5;
    s32 p, i;
    for (i = 0, p = base; i < n; i++, p++) WfcApList_DrawSsid(p, i);
    for (i = 0, p = base; i < n; i++, p++) WfcApList_SetRowIcons(p, i);
    WfcText_RequestTransfer(sWfcApList->textCanvas);
    WfcApList_LayoutRows();
}

void WfcApList_DrawSsid(s32 a, s32 b) {
    u16 buf[17];
    s32 n = WfcUtil_StrNLen(sWfcApList->apEntries[a].ssid, 0x20);
    u32 r5 = b * 0x1c;
    s32 i;
    if (a >= sWfcApList->apCount) return;
    if (n <= 0x10) r5 += 6;
    MI_CpuFill8(buf, 0, 0x22);
    s32 cnt = n <= 0x10 ? n : 0x10;
    for (i = 0; i < cnt; i++) buf[i] = sWfcApList->apEntries[a].ssid[i];
    WfcText_DrawMonospace(sWfcApList->textCanvas, 0xa, r5, 2, 0xa, buf, 1);
    if (n > 0x10) {
        MI_CpuFill8(buf, 0, 0x22);
        cnt = n - 0x10;
        for (i = 0; i < cnt; i++) buf[i] = sWfcApList->apEntries[a].ssid[i + 0x10];
        WfcText_DrawMonospace(sWfcApList->textCanvas, 0xa, r5 + 0xc, 2, 0xa, buf, 1);
    }
}

void WfcApList_SetRowIcons(s32 a, s32 b) {
    WfcApList *o = sWfcApList;
    if (a >= o->apCount) return;
    WfcApScanEntry *rec = &o->apEntries[a];
    GXOamAttr *p = o->securityIcons[b];
    p->attr2 = (p->attr2 & ~0x3ff) | o->securityIconTiles[rec->security];
    o = sWfcApList;
    rec = &o->apEntries[a];
    GXOamAttr *q = o->signalIcons[b];
    q->attr2 = (q->attr2 & ~0x3ff) | o->signalIconTiles[rec->linkLevel];
}

void WfcApList_LayoutRows() {
    s32 n = FX_ModS32(sWfcApListScroll, 0x1c);
    s32 y = 0x36 - n;
    s32 cnt = sWfcApList->apCount;
    s32 i;
    if (cnt > 5) cnt = 5;
    for (i = 0; i < cnt; i++) {
        GXOamAttr *p = sWfcApList->securityIcons[i];
        p->attr01 = (p->attr01 & 0xfe00ff00) | (u8)(y - 2) | 0xb30000;
        GXOamAttr *q = sWfcApList->signalIcons[i];
        q->attr01 = (q->attr01 & 0xfe00ff00) | (u8)(y + 1) | 0xd20000;
        y += 0x1c;
    }
    sWfcApList->bgScrollPending = 1;
}

void WfcApList_ScrollUpTask(void *task) {
    WfcScrollBar_Disable();
    WfcCursor_Clear();
    if (sWfcApListScroll > 4) sWfcApListScroll = sWfcApListScroll - 4;
    else sWfcApListScroll = 0;
    s32 n = FX_ModS32(sWfcApListScroll, 0x1c);
    if (n == 0x18) {
        WfcApList_Redraw();
        return;
    }
    if (n > 0x18) {
        sWfcApListScroll = sWfcApListScroll + (0x1c - n);
        n = 0;
    }
    WfcApList_LayoutRows();
    if (n != 0) return;
    WfcScrollBar_SetPos(FX_DivS32(sWfcApListScroll * sWfcApList->scrollBarRange, sWfcApList->maxScroll));
    WfcScrollBar_Enable();
    WfcApList_UpdateCursor();
    sWfcApList->scrollTask = 0;
    WfcTask_RequestDelete(0, task);
}

void WfcApList_ScrollDownTask(void *task) {
    WfcScrollBar_Disable();
    WfcCursor_Clear();
    sWfcApListScroll += 4;
    s32 n = FX_ModS32(sWfcApListScroll, 0x1c);
    if (n >= 4) {
        WfcApList_LayoutRows();
        return;
    }
    sWfcApListScroll = sWfcApListScroll - n;
    WfcApList_Redraw();
    WfcScrollBar_SetPos(FX_DivS32(sWfcApListScroll * sWfcApList->scrollBarRange, sWfcApList->maxScroll));
    WfcScrollBar_Enable();
    WfcApList_UpdateCursor();
    sWfcApList->scrollTask = 0;
    WfcTask_RequestDelete(0, task);
}

void WfcApList_ApplyBgScrollTask() {
    if (sWfcApList->bgScrollPending == 0) return;
    u32 v = FX_ModS32(sWfcApListScroll, 0x1c) - 0x32;
    v = (v << 16) & 0x1ff0000;
    IO_W((volatile u32 *)0x4000010, v);
    IO_W((volatile u32 *)0x4000018, v);
    sWfcApList->bgScrollPending = 0;
}

void WfcApList_UpdateCursor() {
    u32 i = sWfcApListCursor;
    WfcCursor_ShowPair(i < 4 ? 2 : 3, data_ov001_0222a030[i].left, data_ov001_0222a030[i].right, data_ov001_0222a030[i].top);
}

void WfcApList_MoveCursor(s32 a) {
    s32 r = 1;
    switch (sWfcApListCursor) {
    case 0:
        if (a == 1) {
            if (sWfcApListScroll == 0) {
                sWfcApListCursor = 4;
            } else {
                WfcSound_Play(0x13);
                sWfcApList->scrollTask = WfcTask_Add(0, (void *)WfcApList_ScrollUpTask, 0, 0x78);
                return;
            }
        } else {
            if (sWfcApList->apCount > 1) sWfcApListCursor = sWfcApListCursor + 1;
            else r = 0;
        }
        break;
    case 1:
    case 2:
        if (a == 1) {
            sWfcApListCursor = sWfcApListCursor - 1;
        } else {
            u32 n = sWfcApListCursor + 1;
            if (sWfcApList->apCount > (s32)n) sWfcApListCursor = n;
            else r = 0;
        }
        break;
    case 3:
        if (a == 1) {
            sWfcApListCursor = sWfcApListCursor - 1;
        } else {
            WfcApList_ScrollDown();
            return;
        }
        break;
    case 4:
        if (a == 1) {
            r = 0;
        } else {
            sWfcApListScroll = 0;
            sWfcApListCursor = 0;
            WfcApList_Redraw();
            WfcScrollBar_SetPos(0);
        }
        break;
    }
    if (r == 0) {
        if (sWfcApList->errorSoundPlayed != 0) return;
        WfcSound_Play(9);
        sWfcApList->errorSoundPlayed = 1;
    } else {
        WfcSound_Play(8);
        WfcApList_UpdateCursor();
    }
}

void WfcApList_ScrollUp() {
    if (sWfcApListScroll == 0) {
        if (sWfcApList->errorSoundPlayed != 0) return;
        WfcSound_Play(9);
        sWfcApList->errorSoundPlayed = 1;
    } else {
        WfcSound_Play(0x13);
        sWfcApList->scrollTask = WfcTask_Add(0, (void *)WfcApList_ScrollUpTask, 0, 0x78);
    }
}

void WfcApList_ScrollDown() {
    WfcApList *o = sWfcApList;
    if (sWfcApListScroll == o->maxScroll || o->apCount <= 4) {
        if (o->errorSoundPlayed != 0) return;
        WfcSound_Play(9);
        sWfcApList->errorSoundPlayed = 1;
    } else {
        WfcSound_Play(0x13);
        sWfcApList->scrollTask = WfcTask_Add(0, (void *)WfcApList_ScrollDownTask, 0, 0x78);
    }
}

void WfcApList_HighlightSearchButton() {
    volatile u8 v = data_ov001_0222aea8;
    u8 t = v;
    WfcUtil_RequestPaletteLine(sWfcApList->paletteFile, t, t);
}

void WfcApList_WaitErrorDialog() {
    if (WfcDialog_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcApList_WaitDialogClosed);
}

void WfcApList_WaitDialogClosed() {
    if (WfcDialog_IsOpen() != 0) return;
    WfcButtonBar_EnableInput();
    WfcScrollBar_Enable();
    WfcUtil_SetScene(WfcApList_Update);
}

}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02211b2c) {
    HOST_OVERLAY_VAR(data_ov001_0222aea8),
    HOST_OVERLAY_VAR(sWfcApListCursor),
    HOST_OVERLAY_VAR(sWfcApListScroll),
    HOST_OVERLAY_VAR(sWfcApList),
    HOST_OVERLAY_VARS_END
};
