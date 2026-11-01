#include "types.h"
#include "host_tick.h"
#include "net/WfcObjGroup.h"
#include "net/WfcRect.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02226f68.h"
#include "proto/ov001/unk_ov001_0222449c.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"

struct WfcButtonBar {
    WfcObjGroup *buttonObjs[2];
    WfcObjGroup *barObj;
    void *task;
    void *pressAnimTask;
    u16 timer;
    s8 result;
    u8 kind;
    u8 isInputDisabled;
    u8 isClosing;
};


extern "C" WfcButtonBar *sWfcButtonBar = 0;
extern "C" const u16 data_ov001_02229b3c[2] = {0, 0xa8};
extern "C" const u8 data_ov001_02229b44[8] = {2, 1, 1, 2, 1, 1, 2, 0};
extern "C" const WfcPoint data_ov001_02229b4c[2] = {{8, 0xac}, {0x84, 0xac}};
extern "C" const WfcPoint data_ov001_02229b40 = {0x78, 0x10};
extern "C" const u8 data_ov001_02229b54[16] = {0x27, 0x1f, 0x25, 0, 0x27, 0, 0x23, 0x1d, 0x21, 0, 0x59, 0, 0x27, 0x21, 0, 0};
extern "C" const u8 data_ov001_02229b64[16] = {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0};

extern "C" {
void WfcObj_Free(WfcObjGroup *p);
void WfcTask_SetFunc(void *task, void *v);
void WfcUtil_RectFromPosSize(WfcPoint *a, WfcPoint *b, WfcRect *out);
}

#pragma thumb off

extern "C" void WfcButtonBar_Create(u32 idx) {
    s32 n = data_ov001_02229b44[idx];
    s32 i;
    const u8 *q;
    sWfcButtonBar = (WfcButtonBar *)WfcHeap_AllocClear(sizeof(WfcButtonBar), 4);
    sWfcButtonBar->result = -2;
    sWfcButtonBar->kind = idx;
    i = 0;
    if (i < n) {
        q = data_ov001_02229b54 + idx * 2;
        do {
            sWfcButtonBar->buttonObjs[i] = WfcObj_Create(0, *q, 1);
            WfcObj_SetPriority(sWfcButtonBar->buttonObjs[i], -1, 1);
            i++;
            q++;
        } while (i < n);
    }
    sWfcButtonBar->barObj = WfcObj_Create(0, 1, 1);
    WfcObj_SetPriority(sWfcButtonBar->barObj, -1, 1);
    WfcButtonBar_SetY(0xc0);
    sWfcButtonBar->task = WfcTask_Add(0, (void *)WfcButtonBar_SlideInTask, 0, 0x78);
}

extern "C" void WfcButtonBar_Close() {
    sWfcButtonBar->isClosing = 1;
    WfcTask_SetFunc(sWfcButtonBar->task, (void *)WfcButtonBar_SlideOutTask);
}

extern "C" s32 WfcButtonBar_GetResult() {
    return sWfcButtonBar->result;
}

extern "C" void WfcButtonBar_SetResult(s32 v) {
    if (sWfcButtonBar->result == -1) {
        sWfcButtonBar->result = v;
    }
}

extern "C" void WfcButtonBar_ForceResult(s32 v) {
    sWfcButtonBar->result = v;
}

extern "C" BOOL WfcButtonBar_IsClosed() {
    if (sWfcButtonBar == NULL) {
        return TRUE;
    }
    return sWfcButtonBar->isClosing == 0 ? TRUE : FALSE;
}

extern "C" void WfcButtonBar_EnableInput() {
    sWfcButtonBar->isInputDisabled = 0;
}

extern "C" void WfcButtonBar_DisableInput() {
    sWfcButtonBar->isInputDisabled = 1;
}

extern "C" void WfcButtonBar_SetY(s32 y) {
    WfcButtonBar *g = sWfcButtonBar;
    s32 n = data_ov001_02229b44[g->kind];
    s32 a = y + data_ov001_02229b4c[0].y;
    s32 b = a - data_ov001_02229b3c[1];
    s32 i;
    WfcObj_SetPos(g->barObj, -1, data_ov001_02229b3c[0], y);
    for (i = 0; i < n; i++) {
        WfcButtonBar *s = sWfcButtonBar;
        const u8 *q = data_ov001_02229b64 + s->kind * 2;
        WfcObj_SetPos(s->buttonObjs[i], -1, data_ov001_02229b4c[q[i]].x, b);
    }
}

extern "C" void WfcButtonBar_SlideInTask(void *task, void *work) {
    u32 v[2];
    WfcObj_GetPos(sWfcButtonBar->barObj, 0, &v[0], &v[1]);
    v[1] -= 4;
    WfcButtonBar_SetY(v[1]);
    if ((s32)v[1] > data_ov001_02229b3c[1]) {
        return;
    }
    WfcButtonBar_SetY(data_ov001_02229b3c[1]);
    WfcTask_SetFunc(task, (void *)WfcButtonBar_SettleTask);
}

