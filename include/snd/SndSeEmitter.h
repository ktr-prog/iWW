#ifndef SND_SNDSEEMITTER_H
#define SND_SNDSEEMITTER_H

#include "types.h"
#include "gfx/VecFx32.h"


#ifdef HOST64
struct SndHandle {
    u8 pad00[0x40];
    void (*volCb)(SndHandle *h, s32 idx);
    u8 pad34[8];
};
#else
struct SndHandle {
    /* 0x00 */ u8 pad00[0x30];
    /* 0x30 */ void (*volCb)(SndHandle *h, s32 idx);
    /* 0x34 */ u8 pad34[4];
};
#endif

class SndSeEmitter : public SndHandle {
public:
    SndSeEmitter();
    virtual ~SndSeEmitter();
    virtual void init();
    virtual void update(void *src);
    virtual void stop();
    void stopEffects();
    BOOL playHeld(s32 id, s32 c, s16 d);
    BOOL playOneShot(s32 id, s32 c, s16 d);
    u16 nextAlternateId(u16 s);
    void playAlternate(u16 s);
    void callInit();
    void callUpdateRelative(VecFx32 *v);
    void callStop();
    void callInitAlt();
    void callUpdateRelativeAlt(VecFx32 *v);
    void callStopAlt();

    /* 0x3c */ u16 lastRandomSeId;
    /* 0x3e */ u8 kind;
    /* 0x3f */ u8 alternateFlags;
};

#endif
