typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
typedef int BOOL;
#define NULL 0

typedef struct GeBuf {
    u32 cmd;
    s32 w[14];
} GeBuf;

#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_02104000.h"
#include "proto/autoload_2/unk_02107cac.h"

extern void MIi_CpuClear16(u16 data, void *dest, u32 size);
extern s32 NNS_G3dGetResDictIdxByName(void *dict, void *name);
extern u8 *NNSi_G3dGetTexPatAnmFV(u8 *, u32, u32);
extern u8 *NNSi_G3dGetTexPatAnmTexNameByIdx(u8 *, u32);
extern u8 *NNSi_G3dGetTexPatAnmPlttNameByIdx(u8 *, u32);
extern u32 *NNS_G3dGetResDataByName(const void *dict, const void *name);
extern s32 FX_Div(s32, s32);
extern void NNS_G3dGeBufferOP_N(u32 cmd, void *args, u32 n);


static inline s32 FxMul(s32 a, s32 b)
{
    return (s32)(((long long)a * b) >> 12);
}

void NNSi_G3dSendTexSRTSi3d(const G3dMatAnmResult *a)
{
    GeBuf s;
    if (a->flag & 8) {
        s.cmd = 0x00101710;
    } else {
        s.cmd = 0x00101910;
    }
    s.w[0] = 3;
    s.w[12] = 0;
    s.w[13] = 2;
    s.w[9] = 0;
    s.w[8] = 0;
    s.w[7] = 0;
    s.w[6] = 0;
    s.w[4] = 0;
    s.w[3] = 0;
    s.w[2] = 0;
    if (a->flag & 4) {
        s.w[10] = 0;
        s.w[11] = 0;
        if (a->flag & 1) {
            s.w[1] = 0x1000;
            s.w[5] = 0x1000;
        } else {
            s.w[1] = a->scaleS;
            s.w[5] = a->scaleT;
        }
    } else if (a->flag & 1) {
        s.w[10] = -(s32)((u32)a->transS << 4) * a->origWidth;
        s.w[11] = -(s32)((u32)a->transT << 4) * a->origHeight;
        s.w[1] = 0x1000;
        s.w[5] = 0x1000;
    } else {
        s32 x = (s32)(((long long)a->scaleS * a->transS) >> 8);
        s32 y;
        s.w[10] = a->origWidth * -x;
        y = (s32)(((long long)a->scaleT * a->transT) >> 8);
        s.w[11] = a->origHeight * -y;
        s.w[1] = a->scaleS;
        s.w[5] = a->scaleT;
    }
    if (a->magW != 0x1000) {
        s.w[1] = FxMul(a->magW, s.w[1]);
        s.w[10] = FxMul(a->magW, s.w[10]);
    }
    if (a->magH != 0x1000) {
        s.w[5] = FxMul(a->magH, s.w[5]);
        s.w[11] = FxMul(a->magH, s.w[11]);
    }
    NNS_G3dGeBufferOP_N(s.cmd, s.w, 14);
}

void NNSi_G3dSendJointSRTBasic(G3dJntAnmResult *r)
{
    if ((r->flag & 4) == 0) {
        if ((r->flag & 2) == 0) {
            NNS_G3dGeBufferOP_N(0x19, r->rot, 12);
        } else {
            NNS_G3dGeBufferOP_N(0x1c, r->trans, 3);
        }
    } else if ((r->flag & 2) == 0) {
        NNS_G3dGeBufferOP_N(0x1a, r->rot, 9);
    }
    if ((r->flag & 1) == 0) {
        NNS_G3dGeBufferOP_N(0x1b, r->scale, 3);
    }
}

void NNSi_G3dGetJointScaleBasic(G3dJntAnmResult *obj, const s32 *src, const u8 *info, u32 flags)
{
    if (flags & 4) {
        obj->flag |= 1;
    } else {
        obj->scale[0] = src[0];
        obj->scale[1] = src[1];
        obj->scale[2] = src[2];
    }
    obj->flag |= 0x18;
}

void NNSi_G3dAnmObjInitNsBva(G3dAnmObj *out, void *res, u8 *blk)
{
    u32 i = 0;
    out->funcAnm = data_0213bcb8;
    out->numMapData = blk[23];
    out->resAnm = res;
    for (; i < out->numMapData; i++) {
        out->mapData[i] = i | 0x100;
    }
}

void NNSi_G3dAnmCalcNsBva(G3dVisAnmResult *out, const G3dAnmObj *a, u32 dataIdx)
{
    u8 *t = (u8 *)a->resAnm;
    s32 k = a->frame >> 12;
    u32 idx = k * *(u16 *)(t + 6) + dataIdx;
    out->isVisible = ((u32 *)(t + 12))[idx >> 5] & (1 << (idx & 31));
}