extern "C" void WfcButtonBar_SettleTask(void *task, void *work) {
    sWfcButtonBar->result = -1;
    sWfcButtonBar->timer += TICK_STEP_ENDS() ? 1 : 0;
    if (sWfcButtonBar->timer < 4) {
        return;
    }
    sWfcButtonBar->timer = 0;
    WfcTask_SetFunc(task, (void *)WfcButtonBar_InputTask);
}

extern "C" void WfcButtonBar_InputTask(void *task, void *work) {
    WfcButtonBar *g = sWfcButtonBar;
    s32 n = data_ov001_02229b44[g->kind];
    s32 i;
    WfcRect out;
    if (g->isInputDisabled == 0) {
        if (g->result != -1) {
            return;
        }
        for (i = 0; i < n; i++) {
            const u8 *q = data_ov001_02229b64 + sWfcButtonBar->kind * 2;
            WfcUtil_RectFromPosSize((WfcPoint *)&data_ov001_02229b4c[q[i]], (WfcPoint *)&data_ov001_02229b40, &out);
            if (WfcInput_IsTouchPressedIn(&out) != 0) {
                WfcButtonBar *s = sWfcButtonBar;
                if (s->pressAnimTask != 0) {
                    break;
                }
                const u8 *q1 = data_ov001_02229b54 + s->kind * 2;
                u32 id = q1[i] + 1;
                WfcCell_Copy(0, id, WfcObj_GetOam(s->buttonObjs[i], 0));
                s = sWfcButtonBar;
                const u8 *q2 = data_ov001_02229b64 + s->kind * 2;
                const WfcPoint *pos = &data_ov001_02229b4c[q2[i]];
                WfcObj_SetPos(s->buttonObjs[i], -1, pos->x, pos->y);
                WfcObj_SetPriority(sWfcButtonBar->buttonObjs[i], -1, 1);
                sWfcButtonBar->pressAnimTask = WfcTask_Add(0, (void *)WfcButtonBar_PressAnimTask, 0, 0x6e);
                sWfcButtonBar->result = i;
                return;
            }
        }
    }
    sWfcButtonBar->result = -1;
}

extern "C" void WfcButtonBar_SlideOutTask(void *task, void *work) {
    u32 v[2];
    WfcObj_GetPos(sWfcButtonBar->barObj, 0, &v[0], &v[1]);
    v[1] += 4;
    WfcButtonBar_SetY(v[1]);
    if ((s32)v[1] < 0xc0) {
        return;
    }
    WfcTask_SetFunc(task, (void *)WfcButtonBar_DestroyTask);
}

extern "C" void WfcButtonBar_DestroyTask(void *task, void *work) {
    s32 i;
    WfcTask_RequestDelete(0, task);
    if (sWfcButtonBar->pressAnimTask != 0) {
        WfcTask_RequestDelete(0, sWfcButtonBar->pressAnimTask);
    }
    for (i = 0; i < 2; i++) {
        if (sWfcButtonBar->buttonObjs[i] != NULL) {
            WfcObj_Free(sWfcButtonBar->buttonObjs[i]);
        }
    }
    WfcObj_Free(sWfcButtonBar->barObj);
    WfcHeap_FreeAndClear((void **)&sWfcButtonBar);
}

extern "C" void WfcButtonBar_PressAnimTask(void *task, void *work) {
    WfcButtonBar *g = sWfcButtonBar;
    g->timer += TICK_STEP_ENDS() ? 1 : 0;
    if (sWfcButtonBar->timer < 0x10) {
        return;
    }
    s32 n = data_ov001_02229b44[sWfcButtonBar->kind];
    s32 i;
    for (i = 0; i < n; i++) {
        WfcButtonBar *s = sWfcButtonBar;
        const u8 *q = data_ov001_02229b54 + s->kind * 2;
        u32 id = q[i];
        WfcCell_Copy(0, id, WfcObj_GetOam(s->buttonObjs[i], 0));
        WfcObj_SetPriority(sWfcButtonBar->buttonObjs[i], -1, 1);
    }
    WfcButtonBar_SetY(data_ov001_02229b3c[1]);
    sWfcButtonBar->timer = 0;
    sWfcButtonBar->result = -1;
    if (sWfcButtonBar->pressAnimTask != 0) {
        sWfcButtonBar->pressAnimTask = 0;
        WfcTask_RequestDelete(0, task);
    }
}

#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02207b3c) {
    HOST_OVERLAY_VAR(sWfcButtonBar),
    HOST_OVERLAY_VARS_END
};
