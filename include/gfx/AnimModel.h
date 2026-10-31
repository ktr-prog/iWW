#ifndef GFX_ANIMMODEL_H
#define GFX_ANIMMODEL_H

#include "types.h"
#include "gfx/CachedModel.h"
#include "gfx/AnimFrameCtrl.h"

struct NNSG3dAnmObj;

class AnimModel : public CachedModel, public AnimFrameCtrl {
public:
    AnimModel();
    virtual ~AnimModel();
    /* 0xb4 */ NNSG3dAnmObj *anmObj;

    void detachAnim();
    void detachVisAnim();
    void detachJointAnim();
    void attachAnim();
    void setFrame(s32 v);
    void drawAnimated(void *q);
    void stepAnim();
    BOOL allocAnmObj(void *x);
};

#endif
