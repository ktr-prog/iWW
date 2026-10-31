#ifndef GFX_SPLMANAGER_H
#define GFX_SPLMANAGER_H

#include "types.h"

struct TexEnt;
struct HdrP;
struct B4;
struct B8;
struct B10;
struct B12;
struct B14;
struct ItemU;

struct Pm {
    /* 0x00 */ void *(*alloc)(u32);
#ifdef HOST64
    u8 p4[0x38];
    TexEnt * tex;
    u16 h24;
    u16 h26;
#else
    /* 0x04 */ u8 p4[0x1c];
    /* 0x20 */ TexEnt *tex;
    /* 0x24 */ u16 h24;
    /* 0x26 */ u16 h26;
#endif
};

struct PmNew {
    /* 0x00 */ void *(*alloc)(u32);
#ifdef HOST64
    uptr w4;
    u32 w8;
    u8 hpad_0[0x4];
    uptr w12;
    u32 w16;
    u8 hpad_1[0x4];
    uptr w20;
    u32 w24;
    u8 hpad_2[0x4];
    uptr w28;
    uptr w32;
    u16 h36;
    u16 h38;
    u16 h40;
    u16 h42;
    u32 b0 : 6;
    u32 b6 : 6;
    u32 b12 : 6;
    u32 b18 : 6;
    u32 pad24 : 8;
    u32 w48;
#else
    /* 0x04 */ u32 w4;
    /* 0x08 */ u32 w8;
    /* 0x0c */ u32 w12;
    /* 0x10 */ u32 w16;
    /* 0x14 */ u32 w20;
    /* 0x18 */ u32 w24;
    /* 0x1c */ u32 w28;
    /* 0x20 */ u32 w32;
    /* 0x24 */ u16 h36;
    /* 0x26 */ u16 h38;
    /* 0x28 */ u16 h40;
    /* 0x2a */ u16 h42;
    /* 0x2c */ u32 b0 : 6;
    u32 b6 : 6;
    u32 b12 : 6;
    u32 b18 : 6;
    u32 pad24 : 8;
    /* 0x30 */ u32 w48;
#endif
};

struct RU {
#ifdef HOST64
    HdrP * p0;
    B4 * p4;
    B8 * p8;
    B12 * pc;
    B10 * p10;
    B14 * p14;
    ItemU * p18;
    u16 h1c;
    u8 hpad_0[0x6];
#else
    /* 0x00 */ HdrP *p0;
    /* 0x04 */ B4 *p4;
    /* 0x08 */ B8 *p8;
    /* 0x0c */ B12 *pc;
    /* 0x10 */ B10 *p10;
    /* 0x14 */ B14 *p14;
    /* 0x18 */ ItemU *p18;
    /* 0x1c */ u16 h1c;
#endif
};

#endif
