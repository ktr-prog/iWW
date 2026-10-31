#include "types.h"
#include "nitro/gxoam.h"
#include "nitro/io_access.h"
#include "net/WfcLoadFunc.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_0212b770.h"
#include "proto/ov001/unk_ov001_02208244.h"
#include "proto/ov001/unk_ov001_02208388.h"
#include "proto/ov001/unk_ov001_02208890.h"
#include "proto/ov001/unk_ov001_0220aba4.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_022140bc.h"
#include "proto/ov001/unk_ov001_022156e0.h"
#include "proto/ov001/unk_ov001_0221dcec.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_0221feac.h"
#include "proto/ov001/unk_ov001_02224b14.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225924.h"
#include "proto/ov001/unk_ov001_022266b0.h"

struct WfcAddrEdit {
    WfcTextCanvas *textCanvas;
    GXOamAttr *caretOam;
    u8 name[12];
    u8 octetIndex;
    u8 result;
};

typedef void (*WfcAddrEditLoadFunc)(void *digits);
typedef void (*WfcAddrEditStoreFunc)(u8 *digits);

#pragma thumb off
extern "C" {
void MI_CpuFill8(void *dst, u8 v, u32 size);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
s32 DWC_BACKUPlCheckAddress(u8 *addr);


const u16 data_ov001_0222a070[2] = {0x0b, 0x10};
const u8 data_ov001_0222a074[12] = {0x31, 0x3d, 0x49, 0x5a, 0x66, 0x72, 0x83, 0x8f, 0x9b, 0xac, 0xb8, 0xc4};
u8 data_ov001_0222af7c[4] = {0x32, 0x35, 0x35, 0};
u8 sWfcAddrEditTitleMsgs[8] = {0x91, 0x92, 0x93, 0x94, 0x95, 0, 0, 0};
u16 data_ov001_0222af88[4] = {0, 0x29, 0, 0};
WfcAddrEditLoadFunc sWfcAddrEditLoadFuncs[5] = {WfcConfig_FormatEditIp, WfcConfig_FormatEditSubnetMask, WfcConfig_FormatEditGateway, WfcConfig_FormatEditDns1, WfcConfig_FormatEditDns2};
WfcAddrEditStoreFunc sWfcAddrEditStoreFuncs[5] = {WfcConfig_SetEditIp, WfcConfig_SetEditSubnetMask, WfcConfig_SetEditGateway, WfcConfig_SetEditDns1, WfcConfig_SetEditDns2};
WfcAddrEdit *sWfcAddrEdit;

void WfcAddrEdit_Enter() {
    u32 idx;
    sWfcAddrEdit = (WfcAddrEdit *)WfcHeap_AllocClear(sizeof(WfcAddrEdit), 4);
    WfcUtil_GetEditParams(&idx, 0);
    sWfcAddrEditLoadFuncs[idx](sWfcAddrEdit->name);
    WfcAddrEdit *o = sWfcAddrEdit;
    if (memcmp(o->name, "  0", 3) != 0) {
        o->octetIndex = 3;
    } else {
        MI_CpuFill8(o->name, 0, 12);
        sWfcAddrEdit->octetIndex = 0;
    }
    WfcAddrEdit_LoadBg();
    WfcHighlight_Set(idx + 0xb);
    WfcUtil_ShowTopMessage(sWfcAddrEditTitleMsgs[idx], -1, 0);
    WfcUtil_ShowStepIndicator(2);
    sWfcAddrEdit->textCanvas = WfcText_CreateBgCanvas(0, 0);
    sWfcAddrEdit->caretOam = WfcObj_CreateSingle(0, 0x3f);
    GXOamAttr *caret = sWfcAddrEdit->caretOam;
    caret->attr2 = (caret->attr2 & ~0xc00) | 0xc00;
    WfcAddrEdit_UpdateCaret();
    WfcAddrEdit_DrawText();
    WfcUtil_SetScene(WfcAddrEdit_FadeIn);
}

void WfcAddrEdit_LoadBg() {
    WfcUtil_LoadFileTo((void *)"char/ybObjKb.ncl.l", GX_LoadOBJPltt);
    WfcUtil_LoadFileTo((void *)"char/jbBgStep3.ncg.l", GX_LoadBG2Char);
    WfcUtil_LoadFileTo((void *)"char/ybBgStep3.ncl.l", GX_LoadBGPltt);
    WfcUtil_LoadFileTo((void *)"char/xb4EditAddr.nsc.l", GX_LoadBG2Scr);
    volatile u16 *r1 = (volatile u16 *)0x4001008;
    volatile u16 *r2 = (volatile u16 *)0x400100a;
    volatile u16 *r3 = (volatile u16 *)0x4000008;
    volatile u16 *r4 = (volatile u16 *)0x400000a;
    volatile u16 *r5 = (volatile u16 *)0x400000c;
    IO_W(r1, (IO_R(r1) & ~3) | 3);
    IO_W(r2, (IO_R(r2) & ~3) | 3);
    IO_W(r3, (IO_R(r3) & ~3) | 2);
    IO_W(r4, (IO_R(r4) & ~3) | 3);
    IO_W(r5, (IO_R(r5) & ~3) | 3);
}

void WfcAddrEdit_FadeIn() {
    WfcFade_Start(2, 1, 1, 8);
    WfcFade_Start(2, 0, 0x15, 8);
    WfcGx_ShowPlanes(1, 1);
    WfcGx_ShowPlanes(0, 0x15);
    WfcUtil_SetScene(WfcAddrEdit_OpenKeypad);
}

void WfcAddrEdit_OpenKeypad() {
    if (WfcFade_IsBusy(1) != 0) return;
    if (WfcFade_IsBusy(0) != 0) return;
    WfcNumPad_Create();
    WfcSound_Play(0x14);
    if (sWfcAddrEdit->octetIndex == 0) {
        WfcNumPad_SetDeleteEnabled(0);
        WfcNumPad_SetDotEnabled(0);
    } else {
        if (WfcAddrEdit_IsOctetFull(0x1a) != 0) {
            WfcNumPad_SetInsertEnabled(0);
        }
        WfcNumPad_SetDotEnabled(0);
    }
    WfcUtil_SetScene(WfcAddrEdit_WaitKeypad);
}

void WfcAddrEdit_WaitKeypad() {
    if (WfcNumPad_GetKey() == 0x1f) return;
    WfcUtil_SetScene(WfcAddrEdit_Update);
}

void WfcAddrEdit_Update() {
    WfcAddrEdit_HandleKey();
    WfcAddrEdit_Idle();
}

void WfcAddrEdit_HandleKey() {
    s32 r = WfcNumPad_GetKey();
    WfcAddrEdit *g;
    switch (r) {
    case 0:
        return;
    case 0x10:
        g = sWfcAddrEdit;
        if (g->octetIndex == 0 && g->name[2] == 0) goto end;
        WfcSound_Play(3);
        {
            u32 k = sWfcAddrEdit->octetIndex;
            if (sWfcAddrEdit->name[k * 3 + 2] == 0) sWfcAddrEdit->octetIndex = k - 1;
        }
        MI_CpuFill8(&sWfcAddrEdit->name[sWfcAddrEdit->octetIndex * 3], 0, 3);
        g = sWfcAddrEdit;
        if (g->octetIndex == 0 && g->name[2] == 0) WfcNumPad_SetDeleteEnabled(0);
        WfcNumPad_SetInsertEnabled(1);
        WfcNumPad_SetDotEnabled(0);
        goto end;
    case 0x11: {
        g = sWfcAddrEdit;
        u32 k = g->octetIndex;
        if (k >= 3) goto end;
        if (g->name[k * 3 + 2] == 0) goto end;
        WfcSound_Play(1);
        sWfcAddrEdit->octetIndex = sWfcAddrEdit->octetIndex + 1;
        WfcNumPad_SetDotEnabled(0);
        goto end;
    }
    case 0x12:
        sWfcAddrEdit->result = 0;
        WfcSound_Play(7);
        WfcUtil_SetScene(WfcAddrEdit_StartExit);
        return;
    case 0x13:
        if (WfcAddrEdit_ValidateAddress()) {
            WfcSound_Play(6);
            sWfcAddrEdit->result = 1;
        } else {
            sWfcAddrEdit->result = 2;
            WfcSound_Play(9);
        }
        sWfcAddrEdit->octetIndex = 3;
        {
            volatile u32 *reg = &sWfcAddrEdit->caretOam->attr01;
            *reg = (*reg & 0xc1fffcff) | 0x200;
        }
        WfcAddrEdit_UpdateCaret();
        WfcAddrEdit_NormalizeOctets();
        WfcUtil_SetScene(WfcAddrEdit_StartExit);
        return;
    default: {
        if (sWfcAddrEdit->octetIndex == 3) {
            if (WfcAddrEdit_IsOctetFull(0x1a) != 0) goto end;
        }
        WfcSound_Play(1);
        {
            WfcAddrEdit *h = sWfcAddrEdit;
            u32 idx = h->octetIndex;
            u8 *base = h->name;
            u32 lr = idx * 3;
            u8 *ip = base + (lr + 2);
            u32 t = *ip;
            if (t == 0) {
                *ip = r;
            } else {
                u8 *p1 = base + (lr + 1);
                u32 c = *p1;
                if (c == 0) {
                    *p1 = t;
                    *ip = r;
                    if (WfcAddrEdit_IsOctetFull(0x1a) != 0) {
                        if (sWfcAddrEdit->octetIndex < 3) sWfcAddrEdit->octetIndex++;
                    }
                } else {
                    base[lr] = c;
                    *p1 = *ip;
                    *ip = r;
                    if (sWfcAddrEdit->octetIndex < 3) sWfcAddrEdit->octetIndex++;
                }
            }
        }
        WfcNumPad_SetDeleteEnabled(1);
        if (sWfcAddrEdit->octetIndex < 3) {
            WfcNumPad_SetDotEnabled(1);
        } else {
            WfcNumPad_SetDotEnabled(0);
        }
        if (sWfcAddrEdit->octetIndex == 3) {
            if (WfcAddrEdit_IsOctetFull(0x1a) != 0) WfcNumPad_SetInsertEnabled(0);
        }
    }
    }
end:
    WfcAddrEdit_DrawText();
    WfcAddrEdit_UpdateCaret();
}

s32 WfcAddrEdit_IsOctetFull(s32 n) {
    u8 buf[4];
    s32 i;
    WfcAddrEdit *g = sWfcAddrEdit;
    u8 *p = &g->name[g->octetIndex * 3];
    u32 c = *p;
    u8 *q;
    if (c != 0 && c != 0x20) return 1;
    MI_CpuCopy8(p, buf, 3);
    buf[3] = 0;
    q = buf;
    for (i = 0; i < 3; i++) {
        if (*q != 0) break;
        *q++ = 0x20;
    }
    if (atol((const char *)buf) >= n) return 1;
    return 0;
}

void WfcAddrEdit_Idle() {
}

void WfcAddrEdit_StartExit() {
    WfcFade_StartWait(8);
    WfcUtil_SetScene(WfcAddrEdit_CloseKeypad);
}

void WfcAddrEdit_CloseKeypad() {
    if (WfcFade_IsBusy(1)) return;
    WfcNumPad_Close();
    WfcSound_Play(0x15);
    WfcUtil_SetScene(WfcAddrEdit_WaitKeypadClosed);
}

void WfcAddrEdit_WaitKeypadClosed() {
    if (WfcNumPad_Exists()) return;
    u32 t = sWfcAddrEdit->result;
    if (t == 0) {
        WfcUtil_SetScene(WfcAddrEdit_Exit);
        return;
    }
    if (t == 2) {
        WfcDialog_Open(0x2f, 3, 1, -1, 0);
        WfcUtil_SetScene(WfcAddrEdit_WaitErrorDialog);
        return;
    }
    WfcDialog_Open(0x9b, 2, 1, -1, 0);
    WfcUtil_SetScene(WfcAddrEdit_WaitConfirmDialog);
}

void WfcAddrEdit_Exit() {
    u32 v;
    WfcUtil_HideTopMessage();
    WfcOam_FreeEntry(sWfcAddrEdit->caretOam);
    WfcText_DestroyBgCanvas(0);
    WfcUtil_LoadFileTo((void *)"char/ybObjMain.ncl.l", GX_LoadOBJPltt);
    WfcGx_HidePlanes(1, 1);
    WfcGx_HidePlanes(0, 0x15);
    WfcUtil_GetEditParams(&v, 0);
    if (v >= 3) v = v + 1;
    WfcUtil_SetScreenFlags(2, 1);
    WfcUtil_SetEditParams(0, v + 3);
    WfcUtil_SetScene(WfcManualSetup_Enter);
    WfcHeap_FreeAndClear((void **)&sWfcAddrEdit);
}

void WfcAddrEdit_DrawText() {
    u16 v[6];
    s32 i;
    const u8 *q;
    v[0] = data_ov001_0222af88[0];
    v[1] = data_ov001_0222af88[1];
    v[2] = data_ov001_0222af88[2];
    v[3] = data_ov001_0222af88[3];
    v[2] = data_ov001_0222a070[0];
    v[3] = data_ov001_0222a070[1];
    WfcText_Clear(sWfcAddrEdit->textCanvas, 0);
    v[5] = 0;
    q = data_ov001_0222a074;
    for (i = 0; i < 12; i++, q++) {
        WfcAddrEdit *g = sWfcAddrEdit;
        u32 t;
        v[4] = g->name[i];
        t = *q;
        v[0] = t;
        WfcText_DrawTextRect(g->textCanvas, t, v[1], v[2], v[3], 2, 0x480, &v[4]);
    }
    WfcText_RequestTransfer(sWfcAddrEdit->textCanvas);
}

void WfcAddrEdit_UpdateCaret() {
    s32 idx = sWfcAddrEdit->octetIndex;
    if (idx > 3) idx = 3;
    u32 t = data_ov001_0222a074[idx * 3 + 2];
    GXOamAttr *caret = sWfcAddrEdit->caretOam;
    caret->attr01 = ((t & 0x1ff) << 16) | ((caret->attr01 & 0xfe00ff00) | 0x28);
}

void WfcAddrEdit_WaitConfirmDialog() {
    sWfcAddrEdit->result = WfcDialog_GetResult();
    switch (sWfcAddrEdit->result) {
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
    WfcUtil_SetScene(WfcAddrEdit_ApplyAndExit);
}

void WfcAddrEdit_ApplyAndExit() {
    u32 v;
    if (WfcDialog_IsOpen()) return;
    if (sWfcAddrEdit->result == 0) {
        sWfcAddrEdit->caretOam->attr01 &= 0xc1fffcff;
        WfcUtil_SetScene(WfcAddrEdit_OpenKeypad);
        return;
    }
    WfcUtil_GetEditParams(&v, 0);
    sWfcAddrEditStoreFuncs[v](sWfcAddrEdit->name);
    WfcUtil_SetScene(WfcAddrEdit_Exit);
}

void WfcAddrEdit_NormalizeOctets() {
    u8 *p;
    s32 i;
    s32 j;
    s32 off;
    i = 0; off = i;
    for (; i < 4; i++, off += 3) {
        p = sWfcAddrEdit->name + off;
        for (j = 0; j < 3; j++) {
            u32 c = p[j];
            if (c == 0x30 || c == 0x20 || c == 0) {
                p[j] = (j == 2) ? 0x30 : 0x20;
            } else {
                break;
            }
        }
    }
    WfcAddrEdit_DrawText();
}

s32 WfcAddrEdit_ValidateAddress() {
    u8 *p;
    s32 i, off, j;
    const u8 *maxDigits = data_ov001_0222af7c;
    u32 v;
    u8 out[4];
    WfcAddrEdit *g = sWfcAddrEdit;
    for (i = 0, off = 0; i < 4; i++, off += 3) {
        p = g->name + off;
        if (*p != 0x20) {
            for (j = 0; j < 3; j++) {
                if (p[j] > maxDigits[j]) return 0;
                if (p[j] < maxDigits[j]) break;
            }
        }
    }
    WfcUtil_ParseIpDigits(g->name, out);
    WfcUtil_GetEditParams(&v, 0);
    if (v == 1) {
        BOOL seen = FALSE;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 8; j++) {
                if (seen) {
                    if (out[i] & (1 << (7 - j))) return 0;
                } else {
                    if ((out[i] & (1 << (7 - j))) == 0) seen = TRUE;
                }
            }
        }
        return 1;
    }
    if (DWC_BACKUPlCheckAddress(out) != 0) return 1;
    return 0;
}

void WfcAddrEdit_WaitErrorDialog() {
    if (WfcDialog_GetResult()) return;
    WfcSound_Play(6);
    WfcDialog_Close();
    WfcUtil_SetScene(WfcAddrEdit_ReturnToInput);
}

void WfcAddrEdit_ReturnToInput() {
    if (WfcDialog_IsOpen()) return;
    sWfcAddrEdit->caretOam->attr01 &= 0xc1fffcff;
    WfcUtil_SetScene(WfcAddrEdit_OpenKeypad);
}
}
#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_022140bc) {
    HOST_OVERLAY_VAR(data_ov001_0222af7c),
    HOST_OVERLAY_VAR(sWfcAddrEditTitleMsgs),
    HOST_OVERLAY_VAR(data_ov001_0222af88),
    HOST_OVERLAY_VAR(sWfcAddrEditLoadFuncs),
    HOST_OVERLAY_VAR(sWfcAddrEditStoreFuncs),
    HOST_OVERLAY_VAR(sWfcAddrEdit),
    HOST_OVERLAY_VARS_END
};
