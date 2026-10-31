#ifndef SND_CREATURESNDCHANNEL_H
#define SND_CREATURESNDCHANNEL_H

#include "types.h"
#include "snd/SndEnvChannel.h"

class CreatureSndChannel : public SndEnvChannel {
public:
    CreatureSndChannel() {}
    virtual void vfunc_00();
};

#endif
