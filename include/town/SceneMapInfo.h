#ifndef TOWN_SCENEMAPINFO_H
#define TOWN_SCENEMAPINFO_H

#include "types.h"

struct SceneMapInfo {
    void createMapModule();

    /* 0x0 */ u32 *acreIds;
    /* 0x4 */ u8 width;
    /* 0x5 */ u8 height;
    /* 0x6 */ u16 moduleParam;
};

#endif
