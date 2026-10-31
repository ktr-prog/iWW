#ifndef TOWN_MAPBLOCKENTRY_H
#define TOWN_MAPBLOCKENTRY_H

#include "types.h"

struct MapBlockEntry {
    /* 0x00 */ u32 acreId;
    /* 0x04 */ u16 *layers[2];
    /* 0x0c */ u16 *buried;
#ifdef __cplusplus
    MapBlockEntry();
#endif
};
#ifndef __cplusplus
typedef struct MapBlockEntry MapBlockEntry;
#endif

#endif
