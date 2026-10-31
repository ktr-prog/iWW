#ifndef PLAYER_PLAYERGLASSESMODELREF_H
#define PLAYER_PLAYERGLASSESMODELREF_H

#include "types.h"

extern "C" void PlayerGlassesModelRef_Init(u8 *p);
extern "C" void PlayerGlassesModelRef_Destruct();
struct PlayerGlassesModelRef {
    /* 0x00 */ u8 slot;
    PlayerGlassesModelRef() { PlayerGlassesModelRef_Init(&slot); }
    ~PlayerGlassesModelRef() { PlayerGlassesModelRef_Destruct(); }
};

#endif
