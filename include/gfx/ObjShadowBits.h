#ifndef GFX_OBJSHADOWBITS_H
#define GFX_OBJSHADOWBITS_H

#include "types.h"

struct RGB {
    u16 r : 5;
    u16 g : 5;
    u16 b : 5;
    u16 a : 1;
};

struct Pack {
    u32 a : 6;
    u32 b : 19;
    u32 c : 1;
    u32 d : 6;
};

#endif
