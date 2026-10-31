typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
#include "types64.h"
#include "host_labels.h"
typedef int BOOL;
#define NULL 0

#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_02104000.h"
#include "proto/autoload_2/unk_02106f90.h"

extern G3dRS *data_021f5cc0;
extern const u8 data_02135e5c[9][4];
#define data_02135e5d HOST_LABEL(const u8 (*)[][4], data_02135e5d)
#define data_02135e5e HOST_LABEL(const u8 (*)[][4], data_02135e5e)
#define data_02135e5f HOST_LABEL(const u8 (*)[][4], data_02135e5f)
extern void MI_Zero36B(void *);
extern void MIi_CpuClear16(u32, void *, u32);

static inline u8 *JntEnt(G3dRS *rs)
{
    u8 *jnt = rs->pResNodeInfo;
    u32 id = rs->c[1];
    u8 *t = jnt + *(u16 *)(jnt + 6);
    return jnt + *(u32 *)(t + *(u16 *)t * id + 4);
}

typedef struct P16 { s16 x, y; } P16;

void NNSi_G3dAnmObjInitNsBca(G3dAnmObj *o, u8 *res, u8 *src)
{
    u32 i;
    u16 *offs;
    o->resAnm = res;
    o->funcAnm = data_0213bcbc;
    o->numMapData = src[0x17];
    {
        volatile u16 zero = 0;
        MIi_CpuClear16(zero, o->mapData, o->numMapData * 2);
    }
    offs = (u16 *)(res + 20);
    for (i = 0; i < *(u16 *)(res + 6); i++) {
        o->mapData[i] = (*(u32 *)(res + offs[i]) >> 24) | 0x100;
    }
}

void getMdlTrans_(G3dJntAnmResult *out)
{
    G3dRS *rs = data_021f5cc0;
    u8 *ent = JntEnt(rs);
    if (*(u16 *)ent & 1) {
        out->flag |= 4;
    } else {
        u32 *p = (u32 *)(ent + 4);
        out->trans[0] = p[0];
        out->trans[1] = p[1];
        out->trans[2] = p[2];
    }
}

void getMdlScale_(G3dJntAnmResult *out)
{
    G3dRS *rs = data_021f5cc0;
    u8 *jnt = rs->pResNodeInfo;
    u8 *node = rs->c;
    u8 *t = jnt + *(u16 *)(jnt + 6);
    u8 *ent = jnt + *(u32 *)(t + *(u16 *)t * node[1] + 4);
    u32 flag = *(u16 *)ent;
    u8 *p = ent + 4;
    if (!(flag & 1)) {
        p += 12;
    }
    if (!(flag & 2)) {
        if (flag & 8) {
            p += 4;
        } else {
            p += 16;
        }
    }
    rs->funcJntScale(out, (const int *)p, node, flag);
}

void getMdlRot_(G3dJntAnmResult *out)
{
    G3dRS *rs = data_021f5cc0;
    u8 *ent = JntEnt(rs);
    u32 flag = *(u16 *)ent;
    s16 *p = (s16 *)(ent + 4);
    if (!(flag & 1)) {
        p = (s16 *)((u8 *)p + 12);
    }
    if (!(flag & 2)) {
        if (flag & 8) {
            s32 a = p[0];
            s32 b = p[1];
            s32 k = (s32)(flag & 0xf0) >> 4;
            MI_Zero36B(out->rot);
            out->rot[k] = (*(u16 *)ent & 0x100) ? -0x1000 : 0x1000;
            out->rot[data_02135e5c[k][0]] = a;
            out->rot[data_02135e5d[k][0]] = b;
            if (*(u16 *)ent & 0x200) {
                b = -b;
            }
            out->rot[data_02135e5e[k][0]] = b;
            if (*(u16 *)ent & 0x400) {
                a = -a;
            }
            out->rot[data_02135e5f[k][0]] = a;
        } else {
            out->rot[0] = *(s16 *)(ent + 2);
            out->rot[1] = p[0];
            out->rot[2] = p[1];
            out->rot[3] = p[2];
            out->rot[4] = p[3];
            out->rot[5] = p[4];
            out->rot[6] = p[5];
            out->rot[7] = p[6];
            out->rot[8] = p[7];
        }
    } else {
        out->flag |= 2;
    }
}

