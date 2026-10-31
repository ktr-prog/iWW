#include "talk/MsgString9B.h"
#include "host_labels.h"
#include "talk/MsgString9C.h"
#include "types.h"
#include "sdk_linker_symbols.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "save/BlancaFaceRecord.h"
#include "talk/TalkWindowState.h"
#include "town/TownBlockMap.h"
#include "talk/MsgRequest.h"
#include "ui/HudWallet.h"
#include "talk/TalkMsgRequest.h"
#include "sys/ProcProfile.h"
#include "game/NibblePair.h"
#include "player/PlayerData.h"
#include "save/LostChildRecord.h"
#include "save/SaveData.h"
#include "save/TownExchangeRecord.h"
#include "ui/HudController.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_0212a120.h"
#include "proto/main/unk_0203c92c.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_02041868.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_020637e4.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020a6388.h"
#include "proto/main/unk_020afeb4.h"
#include "proto/ov048/unk_ov048_02258de0.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_02000b7c.h"
#include "proto/main/unk_02065e88.h"
#include "save/TownCompress.h"
#include "save/SaveManager.h"
#include "save/SaveChecksum.h"
#include "town/TownState.h"
#include "save/SaveRecord4.h"
#include "save/Backup.h"
#include "sys/ClockDateTime.h"
#include "sys/OSThread.h"
#include "gfx/ScreenTransition.h"
#include "player/PlayerId.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_0204cc1c.h"


struct GuestSlotTriple { s32 v[3]; };

static inline BOOL Unk_020a3238_Is2(u8 v) {
    if (v == 2) return TRUE;
    return FALSE;
}

static inline BOOL Unk_020a42c4_IsTwo(u8 v) { return v == 2 ? TRUE : FALSE; }


struct SaveClockOffset {
    u32 minutes;
    u16 seconds;
    u8 pad[2];
};

extern "C" {
extern SaveData gSaveData;
#define gSaveBlancaFace HOST_LABEL(BlancaFaceRecord *, gSaveBlancaFace)
#define data_021e7f8c HOST_LABEL(TownExchangeRecord *, data_021e7f8c)
#define data_021ed304 HOST_LABEL(SaveClockOffset *, data_021ed304)
#define gSaveFooter HOST_LABEL(SaveRecord4 *, gSaveFooter)
extern Backup gBackup;
extern CommManager *gCommManager;
extern u8 gTalkMsgIndexEnd;

void MI_CpuCopy8(const void *src, void *dst, u32 size);
void MI_CpuFill8(void *dst, u32 v, u32 size);
void DC_FlushAll();
u32 MI_CompressLZ(const u8 *src, u32 size, u8 *dst);
void MI_InitUncompContextLZ(void *ctx, u8 *dst, const u32 *src);
s32 MI_ReadUncompLZ8(void *ctx, const void *src, s32 size);
void DGT_Hash1CalcHmac(u8 *digest, const u8 *data, u32 dataLen, const u8 *key, int keyLen);
void OS_CreateThread(OSThread *t, void (*func)(void *), void *arg, void *stack, u32 stackSize, u32 prio);
void OS_WakeupThreadDirect(OSThread *t);
BOOL OS_IsThreadTerminated(OSThread *t);
void OS_KillThread(OSThread *t, void *arg);
void OS_ResetSystem(u32 parameter);

s32 Backup_GetStatus(Backup *g);
void Backup_EndAccess(Backup *g);
s32 Backup_Read(Backup *g, void *dst, u32 size, u32 offset);
s32 Backup_ReadAsync(Backup *g, void *dst, u32 size, u32 offset);
s32 Backup_Write(Backup *g, u32 offset, const void *src, u32 size);
s32 Backup_WriteAsync(Backup *g, u32 offset, const void *src, u32 size);
u16 Save_Sum16(const void *p, u32 n);
u16 Save_CalcChecksum(const void *p, u32 n, u32 m);
void OverlayHandle_Unload(OverlayHandleView *s);
u8 *FriendList_GetEntries(void *list);
void AxBbsNotice_Construct();
void AxBbsNotice_Destruct();
u8 *AxBbsNotice_GetDigest(u8 *p);
BOOL AxBbsNotice_Post(u8 *p);
void *AxMail_Construct(void *p);
void *AxMail_Destruct(void *p);
u8 *AxMail_GetDigest(u8 *p);
BOOL AxMail_Deliver(u8 *p);
s32 ClockOffset_CalcMinutes(void *unused, void *dateTime);
s32 ClockOffset_CalcSeconds(void *unused, void *dateTime);
void Clock_GetDateTime(ClockDateTime *p);
void Clock_Init();
void Clock_Update(u32 x);
u16 *PlayerSession_GetLastPlayDate();
void SaveData_Setup(SaveData *p, u32 idx);
void SaveData_Apply(u8 *p);
void SaveVillagers_DailyUpdate(u8 *self, s32 flag);
void SaveVillagers_UpdateAllRoomInfo(void *self);
BOOL LetterStorage_IsValid(void *p);
void LetterStorage_MarkInterrupted(void *p);
void LetterStorage_MarkValid(void *p);
u16 Math_CountDownU16(u16 *p);
u32 Scene_GetCurrent();
void SceneWarp_SetFadeOut(void *warp, u8 v);
void Town_ClearBorderTrees(void *map);
void Town_OnLoad();
void TownState_ClampDate(void *date);
void VillagerStates_Init();
void VillagerStates_Destroy();
void Weather_RerollRainSlant();
}

extern const s32 sSaveSlotSizes[3];
extern const VecFx32 data_020d0770;
extern const s32 sSaveSlotDataSizes[3];
extern const VecFx32 data_020d0788;
extern const u32 sSaveSlotOffsets[3];

extern "C" SaveManager *SaveManager_Create() {
    return new SaveManager;
}

BOOL SaveManager::onCreate() {
    if (Scene_GetCurrent() == 6) {
        if (TownBlockMap_Get() != 0) {
            ((TownBlockMap *)(TownBlockMap_Get()))->updateAcreIds();
            ((TownBlockMap *)(TownBlockMap_Get()))->bindBg();
            Town_ClearBorderTrees(TownBlockMap_Get());
        }
        HouseRoomMaps_UpdateAll();
        HouseRoomMaps_BindBg();
    }
    data_021ed398 = 0;
    if (gCommManager->isOnline()) {
        if (Scene_GetCurrent() == 0xb || Scene_GetCurrent() == 9) {
            return FALSE;
        }
    }
    gSaveManager = this;
    talk.setOwner(this);
    bufferHeap = gCurrentHeap;
    if (Scene_GetCurrent() == 0x2e || Scene_GetCurrent() == 6 || Scene_GetCurrent() == 9 || Scene_GetCurrent() == 0xb) {
        workBuf = (u8 *)Heap_Alloc(bufferHeap, sizeof(SaveData));
        readBackBuf = (u8 *)Heap_Alloc(bufferHeap, sizeof(SaveData));
        letterStorage = (u8 *)Heap_Alloc(bufferHeap, 0x11df4);
        Save_ReadSlot(2);
        void *r4 = SaveManager_GetLetterStorage();
        s32 r6 = Save_Sum16(r4, 0x11df4);
        if (LetterStorage_IsValid(r4) == 0 || r6 != 0) {
            MI_CpuFill8(r4, 0, 0x11df4);
        }
        LetterStorage_MarkValid(r4);
    }
    if (Scene_GetCurrent() == 9) {
        playerDataCopy = Heap_Alloc(bufferHeap, sizeof(PlayerData));
    }
    if (Scene_GetCurrent() == 0x2e) {
        saveDataCopy = Heap_Alloc(bufferHeap, sizeof(SaveData));
        villagerTransferBackup = Heap_Alloc(bufferHeap, 0x84c);
    }
    if (sSaveManagerRequest == 0x14 || sSaveManagerRequest == 0x15) {
        townCompressBuf = (TownCompressBuffer *)Heap_Alloc(bufferHeap, 0x15fe4);
        townCompressThread = (TownCompressThread *)Heap_Alloc(bufferHeap, sizeof(TownCompressThread));
        townCompressThread->init();
    }
    if (sSaveManagerRequest == 0x14) {
        SaveData *p = (SaveData *)Heap_Alloc(bufferHeap, sizeof(SaveData));
        gTownTransferBuf = p;
        p->footer.clearState();
    }
    return TRUE;
}

BOOL SaveManager::onDelete() {
    if (Scene_GetCurrent() == 6) {
        SaveVillagers_UpdateAllRoomInfo(gSaveData.villagers);
    }
    if (gCommManager->isOnline()) {
        if (Scene_GetCurrent() == 0xb || Scene_GetCurrent() == 9) {
            return TRUE;
        }
    }
    gSaveManager = 0;
    if (Scene_GetCurrent() == 0x2e || Scene_GetCurrent() == 6 || Scene_GetCurrent() == 9 || Scene_GetCurrent() == 0xb) {
        Heap_Free(bufferHeap, workBuf);
        Heap_Free(bufferHeap, readBackBuf);
        Heap_Free(bufferHeap, letterStorage);
    }
    if (Scene_GetCurrent() == 9) {
        Heap_Free(bufferHeap, playerDataCopy);
    }
    if (gTownTransferBuf) {
        Heap_Free(bufferHeap, gTownTransferBuf);
        gTownTransferBuf = 0;
    }
    if (townCompressThread) {
        townCompressThread->kill();
        Heap_Free(bufferHeap, townCompressThread);
        townCompressThread = 0;
    }
    if (townCompressBuf) {
        Heap_Free(bufferHeap, townCompressBuf);
    }
    if (Scene_GetCurrent() == 0x2e) {
        Heap_Free(bufferHeap, saveDataCopy);
        Heap_Free(bufferHeap, villagerTransferBackup);
    }
    return TRUE;
}

BOOL SaveManager::onExecute() {
    if (sSaveManagerStates[act].exec) {
        (this->*sSaveManagerStates[act].exec)();
    }
    return TRUE;
}

void SaveManager::setState(s32 idx) {
    if (sSaveManagerStates[idx].enter) {
        (this->*sSaveManagerStates[idx].enter)();
    }
    act = idx;
}

void SaveManager::enterAct00() {}

void SaveManager::execAct00() {
    s32 m = Scene_GetCurrent();
    if (Unk_020a42c4_IsTwo(gScreenTransition.state) != 0) {
        if (m == 9) {
            s32 t = sSaveManagerRequest;
            if (t == 0x12 || t == 0x1f) {
                setState(*(volatile s32 *)&sSaveManagerRequest);
                sSaveManagerRequest = 0;
            }
        } else if (m == 0xb) {
            if (sSaveManagerRequest == 0x13) {
                setState(sSaveManagerRequest);
                sSaveManagerRequest = 0;
            }
        } else if (m == 6) {
            if ((u32)(sSaveManagerRequest - 3) <= 1) {
                setState(sSaveManagerRequest);
                sSaveManagerRequest = 0;
            }
        } else if (m == 0x2e) {
            setState(sSaveManagerRequest);
            sSaveManagerRequest = 0;
        }
        if (m == 0xc && sSaveManagerRequest == 0x14) {
            setState(sSaveManagerRequest);
            sSaveManagerRequest = 0;
        }
        if (m == 0x2f || m == 0xd) {
            setState(sSaveManagerRequest);
            sSaveManagerRequest = 0;
        }
    }
}

void SaveManager::enterAct01() {
    void *r5 = PlayerData_GetCurrent();
    this->startTalk("sp_etc_sequence2", 1);
    MenuCtrl_ClearClockChangeFlags();
    ((PlayerData *)(r5))->clearFlag(2);
    TownState_ClampDate(&gSaveData.townState);
    actStep = 0;
}

void SaveManager::execAct01() {
    switch (actStep) {
    case 0:
        if (this->func_020a15c8(0) != 0) {
            if (gCommManager->isSlotActive(gCommManager->myAid) != 0) {
                Comm_ResetNetSession();
                if (Wifi_EndSession() != 0) {
                    NetOverlay_Restore();
                }
            }
            actStep = 1;
        }
        break;
    case 1: {
        s32 r = this->verifySlotsStep();
        if (r == 1) {
            actStep = 4;
        } else if (r != 3) {
            actStep = 2;
        }
        break;
    }
    case 2: {
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            actStep = 4;
        } else if (r == 0) {
            actStep = 3;
        }
        break;
    }
    case 3: {
        s32 r = this->saveSlotStep(slotOrder.lo);
        if (r == 1) {
            actStep = 4;
        } else if (r == 0) {
            actStep = 6;
        }
        break;
    }
    case 4:
        this->showSequence2Msg0A();
        actStep = 5;
        break;
    case 5:
        break;
    default:
        this->func_020a15f8();
        setState(0xc);
        break;
    }
}

void SaveManager::enterAct02() {
    void *r5 = PlayerData_GetCurrent();
    this->startTalk("sp_npc_gatekeeper", 0x66);
    MenuCtrl_ClearClockChangeFlags();
    ((PlayerData *)(r5))->clearFlag(2);
    TownState_ClampDate(&gSaveData.townState);
    actStep = 0;
}

void SaveManager::execAct02() {
    switch (actStep) {
    case 0:
        if (this->func_020a15c8(0) != 0) {
            if (gCommManager->isSlotActive(gCommManager->myAid) != 0) {
                Comm_ResetNetSession();
                if (Wifi_EndSession() != 0) {
                    NetOverlay_Restore();
                }
            }
            actStep = 1;
        }
        break;
    case 1: {
        s32 r = this->verifySlotsStep();
        if (r == 1) {
            actStep = 4;
        } else if (r != 3) {
            actStep = 2;
        }
        break;
    }
    case 2: {
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            actStep = 4;
        } else if (r == 0) {
            actStep = 3;
        }
        break;
    }
    case 3: {
        s32 r = this->saveSlotStep(slotOrder.lo);
        if (r == 1) {
            actStep = 4;
        } else if (r == 0) {
            actStep = 6;
        }
        break;
    }
    case 4:
        this->showSequence2Msg0A();
        actStep = 5;
        break;
    case 5:
        break;
    default:
        this->func_020a15f8();
        setState(0xd);
        break;
    }
}

void SaveManager::enterAct03() {
    this->startTalk("sp_etc_sequence1", 0x28);
    PlayerOptions_Commit();
    actStep = 0;
}

void SaveManager::execAct03() {
    switch (actStep) {
    case 0:
        if (this->func_020a15c8(0) != 0) {
            Clock_Init();
            actStep = actStep + 1;
        }
        break;
    case 1:
        SaveVillagers_DailyUpdate(gSaveData.villagers, 0);
        actStep = actStep + 1;
        break;
    case 2:
        SaveData_Setup(&gSaveData, 2);
        actStep = actStep + 1;
        break;
    case 3:
        TownUpdateThread_Create();
        actStep = actStep + 1;
        break;
    case 4:
        SaveData_Apply((u8 *)&gSaveData);
        actStep = actStep + 1;
        break;
    default:
        this->setState(4);
        break;
    }
}

void SaveManager::enterAct04() {
    actStep = 0;
}

