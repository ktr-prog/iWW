#include "types.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02226f68.h"

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {
extern void GX_LoadBG1Scr(void *, s32, u32);
extern void GX_LoadBG1Char(void *, s32, u32);
extern void DC_FlushRange(void *, u32);
extern void MIi_CpuCopyFast(void *, void *, u32);
extern void WfcHeap_FreeAndClear(void *);
extern void *WfcHeap_Alloc(s32, s32);
extern u8 *WfcConfig_GetEdit();
extern void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
}

#pragma thumb off

extern "C" void WfcHighlight_Init() {
    sWfcHighlightScreen = (u8 *)WfcHeap_Alloc(0xc0, 4);
    WfcUtil_LoadFileTo((void *)"char/jbBgHl.ncg.l", GX_LoadBG1Char);
    switch (WfcUtil_GetStartMode()) {
    case 0:
        WfcUtil_LoadFileTo(sWfcHighlightScreens[0], GX_LoadBG1Scr);
        break;
    case 1:
        WfcUtil_LoadFileTo(sWfcHighlightScreens[1], GX_LoadBG1Scr);
        break;
    }
}

extern "C" void WfcHighlight_Free() {
    WfcHeap_FreeAndClear(&sWfcHighlightScreen);
}

extern "C" void WfcHighlight_Set(s32 n) {
    void *h = WfcFs_LoadFile(WfcUtil_LocalizePath((u8 *)sWfcHighlightScreens[n]), 0, 4);
    MIi_CpuCopyFast(h, sWfcHighlightScreen, 0xc0);
    WfcFs_FreeFile(h);
    WfcTask_Add(1, (void *)WfcHighlight_TransferTask, 0, 0x78);
}

extern "C" void WfcHighlight_SetConnection() {
    WfcHighlight_Set(WfcConfig_GetEdit()[0xf4] + 5);
}

extern "C" void WfcHighlight_SetListEntry() {
    WfcHighlight_Set(WfcConfig_GetEdit()[0xf4] + 2);
}
extern "C" char data_ov001_0222a638[];
extern "C" void *sWfcHighlightScreens[20];
extern "C" char data_ov001_0222a6a8[];
extern "C" char data_ov001_0222a768[];
extern "C" char data_ov001_0222a6c0[];
extern "C" char data_ov001_0222a738[];
extern "C" char data_ov001_0222a798[];
extern "C" char data_ov001_0222a720[];
extern "C" char data_ov001_0222a708[];
extern "C" char data_ov001_0222a64c[];
extern "C" char data_ov001_0222a678[];
extern "C" char data_ov001_0222a750[];
extern "C" char data_ov001_0222a780[];
extern "C" char data_ov001_0222a610[];
extern "C" char data_ov001_0222a660[];
extern "C" char data_ov001_0222a7c8[];
extern "C" char data_ov001_0222a6f0[];
extern "C" char data_ov001_0222a6d8[];
extern "C" char data_ov001_0222a690[];
extern "C" char data_ov001_0222a624[];
extern "C" char data_ov001_0222a7b0[];

extern "C" void WfcHighlight_TransferTask(void *task) {
    DC_FlushRange(sWfcHighlightScreen, 0xc0);
    GX_LoadBG1Scr(sWfcHighlightScreen, 0, 0xc0);
    WfcTask_RequestDelete(1, task);
}

#pragma thumb reset

extern "C" char data_ov001_0222a638[];
extern "C" void *sWfcHighlightScreens[20];
extern "C" char data_ov001_0222a6a8[];
extern "C" char data_ov001_0222a768[];
extern "C" char data_ov001_0222a6c0[];
extern "C" char data_ov001_0222a738[];
extern "C" char data_ov001_0222a798[];
extern "C" char data_ov001_0222a720[];
extern "C" char data_ov001_0222a708[];
extern "C" char data_ov001_0222a64c[];
extern "C" char data_ov001_0222a678[];
extern "C" u8 *sWfcHighlightScreen;
extern "C" char data_ov001_0222a750[];
extern "C" char data_ov001_0222a780[];
extern "C" char data_ov001_0222a610[];
extern "C" char data_ov001_0222a660[];
extern "C" char data_ov001_0222a7c8[];
extern "C" char data_ov001_0222a6f0[];
extern "C" char data_ov001_0222a6d8[];
extern "C" char data_ov001_0222a690[];
extern "C" char data_ov001_0222a624[];
extern "C" char data_ov001_0222a7b0[];

