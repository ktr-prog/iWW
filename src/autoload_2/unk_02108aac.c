

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

void texmtxCalc_flagR___3dsmax(s32 *m, const MatAnmResult *anm)
{
    s32 A, B;
    m[0] = anm->scaleS;
    m[5] = anm->scaleT;
    m[1] = 0;
    A = (-(s32)anm->origWidth << 11) - anm->transS * anm->origWidth;
    B = anm->transT * anm->origHeight + (-(s32)anm->origHeight << 11);
    m[12] = (s32)(((s64)anm->scaleS * A) >> 8) + (anm->origWidth << 15);
    m[13] = (s32)(((s64)anm->scaleT * B) >> 8) + (anm->origHeight << 15);
    m[4] = 0;
}
