#ifndef PLAYER_PLAYERACT30REQUEST_H
#define PLAYER_PLAYERACT30REQUEST_H

#include "types.h"
#include "player/PlayerAct30Args.h"


struct PlayerAct30Request {
    /* 0x00 */ u8 pad_00[0xc];
    /* 0x0c */ PlayerAct30Args args;
};

#endif
