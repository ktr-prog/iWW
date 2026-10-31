#ifndef GAME_TOUCHPICKER_H
#define GAME_TOUCHPICKER_H

#include "types.h"
#include "gfx/VecFx32.h"

struct TouchPickTriangle;
struct TouchPickSphere;
struct TouchPickCylinder;
struct TouchPickBox;

struct TouchPickResult {
    TouchPickResult();
    ~TouchPickResult();
    void resetResult(u8 a);
    /* 0x00 */ s32 groundX;
    /* 0x04 */ s32 groundY;
    /* 0x08 */ s32 groundZ;
    /* 0x0c */ s32 targetX;
    /* 0x10 */ s32 targetY;
    /* 0x14 */ s32 targetZ;
    /* 0x18 */ u8 targetKind;
    /* 0x19 */ u8 targetIndex;
    /* 0x1a */ u8 enabled;
    MWCC_LAYOUT
};

struct TouchPicker : TouchPickResult {
    TouchPicker();
    ~TouchPicker();
    void reset();
    BOOL addTriangle(TouchPickTriangle *o, VecFx32 *a, VecFx32 *b, VecFx32 *c, s32 d, u8 e);
    BOOL pushTriangle(TouchPickTriangle *o);
    BOOL addCylinder(TouchPickCylinder *o, VecFx32 *pos, s32 radius, s32 height, s32 kind, u8 index);
    BOOL pushCylinder(TouchPickCylinder *o);
    BOOL addSphere(TouchPickSphere *o, VecFx32 *pos, s32 radius, s32 kind, u8 index);
    BOOL pushSphere(TouchPickSphere *o);
    BOOL addBox(TouchPickBox *box, VecFx32 *pos, s32 w, s32 h, s32 d, s16 angle, s32 e, u8 f);
    BOOL pushBox(TouchPickBox *box);
    /* 0x1c */ TouchPickTriangle *triangles;
    /* 0x20 */ TouchPickSphere *spheres;
    /* 0x24 */ TouchPickCylinder *cylinders;
};

#endif
