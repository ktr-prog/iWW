#ifndef GAME_INFOTABLESET_H
#define GAME_INFOTABLESET_H

#include "types.h"
#include "sys/RecordFile.h"

class InfoTableSet {
public:
    InfoTableSet();
    ~InfoTableSet();
    RecordFile *getDma();
    RecordFile *getIndoor();
    RecordFile *getAlways();
    BOOL freeIndoor();
    BOOL loadIndoor(s32 v);
    void close();
    BOOL open(void *a, s32 n0, void *b, s32 n1, void *c, s32 n2, s32 count);

    /* 0x00 */ RecordFile alwaysTable;
    /* 0x1c */ RecordFile indoorTable;
    /* 0x38 */ RecordFile dmaTable;
};

#endif
