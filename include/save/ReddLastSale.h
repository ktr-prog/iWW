#ifndef SAVE_REDDLASTSALE_H
#define SAVE_REDDLASTSALE_H

#include "types.h"

struct ReddSaleName {
    u8 b[8];
};

struct ReddLastSale {
    u16 townId;
    ReddSaleName townName;
    u16 playerId;
    ReddSaleName playerName;
    s8 gender;
    u8 unk_15;
    u16 item;
    void copyItemFrom(const ReddLastSale *o);
    void setItem(const ReddLastSale *o);
    void setBuyer(const ReddLastSale *o);
    void clear();
    ReddLastSale();
    ~ReddLastSale();
};

#endif
