#ifndef GFX_SPLVIEWS_H
#define GFX_SPLVIEWS_H

#include "types.h"

struct TexEnt;
struct Em;
struct EmI;

struct Mt {
    /* 0x00 */ s32 m[12];
};

struct Mc {
#ifdef HOST64
    u8 p0[0x40];
    TexEnt * tex;
    u8 p24[0x10];
    Em * cur;
#else
    /* 0x00 */ u8 p0[0x20];
    /* 0x20 */ TexEnt *tex;
    /* 0x24 */ u8 p24[0x10];
    /* 0x34 */ Em *cur;
#endif
};

struct Mg2 {
#ifdef HOST64
    u8 p0[0x54];
    u32 w48;
    EmI * cur;
    Mt * mt;
#else
    /* 0x00 */ u8 p0[0x30];
    /* 0x30 */ u32 w48;
    /* 0x34 */ EmI *cur;
    /* 0x38 */ Mt *mt;
#endif
};

struct ItemU {
#ifdef HOST64
    void * fn;
    void * p4;
#else
    /* 0x0 */ void *fn;
    /* 0x4 */ void *p4;
#endif
};

struct MU {
#ifdef HOST64
    u8 p0[0x28];
    void * freelist;
    u8 p18[0x20];
    u32 b0 : 6;
    u32 b6 : 6;
    u32 b12 : 6;
    u32 b18 : 6;
    u32 pad : 8;
#else
    /* 0x00 */ u8 p0[20];
    /* 0x14 */ void *freelist;
    /* 0x18 */ u8 p18[0x14];
    /* 0x2c */ u32 b0 : 6;
    u32 b6 : 6;
    u32 b12 : 6;
    u32 b18 : 6;
    u32 pad : 8;
#endif
};

#endif
