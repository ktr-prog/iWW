#ifndef ITEM_FUTURELETTER_H
#define ITEM_FUTURELETTER_H

#include "types.h"
#include "item/Letter.h"

class FutureLetter : public Letter {
public:
    void clearFutureLetter();
    u8 *getDeliveryDate();

    /* 0xf4 */ u8 deliveryDay;
    /* 0xf5 */ u8 deliveryMonth;
    /* 0xf6 */ u8 deliveryYear;
    /* 0xf7 */ u8 unk_f7;
};

static_assert(sizeof(FutureLetter) == 0xf8, "FutureLetter: PlayerData::futureLetter");

#endif
