#ifndef PLAYER_PMRAW_H
#define PLAYER_PMRAW_H

#include "types.h"

struct PMRaw {
    /* 0x0 */ void (*f)();
    /* 0x4 */ s32 d;
};

#endif
