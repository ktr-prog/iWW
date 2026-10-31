#ifndef GFX_POOLEDMODEL_H
#define GFX_POOLEDMODEL_H

#include "types.h"
#include "gfx/ModelResource.h"

class ModelSlot;

class PooledModel {
public:
    PooledModel();
    ~PooledModel();
    void *getModel();
    void unload();
    void reset();
    s32 loadFromSlot(ModelSlot *e, const char *name);

    /* 0x00 */ ModelResource resource;
    /* 0x34 */ u8 isLoaded;
    /* 0x38 */ void *slot;
    /* 0x3c */ void *unk_3c;
};

#endif
