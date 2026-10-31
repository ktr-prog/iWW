#ifndef TOWN_TOWNUNITSHAPEQUERY_H
#define TOWN_TOWNUNITSHAPEQUERY_H

#include "types.h"
#include "game/UnitShapeQueryX.h"

class TownUnitShapeQuery : public UnitShapeQueryX {
public:
    TownUnitShapeQuery();
    virtual ~TownUnitShapeQuery();
    virtual BOOL getUnitShape(s32 *a, s32 *b, s32 *c, volatile s32 x, volatile s32 y);
};

#endif