void NNSi_G3dAnmObjInitNsBtp(G3dAnmObj *obj, u8 *res, u8 *blk)
{
    u8 *dict = blk + *(u32 *)(blk + 8);
    u32 i;
    volatile u16 zero;
    obj->funcAnm = data_0213bcc4;
    obj->numMapData = blk[24];
    obj->resAnm = res;
    zero = 0;
    MIi_CpuClear16(zero, obj->mapData, obj->numMapData * 2);
    for (i = 0; i < res[13]; i++) {
        u8 *d = res + 12 + *(u16 *)(res + 18);
        s32 r = NNS_G3dGetResDictIdxByName(dict + 4, d + *(u16 *)(d + 2) + i * 16);
        if (r >= 0) {
            obj->mapData[r] = i | 0x100;
        }
    }
}

s32 SetTexParamaters_(u8 *A, const u8 *name, G3dMatAnmResult *out)
{
    u32 *p = NNS_G3dGetResDataByName(A + 60, name);
    u32 m;
    u32 w, h;
    s32 r;
    if ((p[0] & 0x1c000000) != 0x14000000) {
        m = *(u32 *)(A + 8) & 0xffff;
    } else {
        m = *(u32 *)(A + 24) & 0xffff;
    }
    out->prmTexImage &= 0xc00f0000;
    out->prmTexImage |= p[0] + m;
    out->origWidth = p[1] & 0x7ff;
    out->origHeight = (p[1] & 0x3ff800) >> 11;
    w = p[1] & 0x7ff;
    h = 0x7ff & (p[1] >> 11);
    if (w == out->origWidth) {
        r = 0x1000;
    } else {
        r = FX_Div(w << 12, out->origWidth << 12);
    }
    out->magW = r;
    if (h == out->origHeight) {
        r = 0x1000;
    } else {
        r = FX_Div(h << 12, out->origHeight << 12);
    }
    out->magH = r;
    return r;
}

u32 SetPlttParamaters_(u8 *A, const u8 *name, G3dMatAnmResult *out)
{
    u16 *p = (u16 *)NNS_G3dGetResDataByName(A + *(u16 *)(A + 52), name);
    u16 w = *(u32 *)(A + 44);
    u16 v;
    u16 f = p[1];
    v = p[0];
    if ((f & 1) == 0) {
        v = v >> 1;
        w = w >> 1;
    }
    out->prmTexPltt = v + w;
    return v + w;
}

u32 NNSi_G3dAnmCalcNsBtp(G3dMatAnmResult *obj, const G3dAnmObj *a, u32 dataIdx)
{
    u8 *res = (u8 *)a->resAnm;
    u8 *e = NNSi_G3dGetTexPatAnmFV(res, (u16)dataIdx, (u16)((u32)a->frame >> 12));
    u32 r = SetTexParamaters_((u8 *)a->resTex, NNSi_G3dGetTexPatAnmTexNameByIdx(res, e[2]), obj);
    if (e[3] == 0xff) {
        return r;
    }
    return SetPlttParamaters_((u8 *)a->resTex, NNSi_G3dGetTexPatAnmPlttNameByIdx(res, e[3]), obj);
}

s32 GetTexSRTAnmVectorVal_(u8 *base, u32 info, u32 offs, u32 frame)
{
    s16 *d;
    u32 last;
    s32 a, b;
    u32 ia, ib;
    if (info & 0x20000000) {
        return offs;
    }
    d = (s16 *)(base + offs);
    if ((info & 0xc0000000) == 0) {
        goto direct;
    }
    last = info & 0xffff;
    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last) {
                frame = (last >> 1) + 1;
                goto direct;
            }
            frame = frame >> 1;
            goto avg;
        }
        frame = frame >> 1;
        goto direct;
    } else {
        u32 r = frame & 3;
        if (r != 0) {
            if (frame > last) {
                frame = r + (last >> 2);
                goto direct;
            }
            if (frame & 1) {
                if (frame & 2) {
                    ib = frame >> 2;
                    ia = ib + 1;
                } else {
                    ia = frame >> 2;
                    ib = ia + 1;
                }
                if (info & 0x10000000) {
                    a = d[ia];
                    b = d[ib];
                } else {
                    a = ((s32 *)d)[ia];
                    b = ((s32 *)d)[ib];
                }
                return (a * 3 + b) >> 2;
            }
            frame = frame >> 2;
            goto avg;
        }
        frame = frame >> 2;
        goto direct;
    }
direct:
    if (info & 0x10000000) {
        return d[frame];
    }
    return ((s32 *)d)[frame];
avg:
    if (info & 0x10000000) {
        a = d[frame];
        b = (d + frame)[1];
    } else {
        a = ((s32 *)d)[frame];
        b = ((s32 *)d + frame)[1];
    }
    return (a + b) >> 1;
}

