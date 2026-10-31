#ifndef GAME_CONSTELLATIONRECORD_H
#define GAME_CONSTELLATIONRECORD_H

#include "types.h"

class ConstellationRecord {
public:
    ConstellationRecord();
    ~ConstellationRecord();
    /* 0x00 */ u8 unk_00[0x16];
    /* 0x16 */ u8 name[0x10];
    /* 0x26 */ u16 lines[0x10];
};

#endif
