#ifndef ITEM_ITEMID_H
#define ITEM_ITEMID_H

#include "types.h"

struct ItemId {
    /* 0x0 */ u16 id;

#ifdef __cplusplus
    ItemId();
    constexpr ItemId(u16 x) : id(x) {}
    ~ItemId();
#endif
};
#ifndef __cplusplus
typedef struct ItemId ItemId;
#endif

#endif
