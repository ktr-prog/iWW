typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
typedef int BOOL;
#define NULL 0

typedef struct GeBuf4 {
    u32 cmd;
    s32 w[18];
} GeBuf4;

extern void NNS_G3dGeBufferOP_N(u32 cmd, void *args, u32 n);
extern void FX_DivAsync(s32 num, s32 den);
extern s32 FX_GetDivResult(void);
extern void (*data_0213bed0[8])(s32 *, u32 *);


static inline s32 FxMul(s32 a, s32 b)
{
    return (s32)(((long long)a * b) >> 12);
}

void texmtxCalc_flagRS___3dsmax(s32 *o, u8 *s)
{
    o[0] = 0x1000;
    o[5] = 0x1000;
    o[1] = 0;
    o[12] = (-*(s32 *)(s + 36) * *(u16 *)(s + 44)) << 4;
    o[13] = (*(s32 *)(s + 40) * *(u16 *)(s + 46)) << 4;
    o[4] = 0;
}

void texmtxCalc_flagT___3dsmax(s32 *o, u8 *s)
{
    u32 w = *(u16 *)(s + 44);
    u32 h = *(u16 *)(s + 46);
    s32 num = w << 12;
    s32 den = h << 12;
    s32 cs, sn, sx, sy, p, q, u, v, A, B, t12, t13;
    long long pA;
    FX_DivAsync(den, num);
    cs = *(s16 *)(s + 34);
    sx = *(s32 *)(s + 24);
    sn = *(s16 *)(s + 32);
    sy = *(s32 *)(s + 28);
    p = FxMul(sx, cs);
    q = FxMul(sx, sn);
    u = FxMul(sy, cs);
    v = FxMul(sy, sn);
    o[0] = p;
    o[5] = u;
    o[1] = v * FX_GetDivResult() >> 12;
    FX_DivAsync(num, den);
    w = *(u16 *)(s + 44);
    h = *(u16 *)(s + 46);
    B = -(s32)h << 11;
    A = -(s32)w << 11;
    pA = (long long)p * A;
    t13 = (s32)(((long long)v * A + (long long)u * B) >> 8);
    t12 = (s32)((pA - (long long)q * B) >> 8);
    o[12] = t12 + (w << 15);
    o[13] = t13 + (*(u16 *)(s + 46) << 15);
    o[4] = (-q * FX_GetDivResult()) >> 12;
}

void texmtxCalc_flagTS___3dsmax(s32 *o, u8 *s)
{
    u32 w = *(u16 *)(s + 44);
    u32 h = *(u16 *)(s + 46);
    s32 num = w << 12;
    s32 den = h << 12;
    s32 A, B;
    FX_DivAsync(den, num);
    o[0] = *(s16 *)(s + 34);
    o[5] = *(s16 *)(s + 34);
    o[1] = (*(s16 *)(s + 32) * FX_GetDivResult()) >> 12;
    FX_DivAsync(num, den);
    w = *(u16 *)(s + 44);
    h = *(u16 *)(s + 46);
    A = -(s32)w << 11;
    B = -(s32)h << 11;
    o[12] = (s32)(((long long)*(s16 *)(s + 34) * A - (long long)*(s16 *)(s + 32) * B) >> 8) + (w << 15);
    o[13] = (s32)(((long long)*(s16 *)(s + 32) * A + (long long)*(s16 *)(s + 34) * B) >> 8) + (*(u16 *)(s + 46) << 15);
    o[4] = (-*(s16 *)(s + 32) * FX_GetDivResult()) >> 12;
}

void texmtxCalc_flagTR___3dsmax(s32 *o, u8 *s)
{
    o[0] = *(s32 *)(s + 24);
    o[5] = *(s32 *)(s + 28);
    o[1] = 0;
    o[12] = ((0x1000 - *(s32 *)(s + 24)) * *(u16 *)(s + 44)) << 3;
    o[13] = ((0x1000 - *(s32 *)(s + 28)) * *(u16 *)(s + 46)) << 3;
    o[4] = 0;
}

void texmtxCalc_flagTRS___3dsmax(s32 *o)
{
    o[0] = 0x1000;
    o[1] = 0;
    o[4] = 0;
    o[5] = 0x1000;
    o[12] = 0;
    o[13] = 0;
}

void NNSi_G3dSendTexSRT3dsMax(u32 *a)
{
    GeBuf4 s;
    if (a[0] & 8) {
        s.cmd = 0x00101610;
    } else {
        s.cmd = 0x00101810;
    }
    s.w[0] = 3;
    s.w[17] = 2;
    s.w[15] = 0;
    s.w[12] = 0;
    s.w[11] = 0;
    s.w[10] = 0;
    s.w[9] = 0;
    s.w[8] = 0;
    s.w[7] = 0;
    s.w[4] = 0;
    s.w[3] = 0;
    s.w[16] = 0x1000;
    data_0213bed0[a[0] & 7](&s.w[1], a);
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

void NNSi_G3dSendJointSRTSi3d(u32 *a)
{
    s32 v[3];
    BOOL t = 0;
    u32 f = a[0] & 0x18;
    if (f == 0) {
        NNS_G3dGeBufferOP_N(0x1b, a + 7, 3);
    }
    if ((a[0] & 4) == 0) {
        if (f != 0) {
            t = 1;
        } else {
            v[0] = FxMul(a[19], a[4]);
            v[1] = FxMul(a[20], a[5]);
            v[2] = FxMul(a[21], a[6]);
            NNS_G3dGeBufferOP_N(0x1c, v, 3);
        }
    }
    if ((a[0] & 2) == 0) {
        if (t != 0) {
            NNS_G3dGeBufferOP_N(0x19, a + 10, 12);
        } else {
            NNS_G3dGeBufferOP_N(0x1a, a + 10, 9);
        }
    } else if (t != 0) {
        NNS_G3dGeBufferOP_N(0x1c, a + 19, 3);
    }
    if (f == 0) {
        NNS_G3dGeBufferOP_N(0x1b, a + 4, 3);
    }
    if ((a[0] & 1) == 0) {
        NNS_G3dGeBufferOP_N(0x1b, a + 1, 3);
    }
}

void texmtxCalc_flag___3dsmax();
void texmtxCalc_flagS___3dsmax();
void texmtxCalc_flagR___3dsmax();
void texmtxCalc_flagRS___3dsmax();
void texmtxCalc_flagT___3dsmax();
void texmtxCalc_flagTS___3dsmax();
void texmtxCalc_flagTR___3dsmax();
void texmtxCalc_flagTRS___3dsmax();
void (*data_0213bed0[8])(s32 *, u32 *) = {
    (void (*)(s32 *, u32 *))texmtxCalc_flag___3dsmax,
    (void (*)(s32 *, u32 *))texmtxCalc_flagS___3dsmax,
    (void (*)(s32 *, u32 *))texmtxCalc_flagR___3dsmax,
    (void (*)(s32 *, u32 *))texmtxCalc_flagRS___3dsmax,
    (void (*)(s32 *, u32 *))texmtxCalc_flagT___3dsmax,
    (void (*)(s32 *, u32 *))texmtxCalc_flagTS___3dsmax,
    (void (*)(s32 *, u32 *))texmtxCalc_flagTR___3dsmax,
    (void (*)(s32 *, u32 *))texmtxCalc_flagTRS___3dsmax,
};
