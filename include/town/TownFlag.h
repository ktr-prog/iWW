#ifndef TOWN_TOWNFLAG_H
#define TOWN_TOWNFLAG_H

#include "types.h"

class TownFlag {
public:
    TownFlag();
    ~TownFlag();
    s32 getGateDesign();
    TownFlag *initDefault();

    /* 0x000 */ u8 pattern[0x228];
    /* 0x228 */ u8 gateDesign;
};

class TownStyleRecordView {
public:
    u8 *getTownFlag();
    void *getHouseStyles();
};

#endif
