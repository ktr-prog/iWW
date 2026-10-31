#ifndef SAVE_BBSPOST_H
#define SAVE_BBSPOST_H

#include "types.h"

class BbsPost {
public:
    BbsPost();
    ~BbsPost();

    void markFreeText();
    BOOL isFreeText();
    void setRead(s32 i);
    BOOL isRead(s32 i);
    u8 getYear();
    u8 getMonth();
    u8 getDay();
    void init(u8 *src);

    /* 0x00 */ u8 text[0xc0];
    /* 0xc0 */ u8 day;
    /* 0xc1 */ u8 month;
    /* 0xc2 */ u8 year;
    /* 0xc3 */ u8 flags;
};

#endif
