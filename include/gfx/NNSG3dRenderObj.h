#ifndef GFX_NNSG3DRENDEROBJ_H
#define GFX_NNSG3DRENDEROBJ_H

#include "types.h"
#include "uptr.h"
#include "nitro/mtx.h"
#include "gfx/VecFx32.h"


struct NNSG3dJntAnmResult {
    /* 0x00 */ u32 flag;
    /* 0x04 */ s32 scale[9];
    /* 0x28 */ MtxFx33 rot;
    /* 0x4c */ VecFx32 trans;
};

struct NNSG3dMatAnmResult {
    /* 0x00 */ u32 flag;
    /* 0x04 */ u32 prmMatColor0;
    /* 0x08 */ u32 prmMatColor1;
    /* 0x0c */ u32 prmPolygonAttr;
    /* 0x10 */ u32 prmTexImage;
    /* 0x14 */ u32 prmTexPltt;
    /* 0x18 */ s32 scaleS;
    /* 0x1c */ s32 scaleT;
    /* 0x20 */ s16 sinR;
    /* 0x22 */ s16 cosR;
    /* 0x24 */ s32 transS;
    /* 0x28 */ s32 transT;
    /* 0x2c */ u16 origWidth;
    /* 0x2e */ u16 origHeight;
    /* 0x30 */ s32 magW;
    /* 0x34 */ s32 magH;
};

struct NNSG3dRenderObj {
    u32 flag;
    void *pad_04[8];
    u8 pad_24[4];
    void *pad_28;
    uptr ptrUser;
    u8 *ptrUserSbc;
    NNSG3dJntAnmResult *recJntAnm;
};

#endif
