#ifndef TOWN_SHOPCLOSINGTIME_H
#define TOWN_SHOPCLOSINGTIME_H

#include "types.h"

class ShopClosingTime {
public:
    BOOL isPastClosingTime();
    void setClosingTimeToday();
    ShopClosingTime *getTime();
    void clearClosingTime();
    void destruct();
    void construct();

    union {
        struct {
            /* 0x0 */ u8 second;
            /* 0x1 */ u8 minute;
            /* 0x2 */ u8 hour;
        };
        /* 0x0 */ s32 raw[2];
    };
};

#endif
