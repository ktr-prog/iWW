#ifndef ROOM_ROOMFTRSTATE_H
#define ROOM_ROOMFTRSTATE_H

#include "types.h"
#include "game/NibblePair.h"

class FtrSwitchGrid {
public:
    /* 0x00 */ u16 rows[16];
    FtrSwitchGrid();
    ~FtrSwitchGrid();
    void set(u32 x, u32 y, u32 set);
    BOOL test(u32 x, u32 y);
    void reset();
};


class GyroidBeatTable {
public:
    /* 0x0 */ NibblePair positions[4];
    /* 0x4 */ u8 usedMask[1];
    /* 0x5 */ u8 beats[2];
    GyroidBeatTable();
    ~GyroidBeatTable();
    BOOL set(u32 x, u32 y, u32 val);
    BOOL remove(u32 x, u32 y);
    s32 get(u32 x, u32 y);
    void clear();
};

class RoomFtrState {
public:
    /* 0x00 */ FtrSwitchGrid switchGrids[2];
    /* 0x40 */ GyroidBeatTable gyroidBeats;
    RoomFtrState();
    ~RoomFtrState();
    BOOL removeGyroidBeat(u32 a, u32 b);
    BOOL setGyroidBeat(u32 a, u32 b, u32 c);
    s32 getGyroidBeat(u32 a, u32 b);
    void setSwitch(u32 x, u32 y, u32 idx, u8 v);
    BOOL getSwitch(u32 x, u32 y, u32 idx);
    void reset();
};

#endif
