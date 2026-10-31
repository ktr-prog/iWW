#ifndef ACTOR_CHARAFACEANIMREF_H
#define ACTOR_CHARAFACEANIMREF_H

#include "types.h"

struct CharaFaceAnimRef {
    /* 0x00 */ u8 v;
    CharaFaceAnimRef();
    ~CharaFaceAnimRef();
    void load(s32 a, s32 b, s32 c, s32 d);
    void loadAnim(s32 a, s32 b, s32 c);
    void *getMouthAnimBuffer();
    void *getEyeAnimBuffer();
    void *getAnimBuffer(u32 j);
    void setSlot(u32 x);
    void assign(u32 x);
};

#endif
