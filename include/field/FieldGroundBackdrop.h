#ifndef FIELD_FIELDGROUNDBACKDROP_H
#define FIELD_FIELDGROUNDBACKDROP_H

#include "types.h"
#include "gfx/CachedModel.h"

struct NNSG3dResMdl;

class FieldGroundBackdrop {
public:
    FieldGroundBackdrop();
    ~FieldGroundBackdrop();
    BOOL followCamera();
    BOOL init();
    void clear();

    /* 0x00 */ CachedModel model;
    /* 0x9c */ NNSG3dResMdl *modelRes;
};

#endif
