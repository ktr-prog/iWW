#ifndef GAME_COLLISIONCYLINDER_H
#define GAME_COLLISIONCYLINDER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/CollisionCircle.h"

class CollisionCylinder : public CollisionCircle {
public:
    /* 0x10 */ s32 cylinderHeight;

    BOOL clipSegmentSideBounded(VecFx32 *out, VecFx32 *a);
    BOOL clipSegmentCaps(VecFx32 *out, VecFx32 *a);
    ~CollisionCylinder();
    CollisionCylinder(VecFx32 *pos, s32 radius, s32 height);
    CollisionCylinder();
};

class CollisionCylinderX : public CollisionCircle {
public:
    /* 0x10 */ s32 cylinderHeight;

    BOOL clipSegmentSideBounded(VecFx32 *out, VecFx32 *a) {
        return reinterpret_cast<CollisionCylinder *>(this)->clipSegmentSideBounded(out, a);
    }
    BOOL clipSegmentCaps(VecFx32 *out, VecFx32 *a) {
        return reinterpret_cast<CollisionCylinder *>(this)->clipSegmentCaps(out, a);
    }
    BOOL clipSegmentSide(VecFx32 *out, VecFx32 *a);
    BOOL clipSegmentTop(VecFx32 *out, VecFx32 *a);
    BOOL landOnTop(VecFx32 *out, VecFx32 *a);
    BOOL pushOut(VecFx32 *pos, s32 r);
    void setCylinder(VecFx32 *pos, s32 radius, s32 height);
    ~CollisionCylinderX();
    CollisionCylinderX(VecFx32 *pos, s32 radius, s32 height);
    CollisionCylinderX();
};

#endif
