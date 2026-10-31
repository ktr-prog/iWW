#ifndef GFX_OBJSHADOWTEXTURE_H
#define GFX_OBJSHADOWTEXTURE_H

#include "types.h"

struct ObjShadowTexture {
    /* 0x00 */ u8 *texRes;
    /* 0x04 */ u32 texImageParam;
    /* 0x08 */ u32 plttBase;
    /* 0x0c */ u16 width;
    /* 0x0e */ u16 height;
    /* 0x10 */ u32 texFormat;
    /* 0x14 */ u8 polygonId;
    /* 0x15 */ u8 unk_15[3];
};

#endif
