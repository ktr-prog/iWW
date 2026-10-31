#ifndef SAVE_VILLAGERDATA_H
#define SAVE_VILLAGERDATA_H

#include "types.h"
#include "npc/VillagerId.h"
#include "save/TownId.h"
#include "save/Pattern.h"
#include "item/Letter.h"
#include "sys/ClockDateTime.h"

class LetterView;
class PlayerId;
class EncodedString;

struct VillagerMemory {
    u8 player[0x16];
    u8 nickname[8];
    u8 compliment[0x10];
    u8 greeting[0x10];
    u8 unk_3e[2];
    ClockDateTimeWords talkDate;
    TownId town;
    u16 receivedItem;
    s8 friendship;
    u8 impression;
    u8 unk_56[2];
    u32 usedTopicMask;
    s64 townTune;
    struct {
        u16 f0 : 1;
        u16 f1 : 1;
        u16 f2 : 1;
        u16 f3 : 1;
        u16 f4 : 1;
        u16 f5 : 1;
        u16 f6 : 1;
        u16 f7 : 1;
        u16 talkStreak : 3;
        u16 f11 : 1;
        u16 f12 : 1;
        u16 f13 : 1;
        u16 f14 : 1;
        u16 f15 : 1;
    } flags;
    u8 unk_66[2];

    PlayerId *asPlayerId() { return (PlayerId *)player; }

    BOOL hasFortuneGreeting();
    void clearFortuneGreeting();
    void setFortuneGreeting();
    BOOL isFleaMarketVisited();
    void clearFleaMarketVisited();
    void setFleaMarketVisited();
    BOOL isNewYearLetterSent();
    void clearNewYearLetterSent();
    void setNewYearLetterSent();
    BOOL isBirthdayLetterSent();
    void clearBirthdayLetterSent();
    void setBirthdayLetterSent();
    BOOL isPartyGreeted();
    void clearPartyGreeted();
    void setPartyGreeted();
    BOOL isPartyGiftReceived();
    void clearPartyGiftReceived();
    void setPartyGiftReceived();
    BOOL isTalkedToday();
    void clearTalkedToday();
    void setTalkedToday();
    BOOL isGiftGiven();
    void setGiftGiven();
    s32 pickUnusedTopic();
    void setImpression(s32 v);
    u32 getImpression();
    void setTownTune(long long *src);
    BOOL hasTownTune();
    u16 *getReceivedItem();
    void setReceivedItem(u16 *p);
    void setGreeting(void *src, s32 n);
    void getGreetingEncoded(EncodedString *out);
    void getGreeting(void *out);
    BOOL hasGreeting();
    void setCompliment(void *src, s32 n);
    void getComplimentEncoded(EncodedString *out);
    void getCompliment(void *out);
    BOOL hasCompliment();
    void setNickname(void *src, s32 n);
    void setNicknameFromMsg(void *out);
    void getNicknameEncoded(EncodedString *out);
    void getNickname(void *out);
    void setLetterReceived();
    BOOL isLetterReceived();
    s32 addFriendship(s32 d);
    void setFriendship(s8 v);
    s32 getFriendship();
};

class MsgString;

struct VillagerData {
    VillagerMemory memories[8];
    Pattern pattern;
    Letter letter;
    u32 planBlock[0x50 / 4];
    u16 furniture[10];
    VillagerId villagerId;
    u16 receivedItems[4];
    TownId movedFromTown;
    u8 catchphrase[0xa];
    u8 housePos[2];
    u16 shownFurnitureMask;
    u16 shirt;
    u8 wallpaper;
    u8 carpet;
    u8 moveInKind;
    u8 furnitureTasteIndex;
    u8 roomLayout;
    u8 pad_6f3;
    u8 umbrella;
    u8 pad_6f5;
    TownId letterTown;

    s32 receiveLetterFrom(LetterView *letter);
    void getCatchphraseEncoded(EncodedString *p);
    void getCatchphrase(MsgString *p, void *q);
    void clearCatchphrase();
    const void *getInfo28();
    s32 findFreeSlot(s32 n);
    void setUmbrella(u16 *p);
    void setShirt(u16 *p);
    u16 *getShirt();
    BOOL hasLetterSenderMemory();
    s32 findLetterSenderMemory();
    void updateMemoriesFromPlayers();
    void sendNewYearLetters(void *a);
    void sendBirthdayLetters(void *a);
    void replyToLetter(void *a, void *b);
    BOOL hasLetterFrom(u16 *p);
    Letter *getLetter();
    Pattern *getPattern();
    VillagerId *getVillagerId();
    void setup(u32 id, u32 a, void *b, u8 c);
    void copyFrom(void *src);
    void clear();
    ~VillagerData();
    VillagerData();
};

struct OutdoorSchedule {
    s8 order[8];
    s8 outdoorSlots[4];
    ClockDateTimeWords lastReroll;
};

struct SaveVillagers {
      VillagerData villagers[8];
      s8 relations[0x1c];
      OutdoorSchedule outdoorSchedule;
      u8 sickVillager[0x90];
      u8 nicknameDate[4];
      ClockDateTimeWords lastMoveDate;
      ClockDateTimeWords lastMoveOutDate;
      u32 speciesHistory[5];
      s8 lastMovedOutSpecies;
      s8 lastMovedInIndex;
      s8 lastSickIndex;
      u8 unk_38eb;
      struct {
          u16 unk0 : 1;
          u16 tuneRequested : 1;
          u16 tuneRequester : 3;
      } tune;
      u8 furnitureDropDate[4];
      u8 pad_38f2[2];
};

static_assert(sizeof(VillagerMemory) == 0x68, "VillagerMemory: DS save layout");
static_assert(sizeof(VillagerData) == 0x700 && __alignof__(VillagerData) == 4, "VillagerData: DS save layout");
static_assert(__builtin_offsetof(VillagerData, pattern) == 0x340, "VillagerData::pattern");
static_assert(__builtin_offsetof(VillagerData, letter) == 0x568, "VillagerData::letter");
static_assert(__builtin_offsetof(VillagerData, villagerId) == 0x6c0, "VillagerData::villagerId");
static_assert(__builtin_offsetof(VillagerData, catchphrase) == 0x6de, "VillagerData::catchphrase");
static_assert(__builtin_offsetof(VillagerData, shirt) == 0x6ec, "VillagerData::shirt");
static_assert(__builtin_offsetof(VillagerData, umbrella) == 0x6f4, "VillagerData::umbrella");
static_assert(__builtin_offsetof(VillagerData, letterTown) == 0x6f6, "VillagerData::letterTown");
static_assert(__builtin_offsetof(SaveVillagers, nicknameDate) == 0x38c0, "SaveVillagers::nicknameDate");
static_assert(__builtin_offsetof(SaveVillagers, furnitureDropDate) == 0x38ee, "SaveVillagers::furnitureDropDate");
static_assert(sizeof(SaveVillagers) == 0x38f4, "SaveVillagers: SaveData::villagers");

#endif
