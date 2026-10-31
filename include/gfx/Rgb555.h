#ifndef GFX_RGB555_H
#define GFX_RGB555_H

#include "types.h"

struct Rgb555 {
    u16 r : 5;
    u16 g : 5;
    u16 b : 5;
    u16 x : 1;
};

#endif
