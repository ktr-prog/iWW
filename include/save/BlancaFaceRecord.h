#ifndef SAVE_BLANCAFACERECORD_H
#define SAVE_BLANCAFACERECORD_H

#include "types.h"

class BlancaFaceRecord {
public:
    BlancaFaceRecord() { construct(); }
    ~BlancaFaceRecord() { destruct(); }
    u16 getChecksum();
    void setChecksum(u32 v);
    BOOL isBlancaDue();
    u8 getConcept();
    void setConcept(u32 v);
    u8 getState();
    void setState(u32 v);
    void *getPattern();
    void resetPattern();
    void init();
    void reset();
    BlancaFaceRecord *destruct();
    BlancaFaceRecord *construct();

    /* 0x000 */ u32 pattern[0x228 / 4];
    /* 0x228 */ u16 checksum;
    /* 0x22a */ u8 visitState;
    /* 0x22b */ u8 concept;
};

#endif
