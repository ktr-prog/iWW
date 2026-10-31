#ifndef PLAYER_PLAYERBODYMODELREF_H
#define PLAYER_PLAYERBODYMODELREF_H

#include "types.h"

extern "C" void PlayerBodyModelRef_Init(u8 *p);
extern "C" void PlayerBodyModelRef_Destruct();
struct PlayerBodyModelRef {
    /* 0x00 */ u8 slot;
    PlayerBodyModelRef() { PlayerBodyModelRef_Init(&slot); }
    ~PlayerBodyModelRef() { PlayerBodyModelRef_Destruct(); }
};

#endif
