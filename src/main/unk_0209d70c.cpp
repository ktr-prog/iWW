#include "uptr.h"
#include "types.h"
#include "save/SaveData.h"
#include "save/VillagerData.h"
#include "player/PlayerData.h"
#include "item/BottleLetterRecord.h"
#include "game/NookShop.h"
#include "game/ReddShop.h"
#include "item/LetterOutbox.h"
#include "item/ReceivedLetterBlock.h"
#include "room/HouseData.h"
#include "save/BbsBoard.h"
#include "save/BlancaFaceRecord.h"
#include "save/ContestRecord.h"
#include "save/MuseumData.h"
#include "save/Pattern.h"
#include "save/SaveRecord4.h"
#include "save/TownExchangeRecord.h"
#include "town/TownMap.h"
#include "town/TownStyleRecord.h"
#include "save/SnowmanRecords.h"
#include "game/ConstellationStore.h"
#include "game/ReddLastSale.h"
#include "item/ItemClassOrders.h"
#include "item/PlayerMailbox.h"
#include "sys/ClockOffset.h"
#include "proto/main/unk_02039b6c.h"
#include "proto/main/unk_02039c08.h"
#include "proto/main/unk_0204c318.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02096c10.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209d70c.h"
#include "proto/main/unk_0209e394.h"
#include "proto/main/unk_020c00c0.h"

extern "C" {
void ClockOffset_Clear(ClockOffset *t);
s32 ClockOffset_CalcMinutes(void *unused, u64 *b);
s32 ClockOffset_CalcSeconds(void *unused, u8 *b);
void Clock_Init();
void MI_CpuCopy8(const void *src, void *dst, u32 size);
void HappyRoomDate_Construct();
u8 *SaveVillagers_Construct(u8 *self);
void *AbleShop_Construct(void *p);
}

static_assert(sizeof(((SaveData *)0)->players) == 4 * sizeof(PlayerData), "SaveData::players: PlayerData[4]");
static_assert(sizeof(((SaveData *)0)->villagers) == sizeof(SaveVillagers), "SaveData::villagers: SaveVillagers");
static_assert(sizeof(((SaveData *)0)->mailboxes[0]) == sizeof(PlayerMailbox), "SaveData::mailboxes: PlayerMailbox");
static_assert(sizeof(((SaveData *)0)->letterOutbox) == sizeof(LetterOutbox), "SaveData::letterOutbox");
static_assert(sizeof(((SaveData *)0)->bottleLetter) == sizeof(BottleLetterRecord), "SaveData::bottleLetter");
static_assert(sizeof(TownMap) <= sizeof(((SaveData *)0)->townMap), "TownMap");
static_assert(sizeof(ConstellationStore) <= sizeof(((SaveData *)0)->constellations), "ConstellationStore");
static_assert(sizeof(TownStyleRecord) <= sizeof(((SaveData *)0)->townStyle), "TownStyleRecord");
static_assert(sizeof(ReddLastSale) <= sizeof(((SaveData *)0)->reddLastSale), "ReddLastSale");
static_assert(sizeof(SnowmanRecords) <= sizeof(((SaveData *)0)->snowmen), "SnowmanRecords");
static_assert(sizeof(ItemClassOrders) <= sizeof(((SaveData *)0)->itemClassOrders), "ItemClassOrders");
static_assert(sizeof(ClockOffset) <= sizeof(((SaveData *)0)->clockOffset), "ClockOffset");
static_assert(sizeof(HouseData) <= sizeof(((SaveData *)0)->house), "HouseData");
static_assert(sizeof(BbsBoard) <= sizeof(((SaveData *)0)->bbsBoard), "BbsBoard");
static_assert(sizeof(NookShop) <= sizeof(((SaveData *)0)->nookShop), "NookShop");
static_assert(sizeof(ReddShop) <= sizeof(((SaveData *)0)->reddShop), "ReddShop");

