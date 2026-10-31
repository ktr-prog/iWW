#include "types.h"
#include "nitro/io_access.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_02203b1c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220864c.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220cbd0.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0220d760.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02226f68.h"
#include "proto/ov001/unk_ov001_02225924.h"

struct WfcSimpleStartResultBuf {
    u8 unk_00[0x20];
    s32 securityType;
    s32 unk_24;
    u8 unk_28[0xec - 0x28];
};

extern "C" {
char data_ov001_0222ab10[16] = "msg/ita.bmg.l";
char data_ov001_0222aae0[16] = "msg/ger.bmg.l";
char data_ov001_0222aaf0[16] = "msg/fre.bmg.l";
char data_ov001_0222aac0[16] = "msg/spa.bmg.l";
char data_ov001_0222aad0[16] = "msg/jap.bmg.l";
char data_ov001_0222ab00[16] = "msg/eng.bmg.l";
void *sWfcMsgFileNames[6] = {data_ov001_0222aad0, data_ov001_0222ab00, data_ov001_0222aaf0, data_ov001_0222aae0, data_ov001_0222ab10, data_ov001_0222aac0};
WfcMsgBank *gWfcMsgBank;
SimpleStartStatus *sWfcSimpleStartStatus;

extern void OS_Sleep(s32);
extern void GXS_LoadBG1Char();
extern void GXS_LoadBGPltt();
extern void GXS_LoadOBJ();
extern void GXS_LoadOBJPltt();
extern void GX_LoadBG2Char();
extern void GX_LoadBGPltt();
extern void GX_LoadOBJ();
extern void GX_LoadOBJPltt();
extern void GXS_LoadBG1Scr();

extern void WfcConfig_StoreSimpleStart(void *);
extern void WfcMsg_Unload(WfcMsgBank *e);
extern WfcMsgBank *WfcMsg_Load(void *a);
extern void WfcConfig_Shutdown();
extern void WfcConfig_Init();
extern void WfcUtil_LoadFileTo(void *, void *);
extern void WfcCell_Unload(s32);
extern void WfcCell_Load(s32, void *);
#pragma thumb off
void WfcSimpleStart_StatusCallback(SimpleStartStatus *);

void WfcBoot_Enter() {
    WfcConfig_Init();
    WfcMsg_InitPool();
    WfcCursor_Init();
    WfcHighlight_Init();
    WfcUtil_ResetTopMessage();
    if (WfcUtil_GetLanguage() == 1 && WfcUtil_TestOptionFlag(2) != 0) {
        gWfcMsgBank = WfcMsg_Load((void *)"msg/usa.bmg.l");
    } else {
        gWfcMsgBank = WfcMsg_Load(sWfcMsgFileNames[WfcUtil_GetLanguage()]);
    }
    WfcCell_Load(1, WfcUtil_LocalizePath((u8 *)"char/jtMain.nce.l"));
    WfcCell_Load(0, WfcUtil_LocalizePath((u8 *)"char/jbMain.nce.l"));
    WfcUtil_LoadFileTo((void *)"char/jtBgMain.ncg.l", (void *)GXS_LoadBG1Char);
    WfcUtil_LoadFileTo((void *)"char/jtBgMain.ncl.l", (void *)GXS_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/jtObjMain.ncg.l", (void *)GXS_LoadOBJ);
    WfcUtil_LoadFileTo((void *)"char/xtObjMain.ncl.l", (void *)GXS_LoadOBJPltt);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep1.ncg.l", (void *)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep1.ncl.l", (void *)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/jbObjMain.ncg.l", (void *)GX_LoadOBJ);
    WfcUtil_LoadFileTo((void *)"char/ybObjMain.ncl.l", (void *)GX_LoadOBJPltt);
    switch (WfcUtil_GetStartMode()) {
    case 0:
        WfcUtil_LoadFileTo((void *)"char/jtTop.nsc.l", (void *)GXS_LoadBG1Scr);
        break;
    case 1:
        WfcUtil_LoadFileTo((void *)"char/jtStep1.nsc.l", (void *)GXS_LoadBG1Scr);
        break;
    }
    volatile u16 *r1 = (volatile u16 *)0x400100a;
    volatile u16 *r2 = (volatile u16 *)0x400000a;
    IO_W(r1, (IO_R(r1) & ~3) | 3);
    IO_W(r2, (IO_R(r2) & ~3) | 3);
    IO_W(r2, (IO_R(r2) & ~3) | 3);
    WfcGx_ShowPlanes(1, 2);
    WfcGx_ShowPlanes(0, 2);
    WfcUtil_SetScene(WfcBoot_FadeIn);
}

void WfcBoot_FadeIn() {
    WfcFade_Start(2, 1, 2, 0x14);
    WfcFade_Start(2, 0, 2, 0x14);
    WfcUtil_SetScene(WfcBoot_Dispatch);
}

void WfcBoot_Dispatch() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    switch (WfcUtil_GetStartMode()) {
    case 0:
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetScene(WfcTopMenu_Enter);
        break;
    case 1:
        WfcUtil_SetScreenFlags(1, 1);
        WfcUtil_SetScene(WfcConnSelect_Enter);
        break;
    }
}

void WfcUtil_QuitFadeOut() {
    WfcFade_Start(3, 1, 0x3f, 0x14);
    WfcFade_Start(3, 0, 0x3f, 0x14);
    WfcUtil_SetScene(WfcUtil_Quit);
}

void WfcUtil_Quit() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcTask_SetListActive(0, 0);
    WfcTask_SetListActive(1, 0);
    WfcCell_Unload(1);
    WfcCell_Unload(0);
    WfcHighlight_Free();
    WfcCursor_Free();
    WfcMsg_Unload(gWfcMsgBank);
    WfcMsg_FreePool();
    WfcConfig_Shutdown();
    WfcUtil_RequestExit();
}

