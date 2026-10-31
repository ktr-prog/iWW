typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;
typedef int BOOL;
#define NULL 0

#include "nnsys/g3d_rt.h"
#include "proto/autoload_2/unk_02104000.h"
#include "proto/autoload_2/unk_02107994.h"

extern void MIi_CpuClear16(u16 data, void *dest, u32 size);
extern s32 NNS_G3dGetResDictIdxByName(void *dict, void *name);
extern s32 GetTexSRTAnmVectorVal_(u8 *base, u32 info, u32 offs, u32 frame);
extern u32 GetTexSRTAnmSinCosVal_(u8 *base, u32 info, u32 offs, u32 frame);


void GetTexSRTAnm_(u8 *res, u32 idx, u32 frame, G3dMatAnmResult *out)
{
    u8 *base = res + 8;
    u32 off = *(u16 *)(res + 14);
    u32 stride = *(u16 *)(base + off);
    u32 *p = (u32 *)(base + off + 4 + stride * idx);
    u32 flags = out->flag;
    s32 a, b;
    u32 rot;
    a = GetTexSRTAnmVectorVal_(res, p[6], p[7], frame);
    b = GetTexSRTAnmVectorVal_(res, p[8], p[9], frame);
    if (a == 0 && b == 0) {
        flags |= 4;
    } else {
        out->transS = a;
        out->transT = b;
        flags &= ~4;
    }
    rot = GetTexSRTAnmSinCosVal_(res, p[4], p[5], frame);
    if (rot == 0x10000000) {
        flags |= 2;
    } else {
        out->sinR = rot;
        out->cosR = rot >> 16;
        flags &= ~2;
    }
    a = GetTexSRTAnmVectorVal_(res, p[0], p[1], frame);
    b = GetTexSRTAnmVectorVal_(res, p[2], p[3], frame);
    if (a == 0x1000 && b == 0x1000) {
        flags |= 1;
    } else {
        out->scaleS = a;
        out->scaleT = b;
        flags &= ~1;
    }
    out->flag = flags;
}

void NNSi_G3dAnmObjInitNsBta(G3dAnmObj *obj, u8 *res, u8 *blk)
{
    u8 *dict = blk + *(u32 *)(blk + 8);
    u32 i;
    volatile u16 zero;
    obj->funcAnm = data_0213bcc0;
    obj->numMapData = blk[24];
    zero = 0;
    MIi_CpuClear16(zero, obj->mapData, obj->numMapData * 2);
    for (i = 0; i < res[9]; i++) {
        u8 *d = res + 8 + *(u16 *)(res + 14);
        s32 r = NNS_G3dGetResDictIdxByName(dict + 4, d + *(u16 *)(d + 2) + i * 16);
        if (r >= 0) {
            obj->mapData[r] = i | 0x100;
        }
    }
}

void NNSi_G3dAnmCalcNsBta(G3dMatAnmResult *result, const G3dAnmObj *anm, u32 dataIdx)
{
    GetTexSRTAnm_((u8 *)anm->resAnm, (u16)dataIdx, anm->frame >> 12, result);
    result->prmTexImage &= ~0xc0000000;
    result->prmTexImage |= 0x40000000;
    result->flag |= 8;
}

