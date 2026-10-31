#ifndef SAVE_PATTERNORDER_H
#define SAVE_PATTERNORDER_H

#include "types.h"


class PatternOrder {
public:
    PatternOrder();
    ~PatternOrder();
    /* 0x0 */ u8 slots[8];
    u32 getSlot(u32 i);
    void swap(u32 a, u32 b);
    void reset();
};

#endif
