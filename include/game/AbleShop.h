#ifndef GAME_ABLESHOP_H
#define GAME_ABLESHOP_H

#include "types.h"
#include "item/ItemId.h"
#include "game/ShopDate.h"

struct AbleShop {
    /* 0x00 */ ItemId items[6];
    /* 0x0c */ ShopDate stockDate;
    /* 0x0f */ u8 stockStale;
    /* 0x10 */ u8 sold[2];
};

#endif
