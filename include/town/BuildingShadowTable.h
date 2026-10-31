#ifndef TOWN_BUILDINGSHADOWTABLE_H
#define TOWN_BUILDINGSHADOWTABLE_H

#include "types.h"
#include "town/Unk_ov009_0225b880.h"

struct BuildingShadowTable {
    BuildingShadowEntry *getEntry(u32 i);
    u32 getCount();

    /* 0x00 */ u32 count;
    /* 0x04 */ BuildingShadowEntry entries[1];
};

#endif
