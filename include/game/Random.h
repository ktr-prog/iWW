#ifndef GAME_RANDOM_H
#define GAME_RANDOM_H

#include "types.h"

extern "C" void Random_SetSeed(u32 *seed, u32 v);

class Random {
public:
    Random() { Random_SetSeed(&seed, 1); }
    ~Random();

    /* 0x00 */ u32 seed;
};

#endif
