#include "uptr.h"
#include "host_mem.h"
#include "types.h"
#include "sdk_linker_symbols.h"
#include "nitro/io_access.h"
#include "sys/OSThread.h"
#include "game/GroundInfo.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_020fe5c0.h"
#include "proto/autoload_2/unk_0210f154.h"
#include "proto/autoload_2/unk_02114624.h"
#include "proto/autoload_2/unk_02114d84.h"
#include "proto/itcm/unk_01ffc538.h"
#include "proto/itcm/unk_01ffcb2c.h"
#include "proto/itcm/unk_01ffcc60.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020e1e2c.h"
#include "proto/main/unk_020376c0.h"
#include "proto/main/unk_02037734.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_020536dc.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/main/unk_0206d5b8.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_02097110.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209c9f8.h"
#include "proto/main/unk_020b0a80.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov004/unk_ov004_0222a500.h"

extern "C" {
}


extern "C" {
u32 Scene_GetCurrent(void);
BOOL SceneId_IsNookShop(u32 a);
BOOL SceneId_IsHouseRoom(u32 a);
BOOL SceneId_IsUnk6To8(u32 a);
BOOL SceneId_IsMuseumRoom(u32 a);
BOOL GroundSeason_IsSnow(void);
u32 Ground_GetExitAtPos(void *p);
u32 GroundAttr_GetFootstepSe(u32 a);
u32 ItemInfo_GetIndoorUnk1(u16 *p);
extern u8 gFieldSceneKind;
void MIi_CpuClearFast(u32 value, void *dst, u32 size);
void GX_SetBankForLCDC(u32 a);
void GX_DisableBankForLCDC(void);
u32 OS_EnableInterrupts(void);
void OS_RestoreInterrupts(u32 a);
void FS_Init(u32 a);
void DC_FlushRange(u32 a, u32 b);
void OS_SetProtectionRegion2(u32 a);
void OS_SetArenaHi(s32 id, void *hi);
void Math_InitSqrt64(void);
void HBlank_Init(void);
void OS_SetIrqFunction(u32 a, void (*cb)(void));
void OS_EnableIrqMask(u32 a);
void GX_VBlankIntr(u32 a);
void GX_HBlankIntr(u32 a);
void Backup_InitDefault(void);
void OverlayHandle_Unload(void *p);
void Main_ResetFrameCounter(void);
void Clock_Init(void);
void Field_ResetActions(void);
}

extern "C" {
}


extern "C" {
}

volatile u8 sWvrStartUpDone;


extern "C" {
extern ProcProfile **gProfileTable;
}

extern "C" {
extern OSThreadQueue gVBlankQueue;
extern OSThreadQueue gFrameWaitQueue;
extern u8 sVBlankReady;
}

inline BOOL isFlag1() {
    return gFieldSceneKind == 1;
}
inline BOOL isSpecial(u32 b) {
    BOOL r = TRUE;
    if ((u8)(b + 0xf5) > 3 && b != 0x2f) {
        r = FALSE;
    }
    return r;
}
inline BOOL isFlag0() {
    return gFieldSceneKind == 0;
}
extern "C" u32 Footstep_AttrToSe(u32 a) {
    u32 b = Scene_GetCurrent();
    u32 r = GroundAttr_GetFootstepSe(a);
    if (r == 0xffff) {
        if (isFlag0()) {
            r = 0xc8;
        } else if (SceneId_IsNookShop(b)) {
            r = Footstep_GetSeForAttr(5);
        } else if (SceneId_IsHouseRoom(b) || SceneId_IsUnk6To8(b)) {
            r = Footstep_GetSeForAttr(6);
        } else if (SceneId_IsMuseumRoom(b)) {
            r = Footstep_GetSeForAttr(5);
        } else {
            r = 0x4a6;
        }
    }
    if (r == 0xc0) {
        if (GroundSeason_IsSnow()) {
            if (isFlag0() || isSpecial(b)) {
                r = 0x877;
            }
        }
    }
    return r;
}

extern "C" u32 GroundAttr_ResolveCarpet(u32 a) {
    if (a == 0x1a) {
        if (isFlag1()) {
            u16 v = *RoomShell_GetCarpet();
            return ItemInfo_GetIndoorUnk1(&v);
        }
    }
    return a;
}

extern "C" u32 GroundAttr_GetAtPos(VecFx32 *a) {
    GroundInfo g;
    g.initAtPos(a, 0, 0);
    return GroundAttr_ResolveCarpet(g.attr);
}

