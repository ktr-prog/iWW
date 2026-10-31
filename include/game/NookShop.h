#ifndef GAME_NOOKSHOP_H
#define GAME_NOOKSHOP_H

#include "types.h"
#include "item/ItemId.h"
#include "game/ShopDate.h"
#include "sys/ClockDate.h"

struct Bits5a {
    u16 saleHour : 5;
    u16 paintCounter : 4;
    u16 level : 2;
    u16 unk_0b : 5;
};

struct NookShopRenovation {
    /* 0x0 */ ShopDate date;
    /* 0x3 */ u8 scheduled;
};

struct NookShop {
    /* 0x00 */ u32 sales;
    /* 0x04 */ ItemId e[0x25];
    /* 0x4e */ ShopDate stockDate;
    /* 0x51 */ u8 stockStale;
    /* 0x52 */ ClockDate pointSpecialDate;
    /* 0x56 */ NookShopRenovation renovation;
    /* 0x5a */ Bits5a packedState;
    /* 0x5c */ u8 sold[5];
    NookShop();
};

#endif
