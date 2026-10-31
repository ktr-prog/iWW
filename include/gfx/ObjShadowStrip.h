#ifndef GFX_OBJSHADOWSTRIP_H
#define GFX_OBJSHADOWSTRIP_H

#include "types.h"
#include "gfx/VecFx32.h"

struct ObjShadowTexture;
class Heap;

class ObjShadowStrip {
public:
    void release(Heap *heap);
    void draw(VecFx32 *pos);
    BOOL build(VecFx32 *pos, s32 size, s32 shift, s32 idx, s32 a, s32 b, Heap *heap);
    ObjShadowStrip();
    ~ObjShadowStrip();
    ObjShadowStrip *func_020ac1e0();

    /* 0x00 */ VecFx32 basePos;
    /* 0x0c */ s32 halfWidth;
    /* 0x10 */ s32 cullExtent;
    /* 0x14 */ u32 numRows;
    /* 0x18 */ s32 cachedZ;
    /* 0x1c */ s32 *rowDepths;
    /* 0x20 */ s32 texLeftS;
    /* 0x24 */ s32 texRightS;
    /* 0x28 */ s32 *rowTexT;
    /* 0x2c */ VecFx32 *rowVertices;
    /* 0x30 */ ObjShadowTexture *texture;
};

#endif
