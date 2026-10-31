#ifndef FIELD_MONEYROCKSTATE_H
#define FIELD_MONEYROCKSTATE_H

#include "types.h"

struct MoneyRockState {
    u8 y;
    u8 x;
    s16 hits;
    s16 timer;
    u8 pad_06[2];
};

#endif
