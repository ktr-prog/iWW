#ifndef SND_MELODY_H
#define SND_MELODY_H

#include "types.h"


typedef struct MelodyTrack MelodyTrack;
typedef struct MelodyPlayer MelodyPlayer;
typedef struct MelodyBeat MelodyBeat;

struct MelodyTrack {
#ifdef __cplusplus
    ~MelodyTrack();
#endif

    /* 0x00 */ void *handle;
    /* 0x04 */ u8 *pat;
    /* 0x08 */ u16 id;
    /* 0x0a */ u8 active;
    /* 0x0b */ s8 pos;
    /* 0x0c */ u8 tick;
    /* 0x0d */ u8 pad0d;
    /* 0x0e */ s8 s14;
    /* 0x0f */ s8 s15;
    /* 0x10 */ s8 s16;
    /* 0x11 */ s8 s17;
};

struct MelodyPlayer {
#ifdef __cplusplus
    ~MelodyPlayer();
#endif

    /* 0x00 */ MelodyTrack a;
    /* 0x14 */ MelodyTrack b;
    /* 0x28 */ u8 pat[16];
    /* 0x38 */ u8 b38;
    /* 0x39 */ s8 b39;
    /* 0x3a */ s8 b3a;
    /* 0x3b */ u8 b3b;
    /* 0x3c */ u8 b3c;
};

struct MelodyBeat {
    /* 0x00 */ void *handle;
    /* 0x04 */ u16 id;
    /* 0x06 */ s8 step;
    /* 0x07 */ u8 tick;
    /* 0x08 */ s8 v8;
    /* 0x09 */ s8 v9;
    /* 0x0a */ u8 active;
    /* 0x0b */ u8 limit;
};

#endif