void SaveManager::execAct04() {
    switch (actStep) {
    case 0:
        actStep = 1;
        break;
    case 1:
        if (TownUpdateThread_Start() != 0) {
            actStep = 2;
        } else {
            actStep = 3;
        }
        break;
    case 2:
        if (TownUpdateThread_PollDone() != 0) {
            actStep = 3;
        }
        break;
    case 3: {
        s32 r = this->verifySlotsStep();
        if (r == 1) {
            actStep = 6;
        } else if (r != 3) {
            actStep = 4;
        }
        break;
    }
    case 4: {
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            actStep = 6;
        } else if (r == 0) {
            actStep = 5;
        }
        break;
    }
    case 5: {
        s32 r = this->saveSlotStep(slotOrder.lo);
        if (r == 1) {
            actStep = 6;
        } else if (r == 0) {
            actStep = 8;
        }
        break;
    }
    case 6:
        this->showSequence2Msg0A();
        actStep = 7;
        break;
    case 7:
        break;
    default:
        this->func_020a15f8();
        this->setState(0x10);
        break;
    }
}

void SaveManager::enterAct05() {
    this->startTalk("sp_etc_sequence1", 0xc);
    actStep = 0;
}

void SaveManager::execAct05() {
    switch (actStep) {
    case 0:
        if (this->func_020a15c8(0) != 0) {
            actStep = 1;
        }
        break;
    case 1: {
        s32 r = Save_InvalidateAll();
        if (r == 1) {
            actStep = 5;
        } else if (r == 0) {
            actStep = 2;
        }
        break;
    }
    case 2: {
        s32 r = this->eraseSlotStep(0);
        if (r == 1) {
            actStep = 5;
        } else if (r == 0) {
            actStep = 3;
        }
        break;
    }
    case 3: {
        s32 r = this->eraseSlotStep(1);
        if (r == 1) {
            actStep = 5;
        } else if (r == 0) {
            actStep = 4;
        }
        break;
    }
    case 4: {
        s32 r = this->eraseSlotStep(2);
        if (r == 1) {
            actStep = 5;
        } else if (r == 0) {
            actStep = 7;
        }
        break;
    }
    case 5:
        this->showSequence2Msg0A();
        actStep = 6;
        break;
    case 6:
        break;
    default:
        this->func_020a15f8();
        this->setState(0xc);
        break;
    }
}

void SaveManager::enterAct06() {
    TalkWindowState *o = TalkWindow_Get(0);
    MsgString9B name;
    u8 *h = PlayerData_GetResident(gSaveData.players, sEraseResidentSlot);
    ((PlayerId *)(((PlayerData *)(h))->getPlayerId()))->getNameString(&name);
    o->setSlot(0, &name);
    ((PlayerData *)(h))->reset();
    gSaveData.resetPlayer(sEraseResidentSlot);
    this->startTalk("sp_etc_sequence1", 7);
    if (PlayerDataArray_CountUsed(gSaveData.players) == 0) {
        gSaveData.townState.unk_22 = 0;
    }
    actStep = 0;
}

void SaveManager::execAct06() {
    switch (actStep) {
    case 0:
        if (this->func_020a15c8(0) != 0) {
            actStep = 1;
        }
        break;
    case 1: {
        s32 r = this->verifySlotsStep();
        if (r == 1) {
            actStep = 5;
        } else if (r != 3) {
            actStep = 2;
        }
        break;
    }
    case 2: {
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            actStep = 5;
        } else if (r == 0) {
            actStep = 3;
        }
        break;
    }
    case 3: {
        s32 r = this->saveSlotStep(slotOrder.lo);
        if (r == 1) {
            actStep = 5;
        } else if (r == 0) {
            actStep = 4;
        }
        break;
    }
    case 4: {
        s32 r = this->saveSlotStep(2);
        if (r == 1) {
            actStep = 5;
        } else if (r == 0) {
            actStep = 7;
        }
        break;
    }
    case 5:
        this->showSequence2Msg0A();
        actStep = 6;
        break;
    case 6:
        break;
    default:
        this->func_020a15f8();
        this->setState(0xc);
        break;
    }
}

void SaveManager::enterAct07() {
    this->startTalk("sp_etc_sequence3", 0x27);
    actStep = 0;
}

void SaveManager::execAct07() {
    switch (actStep) {
    case 0:
        if (this->func_020a15c8(0) != 0) {
            actStep = 1;
        }
        break;
    case 1: {
        s32 r = this->verifySlotsStep();
        if (r == 1) {
            actStep = 4;
        } else if (r != 3) {
            actStep = 2;
        }
        break;
    }
    case 2: {
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            actStep = 4;
        } else if (r == 0) {
            actStep = 3;
        }
        break;
    }
    case 3: {
        s32 r = this->saveSlotStep(slotOrder.lo);
        if (r == 1) {
            actStep = 4;
        } else if (r == 0) {
            actStep = 6;
        }
        break;
    }
    case 4:
        this->showSequence2Msg0A();
        actStep = 5;
        break;
    case 5:
        break;
    default:
        this->func_020a15f8();
        this->setState(0xf);
        break;
    }
}

void SaveManager::enterAct08() {}

void SaveManager::execAct08() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        SceneWarp_RequestExit(Scene_GetWarpRequest(), 1);
        this->setState(0);
    }
}

void SaveManager::enterAct09() {}

void SaveManager::execAct09() {
    VecFx32 v;
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        v.x = data_020d0770.x;
        v.y = data_020d0770.y;
        v.z = data_020d0770.z;
        SceneWarp_RequestAt(Scene_GetWarpRequest(), 0xd, &v, 0x800000, 0, 3, 2);
        this->setState(0);
    }
}

void SaveManager::enterAct0A() {}

void SaveManager::execAct0A() {
    VecFx32 v;
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        v.x = data_020d0788.x;
        v.y = data_020d0788.y;
        v.z = data_020d0788.z;
        SceneWarp_RequestAt(Scene_GetWarpRequest(), 0xe, &v, 0x800000, 0, 3, 2);
        this->setState(0);
    }
}

void SaveManager::enterAct0B() {}

void SaveManager::execAct0B() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2f, 3, 2);
        this->setState(0);
    }
}

void SaveManager::enterAct0C() {}

void SaveManager::execAct0C() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        s32 r = Save_LoadSync();
        if (r == 4 || r == 1) {
            gSaveData.reset();
            GuestPlayers_ResetAll();
            VillagerStates_Init();
            SaveData_Setup(&gSaveData, 3);
        } else {
            SaveData_Setup(&gSaveData, 4);
        }
        SaveData_Apply((u8 *)&gSaveData);
        VillagerStates_Destroy();
        SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2c, 3, 2);
        this->setState(0);
    }
}

void SaveManager::enterAct0D() {}

void SaveManager::execAct0D() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        Scene_Request(2, 3, 0, 0);
        this->setState(0);
    }
}

void SaveManager::enterAct0E() {}

void SaveManager::execAct0E() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (Unk_020a3238_Is2(gScreenTransition.state)) {
        if (o->state == 0) {
            o->detachRequest();
            if (gSaveData.testFlag(0x12) != 0) {
                GameStart_SetMode3();
            } else {
                GameStart_SetMode4();
            }
            GameStart_SetupSave();
            SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2d, 3, 0);
            this->setState(0);
        }
    }
}

void SaveManager::enterAct0F() {}

void SaveManager::execAct0F() {
    VecFx32 v;
    TalkWindowState *o = TalkWindow_Get(0);
    if (Unk_020a3238_Is2(gScreenTransition.state)) {
        if (o->state == 0) {
            o->detachRequest();
            Town_FindTownHallFront(TownBlockMap_Get(), &v, NULL, NULL);
            SceneWarp_RequestAt(Scene_GetWarpRequest(), 0, &v, 0x400000, -0x8000, 3, 2);
            this->setState(0);
        }
    }
}

void SaveManager::enterAct10() {}

void SaveManager::execAct10() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        if (Scene_GetCurrent() == 6) {
            SceneWarp_RequestExit(Scene_GetWarpRequest(), 2);
        } else {
            SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
        }
        this->setState(0);
    }
}

void SaveManager::enterAct11() {}

void SaveManager::execAct11() {
    TalkWindowState *o = TalkWindow_Get(0);
    if (o->state == 0) {
        o->detachRequest();
        SceneWarp_RequestExit(Scene_GetWarpRequest(), 2);
        this->setState(0);
    }
}

void SaveManager::enterAct12() {
    actStep = 0;
}

void SaveManager::execAct12() {
    switch (actStep) {
    case 0: {
        s32 r = this->verifySlotsStep();
        if (r == 1) {
            actStep = 3;
        } else if (r != 3) {
            actStep = 1;
        }
        break;
    }
    case 1: {
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            actStep = 3;
        } else if (r == 0) {
            actStep = 2;
        }
        break;
    }
    case 2: {
        s32 r = this->saveSlotStep(2);
        if (r == 1) {
            actStep = 3;
        } else if (r == 0) {
            actStep = 4;
        }
        break;
    }
    case 3:
        break;
    default:
        this->setState(0);
        break;
    }
}

void SaveManager::enterAct13() {
    (PlayerData_GetCurrent())->clearFlag(2);
    actStep = 0;
}

void SaveManager::execAct13() {
    switch (actStep) {
    case 0: {
        s32 r = this->verifySlotsStep();
        if (r == 1) {
            actStep = 3;
        } else if (r != 3) {
            actStep = 1;
        }
        break;
    }
    case 1: {
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            actStep = 3;
        } else if (r == 0) {
            actStep = 2;
        }
        break;
    }
    case 2: {
        s32 r = this->saveSlotStep(2);
        if (r == 1) {
            actStep = 3;
        } else if (r == 0) {
            actStep = 4;
        }
        break;
    }
    case 3:
        break;
    default:
        this->setState(0);
        break;
    }
}

void SaveManager::enterAct14() {
    SaveManager_StartGatekeeperTalk(this, 1);
    Constellation_PrepareExchange();
}

void SaveManager::execAct14() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (CommCtrl_SendAct07()) {
            actStep = 1;
        }
        break;
    case 1:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (hostMemberMask != 0) {
            sendChunk = 0;
            actStep = 2;
        }
        break;
    case 2:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (CommSend_VillagerTransfer(&sendChunk)) {
            sendChunk = 0;
            actStep = 3;
        }
        break;
    case 3:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (townCompressThread->isDone()) {
            BOOL r6 = TRUE;
            s32 r5 = 3;
            for (; r5 >= 0; r5--) {
                if (r5 != 0) {
                    u32 m = (u16)(1 << r5);
                    if (m == (m & hostMemberMask)) {
                        if (PlayerData_IsUsedByIndex(r5 + 3) == 0) {
                            r6 = FALSE;
                            break;
                        }
                    }
                }
            }
            if (!r6) {
                actStep = 4;
            }
        }
        break;
    case 4:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (SaveManager_IsGatePassed()) {
            ProcBase_RequestDelete((ProcBase *)PlayerActor_GetActor(4));
            actStep = 5;
        }
        break;
    case 5:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (PlayerActor_GetActor(4) == 0) {
            if (CommSend_JoinReady()) {
                actStep = 6;
            }
        }
        break;
    case 6:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (dateTimeReceived != 0) {
            u32 r7 = Net_GetMyAid();
            CommManager *r5 = gCommManager;
            r5->myAid = r7;
            void *r6 = PlayerData_Get(PlayerSession_GetDataIndex(r5->localSlot));
            MI_CpuCopy8(r6, PlayerData_Get(r5->myAid + 3), sizeof(PlayerData));
            sSessionResidentIndex = PlayerSession_GetDataIndex(r5->localSlot);
            r5->localSlot = r7;
            u32 cnt = 0;
            u32 zero = 0;
            s32 i = 3;
            for (; i >= 0; i--) {
                if (hostMemberMask & (1 << i)) {
                    r5->setSlotActive(i, 1);
                    cnt = (u8)(cnt + 1);
                } else {
                    r5->setSlotActive(i, zero);
                }
            }
            r5->setMemberCount(cnt);
            NetArea_SetSlotStatus(r7, 0xc, 1, 0, 7);
            PlayerSession_SetDataIndex(0, hostDataIndex);
            PlayerSession_SetDataIndex(r7, r7 + 3);
            MI_CpuCopy8(gTownTransferBuf, &gSaveData, sizeof(SaveData));
            u8 buf1[8];
            u8 buf2[8];
            MI_CpuCopy8(&hostDateTime, buf1, 8);
            SaveClockOffset *const r7p = &data_021ed304;
            u32 r6b = ClockOffset_CalcMinutes(r7p, buf1);
            MI_CpuCopy8(&hostDateTime, buf2, 8);
            u32 h = ClockOffset_CalcSeconds(r7p, buf2);
            r7p->minutes = r6b;
            r7p->seconds = h;
            if (TownBlockMap_Get()) {
                TownBlockMap_Get()->updateAcreIds();
                TownBlockMap_Get()->bindBg();
                Town_ClearBorderTrees(TownBlockMap_Get());
            }
            HouseRoomMaps_UpdateAll();
            HouseRoomMaps_BindBg();
            Comm_ResetPeerState(4);
            Melody_SetPacked((u32 *)&gSaveData.townTune);
            Weather_RerollRainSlant();
            sessionJoined = 1;
            r5->setMode(1);
            actStep = 7;
        }
        break;
    case 7:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (CommSend_JoinDone(Comm_GetRemoteMask())) {
            actStep = 8;
        }
        break;
    case 8:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend()) {
                gCommManager->setMode(2);
                if (SpNpcCopper_CheckKatieEscort()) {
                    SceneWarp_RequestExit(Scene_GetWarpRequest(), 2);
                    SceneWarp_SetFadeOut(Scene_GetWarpRequest(), 3);
                } else {
                    SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
                    SceneWarp_SetFadeOut(Scene_GetWarpRequest(), 3);
                }
                data_021c3cb8 = 1;
                actStep = 9;
            }
        }
        break;
    }
}

void SaveManager::enterAct15() {
    SaveManager_StartGatekeeperTalk(this, 1);
    if (gCommManager->memberCount == 1) {
        LetterDelivery_DeliverOutgoing();
        LetterDelivery_DeliverOutgoing();
        Constellation_PrepareExchange();
        JoinHistory_Clear();
    }
}

void SaveManager::execAct15() {
    switch (actStep) {
    case 0: {
        u32 r5 = Comm_GetRemoteMask();
        r5 |= 1 << NetSession_GetLastSyncSlot();
        if (Comm_IsConnectionLost(r5)) {
            Comm_SetLostFlag();
        } else if (NetSession_GetCtrl07Received()) {
            actStep = 1;
        }
        break;
    }
    case 1:
    case 2: {
        u32 r5 = Comm_GetRemoteMask();
        r5 |= 1 << NetSession_GetLastSyncSlot();
        if (Comm_IsConnectionLost(r5)) {
            Comm_SetLostFlag();
        } else {
            runGatherPeersInScene(&actStep, 1, 0xd, 0x2f);
            if (actStep > 2) {
                NetArea_SetSlotStatus(sJoiningAid, 0xc, 1, 0, 7);
                CommManager *g = gCommManager;
                g->setMemberCount((u8)(g->memberCount + 1));
                g->setSlotActive(sJoiningAid, 1);
                Comm_ResetPeerState(sJoiningAid);
            }
        }
        break;
    }
    case 3:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (CommSend_MemberInfo((u16)(1 << sJoiningAid))) {
            actStep = 4;
        }
        break;
    case 4:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (CommBlock_BuildPacket(sJoiningAid)) {
            actStep = 5;
        }
        break;
    case 5:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (CommSend_BuiltPacket((u16)(1 << sJoiningAid))) {
            sendChunk = 0;
            actStep = 6;
        }
        break;
    case 6:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (CommSend_SyncVarChunk(&sendChunk, (u16)(1 << sJoiningAid))) {
            actStep = 7;
        }
        break;
    case 7:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (CommSend_SlotStatusAll(sJoiningAid)) {
            townCompressThread->start(1);
            sendChunk = 0;
            actStep = 8;
        }
        break;
    case 8:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (townCompressThread->isDone()) {
            DC_FlushAll();
            if (CommSend_TownChunk(&sendChunk, (u16)(1 << sJoiningAid))) {
                actStep = 9;
            }
        }
        break;
    case 9:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (joinReady != 0) {
            if (CommSend_DateTime((u16)(1 << sJoiningAid))) {
                actStep = 10;
            }
        }
        break;
    case 10:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend()) {
                if (joinDone != 0) {
                    gCommManager->setMode(2);
                    sessionJoined = 1;
                    JoinHistory_Push(sJoiningAid);
                    actStep = 11;
                }
            }
        }
        break;
    }
}

