#ifndef SAVE_SAVERECORD4_H
#define SAVE_SAVERECORD4_H

#include "types.h"

class SaveRecord4 {
public:
    BOOL isDateActive();
    void expireDate();
    void setDateToday(void *src);
    void resetDate();
    u8 getStamp();
    void setStamp(u8 v);
    void newStamp();
    BOOL isStateUnset();
    BOOL isStateValid();
    void setStateValidAlt();
    void markInterrupted();
    void clearState();
    void setStateValid();
    void destruct();
    void construct();

    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
};

#endif
