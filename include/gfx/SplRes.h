#ifndef GFX_SPLRES_H
#define GFX_SPLRES_H

#include "types.h"

struct Rh {
    /* 0x00 */ u32 pad0 : 16;
    u32 b16 : 1;
    u32 k17 : 2;
    u32 k19 : 1;
    u32 pad20 : 3;
    u32 b23 : 1;
    u32 pad24 : 8;
    /* 0x04 */ s32 w4;
    /* 0x08 */ s32 w8;
    /* 0x0c */ s32 w12;
    /* 0x10 */ u32 w16;
    /* 0x14 */ u32 w20;
    /* 0x18 */ u32 w24;
    /* 0x1c */ u16 h28;
    /* 0x1e */ u16 h30;
    /* 0x20 */ u16 h32;
    /* 0x22 */ u16 pad34;
    /* 0x24 */ u32 w36;
    /* 0x28 */ u32 w40;
    /* 0x2c */ u32 w44;
    /* 0x30 */ s16 s48;
    /* 0x32 */ u8 p4a[8];
    /* 0x3a */ u16 h58;
    /* 0x3c */ u8 p5c[4];
    /* 0x40 */ u8 c64;
    /* 0x41 */ u8 c65;
    /* 0x42 */ u8 p66[2];
    /* 0x44 */ u32 pad68a : 8;
    u32 k : 16;
    u32 s24 : 2;
    u32 s26 : 2;
    u32 mode : 3;
    u32 pad68b : 1;
    /* 0x48 */ u32 flip0 : 1;
    u32 flip1 : 1;
    u32 pad72 : 30;
    /* 0x4c */ s16 s76;
    /* 0x4e */ s16 s78;
    /* 0x50 */ u8 c80;
};

struct Rb14 {
    /* 0x00 */ u16 pad0 : 9;
    u16 k9 : 2;
    u16 k11 : 1;
    u16 pad12 : 4;
    /* 0x02 */ u8 p2[14];
    /* 0x10 */ u32 s0 : 2;
    u32 s2 : 2;
    u32 fx : 1;
    u32 fy : 1;
    u32 pad : 26;
};

struct ResB {
    /* 0x00 */ Rh *p0;
    /* 0x04 */ void *p4[4];
    /* 0x14 */ Rb14 *p14;
};

#endif
