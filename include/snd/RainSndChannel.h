#ifndef SND_RAINSNDCHANNEL_H
#define SND_RAINSNDCHANNEL_H

#include "types.h"
#include "snd/SndEnvChannel.h"

class RainSndChannel : public SndEnvChannel {
public:
    RainSndChannel() {}
    virtual void vfunc_00();

    /* 0x0c */ s32 volume;
};

#endif