inline SaveData::SaveData() {
    TownId_Construct();
    PlayerDataArray_Construct(players);
    SaveVillagers_Construct(villagers);
    new (townMap) TownMap();
    GulliverQuest_Construct();
    RoostGuestRoll_Construct();
    new (house) HouseData();
    new (ableSistersPatterns) AbleSistersPatterns();
    new (townExchange) TownExchangeRecord();
    new (bbsBoard) BbsBoard();
    for (s32 i = 0; i < 4; i++) {
        new (mailboxes[i]) PlayerMailbox();
    }
    new (letterOutbox) LetterOutbox();
    new (constellations) ConstellationStore();
    for (s32 i = 0; i < 4; i++) {
        ChestStorage_Construct();
    }
    ((BlancaFaceRecord *)blancaFace)->construct();
    new (townStyle) TownStyleRecord();
    BottleLetterRecord_Construct((Letter *)bottleLetter);
    new (receivedLetters) ReceivedLetterBlock();
    ((MuseumData *)museum)->construct();
    new (nookShop) NookShop();
    EventWeekSlots_Construct(eventWeekSlots);
    TownState_Construct();
    LostAndFound_Construct();
    RecycleBin_Construct();
    ((ContestRecord *)contestRecord)->construct();
    new (reddLastSale) ReddLastSale();
    TurnipMarket_Construct();
    Weather_Construct();
    new (reddShop) ReddShop();
    AbleShop_Construct(ableShop);
    new (snowmen) SnowmanRecords();
    HappyRoomDate_Construct();
    new (itemClassOrders) ItemClassOrders();
    SaveData_ConstructDateRecord();
    LostChildRecord_Construct(lostChild);
    footer.construct();
}

SaveData gSaveData;

typedef void (SaveData::*Unk_0209d70c_Fn)();


extern "C" void SaveData_SyncClockOffset(SaveData *p) {
    ClockOffset *offset = (ClockOffset *)p->clockOffset;
    u64 a;
    u64 b;
    u64 c;
    ClockOffset_Clear(offset);
    a = 0;
    MenuCtrl_GetDateTime(&a);
    MI_CpuCopy8(&a, &b, 8);
    s32 minutes = ClockOffset_CalcMinutes(offset, &b);
    MI_CpuCopy8(&a, &c, 8);
    u16 seconds = ClockOffset_CalcSeconds(offset, (u8 *)&c);
    offset->minutes = minutes;
    offset->seconds = seconds;
    Clock_Init();
}

extern "C" void SaveData_Setup(SaveData *p, u32 idx) {
    static Unk_0209d70c_Fn tbl[7] = {&SaveData::setupNewTown, &SaveData::setupNewResident,
                                     &SaveData::setupContinue, &SaveData::setupNoSave,
                                     &SaveData::setupLoaded, &SaveData::setupMode05,
                                     &SaveData::setupMode06};
    (p->*tbl[idx])();
}

#include "host_labels.h"

