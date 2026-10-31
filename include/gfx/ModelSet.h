#ifndef GFX_MODELSET_H
#define GFX_MODELSET_H

#include "types.h"

class CachedModel;

class ModelSet {
public:
    /* 0x04 */ u32 numModels;
    /* 0x08 */ CachedModel *models;
    /* 0x0c */ u8 *modelNames;
    ModelSet();
    virtual ~ModelSet();
};

#endif
