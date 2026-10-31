#include "types.h"
#include "nitro/io_access.h"
#include "proto/ov001/unk_ov001_02207904.h"
#include "proto/ov001/unk_ov001_02207b3c.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220cd24.h"
#include "proto/ov001/unk_ov001_0220eb90.h"
#include "proto/ov001/unk_ov001_0220f3fc.h"
#include "proto/ov001/unk_ov001_02210390.h"
#include "proto/ov001/unk_ov001_022107f0.h"
#include "proto/ov001/unk_ov001_02210cc0.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"

extern "C" {
extern u8 GX_LoadBG2Scr[];
void MIi_CpuClear16(u32 a, void *b, u32 c);
void MIi_CpuCopy16(void *a, void *b, u32 c);
void WfcUtil_LoadFileTo(void *a, void *b);
void WfcTransfer_SetCallback(void (*f)(u32));
s32 WfcInput_IsKeyPressed(u32 a);

u8 sWfcTransferConfirmAccepted;
u8 sWfcTransferConfirmError;
extern const u16 data_ov001_02229ff8[4];
const u16 data_ov001_02229ff8[4] = {0x8, 0x35, 0xf8, 0x51};

#pragma thumb off


void WfcTransferConfirm_Enter() {
    u8 *p = (u8 *)WfcTransfer_GetChildUser();
    WfcTextCanvas *w = WfcText_CreateBgCanvas(0, 0);
    sWfcTransferConfirmAccepted = 0;
    sWfcTransferConfirmError = 0;
    WfcTransferConfirm_LoadBg();
    volatile u16 v = 0;
    u16 buf[11];
    MIi_CpuClear16(v, buf, 0x16);
    MIi_CpuCopy16(p + 2, buf, p[1] * 2);
    const u16 *h = data_ov001_02229ff8;
    WfcText_DrawTextRect(w, h[0], h[1], h[2] - h[0], h[3] - h[1], 2, 0x480, buf);
    WfcText_RequestTransfer(w);
    WfcTransfer_SetCallback(WfcTransferConfirm_OnTransferError);
    WfcUtil_SetScene(WfcTransferConfirm_FadeIn);
}

void WfcTransferConfirm_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/jb5Move.nsc.l", (void *)GX_LoadBG2Scr);
    volatile u16 *r1 = (volatile u16 *)0x4001008;
    volatile u16 *r2 = (volatile u16 *)0x400100a;
    volatile u16 *r3 = (volatile u16 *)0x4000008;
    volatile u16 *r4 = (volatile u16 *)0x400000a;
    volatile u16 *r5 = (volatile u16 *)0x400000c;
    IO_W(r1, (IO_R(r1) & ~3) | 3);
    IO_W(r2, (IO_R(r2) & ~3) | 3);
    IO_W(r3, (IO_R(r3) & ~3) | 3);
    IO_W(r4, (IO_R(r4) & ~3) | 3);
    IO_W(r5, (IO_R(r5) & ~3) | 3);
}

void WfcTransferConfirm_FadeIn() {
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTransferConfirm_OpenDialog);
}

void WfcTransferConfirm_OpenDialog() {
    if (WfcFade_IsBusy(0)) return;
    WfcDialog_Open(0x5f, 4, 0, -1, 0);
    WfcUtil_SetScene(WfcTransferConfirm_WaitDialogOpen);
}

void WfcTransferConfirm_WaitDialogOpen() {
    if (WfcDialog_GetResult() == -2) return;
    WfcUtil_SetScene(WfcTransferConfirm_HandleResult);
}

void WfcTransferConfirm_HandleResult() {
    WfcTransferConfirm_Nop1();
    WfcTransferConfirm_Nop2();
    switch (WfcDialog_GetResult()) {
    case 0:
        sWfcTransferConfirmAccepted = 0;
        WfcSound_Play(7);
        break;
    case 1:
        sWfcTransferConfirmAccepted = 1;
        WfcSound_Play(0xe);
        break;
    default:
        return;
    }
    WfcTransfer_SetCallback(0);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcTransferConfirm_WaitDialogClosed);
}

void WfcTransferConfirm_Nop1() {
}

void WfcTransferConfirm_Nop2() {
}

void WfcTransferConfirm_WaitDialogClosed() {
    if (WfcDialog_IsOpen()) return;
    if (sWfcTransferConfirmAccepted == 0) {
        WfcFade_Start(3, 1, 1, 8);
    }
    WfcFade_Start(3, 0, 0x15, 8);
    WfcUtil_SetScene(WfcTransferConfirm_StartSendOrEnd);
}

void WfcTransferConfirm_StartSendOrEnd() {
    if (WfcFade_IsBusy(1)) return;
    if (WfcFade_IsBusy(0)) return;
    if (sWfcTransferConfirmError == 0 && sWfcTransferConfirmAccepted == 1) {
        WfcTransfer_StartSend();
    } else {
        WfcTransfer_RequestEnd();
    }
    WfcUtil_SetScene(WfcTransferConfirm_Exit);
}

void WfcTransferConfirm_Exit() {
    if (sWfcTransferConfirmError != 0 || sWfcTransferConfirmAccepted == 0) {
        if (WfcTransfer_IsFinished() == 0) return;
    }
    WfcText_DestroyBgCanvas(0);
    WfcGx_HidePlanes(0, 0x15);
    if (sWfcTransferConfirmAccepted == 0) {
        WfcUtil_HideTopMessage();
        WfcGx_HidePlanes(1, 1);
    }
    WfcUtil_SetScreenFlags(0, 1);
    if (sWfcTransferConfirmError != 0) {
        WfcUtil_SetScene(WfcTransferFailed_Enter);
    } else if (sWfcTransferConfirmAccepted == 0) {
        WfcGx_HidePlanes(1, 1);
        WfcUtil_SetScene(WfcOptions_Enter);
    } else {
        WfcUtil_SetScene(WfcTransferSend_Enter);
    }
}

void WfcTransferConfirm_OnTransferError(u32 event) {
    sWfcTransferConfirmError = 1;
}
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_022107f0) {
    HOST_OVERLAY_VAR(sWfcTransferConfirmAccepted),
    HOST_OVERLAY_VAR(sWfcTransferConfirmError),
    HOST_OVERLAY_VARS_END
};
