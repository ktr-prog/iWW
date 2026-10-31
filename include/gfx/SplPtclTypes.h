#ifndef GFX_SPLPTCLTYPES_H
#define GFX_SPLPTCLTYPES_H

#include "types.h"

struct P;

struct PList {
    /* 0x0 */ P *head;
    /* 0x4 */ s32 count;
};

struct SclRec {
    /* 0x0 */ u8 p0[4];
    /* 0x4 */ s16 sc;
};

struct RandF {
    /* 0x0 */ s16 x, y, z;
    /* 0x6 */ u16 intv;
};

struct SpinF {
    /* 0x0 */ u16 angle;
    /* 0x2 */ u16 axis;
};

#endif
