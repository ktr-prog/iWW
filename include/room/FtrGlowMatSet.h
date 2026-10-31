#ifndef ROOM_FTRGLOWMATSET_H
#define ROOM_FTRGLOWMATSET_H

#include "types.h"
#include "room/FtrGlowMat.h"

class FtrGlowMatSet {
public:
    FtrGlowMatSet();
    ~FtrGlowMatSet();
    void update();
    u32 setLit(u32 a, u32 b, u32 c);
    u32 init(void *mdl, u32 b);

    /* 0x00 */ FtrGlowMat mats[3];
    /* 0x54 */ u8 anyBound;
};

#endif
