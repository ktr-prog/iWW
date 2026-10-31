#ifndef SAVE_TOWNEXCHANGERECORD_H
#define SAVE_TOWNEXCHANGERECORD_H

#include "types.h"

class TownExchangeRecord {
public:
    TownExchangeRecord();
    ~TownExchangeRecord();
    u8 getChecksumByte();
    void setChecksumByte(u32 v);
    void *getVillager();
    void *getConstellation();
    u32 getCounter();
    void resetCounter();
    void incrementCounter();
    void *getLostChildRecord();
    u32 getUnkFlag();
    void setUnkFlag(u32 v);
    s32 isValid();
    u32 getChecksum();
    void setChecksum(u32 v);

    /* 0x000 */ u8 unk_000[0xf4];
    /* 0x0f4 */ u8 constellation[0x48];
    /* 0x13c */ u8 villager[0x700];
    /* 0x83c */ u8 counter;
    /* 0x83d */ u8 flags;
    /* 0x83e */ u8 lostChild[0xc];
    /* 0x84a */ u16 checksum;
};

#endif