extern "C" char data_ov001_0222a638[] = "char/jb4HlWep.nsc.l";

extern "C" void *sWfcHighlightScreens[20] = {
    data_ov001_0222a6a8,
    data_ov001_0222a610,
    data_ov001_0222a750,
    data_ov001_0222a768,
    data_ov001_0222a780,
    data_ov001_0222a738,
    data_ov001_0222a6f0,
    data_ov001_0222a720,
    data_ov001_0222a64c,
    data_ov001_0222a678,
    data_ov001_0222a638,
    data_ov001_0222a624,
    data_ov001_0222a6d8,
    data_ov001_0222a7c8,
    data_ov001_0222a708,
    data_ov001_0222a660,
    data_ov001_0222a7b0,
    data_ov001_0222a6c0,
    data_ov001_0222a798,
    data_ov001_0222a690,
};

extern "C" char data_ov001_0222a6a8[] = "char/jb2HlWiFi.nsc.l";

extern "C" char data_ov001_0222a768[] = "char/jb3HlList2.nsc.l";

extern "C" char data_ov001_0222a6c0[] = "char/jb5HlInfo.nsc.l";

extern "C" char data_ov001_0222a738[] = "char/jb4HlSet1.nsc.l";

extern "C" char data_ov001_0222a798[] = "char/jb5HlErase.nsc.l";

extern "C" char data_ov001_0222a720[] = "char/jb4HlSet3.nsc.l";

extern "C" char data_ov001_0222a708[] = "char/jb4HlDns0.nsc.l";

extern "C" char data_ov001_0222a64c[] = "char/jb4HlUsb.nsc.l";

extern "C" char data_ov001_0222a678[] = "char/jb4HlSsid.nsc.l";

extern "C" u8 *sWfcHighlightScreen = 0;

extern "C" char data_ov001_0222a750[] = "char/jb3HlList1.nsc.l";

extern "C" char data_ov001_0222a780[] = "char/jb3HlList3.nsc.l";

extern "C" char data_ov001_0222a610[] = "char/jb2HlAp.nsc.l";

extern "C" char data_ov001_0222a660[] = "char/jb4HlDns1.nsc.l";

extern "C" char data_ov001_0222a7c8[] = "char/jb4HlGateway.nsc.l";

extern "C" char data_ov001_0222a6f0[] = "char/jb4HlSet2.nsc.l";

extern "C" char data_ov001_0222a6d8[] = "char/jb4HlMask.nsc.l";

extern "C" char data_ov001_0222a690[] = "char/jb5HlMove.nsc.l";

extern "C" char data_ov001_0222a624[] = "char/jb4HlIp.nsc.l";

extern "C" char data_ov001_0222a7b0[] = "char/jb5HlOption.nsc.l";

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02208890) {
    HOST_OVERLAY_VAR(data_ov001_0222a638),
    HOST_OVERLAY_VAR(sWfcHighlightScreens),
    HOST_OVERLAY_VAR(data_ov001_0222a6a8),
    HOST_OVERLAY_VAR(data_ov001_0222a768),
    HOST_OVERLAY_VAR(data_ov001_0222a6c0),
    HOST_OVERLAY_VAR(data_ov001_0222a738),
    HOST_OVERLAY_VAR(data_ov001_0222a798),
    HOST_OVERLAY_VAR(data_ov001_0222a720),
    HOST_OVERLAY_VAR(data_ov001_0222a708),
    HOST_OVERLAY_VAR(data_ov001_0222a64c),
    HOST_OVERLAY_VAR(data_ov001_0222a678),
    HOST_OVERLAY_VAR(sWfcHighlightScreen),
    HOST_OVERLAY_VAR(data_ov001_0222a750),
    HOST_OVERLAY_VAR(data_ov001_0222a780),
    HOST_OVERLAY_VAR(data_ov001_0222a610),
    HOST_OVERLAY_VAR(data_ov001_0222a660),
    HOST_OVERLAY_VAR(data_ov001_0222a7c8),
    HOST_OVERLAY_VAR(data_ov001_0222a6f0),
    HOST_OVERLAY_VAR(data_ov001_0222a6d8),
    HOST_OVERLAY_VAR(data_ov001_0222a690),
    HOST_OVERLAY_VAR(data_ov001_0222a624),
    HOST_OVERLAY_VAR(data_ov001_0222a7b0),
    HOST_OVERLAY_VARS_END
};
