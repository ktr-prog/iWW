#ifndef ITEM_ITEMNAME_H
#define ITEM_ITEMNAME_H

#include "types.h"
#include "talk/MsgString.h"

class ItemName : public MsgString {
public:
    ItemName();
    ItemName(s32 idx);
    ItemName(u16 *p);
    virtual ~ItemName();
    virtual u32 capacity();
    virtual u8 *data();
    u8 setString(u8 *str);
    BOOL setSeriesName(s32 idx);
    BOOL setFromItem(u16 *p);

    /* 0x12 */ u8 text[0x11];
};

#endif
