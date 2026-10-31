#ifndef GFX_EFFECTSLOT_H
#define GFX_EFFECTSLOT_H

#include "types.h"
#include "gfx/VecFx32.h"


class EffectSlot {
public:
    void clear();
    void set(s32 id, u32 type, VecFx32 *pos, s16 *a, s16 *b, s16 v);

    union {
        struct {
            /* 0x00 */ s32 x;
            /* 0x04 */ s32 y;
            /* 0x08 */ s32 z;
        };
        /* 0x00 */ VecFx32 pos;
    };
    /* 0x0c */ s16 angle;
    /* 0x0e */ s16 life;
    /* 0x10 */ s16 param;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s32 handle;
    /* 0x18 */ u16 kind;
    /* 0x1a */ u16 unk_1a;
};

#endif
