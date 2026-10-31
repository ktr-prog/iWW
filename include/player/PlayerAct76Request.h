#ifndef PLAYER_PLAYERACT76REQUEST_H
#define PLAYER_PLAYERACT76REQUEST_H

#include "types.h"
#include "player/PlayerAct76Args.h"
#include "player/PlayerTurnToWork.h"

struct PlayerAct76Request {
    /* 0x00 */ u32 action;
    /* 0x04 */ u32 priority;
    /* 0x08 */ u32 netSeq;
    /* 0x0c */ PlayerAct76Args args;
};

struct PlayerTurnToRequest {
    /* 0x00 */ u32 action;
    /* 0x04 */ u32 priority;
    /* 0x08 */ u32 netSeq;
    /* 0x0c */ PlayerTurnToArgs args;
    /* 0x0e */ u8 pad_0e[0xe];
};

#endif
