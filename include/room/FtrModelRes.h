#ifndef ROOM_FTRMODELRES_H
#define ROOM_FTRMODELRES_H

#include "types.h"
#include "gfx/ModelResource.h"
#include "room/FtrAnimSet.h"

class ModelSlot;

struct FtrModelRes {
    FtrModelRes();
    ~FtrModelRes();
    /* 0x00 */ void *texFile;
    /* 0x04 */ void *arcFile;
    /* 0x08 */ void *model;
    /* 0x0c */ void *texture;
    /* 0x10 */ ModelResource texLoader;
    /* 0x44 */ FtrAnimSet animSet;
    /* 0x70 */ u16 item;
    /* 0x72 */ u8 keepTexCopy;

    void release();
    void *getTexture();
    void *getModel();
    BOOL loadAsync(ModelSlot *obj, s32 a, s32 flag);
    BOOL loadSync(ModelSlot *obj, s32 a, s32 flag);
    void freeTexFile();
    FtrAnimSet *getAnimSet();
    BOOL loadFiles(ModelSlot *obj, s32 id);
    char *makeTexPath(s32 id);
    char *makeArcPath(s32 id);
    BOOL isLoaded();
};

#endif