void SaveManager::enterAct16() {
    SaveManager_StartGatekeeperTalk(this, 1);
}

void SaveManager::execAct16() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (gCommManager->getMode() == 1) {
            NetArea_SetSlotStatus(sJoiningAid, 0xc, 1, 0, 7);
            CommManager *g = gCommManager;
            g->setMemberCount((u8)(g->memberCount + 1));
            g->setSlotActive(sJoiningAid, 1);
            Comm_ResetPeerState(sJoiningAid);
            actStep = 1;
        }
        break;
    case 1:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (CommSend_PlayerData(&sendChunk, (u16)(1 << sJoiningAid))) {
            actStep = 2;
        }
        break;
    case 2:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend()) {
                if (joinDone != 0) {
                    gCommManager->setMode(2);
                    sessionJoined = 1;
                    actStep = 3;
                }
            }
        }
        break;
    }
}

void SaveManager::enterAct17() {
    SaveManager_StartGatekeeperTalk(this, 0);
    ((PlayerData *)(PlayerData_GetCurrent()))->setFlag(2);
    NetSession_SetLastSyncSlot(gCommManager->myAid);
}

void SaveManager::execAct17() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (func_020a15c8(0)) {
            memberMask = Comm_GetMemberMask();
            actStep = 1;
        }
        break;
    case 1:
    case 2:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            runSendAct10(&actStep, 1);
        }
        break;
    case 3:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (isTransferReceived(gCommManager->myAid)) {
            backupVillagerTransfer();
            actStep = 4;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        runSyncedSaveClient(&actStep, 4, 0xe, 0x14, 1, 0, 1);
        break;
    case 12:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            BOOL r6 = TRUE;
            s32 r5 = 3;
            CommManager *g = gCommManager;
            for (; r5 >= 0; r5--) {
                if (g->isSlotActive(r5)) {
                    if (!g->isMyAid(r5)) {
                        if (g->getAckCount(r5)) {
                            r6 = FALSE;
                            break;
                        }
                    }
                }
            }
            if (r6) {
                if (CommCtrl_SendAct11()) {
                    actStep = 0xd;
                }
            }
        }
        break;
    case 13:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (ctrlAct12 != 0) {
            NetSession_ReturnToSolo(this, sSessionResidentIndex, 0);
            sSessionResidentIndex = 7;
            NetOverlay_Restore();
            Weather_RerollRainSlant();
            actStep = 0x19;
        }
        break;
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
        SaveManager_RunSessionEnd(this, &actStep, 0xe, 0x14, 1, 1);
        break;
    default:
        func_020a15f8();
        setState(8);
        break;
    }
}

void SaveManager::enterAct18() {
    SaveManager_StartGatekeeperTalk(this, 0);
}

void SaveManager::execAct18() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (func_020a15c8(0)) {
            memberMask = Comm_GetMemberMask();
            VillagerTransfer_PlanSwap(this);
            LostChild_ResetAndPairLast(this);
            actStep = 1;
        }
        break;
    case 1:
    case 2:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            runGatherPeersInScene(&actStep, 1, 0x2e, 0x2e);
        }
        break;
    case 3:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (allPeersSentAct10()) {
            actStep = 4;
        }
        break;
    case 4:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (VillagerTransfer_SendReplies(this)) {
            s32 r5 = NetSession_GetLastSyncSlot();
            u32 r7 = getTransferDest(r5);
            void *r6 = TownExchange_GetForAid(r5);
            MI_CpuCopy8(r6, TownExchange_GetForAid(r7), 0x84c);
            TownExchange_Clear(r6);
            backupVillagerTransfer();
            JoinHistory_Remove((u8)r5);
            actStep = 5;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11: {
        u32 t = Comm_GetRemoteMask();
        SaveManager_RunSyncedSaveHost(this, &actStep, 1, 5, 0xf, 0x15, 4, 1, t);
        break;
    }
    case 12:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            BOOL r6 = TRUE;
            s32 r5 = 3;
            CommManager *g = gCommManager;
            for (; r5 >= 0; r5--) {
                if (g->isSlotActive(r5)) {
                    if (!g->isMyAid(r5)) {
                        if (ctrlAct11[r5] == 0) {
                            r6 = FALSE;
                            break;
                        }
                    }
                }
            }
            if (r6) {
                if (g->getAckCount(NetSession_GetLastSyncSlot())) {
                    r6 = FALSE;
                }
            }
            if (r6) {
                if (CommCtrl_SendAct12((u16)(1 << NetSession_GetLastSyncSlot()))) {
                    actStep = 0xd;
                }
            }
        }
        break;
    case 13: {
        u32 r5 = Comm_GetRemoteMask();
        r5 ^= (u16)(1 << NetSession_GetLastSyncSlot());
        if (Comm_IsConnectionLost(r5)) {
            Comm_SetLostFlag();
        } else {
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend() || Net_GetMemberCount() <= 1) {
                Comm_RemoveMember(NetSession_GetLastSyncSlot());
                CommManager *g = gCommManager;
                g->setMode(2);
                if (g->isOnline()) {
                    u8 b = NetSession_GetLastSyncSlot();
                    g = gCommManager;
                    g->beginRecord();
                    g->writeRecord(&b, 1);
                    g->endRecord(5, 5);
                }
                actStep = 0xe;
            }
        }
        break;
    }
    case 14:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            BOOL r6 = TRUE;
            s32 r5 = 3;
            CommManager *g = gCommManager;
            for (; r5 >= 0; r5--) {
                if (g->isSlotActive(r5)) {
                    if (!g->isMyAid(r5)) {
                        if (recvAct06[r5] == 0) {
                            r6 = FALSE;
                            break;
                        }
                    }
                }
            }
            if (r6) {
                Weather_RerollRainSlant();
                g = gCommManager;
                g->beginRecord();
                g->endRecord(7, 5);
                if (g->memberCount == 1) {
                    Town_OnLoad();
                }
                actStep = 0x1a;
            }
        }
        break;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
        SaveManager_RunSessionEnd(this, &actStep, 0xf, 0x15, Comm_GetRemoteMask(), 1);
        break;
    default:
        func_020a15f8();
        setState(10);
        break;
    }
}

void SaveManager::enterAct19() {
    SaveManager_StartGatekeeperTalk(this, 0);
}

void SaveManager::execAct19() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (this->func_020a15c8(0)) {
            memberMask = Comm_GetMemberMask();
            actStep = 1;
        }
        break;
    case 1:
    case 2:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            this->runSendAct10(&actStep, 1);
        }
        break;
    case 3:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (this->isTransferReceived(gCommManager->myAid)) {
            this->backupVillagerTransfer();
            actStep = 4;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        this->runSyncedSaveClient(&actStep, 4, 0xf, 0x15, 1, 1, 1);
        break;
    case 12:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            BOOL r5 = TRUE;
            if (gCommManager->getAckCount(NetSession_GetLastSyncSlot())) {
                r5 = FALSE;
            }
            if (r5) {
                if (CommCtrl_SendAct11()) {
                    actStep = 0xd;
                }
            }
        }
        break;
    case 13:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend()) {
                u32 t = Comm_GetMemberMask();
                if (memberMask != t) {
                    CommManager *r5;
                    NetSession_RemoveSlot(NetSession_GetLastSyncSlot());
                    r5 = gCommManager;
                    r5->setMode(2);
                    r5->beginRecord();
                    r5->endRecord(6, 0);
                    actStep = 0xe;
                }
            }
        }
        break;
    case 14:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (recvAct07) {
            Weather_RerollRainSlant();
            actStep = 0x1a;
        }
        break;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
        SaveManager_RunSessionEnd(this, &actStep, 0xf, 0x15, 1, 1);
        break;
    default:
        this->func_020a15f8();
        this->setState(0xa);
        break;
    }
}

void SaveManager::enterAct1A() {
    SaveManager_StartSequence2Talk(this);
}

void SaveManager::execAct1A() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (this->func_020a15c8(0)) {
            if (SaveManager_IsEndSessionSave()) {
                VillagerTransfer_PlanRotate(this);
                LostChild_ResetAndPairAll(this);
            }
            actStep = 1;
        }
        break;
    case 1:
    case 2:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            this->runGatherPeersInScene(&actStep, 1, 0x2e, 0x2e);
        }
        break;
    case 3:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (this->allPeersSentAct10()) {
            actStep = 4;
        }
        break;
    case 4:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else if (SaveManager_IsEndSessionSave()) {
            if (VillagerTransfer_SendReplies(this)) {
                s32 r5 = this->getTransferDest(0);
                if (r5 < 4) {
                    void *dst = TownExchange_GetForAid(0);
                    void *src = TownExchange_GetForAid(r5);
                    MI_CpuCopy8(src, dst, 0x84c);
                } else {
                    TownExchange_Clear(TownExchange_GetForAid(0));
                }
                for (r5 = 2; r5 >= 0; r5--) {
                    TownExchange_Clear(TownExchange_GetForAid(r5 + 1));
                }
                this->backupVillagerTransfer();
                actStep = 5;
            }
        } else {
            actStep = 5;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11: {
        BOOL r5;
        if (SaveManager_IsEndSessionSave()) r5 = TRUE; else r5 = FALSE;
        SaveManager_RunSyncedSaveHost(this, &actStep, 1, 5, 0x10, 0x16, 4, r5, Comm_GetRemoteMask());
        break;
    }
    case 12:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend()) {
                if (!SaveManager_IsEndSessionSave()) {
                    gCommManager->setMode(2);
                    actStep = 0xe;
                } else {
                    actStep = 0xd;
                }
            }
        }
        break;
    case 14:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            CommManager *r5 = gCommManager;
            r5->beginRecord();
            r5->endRecord(7, 5);
            actStep = 0x1b;
        }
        break;
    case 13:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            BOOL r6 = TRUE;
            s32 r5 = 3;
            CommManager *r7 = gCommManager;
            for (; r5 >= 0; r5--) {
                if (r7->isSlotActive(r5)) {
                    if (!r7->isMyAid(r5)) {
                        if (!ctrlAct11[r5]) {
                            r6 = FALSE;
                            break;
                        }
                    }
                }
            }
            if (r6) {
                for (r5 = 3; r5 >= 0; r5--) {
                    if (r7->isSlotActive(r5)) {
                        if (!r7->isMyAid(r5)) {
                            if (r7->getAckCount(r5)) {
                                r6 = FALSE;
                                break;
                            }
                        }
                    }
                }
            }
            if (r6) {
                if (CommCtrl_SendAct12(Comm_GetRemoteMask())) {
                    actStep = 0xf;
                }
            }
        }
        break;
    case 15:
        if (Comm_IsConnectionLost(Comm_GetRemoteMask())) {
            Comm_SetLostFlag();
        } else {
            BOOL r6 = TRUE;
            s32 r5;
            CommManager *r7;
            Comm_EnterCritical();
            r5 = 3;
            r7 = gCommManager;
            for (; r5 >= 0; r5--) {
                if (r7->isSlotActive(r5)) {
                    if (!r7->isMyAid(r5)) {
                        if (!recvAct06[r5]) {
                            r6 = FALSE;
                            break;
                        }
                    }
                }
            }
            Comm_LeaveCritical();
            if (r6) {
                NetSession_ReturnToSolo(this, 7, 1);
                NetOverlay_Restore();
                actStep = 0x1b;
            }
        }
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
        SaveManager_RunSessionEnd(this, &actStep, 0x10, 0x16, Comm_GetRemoteMask(), 1);
        break;
    default: {
        u8 b;
        this->func_020a15f8();
        if (SaveManager_IsEndSessionSave()) {
            b = 6;
            TalkWindow_Get(0)->setNextMessage(&b, (u8 *)"sp_etc_sequence2");
        }
        this->setState(8);
        break;
    }
    }
}

void SaveManager::enterAct1B() {
    SaveManager_StartSequence2Talk(this);
}

void SaveManager::execAct1B() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (this->func_020a15c8(0)) {
            actStep = 1;
        }
        break;
    case 1:
    case 2:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            this->runSendAct10(&actStep, 1);
        }
        break;
    case 3:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (SaveManager_IsEndSessionSave()) {
            if (this->isTransferReceived(gCommManager->myAid)) {
                this->backupVillagerTransfer();
                actStep = 4;
            }
        } else {
            actStep = 4;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11: {
        BOOL a, b;
        if (SaveManager_IsEndSessionSave()) a = FALSE; else a = TRUE;
        if (SaveManager_IsEndSessionSave()) b = TRUE; else b = FALSE;
        this->runSyncedSaveClient(&actStep, 4, 0x11, 0x17, b, a, 1);
        break;
    }
    case 12:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend()) {
                if (!SaveManager_IsEndSessionSave()) {
                    actStep = 0xd;
                } else {
                    actStep = 0xe;
                }
            }
        }
        break;
    case 13:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (recvAct07) {
            gCommManager->setMode(2);
            actStep = 0x1c;
        }
        break;
    case 14:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            BOOL r6 = TRUE;
            s32 r5 = 3;
            CommManager *g = gCommManager;
            for (; r5 >= 0; r5--) {
                if (g->isSlotActive(r5)) {
                    if (!g->isMyAid(r5)) {
                        if (g->getAckCount(r5)) {
                            r6 = FALSE;
                            break;
                        }
                    }
                }
            }
            if (r6) {
                if (CommCtrl_SendAct11()) {
                    actStep = 0xf;
                }
            }
        }
        break;
    case 15:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (ctrlAct12) {
            if (CommCtrl_SendAct13()) {
                gCommManager->setErrorMode(2);
                actStep = 0x10;
            }
        }
        break;
    case 16:
        NetOverlay_AssertAny();
        if (!Net_PollConnected()) {
            NetSession_ReturnToSolo(this, sSessionResidentIndex, 0);
            NetOverlay_Restore();
            sSessionResidentIndex = 7;
            actStep = 0x1c;
        }
        break;
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
        SaveManager_RunSessionEnd(this, &actStep, 0x11, 0x17, 1, 1);
        break;
    default: {
        u8 b;
        this->func_020a15f8();
        if (SaveManager_IsEndSessionSave()) {
            b = 6;
            TalkWindow_Get(0)->setNextMessage(&b, (u8 *)"sp_etc_sequence2");
            this->setState(0x11);
        } else {
            this->setState(8);
        }
        break;
    }
    }
}

void SaveManager::enterAct1C() {
    this->startTalk("sp_etc_sequence1", 0x23);
}

void SaveManager::execAct1C() {
    if (this->func_020a15c8(1)) {
        NetOverlay_LoadWireless();
        this->setState(0x1d);
    }
}

