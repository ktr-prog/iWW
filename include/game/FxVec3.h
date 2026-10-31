#ifndef GAME_FXVEC3_H
#define GAME_FXVEC3_H

#include "types.h"
#include "gfx/VecFx32.h"

struct FxVec3 : VecFx32Copy {
    FxVec3() {}
    constexpr FxVec3(s32 a, s32 b, s32 c) : VecFx32Copy(a, b, c) {}
    constexpr FxVec3(s32 v) : VecFx32Copy(v, 0, 0) {}
};

class FxVec3NoCtor : public VecFx32Copy {
};

#endif
