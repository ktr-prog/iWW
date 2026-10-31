#ifndef ROOM_FTRGLOWMAT_H
#define ROOM_FTRGLOWMAT_H

#include "types.h"
#include "game/LightLevel.h"

class G3dResAccess;

struct FtrGlowMat : public LightLevel {
    FtrGlowMat();
    ~FtrGlowMat();
    BOOL setLit(BOOL on, s32 a, s32 b);
    BOOL bindMaterial(G3dResAccess *res, const char *matName, BOOL on);
    void updateEmission();
    /* 0x14 */ s8 matIdx;
    /* 0x18 */ G3dResAccess *resMdl;
};

#endif
