#ifndef GAME_UNITSHAPEQUERYX_H
#define GAME_UNITSHAPEQUERYX_H

#include "types.h"

struct UnitShapeQueryX {
    UnitShapeQueryX();
    virtual ~UnitShapeQueryX();
    virtual BOOL getUnitShape(s32 *a, s32 *b, s32 *c, s32 x, s32 z);
};

#endif
