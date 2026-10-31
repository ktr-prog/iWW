#ifndef GFX_SPRITEANIM_H
#define GFX_SPRITEANIM_H

#include "types.h"
#include "nitro/gxoam.h"

struct SpriteAnimFrame {
    /* 0x00 */ GXOamAttr *cell;
    /* 0x04 */ s32 duration;
    /* 0x08 */ s16 x;
    /* 0x0a */ s16 y;
};

struct SpriteAnimSeq {
    /* 0x00 */ SpriteAnimFrame *frames;
    /* 0x04 */ s32 frameCount;
};

class SpriteAnim {
public:
    SpriteAnim();
    ~SpriteAnim();
    void update();
    void restart();
    void pause();
    BOOL isFinished();
    s32 getFrameY(s32 v);
    s32 getFrameX(s32 v);
    SpriteAnimSeq *getSeq();
    s32 getFrameIndex();
    GXOamAttr *getCell();
    void setFrame(s32 a, s32 b);
    void setSpeed(s32 v);
    void setPlayOnce(s32 v);
    void setSeq(SpriteAnimSeq *v);

    /* 0x00 */ SpriteAnimSeq *seq;
    /* 0x04 */ s32 frameIndex;
    /* 0x08 */ s32 frameTime;
    /* 0x0c */ s32 speed;
    /* 0x10 */ s32 playOnce;
};

#endif
