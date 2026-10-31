typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
typedef int BOOL;
#define NULL 0


extern void FX_DivAsync(s32 num, s32 den);
extern s32 FX_GetDivResult(void);


void texmtxCalc_flagS___3dsmax(s32 *o, u8 *s)
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
    B = *(s32 *)(s + 40) * h + (-(s32)h << 11);
    A = (-(s32)w << 11) - *(s32 *)(s + 36) * w;
    o[12] = (s32)(((long long)*(s16 *)(s + 34) * A - (long long)*(s16 *)(s + 32) * B) >> 8) + (w << 15);
    o[13] = (s32)(((long long)*(s16 *)(s + 32) * A + (long long)*(s16 *)(s + 34) * B) >> 8) + (*(u16 *)(s + 46) << 15);
    o[4] = (-*(s16 *)(s + 32) * FX_GetDivResult()) >> 12;
}

