#ifndef SND_SNDSEGROUP_H
#define SND_SNDSEGROUP_H

#include "types.h"


struct Ent {
    /* 0x00 */ void *handle;
    /* 0x04 */ s16 trackPitch;
    /* 0x06 */ u16 index;
    /* 0x08 */ u8 seqArc;
    /* 0x09 */ u8 flags;
    /* 0x0a */ u8 trackVolume;
    /* 0x0b */ u8 pad;
};

struct Group;
typedef void (*GroupFn)(Group *g, s32 i, s32 v);
struct Group {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ Ent voices[3];
    /* 0x2c */ GroupFn startVoiceFn;
    /* 0x30 */ GroupFn applyParamsFn;
    /* 0x34 */ u16 flags;
    /* 0x36 */ u8 numVoices;
};

struct InfoB {
    /* 0x0 */ u8 pad[4];
    /* 0x4 */ u8 playerPrio;
};

#endif
