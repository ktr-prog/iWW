#ifndef FIELD_INSECTSPAWNLIST_H
#define FIELD_INSECTSPAWNLIST_H

#include "types.h"

typedef struct InsectSpawnEntry {
    u8 kind;
    u8 cumulativeChance;
} InsectSpawnEntry;

typedef struct InsectSpawnList {
    InsectSpawnEntry *entries;
    u8 entryCount;
} InsectSpawnList;

#endif
