#ifndef GFX_MODELANIM_H
#define GFX_MODELANIM_H

#include "types.h"
#include "gfx/AnimFrameCtrl.h"

struct NNSG3dResMdl;
struct NNSG3dAnmObj;

class ModelAnim : public AnimFrameCtrl {
public:
    ModelAnim();
    virtual ~ModelAnim();
    void removeFromRenderObj(void *renderObj);
    void addToRenderObj(void *renderObj);
    void replaceWithTex(void *renderObj, void *anm, void *tex, u8 mode, s32 speed, u16 frame);
    void initWithTex(void *anm, void *tex, s32 mode, s32 speed, u16 frame);
    void replace(void *renderObj, void *anm, s32 mode, s32 speed, u16 frame);
    void init(void *anm, s32 mode, s32 speed, u16 frame);
    void initFromResource(void *anm, void *tex, u32 mode, u32 speed, u16 frame);
    BOOL allocJointAnm(NNSG3dResMdl *mdl, void *heap);
    BOOL allocMatAnm(NNSG3dResMdl *mdl, void *heap);

    /* 0x18 */ NNSG3dAnmObj *anmObj;
    /* 0x1c */ NNSG3dResMdl *resMdl;
};

#endif
