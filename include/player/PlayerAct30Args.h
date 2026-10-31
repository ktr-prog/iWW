#ifndef PLAYER_PLAYERACT30ARGS_H
#define PLAYER_PLAYERACT30ARGS_H

#include "types.h"

class Character;


struct PlayerAct30Args {
    /* 0x0 */ u32 kind;
    /* 0x4 */ u8 nextMode;
    /* 0x8 */ u32 variant;
    /* 0xc */ Character *partner;
};

#endif
