#ifndef GAME_UNK_02034014_H
#define GAME_UNK_02034014_H

#include "types.h"

class Unk_02034014 {
public:
    Unk_02034014();
    ~Unk_02034014();
    void setDefaults();
    void setEntry(u32 i, s16 a, s16 b);
    void clear();

    /* 0x00 */ s16 unk_00[3];
    /* 0x06 */ s16 unk_06[3];
    /* 0x0c */ s16 unk_0c[3];
    /* 0x12 */ u8 unk_12;
};

#endif
