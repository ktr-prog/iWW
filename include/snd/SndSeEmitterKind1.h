#ifndef SND_SNDSEEMITTERKIND1_H
#define SND_SNDSEEMITTERKIND1_H

#include "types.h"
#include "snd/SndSeEmitter.h"

class SndSeEmitterKind1 : public SndSeEmitter {
public:
    SndSeEmitterKind1();
    virtual ~SndSeEmitterKind1();
    static void onVolume(SndHandle *h, s32 idx);

    /* 0x40 */ u8 volume;
};

#endif
