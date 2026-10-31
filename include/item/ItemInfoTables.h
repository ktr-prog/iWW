#ifndef ITEM_ITEMINFOTABLES_H
#define ITEM_ITEMINFOTABLES_H

#include "types.h"
#include "game/InfoTableSet.h"
#include "sys/RecordFile.h"

class ItemInfoTables : public InfoTableSet {
public:
    ItemInfoTables();
    ~ItemInfoTables();

    /* 0x54 */ RecordFile series;
};

#endif
