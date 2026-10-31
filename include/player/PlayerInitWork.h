#ifndef PLAYER_PLAYERINITWORK_H
#define PLAYER_PLAYERINITWORK_H

#include "types.h"

struct PlayerInitWork {
    /* 0x0 */ u32 firstAction;
    /* 0x4 */ u8 modelSetupDone;
    void initInitWork(u32 v);
};

struct PlayerInitArgs {
    /* 0x0 */ u32 firstAction;
    void setInitArgs(u32 v);
};

#endif
