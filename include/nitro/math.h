#ifndef NITRO_MATH_H
#define NITRO_MATH_H

#include "types.h"

typedef struct MATHRandContext32 {
    /* 0x00 */ u64 x;
    /* 0x08 */ u64 mul;
    /* 0x10 */ u64 add;
} MATHRandContext32;

#endif
