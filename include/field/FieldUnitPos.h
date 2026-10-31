#ifndef FIELD_FIELDUNITPOS_H
#define FIELD_FIELDUNITPOS_H

#include "types.h"
#include "gfx/VecFx32.h"

struct FieldUnitPos {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 z;
    FieldUnitPos() {}
    FieldUnitPos(s32 a, s32 b) { x = a; z = b; }
    FieldUnitPos(const FieldUnitPos &o) { x = o.x; z = o.z; }
    FieldUnitPos(const VecXZ &o) { x = o.x; z = o.z; }
    bool operator==(const FieldUnitPos &o) const { return x == o.x && z == o.z; }
};

#endif