void SaveManager::enterAct1D() {
    u8 buf[16];
    hostWaitTimer = 0x258;
    Comm_Start(1, 2, 0);
    Comm_SetRecvBuffersAsHost();
    MI_CpuCopy8(TownId_GetName((u16 *)gSaveData.townId), buf, 8);
    buf[9] = 1;
    buf[8] = 0;
    if (gSaveData.isValid() == 0) {
        buf[8] = 1;
    }
    NetOverlay_AssertWireless();
    Net_SetLocalGameInfo(buf, 10);
    freePlayerSlot = PlayerDataArray_FindUnused(gSaveData.players);
}

void SaveManager::execAct1D() {
    u8 b[2];
    s32 n = SaveManager_GetCtrlAct14Aid();
    if (n > 0 && n < 4) {
        TalkWindowState *p = TalkWindow_Get(0);
        p->hideBusyIcon();
        p->unlockAdvance();
        b[0] = 0x26;
        p->setNextMessage(&b[0], (u8 *)"sp_etc_sequence1");
        this->setState(0);
    } else {
        BOOL ok = FALSE;
        if (Net_GetMemberCount() == 2) {
            hostWaitTimer = ok;
            return;
        }
        if (Net_GetMemberCount() == 1) {
            if (Math_CountDownU16(&hostWaitTimer) == 0) {
                ok = TRUE;
            } else {
                Comm_SendEmpty();
            }
        } else {
            ok = TRUE;
        }
        if (ok) {
            if (Wifi_EndSession()) {
                NetOverlay_Restore();
            }
            TalkWindowState *p = TalkWindow_Get(0);
            b[1] = 0x25;
            p->setNextMessage(&b[1], (u8 *)"sp_etc_sequence1");
            p->hideBusyIcon();
            p->unlockAdvance();
            this->setState(0xc);
        }
    }
}

void SaveManager::enterAct1E() {
    actStep = 0;
    if (gSaveData.isValid() == 0) {
        noSaveData = 1;
    } else {
        noSaveData = 0;
    }
}

void SaveManager::execAct1E() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(-1)) {
            Comm_SetLostFlag();
        } else if (func_020a15c8(0)) {
            actStep = 1;
        }
        break;
    case 1:
        if (Comm_IsConnectionLost(-1)) {
            Comm_SetLostFlag();
        } else {
            s32 r = SaveManager_GetCtrlAct14Aid();
            if (r > 0) {
                if (r < 4) {
                    actStep = 2;
                }
            }
        }
        break;
    case 2:
        if (Comm_IsConnectionLost(-1)) {
            Comm_SetLostFlag();
        } else if (ctrlAct17 != 0) {
            if (noSaveData == 0) {
                SaveData_Setup(&gSaveData, 5);
                SaveData_Apply((u8 *)&gSaveData);
            } else {
                gSaveData.setFlag(0x12);
            }
            PlayerOptions_Commit();
            actStep = 3;
        }
        break;
    case 3:
        if (Comm_IsConnectionLost(-1)) {
            Comm_SetLostFlag();
        } else {
            s32 r = this->saveSlotStep(2);
            if (r == 1) {
                actStep = 0xb;
            } else if (r == 0) {
                actStep = 4;
            }
        }
        break;
    case 4:
        if (Comm_IsConnectionLost(-1)) {
            Comm_SetLostFlag();
        } else {
            s32 r = verifySlotsStep();
            if (r == 1) {
                actStep = 0xb;
            } else if (r != 3) {
                gSaveFooter.markInterrupted();
                actStep = 5;
            }
        }
        break;
    case 5:
        if (Comm_IsConnectionLost(-1)) {
            Comm_SetLostFlag();
        } else {
            s32 r = this->saveSlotStep(slotOrder.hi);
            if (r == 1) {
                actStep = 0xb;
            } else if (r == 0) {
                actStep = 6;
            }
        }
        break;
    case 6:
        if (Comm_IsConnectionLost(-1)) {
            Comm_SetLostFlag();
        } else {
            u32 t = ctrlAct0E[SaveManager_GetCtrlAct14Aid()];
            if (t == 1) {
                gSaveFooter.setStateValidAlt();
                ctrlAct0E[SaveManager_GetCtrlAct14Aid()] = 0;
                gCommManager->setErrorMode(2);
                actStep = 7;
            } else if (t == 2) {
                actStep = 0x11;
            }
        }
        break;
    case 7: {
        Comm_IsConnectionLost(-1);
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            gCommManager->setErrorMode(0);
            actStep = 0xb;
        } else if (r == 0) {
            actStep = 8;
        }
        break;
    }
    case 8:
        if (Comm_IsConnectionLost(-1)) {
            gSaveFooter.markInterrupted();
            actStep = 0xa;
        } else {
            s32 i = SaveManager_GetCtrlAct14Aid();
            if (CommCtrl_SendAct0E(1, (u16)(1 << i))) {
                gCommManager->setErrorMode(0);
                actStep = 9;
            }
        }
        break;
    case 9: {
        u32 m = Net_GetConnectedMask();
        if ((m & (1 << SaveManager_GetCtrlAct14Aid())) == 0) {
            if (Wifi_EndSession()) {
                NetOverlay_Restore();
            }
            actStep = 0x16;
        }
        break;
    }
    case 10: {
        Comm_IsConnectionLost(-1);
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            gCommManager->setErrorMode(0);
            actStep = 0xb;
        } else if (r == 0) {
            gCommManager->setErrorMode(0);
            actStep = 0x11;
        }
        break;
    }
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21: {
        s32 i = SaveManager_GetCtrlAct14Aid();
        SaveManager_RunSessionEnd(this, &actStep, 0xb, 0x11, (u16)(1 << i), 1);
        break;
    }
    default:
        func_020a15f8();
        this->setState(0xe);
        break;
    }
}

void SaveManager::enterAct1F() {
    ((PlayerData *)(PlayerData_GetCurrent()))->clearFlag(2);
    Comm_PrepareJoin(Net_GetMyAid());
    actStep = 0;
}

void SaveManager::execAct1F() {
    switch (actStep) {
    case 0:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (CommCtrl_SendAct14()) {
            actStep = 1;
        }
        break;
    case 1:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (CommSend_PlayerDataToHost(&sendChunk)) {
            sendChunk = 0;
            actStep = 2;
        }
        break;
    case 2:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (CommSend_LetterStorageToHost(&sendChunk)) {
            sendChunk = 0;
            actStep = 3;
        }
        break;
    case 3:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if (CommCtrl_SendAct17()) {
            actStep = 4;
        }
        break;
    case 4:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else if ((NetOverlay_AssertAny(), Net_IsReadyToSend())) {
            ((HudWallet *)Hud_GetWallet())->freezeValue();
            MI_CpuCopy8(PlayerData_GetCurrent(), playerDataCopy, sizeof(PlayerData));
            ((PlayerData *)(PlayerData_GetCurrent()))->reset();
            gSaveData.resetPlayer(PlayerData_GetCurrentIndex());
            actStep = 5;
        }
        break;
    case 5:
        if (Comm_IsConnectionLost(1)) {
            Comm_SetLostFlag();
        } else {
            s32 r = verifySlotsStep();
            if (r == 1) {
                actStep = 0xb;
            } else if (r != 3) {
                gCommManager->setErrorMode(2);
                actStep = 6;
            }
        }
        break;
    case 6: {
        Comm_IsConnectionLost(1);
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            gCommManager->setErrorMode(0);
            actStep = 0xb;
        } else if (r == 0) {
            actStep = 7;
        }
        break;
    }
    case 7:
        if (Comm_IsConnectionLost(1)) {
            gSaveFooter.markInterrupted();
            actStep = 0xa;
        } else if (CommCtrl_SendAct0E(1, 1)) {
            actStep = 8;
        }
        break;
    case 8:
        if (Comm_IsConnectionLost(1)) {
            gSaveFooter.markInterrupted();
            actStep = 0xa;
        } else if ((NetOverlay_AssertAny(), Net_IsReadyToSend())) {
            u32 t = ctrlAct0E[0];
            if (t == 1) {
                gCommManager->setErrorMode(0);
                actStep = 9;
            } else if (t == 2) {
                gSaveFooter.markInterrupted();
                actStep = 0xa;
            }
        }
        break;
    case 9:
        if (Wifi_EndSession()) {
            NetOverlay_Restore();
        }
        MI_CpuCopy8(playerDataCopy, PlayerData_GetCurrent(), sizeof(PlayerData));
        ((HudWallet *)Hud_GetWallet())->unfreezeValue();
        actStep = 0x16;
        break;
    case 10: {
        Comm_IsConnectionLost(1);
        s32 r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            gCommManager->setErrorMode(0);
            actStep = 0xb;
        } else if (r == 0) {
            gCommManager->setErrorMode(0);
            actStep = 0x11;
        }
        break;
    }
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        SaveManager_RunSessionEnd(this, &actStep, 0xb, 0x11, 1, 1);
        break;
    default:
        this->setState(0);
        break;
    }
}

void SaveManager::showSequence2Msg0A() {
    u8 b;
    void *o = TalkWindow_Get(0);
    ((TalkWindowState *)(o))->hideBusyIcon();
    ((TalkWindowState *)(o))->unlockAdvance();
    b = 0xa;
    ((TalkWindowState *)(o))->setNextMessage((u8 *)(&b), (u8 *)"sp_etc_sequence2");
}

void SaveManager::showSequence2Msg0B() {
    u8 b;
    void *o = TalkWindow_Get(0);
    ((TalkWindowState *)(o))->hideBusyIcon();
    ((TalkWindowState *)(o))->unlockAdvance();
    b = 0xb;
    ((TalkWindowState *)(o))->setNextMessage((u8 *)(&b), (u8 *)"sp_etc_sequence2");
}

void SaveManager::func_020a15f8() {
    void *o = TalkWindow_Get(0);
    ((TalkWindowState *)(o))->hideBusyIcon();
    ((TalkWindowState *)(o))->unlockAdvance();
}

BOOL SaveManager::func_020a15c8(u32 v) {
    void *o = TalkWindow_Get(0);
    if (((u32 *)o)[1] == 2) {
        if (v != 0) {
            ((TalkWindowState *)(o))->showBusyIcon(1);
        } else {
            ((TalkWindowState *)(o))->showBusyIcon(0);
        }
        return TRUE;
    }
    return FALSE;
}

SaveManagerTalk::SaveManagerTalk() {
}

SaveManagerTalk::~SaveManagerTalk() {
}

void SaveManagerTalk::setOwner(SaveManager *v) {
    owner = v;
}

void SaveManagerTalk::onMessageEnd(u32) {
    void *o = TalkWindow_Get(0);
    switch (msgIndex) {
    case 0xa:
        ((TalkWindowState *)(o))->lockAdvance();
        break;
    case 8:
        ((TalkWindowState *)(o))->setNextMessage(&gTalkMsgIndexEnd, 0);
        break;
    case 0x27:
        ((TalkWindowState *)(o))->setNextMessage(&gTalkMsgIndexEnd, 0);
        break;
    case 0x26:
        ((TalkWindowState *)(o))->lockAdvance();
        owner->setState(0x1e);
        break;
    case 0x69:
        ((TalkWindowState *)(o))->setNextMessage(&gTalkMsgIndexEnd, 0);
        break;
    }
}

void SaveManagerTalk::onChoice(u32) {
}

extern "C" void Save_StoreCurrentPlayerToResident(void) {
    void *o = PlayerData_GetCurrent();
    MI_CpuCopy8(o, (void *)PlayerData_Get(sSessionResidentIndex), sizeof(PlayerData));
}

void SaveManager::backupVillagerTransfer() {
    TownExchangeRecord *const g = &data_021e7f8c;
    g->incrementCounter();
    MI_CpuCopy8(g, villagerTransferBackup, 0x84c);
}

void SaveManager::restoreVillagerTransfer() {
    MI_CpuCopy8(villagerTransferBackup, &data_021e7f8c, 0x84c);
}

u32 SaveManager::func_020a148c() {
    return freePlayerSlot;
}

u32 SaveManager::getTransferDest(u32 i) {
    return transferDests[i];
}

void SaveManager::setTransferDest(u32 i, u8 v) {
    transferDests[i] = v;
}

u32 SaveManager::isTransferReceived(u32 i) {
    return transferReceived[i];
}

void SaveManager::setTransferReceived(u32 i, u8 v) {
    transferReceived[i] = v;
}

AxMail sAxMailBuf;

AxBbsNotice sAxBbsBuf;

BlancaFaceRecord sGameStatsBuf;


SaveManagerActEntry sSaveManagerStates[32] = {
    {&SaveManager::enterAct00, &SaveManager::execAct00},
    {&SaveManager::enterAct01, &SaveManager::execAct01},
    {&SaveManager::enterAct02, &SaveManager::execAct02},
    {&SaveManager::enterAct03, &SaveManager::execAct03},
    {&SaveManager::enterAct04, &SaveManager::execAct04},
    {&SaveManager::enterAct05, &SaveManager::execAct05},
    {&SaveManager::enterAct06, &SaveManager::execAct06},
    {&SaveManager::enterAct07, &SaveManager::execAct07},
    {&SaveManager::enterAct08, &SaveManager::execAct08},
    {&SaveManager::enterAct09, &SaveManager::execAct09},
    {&SaveManager::enterAct0A, &SaveManager::execAct0A},
    {&SaveManager::enterAct0B, &SaveManager::execAct0B},
    {&SaveManager::enterAct0C, &SaveManager::execAct0C},
    {&SaveManager::enterAct0D, &SaveManager::execAct0D},
    {&SaveManager::enterAct0E, &SaveManager::execAct0E},
    {&SaveManager::enterAct0F, &SaveManager::execAct0F},
    {&SaveManager::enterAct10, &SaveManager::execAct10},
    {&SaveManager::enterAct11, &SaveManager::execAct11},
    {&SaveManager::enterAct12, &SaveManager::execAct12},
    {&SaveManager::enterAct13, &SaveManager::execAct13},
    {&SaveManager::enterAct14, &SaveManager::execAct14},
    {&SaveManager::enterAct15, &SaveManager::execAct15},
    {&SaveManager::enterAct16, &SaveManager::execAct16},
    {&SaveManager::enterAct17, &SaveManager::execAct17},
    {&SaveManager::enterAct18, &SaveManager::execAct18},
    {&SaveManager::enterAct19, &SaveManager::execAct19},
    {&SaveManager::enterAct1A, &SaveManager::execAct1A},
    {&SaveManager::enterAct1B, &SaveManager::execAct1B},
    {&SaveManager::enterAct1C, &SaveManager::execAct1C},
    {&SaveManager::enterAct1D, &SaveManager::execAct1D},
    {&SaveManager::enterAct1E, &SaveManager::execAct1E},
    {&SaveManager::enterAct1F, &SaveManager::execAct1F},
};

u8 data_021ed390;

SaveManager *gSaveManager;



u8 sJoiningAid;


char *sNetRegion = data_020e24f0;

char data_020e2790[] = "forest_mail_USA.bin";

char data_020e24f0[] = "us";

s32 sSaveManagerRequest;

u8 sRecentJoinAids[3];



const VecFx32 data_020d0770 = {0x10000, 0, 0x5000};

u8 sGameStatsReceived;

u8 sAxBbsReceived;



void *gTownTransferBuf;


GuestSlotTriple data_020e2770 = {4, 4, 4};

const s32 sSaveSlotSizes[3] = {0x15fe0, 0x15fe0, 0x11df4};

char data_020e277c[] = "forest_bbs_USA.bin";

char *sAxMailFileName = data_020e2790;

s32 sGameStartMode;


