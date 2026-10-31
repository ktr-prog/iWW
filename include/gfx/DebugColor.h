#ifndef GFX_DEBUGCOLOR_H
#define GFX_DEBUGCOLOR_H

#include "types.h"

struct DebugColor {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
    constexpr DebugColor(u8 r_, u8 g_, u8 b_, u8 a_) : r(r_), g(g_), b(b_), a(a_) {}
};

#endif
