#ifndef PLAYER_PLAYERWALKTOREQUEST_H
#define PLAYER_PLAYERWALKTOREQUEST_H

#include "types.h"
#include "player/PlayerWalkToArgs.h"

struct PlayerWalkToRequest {
    /* 0x00 */ u32 action;
    /* 0x04 */ u32 priority;
    /* 0x08 */ u32 netSeq;
    /* 0x0c */ PlayerWalkToArgs args;
    /* 0x1c */ u8 pad_1c[4];
};

#endif
