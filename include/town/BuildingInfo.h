#ifndef TOWN_BUILDINGINFO_H
#define TOWN_BUILDINGINFO_H

#include "types.h"

#ifndef __cplusplus
typedef struct BuildingInfo BuildingInfo;
#endif

struct BuildingInfo {
    /* 0x0 */ u16 profile;
    /* 0x2 */ u8 entranceType;
    /* 0x3 */ u8 kind;
    /* 0x4 */ s8 interiorScene;
    /* 0x5 */ u8 flickeringLights;
    /* 0x6 */ u8 viewRangeX;
    /* 0x7 */ u8 viewRangeFront;
    /* 0x8 */ u8 viewRangeBack;
    /* 0x9 */ u8 capacity;
};

#endif
