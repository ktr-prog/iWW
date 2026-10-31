#include "types.h"
#include "nitro/gxoam.h"
#include "ui/WfcTextEdit.h"
#include "nitro/io_access.h"
#include "net/WfcLoadFunc.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_02208c2c.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_02211b2c.h"
#include "proto/ov001/unk_ov001_02213424.h"
#include "proto/ov001/unk_ov001_022156e0.h"
#include "proto/ov001/unk_ov001_0221bc10.h"
#include "proto/ov001/unk_ov001_0221dcec.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226c24.h"

typedef void (*WfcTextEditStoreFunc)(u8 *text);

#pragma thumb off
extern "C" {

const u8 data_ov001_0222a058[4] = {0x20, 0x31, 0, 0};
const u16 data_ov001_0222a05c[2] = {0x0e, 0x10};
const u8 data_ov001_0222a060[0x10] = {0x08, 0x17, 0x26, 0x35, 0x44, 0x53, 0x62, 0x71, 0x80, 0x8f, 0x9e, 0xad, 0xbc, 0xcb, 0xda, 0xe9};
u8 sWfcTextEditTitleMsgs[4] = {0x90, 0x8f, 0, 0};
u32 sWfcTextEditConfirmMsgs[2] = {0x9b, 0x9c};
WfcTextEditStoreFunc sWfcTextEditStoreFuncs[2] = {WfcConfig_SetEditSsid, WfcConfig_SetEditWepKey};
WfcTextEdit *sWfcTextEdit;

void WfcTextEdit_Enter() {
    u8 b[2];
    u32 idx[2];
    b[0] = sWfcTextEditTitleMsgs[0];
    b[1] = sWfcTextEditTitleMsgs[1];
    sWfcTextEdit = (WfcTextEdit *)WfcHeap_AllocClear(sizeof(WfcTextEdit), 4);
    WfcUtil_GetEditParams(&idx[0], &idx[1]);
    if (idx[0] == 0) {
        WfcConfig_GetEditSsid(sWfcTextEdit->text);
        sWfcTextEdit->textLen = WfcUtil_StrNLen(sWfcTextEdit->text, 0x20);
    }
    WfcTextEdit_LoadBg();
    WfcHighlight_Set(idx[0] + 9);
    if (idx[1] == 1) {
        WfcUtil_ShowTopMessage(0x81, -1, 0);
    } else {
        WfcUtil_ShowTopMessage(b[idx[0]], -1, 0);
    }
    WfcUtil_ShowStepIndicator(2);
    sWfcTextEdit->textCanvas = WfcText_CreateBgCanvas(0, 0);
    sWfcTextEdit->caretOam = WfcObj_CreateSingle(0, 0x3e);
    sWfcTextEdit->caretOam->attr2 = (sWfcTextEdit->caretOam->attr2 & ~0xc00) | 0xc00;
    WfcTextEdit_UpdateCaret();
    WfcTextEdit_DrawText();
    WfcUtil_SetScene(WfcTextEdit_FadeIn);
}

void WfcTextEdit_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/ybObjKb.ncl.l", GX_LoadOBJPltt);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep3.ncg.l", GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep3.ncl.l", GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/xb4Edit.nsc.l", GX_LoadBG2Scr);
    IO_W((volatile u16 *)0x4001008, (IO_R((volatile u16 *)0x4001008) & ~3) | 3);
    IO_W((volatile u16 *)0x400100a, (IO_R((volatile u16 *)0x400100a) & ~3) | 3);
    IO_W((volatile u16 *)0x4000008, (IO_R((volatile u16 *)0x4000008) & ~3) | 2);
    IO_W((volatile u16 *)0x400000a, (IO_R((volatile u16 *)0x400000a) & ~3) | 3);
    IO_W((volatile u16 *)0x400000c, (IO_R((volatile u16 *)0x400000c) & ~3) | 3);
}

void WfcTextEdit_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcTextEdit_OpenKeyboard);
}

void WfcTextEdit_OpenKeyboard() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcTextKb_Create();
    WfcSound_Play(0x14);
    if (sWfcTextEdit->textLen == 0) WfcTextKb_SetDeleteEnabled(0);
    if (sWfcTextEdit->textLen == 0x20) WfcTextKb_SetInsertEnabled(0);
    WfcUtil_SetScene(WfcTextEdit_WaitKeyboard);
}

void WfcTextEdit_WaitKeyboard() {
    if (WfcTextKb_GetKey() == 0xff) return;
    WfcUtil_SetScene(WfcTextEdit_Update);
}

