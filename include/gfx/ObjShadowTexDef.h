#ifndef GFX_OBJSHADOWTEXDEF_H
#define GFX_OBJSHADOWTEXDEF_H

#include "types.h"

struct ObjShadowTexDef {
    /* 0x0 */ char *texName;
    /* 0x4 */ u8 texFlip, texRepeat, polygonId, unk_07;
};

#endif
