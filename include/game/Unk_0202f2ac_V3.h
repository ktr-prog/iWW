#ifndef GAME_UNK_0202F2AC_V3_H
#define GAME_UNK_0202F2AC_V3_H

#include "types.h"
#include "gfx/VecFx32.h"

struct Unk_0202f2ac_V3 : VecFx32 {
    Unk_0202f2ac_V3() {}
    Unk_0202f2ac_V3(s32 c, s32 a) { x = a; y = 0; z = c; }
    Unk_0202f2ac_V3(s32 a, s32 b, s32 c) { x = a; y = b; z = c; }
};

#endif
