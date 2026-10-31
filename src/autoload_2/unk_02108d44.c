typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
#include "types64.h"
typedef int BOOL;
#define NULL 0

typedef struct GeBuf4 {
    u32 cmd;
    s32 w[18];
} GeBuf4;

extern void NNS_G3dGeBufferOP_N(u32 cmd, void *args, u32 n);
extern void FX_DivAsync(s32 num, s32 den);
extern s32 FX_GetDivResult(void);
extern void (*data_0213bef0[8])(s32 *, u32 *);


static inline s32 FxMul(s32 a, s32 b)
{
    return (s32)(((long long)a * b) >> 12);
}

typedef struct TexSrt {
    u8 pad[0x18];
    s32 sx;
    s32 sy;
    s16 sn;
    s16 cs;
    s32 tx;
    s32 ty;
    u16 w;
    u16 h;
} TexSrt;
#define FXM(a, b) ((s32)(((s64)(a) * (b)) >> 12))
void texmtxCalc_flag___xsi(s32 *m, TexSrt *t)
{
    s32 h, w, sn, sy, cs, sx, x, y, e;
    s64 q, d;
    w = t->w << 12; h = t->h << 12;
    FX_DivAsync(h, w);
    cs = t->cs; sx = t->sx; sn = t->sn; sy = t->sy;
    m[0] = FXM(sx, cs);
    x = FXM(sx, sn);
    y = FXM(sy, cs);
    m[5] = y;
    m[1] = FXM(sy, sn) * FX_GetDivResult() >> 12;
    FX_DivAsync(w, h);
    q = ((s64)t->tx * t->cs + (s64)t->ty * t->sn) >> 12;
    d = ((s64)t->tx * t->sn - (s64)t->ty * t->cs) >> 12;
    e = y + (s32)(d * t->sy >> 12);
    m[12] = (t->w * (x - (s32)(q * t->sx >> 12))) << 4;
    m[13] = (-(s32)t->h * (e - 0x1000)) << 4;
    m[4] = (-x) * FX_GetDivResult() >> 12;
}

void texmtxCalc_flagS___xsi(s32 *m, TexSrt *t)
{
    s32 w = t->w << 12;
    s32 h = t->h << 12;
    s32 a, b;
    FX_DivAsync(h, w);
    m[0] = t->cs;
    m[5] = t->cs;
    m[1] = t->sn * FX_GetDivResult() >> 12;
    FX_DivAsync(w, h);
    a = (s32)(((s64)t->tx * t->cs + (s64)t->ty * t->sn) >> 12);
    b = (s32)(((s64)t->tx * t->sn - (s64)t->ty * t->cs) >> 12);
    m[12] = (t->w * (t->sn - a)) << 4;
    m[13] = (-(s32)t->h * (t->cs + b - 0x1000)) << 4;
    m[4] = (-t->sn) * FX_GetDivResult() >> 12;
}

void texmtxCalc_flagR___xsi(s32 *m, TexSrt *t)
{
    s32 tx, ty;
    m[0] = t->sx; m[5] = t->sy; m[1] = 0;
    tx = -FXM(t->tx, t->sx); ty = FXM(-t->ty, t->sy);
    m[12] = (t->w * tx) << 4;
    m[13] = (-(s32)t->h * (t->sy + ty - 0x1000)) << 4;
    m[4] = 0;
}

void texmtxCalc_flagRS___xsi(s32 *m, TexSrt *t)
{
    s32 tx, ty;
    m[0] = 0x1000; m[5] = 0x1000; m[1] = 0;
    tx = -t->tx; ty = -t->ty;
    m[12] = (t->w * tx) << 4;
    m[13] = (-(s32)t->h * ty) << 4;
    m[4] = 0;
}

void texmtxCalc_flagT___xsi(s32 *o, u8 *s)
{
    u32 w = *(u16 *)(s + 44);
    u32 h = *(u16 *)(s + 46);
    s32 num = w << 12;
    s32 den = h << 12;
    s32 sn, sy, r, t, cs, sx;
    FX_DivAsync(den, num);
    cs = *(s16 *)(s + 34);
    sx = *(s32 *)(s + 24);
    sn = *(s16 *)(s + 32);
    sy = *(s32 *)(s + 28);
    r = FxMul(sx, sn);
    t = FxMul(sy, cs);
    o[0] = FxMul(sx, cs);
    o[5] = t;
    o[1] = FxMul(sy, sn) * FX_GetDivResult() >> 12;
    FX_DivAsync(num, den);
    o[12] = (*(u16 *)(s + 44) * r) << 4;
    o[13] = (-(s32)*(u16 *)(s + 46) * (t - 0x1000)) << 4;
    o[4] = (-r * FX_GetDivResult()) >> 12;
}

