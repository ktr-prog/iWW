#ifndef SND_SKYSNDCHANNEL_H
#define SND_SKYSNDCHANNEL_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/SndEnvChannel.h"


class SkySndChannel : public SndEnvChannel {
public:
    virtual void vfunc_00();
    virtual void requestSustained(u32 v);
    virtual void request(u32 v);
    virtual void update(VecFx32 *pos);
};

#endif
