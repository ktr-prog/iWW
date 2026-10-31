#ifndef TOWN_BUILDINGRESOURCES_H
#define TOWN_BUILDINGRESOURCES_H

#include "types.h"

struct BuildingShadowTable;
struct NNSG3dResMdl;

struct BuildingResources {
    BuildingResources();
    ~BuildingResources();

    /* 0x00 */ NNSG3dResMdl *bmd0;
    /* 0x04 */ NNSG3dResMdl *bmd1;
    /* 0x08 */ void *bca0;
    /* 0x0c */ void *bca1;
    /* 0x10 */ void *bca2;
    /* 0x14 */ void *tex;
    /* 0x18 */ void *lightTex;
    /* 0x1c */ BuildingShadowTable *shadowTable;
    /* 0x20 */ void *btaAnims[4];
    /* 0x30 */ void *btpAnims[4];
    /* 0x40 */ s32 solidCenterX;
    /* 0x44 */ s32 solidCenterZ;
    /* 0x48 */ s32 solidSizeX;
    /* 0x4c */ s32 solidSizeZ;
};

#endif
