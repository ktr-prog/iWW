#ifndef FIELD_FIELDOBJECTSHAPEQUERY_H
#define FIELD_FIELDOBJECTSHAPEQUERY_H

#include "types.h"
#include "game/UnitShapeQueryX.h"

class FieldObjectShapeQuery : public UnitShapeQueryX {
public:
    virtual BOOL getUnitShape(s32 *a, s32 *b, s32 *c, s32 x, s32 z);
    virtual ~FieldObjectShapeQuery() {}
};

#endif
