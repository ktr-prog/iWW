#ifndef GFX_NNSG3DRESMDL_H
#define GFX_NNSG3DRESMDL_H

#include "types.h"
#include "gfx/NNSG3dResTex.h"

struct NNSG3dResMdlInfo {
    /* 0x0 */ u8 sbcType;
    /* 0x1 */ u8 scalingRule;
    /* 0x2 */ u8 texMtxMode;
    /* 0x3 */ u8 numNode;
    /* 0x4 */ u8 numMat;
    /* 0x5 */ u8 numShp;
    /* 0x6 */ u8 firstUnusedMtxStackID;
    /* 0x7 */ u8 pad_07;
};

struct NNSG3dResMdl {
    /* 0x00 */ u32 size;
    /* 0x04 */ u32 ofsSbc;
    /* 0x08 */ u32 ofsMat;
    /* 0x0c */ u32 ofsShp;
    /* 0x10 */ u32 ofsEvpMtx;
    /* 0x14 */ NNSG3dResMdlInfo info;
};

struct NNSG3dResMat {
    /* 0x0 */ u16 ofsDictTexToMatList;
    /* 0x2 */ u16 ofsDictPlttToMatList;
    /* 0x4 */ NNSG3dResDict dict;
};

#endif
