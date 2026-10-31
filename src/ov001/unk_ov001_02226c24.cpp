#include "types.h"
#include "host_mem.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_0210fa84.h"
#include "proto/ov001/unk_ov001_02226c24.h"

struct WfcVramBankState {
    u32 bg, obj, bgExtPltt, objExtPltt, tex, texPltt, clearImage, subBg, subObj, subBgExtPltt, subObjExtPltt, arm7, lcdc;
};

extern "C" {
u32 GX_DisableBankForBG();
u32 GX_DisableBankForOBJ();
u32 GX_DisableBankForBGExtPltt();
u32 GX_DisableBankForOBJExtPltt();
u32 GX_DisableBankForTex();
u32 GX_DisableBankForTexPltt();
u32 GX_DisableBankForClearImage();
u32 GX_DisableBankForSubBG();
u32 GX_DisableBankForSubOBJ();
u32 GX_DisableBankForSubBGExtPltt();
u32 GX_DisableBankForSubOBJExtPltt();
u32 GX_DisableBankForARM7();
u32 GX_DisableBankForLCDC();
void GX_SetBankForSubBG(u32);
void GX_SetBankForSubOBJ(u32);
void GX_SetBankForSubBGExtPltt(u32);
void GX_SetBankForSubOBJExtPltt(u32);
void GX_SetBankForLCDC(u32);
void GX_SetBankForARM7(u32);
void PM_SetLCDPower(s32);
void PMi_SendLEDPatternCommand(s32);
s32 PM_GetLEDPattern(u32 *);
void MIi_CpuClearFast(u32, void *, u32);
}

extern "C" WfcVramBankState sWfcSavedVramBanks = {0};

#pragma thumb off

void WfcGx_SaveVramBanks() {
    sWfcSavedVramBanks.bg = GX_DisableBankForBG();
    sWfcSavedVramBanks.obj = GX_DisableBankForOBJ();
    sWfcSavedVramBanks.bgExtPltt = GX_DisableBankForBGExtPltt();
    sWfcSavedVramBanks.objExtPltt = GX_DisableBankForOBJExtPltt();
    sWfcSavedVramBanks.tex = GX_DisableBankForTex();
    sWfcSavedVramBanks.texPltt = GX_DisableBankForTexPltt();
    sWfcSavedVramBanks.clearImage = GX_DisableBankForClearImage();
    sWfcSavedVramBanks.subBg = GX_DisableBankForSubBG();
    sWfcSavedVramBanks.subObj = GX_DisableBankForSubOBJ();
    sWfcSavedVramBanks.subBgExtPltt = GX_DisableBankForSubBGExtPltt();
    sWfcSavedVramBanks.subObjExtPltt = GX_DisableBankForSubOBJExtPltt();
    sWfcSavedVramBanks.arm7 = GX_DisableBankForARM7();
    sWfcSavedVramBanks.lcdc = GX_DisableBankForLCDC();
    GX_SetBankForARM7(sWfcSavedVramBanks.arm7);
    WfcGx_ClearVram();
}

void WfcGx_RestoreVramBanks() {
    GX_DisableBankForBG();
    GX_DisableBankForOBJ();
    GX_DisableBankForSubBG();
    GX_DisableBankForSubOBJ();
    WfcGx_ClearVram();
    GX_SetBankForBG(sWfcSavedVramBanks.bg);
    GX_SetBankForOBJ(sWfcSavedVramBanks.obj);
    GX_SetBankForBGExtPltt(sWfcSavedVramBanks.bgExtPltt);
    GX_SetBankForOBJExtPltt(sWfcSavedVramBanks.objExtPltt);
    GX_SetBankForTex(sWfcSavedVramBanks.tex);
    GX_SetBankForTexPltt(sWfcSavedVramBanks.texPltt);
    GX_SetBankForClearImage(sWfcSavedVramBanks.clearImage);
    GX_SetBankForSubBG(sWfcSavedVramBanks.subBg);
    GX_SetBankForSubOBJ(sWfcSavedVramBanks.subObj);
    GX_SetBankForSubBGExtPltt(sWfcSavedVramBanks.subBgExtPltt);
    GX_SetBankForSubOBJExtPltt(sWfcSavedVramBanks.subObjExtPltt);
    GX_SetBankForLCDC(sWfcSavedVramBanks.lcdc);
    IO_W((volatile u16 *)0x4000050, 0);
    IO_W((volatile u16 *)0x4001050, 0);
    IO_W((volatile u32 *)0x4000010, 0);
    IO_W((volatile u32 *)0x4000014, 0);
    IO_W((volatile u32 *)0x4000018, 0);
    IO_W((volatile u32 *)0x400001c, 0);
    IO_W((volatile u32 *)0x4001010, 0);
    IO_W((volatile u32 *)0x4001014, 0);
    IO_W((volatile u32 *)0x4001018, 0);
    IO_W((volatile u32 *)0x400101c, 0);
    PM_SetLCDPower(1);
}

void WfcGx_ClearVram()
{
    volatile u32 a, b, c, d, e, f;
    GX_SetBankForLCDC(0x1f3);
    c = 0;
    MIi_CpuClearFast(c, HostVram_CpuPtr(0x06800000), 0x40000);
    d = 0;
    MIi_CpuClearFast(d, HostVram_CpuPtr(0x06880000), 0x24000);
    GX_DisableBankForLCDC();
    a = 0x200;
    MIi_CpuClearFast(a, (void *)HW_OAM, 0x400);
    e = 0;
    MIi_CpuClearFast(e, (void *)HW_PLTT, 0x400);
    b = 0x200;
    MIi_CpuClearFast(b, (void *)(HW_OAM + 0x400), 0x400);
    f = 0;
    MIi_CpuClearFast(f, (void *)(HW_PLTT + 0x400), 0x400);
}

void WfcUtil_UpdateLed()
{
    u32 v;
    if (PM_GetLEDPattern(&v) != 0) return;
    if (v == 0xf) return;
    PMi_SendLEDPatternCommand(0xf);
}

void WfcUtil_RestoreLed()
{
    PMi_SendLEDPatternCommand(1);
}

s32 WfcUtil_StrNLen(u8 *s, s32 n)
{
    s32 i = 0;
    if (n > 0) {
        do {
            if (s[i] == 0) break;
            i++;
        } while (i < n);
    }
    return i;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_02226c24) {
    HOST_OVERLAY_VAR(sWfcSavedVramBanks),
    HOST_OVERLAY_VARS_END
};
