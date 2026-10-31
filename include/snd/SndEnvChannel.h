#ifndef SND_SNDENVCHANNEL_H
#define SND_SNDENVCHANNEL_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/SndSeqHandle.h"

class SndEnvChannel {
public:
    SndEnvChannel() {}
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void requestSustained(u32 v);
    virtual void request(u32 v);
    virtual void update(VecFx32 *pos);

    void callRelease();
    void callRequest(u32 id);
    void callRequestSustained(u32 id);
    void callUpdate(void *a);
    void callUpdateRelative(VecFx32 *pos);
    void callReset();

    /* 0x04 */ SndSeqHandle h;
    /* 0x08 */ u16 v;
    /* 0x0a */ u8 flags;
};

#endif
