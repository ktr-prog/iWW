#ifndef GFX_MATTEXPATANIM_H
#define GFX_MATTEXPATANIM_H

#include "types.h"
#include "gfx/AnimFrameCtrl.h"

class MatTexPatTrack;

class MatTexPatAnim : public AnimFrameCtrl {
public:
    /* 0x18 */ void *resMdl;
    /* 0x1c */ void *resTex;
    /* 0x20 */ void *patAnm;
    /* 0x24 */ u16 patNumFrames;
    /* 0x26 */ u8 numTracks;
    /* 0x28 */ MatTexPatTrack *tracks;
    MatTexPatAnim();
    virtual ~MatTexPatAnim();
    BOOL setMaterialTex(const char *matName, const char *texName);
    void applyFrame();
    void update();
    void setAnim(void *anm, u16 lastFrame, u32 numFrames, u8 mode, s32 speed);
    void release();
    BOOL init(void *r1, void *r2, u32 r3, void *heap);
    void clear();
    void pauseMaterial(const char *matName);
};

#endif
