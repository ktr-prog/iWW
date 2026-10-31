#ifndef GFX_SPLPARTICLEVIEWS_H
#define GFX_SPLPARTICLEVIEWS_H

#include "types.h"

struct Hdr;
struct Tab;
struct SclRec;

struct AnimRec {
    s16 s0, s2, s4;
    u8 t1, t2;
};

struct ColRec {
    u16 c0;
    u16 c2;
    u8 b4, b5, b6, b7;
    u16 f0 : 1;
    u16 f1 : 1;
    u16 f2 : 1;
    u16 frest : 13;
};

struct Col5 {
    u16 r : 5;
    u16 g : 5;
    u16 b : 5;
    u16 x : 1;
};

struct AlphaRec {
    Col5 c;
    u8 b2;
    u8 p3;
    u8 t1, t2;
};

struct Ctx {
    Hdr *hdr;
    AnimRec *rec4;
    ColRec *rec8;
    AlphaRec *recc;
    Tab *rec10;
    SclRec *rec14;
};

struct CollF { s32 y; s16 coef; u16 type : 2; u16 rest : 14; };
struct ConvF { s32 x, y, z; s16 coef; };


struct Fl2e {
    u16 col : 5;
    u16 alpha : 5;
    u16 rest : 6;
};

struct HF {
    u32 type : 4;
    u32 a : 2;
    u32 axis : 2;
    u32 c : 1;
    u32 f9 : 1;
    u32 b10 : 1;
    u32 f11 : 1;
    u32 f12 : 1;
    u32 f13 : 1;
    u32 b14 : 6;
    u32 f20 : 1;
    u32 rest : 11;
};

struct Hdr {
    /* 0x00 */ HF f;
    /* 0x04 */ u8 p4[12];
    /* 0x10 */ s32 rate;
    /* 0x14 */ u8 p14[14];
    /* 0x22 */ u16 col;
    /* 0x24 */ u8 p24[16];
    /* 0x34 */ s16 s34;
    /* 0x36 */ s16 s36;
    /* 0x38 */ u8 p38[4];
    /* 0x3c */ u8 b3c;
    /* 0x3d */ u8 b3d;
    /* 0x3e */ u8 b3e;
    /* 0x3f */ u8 p3f[4];
    /* 0x43 */ u8 b43;
    /* 0x44 */ u8 b44;
};

struct GravF {
    /* 0x0 */ s16 x, y, z;
};

#endif
