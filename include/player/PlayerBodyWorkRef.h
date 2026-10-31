#ifndef PLAYER_PLAYERBODYWORKREF_H
#define PLAYER_PLAYERBODYWORKREF_H

#include "types.h"

extern "C" void PlayerBodyWorkRef_Destruct(void);
struct PlayerBodyWorkRef {
    /* 0x00 */ u8 slot;
    PlayerBodyWorkRef();
    ~PlayerBodyWorkRef() { PlayerBodyWorkRef_Destruct(); }
};

#endif
