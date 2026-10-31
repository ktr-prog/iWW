#ifndef ITEM_ITEMCLASSORDERS_H
#define ITEM_ITEMCLASSORDERS_H

#include "types.h"

class RandomSource;


class ItemClassOrder {
public:
    ItemClassOrder();
    ~ItemClassOrder();
    u32 getClassOfWeight(u32 x);
    u32 getIndex();
    u32 pickClass(s32 mode, RandomSource *rng);
    u8 *getWeights();
    void randomize();

    /* 0x00 */ u8 orderIndex;
};

class ItemClassOrders {
public:
    ItemClassOrders();
    ~ItemClassOrders();
    void randomizeAll();
    ItemClassOrder *get(s32 i);

    /* 0x00 */ ItemClassOrder orders[9];
};

#endif
