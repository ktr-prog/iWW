#ifndef ITEM_ITEMICONCACHE_H
#define ITEM_ITEMICONCACHE_H

#include "types.h"


struct ItemIconCache {
    /* 0x004 */ u8 iconChars[0x800];
    /* 0x804 */ u8 loadedPage;

    ItemIconCache();
    virtual ~ItemIconCache();
    u8 *getPresentChars(s32 idx, s32 variant);
    u8 *getIconChars(s32 idx);
    void invalidate();
};

#endif
