#include "types.h"
#include "save/SaveData.h"
#include "save/TownId.h"
#include "game/ReddShop.h"
#include "player/PlayerData.h"
#include "player/PlayerSpNpcRecord.h"
#include "room/HouseData.h"
#include "save/BbsBoard.h"
#include "save/BlancaFaceRecord.h"
#include "save/ContestRecord.h"
#include "save/LostChildRecord.h"
#include "save/Pattern.h"
#include "save/SaveRecord4.h"
#include "town/TownBlockMap.h"
#include "town/TownMap.h"
#include "town/ResettiVisitFlag.h"
#include "game/TurnipMarket.h"
#include "item/ItemClassOrders.h"
#include "field/LooseSnowballs.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_02039c08.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206d988.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02097d1c.h"
#include "proto/main/unk_0209c4a8.h"
#include "proto/main/unk_0209d81c.h"
#include "proto/main/unk_020af3f4.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/main/unk_0204cc1c.h"

extern "C" {
void SaveData_SyncClockOffset(SaveData *p);
void TownState_InitNew(void *);
void Town_ClearBorderTrees(void *);
void FengShui_UpdateHouse(void);
void HappyRoomDate_Reset(void *);
void VillagerStates_SetBirthdayVisitor(s32);
void SaveVillagers_UpdateAllRoomInfo(void *);
void SaveVillagers_AssignErrands(void *);
void VillagerStates_ResetErrands(void);
void SaveVillagers_PlaceMissingHouses(void *);
void SaveVillagers_DailyUpdate(void *, s32);
void SaveVillagers_UpdateOutdoor(void *, s32);
void SaveVillagers_InitNewTown(void *);
void ReddLastSale_Clear(void *);
s32 ClockOffset_Clear(void *p);
void Clock_GetDate(void *p);
void Clock_Init(void);
void AbleShop_InitNew(void *);
void NookShop_InitNew(void *);
void Weather_RerollRainSlantAlt();
void Weather_RerollRainSlantAlt2();
void Weather_InitNew(void *);
extern u8 gSaveData[];
}

u8 sFallbackTownName[8] = {0x13, 0x1b, 0x30, 0x1b, 0x0e, 0x29, 0x28, 0x1f};


void SaveData::setupNoSave() {
    ClockOffset_Clear(&clockOffset);
    Clock_Init();
    TownMap_Generate((TownMap *)townMap, gCurrentHeap);
    SaveData_RefreshTownBlockMap(this);
    TownId_InitWithName((u16 *)townId, sFallbackTownName);
    SaveData_InitNew((u8 *)this);
    LooseSnowballs_Get()->reset();
    ((TownMap *)townMap)->updateGroundSeason();
    VillagerStates_SetBirthdayVisitor(-1);
    SaveVillagers_UpdateOutdoor(&villagers, 0);
    ((SaveRecord4 *)(&footer))->clearState();
    Weather_RerollRainSlantAlt();
    TownSessionState_GetResettiFlag(TownSessionState_Get())->clear();
}

void SaveData::setupLoaded() {
    SaveData_RefreshTownBlockMap(this);
    HouseRoomMaps_UpdateAll();
    HouseRoomMaps_BindBg();
    Clock_Init();
    SaveVillagers_DailyUpdate(&villagers, 1);
    SaveVillagers_PlaceMissingHouses(&villagers);
    VillagerStates_SetBirthdayVisitor(-1);
    SaveVillagers_UpdateOutdoor(&villagers, 1);
    Weather_RerollRainSlantAlt2();
    TownSessionState_GetResettiFlag(TownSessionState_Get())->clear();
    s32 z, i;
    u8 *p = gSaveData;
    i = 0;
    z = i;
    p += 0xc;
    for (; i < 4; i++) {
        void *x = PlayerData_GetResident(p, i);
        if (x) PlayerData_SetStungFace(x, z);
    }
}

void SaveData::setupMode05() {
    void *a = PlayerData_GetCurrent();
    SaveData_RefreshTownBlockMap(this);
    HouseRoomMaps_UpdateAll();
    HouseRoomMaps_BindBg();
    Clock_Init();
    SaveData_InitCurrentPlayer((u8 *)this);
    ((PlayerData *)(a))->setFlag(1);
    ((PlayerData *)(a))->setFlag(0x23);
    ((PlayerData *)(a))->clearFlag(9);
    SaveVillagers_DailyUpdate(&villagers, 0);
    SaveVillagers_PlaceMissingHouses(&villagers);
    VillagerStates_ResetErrands();
    SaveVillagers_AssignErrands(&villagers);
    LooseSnowballs_Get()->reset();
    ((TownMap *)townMap)->updateGroundSeason();
    RoomEntry_Reset();
    ((PlayerData *)(a))->setSkyShotHits(0);
    VillagerStates_SetBirthdayVisitor(-1);
    SaveVillagers_UpdateOutdoor(&villagers, 1);
    TownSessionState_GetResettiFlag(TownSessionState_Get())->clear();
    SaveVillagers_UpdateAllRoomInfo(&villagers);
}