HOST_LABEL_DEFINE(data_021e5890, (char *)&gSaveData.townMap[8720]);
HOST_LABEL_DEFINE(data_021e58a6, (char *)&gSaveData.gulliverQuest[0]);
HOST_LABEL_DEFINE(data_021e58a7, (char *)&gSaveData.roostGuestRoll[0]);
HOST_LABEL_DEFINE(data_021e7f8c, (char *)&gSaveData.townExchange[0]);
HOST_LABEL_DEFINE(data_021e87d8, (char *)&gSaveData.bbsBoard[0]);
HOST_LABEL_DEFINE(data_021e935c, (char *)&gSaveData.mailboxes[0]);
HOST_LABEL_DEFINE(data_021eb98c, (char *)&gSaveData.letterOutbox[0]);
HOST_LABEL_DEFINE(data_021ec31c, (char *)&gSaveData.constellations[0]);
HOST_LABEL_DEFINE(data_021eceac, (char *)&gSaveData.bottleLetter[0]);
HOST_LABEL_DEFINE(data_021ecfa8, (char *)&gSaveData.receivedLetters[0]);
HOST_LABEL_DEFINE(data_021ed0a0, (char *)&gSaveData.museum[0]);
HOST_LABEL_DEFINE(data_021ed104, (char *)&gSaveData.nookShop[0]);
HOST_LABEL_DEFINE(data_021ed150, (char *)&gSaveData.nookShop[0x4c]);
HOST_LABEL_DEFINE(data_021ed170, (char *)&gSaveData.unk_15e20[0]);
HOST_LABEL_DEFINE(data_021ed174, (char *)&gSaveData.unk_15e24[0]);
HOST_LABEL_DEFINE(data_021ed1b0, (char *)&gSaveData.townState.unk_0c[0]);
HOST_LABEL_DEFINE(data_021ed20c, (char *)&gSaveData.townState.unk_68);
HOST_LABEL_DEFINE(data_021ed284, (char *)&gSaveData.reddLastSale[0]);
HOST_LABEL_DEFINE(data_021ed29c, (char *)&gSaveData.turnipMarket[0]);
HOST_LABEL_DEFINE(data_021ed2b0, (char *)&gSaveData.turnipMarket[20]);
HOST_LABEL_DEFINE(data_021ed2c0, (char *)&gSaveData.reddShop[0]);
HOST_LABEL_DEFINE(data_021ed2d4, (char *)&gSaveData.ableShop[0]);
HOST_LABEL_DEFINE(data_021ed2e6, (char *)&gSaveData.snowmen[0]);
HOST_LABEL_DEFINE(data_021ed304, (char *)&gSaveData.clockOffset[0]);
HOST_LABEL_DEFINE(data_021ed30c, (char *)&gSaveData.itemClassOrders[0]);
HOST_LABEL_DEFINE(gContestRecord, (char *)&gSaveData.contestRecord[0]);
HOST_LABEL_DEFINE(gSaveAbleSistersPatterns, (char *)&gSaveData.ableSistersPatterns[0]);
HOST_LABEL_DEFINE(gSaveBlancaFace, (char *)&gSaveData.blancaFace[0]);
HOST_LABEL_DEFINE(gSaveEventWeekSlots, (char *)&gSaveData.eventWeekSlots[0]);
HOST_LABEL_DEFINE(gSaveFooter, (char *)&gSaveData.footer.unk_00);
HOST_LABEL_DEFINE(gSaveHappyRoomDate, (char *)&gSaveData.happyRoomDate[0]);
HOST_LABEL_DEFINE(gSaveHouse, (char *)&gSaveData.house[0]);
HOST_LABEL_DEFINE(gSaveLostAndFound, (char *)&gSaveData.lostAndFound[0]);
HOST_LABEL_DEFINE(gSavePlayers, (char *)&gSaveData.players[0]);
HOST_LABEL_DEFINE(gSaveRecycleBin, (char *)&gSaveData.recycleBin[0]);
HOST_LABEL_DEFINE(gSaveTownEventDate, (char *)&gSaveData.townState.eventUpdateDay);
HOST_LABEL_DEFINE(gSaveTownEvents, (char *)&gSaveData.townState.events[0]);
HOST_LABEL_DEFINE(gSaveTownFlag, (char *)&gSaveData.townStyle[0]);
HOST_LABEL_DEFINE(gSaveTownId, (char *)&gSaveData.townId[0]);
HOST_LABEL_DEFINE(gSaveTownMap, (char *)&gSaveData.townMap[0]);
HOST_LABEL_DEFINE(gSaveTownState, (char *)&gSaveData.townState.lastUpdate.day);
HOST_LABEL_DEFINE(gSaveTownTune, (char *)&gSaveData.townTune);
HOST_LABEL_DEFINE(gSaveVillagers, (char *)&gSaveData.villagers[0]);