void texmtxCalc_flagTS___xsi(s32 *o, u8 *s)
{
    u32 w = *(u16 *)(s + 44);
    u32 h = *(u16 *)(s + 46);
    s32 num = w << 12;
    s32 den = h << 12;
    FX_DivAsync(den, num);
    o[0] = *(s16 *)(s + 34);
    o[5] = *(s16 *)(s + 34);
    o[1] = (*(s16 *)(s + 32) * FX_GetDivResult()) >> 12;
    FX_DivAsync(num, den);
    o[12] = (*(u16 *)(s + 44) * *(s16 *)(s + 32)) << 4;
    o[13] = (-(s32)*(u16 *)(s + 46) * (*(s16 *)(s + 34) - 0x1000)) << 4;
    o[4] = (-*(s16 *)(s + 32) * FX_GetDivResult()) >> 12;
}

void texmtxCalc_flagTR___xsi(s32 *o, u8 *s)
{
    o[0] = *(s32 *)(s + 24);
    o[5] = *(s32 *)(s + 28);
    o[1] = 0;
    o[12] = 0;
    o[13] = (-(s32)*(u16 *)(s + 46) * (*(s32 *)(s + 28) - 0x1000)) << 4;
    o[4] = 0;
}

void texmtxCalc_flagTRS___xsi(s32 *o)
{
    o[0] = 0x1000;
    o[1] = 0;
    o[4] = 0;
    o[5] = 0x1000;
    o[12] = 0;
    o[13] = 0;
}

void NNSi_G3dSendTexSRTXsi(u32 *a)
{
    GeBuf4 s;
    if (a[0] & 8) {
        s.cmd = 0x00101610;
    } else {
        s.cmd = 0x00101810;
    }
    s.w[0] = 3;
    s.w[17] = 2;
    s.w[16] = 0x1000;
    s.w[15] = 0;
    s.w[12] = 0;
    s.w[11] = 0;
    s.w[10] = 0;
    s.w[9] = 0;
    s.w[8] = 0;
    s.w[7] = 0;
    s.w[4] = 0;
    s.w[3] = 0;
    if (a[0] & 1) {
        a[7] = 0x1000;
        a[6] = a[7];
    }
    if (a[0] & 2) {
        *(u16 *)((u8 *)a + 34) = 0x1000;
        *(u16 *)((u8 *)a + 32) = 0;
    }
    if (a[0] & 4) {
        a[10] = 0;
        a[9] = a[10];
    }
    data_0213bef0[a[0] & 7](&s.w[1], a);
    if (a[12] != 0x1000) {
        s.w[1] = FxMul(a[12], s.w[1]);
        s.w[2] = FxMul(a[12], s.w[2]);
        s.w[13] = FxMul(a[12], s.w[13]);
    }
    if (a[13] != 0x1000) {
        s.w[5] = FxMul(a[13], s.w[5]);
        s.w[6] = FxMul(a[13], s.w[6]);
        s.w[14] = FxMul(a[13], s.w[14]);
    }
    NNS_G3dGeBufferOP_N(s.cmd, (u32 *)&s + 1, 18);
}

void texmtxCalc_flag___xsi();
void texmtxCalc_flagS___xsi();
void texmtxCalc_flagR___xsi();
void texmtxCalc_flagRS___xsi();
void texmtxCalc_flagT___xsi();
void texmtxCalc_flagTS___xsi();
void texmtxCalc_flagTR___xsi();
void texmtxCalc_flagTRS___xsi();
void (*data_0213bef0[8])(s32 *, u32 *) = {
    (void (*)(s32 *, u32 *))texmtxCalc_flag___xsi,
    (void (*)(s32 *, u32 *))texmtxCalc_flagS___xsi,
    (void (*)(s32 *, u32 *))texmtxCalc_flagR___xsi,
    (void (*)(s32 *, u32 *))texmtxCalc_flagRS___xsi,
    (void (*)(s32 *, u32 *))texmtxCalc_flagT___xsi,
    (void (*)(s32 *, u32 *))texmtxCalc_flagTS___xsi,
    (void (*)(s32 *, u32 *))texmtxCalc_flagTR___xsi,
    (void (*)(s32 *, u32 *))texmtxCalc_flagTRS___xsi,
};
