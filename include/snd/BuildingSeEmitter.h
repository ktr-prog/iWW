#ifndef SND_BUILDINGSEEMITTER_H
#define SND_BUILDINGSEEMITTER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/Unk_0213b9c4.h"

class BuildingSeEmitter {
public:
    BuildingSeEmitter();

    void playSeHeld(u32 a);
    void playSe(u32 a);
    void deactivate();
    void setPosition(VecFx32 *v);
    void activate();

    /* 0x00 */ Unk_0213b9c4 emitter;
    /* 0x40 */ u8 active;
};

#endif
