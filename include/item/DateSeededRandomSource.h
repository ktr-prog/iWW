#ifndef ITEM_DATESEEDEDRANDOMSOURCE_H
#define ITEM_DATESEEDEDRANDOMSOURCE_H

#include "types.h"
#include "item/RandomSource.h"

class DateSeededRandomSource : public RandomSource {
public:
    DateSeededRandomSource();
    ~DateSeededRandomSource();
    virtual u8 getYear();
    virtual u8 getMonth();
    virtual u8 getDay();
    virtual u32 random(u32 n);
    void seed(u8 a, u8 b, u8 c);
    void seedFromToday();

    /* 0x04 */ u32 rngState;
    /* 0x08 */ u8 year;
    /* 0x09 */ u8 month;
    /* 0x0a */ u8 day;
};

#endif
