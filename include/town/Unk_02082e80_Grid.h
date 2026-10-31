#ifndef TOWN_UNK_02082E80_GRID_H
#define TOWN_UNK_02082E80_GRID_H

#include "types.h"
#include "town/TownBlockCell.h"


struct Unk_02082e80_Grid {
    /* 0x00 */ TownBlockCell *blocks;
    /* 0x04 */ u32 size[2];
};

struct Unk_02082e80_Pos {
    s32 x, y;
    Unk_02082e80_Pos() { x = 0; y = 0; }
};

#endif
