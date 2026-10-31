#ifndef SND_PLAYCTX_H
#define SND_PLAYCTX_H

#include "types.h"
#include "gfx/VecFx32.h"

struct Group;

struct PlayCtx {
    /* 0x00 */ Group *group;
    /* 0x04 */ void *source;
    /* 0x08 */ u8 pad[8];
    /* 0x10 */ s32 distance;
    /* 0x14 */ s32 volume;
    /* 0x18 */ s32 pan;
    /* 0x1c */ s32 baseVolume;
    /* 0x20 */ s32 unk_20;
};

#endif
