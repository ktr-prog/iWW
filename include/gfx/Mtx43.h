#ifndef GFX_MTX43_H
#define GFX_MTX43_H

#include "types.h"

struct Mtx43 {
    /* 0x00 */ s32 m[12];
};

struct Mtx43Align8 {
    /* 0x00 */ s64 v[6];
};
#ifndef __cplusplus
typedef struct Mtx43 Mtx43;
typedef struct Mtx43Align8 Mtx43Align8;
#endif

#endif
