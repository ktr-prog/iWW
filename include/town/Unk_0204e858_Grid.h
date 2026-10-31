#ifndef TOWN_UNK_0204E858_GRID_H
#define TOWN_UNK_0204E858_GRID_H

#include "types.h"
#include "town/TownBlockCell.h"


struct Unk_0204e858_Grid {
    /* 0x00 */ TownBlockCell *blocks;
    /* 0x04 */ u32 width;
    /* 0x08 */ u32 height;
};

#endif
