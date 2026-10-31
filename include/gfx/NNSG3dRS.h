#ifndef GFX_NNSG3DRS_H
#define GFX_NNSG3DRS_H

#include "types.h"
#include "gfx/NNSG3dRenderObj.h"

struct NNSG3dJntAnmResult;
struct NNSG3dRS;

typedef void (*NNSG3dSbcCallBackFunc)(NNSG3dRS *);

struct NNSG3dRS {
    /* 0x00 */ u8 *c;
    /* 0x04 */ NNSG3dRenderObj *pRenderObj;
    /* 0x08 */ u32 flag;
    /* 0x0c */ void *cbVecFunc[0x20];
    /* 0x8c */ u8 cbVecTiming[0x20];
    /* 0xac */ u8 currentNode;
    /* 0xad */ u8 currentMat;
    /* 0xae */ u8 currentNodeDesc;
    /* 0xaf */ u8 dummy_;
    /* 0xb0 */ NNSG3dMatAnmResult *pMatAnmResult;
    /* 0xb4 */ NNSG3dJntAnmResult *pJntAnmResult;
    /* 0xb8 */ void *pVisAnmResult;
    /* 0xbc */ u32 isMatCached[2];
    /* 0xc4 */ u32 isScaleCacheOne[2];
    /* 0xcc */ u32 isEnvCached[2];
    /* 0xd4 */ u8 *pResNodeInfo;
    /* 0xd8 */ u8 *pResMat;
};

#endif