void WfcTextEdit_Update() {
    WfcTextEdit_HandleKey();
    WfcTextEdit_Idle();
}

void WfcTextEdit_HandleKey() {
    s32 r = WfcTextKb_GetKey();
    switch (r) {
    case 0x80:
        if (sWfcTextEdit->textLen != 0) {
            WfcSound_Play(3);
            sWfcTextEdit->textLen--;
            sWfcTextEdit->text[sWfcTextEdit->textLen] = 0;
            if (sWfcTextEdit->textLen == 0) WfcTextKb_SetDeleteEnabled(0);
            WfcTextKb_SetInsertEnabled(1);
        }
        break;
    case 0x82:
        WfcSound_Play(7);
        sWfcTextEdit->result = 0;
        WfcUtil_SetScene(WfcTextEdit_StartExit);
        return;
    case 0x83:
        if (WfcTextEdit_ValidateInput() != 0) {
            WfcSound_Play(6);
            sWfcTextEdit->result = 1;
        } else {
            sWfcTextEdit->result = 2;
            WfcSound_Play(9);
        }
        sWfcTextEdit->caretOam->attr01 = (sWfcTextEdit->caretOam->attr01 & 0xc1fffcff) | 0x200;
        WfcUtil_SetScene(WfcTextEdit_StartExit);
        return;
    case 0:
        break;
    case 0xe01d:
    default:
        if (sWfcTextEdit->textLen != 0x20) {
            WfcSound_Play(1);
            sWfcTextEdit->text[sWfcTextEdit->textLen] = r;
            sWfcTextEdit->textLen++;
            WfcTextKb_SetDeleteEnabled(1);
            if (sWfcTextEdit->textLen == 0x20) WfcTextKb_SetInsertEnabled(0);
        }
        break;
    }
    WfcTextEdit_DrawText();
    WfcTextEdit_UpdateCaret();
}

void WfcTextEdit_Idle() {}

void WfcTextEdit_StartExit() {
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcTextEdit_CloseKeyboard);
}

void WfcTextEdit_CloseKeyboard() {
    if (WfcFade_IsBusy(1) != 0) return;
    WfcTextKb_Close();
    WfcSound_Play(0x15);
    WfcUtil_SetScene(WfcTextEdit_WaitKeyboardClosed);
}

void WfcTextEdit_WaitKeyboardClosed() {
    u32 v[2];
    u32 idx;
    v[0] = sWfcTextEditConfirmMsgs[0];
    v[1] = sWfcTextEditConfirmMsgs[1];
    if (WfcTextKb_Exists() != 0) return;
    u32 t = sWfcTextEdit->result;
    if (t == 0) {
        WfcUtil_SetScene(WfcTextEdit_Exit);
    } else if (t == 2) {
        WfcDialog_Open(0x2f, 3, 1, -1, 0);
        WfcUtil_SetScene(WfcTextEdit_WaitErrorDialog);
    } else {
        WfcUtil_GetEditParams(0, &idx);
        WfcDialog_Open(v[idx], 2, 1, -1, 0);
        WfcUtil_SetScene(WfcTextEdit_WaitConfirmDialog);
    }
}

void WfcTextEdit_Exit() {
    u32 a, b;
    WfcUtil_HideTopMessage();
    WfcOam_FreeEntry(sWfcTextEdit->caretOam);
    WfcText_DestroyBgCanvas(0);
    WfcUtil_LoadFileTo((void *)"char/ybObjMain.ncl.l", GX_LoadOBJPltt);
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_GetEditParams(&a, &b);
    if (b == 0) {
        WfcUtil_SetScreenFlags(2, 1);
        WfcUtil_SetEditParams(0, a);
        WfcUtil_SetScene(WfcManualSetup_Enter);
    } else if (sWfcTextEdit->result == 0) {
        WfcUtil_SetScreenFlags(0, 1);
        WfcUtil_SetEditParams(1, 0);
        WfcUtil_SetScene(WfcApList_Enter);
    } else {
        WfcUtil_SetScreenFlags(0, 0);
        WfcUtil_SetEditParams(0, 1);
        WfcUtil_SetScene(WfcTestConfirm_Enter);
    }
    WfcHeap_FreeAndClear((void **)&sWfcTextEdit);
}