s32 sEraseResidentSlot;


const VecFx32 data_020d0788 = {0x10000, 0, 0x5000};

const u32 sSaveSlotOffsets[3] = {0, 0x15fe0, 0x2e20c};

GuestSlotTriple data_020e2764 = {3, 3, 3};

u8 data_021ed3a4;


char *sAxBbsFileName = data_020e277c;

u8 sAxMailReceived;


u8 data_020e252c[8] = {0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0, 0};

s32 SaveManager::verifySlotsStep() {
    s32 r = 0;
    static Fn tbl[4] = {&SaveManager::verifyStepReset, &SaveManager::verifyStepSlot0, &SaveManager::verifyStepSlot1,
                        &SaveManager::verifyStepChoose};
    if (tbl[slotStep] != 0) {
        r = (this->*tbl[slotStep])();
    }
    if (r != 3) {
        slotStep = 0;
        return r;
    }
    return 3;
}

s32 SaveManager::verifyStepReset() {
    slotStatus.hi = 3;
    slotStatus.lo = 3;
    slotOrder.lo = 3;
    slotOrder.hi = 3;
    slotStep = slotStep + 1;
    return 3;
}

s32 SaveManager::verifyStepSlot0() {
    slotStatus.hi = this->verifySlotStep(0);
    if (slotStatus.hi == 3) {
        return 3;
    }
    slotStep = slotStep + 1;
    return 3;
}

s32 SaveManager::verifyStepSlot1() {
    slotStatus.lo = this->verifySlotStep(1);
    if (slotStatus.lo == 3) {
        return 3;
    }
    slotStep = slotStep + 1;
    return 3;
}

s32 SaveManager::verifyStepChoose() {
    s32 r = 0;
    if (slotStatus.lo == 1 || slotStatus.hi == 1) {
        r = 1;
    } else if (slotStatus.hi != 0 && slotStatus.lo != 0) {
        slotOrder.lo = 1;
        slotOrder.hi = 0;
        r = 4;
    } else if (slotStatus.hi != 0) {
        slotOrder.lo = 1;
        slotOrder.hi = 0;
    } else if (slotStatus.lo != 0) {
        slotOrder.lo = 0;
        slotOrder.hi = 1;
    } else {
        slotOrder.lo = (u8)Save_SlotStampsMatch();
        if (slotOrder.lo == 1) {
            slotOrder.hi = 0;
        } else {
            slotOrder.hi = 1;
        }
    }
    slotStep = 6;
    return r;
}

s32 SaveManager::saveSlotStep(s32 arg) {
    static SlotStepFn tbl[7] = {
        &SaveManager::stepPrepare, &SaveManager::stepChecksum, &SaveManager::stepReadBack,
        &SaveManager::stepFindDirty, &SaveManager::stepWriteDirty, &SaveManager::stepCommit,
        0};
    s32 r = 3;
    if (tbl[slotStep]) r = (this->*tbl[slotStep])(arg);
    if (slotStep == 6) {
        r = 0;
        slotStep = r;
    }
    return r;
}

s32 SaveManager::stepPrepare(s32 idx) {
    u8 *a[3];
    a[0] = (u8 *)&gSaveData;
    a[1] = (u8 *)&gSaveData;
    a[2] = SaveManager_GetLetterStorage();
    MI_CpuFill8(workBuf, 0, sSaveSlotSizes[idx]);
    MI_CpuCopy8(a[idx], workBuf, sSaveSlotDataSizes[idx]);
    blockCursor = 0;
    dirtyFirstBlock = -1;
    dirtySize = 0;
    slotStep = 1;
    return 3;
}

s32 SaveManager::stepChecksum(s32 mode) {
    if (mode == 2) {
        u8 *b = workBuf;
        *(u16 *)(b + 0x11df2) = Save_CalcChecksum(b, 0x11df4, *(u16 *)(b + 0x11df2));
    } else {
        s32 s = 0;
        if (mode == 1) s = verifySlotStep(s);
        if (s == 3) return 3;
        if (s == 1) return 1;
        u8 *buf = workBuf;
        if (mode == 0) {
            ((SaveRecord4 *)(buf + __builtin_offsetof(SaveData, footer)))->newStamp();
        } else if (s == 0) {
            SaveRecord4 local;
            Save_ReadSlotFooter(0, &local);
            ((SaveRecord4 *)(buf + __builtin_offsetof(SaveData, footer)))->setStamp(local.getStamp());
        }
        u8 *p = buf + __builtin_offsetof(SaveData, townExchange);
        ((TownExchangeRecord *)(p))->setChecksum(Save_CalcChecksum(p, 0x84c, ((TownExchangeRecord *)(p))->getChecksum()));
        p = buf + __builtin_offsetof(SaveData, receivedLetters);
        ((TownExchangeRecord *)(p))->setChecksumByte(Save_CalcChecksum(p, 0xf8, ((TownExchangeRecord *)(p))->getChecksumByte()));
        for (s32 i = 0; i < 4; i++) {
            u8 *e = (u8 *)((PlayerData *)(PlayerData_GetResident(buf + 0xc, i)))->getWifiUserData();
            PlayerWifiData_SetChecksum(e, Save_CalcChecksum(e, 0x50, PlayerWifiData_GetChecksum(e)));
            e = (u8 *)((PlayerData *)PlayerData_GetResident(buf + __builtin_offsetof(SaveData, players), i))->getFriendList();
            FriendList_SetChecksum(e, Save_CalcChecksum(e, 0x384, FriendList_GetChecksum(e)));
        }
        SaveChecksum *sum = (SaveChecksum *)(buf + __builtin_offsetof(SaveData, footer));
        sum->set(Save_CalcChecksum(buf, 0x15fe0, sum->get()));
        Save_Sum16(buf, 0x15fe0);
        Save_Sum16(buf, 0x15fe0);
    }
    slotStep = 2;
    return 3;
}

s32 SaveManager::stepReadBack(s32 idx) {
    s32 r = Backup_GetStatus(&gBackup);
    s32 off = sSaveSlotOffsets[idx];
    s32 size = sSaveSlotSizes[idx];
    if (r == 1) {
        Backup_EndAccess(&gBackup);
        return 1;
    } else if (r == 4) {
        MI_CpuFill8(readBackBuf, 0, size);
        Backup_ReadAsync(&gBackup, readBackBuf, size, off);
    } else if (r != 3) {
        Backup_EndAccess(&gBackup);
        slotStep = 3;
    }
    return 3;
}

s32 SaveManager::stepFindDirty(s32 idx) {
    s32 size = sSaveSlotSizes[idx];
    s32 q = size / 0x200;
    s32 rem = size % 0x200;
    while (blockCursor <= q) {
        s32 n = 0x200;
        if (blockCursor == q) n = rem;
        s32 o = blockCursor << 9;
        if (memEqual(workBuf + o, readBackBuf + o, n) == 0) {
            if (dirtyFirstBlock == -1) dirtyFirstBlock = blockCursor;
            dirtySize = dirtySize + n;
            if (blockCursor == q) {
                slotStep = 4;
                blockCursor = blockCursor + 1;
                return 3;
            }
        } else if (dirtySize != 0) {
            slotStep = 4;
            return 3;
        }
        blockCursor = blockCursor + 1;
    }
    if (blockCursor > q) slotStep = 5;
    return 3;
}

s32 SaveManager::stepWriteDirty(s32 idx) {
    s32 r = Backup_GetStatus(&gBackup);
    s32 off = sSaveSlotOffsets[idx];
    if (r == 1) {
        Backup_EndAccess(&gBackup);
        return 1;
    } else if (r == 4) {
        s32 o = dirtyFirstBlock << 9;
        Backup_WriteAsync(&gBackup, o + off, workBuf + o, dirtySize);
    } else if (r != 3) {
        Backup_EndAccess(&gBackup);
        dirtyFirstBlock = -1;
        dirtySize = 0;
        slotStep = 3;
    }
    return 3;
}

s32 SaveManager::stepCommit(s32 idx) {
    u8 *a[3];
    a[0] = (u8 *)&gSaveData;
    a[1] = (u8 *)&gSaveData;
    a[2] = SaveManager_GetLetterStorage();
    MI_CpuCopy8(workBuf, a[idx], sSaveSlotDataSizes[idx]);
    slotStep = 6;
    return 3;
}

s32 SaveManager::eraseSlotStep(s32 idx) {
    s32 r = Backup_GetStatus(&gBackup);
    s32 off = sSaveSlotOffsets[idx];
    s32 size = sSaveSlotSizes[idx];
    if (r == 1) {
        Backup_EndAccess(&gBackup);
        return 1;
    } else if (r == 4) {
        MI_CpuFill8(workBuf, 0xff, size);
        Backup_WriteAsync(&gBackup, off, workBuf, size);
    } else if (r != 3) {
        Backup_EndAccess(&gBackup);
        return 0;
    }
    return 3;
}

extern "C" s32 Save_LoadSync(void) {
    s32 a = Save_CheckSlot(0);
    s32 b = Save_CheckSlot(1);
    if (a == 1 || b == 1) return 1;
    if (a != 0 && b != 0) return 4;
    if (a != 0) Save_ReadSlot(1);
    else if (b != 0) Save_ReadSlot(0);
    else Save_ReadSlot(Save_SlotStampsMatch());
    return 0;
}

extern "C" s32 Save_CheckSlot(s32 idx) {
    return Save_ReadAndCheckSlot(idx, 0);
}

extern "C" s32 Save_ReadAndCheckSlot(s32 idx, s32 flag) {
    if (flag != 0 && gSaveManager == NULL) return 1;
    s32 r = Save_ReadSlotSync(idx, flag);
    if (r == 0) {
        u8 *buf;
        if (flag != 0) buf = gSaveManager->workBuf;
        else buf = (u8 *)&gSaveData;
        s32 t = Save_Sum16(buf, 0x15fe0);
        if (((SaveData *)(buf))->isValid() == 0) return 4;
        if (t == 0) {
            Save_Sum16(buf + __builtin_offsetof(SaveData, townExchange), 0x84c);
            s32 i = 0;
            u8 *p = buf + __builtin_offsetof(SaveData, players);
            for (; i < 4; i++) {
                Save_Sum16(((PlayerData *)(PlayerData_GetResident(p, i)))->getWifiUserData(), 0x50);
                Save_Sum16(((PlayerData *)(PlayerData_GetResident(buf + 0xc, i)))->getFriendList(), 0x384);
            }
        } else {
            return 4;
        }
    }
    return r;
}

extern "C" BOOL Save_ReadSlot(u32 idx) {
    return Save_ReadSlotSync(idx, 0);
}

extern "C" BOOL Save_ReadSlotSync(u32 idx, s32 flag) {
    u8 *a[3];
    a[0] = (u8 *)&gSaveData;
    a[1] = (u8 *)&gSaveData;
    a[2] = SaveManager_GetLetterStorage();
    u8 *buf = a[idx];
    s32 off = sSaveSlotOffsets[idx];
    s32 size = sSaveSlotSizes[idx];
    if (flag != 0 && idx <= 1) {
        SaveManager *g = gSaveManager;
        if (g == NULL) return TRUE;
        buf = g->workBuf;
    }
    if (Backup_Read(&gBackup, buf, size, off) != 0) return TRUE;
    return FALSE;
}

s32 SaveManager::verifySlotStep(s32 idx) {
    s32 r = Backup_GetStatus(&gBackup);
    s32 off = sSaveSlotOffsets[idx];
    s32 size = sSaveSlotSizes[idx];
    if (r == 4) {
        MI_CpuFill8(readBackBuf, 0, size);
        Backup_ReadAsync(&gBackup, readBackBuf, size, off);
    } else if (r != 3) {
        Backup_EndAccess(&gBackup);
        if (((SaveData *)(gSaveManager->readBackBuf))->isValid() == 0) return 4;
        if (Save_Sum16(readBackBuf, sSaveSlotDataSizes[idx]) == 0) return 0;
        return 4;
    } else if (r == 1) {
        Backup_EndAccess(&gBackup);
        return 1;
    }
    return 3;
}

extern "C" s32 Save_ReadSlotAsyncStep(s32 idx, u8 *buf) {
    s32 r = Backup_GetStatus(&gBackup);
    s32 off = sSaveSlotOffsets[idx];
    s32 size = sSaveSlotSizes[idx];
    if (r == 4) {
        MI_CpuFill8(buf, 0, size);
        Backup_ReadAsync(&gBackup, buf, size, off);
    } else if (r != 3) {
        Backup_EndAccess(&gBackup);
        s32 t = Save_Sum16(buf, sSaveSlotDataSizes[idx]);
        if (((SaveData *)(buf))->isValid() == 0) return 4;
        if (t == 0) return 0;
        return 4;
    } else if (r == 1) {
        Backup_EndAccess(&gBackup);
        return 1;
    }
    return 3;
}

s32 SaveManager::loadSlotStep(s32 idx) {
    u8 *a[3];
    a[0] = (u8 *)&gSaveData;
    a[1] = (u8 *)&gSaveData;
    a[2] = SaveManager_GetLetterStorage();
    u8 *buf = a[idx];
    s32 r = Backup_GetStatus(&gBackup);
    s32 off = sSaveSlotOffsets[idx];
    s32 size = sSaveSlotSizes[idx];
    if (r == 4) {
        Backup_ReadAsync(&gBackup, buf, size, off);
    } else if (r == 1) {
        Backup_EndAccess(&gBackup);
        return 1;
    } else if (r != 3) {
        Backup_EndAccess(&gBackup);
        if (Save_Sum16(buf, sSaveSlotDataSizes[idx]) == 0) return 0;
        return 4;
    }
    return 3;
}

BOOL SaveManager::memEqual(u8 *p, u8 *q, s32 n) {
    while (n != 0) {
        if (*p != *q) return FALSE;
        p++;
        q++;
        n--;
    }
    return TRUE;
}

void SaveManager::startTalk(const char *str, u8 flag) {
    TalkWindowState *o = TalkWindow_Get(0);
    talk.resetMsg();
    talk.setFileName(str);
    talk.msgIndex = flag;
    o->lockAdvance();
    o->attachRequest(&talk);
    o->nextState = 1;
}

extern "C" void SaveManager_RequestAct01(void) { sSaveManagerRequest = 1; }

extern "C" void SaveManager_RequestAct02(void) { sSaveManagerRequest = 2; }

extern "C" void SaveManager_RequestAct06(void) { sSaveManagerRequest = 6; }

extern "C" void SaveManager_RequestAct05(void) { sSaveManagerRequest = 5; }

extern "C" void SaveManager_RequestAct03(void) { sSaveManagerRequest = 3; }

extern "C" void SaveManager_RequestAct12(void) { sSaveManagerRequest = 0x12; }

extern "C" void SaveManager_RequestAct13(void) { sSaveManagerRequest = 0x13; }

extern "C" void SaveManager_RequestAct14(void) { sSaveManagerRequest = 0x14; }

extern "C" void SaveManager_RequestAct15(void) { sSaveManagerRequest = 0x15; }

extern "C" void SaveManager_RequestAct16(void) { sSaveManagerRequest = 0x16; }

extern "C" void SaveManager_RequestAct17(void) { sSaveManagerRequest = 0x17; }

extern "C" void SaveManager_RequestAct18(void) { sSaveManagerRequest = 0x18; }

extern "C" void SaveManager_RequestAct19(void) { sSaveManagerRequest = 0x19; }

extern "C" void SaveManager_RequestAct1A(void) { sSaveManagerRequest = 0x1a; }

