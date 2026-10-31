typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
#include "types64.h"
typedef int BOOL;
#define NULL 0

static inline u32 *MatEnt(u8 *res, u32 i)
{
    u8 *b = res + *(u32 *)(res + 8);
    u8 *p = b + 4 + *(u16 *)(b + 10);
    return (u32 *)(b + *(u32 *)(p + *(u16 *)p * i + 4));
}

static inline u32 *MatEntI(u8 *b, u32 i)
{
    u8 *p = b + 4 + *(u16 *)(b + 10);
    return (u32 *)(b + *(u32 *)(p + *(u16 *)p * i + 4));
}

u8 *NNS_G3dGetDataBlockHeaderByIdx(u8 *p, u32 i)
{
    u8 *b = p + *(u16 *)(p + 12);
    return p + ((u32 *)b)[i];
}

u8 *NNS_G3dGetMdlSet(u8 *p)
{
    return p + *(u32 *)(p + *(u16 *)(p + 12));
}

u8 *NNS_G3dGetTex(u8 *p)
{
    u8 *b = p + *(u16 *)(p + 12);
    if (*(u16 *)(p + 14) == 1) {
        if (*(u32 *)p == 0x30585442) {
            return p + *(u32 *)b;
        }
        return NULL;
    }
    return p + ((u32 *)b)[1];
}

void NNSi_G3dModifyMatFlag(u8 *res, BOOL on, u32 mask)
{
    u32 n = res[0x18];
    u32 i;
    u8 *b = res + *(u32 *)(res + 8);
    for (i = 0; i < n; i++) {
        u16 *m = (u16 *)MatEntI(b, i);
        if (on) {
            m[15] |= mask;
        } else {
            m[15] &= ~mask;
        }
    }
}

void NNSi_G3dModifyPolygonAttrMask(u8 *res, BOOL on, u32 mask)
{
    u32 n = res[0x18];
    u32 i;
    u8 *b = res + *(u32 *)(res + 8);
    for (i = 0; i < n; i++) {
        u32 *m = MatEntI(b, i);
        if (on) {
            m[4] |= mask;
        } else {
            m[4] &= ~mask;
        }
    }
}

void NNS_G3dMdlSetMdlDiff(u8 *res, u32 i, u32 v)
{
    u32 *m = MatEnt(res, i);
    m[1] = (m[1] & ~0x7fff) | v;
}

void NNS_G3dMdlSetMdlEmi(u8 *res, u32 i, u32 v)
{
    u32 *m = MatEnt(res, i);
    m[2] = (m[2] & 0x8000ffff) | (v << 16);
}

void NNS_G3dMdlSetMdlLightEnableFlag(u8 *res, u32 i, u32 v)
{
    u32 *m = MatEnt(res, i);
    m[3] = (m[3] & ~0xf) | v;
}

void NNS_G3dMdlSetMdlPolygonID(u8 *res, u32 i, u32 v)
{
    u32 *m = MatEnt(res, i);
    m[3] = (m[3] & ~0x3f000000) | (v << 24);
}

void NNS_G3dMdlSetMdlAlpha(u8 *res, u32 i, u32 v)
{
    u32 *m = MatEnt(res, i);
    m[3] = (m[3] & ~0x1f0000) | (v << 16);
}

u32 NNS_G3dMdlGetMdlAlpha(u8 *res, u32 i)
{
    u32 *m = MatEnt(res, i);
    return (m[3] & 0x1f0000) >> 16;
}
