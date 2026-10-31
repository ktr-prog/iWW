#ifndef MENU_INVENTORYITEMGRID_H
#define MENU_INVENTORYITEMGRID_H

#include "types.h"
#include "item/ItemIconCache.h"
#include "gfx/BgVramTask.h"

struct ItemIconUploadChars {
    /* 0x00 */ u8 top[0x40];
    /* 0x40 */ u8 bottom[0x40];
};

struct InventoryItemGrid {
    InventoryItemGrid();
    virtual ~InventoryItemGrid();

    /* 0x004 */ ItemIconUploadChars iconUploadChars[3];
    /* 0x184 */ ItemIconCache iconCache;
    /* 0x98c */ BgVramTaskPair iconUploadTasks[3];
    /* 0xa34 */ u16 *boxItems;
    /* 0xa38 */ u32 occupiedBits[2];
    /* 0xa40 */ u32 markedBits[2];
    /* 0xa48 */ u32 disabledBits[2];
    /* 0xa50 */ u32 objPriority;
    /* 0xa54 */ u16 presentItem;
    /* 0xa56 */ u8 cursorSlot;
    /* 0xa57 */ u8 cursorLiftTimer;
    /* 0xa58 */ u8 numIconUploads;
    /* 0xa59 */ u8 heldScale;
    /* 0xa5a */ u8 presentAnimStep;
    /* 0xa5b */ u8 presentVariant;
    /* 0xa5c */ u8 showHeldFocus;
};

#endif
