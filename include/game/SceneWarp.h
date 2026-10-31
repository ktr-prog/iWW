#ifndef GAME_SCENEWARP_H
#define GAME_SCENEWARP_H

#include "types.h"
#include "gfx/VecFx32.h"

struct SceneWarp {
    SceneWarp();
    constexpr SceneWarp(u8 id, VecFx32Copy v, u32 w, s16 s, u8 p, u8 q, s16 r, u8 t)
        : type(id), flag(0), angle(s), pos{v.x, v.y, v.z}, spawnParam(w), fadeOut(p), fadeIn(q), exitAngle(r),
          exitKind(t) {}

    /* 0x00 */ u8 type;
    /* 0x01 */ u8 flag;
    /* 0x02 */ s16 angle;
    /* 0x04 */ VecFx32 pos;
    /* 0x10 */ u32 spawnParam;
    /* 0x14 */ u8 fadeOut;
    /* 0x15 */ u8 fadeIn;
    /* 0x16 */ s16 exitAngle;
    /* 0x18 */ u8 exitKind;
};

#endif
