#ifndef GFX_SPLEMITTERVIEWS_H
#define GFX_SPLEMITTERVIEWS_H

#include "types.h"

struct Blk14 {
    u16 pad0 : 7;
    u16 k7 : 2;
    u16 pad9 : 7;
    u8 p2[13];
    u8 c15;
};

struct Cbits {
    u16 a : 5;
    u16 b : 5;
    u16 id : 6;
};

struct A3 {
    s32 a[3];
};

struct B4 {
    u8 p0[8];
    u16 b0 : 1;
    u16 pad : 15;
};

struct B8 {
    u8 p0[8];
    u16 b0 : 1;
    u16 b1 : 1;
    u16 pad : 14;
};

struct B12 {
    u8 p0[2];
    u16 pad : 8;
    u16 b8 : 1;
    u16 pad2 : 7;
};

struct B10 {
    u8 p0[8];
    u32 pad : 16;
    u32 b16 : 1;
    u32 b17 : 1;
    u32 pad2 : 14;
};

struct B14 {
    u16 b0 : 1;
    u16 b1 : 1;
    u16 b2 : 1;
    u16 b3 : 1;
    u16 b4 : 1;
    u16 b5 : 1;
    u16 pad : 10;
    u8 p2[11];
    u8 c13;
    u8 c14;
};


struct Node;
struct Res;
struct ResB;
struct SplPt;
struct RU;

struct HdrBits {
    u32 pad0 : 8;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    u32 pad12 : 4;
    u32 b16 : 1;
    u32 pad17 : 7;
    u32 b24 : 1;
    u32 b25 : 1;
    u32 b26 : 1;
    u32 b27 : 1;
    u32 b28 : 1;
    u32 b29 : 1;
    u32 pad30 : 2;
};

struct Hdr20 {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w4;
    /* 0x08 */ u8 p8[0x14];
    /* 0x1c */ u32 w1c;
};

struct HdrW {
    /* 0x00 */ u32 pad0 : 4;
    u32 k4 : 2;
    u32 pad6 : 5;
    u32 b11 : 1;
    u32 pad12 : 4;
    u32 b16 : 1;
    u32 pad17 : 4;
    u32 b21 : 1;
    u32 b22 : 1;
    u32 pad23 : 9;
    /* 0x04 */ u8 p4[0x3f];
    /* 0x43 */ u8 c43;
};

struct H2 {
    /* 0x0 */ u16 a;
    /* 0x2 */ u16 b;
};

struct Em {
#ifdef HOST64
    u8 p0[0x10];
    Node * l8;
    u8 pc[0x8];
    Node * l16;
    u8 p14[0x8];
    Res * res;
#else
    /* 0x00 */ u8 p0[8];
    /* 0x08 */ Node *l8;
    /* 0x0c */ u8 pc[4];
    /* 0x10 */ Node *l16;
    /* 0x14 */ u8 p14[4];
    /* 0x18 */ Res *res;
#endif
};

struct U16x3 {
    u16 v[3];
};

struct EmI {
#ifdef HOST64
    sptr w0;
    sptr w4;
    sptr w8;
    s32 w12;
    u8 hpad_0[0x4];
    sptr w16;
    s32 w20;
    u8 hpad_1[0x4];
    ResB * res;
    s32 w28;
    s32 w32;
    s32 w36;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w52;
    u16 h56;
    u16 h58;
    U16x3 h60;
    u16 h66;
    u32 w68;
    u32 w72;
    u32 w76;
    u32 w80;
    u32 w84;
    u16 h88;
    u16 h90;
    u32 w92;
    s16 s96;
    s16 s98;
    s16 s100;
    s16 s102;
    u32 c104 : 8;
    u32 c105 : 8;
    u32 f16 : 3;
    u32 pad104 : 13;
    u8 p108[0x10];
    uptr w120;
    uptr w124;
    u32 w128;
    u8 hpad_2[0x4];
#else
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w4;
    /* 0x08 */ s32 w8;
    /* 0x0c */ s32 w12;
    /* 0x10 */ s32 w16;
    /* 0x14 */ s32 w20;
    /* 0x18 */ ResB *res;
    /* 0x1c */ s32 w28;
    /* 0x20 */ s32 w32;
    /* 0x24 */ s32 w36;
    /* 0x28 */ s32 w40;
    /* 0x2c */ s32 w44;
    /* 0x30 */ s32 w48;
    /* 0x34 */ s32 w52;
    /* 0x38 */ u16 h56;
    /* 0x3a */ u16 h58;
    /* 0x3c */ U16x3 h60;
    /* 0x42 */ u16 h66;
    /* 0x44 */ u32 w68;
    /* 0x48 */ u32 w72;
    /* 0x4c */ u32 w76;
    /* 0x50 */ u32 w80;
    /* 0x54 */ u32 w84;
    /* 0x58 */ u16 h88;
    /* 0x5a */ u16 h90;
    /* 0x5c */ u32 w92;
    /* 0x60 */ s16 s96;
    /* 0x62 */ s16 s98;
    /* 0x64 */ s16 s100;
    /* 0x66 */ s16 s102;
    /* 0x68 */ u32 c104 : 8;
    u32 c105 : 8;
    u32 f16 : 3;
    u32 pad104 : 13;
    /* 0x6c */ u8 p108[12];
    /* 0x78 */ u32 w120;
    /* 0x7c */ u32 w124;
    /* 0x80 */ u32 w128;
#endif
};

struct HdrU {
    u32 pad0 : 8;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    u32 pad12 : 3;
    u32 b15 : 1;
    u32 b16 : 1;
    u32 pad17 : 13;
    u32 b30 : 1;
    u32 b31 : 1;
};

struct HdrP {
    /* 0x00 */ u8 p0[0x38];
    /* 0x38 */ u16 h56;
    /* 0x3a */ u8 p3a[0x08];
    /* 0x42 */ u8 c66;
};

struct Fi {
    /* 0x0 */ void (*fn)(SplPt *, SplPt *, s32 *, void *);
};

struct EFlags {
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 pad : 27;
};

struct EU {
#ifdef HOST64
    u8 p0[0x10];
    SplPt * l8;
    u8 pc[0x8];
    SplPt * l16;
    u8 p14[0x8];
    RU * res;
    EFlags fl;
    A3 v32;
    s32 w44;
    s32 w48;
    s32 w52;
    u16 h56;
    u8 p3a[0x2e];
    u8 c104;
    u8 p69[0x13];
    void (*cb)(EU *, u32);
#else
    /* 0x00 */ u8 p0[8];
    /* 0x08 */ SplPt *l8;
    /* 0x0c */ u8 pc[4];
    /* 0x10 */ SplPt *l16;
    /* 0x14 */ u8 p14[4];
    /* 0x18 */ RU *res;
    /* 0x1c */ EFlags fl;
    /* 0x20 */ A3 v32;
    /* 0x2c */ s32 w44;
    /* 0x30 */ s32 w48;
    /* 0x34 */ s32 w52;
    /* 0x38 */ u16 h56;
    /* 0x3a */ u8 p3a[0x2e];
    /* 0x68 */ u8 c104;
    /* 0x69 */ u8 p69[0x0f];
    /* 0x78 */ void (*cb)(EU *, u32);
#endif
};

typedef void (*FldFn)(SplPt *, RU *, u32);

struct FEnt {
    /* 0x0 */ FldFn fn;
    /* 0x4 */ u32 arg;
};

#endif
