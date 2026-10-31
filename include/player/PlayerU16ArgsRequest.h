#ifndef PLAYER_PLAYERU16ARGSREQUEST_H
#define PLAYER_PLAYERU16ARGSREQUEST_H

#include "types.h"


struct PlayerU16ArgsRequest {
    /* 0x00 */ u32 action;
    /* 0x04 */ u32 priority;
    /* 0x08 */ u16 netSeq;
    /* 0x0a */ u16 unk_0a;
    /* 0x0c */ u16 args;
    /* 0x0e */ u8 unk_0e[0x0e];
};

struct PlayerU8ArgsRequest {
    /* 0x00 */ u32 action;
    /* 0x04 */ u32 priority;
    /* 0x08 */ u16 netSeq;
    /* 0x0a */ u16 unk_0a;
    /* 0x0c */ u8 args;
    /* 0x0d */ u8 unk_0d[0x0f];
};

#endif