void getTransData_(s32 *out, s32 frame, const u32 *ent, const void *base)
{
    const u8 *d;
    u32 info;
    u32 lim, q;
    u32 f = frame >> 12;
    d = (const u8 *)base + ent[1];
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
                u32 ib, ia;
                if (f & 2) {
                    ib = f >> 2;
                    ia = ib + 1;
                } else {
                    ia = f >> 2;
                    ib = ia + 1;
                }
                if (info & 0x20000000) {
                    *out = (((const s16 *)d)[ia] + ((const s16 *)d)[ia] + ((const s16 *)d)[ia] + ((const s16 *)d)[ib]) >> 2;
                } else {
                    *out = (s32)(((s64)((const s32 *)d)[ia] + ((const s32 *)d)[ia] + ((const s32 *)d)[ia] + ((const s32 *)d)[ib]) >> 2);
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
    goto fetch;
avg:
    if (info & 0x20000000) {
        *out = (((const s16 *)d)[q] + ((const s16 *)d + q)[1]) >> 1;
    } else {
        *out = (((const s32 *)d)[q] >> 1) + (((const s32 *)d + q)[1] >> 1);
    }
    return;
fetch:
    if (info & 0x20000000) {
        *out = ((const s16 *)d)[f];
    } else {
        *out = ((const s32 *)d)[f];
    }
}

void getTransDataEx_(s32 *out, s32 frame, const u32 *ent, const void *res)
{
    const u8 *hdr = (const u8 *)res;
    const u8 *d = hdr + ent[1];
    u32 info = ent[0];
    s32 f = frame >> 12;
    if (f == *(const u16 *)(hdr + 4) - 1) {
        if (info & 0xc0000000) {
            if (info & 0x40000000) {
                f = (f & 1) + ((u32)f >> 1);
            } else {
                f = (f & 3) + ((u32)f >> 2);
            }
        }
        if (*(const u32 *)(hdr + 8) & 2) {
            s32 t = frame & 0xfff;
            s32 a, b;
            if (info & 0x20000000) {
                a = ((const s16 *)d)[f];
                b = ((const s16 *)d)[0];
            } else {
                a = ((const s32 *)d)[f];
                b = ((const s32 *)d)[0];
            }
            *out = a + ((t * (b - a)) >> 12);
        } else {
            if (info & 0x20000000) {
                *out = ((const s16 *)d)[f];
            } else {
                *out = ((const s32 *)d)[f];
            }
        }
    } else {
        s32 mul, sh;
        s32 a, b;
        s32 t;
        if (info & 0xc0000000) {
            u32 lim = (info & 0x1fff0000) >> 16;
            if (info & 0x40000000) {
                if ((u32)f >= lim) {
                    f = lim >> 1;
                    goto one;
                }
                f = (u32)f >> 1;
                t = frame & 0x1fff;
                mul = 2;
                sh = 1;
            } else {
                if ((u32)f >= lim) {
                    f = (f & 3) + ((u32)f >> 2);
                    goto one;
                }
                f = (u32)f >> 2;
                t = frame & 0x3fff;
                mul = 4;
                sh = 2;
            }
            goto fin;
        }
    one:
        t = frame & 0xfff;
        mul = 1;
        sh = 0;
    fin:
        if (info & 0x20000000) {
            a = ((const s16 *)d)[f];
            b = ((const s16 *)d + f)[1];
        } else {
            a = ((const s32 *)d)[f];
            b = ((const s32 *)d + f)[1];
        }
        *out = (a * mul + ((t * (b - a)) >> 12)) >> sh;
    }
}

const u8 data_02135e5c[9][4] = {
    {4, 5, 7, 8}, {3, 5, 6, 8}, {3, 4, 6, 7},
    {1, 2, 7, 8}, {0, 2, 6, 8}, {0, 1, 6, 7},
    {1, 2, 4, 5}, {0, 2, 3, 5}, {0, 1, 3, 4},
};

#include "host_labels.h"

HOST_LABEL_DEFINE(data_02135e5d, (char *)&data_02135e5c[1]);
HOST_LABEL_DEFINE(data_02135e5e, (char *)&data_02135e5c[2]);
HOST_LABEL_DEFINE(data_02135e5f, (char *)&data_02135e5c[3]);
