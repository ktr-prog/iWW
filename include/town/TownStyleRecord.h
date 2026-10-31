#ifndef TOWN_TOWNSTYLERECORD_H
#define TOWN_TOWNSTYLERECORD_H

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

class TownStyleRecord {
public:
    TownStyleRecord();
    ~TownStyleRecord();

    /* 0x00 */ u32 houseStyles;
    /* 0x04 */ TownFlag townFlag;
};

#endif
