#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220cbd0.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_022140bc.h"
#include "proto/ov001/unk_ov001_02214f50.h"
#include "proto/ov001/unk_ov001_022156e0.h"
#include "proto/ov001/unk_ov001_02219c3c.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_02225f40.h"

#pragma thumb off

#define REGSET(a) do { u32 t = IO_R((volatile u16 *)(a)); t &= ~3; t |= 3; IO_W((volatile u16 *)(a), t); } while (0)

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {

void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
s32 swprintf(wchar_t *s, u32 n, const wchar_t *fmt, ...);
void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);


const u16 sWfcErrorTextRect[4] = {0x0d, 0x3c, 0xe6, 0x5e};
const u8 sWfcErrorCodeFont[8] = {0, 1, 1, 1, 1, 1, 0, 0};
const u16 sWfcErrorCodePos[6][2] = {{0x62, 0x22}, {0x62, 0x22}, {0x3d, 0x22}, {0x65, 0x22}, {0x6c, 0x22}, {0x34, 0x22}};
wchar_t sWfcErrorCodeFormat[4] = {0x25, 0x64, 0, 0};
s32 sWfcErrorCode;

void WfcError_Enter() {
    WfcError_LoadBg();
    WfcError_DrawMessage();
    WfcUtil_SetScene(WfcError_FadeIn);
}

void WfcError_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jb4Error.nsc.l", (WfcLoadFunc)GX_LoadBG2Scr);
    REGSET(0x4001008);
    REGSET(0x400100a);
    REGSET(0x4000008);
    REGSET(0x400000a);
    REGSET(0x400000c);
}

void WfcError_DrawMessage() {
    u32 sel;
    s32 r4;
    wchar_t buf[8];
    WfcUtil_GetEditParams(0, &sel);
    s32 v = sWfcErrorCode;
    if (v >= -20099) r4 = 0;
    else if (v >= -20100) r4 = 21;
    else if (v >= -20101) r4 = 74;
    else if (v >= -20107) r4 = 21;
    else if (v >= -20108) r4 = 73;
    else if (v >= -20109) r4 = 21;
    else if (v >= -20110) r4 = 24;
    else if (v >= -20999) r4 = 21;
    else if (v >= -22999) r4 = 0;
    else if (v >= -23999) r4 = 74;
    else if (v >= -49999) r4 = 0;
    else if (v >= -50002) r4 = 53;
    else if (v >= -50003) r4 = 38;
    else if (v >= -50098) r4 = 0;
    else if (v >= -50099) { r4 = (sel == 2) ? 0x26 : 0x35; }
    else if (v >= -51098) r4 = 0;
    else if (v >= -51099) { r4 = (sel == 2) ? 0x26 : 0x36; }
    else if (v >= -51102) r4 = 55;
    else if (v >= -51103) r4 = 38;
    else if (v >= -51199) r4 = 0;
    else if (v >= -51299) r4 = 76;
    else if (v >= -51302) r4 = 77;
    else if (v >= -51303) r4 = 37;
    else if (v >= -51999) r4 = 0;
    else if (v >= -52002) r4 = 56;
    else if (v >= -52003) r4 = 78;
    else if (v >= -52099) r4 = 0;
    else if (v >= -52103) r4 = 59;
    else if (v >= -52199) r4 = 0;
    else if (v >= -52203) r4 = 59;
    else if (v >= -52299) r4 = 0;
    else if (v >= -52399) r4 = 21;
    else if (v >= -52999) r4 = 0;
    else if (v >= -53299) r4 = 0x15;
    else r4 = 0;
    WfcTextCanvas *canvas = WfcText_CreateBgCanvas(0, sWfcErrorCodeFont[WfcUtil_GetLanguage()]);
    const u16 *text = (const u16 *)WfcMsg_GetString((WfcMsgBank *)gWfcMsgBank, r4);
    swprintf(buf, 8, sWfcErrorCodeFormat, -sWfcErrorCode);
    u32 a = sWfcErrorCodePos[WfcUtil_GetLanguage()][1];
    u32 b = sWfcErrorCodePos[WfcUtil_GetLanguage()][0];
    WfcText_DrawMonospace(canvas, b, a, 2, 10, (u16 *)buf, 0);
    WfcText_DrawTextRect(canvas, sWfcErrorTextRect[0], sWfcErrorTextRect[1], sWfcErrorTextRect[2], sWfcErrorTextRect[3], 2, WfcUtil_GetTextFlags(), text);
    WfcText_RequestTransfer(canvas);
}

void WfcError_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcError_WaitFadeIn);
}

void WfcError_WaitFadeIn() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcUtil_OpenButtonBar(4);
    WfcUtil_SetScene(WfcError_WaitButtonBar);
}

void WfcError_WaitButtonBar() {
    if (WfcButtonBar_GetResult() == -2) return;
    WfcButtonBar_EnableInput();
    WfcUtil_SetScene(WfcError_Update);
}

void WfcError_Update() {
    WfcError_HandleInput();
    WfcError_Idle();
    WfcError_HandleResult();
}

void WfcError_HandleInput() {
    if (WfcInput_IsKeyPressed(1) == 0) return;
    WfcButtonBar_SetResult(0);
}

void WfcError_Idle() {}

void WfcError_HandleResult() {
    if (WfcButtonBar_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcUtil_SetScene(WfcError_StartExit);
}

void WfcError_StartExit() {
    WfcButtonBar_DisableInput();
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcError_FadeOut);
}

void WfcError_FadeOut() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcButtonBar_Close();
    WfcFade_Start(3, 1, 1, 8);
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcError_Exit);
}

void WfcError_Exit() {
    u32 sel;
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    if (WfcButtonBar_IsClosed() == 0) return;
    WfcText_DestroyBgCanvas(0);
    WfcUtil_HideTopMessage();
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_GetEditParams(0, &sel);
    if (sel != 0) {
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetScene(WfcConnSelect_Enter);
    } else {
        WfcUtil_SetScreenFlags(2, 0);
        WfcUtil_SetEditParams(0, 0);
        WfcManualSetup_SetMode(0);
        WfcUtil_SetScene(WfcManualSetup_Enter);
    }
}

void WfcError_SetCode(s32 a) {
    sWfcErrorCode = a;
}
}
#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02214f50) {
    HOST_OVERLAY_VAR(sWfcErrorCodeFormat),
    HOST_OVERLAY_VAR(sWfcErrorCode),
    HOST_OVERLAY_VARS_END
};