extern "C" void SaveManager_RequestAct1B(void) { sSaveManagerRequest = 0x1b; }

extern "C" void SaveManager_RequestAct1F(void) { sSaveManagerRequest = 0x1f; }

extern "C" void SaveManager_RequestAct1C(void) { sSaveManagerRequest = 0x1c; }

extern "C" BOOL SaveManager_IsIdle(void) {
    SaveManager *p = gSaveManager;
    if (p != NULL && p->act == 0) return TRUE;
    return FALSE;
}

extern "C" BOOL SaveManager_HasAct12Failed(void) {
    SaveManager *p = gSaveManager;
    if (p != NULL && p->act == 0x12 && p->actStep == 3) return TRUE;
    return FALSE;
}

extern "C" BOOL SaveManager_IsIdleForRoom(void) {
    SaveManager *p = gSaveManager;
    if (p != NULL && p->act == 0) return TRUE;
    return FALSE;
}

extern "C" BOOL SaveManager_IsIdleAfterAct13() {
    SaveManager *g = gSaveManager;
    if (g && g->act == 0) return TRUE;
    return FALSE;
}

extern "C" BOOL SaveManager_HasAct13Failed() {
    SaveManager *g = gSaveManager;
    if (g && g->act == 0x13 && g->actStep == 3) return TRUE;
    return FALSE;
}

extern "C" BOOL SaveManager_IsIdleAfterAct1F() {
    SaveManager *g = gSaveManager;
    if (g && g->act == 0) return TRUE;
    return FALSE;
}

