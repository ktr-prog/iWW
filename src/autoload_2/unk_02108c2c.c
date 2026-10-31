

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
#include "types64.h"
typedef struct MatAnmResult {
    u32 flag;
    u32 prm[5];
    s32 scaleS, scaleT;
    s16 sinR, cosR;
    s32 transS, transT;
    u16 origWidth, origHeight;
    s32 magW, magH;
} MatAnmResult;
extern void FX_DivAsync(s32, s32);
extern s32 FX_GetDivResult(void);
static inline s32 FxMul(s32 a, s32 b) { return (s32)(((s64)a * b) >> 12); }

void texmtxCalc_flag___3dsmax(s32 *m, const MatAnmResult *anm)
{
    s32 ss_cos, ss_sin, st_cos, st_sin;
    s32 A, B;
    s32 tmpW = anm->origWidth << 12;
    s32 tmpH = anm->origHeight << 12;
    FX_DivAsync(tmpH, tmpW);
    ss_cos = FxMul(anm->scaleS, anm->cosR);
    ss_sin = FxMul(anm->scaleS, anm->sinR);
    st_cos = FxMul(anm->scaleT, anm->cosR);
    st_sin = FxMul(anm->scaleT, anm->sinR);
    m[0] = ss_cos;
    m[5] = st_cos;
    m[1] = st_sin * FX_GetDivResult() >> 12;
    FX_DivAsync(tmpW, tmpH);
    A = (-(s32)anm->origWidth << 11) - anm->transS * anm->origWidth;
    B = anm->transT * anm->origHeight + (-(s32)anm->origHeight << 11);
    m[12] = (s32)(((s64)ss_cos * A - (s64)ss_sin * B) >> 8) + (anm->origWidth << 15);
    m[13] = (s32)(((s64)st_sin * A + (s64)st_cos * B) >> 8) + (anm->origHeight << 15);
    m[4] = (-ss_sin * FX_GetDivResult()) >> 12;
}
