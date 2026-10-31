#ifndef GAME_REDDSHOP_H
#define GAME_REDDSHOP_H

#include "types.h"
#include "item/ItemId.h"
#include "game/ReddPassword.h"

class ReddShop {
public:
    /* 0x00 */ ItemId arr[3];
    /* 0x08 */ ReddPassword s;
    /* 0x10 */ u8 sold[4];

    ReddShop();
    ~ReddShop();
    void restock();
    ReddPassword *getPassword();
    void clearStock();
    void reset();
};

#endif
