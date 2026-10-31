#include "types.h"
#include "nitro/gxoam.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226f68.h"

struct WfcBusyIcon {
    void *task;
    GXOamAttr *oam;
    u8 paletteKind;
    u8 animFrame;
};

extern "C" const u16 data_ov001_02229b38[2] = {0xe6, 0x8b};
extern "C" const u8 data_ov001_02229b34[4] = {0x0e, 0x04, 0x05, 0x00};
extern "C" WfcBusyIcon *sWfcBusyIcon = 0;

extern "C" {
s32 FX_ModS32(s32, s32);
s32 FX_DivS32(s32, s32);
void *WfcHeap_AllocClear(u32, u32);
void WfcHeap_FreeAndClear(void *);
}

#pragma thumb off

extern "C" void WfcBusyIcon_Create(u32 idx) {
    WfcBusyIcon *n = (WfcBusyIcon *)WfcHeap_AllocClear(sizeof(WfcBusyIcon), 4);
    sWfcBusyIcon = n;
    n->paletteKind = idx;
    sWfcBusyIcon->oam = WfcObj_CreateSingle(0, 0x47);
    sWfcBusyIcon->oam->attr2 = (sWfcBusyIcon->oam->attr2 & ~0xc00) | 0x400;
    GXOamAttr *o = sWfcBusyIcon->oam;
    o->attr01 = o->attr01 & ~0xc00;
    o->attr2 = (o->attr2 & ~0xf000) | (data_ov001_02229b34[idx] << 12);
    o = sWfcBusyIcon->oam;
    o->attr01 = (o->attr01 & 0xfe00ff00) | (data_ov001_02229b38[1] & 0xff) | ((data_ov001_02229b38[0] & 0x1ff) << 16);
    sWfcBusyIcon->task = WfcTask_Add(1, (void *)WfcBusyIcon_Task, 0, 0x78);
}

extern "C" void WfcBusyIcon_Delete() {
    WfcTask_Delete(1, sWfcBusyIcon->task);
    WfcOam_FreeEntry(sWfcBusyIcon->oam);
    WfcHeap_FreeAndClear(&sWfcBusyIcon);
}

extern "C" void WfcBusyIcon_Task(void *task) {
    sWfcBusyIcon->animFrame = FX_ModS32(sWfcBusyIcon->animFrame + 1, 0x28);
    s32 id = FX_DivS32(sWfcBusyIcon->animFrame, 5) + 0x47;
    WfcCell_Copy(0, id, sWfcBusyIcon->oam);
    sWfcBusyIcon->oam->attr2 = (sWfcBusyIcon->oam->attr2 & ~0xc00) | 0x400;
    WfcBusyIcon *d = sWfcBusyIcon;
    u32 t = data_ov001_02229b34[d->paletteKind];
    GXOamAttr *o = d->oam;
    o->attr01 = o->attr01 & ~0xc00;
    o->attr2 = (o->attr2 & ~0xf000) | (t << 12);
    o = sWfcBusyIcon->oam;
    o->attr01 = (o->attr01 & 0xfe00ff00) | (data_ov001_02229b38[1] & 0xff) | ((data_ov001_02229b38[0] & 0x1ff) << 16);
}

#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02207904) {
    HOST_OVERLAY_VAR(sWfcBusyIcon),
    HOST_OVERLAY_VARS_END
};
