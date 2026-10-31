typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
#include "types64.h"
typedef int BOOL;
#define NULL 0

typedef struct P16 { s16 x, y; } P16;
typedef struct P32 { s32 x, y; } P32;

void getScaleData_(s32 *out, u32 f, u32 *ent, u8 *base)
{
    u8 *d;
    u32 info;
    u32 lim, q;
    f = (s32)f >> 12;
    d = base + ent[1];
    info = ent[0];
    if ((info & 0xc0000000) != 0) {
        lim = (info & 0x1fff0000) >> 16;
        if (info & 0x40000000) {
            if (f & 1) {
                if (f > lim) {
                    f = (lim >> 1) + 1;
                    goto fetch;
                }
                q = f >> 1;
                goto avg;
            }
            f = f >> 1;
            goto fetch;
        } else {
            u32 r = f & 3;
            if (r != 0) {
                if (f > lim) {
                    f = (lim >> 2) + r;
                    goto fetch;
                }
                if (f & 1) {
                    s32 v, v_sub;
                    s64 t;
                    u32 ia;
                    if (f & 2) {
                        f = f >> 2;
                        ia = f + 1;
                    } else {
                        ia = f >> 2;
                        f = ia + 1;
                    }
                    if (info & 0x20000000) {
                        P16 *p = (P16 *)d;
                        v = p[ia].x; v_sub = p[f].x;
                        out[0] = (v + (v << 1) + v_sub) >> 2;
                        v = p[ia].y; v_sub = p[f].y;
                        out[1] = (v + (v << 1) + v_sub) >> 2;
                    } else {
                        P32 *p = (P32 *)d;
                        v = p[ia].x; v_sub = p[f].x;
                        t = ((s64)v << 1) + v; out[0] = (s32)((t + v_sub) >> 2);
                        v = p[ia].y; v_sub = p[f].y;
                        t = ((s64)v << 1) + v; out[1] = (s32)((t + v_sub) >> 2);
                    }
                    return;
                }
                q = f >> 2;
                goto avg;
            }
            f = f >> 2;
            goto fetch;
        }
    }
fetch:
    if (info & 0x20000000) {
        P16 *p = (P16 *)d;
        out[0] = p[f].x;
        out[1] = p[f].y;
    } else {
        P32 *p = (P32 *)d;
        out[0] = p[f].x;
        out[1] = p[f].y;
    }
    return;
avg:
    if (info & 0x20000000) {
        P16 *p = (P16 *)d + q;
        out[0] = (p[0].x + p[1].x) >> 1;
        out[1] = (p[0].y + p[1].y) >> 1;
    } else {
        P32 *p = (P32 *)d + q;
        out[0] = (p[0].x + p[1].x) >> 1;
        out[1] = (p[0].y + p[1].y) >> 1;
    }
}
