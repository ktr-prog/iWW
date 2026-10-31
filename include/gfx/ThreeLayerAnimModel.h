#ifndef GFX_THREELAYERANIMMODEL_H
#define GFX_THREELAYERANIMMODEL_H

#include "types.h"
#include "gfx/TwoLayerAnimModel.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/JointBlend.h"

struct NNSG3dRS;

class ThreeLayerAnimModel : public TwoLayerAnimModel {
public:
    ThreeLayerAnimModel();
    virtual ~ThreeLayerAnimModel();
    void assignJointsToLayer3(u32 a, u32 b);
    void playLayer3FromBase(u32 a, u32 b);
    BOOL checkLayer3Finished();
    void playLayer3(void *anm, u32 blend, u32 mode, u32 speed, u32 frame, u32 numFrames, BOOL g);
    void updateLayers3();
    BOOL allocLayer3Anims(void *heap);
    void onJointCalcPostLayer3(NNSG3dRS *m);
    void applyLayer3Blend(NNSG3dRS *m);
    void onJointCalcPreLayer3(NNSG3dRS *m);
    void captureLayer3Pose(NNSG3dRS *m);
    BOOL isLayer3Joint(u32 i);
    void clearLayer3Joint(u32 i);
    void setLayer3Joint(u32 i);
    u32 func_02054b38(u32 a);

    /* 0x154 */ void *layer3AnmObj;
    /* 0x158 */ AnimFrameCtrl layer3Frame;
    /* 0x170 */ JointBlend layer3Blend;
    /* 0x1ac */ u32 layer3JointMask;
    /* 0x1b0 */ u32 layer3JointMaskHi;
};

#endif
