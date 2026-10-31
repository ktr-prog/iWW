#ifndef GAME_BASIS_H
#define GAME_BASIS_H

#include "types.h"
#include "gfx/VecFx32.h"

struct Basis {
    /* 0x00 */ VecFx32 a;
    /* 0x0c */ VecFx32 b;
    /* 0x18 */ VecFx32 c;
};

#endif
