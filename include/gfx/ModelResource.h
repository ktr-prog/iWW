#ifndef GFX_MODELRESOURCE_H
#define GFX_MODELRESOURCE_H

#include "types.h"
#include "gfx/TexVramTask.h"

class TexVramSlot;
class Heap;

class ModelResource {
public:
    void *fileData;
    Heap *fileHeap;
    void *model;
    void *texture;
    TexVramTask texVramTask;
    u8 loadState;
    u8 unk_31;

    ModelResource();
    virtual ~ModelResource();
    u32 loadTexture(void *a, TexVramSlot *b, void *c);
    u32 loadModel(void *res, TexVramSlot *b, void *tex, void *heap);
    void release(void);
    void *getTexture(void);
    void *getModel(void);
};

#endif
