#ifndef FIELD_SNOWMANRECORDS_H
#define FIELD_SNOWMANRECORDS_H

#include "types.h"

class SnowmanRecord {
public:
    SnowmanRecord();
    ~SnowmanRecord();
    s32 getDaysSinceBuilt();
    u32 getRank();
    s32 getBodySize();
    s32 getHeadSize();
    void build(u32 a, u32 b, u32 c);
    BOOL isUsed();
    void clear();

    u16 a0 : 7;
    u16 a1 : 4;
    u16 a2 : 5;
    u16 b0 : 7;
    u16 b1 : 7;
    u16 b2 : 2;
    u8 c4;
    u8 c5;
};

static_assert(sizeof(SnowmanRecord) == 6, "SnowmanRecord: the save layout");

class SnowmanRecords {
public:
    SnowmanRecords();
    ~SnowmanRecords();
    void markUnplaced(u32 idx);
    BOOL isFull();
    BOOL getInfo(u32 idx, u32 *a, u32 *b, u32 *c, u8 *d, u8 *e, u8 *f);
    s32 add(u32 a, u32 b, u32 c);
    BOOL remove(u32 idx);
    void clearAll();
    void updateDaily();

    SnowmanRecord e[3];
};

#endif
