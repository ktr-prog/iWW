#include "types.h"
#include "sys/ProcProfile.h"
#include "Unk_020d8c7c.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0202e840.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02038474.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_0209c9f8.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/main/unk_0204cc1c.h"

extern const u16 sGameRootChildProfiles[8];
const u16 sGameRootChildProfiles[8] = { 0xd7, 0xce, 0xcf, 0xcb, 8, 0xa, 0xcc, 0 };

GameProc *gGameRoot;

extern "C" {
BOOL AcreAttr_Unload();
void ItemInfo_Exit();
BOOL AcreAttr_Load();
void ItemInfo_Init();
}

class GameRoot : public GameProc {
public:
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
};

extern "C" GameRoot *GameRoot_Create() {
    return new GameRoot();
}

ProcProfile sGameRootProfile = {(void *(*)())GameRoot_Create, 0x0, 0xd7};

extern "C" void GameRoot_Boot() {
    ProcBase *r;
    s32 i;
    Scene_RequestBoot();
    r = GameProc_CreateRoot(0, 0, 1);
    for (i = 0; i < 7; i++) {
        GameProc_CreateChild(sGameRootChildProfiles[i], r, 0, 0);
    }
}

extern "C" void SoftReset_ClearSystems() {
    ChatBalloon_ClearAll();
    Bgm_ResetAll();
    Text_ResetLabels();
}

BOOL GameRoot::onCreate() {
    gGameRoot = this;
    StrBSize_Load();
    AcreAttr_Load();
    FtrInfo_Init();
    ItemInfo_Init();
    PatternPresetInfo_Open(PatternPresetInfo_Get());
    FgData_Load(gCurrentHeap);
    TownBlockMap_Create(gCurrentHeap);
    HouseRoomMaps_Create(gCurrentHeap);
    Comm_CreateHeap(gCurrentHeap);
    NetSession_Init();
    NpcSpawn_ResetAll();
    return TRUE;
}

BOOL GameRoot::onDelete() {
    StrBSize_Unload();
    AcreAttr_Unload();
    FtrInfo_Exit();
    ItemInfo_Exit();
    PatternPresetInfo_Close(PatternPresetInfo_Get());
    FgData_Unload(gCurrentHeap);
    TownBlockMap_Destroy(gCurrentHeap);
    HouseRoomMaps_Destroy(gCurrentHeap);
    Comm_DestroyHeap();
    NetSession_Exit();
    return TRUE;
}

BOOL GameRoot::onExecute() {
    Scene_CreateRequested();
    return TRUE;
}

BOOL GameRoot::onDraw() {
    return TRUE;
}


