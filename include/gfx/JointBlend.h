#ifndef GFX_JOINTBLEND_H
#define GFX_JOINTBLEND_H

#include "types.h"
#include "nitro/mtx.h"
#include "gfx/VecFx32.h"

struct NNSG3dRS;


class JointBlend {
public:
    /* 0x04 */ MtxFx33 poseRot;
    /* 0x28 */ VecFx32 poseTrans;
    /* 0x34 */ s32 blendRatio;
    /* 0x38 */ s32 blendStep;
    JointBlend();
    virtual ~JointBlend();
    void capturePose(NNSG3dRS *x);
    void blendPose(NNSG3dRS *x);
    void start(s32 n);
    BOOL advance();
};

#endif
