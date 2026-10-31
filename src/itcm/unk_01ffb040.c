#include "nitro/mtx.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define NULL 0
typedef s32 fx32;
typedef s16 fx16;

typedef struct VecFx32 { fx32 x, y, z; } VecFx32;

typedef struct ResJntAnm {
    u32 anmHeader;
    u16 numFrame;
    u16 numNode;
    u32 flag;
    u32 ofsRot3;
    u32 ofsRot5;
    u16 ofsAnm[1];
} ResJntAnm;

extern BOOL getRotDataByIdx_(MtxFx33 *pMtx, const fx16 *pArray3, const fx16 *pArray5, u32 idx);
extern void VEC_Normalize(VecFx32 *src, VecFx32 *dst);

static inline void vecCross_(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb) {
    fx32 x, y, z;
    x = (a->y * b->z - a->z * b->y) >> 12;
    y = (a->z * b->x - a->x * b->z) >> 12;
    z = (a->x * b->y - a->y * b->x) >> 12;
    axb->x = x;
    axb->y = y;
    axb->z = z;
}

void getRotData_(MtxFx33 *pRot, fx32 Frame, const u32 *pData, const ResJntAnm *pJntAnm) {
    u32 frame = (u32)(Frame >> 12);
    const fx16 *pArrayRot3 = (const fx16 *)((const u8 *)pJntAnm + pJntAnm->ofsRot3);
    const fx16 *pArrayRot5 = (const fx16 *)((const u8 *)pJntAnm + pJntAnm->ofsRot5);
    u32 info = *pData;
    const u16 *pDataRot = (const u16 *)((const u8 *)pJntAnm + *(pData + 1));
    u32 idx;
    u32 idx_sub;
    u32 last_interp;

    if (!(info & 0xc0000000)) {
        idx = frame;
        goto ROT_NONINTERP;
    }
    last_interp = (info & 0x1fff0000) >> 16;
    if (info & 0x40000000) {
        if (frame & 1) {
            if (frame > last_interp) {
                idx = (last_interp >> 1) + 1;
                goto ROT_NONINTERP;
            } else {
                idx = frame >> 1;
                goto ROT_INTERP_1_1;
            }
        } else {
            idx = frame >> 1;
            goto ROT_NONINTERP;
        }
    } else {
        if (frame & 3) {
            if (frame > last_interp) {
                idx = (last_interp >> 2) + (frame & 3);
                goto ROT_NONINTERP;
            }
            if (frame & 1) {
                BOOL doCross = FALSE;
                MtxFx33 r;
                if (frame & 2) {
                    idx_sub = frame >> 2;
                    idx = idx_sub + 1;
                } else {
                    idx = frame >> 2;
                    idx_sub = idx + 1;
                }
                doCross |= getRotDataByIdx_(pRot, pArrayRot3, pArrayRot5, pDataRot[idx]);
                doCross |= getRotDataByIdx_(&r, pArrayRot3, pArrayRot5, pDataRot[idx_sub]);
                pRot->a[0] = pRot->a[0] * 3 + r.a[0];
                pRot->a[1] = pRot->a[1] * 3 + r.a[1];
                pRot->a[2] = pRot->a[2] * 3 + r.a[2];
                pRot->a[3] = pRot->a[3] * 3 + r.a[3];
                pRot->a[4] = pRot->a[4] * 3 + r.a[4];
                pRot->a[5] = pRot->a[5] * 3 + r.a[5];
                VEC_Normalize((VecFx32 *)&pRot->a[0], (VecFx32 *)&pRot->a[0]);
                VEC_Normalize((VecFx32 *)&pRot->a[3], (VecFx32 *)&pRot->a[3]);
                if (!doCross) {
                    pRot->a[6] = pRot->a[6] * 3 + r.a[6];
                    pRot->a[7] = pRot->a[7] * 3 + r.a[7];
                    pRot->a[8] = pRot->a[8] * 3 + r.a[8];
                    VEC_Normalize((VecFx32 *)&pRot->a[6], (VecFx32 *)&pRot->a[6]);
                } else {
                    vecCross_((const VecFx32 *)&pRot->a[0], (const VecFx32 *)&pRot->a[3], (VecFx32 *)&pRot->a[6]);
                }
                return;
            } else {
                idx = frame >> 2;
                goto ROT_INTERP_1_1;
            }
        } else {
            idx = frame >> 2;
            goto ROT_NONINTERP;
        }
    }
ROT_INTERP_1_1:
    {
        BOOL doCross = FALSE;
        MtxFx33 r;
        doCross |= getRotDataByIdx_(pRot, pArrayRot3, pArrayRot5, pDataRot[idx]);
        doCross |= getRotDataByIdx_(&r, pArrayRot3, pArrayRot5, pDataRot[idx + 1]);
        pRot->a[0] += r.a[0];
        pRot->a[1] += r.a[1];
        pRot->a[2] += r.a[2];
        pRot->a[3] += r.a[3];
        pRot->a[4] += r.a[4];
        pRot->a[5] += r.a[5];
        VEC_Normalize((VecFx32 *)&pRot->a[0], (VecFx32 *)&pRot->a[0]);
        VEC_Normalize((VecFx32 *)&pRot->a[3], (VecFx32 *)&pRot->a[3]);
        if (!doCross) {
            pRot->a[6] += r.a[6];
            pRot->a[7] += r.a[7];
            pRot->a[8] += r.a[8];
            VEC_Normalize((VecFx32 *)&pRot->a[6], (VecFx32 *)&pRot->a[6]);
        } else {
            vecCross_((const VecFx32 *)&pRot->a[0], (const VecFx32 *)&pRot->a[3], (VecFx32 *)&pRot->a[6]);
        }
        return;
    }
ROT_NONINTERP:
    if (getRotDataByIdx_(pRot, pArrayRot3, pArrayRot5, pDataRot[idx])) {
        vecCross_((const VecFx32 *)&pRot->a[0], (const VecFx32 *)&pRot->a[3], (VecFx32 *)&pRot->a[6]);
    }
}
