#include "types.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02218054.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_02225924.h"

#pragma thumb off

#define BGCNT(a, v) (*(volatile u16 *)(a) = (*(volatile u16 *)(a) & ~3) | (v))

extern "C" {
void GX_LoadBG2Char();
s32 GX_LoadBG2Scr(void *, s32, u32);
void GX_LoadBGPltt();
void WfcUtil_LoadFileTo(void *, void *);
void WfcConfig_CommitEdit();
}

extern "C" void WfcSaveSettings_Enter() {
    WfcSaveSettings_LoadBg();
    WfcHighlight_SetConnection();
    WfcConfig_CommitEdit();
    WfcUtil_SetScene(WfcSaveSettings_FadeIn);
}

extern "C" void WfcSaveSettings_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jbBgStep3.ncg.l", (void *)GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep3.ncl.l", (void *)GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/xb4None.nsc.l", (void *)GX_LoadBG2Scr);
    BGCNT(0x4001008, 3);
    BGCNT(0x400100a, 3);
    BGCNT(0x400000a, 3);
    BGCNT(0x400000c, 3);
}

extern "C" void WfcSaveSettings_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x14, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x14);
    WfcUtil_SetScene(WfcSaveSettings_ShowDialog);
}

extern "C" void WfcSaveSettings_ShowDialog() {
    if (WfcFade_IsBusy(1)) return;
    if (WfcFade_IsBusy(0)) return;
    WfcDialog_Open(0x96, 5, 1, -1, 0);
    WfcUtil_SetScene(WfcSaveSettings_WaitDialog);
}

extern "C" void WfcSaveSettings_WaitDialog() {
    func_ov001_02218118();
    func_ov001_02218114();
    if (WfcDialog_IsOpen()) return;
    WfcUtil_SetScene(WfcSaveSettings_FadeOut);
}

extern "C" void func_ov001_02218118() {}

extern "C" void func_ov001_02218114() {}

extern "C" void WfcSaveSettings_FadeOut() {
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x14, 8);
    WfcUtil_SetScene(WfcSaveSettings_Exit);
}

extern "C" void WfcSaveSettings_Exit() {
    if (WfcFade_IsBusy(1)) return;
    if (WfcFade_IsBusy(0)) return;
    WfcUtil_HideTopMessage();
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x14);
    WfcUtil_SetScreenFlags(2, 1);
    WfcUtil_SetScene(WfcConnSelect_Enter);
}
