#ifndef GAME_UNK_0203C92C_BITS_H
#define GAME_UNK_0203C92C_BITS_H

#include "types.h"

struct PlayerOptionBits {
    /* 0x0 */ u8 hiragana : 1;
    u8 stereo : 1;
    u8 talkVoice : 2;
};

struct Unk_0203c92c_Bits1 {
    /* 0x0 */ u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
};

#endif