void SaveData::setupMode06() {
    void *a = PlayerData_GetCurrent();
    SaveData_SyncClockOffset(this);
    TownMap_Generate((TownMap *)townMap, gCurrentHeap);
    SaveData_RefreshTownBlockMap(this);
    ((SaveRecord4 *)(&unk_15fc5))->setDateToday((void *)(0));
    SaveData_InitCurrentPlayer((u8 *)this);
    SaveData_InitNew((u8 *)this);
    LooseSnowballs_Get()->reset();
    ((TownMap *)townMap)->updateGroundSeason();
    RoomEntry_Reset();
    ((PlayerData *)(a))->setFlag(1);
    ((PlayerData *)(a))->setFlag(0x23);
    ((PlayerData *)(a))->clearFlag(9);
    VillagerStates_SetBirthdayVisitor(-1);
    SaveVillagers_UpdateOutdoor(&villagers, 1);
    TownSessionState_GetResettiFlag(TownSessionState_Get())->clear();
    SaveVillagers_UpdateAllRoomInfo(&villagers);
}

void SaveData_InitCurrentPlayer(u8 *p) {
    void *r4 = PlayerData_GetCurrent();
    TownId l;
    l = *(TownId *)PlayerId_GetTownId(((PlayerData *)(r4))->getPlayerId());
    Clock_GetDate(((PlayerData *)(r4))->getDayUpdateDate());
    ((TownId *)(((PlayerData *)(r4))->getPlayerId()))->setTown((TownId *)((SaveData *)p)->townId);
    void *r5 = ((PlayerData *)(r4))->getPatterns();
    ((PlayerPatterns *)(r5))->replaceAuthorTown((Unk_020942c8 *)(((PlayerData *)(r4))->getPlayerId()), (Unk_020942c8 *)(&l));
    ((PlayerData *)(r4))->clearFlag(0x24);
    ((PlayerData *)(r4))->clearFlag(0x25);
    ((PlayerData *)(r4))->clearFlag(0x26);
    ((PlayerSpNpcRecord *)(((PlayerData *)(r4))->getSpNpcRecord()))->resetAcornCount();
    ((PlayerData *)(r4))->clearFlag(0xf);
    ((PlayerSpNpcRecord *)(((PlayerData *)(r4))->getSpNpcRecord()))->clearFestivalGift();
    ((LostChildRecord *)(((PlayerData *)(r4))->getLostChildRecord()))->clear();
    ((PlayerData *)(r4))->resetForNewTown();
    TownId_Destruct();
}

void SaveData_InitNew(u8 *p) {
    SaveData *d = (SaveData *)p;
    p[0] = 0x8a;
    (&d->footer)->setStateValid();
    SaveVillagers_InitNewTown(d->villagers);
    SaveVillagers_PlaceMissingHouses(d->villagers);
    VillagerStates_ResetErrands();
    if (PlayerData_GetCurrent()) {
        SaveVillagers_AssignErrands(d->villagers);
    }
    TownStyleRecord_InitNew(d->townStyle);
    ((HouseData *)d->house)->resetDebt();
    HouseRoomMaps_UpdateAll();
    HouseRoomMaps_BindBg();
    ((AbleSistersPatterns *)d->ableSistersPatterns)->initDefaultPatterns();
    FengShui_UpdateHouse();
    ((ItemClassOrders *)d->itemClassOrders)->randomizeAll();
    ((BbsBoard *)d->bbsBoard)->reset();
    NookShop_InitNew(d->nookShop);
    AbleShop_InitNew(d->ableShop);
    ((ReddShop *)d->reddShop)->reset();
    TownState_InitNew(&d->townState);
    Weather_InitNew(&d->weather);
    EventWeekSlots_InitNew(d->eventWeekSlots);
    ((BlancaFaceRecord *)d->blancaFace)->init();
    ((TurnipMarket *)d->turnipMarket)->init();
    ReddLastSale_Clear(d->reddLastSale);
    GulliverQuest_Init(d->gulliverQuest);
    ((ContestRecord *)d->contestRecord)->resetToday();
    HappyRoomDate_Reset(d->happyRoomDate);
    Melody_ResetToDefault();
    LostAndFound_InitRandom((u16 *)d->lostAndFound);
    RoostGuestRoll_Init(d->roostGuestRoll);
    TownExchange_InitNop();
}

void SaveData_RefreshTownBlockMap(void *) {
    if (TownBlockMap_Get()) {
        ((TownBlockMap *)(TownBlockMap_Get()))->updateAcreIds();
        ((TownBlockMap *)(TownBlockMap_Get()))->bindBg();
        Town_ClearBorderTrees(TownBlockMap_Get());
    }
}

