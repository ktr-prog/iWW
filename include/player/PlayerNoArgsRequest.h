#ifndef PLAYER_PLAYERNOARGSREQUEST_H
#define PLAYER_PLAYERNOARGSREQUEST_H

#include "types.h"


struct PlayerNoArgsRequest {
    /* 0x00 */ u32 action;
    /* 0x04 */ u32 priority;
    /* 0x08 */ u32 netSeq;
    /* 0x0c */ u8 pad_0c[0x10];
};

#endif
