#ifndef PLAYER_PLAYERACTIONREQUESTBASE_H
#define PLAYER_PLAYERACTIONREQUESTBASE_H

#include "types.h"

struct PlayerActionRequestBase {
    PlayerActionRequestBase();
    ~PlayerActionRequestBase();
};

struct PlayerActionPayload {
    /* 0x0 */ s32 v[4];
};

#endif