void WfcSimpleStart_Begin() {
    sWfcSimpleStartStatus = (SimpleStartStatus *)WfcHeap_AllocClear(sizeof(SimpleStartStatus), -4);
    if (SimpleStart_Start(0xf, 0x40, WfcSimpleStart_StatusCallback, WfcSimpleStart_Alloc, WfcSimpleStart_Free, 0x800) != 1) Fatal_Trap();
    OS_Sleep(10);
}

void WfcSimpleStart_End() {
    if (SimpleStart_Stop() != 1) Fatal_Trap();
    WfcHeap_FreeAndClear((void **)&sWfcSimpleStartStatus);
}

s32 WfcSimpleStart_GetState() {
    WfcSimpleStartResultBuf buf;
    s32 r;
    switch (sWfcSimpleStartStatus->state) {
    case 0:
    case 1:
    case 3:
    case 5:
        return 0;
    case 2:
        return 1;
    case 4:
        return 2;
    case 6:
        if (SimpleStart_GetResult(&buf) != 1) Fatal_Trap();
        if (buf.securityType >= 0 && buf.securityType <= 3) {
            if (buf.unk_24 == 1) return 3;
        }
        return 5;
    case 7:
        r = 4;
        break;
    }
    return r;
}

void WfcSimpleStart_ApplyResult() {
    u8 buf[0xec];
    if (SimpleStart_GetResult(buf) != 1) Fatal_Trap();
    WfcConfig_StoreSimpleStart(buf);
}

void WfcSimpleStart_StatusCallback(SimpleStartStatus *p) {
    *sWfcSimpleStartStatus = *p;
}

void *WfcSimpleStart_Alloc(u32 a) {
    return WfcHeap_Alloc(a, 0x20);
}

void WfcSimpleStart_Free(void *p) {
    WfcHeap_Free(p);
}
}
#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220d1d8) {
    HOST_OVERLAY_VAR(data_ov001_0222ab10),
    HOST_OVERLAY_VAR(data_ov001_0222aae0),
    HOST_OVERLAY_VAR(data_ov001_0222aaf0),
    HOST_OVERLAY_VAR(data_ov001_0222aac0),
    HOST_OVERLAY_VAR(data_ov001_0222aad0),
    HOST_OVERLAY_VAR(data_ov001_0222ab00),
    HOST_OVERLAY_VAR(sWfcMsgFileNames),
    HOST_OVERLAY_VAR(gWfcMsgBank),
    HOST_OVERLAY_VAR(sWfcSimpleStartStatus),
    HOST_OVERLAY_VARS_END
};
