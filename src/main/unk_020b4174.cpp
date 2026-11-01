#include "types.h"
#include "host_tick.h"
#include "host_labels.h"
#include "sys/ProcProfile.h"
#include "Unk_020d8c7c.h"
#include "sys/SceneBase.h"
#include "nitro/io_access.h"
#include "save/SaveData.h"
#include "save/SaveRecord4.h"
#include "proto/main/unk_020b4828.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_0210fa84.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_020536dc.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020b4174.h"

extern "C" const u8 data_020d0c08;

extern "C" {
void VillagerStates_Init(void);
void VillagerStates_Destroy(void);
void SaveData_Apply(void *p);
void SaveData_Setup(void *p, u32 x);
void VramQueue2d_Init(void);
void VramQueueTex_Init(void);
void GX_SetBankForSubBG(u32 x);
void MI_CpuCopy8(const void *src, void *dst, u32 size);

extern u8 gSaveData;
#define gSaveFooter HOST_LABEL(u8 *, gSaveFooter)
}


class BootLogoScene : public SceneBase {
public:
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();

    void applyLoadedSave();
    void chooseSaveSlot();
    void setupGraphics();

    /* 0x50 */ u8 logoState;
    /* 0x51 */ volatile u8 fadeTimer;
    /* 0x54 */ u64 startTick;
    /* 0x5c */ u8 slot0Result;
    /* 0x5d */ u8 slot1Result;
    /* 0x5e */ u8 loadResult;
    /* 0x5f */ u8 loadState;
    /* 0x60 */ Heap *bufferHeap;
    /* 0x64 */ u8 *slot0Buffer;
    /* 0x68 */ u8 *slot1Buffer;
};

extern "C" BootLogoScene *BootLogoScene_Create(void) { return new BootLogoScene; }

ProcProfile data_020e3fd4 = {(void *(*)())BootLogoScene_Create, 0x1, 0x0};

BOOL BootLogoScene::onCreate() {
    gVBlanksPerFrame = 3;
    Snd_CreateScene();
    logoState = 0;
    bufferHeap = gCurrentHeap;
    slot0Buffer = (u8 *)Heap_Alloc(bufferHeap, 0x15fe0);
    slot1Buffer = (u8 *)Heap_Alloc(bufferHeap, 0x15fe0);
    return TRUE;
}

BOOL BootLogoScene::onDelete() {
    Heap_Free(bufferHeap, slot0Buffer);
    Heap_Free(bufferHeap, slot1Buffer);
    return TRUE;
}

BOOL BootLogoScene::onExecute() {
    switch (loadState) {
    case 0:
        if (logoState == 1) loadState = 1;
        break;
    case 1: {
        u32 r = Save_ReadSlotAsyncStep(0, slot0Buffer);
        if (r != 3) {
            slot0Result = r;
            loadState = 2;
        }
        break;
    }
    case 2: {
        u32 r = Save_ReadSlotAsyncStep(1, slot1Buffer);
        if (r != 3) {
            slot1Result = r;
            loadState = 3;
        }
        break;
    }
    }
    switch (logoState) {
    case 0:
        setupGraphics();
        Gfx2d_SetBrightness(-16);
        logoState = 1;
        fadeTimer = 0x10;
        Snd_PlaySe(0x88c);
        break;
    case 1:
        if (fadeTimer != 0) {
            fadeTimer = fadeTimer - (TICK_STEP_ENDS() ? 1 : 0);
            Gfx2d_SetBrightness(-fadeTimer);
        } else {
            logoState = 2;
            startTick = OS_GetTick();
        }
        break;
    case 2: {
        u64 now = OS_GetTick();
        if (loadState < 5) {
            if (loadState < 3) break;
            chooseSaveSlot();
            applyLoadedSave();
            loadState = 5;
        }
        if (now - startTick < 0x7fd88) break;
        logoState = 3;
        fadeTimer = 0x10;
        break;
    }
    case 3:
        if (fadeTimer != 0) {
            fadeTimer = fadeTimer - (TICK_STEP_ENDS() ? 1 : 0);
            Gfx2d_SetBrightness(fadeTimer - 0x10);
        } else {
            Gfx2d_SetMainPlanes(0);
            Gfx2d_SetSubPlanes(0);
            logoState = 4;
            SceneWarp_RequestScene(Scene_GetWarpRequest(), 0x2c);
            FieldScene_Request(3, 2);
        }
        break;
    }
    return TRUE;
}

void BootLogoScene::setupGraphics() {
    Gfx_ResetScene();
    VramQueue2d_Init();
    VramQueueTex_Init();
    Gfx_DisableAllBanks();
    GX_SetBankForBG(0x20);
    GX_SetBankForSubBG(0x80);
    IO_W((volatile u32 *)0x4000000, IO_R((volatile u32 *)0x4000000) & 0xffcfffef);
    IO_W((volatile u32 *)0x4001000, IO_R((volatile u32 *)0x4001000) & 0xffcfffef);
    Gfx2d_SetMainBgMode(0);
    Gfx2d_SetSubBgMode(0);
    IO_W((volatile u32 *)0x4000000, IO_R((volatile u32 *)0x4000000) & 0xc7ffffff);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerControl(2, 0, 0, 0);
    void *heap = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/nin/nin.bch", heap, 6, 0, 0, 0x2ff);
    Gfx2d_LoadPaletteFile("menu/nin/ninE.bpl", heap, 6, 0, 0, 0);
    Gfx2d_LoadScreenFile("menu/nin/nin.bsc", heap, 6);
    Gfx2d_LoadCharFile("menu/nin/arrE.bch", heap, 2, 0, 0, 0x13f);
    Gfx2d_LoadPaletteFile("menu/nin/arrE.bpl", heap, 2, 0, 0, 0);
    Gfx2d_LoadScreenFile("menu/nin/arrE.bsc", heap, 2);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(2);
}

void BootLogoScene::chooseSaveSlot() {
    if (slot0Result == 1 || slot1Result == 1) {
        loadResult = 1;
    } else if (slot0Result != 0 && slot1Result != 0) {
        loadResult = 4;
    } else {
        u32 r;
        if (slot0Result != 0) {
            r = 1;
        } else if (slot1Result != 0) {
            r = 0;
        } else {
            r = Save_SlotStampsMatch();
        }
        if (r == 0) {
            MI_CpuCopy8(slot0Buffer, &gSaveData, 0x15fe0);
        } else {
            MI_CpuCopy8(slot1Buffer, &gSaveData, 0x15fe0);
        }
        loadResult = 0;
    }
}

void BootLogoScene::applyLoadedSave() {
    BgHeap_Create(0x5000, 0);
    if (loadResult == 4 || loadResult == 1) {
        if (loadResult == 4) {
            if (!((SaveRecord4 *)(&gSaveFooter))->isStateUnset()) SaveManager_SetSaveCorrupted(1);
        }
        if (loadResult == 4) Save_InvalidateLetterStorage();
        ((SaveData *)(&gSaveData))->reset();
        GuestPlayers_ResetAll();
        VillagerStates_Init();
        SaveData_Setup(&gSaveData, 3);
    } else {
        SaveData_Setup(&gSaveData, 4);
    }
    SaveData_Apply(&gSaveData);
    VillagerStates_Destroy();
    BgHeap_Destroy();
}




const u8 data_020d0c08 = 0x11;
