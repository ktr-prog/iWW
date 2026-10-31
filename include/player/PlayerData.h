#ifndef PLAYER_PLAYERDATA_H
#define PLAYER_PLAYERDATA_H

#include "types.h"
#include "item/ItemId.h"
#include "item/Letter.h"
#include "save/Pattern.h"
#include "game/NibblePair.h"
#include "player/PlayerErrands.h"
#include "save/DramaPart.h"

class PlayerId;
class TownId;
struct PlayerBank;
struct Unk_0209865c_Tri {
    u8 lo : 3;
    u8 mid : 3;
    u8 hi : 2;
};

struct Unk_0209865c_Bits {
    u16 a : 7;
    u16 b : 4;
    u16 c : 5;
};

struct Unk_0209865c_Grp {
    Letter a[10];
    u8 gap[0x52];
    ItemId b[15];
};

class PlayerData : public PlayerPatterns {
public:
    PlayerData();
    ~PlayerData();

    /* 0x1148 */ Unk_0209865c_Grp inventory;
    /* 0x1b40 */ u8 wallet[8];
    /* 0x1b48 */ u8 catalog[0x123];
    /* 0x1c6b */ u8 options[1];
    /* 0x1c6c */ u8 futureLetter[0xf8];
    /* 0x1d64 */ PlayerErrands errands;
    /* 0x1e10 */ u8 wifiUserData[0x50];
    /* 0x1e60 */ u8 friendList[0x384];
    /* 0x21e4 */ u8 bank[8];
    /* 0x21ec */ u8 emotions[4];
    /* 0x21f0 */ u8 dailyTalkFlags[0xc];
    /* 0x21fc */ u32 flags[2];
    /* 0x2204 */ u8 dayUpdateDate[4];
    /* 0x2208 */ u8 nookPoints[2];
    /* 0x220a */ u16 heldItem;
    /* 0x220c */ u16 shirt;
    /* 0x220e */ u16 hat;
    /* 0x2210 */ u16 faceItem;
    /* 0x2212 */ u16 bed;
    /* 0x2214 */ u16 inventoryBackground;
    /* 0x2216 */ s16 lastPlayDate;
    /* 0x2218 */ u8 birthday[2];
    /* 0x221a */ u8 spNpcRecord[0x11];
    /* 0x222b */ DramaRecord dramaRecord;
    /* 0x2230 */ u8 lostChildRecord[0xc];
    /* 0x223c */ NibblePair faceHair;
    /* 0x223d */ Unk_0209865c_Tri hairColorTanFortune;
    /* 0x223e */ u8 motherLetterState[0x13];
    /* 0x2251 */ u8 arbeitTalkCount;
    /* 0x2252 */ u8 skyShotHits;
    /* 0x2253 */ u8 birthdayTalkYear;
    /* 0x2254 */ u8 birthdayNoticeDays[8];
    /* 0x225c */ u8 foreignVillagerRecord[0x1a];
    /* 0x2276 */ u8 id[0x16];

    PlayerErrands *getErrands();
    void *getOptions();
    void *getFriendList();
    void *getWifiUserData();
    void *getSpNpcRecord();
    void *getDailyTalkFlags();
    void *getLostChildRecord();
    DramaRecord *getDramaRecord();
    void *getNookPoints();
    u8 *getCatalog();
    void *getPatterns();
    void setBed(u16 *v);
    u16 *getBed();
    void setFaceItem(u16 *v);
    u16 *getFaceItem();
    void setHat(u16 *v);
    u16 *getHat();
    void setShirt(u16 *v);
    u16 *getShirt();
    void setHeldItem(u16 *v);
    u16 *getHeldItem();
    void *getInventory();
    void setFortune(u8 v);
    u32 getFortune();
    void setLastPlayDate(Unk_0209865c_Bits v);
    s32 getLastPlayDate();
    void setTan(u8 v);
    u32 getTan();
    void setHairColor(u8 v);
    u32 getHairColor();
    void setHairStyle(u8 v);
    u32 getHairStyle();
    void setFaceType(u8 v);
    u32 getFaceType();
    s32 getIndex();
    void setupNew(void *name, u32 p2, u32 p3, TownId *town, u8 s1, u8 s2, u8 s3, u8 s4, u8 s5, u32 s6, u16 *s7);
    BOOL isUsed();
    void reset();
    void fillZero();
    PlayerId *getPlayerId();
    void clearFlag(u32 bit);
    void setFlag(u32 bit);
    BOOL testFlag(u32 bit);
    void sendForeignVillagerLetter();
    void *getForeignVillagerRecord();
    void setBirthdayNoticeDay(u32 idx, u32 v);
    u32 getBirthdayNoticeDay(u32 idx);
    void setSkyShotHits(u32 v);
    u32 getSkyShotHits();
    void advanceArbeitTalkCount();
    u32 getArbeitTalkCount();
    u32 getBirthdayTalkYear();
    void setBirthdayTalkYear(u32 v);
    void clearBirthday();
    void setBirthday(u32 a, u32 b);
    u8 *getBirthday();
    u8 *getEmotions();
    PlayerBank *getBankAccount();
    u8 *getDayUpdateDate();
    s32 findUnusedSlot(s32 n);
    BOOL getOtherResidentName(void *p);
    PlayerData *pickOtherResident();
    void setInventoryBackground(u16 *p);
    void *getInventoryBackground();
    void resetForNewTown();
    void rerollFlaggedPocketItems();
};

static_assert(sizeof(Unk_0209865c_Grp) == 0x9f8, "PlayerData::inventory");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
static_assert(sizeof(PlayerData) == 0x228c && __alignof__(PlayerData) == 4, "PlayerData: DS save layout");
static_assert(__builtin_offsetof(PlayerData, inventory) == 0x1148, "PlayerData::inventory");
static_assert(__builtin_offsetof(PlayerData, wallet) == 0x1b40, "PlayerData::wallet");
static_assert(__builtin_offsetof(PlayerData, futureLetter) == 0x1c6c, "PlayerData::futureLetter");
static_assert(__builtin_offsetof(PlayerData, errands) == 0x1d64, "PlayerData::errands");
static_assert(__builtin_offsetof(PlayerData, flags) == 0x21fc, "PlayerData::flags");
static_assert(__builtin_offsetof(PlayerData, heldItem) == 0x220a, "PlayerData::heldItem");
static_assert(__builtin_offsetof(PlayerData, faceHair) == 0x223c, "PlayerData::faceHair");
static_assert(__builtin_offsetof(PlayerData, id) == 0x2276, "PlayerData::id");
#pragma GCC diagnostic pop

#endif