extern "C" BOOL SaveManager_HasAct1FFailed() {
    SaveManager *g = gSaveManager;
    if (g && g->act == 0x1f) {
        u32 t = g->actStep;
        if (t == 0xf || t == 0x14) return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Save_CheckFooterReadError(s32 idx) {
    SaveRecord4 d;
    if (Save_ReadSlotFooter(idx, &d)) return TRUE;
    return FALSE;
}

extern "C" BOOL Save_CheckBackupError() { return Save_CheckFooterReadError(0); }

extern "C" s32 Save_ReadSlotFooter(s32 idx, SaveRecord4 *d) {
    return Backup_Read(&gBackup, d, 4, ((u8 *)&gSaveFooter - (u8 *)&gSaveData) + sSaveSlotOffsets[idx]);
}

extern "C" BOOL Save_SlotStampsMatch() {
    SaveRecord4 a;
    Save_ReadSlotFooter(0, &a);
    SaveRecord4 b;
    Save_ReadSlotFooter(1, &b);
    if (a.getStamp() == b.getStamp()) return TRUE;
    return FALSE;
}

extern "C" BOOL Save_InvalidateLetterStorage() {
    u8 z = 0;
    if (Backup_Write(&gBackup, 0x3fffc, &z, 1) == 1) return TRUE;
    return FALSE;
}

extern "C" BOOL Save_InvalidateAll() {
    u8 *ls = SaveManager_GetLetterStorage();
    SaveRecord4 *const r7 = &gSaveFooter;
    u8 *r6;
    u32 r5, r4;
    r7->clearState();
    LetterStorage_MarkInterrupted(ls);
    r6 = ls + 0x11df0;
    r5 = (u8 *)r7 - (u8 *)&gSaveData;
    r4 = r6 - ls;
    if (Backup_Write(&gBackup, sSaveSlotOffsets[0] + r5, r7, 4) == 1) return TRUE;
    if (Backup_Write(&gBackup, sSaveSlotOffsets[1] + r5, r7, 4) == 1) return TRUE;
    if (Backup_Write(&gBackup, sSaveSlotOffsets[2] + r4, r6, 1) == 1) return TRUE;
    return FALSE;
}

extern "C" BOOL Save_WritePlayerWifiData() {
    u8 *q;
    u32 d;
    q = (u8 *)((PlayerData *)PlayerData_GetResident(gSaveData.players, PlayerData_GetCurrentIndex()))->getWifiUserData();
    PlayerWifiData_SetChecksum(q, Save_CalcChecksum(q, 0x50, PlayerWifiData_GetChecksum(q)));
    d = q - (u8 *)&gSaveData;
    if (Backup_Write(&gBackup, sSaveSlotOffsets[0] + d, q, 0x50) == 1) return TRUE;
    if (Backup_Write(&gBackup, sSaveSlotOffsets[1] + d, q, 0x50) == 1) return TRUE;
    return FALSE;
}

extern "C" BOOL Save_WritePlayerFriendList() {
    u8 *base = (u8 *)&gSaveData;
    s32 t = PlayerData_GetCurrentIndex();
    u8 *p;
    u8 *q;
    p = (u8 *)PlayerData_GetCurrent()->getFriendList();
    if (t >= 4) t = sSessionResidentIndex;
    q = (u8 *)((PlayerData *)PlayerData_GetResident(gSaveData.players, t))->getFriendList();
    FriendList_SetChecksum(p, Save_CalcChecksum(p, 0x384, FriendList_GetChecksum(p)));
    {
        u32 d = q - base;
        if (Backup_Write(&gBackup, sSaveSlotOffsets[0] + d, p, 0x384) == 1) return TRUE;
        if (Backup_Write(&gBackup, sSaveSlotOffsets[1] + d, p, 0x384) == 1) return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Save_WriteVillagerTransfer() {
    u32 y, x;
    u32 a, b;
    u8 *base = (u8 *)&gSaveData;
    TownExchangeRecord *p = &data_021e7f8c;
    u8 *q = gSaveData.receivedLetters;
    a = (u8 *)p - base;
    b = q - base;
    p->setChecksum(Save_CalcChecksum(p, 0x84c, p->getChecksum()));
    ((TownExchangeRecord *)(q))->setChecksumByte(Save_CalcChecksum(q, 0xf8, ((TownExchangeRecord *)(q))->getChecksumByte()));
    if (Backup_Write(&gBackup, sSaveSlotOffsets[0] + a, p, 0x84c) == 1) return TRUE;
    if (Backup_Write(&gBackup, sSaveSlotOffsets[1] + a, p, 0x84c) == 1) return TRUE;
    if (Backup_Write(&gBackup, sSaveSlotOffsets[0] + b, q, 0xf8) == 1) return TRUE;
    if (Backup_Write(&gBackup, sSaveSlotOffsets[1] + b, q, 0xf8) == 1) return TRUE;
    return FALSE;
}

extern "C" void GameStart_SetupSave() {
    if (!GameStart_IsMode4()) {
        if (GameStart_IsNewTown()) gSaveData.reset();
        if (GameStart_IsMode3()) {
            CommManager *g = gCommManager;
            g->localSlot = 0;
            PlayerSession_SetDataIndex(g->localSlot, 0);
        } else {
            u8 *p = gSaveData.players;
            s32 t = PlayerDataArray_FindUnused(p);
            CommManager *g = gCommManager;
            g->localSlot = 0;
            PlayerSession_SetDataIndex(g->localSlot, t);
            PlayerDataArray_CreateResident(p, data_020e252c, 0, t);
        }
    }
}

extern "C" void SaveManager_SetEraseResidentSlot(s32 v) { sEraseResidentSlot = v; }

extern "C" u32 Net_GetJoiningAid() { return sJoiningAid; }

extern "C" void Net_SetJoiningAid(u32 v) { sJoiningAid = v; }

extern "C" void *SaveManager_GetTownTransferBuf() { return gTownTransferBuf; }

extern "C" u32 SaveManager_IsGatePassed() { return data_021ed398; }

extern "C" void SaveManager_SetGatePassed() { data_021ed398 = 1; }

extern "C" u32 SaveManager_IsSessionJoined() {
    if (SaveManager_Get()) return SaveManager_Get()->sessionJoined;
    return 0;
}

extern "C" u8 *SaveManager_GetLetterStorage() {
    if (gSaveManager == NULL) return NULL;
    return gSaveManager->letterStorage;
}

extern "C" TownCompressBuffer *SaveManager_GetTownCompressBuf() {
    if (gSaveManager == NULL) return NULL;
    return gSaveManager->townCompressBuf;
}

extern "C" TownCompressThread *SaveManager_GetTownCompressThread() {
    if (gSaveManager == NULL) return NULL;
    return gSaveManager->townCompressThread;
}

extern "C" SaveManager *SaveManager_Get() { return gSaveManager; }

extern "C" void GameStart_SetNewTown() { sGameStartMode = 1; }

extern "C" void GameStart_SetNewResident() { sGameStartMode = 2; }

extern "C" void GameStart_SetMode3() { sGameStartMode = 3; }

extern "C" void GameStart_SetMode4() { sGameStartMode = 4; }

extern "C" BOOL GameStart_IsActive() {
    if (sGameStartMode != 0) return TRUE;
    return FALSE;
}

extern "C" BOOL GameStart_IsNewTown() {
    if (sGameStartMode == 1) return TRUE;
    return FALSE;
}

extern "C" BOOL GameStart_IsNewResident() {
    if (sGameStartMode == 2) return TRUE;
    return FALSE;
}

extern "C" BOOL GameStart_IsMode3() {
    if (sGameStartMode == 3) return TRUE;
    return FALSE;
}

extern "C" BOOL GameStart_IsMode4() {
    if (sGameStartMode == 4) return TRUE;
    return FALSE;
}

extern "C" void GameStart_Clear() { sGameStartMode = 0; }

extern "C" void SaveManager_SetHostMemberMask(SaveManager *p, u32 v) { p->hostMemberMask = v; }

extern "C" void SaveManager_SetHostDataIndex(SaveManager *p, u32 v) { p->hostDataIndex = v; }

extern "C" void SaveManager_SetJoinDone(SaveManager *p, u32 v) { p->joinDone = v; }

extern "C" void SaveManager_SetCtrlAct12(SaveManager *p, u32 v) { p->ctrlAct12 = v; }

extern "C" void SaveManager_SetRecvAct07(SaveManager *p, u32 v) { p->recvAct07 = v; }

extern "C" void SaveManager_SetJoinReady(SaveManager *p, u32 v) { p->joinReady = v; }

extern "C" void SaveManager_SetDateTimeReceived(SaveManager *p, u32 v) { p->dateTimeReceived = v; }

extern "C" u8 *SaveManager_GetHostDateTime(SaveManager *p) { return (u8 *)&p->hostDateTime; }

extern "C" void SaveManager_SetRecvAct04(SaveManager *p, s32 i, u32 v) { p->recvAct04[i] = v; }

extern "C" void SaveManager_SetRecvAct02(SaveManager *p, s32 i, u32 v) { p->recvAct02[i] = v; }

extern "C" void SaveManager_SetCtrlAct0E(SaveManager *p, s32 i, u32 v) { p->ctrlAct0E[i] = v; }

extern "C" void SaveManager_ClearCtrlAct0E(SaveManager *p) {
    s32 i;
    for (i = 3; i >= 0; i--) p->ctrlAct0E[i] = 0;
}

extern "C" void SaveManager_SetRecvAct03(u32 v) {
    if (gSaveManager) gSaveManager->recvAct03 = v;
}

extern "C" void SaveManager_SetRecvAct06(SaveManager *p, s32 i, u32 v) { p->recvAct06[i] = v; }

extern "C" void SaveManager_SetCtrlAct10(SaveManager *p, s32 i, u32 v) { p->ctrlAct10[i] = v; }

extern "C" void SaveManager_SetCtrlAct11(SaveManager *p, s32 i, u32 v) { p->ctrlAct11[i] = v; }

extern "C" void SaveManager_SetCtrlAct14Aid(u32 v) {
    if (gSaveManager) gSaveManager->ctrlAct14Aid = v;
}

extern "C" u32 SaveManager_GetCtrlAct14Aid() {
    if (gSaveManager) return gSaveManager->ctrlAct14Aid;
    return 4;
}

extern "C" void SaveManager_SetCtrlAct17(SaveManager *p, u32 v) { p->ctrlAct17 = v; }

extern "C" void NetSession_ReturnToSolo(void *a, s32 b, s32 c) {
    s32 i;
    CommManager *g;
    s32 s;
    s32 t;
    PlayerData *r5;
    u8 *r4;
    union { u16 raw; Unk_0209865c_Bits bits; } packed;
    ClockDateTimeWords l;
    Comm_ResetNetSession();
    Wifi_EndSession();
    if (b < 7) {
        g = gCommManager;
        PlayerSession_ClearDataIndex(g->localSlot);
        g->localSlot = 0;
    }
    g = gCommManager;
    g->setMemberCount(1);
    if (b < 7) {
        PlayerSession_SetDataIndex(g->localSlot, b);
    }
    s = g->localSlot;
    PlayerSession_GetDataIndex(s);
    for (i = 3; i >= 0; i--) {
        if (i != s) PlayerSession_ClearDataIndex(i);
    }
    for (i = 2; i >= 0; i--) {
        PlayerData *p = PlayerData_Get(i + 4);
        if (p) p->reset();
    }
    if (c == 0) {
        Clock_Update(0);
        SaveData_Setup(&gSaveData, 2);
        SaveData_Apply((u8 *)&gSaveData);
        if (TownBlockMap_Get()) {
            ((TownBlockMap *)(TownBlockMap_Get()))->updateAcreIds();
            ((TownBlockMap *)(TownBlockMap_Get()))->bindBg();
            Town_ClearBorderTrees(TownBlockMap_Get());
        }
        HouseRoomMaps_UpdateAll();
        HouseRoomMaps_BindBg();
    } else {
        Town_OnLoad();
    }
    Comm_ResetPeerState(-4);
    if (c == 0) {
        t = PlayerSession_GetDataIndex(0);
        if (t < 7) {
            r5 = PlayerData_Get(t);
            r4 = PlayerSession_GetSessionFlags();
            if (*r4 & 6) {
                l.words[0] = 0;
                l.words[1] = 0;
                Clock_GetDateTime(&l.dt);
                packed.raw = (packed.raw & ~0x7f) | (l.dt.year & 0x7f);
                packed.raw = (packed.raw & ~0x780) | ((l.dt.month & 0xf) << 7);
                packed.raw = (packed.raw & ~0xf800) | ((l.dt.day & 0x1f) << 11);
                if (*r4 & 2) *r4 |= 0x11;
            } else {
                packed.raw = *PlayerSession_GetLastPlayDate();
                *r4 = *r4 | ((*r4 >> 4) & 1);
            }
            r5->setLastPlayDate(packed.bits);
        }
    }
}

extern "C" void VillagerTransfer_PlanSwap(void *a) {
    s32 list[4];
    CommManager *g;
    s32 n;
    s32 i;
    s32 cur = NetSession_GetLastSyncSlot();
    s32 pick;
    n = 0;
    i = 3;
    g = gCommManager;
    for (; i >= 0; i--) {
        if (i != cur && g->isSlotActive(i)) {
            list[n] = i;
            n++;
        }
    }
    for (i = 3; i >= 0; i--) {
        if (g->isSlotActive(i)) {
            ((SaveManager *)(a))->setTransferDest(i, i);
        } else {
            ((SaveManager *)(a))->setTransferDest(i, 4);
        }
    }
    pick = list[Random_GlobalBelow(n)];
    ((SaveManager *)(a))->setTransferDest(pick, cur);
    ((SaveManager *)(a))->setTransferDest(cur, pick);
}

extern "C" void VillagerTransfer_PlanRotate(void *a) {
    s32 list[4];
    s32 n = 0;
    s32 i = 3, j;
    CommManager *g = gCommManager;
    for (; i >= 0; i--) {
        if (g->isSlotActive(i)) {
            list[n] = i;
            n++;
        }
    }
    for (i = 3; i >= 0; i--) {
        ((SaveManager *)(a))->setTransferDest(i, 4);
    }
    j = 0;
    for (i = 0; i < n; i++) {
        s32 k = i + 1;
        if (k >= n) k = j;
        ((SaveManager *)(a))->setTransferDest(n ? list[i] : list[i], list[k]);
    }
}

extern "C" void LostChild_ResetAndPairLast(SaveManager *a) {
    s32 i = 3;
    CommManager *g = gCommManager;
    for (; i >= 0; i--) {
        if (g->isSlotActive(i)) {
            ((LostChildRecord *)(((TownExchangeRecord *)(TownExchange_GetForAid(i)))->getLostChildRecord()))->clear();
        }
    }
    LostChild_TryPair(a, NetSession_GetLastSyncSlot());
}

extern "C" void LostChild_ResetAndPairAll(SaveManager *self) {
    CommManager *o;
    s32 i = 3;
    o = gCommManager;
    for (; i >= 0; i--) {
        if (o->isSlotActive(i)) {
            ((LostChildRecord *)(((TownExchangeRecord *)(TownExchange_GetForAid(i)))->getLostChildRecord()))->clear();
        }
    }
    for (i = 3; i >= 0; i--) {
        if (o->isSlotActive(i)) {
            LostChild_TryPair(self, i);
        }
    }
}

extern "C" void LostChild_DebugPrint(SaveManager *p, void *q) {}

extern "C" void LostChild_TryPair(SaveManager *self, s32 idx) {
    void *r7 = PlayerData_GetBySessionSlot(idx);
    if (r7 == 0) return;
    MsgString9C sa;
    TownId_GetNameString(PlayerId_GetTownId(((PlayerData *)(r7))->getPlayerId()), &sa);
    void *r6 = ((PlayerData *)(r7))->getLostChildRecord();
    if (((LostChildRecord *)(r6))->getDaysLeft()) {
        LostChild_DebugPrint(self, r6);
        return;
    }
    s32 found = 4;
    void *other = 0;
    void *other2 = 0;
    MsgString9C sb;
    s32 i = 0;
    CommManager *o = gCommManager;
    for (; i < 4; i++) {
        if (i == idx) continue;
        if (!o->isSlotActive(i)) continue;
        other = PlayerData_GetBySessionSlot(i);
        if (!other) continue;
        TownId_GetNameString(PlayerId_GetTownId(((PlayerData *)(other))->getPlayerId()), &sb);
        other2 = ((PlayerData *)(other))->getLostChildRecord();
        if (((LostChildRecord *)(other2))->getDaysLeft()) continue;
        if (Net_GetMode() == 3 || Net_GetMode() == 4) {
            if (!Wifi_IsInFriendList(self, other, r7)) continue;
            if (!Wifi_IsInFriendList(self, r7, other)) continue;
        }
        found = i;
        break;
    }
    if (found == 4) {
        return;
    }
    s16 *pp = (s16 *)DebugVar_GetPtr(0, 0x49);
    if (*pp == 0 && Random_GlobalBelow(0x10)) {
        return;
    }
    s32 r4 = Random_GlobalBelow(2);
    ((LostChildRecord *)(other2))->setKaitlinRole(r4 == 0 ? 1 : 0);
    ((LostChildRecord *)(other2))->setTownId(PlayerId_GetTownId(((PlayerData *)(r7))->getPlayerId()));
    ((LostChildRecord *)(other2))->setDaysLeft(0xa);
    ((LostChildRecord *)(r6))->setKaitlinRole(r4 == 1 ? 1 : 0);
    ((LostChildRecord *)(r6))->setTownId(PlayerId_GetTownId(((PlayerData *)(other))->getPlayerId()));
    ((LostChildRecord *)(r6))->setDaysLeft(0xa);
    LostChild_DebugPrint(self, r6);
    LostChild_DebugPrint(self, other2);
    u32 h7 = (self)->getTransferDest(idx);
    u32 h5 = (self)->getTransferDest(found);
    void *c4 = PlayerData_GetBySessionSlot((s32)h7);
    void *m7 = TownExchange_GetForAid(h7);
    MsgString9C sc;
    if (c4) {
        TownId_GetNameString(PlayerId_GetTownId(((PlayerData *)(c4))->getPlayerId()), &sc);
    }
    MI_CpuCopy8(r6, ((TownExchangeRecord *)(m7))->getLostChildRecord(), 0xc);
    c4 = PlayerData_GetBySessionSlot((s32)h5);
    void *m5 = TownExchange_GetForAid(h5);
    MsgString9C sd;
    if (c4) {
        TownId_GetNameString(PlayerId_GetTownId(((PlayerData *)(c4))->getPlayerId()), &sd);
    }
    MI_CpuCopy8(other2, ((TownExchangeRecord *)(m5))->getLostChildRecord(), 0xc);
    return;
}

extern "C" BOOL Wifi_IsInFriendList(SaveManager *self, void *a, void *b) {
    void *r6 = DwcFriendData_GetBytes(PlayerWifiData_GetOwnFriendData((u8 *)((PlayerData *)(a))->getWifiUserData()));
    u8 *r5 = FriendList_GetEntries(((PlayerData *)(b))->getFriendList());
    s32 i;
    u32 st = 0x1c;
    for (i = 0; i < 0x20; i++) {
        void *e = DwcFriendData_GetBytes(FriendEntry_GetFriendData(r5 + i * st));
        if (e) {
            if (Net_IsSameFriendData(r6, e)) return TRUE;
        }
    }
    return FALSE;
}

extern "C" void LostChild_ApplyReceived(SaveManager *self) {
    void *p5 = TownExchange_GetForAid(4);
    void *r4 = PlayerData_GetCurrent();
    MsgString9C s1;
    TownId_GetNameString(PlayerId_GetTownId(((PlayerData *)(r4))->getPlayerId()), &s1);
    void *r6 = ((PlayerData *)(r4))->getLostChildRecord();
    void *q = ((TownExchangeRecord *)(p5))->getLostChildRecord();
    MsgString9C s2;
    TownId_GetNameString(((LostChildRecord *)(q))->getTownId(), &s2);
    if (((LostChildRecord *)(q))->getDaysLeft()) {
        MI_CpuCopy8(q, r6, 0xc);
        ((LostChildRecord *)(q))->isKaitlinRole();
    }
    ((LostChildRecord *)(((TownExchangeRecord *)(p5))->getLostChildRecord()))->clear();
}

extern "C" BOOL VillagerTransfer_SendReplies(SaveManager *self) {
    GuestSlotTriple a = data_020e2764;
    GuestSlotTriple b = data_020e2770;
    s32 i = 2;
    CommManager *o = gCommManager;
    for (; i >= 0; i--) {
        s32 n = i + 1;
        if (o->isSlotActive(n)) {
            s32 q = (s32)(self)->getTransferDest(n);
            if (q < 4) {
                if (((TownExchangeRecord *)(TownExchange_GetForAid(q)))->isValid()) {
                    a.v[i] = 2;
                    b.v[i] = q;
                } else {
                    a.v[i] = 1;
                }
            } else {
                a.v[i] = 0;
            }
        }
    }
    return CommSend_VillagerTransferReply(a.v[0], b.v[0], a.v[1], b.v[1], a.v[2], b.v[2]);
}

extern "C" s32 SaveManager_RunSessionEnd(SaveManager *self, u8 *st, s32 base, s32 base2, u32 mask, u8 a6) {
    u32 cur = *st;
    if (cur == base) {
        if (Comm_IsConnectionLost(mask)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        if (Net_GetMyAid() == 0) {
            if (CommCtrl_SendAct0E(2, mask)) {
                *st = base + 1;
            }
        } else {
            if (CommCtrl_SendAct0E(2, 1)) {
                *st = base + 1;
            }
        }
    } else if (cur == base + 1) {
        if (Comm_IsConnectionLost(mask)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        NetOverlay_AssertAny();
        if (Net_IsReadyToSend()) {
            *st = base + 2;
        }
    } else if (cur == base + 2) {
        if (Net_GetMyAid() == 0) {
            BOOL flag = TRUE;
            u32 m = 0;
            s32 i;
            Comm_EnterCritical();
            for (i = 3; i >= 0; i--) {
                if (i != 0) {
                    u32 bit = 1 << i;
                    if (mask & bit) {
                        if (self->recvAct06[i] == 0) {
                            flag = FALSE;
                            m = m | bit;
                            m = (u16)m;
                        }
                    }
                }
            }
            BOOL err = Comm_IsConnectionLost(m);
            Comm_LeaveCritical();
            if (err) {
                Comm_SetLostFlag();
                return 0x20;
            }
            if (flag) {
                Comm_ResetNetSession();
                Wifi_EndSession();
                *st = base + 3;
            }
        } else {
            if (Comm_IsConnectionLost(mask)) {
                Comm_SetLostFlag();
                return 0x20;
            }
            if (self->ctrlAct0E[0]) {
                if (CommCtrl_SendAct13()) {
                    *st = base + 3;
                }
            }
        }
    } else if (cur == base + 3) {
        if (Net_GetMyAid() == 0) {
            *st = base + 4;
        } else {
            if (Comm_IsConnectionLost(mask)) {
                Comm_SetLostFlag();
                return 0x20;
            }
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend()) {
                Comm_ResetNetSession();
                Wifi_EndSession();
                *st = base + 4;
            }
        }
    } else if (cur == base + 4) {
        if (a6) (self)->showSequence2Msg0A();
        *st = base + 5;
    }

    cur = *st;
    if (cur == base2) {
        if (Comm_IsConnectionLost(mask)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        if (Net_GetMyAid() == 0) {
            if (CommCtrl_SendAct0E(2, mask)) {
                *st = base2 + 1;
            }
        } else {
            if (CommCtrl_SendAct13()) {
                *st = base2 + 1;
            }
        }
    } else if (cur == base2 + 1) {
        if (Comm_IsConnectionLost(mask)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        NetOverlay_AssertAny();
        if (Net_IsReadyToSend()) {
            *st = base2 + 2;
        }
    } else if (cur == base2 + 2) {
        if (Net_GetMyAid() == 0) {
            BOOL flag = TRUE;
            u32 m = 0;
            s32 i;
            Comm_EnterCritical();
            for (i = 3; i >= 0; i--) {
                if (i != 0) {
                    u32 bit = 1 << i;
                    if (mask & bit) {
                        if (self->recvAct06[i] == 0) {
                            flag = FALSE;
                            m = m | bit;
                            m = (u16)m;
                        }
                    }
                }
            }
            m = Comm_IsConnectionLost(m);
            Comm_LeaveCritical();
            if (m) {
                Comm_SetLostFlag();
                return 0x20;
            }
            if (flag) {
                Comm_ResetNetSession();
                Wifi_EndSession();
                *st = base2 + 3;
            }
        } else {
            Comm_ResetNetSession();
            Wifi_EndSession();
            *st = base2 + 3;
        }
    } else if (cur == base2 + 3) {
        if (a6) (self)->showSequence2Msg0B();
        *st = base2 + 4;
    } else if (cur == base2 + 4) {
        if (TalkWindow_Get(0)->state == 0) {
            OS_ResetSystem(0);
        }
    }
    return 0x20;
}

extern "C" s32 SaveManager_RunSyncedSaveHost(SaveManager *self, u8 *st, s32 a2, s32 base, u8 a5, u8 a6, s32 a7, u8 a8, u32 a9) {
    CommManager *o5, *o2;
    u32 cur = *st;
    if (cur == base) {
        if (Comm_IsConnectionLost(a9)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        s32 r = (self)->verifySlotsStep();
        if (r == 1) {
            *st = a5;
        } else if (r == 3) {
        } else {
            gSaveFooter.markInterrupted();
            if (a8) {
                (self)->restoreVillagerTransfer();
                LostChild_ApplyReceived(self);
                LostChild_SaveToTown();
            }
            *st = base + 1;
        }
    } else if (cur == base + 1) {
        if (Comm_IsConnectionLost(a9)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        s32 r = (self)->saveSlotStep(self->slotOrder.hi);
        if (r == 1) {
            *st = a5;
        } else if (r == 0) {
            *st = base + 2;
        }
    } else if (cur == base + 2) {
        if (Comm_IsConnectionLost(a9)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        s32 r6 = 1;
        s32 i = 3;
        o2 = gCommManager;
        for (; i >= 0; i--) {
            if (o2->isSlotActive(i) && !o2->isMyAid(i)) {
                u8 v = self->ctrlAct0E[i];
                if (v == 0) {
                    r6 = 0;
                    break;
                }
                if (v == 2) {
                    r6 = 2;
                    break;
                }
            }
        }
        if (r6) {
            if (a2 == 0) r6 = 0;
            else if (a2 == 2) r6 = 2;
        }
        if (r6 == 1) {
            SaveManager_ClearCtrlAct0E(self);
            *st = base + 3;
        } else if (r6 == 2) {
            *st = a6;
        }
    } else if (cur == base + 3) {
        if (Comm_IsConnectionLost(a9)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        NetOverlay_AssertAny();
        if (Net_IsReadyToSend()) {
            u32 m = Comm_GetRemoteMask();
            if (CommCtrl_SendAct0E(1, m)) {
                gSaveFooter.setStateValidAlt();
                *st = base + 4;
            }
        }
    } else if (cur == base + 4) {
        if (Comm_IsConnectionLost(a9)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        s32 r = (self)->saveSlotStep(self->slotOrder.hi);
        if (r == 1) {
            *st = a5;
        } else if (r == 0) {
            *st = base + 5;
        }
    } else if (cur == base + 5) {
        if (Comm_IsConnectionLost(a9)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        s32 r7 = 1;
        s32 i = 3;
        o5 = gCommManager;
        for (; i >= 0; i--) {
            if (o5->isSlotActive(i) && !o5->isMyAid(i)) {
                u8 v = self->ctrlAct0E[i];
                if (v == 0) {
                    r7 = 0;
                    break;
                }
                if (v == 2) {
                    r7 = 2;
                    break;
                }
            }
        }
        if (r7 == 1) {
            *st = base + 6;
        } else if (r7 == 2) {
            *st = a6;
        }
    } else if (cur == base + 6) {
        if (Comm_IsConnectionLost(a9)) {
            Comm_SetLostFlag();
            return 0x20;
        }
        u32 m = Comm_GetRemoteMask();
        if (a7 < 4) {
            m = (u16)(m | (1 << a7));
        }
        if (CommCtrl_SendAct0E(1, m)) {
            *st = base + 7;
        }
    }
    return 0x20;
}

s32 SaveManager::runSyncedSaveClient(u8 *p, u32 base, u32 fail, u8 a5, u8 a6, u8 a7, u32 a8) {
    u32 v = *p;
    s32 r;
    if (v == base) {
        if (Comm_IsConnectionLost(a8) != 0) {
            Comm_SetLostFlag();
            return 0x20;
        }
        r = this->verifySlotsStep();
        if (r == 1) {
            *p = fail;
        } else if (r != 3) {
            MI_CpuCopy8(&gSaveData, saveDataCopy, 0x15fe0);
            *p = base + 1;
        }
    } else if (v == base + 1) {
        if (Comm_IsConnectionLost(a8) != 0) {
            Comm_SetLostFlag();
            return 0x20;
        }
        r = this->loadSlotStep(slotOrder.lo);
        if (r == 1) {
            *p = fail;
        } else if (r == 0) {
            if (a6 != 0) {
                this->restoreVillagerTransfer();
            }
            Save_StoreCurrentPlayerToResident();
            if (a6 != 0) {
                LostChild_ApplyReceived(this);
                LostChild_SaveToTown();
            }
            gSaveFooter.markInterrupted();
            *p = base + 2;
        }
    } else if (v == base + 2) {
        if (Comm_IsConnectionLost(a8) != 0) {
            Comm_SetLostFlag();
            return 0x20;
        }
        r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            *p = fail;
        } else if (r == 0) {
            *p = base + 3;
        }
    } else if (v == base + 3) {
        if (Comm_IsConnectionLost(a8) != 0) {
            Comm_SetLostFlag();
            return 0x20;
        }
        if (CommCtrl_SendAct0E(1, 1) != 0) {
            *p = base + 4;
        }
    } else if (v == base + 4) {
        if (Comm_IsConnectionLost(a8) != 0) {
            Comm_SetLostFlag();
            return 0x20;
        }
        if (ctrlAct0E[0] == 1) {
            SaveManager_ClearCtrlAct0E(this);
            gSaveFooter.setStateValidAlt();
            *p = base + 5;
        } else if (ctrlAct0E[0] == 2) {
            *p = a5;
        }
    } else if (v == base + 5) {
        if (Comm_IsConnectionLost(a8) != 0) {
            Comm_SetLostFlag();
            return 0x20;
        }
        r = this->saveSlotStep(slotOrder.hi);
        if (r == 1) {
            *p = fail;
        } else if (r == 0) {
            if (a7 != 0) {
                MI_CpuCopy8(saveDataCopy, &gSaveData, 0x15fe0);
            }
            *p = base + 6;
        }
    } else if (v == base + 6) {
        if (Comm_IsConnectionLost(a8) != 0) {
            Comm_SetLostFlag();
            return 0x20;
        }
        if (CommCtrl_SendAct0E(1, 1) != 0) {
            *p = base + 7;
        }
    } else if (v == base + 7) {
        if (Comm_IsConnectionLost(a8) != 0) {
            Comm_SetLostFlag();
            return 0x20;
        }
        if (ctrlAct0E[0] == 1) {
            *p = base + 8;
        } else if (ctrlAct0E[0] == 2) {
            *p = a5;
        }
    }
    return 0x20;
}

void SaveManager::runGatherPeersInScene(u8 *p, u32 base, u32 x, u32 y) {
    u32 v = *p;
    if (v == base) {
        BOOL r = TRUE;
        s32 i = 3;
        CommManager *g = gCommManager;
        for (; i >= 0; i--) {
            if (((CommManager *)(g))->isSlotActive(i) != 0 && ((CommManager *)(g))->isMyAid(i) == 0) {
                if (x == NetArea_GetSlotScene(i) || y == NetArea_GetSlotScene(i)) {
                    if (NetArea_IsSlotMoving(i) == 0) {
                        continue;
                    }
                }
                r = FALSE;
                break;
            }
        }
        if (r) {
            ((CommManager *)(g))->setPendingMode(1);
            *p = base + 1;
        }
    } else if (v == base + 1) {
        if (((CommManager *)(gCommManager))->getMode() == 1 && CommCtrl_SendAct08() != 0) {
            *p = base + 2;
        }
    }
}

BOOL SaveManager::allPeersSentAct10() {
    BOOL r = TRUE;
    s32 i = 3;
    CommManager *g = gCommManager;
    for (; i >= 0; i--) {
        if (((CommManager *)(g))->isSlotActive(i) != 0 && ((CommManager *)(g))->isMyAid(i) == 0 && ctrlAct10[i] == 0) {
            r = FALSE;
            break;
        }
    }
    return r;
}

void SaveManager::runSendAct10(u8 *p, u32 base) {
    u32 v = *p;
    if (v == base) {
        if (((CommManager *)(gCommManager))->getMode() == 1) {
            *p = base + 1;
        }
    } else if (v == base + 1) {
        if (CommCtrl_SendAct10() != 0) {
            *p = base + 2;
        }
    }
}

extern "C" void SaveManager_StartGatekeeperTalk(SaveManager *a, u32 b) {
    if (b == 0) {
        a->startTalk("sp_npc_gatekeeper", 0x69);
    }
    PlayerData_GetCurrent()->clearFlag(2);
    ((HudCountdown *)(Hud_GetCountdown()))->start(0, 1);
}

extern "C" void SaveManager_StartSequence2Talk(SaveManager *a) {
    a->startTalk("sp_etc_sequence2", 7);
    PlayerData_GetCurrent()->clearFlag(2);
    if (SaveManager_IsEndSessionSave() != 0) {
        ((HudCountdown *)(Hud_GetCountdown()))->start(0, 1);
        PlayerData_GetCurrent()->setFlag(2);
    }
}

extern "C" void Wifi_StoreFriendList(void) {
    u8 *r6 = gCommManager->getWifiFriendList();
    u8 *r5 = FriendList_GetEntries(PlayerData_GetCurrent()->getFriendList());
    s32 i;
    for (i = 0; i < 0x20; i++) {
        MI_CpuCopy8(r6 + i * 12, DwcFriendData_GetBytes(FriendEntry_GetFriendData(r5)), 12);
        r5 += 0x1c;
    }
}

extern "C" u8 SaveManager_IsEndSessionSave(void) { return data_021ed3a4; }

extern "C" void SaveManager_SetEndSessionSave(u32 v) { data_021ed3a4 = v; }

extern "C" void SaveManager_SetSaveCorrupted(u32 v) { data_021ed390 = v; }

extern "C" void NetOverlay_LoadWireless(void) {
    OverlayHandle_Unload((OverlayHandleView *)&gOverlayHandle);
    OverlayHandle_Load((OverlayHandleView *)&gOverlayHandle, OVERLAY_66_ID);
}

extern "C" void NetOverlay_LoadWifi(void) {
    OverlayHandle_Unload((OverlayHandleView *)&gOverlayHandle);
    OverlayHandle_Load((OverlayHandleView *)&gOverlayHandle, OVERLAY_65_ID);
}

extern "C" void NetOverlay_Restore(void) {
    OverlayHandle_Unload((OverlayHandleView *)&gOverlayHandle);
    OverlayHandle_Load((OverlayHandleView *)&gOverlayHandle, OVERLAY_68_ID);
}

void TownCompressBuffer::compress() {
    s32 r = MI_CompressLZ((u8 *)&gSaveData, 0x15fe0, data);
    if (r == 0) {
        size = 0;
        MI_CpuCopy8(&gSaveData, data, 0x15fe0);
    } else {
        size = r;
    }
}

void TownCompressBuffer::decompress() {
    u8 *dst = (u8 *)SaveManager_GetTownTransferBuf();
    if (size != 0) {
        u8 ctx[0x20];
        MI_InitUncompContextLZ(ctx, dst, (const u32 *)data);
        MI_ReadUncompLZ8(ctx, dataBody, size - 4);
    } else {
        MI_CpuCopy8(data, dst, 0x15fe0);
    }
}

u32 TownCompressBuffer::getSize() {
    return size;
}

extern "C" void TownCompressThread_Main(void *arg) {
    BOOL r = arg != NULL ? TRUE : FALSE;
    if (r) {
        SaveManager_GetTownCompressBuf()->compress();
    } else {
        SaveManager_GetTownCompressBuf()->decompress();
    }
    SaveManager_GetTownCompressThread()->done = 1;
    OS_ExitThread();
}

void TownCompressThread::init() {
    stackGuardLow = 0x3039;
    stackGuardHigh = 0x3039;
    done = 0;
    MI_CpuFill8(&thread, 0, sizeof(OSThread));
    thread.state = 2;
}

void TownCompressThread::kill() {
    if (OS_IsThreadTerminated(&thread) == 0) {
        OS_KillThread(&thread, 0);
    }
}

void TownCompressThread::start(u32 a) {
    OS_CreateThread(&thread, TownCompressThread_Main, (void *)(uptr)a, &stackGuardHigh, sizeof(stack), 0x1e);
    OS_WakeupThreadDirect(&thread);
}

u8 TownCompressThread::isDone() {
    return done;
}

extern "C" s32 Wifi_EndSession(void) {
    BOOL r4 = FALSE;
    if (Net_GetMode() == 3 || Net_GetMode() == 4) {
        r4 = TRUE;
    }
    s32 r5 = Comm_End();
    if (r4) {
        PlayerData *h = PlayerData_GetCurrent();
        if (h != NULL) {
            s32 q = h->getIndex();
            if (q >= 0 && q < 4) {
                GameStats_ApplyDownload();
                AxMail_ApplyMail();
                AxMail_ApplyBbs();
                Wifi_StoreFriendList();
                if (Save_WritePlayerFriendList() != 0) {
                    TalkWindowState *t = TalkWindow_Get(0);
                    t->hideBusyIcon();
                    t->unlockAdvance();
                    u8 b = 2;
                    t->setNextMessage(&b, (u8 *)"sp_npc_gatekeeper");
                }
            }
        }
    }
    return r5;
}

extern "C" BOOL GameStats_Upload(void) {
    BlancaFaceRecord *p = &gSaveBlancaFace;
    if (p->getState() == 3) {
        s32 v = p->getChecksum();
        p->setChecksum(Save_CalcChecksum(p, 0x22c, v));
        const char *t = sNetRegion;
        NetOverlay_AssertWifi();
        Net_GameStatsUpload("http://gamestats.gs.nintendowifi.net/acrossingds/upload.asp", p, 0x22c, t);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL GameStats_Download(void) {
    if (gSaveBlancaFace.getState() == 0) {
        const char *t = sNetRegion;
        NetOverlay_AssertWifi();
        if (Net_GameStatsDownload("http://gamestats.gs.nintendowifi.net/acrossingds/download.asp", &sGameStatsBuf, 0x22c, t) != 0) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" BOOL AxMail_DownloadMail(void) {
    char a[0xc];
    char buf[0x84];
    if (gSaveData.testFlag(0x14) != 0) {
        return FALSE;
    }
    strcpy(buf, sAxMailBaseUrl);
    strcat(buf, sAxMailFileName);
    Net_GetBrid((u8 *)a);
    strcat(buf, "?brid=");
    strcat(buf, a);
    const char *t = sNetRegion;
    NetOverlay_AssertWifi();
    if (Net_HttpDownload(buf, &sAxMailBuf, 0x108, t) != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL AxMail_DownloadBbs(void) {
    char a[0xc];
    char buf[0x84];
    if (gSaveData.testFlag(0x14) != 0) {
        return FALSE;
    }
    strcpy(buf, sAxMailBaseUrl);
    strcat(buf, sAxBbsFileName);
    Net_GetBrid((u8 *)a);
    strcat(buf, "?brid=");
    strcat(buf, a);
    const char *t = sNetRegion;
    NetOverlay_AssertWifi();
    if (Net_HttpDownload(buf, &sAxBbsBuf, 0xd2, t) != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL GameStats_PollDownload(void) {
    NetOverlay_AssertWifi();
    if (Net_IsDownloadDone(0) != 0) {
        sGameStatsReceived = 1;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL AxMail_PollMail(void) {
    NetOverlay_AssertWifi();
    if (Net_IsDownloadDone(0) != 0) {
        sAxMailReceived = 1;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL AxMail_PollBbs(void) {
    NetOverlay_AssertWifi();
    if (Net_IsDownloadDone(0) != 0) {
        sAxBbsReceived = 1;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL GameStats_PollUpload(void) {
    NetOverlay_AssertWifi();
    if (Net_IsUploadDone(0) != 0) {
        gSaveBlancaFace.reset();
        return TRUE;
    }
    return FALSE;
}

extern "C" void GameStats_ApplyDownload(void) {
    if (sGameStatsReceived != 0) {
        sGameStatsReceived = 0;
        s32 r = Save_Sum16(&sGameStatsBuf, 0x22c);
        BlancaFaceRecord *dst = &gSaveBlancaFace;
        if (r == 0) {
            sGameStatsBuf.setState(1);
            MI_CpuCopy8(&sGameStatsBuf, dst, 0x22c);
        }
        MI_CpuFill8(&sGameStatsBuf, 0, 0x22c);
        sGameStatsBuf.setChecksum(1);
    }
}

extern "C" void AxMail_ApplyMail(void) {
    if (sAxMailReceived != 0) {
        u32 buf[4];
        u32 obj[0x42];
        sAxMailReceived = 0;
        AxMail_Construct(obj);
        MI_CpuCopy8(&sAxMailBuf, obj, 0x108);
        MI_CpuFill8(AxMail_GetDigest((u8 *)obj), 0, 0x10);
        DGT_Hash1CalcHmac((u8 *)buf, (u8 *)obj, 0x108, AxMail_GetDigestKey(), 0x10);
        if (Mem_Differs(AxMail_GetDigest((u8 *)sAxMailBuf.unk_00), (u8 *)buf, 0x10) == 0) {
            AxMail_Deliver((u8 *)sAxMailBuf.unk_00);
        }
        MI_CpuFill8(&sAxMailBuf, 0, 0x108);
        AxMail_Destruct(obj);
    }
}

extern "C" void AxMail_ApplyBbs() {
    u8 a[0x10];
    u8 b[0xd2];
    if (sAxBbsReceived != 0) {
        sAxBbsReceived = 0;
        AxBbsNotice_Construct();
        MI_CpuCopy8(&sAxBbsBuf, b, 0xd2);
        MI_CpuFill8(AxBbsNotice_GetDigest(b), 0, 0x10);
        DGT_Hash1CalcHmac(a, b, 0xd2, AxMail_GetDigestKey(), 0x10);
        if (Mem_Differs(AxBbsNotice_GetDigest(sAxBbsBuf.unk_00), a, 0x10) == 0) {
            AxBbsNotice_Post(sAxBbsBuf.unk_00);
        }
        MI_CpuFill8(&sAxBbsBuf, 0, 0xd2);
        AxBbsNotice_Destruct();
    }
}

extern "C" void JoinHistory_Push(u32 v) {
    s32 i;
    for (i = 0; i < 2; i++) {
        sRecentJoinAids[i] = sRecentJoinAids[i + 1];
    }
    sRecentJoinAids[2] = v;
}

extern "C" void JoinHistory_Remove(u32 v) {
    u32 idx = 0xff;
    s32 i;
    for (i = 0; i < 3; i++) {
        if (sRecentJoinAids[i] == v) {
            idx = i;
            break;
        }
    }
    if (idx != 0xff) {
        for (; (s32)idx < 2; idx++) {
            sRecentJoinAids[idx] = sRecentJoinAids[idx + 1];
        }
        sRecentJoinAids[2] = 0xff;
    }
}

extern "C" void JoinHistory_Clear() {
    s32 i;
    for (i = 0; i < 3; i++) {
        sRecentJoinAids[i] = 0xff;
    }
}

extern "C" u32 JoinHistory_GetLatest() {
    s32 i;
    for (i = 2; i >= 0; i--) {
        if (sRecentJoinAids[i] != 0xff) {
            return sRecentJoinAids[i];
        }
    }
    return 4;
}

ProcProfile sSaveManagerProfile = {(void *(*)())SaveManager_Create, 0xc7, 0xc5};

u8 sSessionResidentIndex = 7;

char data_020e27a4[] = "http://axing.nintendowifi.net/axmail/";

const s32 sSaveSlotDataSizes[3] = {0x15fe0, 0x15fe0, 0x11df4};

char *sAxMailBaseUrl = data_020e27a4;

u8 data_021ed398;

