#ifndef ITEM_ITEMPICKSPEC_H
#define ITEM_ITEMPICKSPEC_H

#include "types.h"

struct ItemPickSpec {
    ItemPickSpec() {}
    ItemPickSpec(s32 a, s32 b) { set(a, b); }
    ItemPickSpec(const ItemPickSpec &o) { listIndex = o.listIndex; itemClass = o.itemClass; }
    ~ItemPickSpec();
    s32 getClass();
    s32 getList();
    void set(s32 a, s32 b);

    /* 0x0 */ s32 listIndex;
    /* 0x4 */ s32 itemClass;
};

#endif
