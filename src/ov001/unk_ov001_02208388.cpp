#include "types.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220cbd0.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0221eb38.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_0222516c.h"

typedef void (*WfcLoadFunc)(void *, s32, u32);

extern "C" {

extern void DC_FlushRange(void *, u32);
extern void *strncpy(void *, void *, u32);


void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn);
}

extern "C" const u8 data_ov001_02229b7c[8] = {0x6a, 0x65, 0x66, 0x67, 0x69, 0x73, 0, 0};
extern "C" const u16 data_ov001_02229b84[4] = {0x0d, 0x28, 0xe6, 0x70};
extern "C" const u16 data_ov001_02229b8c[4] = {0x0d, 0x3c, 0xe6, 0x5e};
extern "C" const u32 data_ov001_02229b94[6] = {0x480, 0x280, 0x280, 0x280, 0x280, 0x280};
extern "C" const u16 data_ov001_02229bac[12] = {0x6b, 0x22, 0x6c, 0x22, 0x7c, 0x22, 0x5d, 0x22, 0x5f, 0x22, 0x7d, 0x22};
extern "C" {
u8 sWfcPathBuf[0x40];
}

#pragma thumb off

extern "C" u8 *WfcUtil_LocalizePath(u8 *p) {
    strncpy(sWfcPathBuf, p, 0x3f);
    if (p[5] == 0x78) return sWfcPathBuf;
    u32 r = WfcUtil_GetLanguage();
    if (p[5] == 0x79) {
        if (r != 0) return sWfcPathBuf;
    }
    sWfcPathBuf[5] = data_ov001_02229b7c[r];
    return sWfcPathBuf;
}

extern "C" void WfcUtil_LoadFileTo(void *a, WfcLoadFunc fn) {
    u32 sz;
    void *h = WfcFs_LoadFile(WfcUtil_LocalizePath((u8 *)a), &sz, 4);
    DC_FlushRange(h, sz);
    fn(h, 0, sz);
    WfcFs_FreeFile(h);
}

extern "C" void WfcUtil_ShowStepIndicator(s32 a) {
    u32 out;
    WfcUtil_GetScreenFlags(&out, 0);
    if (out == 1) WfcHeader_Create(a);
    else if (out == 2) WfcHeader_SetStep(a);
}

extern "C" void WfcUtil_OpenButtonBar(s32 a) {
    u32 out;
    WfcUtil_GetScreenFlags(0, &out);
    if (out == 1) WfcButtonBar_Create(a);
}

extern "C" void WfcUtil_ShowBottomMessage(s32 a) {
    WfcTextCanvas *r5 = WfcText_CreateBgCanvas(0, 0);
    const u16 *r4 = (const u16 *)WfcMsg_GetString(gWfcMsgBank, a);
    u32 t = WfcUtil_GetTextFlags();
    const u16 *s = data_ov001_02229b84;
    WfcText_DrawTextRect(r5, s[0], s[1], s[2], s[3], 2, t, r4);
    WfcText_RequestTransfer(r5);
}

extern "C" void WfcUtil_ShowBottomMessageNum(const u16 *name, s32 b) {
    WfcTextCanvas *r4 = WfcText_CreateBgCanvas(0, 0);
    const u16 *r6 = (const u16 *)WfcMsg_GetString(gWfcMsgBank, b);
    u32 t = WfcUtil_GetTextFlags();
    const u16 *s = data_ov001_02229b8c;
    WfcText_DrawTextRect(r4, s[0], s[1], s[2], s[3], 2, t, r6);
    u32 i = WfcUtil_GetLanguage();
    u32 j = WfcUtil_GetLanguage();
    WfcText_DrawText(r4, data_ov001_02229bac[i * 2], data_ov001_02229bac[j * 2 + 1], 2, 0x209, name);
    WfcText_RequestTransfer(r4);
}

extern "C" u32 WfcUtil_GetTextFlags() {
    return data_ov001_02229b94[WfcUtil_GetLanguage()];
}

#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02208388) {
    HOST_OVERLAY_VAR(sWfcPathBuf),
    HOST_OVERLAY_VARS_END
};
