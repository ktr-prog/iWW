#include "types.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_0210f154.h"
#include "proto/autoload_2/unk_0210fa84.h"
#include "proto/autoload_2/unk_0211bcdc.h"
#include "proto/autoload_2/unk_0211d20c.h"
#include "proto/itcm/unk_01ffc538.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov001/unk_ov001_0220c37c.h"
#include "proto/ov001/unk_ov001_0220c594.h"
#include "proto/ov001/unk_ov001_0220d1d8.h"
#include "proto/ov001/unk_ov001_0221e930.h"
#include "proto/ov001/unk_ov001_02223fc4.h"
#include "proto/ov001/unk_ov001_02224ca0.h"
#include "proto/ov001/unk_ov001_0222516c.h"
#include "proto/ov001/unk_ov001_02225ea0.h"
#include "proto/ov001/unk_ov001_022265ac.h"
#include "proto/ov001/unk_ov001_022266b0.h"
#include "proto/ov001/unk_ov001_02226994.h"
#include "proto/ov001/unk_ov001_02226c24.h"
#include "proto/ov001/unk_ov001_02226f68.h"

struct WfcParamBits {
    u32 startMode : 4;
    u32 optionFlags : 28;
};

extern "C" {
u8 sWfcLanguage;
u32 sWfcParams;
u8 sWfcExitRequested;
void *sWfcWorkArea;
void (*sWfcSceneFunc)();
u32 sWfcScreenFlags[4];

extern s32 DWC_BM_Init(u8 *buf);
extern void VBlankIntrWait();


extern void WfcHeap_Free(void *p);
extern void *WfcHeap_Alloc(s32, s32);
extern void *WfcHeap_AllocClear(s32, s32);
extern void WfcHeap_FreeAndClear(void *);
extern void WfcConfig_StoreAoss(void *);
extern void MIi_CpuClear16(u32, void *, u32);
extern void MI_CpuCopy8(void *, void *);
extern void OS_GetMacAddress(void *);
extern void GX_VBlankIntr(s32);
extern void GX_SetGraphicsMode(s32, s32, s32);
extern void GXx_SetMasterBrightness_(u32, s32);
extern void G2x_SetBlendBrightness_(u32, s32, s32);
extern void GX_SetBankForSubBG(s32);
extern void GX_SetBankForSubOBJ(s32);
extern void GXS_SetGraphicsMode(s32);
extern s32 OS_IsTickAvailable();
extern s32 OS_IsAlarmAvailable();
extern void FS_Init(s32);
extern void WfcInput_Shutdown();
extern void WfcObj_Shutdown();
extern s32 WfcHeap_Destroy();
extern void WfcObj_Init();
extern void WfcHeap_Init(void *);
extern void WfcInput_Init();
extern void WfcInput_Update();
extern void *WfcPool_Get(void *);
extern void WfcPool_Put(void *, void *);


#pragma thumb off


s32 WfcUtil_Run(void *a, s32 b, u32 c) {
    sWfcWorkArea = a;
    if (WfcUtil_CheckParams(b, c) == 0) return -1;
    sWfcExitRequested = 0;
    WfcUtil_InitSystem();
    WfcUtil_InitDisplay();
    WfcSound_Init();
    WfcUtil_SetScene(WfcBoot_Enter);
    do {
        WfcInput_Update();
        sWfcSceneFunc();
        WfcTask_RunList(0);
        WfcUtil_UpdateLidPower();
        WfcUtil_UpdateLed();
        VBlankIntrWait();
    } while (sWfcExitRequested == 0);
    WfcUtil_Shutdown();
    return 0;
}

s32 WfcUtil_CheckParams(s32 a, u32 b) {
    sWfcLanguage = a;
    sWfcParams = b;
    if (a < 0 || a > 5) return 0;
    if ((u32)(b << 28) >> 28 > 1) return 0;
    if (a != 0) {
        if (((b >> 4) & 1) != 0) return 0;
    }
    if (a == 0) {
        if (((*(volatile u32 *)&sWfcParams >> 4) & 1) == 0) return 0;
    }
    return 1;
}

void WfcUtil_InitSystem() {
    volatile u16 *ime = (volatile u16 *)0x4000208;
    u16 old = IO_R(ime);
    IO_W(ime, 0);
    GX_DispOff();
    IO_AND((volatile u32 *)0x4001000, ~0x10000);
    if (OS_IsTickAvailable() == 0) Fatal_Trap();
    if (OS_IsAlarmAvailable() == 0) Fatal_Trap();
    GX_VBlankIntr(0);
    FX_Init();
    FS_Init(-1);
    TP_Init();
    RTC_Init();
    GX_DispOff();
    IO_AND((volatile u32 *)0x4001000, ~0x10000);
    WfcGx_SaveVramBanks();
    WfcHeap_Init(sWfcWorkArea);
    WfcIrq_Init();
    WfcTask_Init();
    WfcFs_MountArchive();
    WfcInput_Init();
    WfcFade_Init();
    void *p = WfcHeap_Alloc(0x700, 0x20);
    DWC_BM_Init((u8 *)p);
    WfcHeap_FreeAndClear(&p);
}

void WfcUtil_InitDisplay() {
    GX_VBlankIntr(0);
    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    GX_SetGraphicsMode(1, 0, 0);
    IO_AND((volatile u32 *)0x4000000, ~0x1f00);
    IO_AND((volatile u32 *)0x4000000, ~0xe000);
    GXx_SetMasterBrightness_(0x400006c, 0);
    IO_W((volatile u32 *)0x4000000, (IO_R((volatile u32 *)0x4000000) & 0xffcfffef) | 0x200010);
    IO_AND((volatile u16 *)0x4000008, ~0x40);
    IO_AND((volatile u16 *)0x400000a, ~0x40);
    IO_AND((volatile u16 *)0x400000c, ~0x40);
    IO_AND((volatile u16 *)0x400000e, ~0x40);
    IO_W((volatile u32 *)0x4000010, 0);
    IO_W((volatile u32 *)0x4000014, 0);
    IO_W((volatile u32 *)0x4000018, 0);
    IO_W((volatile u32 *)0x400001c, 0);
    G2x_SetBlendBrightness_(0x4000050, 0x3f, 0x10);
    GX_SetBankForSubBG(0x80);
    GX_SetBankForSubOBJ(0x100);
    GXS_SetGraphicsMode(0);
    IO_AND((volatile u32 *)0x4001000, ~0x1f00);
    IO_AND((volatile u32 *)0x4001000, ~0xe000);
    GXx_SetMasterBrightness_(0x400106c, 0);
    IO_W((volatile u32 *)0x4001000, (IO_R((volatile u32 *)0x4001000) & 0xffcfffef) | 0x10);
    IO_AND((volatile u16 *)0x4001008, ~0x40);
    IO_AND((volatile u16 *)0x400100a, ~0x40);
    IO_AND((volatile u16 *)0x400100c, ~0x40);
    IO_AND((volatile u16 *)0x400100e, ~0x40);
    IO_W((volatile u32 *)0x4001010, 0);
    IO_W((volatile u32 *)0x4001014, 0);
    IO_W((volatile u32 *)0x4001018, 0);
    IO_W((volatile u32 *)0x400101c, 0);
    G2x_SetBlendBrightness_(0x4001050, 0x3f, 0x10);
    IO_W((volatile u16 *)0x4000008, (IO_R((volatile u16 *)0x4000008) & 0x43) | 0xc00);
    IO_W((volatile u16 *)0x400000a, (IO_R((volatile u16 *)0x400000a) & 0x43) | 0xd08);
    IO_W((volatile u16 *)0x400000c, (IO_R((volatile u16 *)0x400000c) & 0x43) | 0xe10);
    IO_W((volatile u16 *)0x400000e, (IO_R((volatile u16 *)0x400000e) & 0x43) | 0xf10);
    IO_W((volatile u16 *)0x4001008, (IO_R((volatile u16 *)0x4001008) & 0x43) | 0xc00);
    IO_W((volatile u16 *)0x400100a, (IO_R((volatile u16 *)0x400100a) & 0x43) | 0xd00);
    IO_W((volatile u16 *)0x400100c, (IO_R((volatile u16 *)0x400100c) & 0x43) | 0xe00);
    IO_W((volatile u16 *)0x400100e, (IO_R((volatile u16 *)0x400100e) & 0x43) | 0xf00);
    IO_AND((volatile u16 *)0x4000304, ~0x8000);
    WfcText_Init();
    WfcOam_Init();
    WfcVram_Init();
    WfcObj_Init();
    GX_DispOn();
    IO_OR((volatile u32 *)0x4001000, 0x10000);
    GX_VBlankIntr(1);
}

void WfcUtil_Shutdown() {
    GX_DispOff();
    IO_AND((volatile u32 *)0x4001000, ~0x10000);
    WfcUtil_RestoreLed();
    WfcInput_Shutdown();
    WfcIrq_Restore();
    WfcSound_Shutdown();
    WfcObj_Shutdown();
    WfcOam_Shutdown();
    WfcText_Shutdown();
    WfcFade_Shutdown();
    WfcFs_UnmountArchive();
    WfcTask_Shutdown();
    WfcHeap_Destroy();
    WfcGx_RestoreVramBanks();
}

void WfcUtil_SetScene(void (*f)()) {
    sWfcSceneFunc = f;
}

void WfcUtil_SetScreenFlags(u32 a, u32 b) {
    sWfcScreenFlags[0] = a;
    sWfcScreenFlags[1] = b;
}

void WfcUtil_GetScreenFlags(u32 *a, u32 *b) {
    if (a) *a = sWfcScreenFlags[0];
    if (b) *b = sWfcScreenFlags[1];
}

void WfcUtil_SetEditParams(u32 a, u32 b) {
    sWfcScreenFlags[2] = a;
    sWfcScreenFlags[3] = b;
}

void WfcUtil_GetEditParams(u32 *a, u32 *b) {
    if (a) *a = sWfcScreenFlags[2];
    if (b) *b = sWfcScreenFlags[3];
}

u32 WfcUtil_GetLanguage() {
    return sWfcLanguage;
}

u32 WfcUtil_GetStartMode() {
    return ((WfcParamBits *)&sWfcParams)->startMode;
}

BOOL WfcUtil_TestOptionFlag(u32 m) {
    if (((sWfcParams >> 4) & m) != 0) return TRUE;
    return FALSE;
}

void WfcUtil_RequestExit() {
    sWfcExitRequested = 1;
}
}
#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov001_0220c594) {
    HOST_OVERLAY_VAR(sWfcLanguage),
    HOST_OVERLAY_VAR(sWfcParams),
    HOST_OVERLAY_VAR(sWfcExitRequested),
    HOST_OVERLAY_VAR(sWfcWorkArea),
    HOST_OVERLAY_VAR(sWfcSceneFunc),
    HOST_OVERLAY_VAR(sWfcScreenFlags),
    HOST_OVERLAY_VARS_END
};
