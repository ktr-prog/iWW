#ifndef SAVE_UNK_020942C8_H
#define SAVE_UNK_020942C8_H

#include "types.h"
#include "save/EncodedName8.h"


extern "C" void TownId_Construct();
extern "C" void TownId_Destruct();
class Unk_020942c8 {
public:
    Unk_020942c8() { TownId_Construct(); }
    ~Unk_020942c8() { TownId_Destruct(); }
    /* 0x00 */ u16 townId;
    /* 0x02 */ EncodedName8 townName;
    /* 0x0a */ u16 playerId;
    /* 0x0c */ EncodedName8 playerName;
    /* 0x14 */ s8 gender;
    /* 0x15 */ u8 unk_15;
    BOOL func_020941e8(Unk_020942c8 *o);
};

#endif
