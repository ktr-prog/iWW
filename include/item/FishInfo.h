#ifndef ITEM_FISHINFO_H
#define ITEM_FISHINFO_H

#include "types.h"

struct FishInfo {
    u8 sizeClass;
    u8 rodClass;
    u8 timingClass;
    u16 baseSize;
};

#define FISH_INFO_COUNT 0x3b

extern "C" const FishInfo gFishInfo[FISH_INFO_COUNT];

#endif
