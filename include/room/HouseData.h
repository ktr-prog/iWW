#ifndef ROOM_HOUSEDATA_H
#define ROOM_HOUSEDATA_H

#include "types.h"
#include "room/HouseRoom.h"

struct MapBlockEntry;

class SongSet {
public:
    u8 bits[12];
    SongSet();
    ~SongSet();
    void clear();
};

struct HouseStatus {
    u32 a : 3;
    u32 b : 3;
    u32 c : 4;
    u32 d : 4;
    u32 e : 4;
    u32 f : 6;
    u32 cnt : 8;
};

class HouseData {
public:
    /* 0x0000 */ HouseRoom rooms[5];
    /* 0x1590 */ s32 debt;
    /* 0x1594 */ SongSet songs;
    /* 0x15a0 */ HouseStatus status;

    HouseData();
    ~HouseData();
    BOOL hasRoomFlags();
    BOOL setRoomFlag(u32 x, u32 set);
    BOOL orderUpgrade(u32 v);
    s32 isUpgradePaidOff();
    void startLoan();
    void setDebt(s32 v);
    s32 getDebt();
    void addRoachesForDays(s32 v);
    void setRoachCount(u8 v);
    u8 getRoachCount();
    u16 getRoomAcreId(s32 x);
    BOOL orderRoofPaint(u32 v);
    u8 getRoofColor();
    BOOL requestLevelUp();
    u32 getLevel();
    BOOL isUpgradePending();
    MapBlockEntry *buildRoomBlockEntry(s32 idx, void *heap);
    HouseRoom *getRoom(s32 idx);
    HouseRoom *getRoomForScene(s32 x);
    void resetDebt();
    void applyPendingWork();
    void reset();
};

#endif
