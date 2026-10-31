#ifndef ITEM_LETTEROUTBOX_H
#define ITEM_LETTEROUTBOX_H

#include "types.h"
#include "item/Letter.h"

class LetterOutbox {
public:
    LetterOutbox();
    ~LetterOutbox();
    Letter *getLetter(s32 i);
    void clear();
    BOOL testFlag(u32 mask);
    void setFlag(u32 mask);
    u8 *getLastDeliveryTime();

    /* 0x000 */ Letter letters[10];
    /* 0x988 */ u8 lastDeliveryDay;
    /* 0x989 */ u8 lastDeliveryMonth;
    /* 0x98a */ u8 lastDeliveryYear;
    /* 0x98b */ u8 lastDeliveryHour;
    /* 0x98c */ u16 flags;
    /* 0x98e */ u16 pad_98e;
};

static_assert(sizeof(LetterOutbox) == 0x990, "LetterOutbox: SaveData::letterOutbox");

#endif
