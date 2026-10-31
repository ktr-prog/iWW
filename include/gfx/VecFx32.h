#ifndef GFX_VECFX32_H
#define GFX_VECFX32_H

#include "types.h"

struct VecFx32 {
    /* 0x0 */ s32 x, y, z;
};

struct VecFx16 {
    /* 0x0 */ s16 x, y, z;
};

struct VecFx32Ctor : VecFx32 {
    VecFx32Ctor() {}
    constexpr VecFx32Ctor(s32 a, s32 b, s32 c) : VecFx32{a, b, c} {}
};

struct VecFx32CtorDtor : VecFx32 {
    VecFx32CtorDtor() {}
    VecFx32CtorDtor(s32 a, s32 b, s32 c) { x = a; y = b; z = c; }
    ~VecFx32CtorDtor() {}
};

struct VecFx32Copy : VecFx32 {
    VecFx32Copy() {}
    constexpr VecFx32Copy(s32 a, s32 b, s32 c) : VecFx32{a, b, c} {}
    constexpr VecFx32Copy(const VecFx32Copy &o) : VecFx32{o.x, o.y, o.z} {}
};

struct VecFx32CopyDtor : VecFx32 {
    VecFx32CopyDtor() {}
    VecFx32CopyDtor(s32 a, s32 b, s32 c) { x = a; y = b; z = c; }
    VecFx32CopyDtor(const VecFx32CopyDtor &o) { x = o.x; y = o.y; z = o.z; }
    ~VecFx32CopyDtor() {}
};

struct Vec2 {
    /* 0x0 */ s32 x, y;
};

struct VecXZ {
    /* 0x0 */ s32 x, z;
};

#endif
