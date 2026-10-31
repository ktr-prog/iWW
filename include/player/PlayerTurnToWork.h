#ifndef PLAYER_PLAYERTURNTOWORK_H
#define PLAYER_PLAYERTURNTOWORK_H

#include "types.h"


struct PlayerTurnToWork {
    /* 0x0 */ s16 targetAngle;
    void initTurnTo(s16 v);
};

struct PlayerTurnToArgs {
    /* 0x0 */ s16 targetAngle;
    void setTurnToArgs(s16 v);
};

#endif
