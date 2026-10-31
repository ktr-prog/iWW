#ifndef GAME_SHOPACKCOUNTER_H
#define GAME_SHOPACKCOUNTER_H

#include "types.h"

struct ShopAckCounter {
    ShopAckCounter();
    ~ShopAckCounter();
    /* 0x0 */ u8 needed;
    /* 0x1 */ u8 received;
};

#endif
