#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220cbd0.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0222516c.h"

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" u8 sWfcTopMessageShown = 0;
extern "C" const u16 data_ov001_02229b74[4] = {0x14, 0, 0xd8, 0x40};

extern "C" {
extern void GXS_LoadBG0Scr(void *, s32, u32);
void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
}

#pragma thumb off

extern "C" void WfcUtil_ResetTopMessage() {
    sWfcTopMessageShown = 0;
}

extern "C" s32 WfcUtil_ShowTopMessage(s32 a, s32 b, s32 c) {
    WfcTextCanvas *canvas;
    u16 *text;
    if (sWfcTopMessageShown != 0) return 0;
    WfcUtil_LoadFileTo((void *)"char/jtNull.nsc.l", GXS_LoadBG0Scr);
    IO_W((volatile u32 *)0x4001010, 0x1920000);
    canvas = WfcText_CreateBgCanvas(1, 0);
    text = WfcMsg_GetStringWithDigit(gWfcMsgBank, a, b, c);
    u32 t = WfcUtil_GetTextFlags();
    const u16 *s = data_ov001_02229b74;
    WfcText_DrawTextRect(canvas, s[0], s[1], s[2], s[3], 2, t, text);
    WfcText_RequestTransfer(canvas);
    sWfcTopMessageShown = 1;
    return 1;
}

extern "C" s32 WfcUtil_HideTopMessage() {
    if (sWfcTopMessageShown == 0) return 0;
    WfcText_DestroyBgCanvas(1);
    sWfcTopMessageShown = 0;
    return 1;
}

#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02208244) {
    HOST_OVERLAY_VAR(sWfcTopMessageShown),
    HOST_OVERLAY_VARS_END
};