void WfcTextEdit_DrawText() {
    u16 v[4] = {0, 0, 0, 0};
    u16 w[2];
    s32 j, i;
    v[1] = data_ov001_0222a058[0];
    v[2] = data_ov001_0222a05c[0];
    v[3] = data_ov001_0222a05c[1];
    WfcText_Clear(sWfcTextEdit->textCanvas, 0);
    w[1] = 0;
    u8 hi = data_ov001_0222a058[1];
    i = 0; j = 0;
    for (; i < 0x20; i++, j++) {
        WfcTextEdit *g = sWfcTextEdit;
        if (i == 0x10) {
            j = 0;
            v[1] = hi;
        }
        u32 c = g->text[i];
        if (c == 0x20) w[0] = 0xe01d; else w[0] = c;
        u32 t = data_ov001_0222a060[j];
        v[0] = t;
        WfcText_DrawTextRect(g->textCanvas, v[0], v[1], v[2], v[3], 2, 0x480, w);
    }
    WfcText_RequestTransfer(sWfcTextEdit->textCanvas);
}

void WfcTextEdit_UpdateCaret() {
    WfcTextEdit *g = sWfcTextEdit;
    s32 n = g->textLen;
    s32 a = n & 0xf;
    s32 b = n >> 4;
    if ((u32)n >= 0x20) { a = 0xf; b = 1; }
    u32 x = data_ov001_0222a060[a];
    u32 y = data_ov001_0222a058[b];
    GXOamAttr *hw = g->caretOam;
    hw->attr01 = (hw->attr01 & 0xfe00ff00) | (y & 0xff) | ((x & 0x1ff) << 16);
}

void WfcTextEdit_WaitConfirmDialog() {
    sWfcTextEdit->result = WfcDialog_GetResult();
    switch (sWfcTextEdit->result) {
    case 0:
        WfcSound_Play(7);
        break;
    case 1:
        WfcSound_Play(0xe);
        break;
    default:
        return;
    }
    WfcDialog_Close();
    WfcUtil_SetScene(WfcTextEdit_ApplyAndExit);
}

void WfcTextEdit_ApplyAndExit() {
    u32 idx;
    if (WfcDialog_IsOpen() != 0) return;
    if (sWfcTextEdit->result == 0) {
        sWfcTextEdit->caretOam->attr01 &= 0xc1fffcff;
        WfcUtil_SetScene(WfcTextEdit_OpenKeyboard);
        return;
    }
    WfcUtil_GetEditParams(&idx, 0);
    sWfcTextEditStoreFuncs[idx](sWfcTextEdit->text);
    WfcUtil_SetScene(WfcTextEdit_Exit);
}

BOOL WfcTextEdit_ValidateInput() {
    u32 a, b;
    s32 r, i;
    u32 c;
    WfcUtil_GetEditParams(&a, &b);
    if (b == 1) {
        WfcUtil_ShowTopMessage(0x81, -1, 0);
    }
    WfcUtil_GetEditParams(&a, &b);
    if (a == 0) {
        return sWfcTextEdit->text[0] != 0 ? 1 : 0;
    }
    if (b == 1) {
        if (sWfcTextEdit->text[0] == 0) return 0;
    }
    r = WfcUtil_StrNLen(sWfcTextEdit->text, 0x20);
    switch (r) {
    case 0:
    case 5:
    case 13:
    case 16:
        return 1;
    case 10:
    case 26:
    case 32: {
        i = 0;
        if (r > 0) {
            u8 *p = sWfcTextEdit->text;
            do {
                c = *p;
                if (c >= 0x30 && c <= 0x39) goto next;
                if (c >= 0x41 && c <= 0x46) goto next;
                if (c >= 0x61 && c <= 0x66) goto next;
                return 0;
            next:
                i++;
                p++;
            } while (i < r);
        }
        return 1;
    }
    }
    return 0;
}

void WfcTextEdit_WaitErrorDialog() {
    if (WfcDialog_GetResult() != 0) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcTextEdit_ReturnToInput);
}

void WfcTextEdit_ReturnToInput() {
    if (WfcDialog_IsOpen() != 0) return;
    sWfcTextEdit->caretOam->attr01 &= 0xc1fffcff;
    WfcUtil_SetScene(WfcTextEdit_OpenKeyboard);
}
}
#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02213424) {
    HOST_OVERLAY_VAR(sWfcTextEditTitleMsgs),
    HOST_OVERLAY_VAR(sWfcTextEditConfirmMsgs),
    HOST_OVERLAY_VAR(sWfcTextEditStoreFuncs),
    HOST_OVERLAY_VAR(sWfcTextEdit),
    HOST_OVERLAY_VARS_END
};
