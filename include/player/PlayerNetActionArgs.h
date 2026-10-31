#ifndef PLAYER_PLAYERNETACTIONARGS_H
#define PLAYER_PLAYERNETACTIONARGS_H

#include "types.h"


class PlayerNetActionArgs {
public:
    void readU16(u16 *out);
    void writeU16(u16 v);
    void readS16(s16 *out);
    void writeS16(s16 v);
    void readAct76Net(u8 *a, u8 *b, u8 *c);
    void writeAct76Net(u8 a, u8 b, u8 c);
    /* 0x00 */ u8 bytes[8];
};

#endif