extern "C" u32 Footstep_GetSeForAttr(u32 a) {
    return Footstep_AttrToSe(GroundAttr_ResolveCarpet(a));
}

extern "C" u32 Footstep_GetSeAtPos(VecFx32 *a) {
    if (Ground_GetExitAtPos(a) != (u32)-1) {
        u32 b = Scene_GetCurrent();
        if (SceneId_IsNookShop(b)) {
            return Footstep_GetSeForAttr(5);
        }
        if (SceneId_IsHouseRoom(b) || SceneId_IsUnk6To8(b)) {
            return Footstep_GetSeForAttr(6);
        }
        if (SceneId_IsMuseumRoom(b)) {
            return Footstep_GetSeForAttr(5);
        }
    }
    return Footstep_GetSeForAttr(GroundAttr_GetAtPos(a));
}

extern "C" void Main_InitVBlank(void) {
    gVBlankQueue.tail = NULL;
    gVBlankQueue.head = NULL;
    gFrameWaitQueue.tail = NULL;
    gFrameWaitQueue.head = NULL;
    OS_SetIrqFunction(1, Main_VBlankCallback);
    sVBlankReady = 1;
}

extern "C" void Main_InitStub(void) {}

extern "C" void Main_Init(void) {
    Main_InitStub();
    FX_Init();
    Math_InitSqrt64();
    HBlank_Init();
    Main_InitVBlank();
    OS_SetIrqFunction(2, HBlank_Handler);
    OS_EnableIrqMask(3);
    IO_R((vu16 *)0x4000208);
    IO_W((vu16 *)0x4000208, 1);
    OS_EnableInterrupts();
    GX_VBlankIntr(1);
    GX_HBlankIntr(1);
    Backup_InitDefault();
    Main_LoadBuildTime();
    OverlayHandle_Load((OverlayHandleView *)&gOverlayHandle, OVERLAY_69_ID);
    OverlayHandle_Unload(&gOverlayHandle);
    Touch_Init();
    Main_InitTick();
#ifdef HOST64
    Heap_CreateProcHeap(0x13fc8 * 2, 0);
#else
    Heap_CreateProcHeap(0x13fc8, 0);
#endif
    Gfx_Init();
    Snd_Init();
    Main_ResetFrameCounter();
    Clock_Init();
    Field_ResetActions();
    CommCaution_LoadMessages();
    gProfileTable = sProfileTableMain;
    Main_EmptyInitStub();
    Random_SeedGlobal();
    IO_W((vu32 *)0x40004c8, 0x296a5800);
    IO_W((vu32 *)0x40004cc, 0x7fff);
    IO_W((vu32 *)0x40004c0, 0x7fff);
    IO_W((vu32 *)0x40004c4, 0);
    Main_InitNop();
    GameRoot_Boot();
    OverlayHandle_Load((OverlayHandleView *)&gOverlayHandle, OVERLAY_68_ID);
}

extern "C" void Startup_OnWvrStartUp(u32 a, u32 b) {
    if (b != 0) {
        Fatal_Trap();
    }
    sWvrStartUpDone = 1;
}

extern "C" void Startup_SetupMainArena(void) {
    OS_SetProtectionRegion2(0x23ff017);
    OS_SetArenaHi(0, HostMainRam_Ptr(0x023ff000));
}

extern "C" void Startup_FillOverlayArea(void) {}

extern "C" void NitroStartUp(void) {
    vu16 *ime = (vu16 *)0x4000208;
    volatile u32 zero;
    u32 r5;
    u16 old;
    OS_Init();
    OS_InitTick();
    GX_Init();
    GX_SetBankForLCDC(8);
    zero = 0;
    MIi_CpuClearFast(zero, HostVram_CpuPtr(0x06800000), 0x20000);
    GX_DisableBankForLCDC();
    old = IO_R(ime);
    IO_W(ime, 1);
    r5 = OS_EnableInterrupts();
    sWvrStartUpDone = 0;
    WVR_StartUpAsync(8, Startup_OnWvrStartUp, 0);
    while (sWvrStartUpDone == 0) {
    }
    OS_RestoreInterrupts(r5);
    IO_R(ime);
    IO_W(ime, old);
    Startup_SetupMainArena();
    Startup_SetCardPulledOutCallback();
    FS_Init(2);
    Startup_FillOverlayArea();
    OverlayMgr_Init();
    gHeapCreateOption = 1;
    Heap_InitSystem();
}

