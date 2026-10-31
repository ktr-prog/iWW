#ifndef ITEM_RANDOMSOURCE_H
#define ITEM_RANDOMSOURCE_H

#include "types.h"

class RandomSource {
public:
    RandomSource();
    ~RandomSource();
    virtual u8 getYear();
    virtual u8 getMonth();
    virtual u8 getDay();
    virtual u32 random(u32 n);
};

#endif
