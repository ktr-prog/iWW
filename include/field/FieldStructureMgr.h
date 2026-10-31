#ifndef FIELD_FIELDSTRUCTUREMGR_H
#define FIELD_FIELDSTRUCTUREMGR_H

#include "types.h"
#include "sys/ProcBase.h"

struct NNSG3dResTex;

class FieldStructureMgr : public GameProc {
public:
    FieldStructureMgr();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~FieldStructureMgr();
};

class PlayerHouseTex {
public:
    PlayerHouseTex();
    ~PlayerHouseTex();
    NNSG3dResTex *tex;
};

class HouseLightUpDeco {
public:
    HouseLightUpDeco();
    ~HouseLightUpDeco();
    /* 0x00 */ NNSG3dResTex *tex;
    /* 0x04 */ void *models[5];
    /* 0x18 */ void *texPattern;
    /* 0x1c */ u8 isLoaded;
};

class VillagerHouseTex {
public:
    VillagerHouseTex();
    ~VillagerHouseTex();
    /* 0x00 */ NNSG3dResTex *houseTextures[4];
    /* 0x10 */ NNSG3dResTex *lightTextures[4];
    /* 0x20 */ void *doorInAnim;
    /* 0x24 */ void *doorOutAnim;
};

#endif
