#ifndef GFX_SPLNODE_H
#define GFX_SPLNODE_H

#include "types.h"
#include "gfx/SplEmitterViews.h"


struct Node {
#ifdef HOST64
    Node * next;
    u8 p4[0x2c];
    u8 c2c;
    u8 hpad_0[0x3];
#else
    /* 0x00 */ Node *next;
    /* 0x04 */ u8 p4[0x28];
    /* 0x2c */ u8 c2c;
#endif
};

struct Nd {
#ifdef HOST64
    u8 p0[0x10];
    s32 w8;
    s32 w12;
    s32 w16;
    u8 p14[0xc];
    u16 h32;
    u8 p22[0xc];
    Cbits c46;
    s32 w48;
    s16 s52;
    u16 h54;
    s32 w56;
    s32 w60;
    s32 w64;
    u8 hpad_0[0x4];
#else
    /* 0x00 */ u8 p0[8];
    /* 0x08 */ s32 w8;
    /* 0x0c */ s32 w12;
    /* 0x10 */ s32 w16;
    /* 0x14 */ u8 p14[12];
    /* 0x20 */ u16 h32;
    /* 0x22 */ u8 p22[12];
    /* 0x2e */ Cbits c46;
    /* 0x30 */ s32 w48;
    /* 0x34 */ s16 s52;
    /* 0x36 */ u16 h54;
    /* 0x38 */ s32 w56;
    /* 0x3c */ s32 w60;
    /* 0x40 */ s32 w64;
#endif
};

#endif
