#include "types.h"
#include "proto/ov001/unk_ov001_0220864c.h"

extern "C" {
extern void WfcObj_Free(void *);
extern void *WfcObj_Create(s32, s32, s32);
extern void WfcObj_SetPriority(void *, s32, s32);
extern void WfcObj_SetPos(void *, s32, s32, s32);
extern void WfcHeap_FreeAndClear(void *);
extern void *WfcHeap_AllocClear(s32, s32);
}

extern "C" const u8 data_ov001_02229bc4[8] = {0x0a, 0x0b, 0x04, 0x05, 0x02, 0x03, 0x0c, 0x0d};
extern "C" {
void **sWfcCursor;
}

#pragma thumb off

extern "C" void WfcCursor_Init() {
    sWfcCursor = (void **)WfcHeap_AllocClear(0x10, 4);
}

extern "C" void WfcCursor_Free() {
    WfcCursor_Clear();
    WfcHeap_FreeAndClear(&sWfcCursor);
}

extern "C" void WfcCursor_ShowPair(s32 idx, s32 a, s32 b, s32 c) {
    s32 i;
    const u8 *p;
    WfcCursor_Clear();
    p = &data_ov001_02229bc4[idx * 2];
    for (i = 0; i < 2; i++, p++) {
        sWfcCursor[i] = WfcObj_Create(0, *p, 1);
        WfcObj_SetPriority(sWfcCursor[i], -1, 1);
    }
    WfcObj_SetPos(sWfcCursor[0], -1, a, c);
    WfcObj_SetPos(sWfcCursor[1], -1, b, c);
}

extern "C" void WfcCursor_ShowCorners(s32 a, s32 b, s32 c, s32 d) {
    s32 k = 6;
    s32 i;
    WfcCursor_Clear();
    for (i = 0; i < 4; i++, k++) {
        sWfcCursor[i] = WfcObj_Create(0, k, 1);
        WfcObj_SetPriority(sWfcCursor[i], -1, 1);
    }
    WfcObj_SetPos(sWfcCursor[0], -1, a, c);
    WfcObj_SetPos(sWfcCursor[1], -1, b, c);
    WfcObj_SetPos(sWfcCursor[2], -1, a, d);
    WfcObj_SetPos(sWfcCursor[3], -1, b, d);
}

extern "C" void WfcCursor_Clear() {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (sWfcCursor[i] != 0) {
            WfcObj_Free(sWfcCursor[i]);
            sWfcCursor[i] = 0;
        }
    }
}

#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220864c) {
    HOST_OVERLAY_VAR(sWfcCursor),
    HOST_OVERLAY_VARS_END
};
