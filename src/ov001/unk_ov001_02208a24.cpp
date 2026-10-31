#include "types.h"
#include "ui/WfcLinkIcon.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02208a24.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226f68.h"

extern "C" {
extern void WfcHeap_FreeAndClear(void *);
extern void *WfcHeap_Alloc(s32, s32);
extern u32 WM_GetAllowedChannel();
extern u32 WM_GetLinkLevel();
}

extern "C" const u16 data_ov001_02229bcc[2] = {0xe5, 0x26};
extern "C" const u8 data_ov001_02229bd0[2][4] = {{0x18, 0x17, 0x16, 0x15}, {0x5f, 0x5e, 0x5d, 0x5c}};
extern "C" {
WfcLinkIcon *sWfcLinkIcon;
}

#pragma thumb off

extern "C" void WfcLinkIcon_Create(s32 a) {
    if (sWfcLinkIcon != NULL) {
        return;
    }
    sWfcLinkIcon = (WfcLinkIcon *)WfcHeap_Alloc(sizeof(WfcLinkIcon), 4);
    sWfcLinkIcon->iconSet = a;
    sWfcLinkIcon->oam = WfcObj_CreateSingle(0, data_ov001_02229bd0[a][0]);
    sWfcLinkIcon->oam->attr01 = (sWfcLinkIcon->oam->attr01 & 0xfe00ff00) | (data_ov001_02229bcc[1] & 0xff) | ((data_ov001_02229bcc[0] & 0x1ff) << 16);
    sWfcLinkIcon->oam->attr2 = (sWfcLinkIcon->oam->attr2 & ~0xc00) | 0x800;
    sWfcLinkIcon->task = WfcTask_Add(0, (void *)WfcLinkIcon_Task, 0, 0x78);
}

extern "C" void WfcLinkIcon_Delete() {
    if (sWfcLinkIcon == 0) return;
    WfcTask_Delete(0, sWfcLinkIcon->task);
    WfcOam_FreeEntry(sWfcLinkIcon->oam);
    WfcHeap_FreeAndClear(&sWfcLinkIcon);
}

extern "C" void WfcLinkIcon_Task() {
    volatile u16 *ime = (volatile u16 *)0x4000208;
    u16 saved = IO_R(ime);
    u32 x = 0;
    IO_W(ime, 0);
    if (WM_GetAllowedChannel() != 0x8000) x = WM_GetLinkLevel();
    IO_R(ime);
    IO_W(ime, saved);
    const u8 *q = data_ov001_02229bd0[sWfcLinkIcon->iconSet];
    WfcCell_Copy(0, q[x], sWfcLinkIcon->oam);
    const u16 *p = data_ov001_02229bcc;
    GXOamAttr *r = sWfcLinkIcon->oam;
    r->attr01 = (r->attr01 & 0xfe00ff00) | (p[1] & 0xff) | ((p[0] & 0x1ff) << 16);
    r = sWfcLinkIcon->oam;
    r->attr2 = (r->attr2 & ~0xc00) | 0x800;
}

#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02208a24) {
    HOST_OVERLAY_VAR(sWfcLinkIcon),
    HOST_OVERLAY_VARS_END
};
