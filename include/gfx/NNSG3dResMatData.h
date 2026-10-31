#ifndef GFX_NNSG3DRESMATDATA_H
#define GFX_NNSG3DRESMATDATA_H

#include "types.h"

struct NNSG3dResMatData {
    /* 0x00 */ u16 itemTag, size;
    /* 0x04 */ u32 diffAmb, specEmi, polyAttr, polyAttrMask;
    /* 0x14 */ u32 texImageParam, texImageParamMask;
    /* 0x1c */ u16 texPlttBase, flag;
    /* 0x20 */ u16 origWidth, origHeight;
    /* 0x24 */ s32 magW, magH;
};

#endif
