#ifndef SAVE_MOTHERLETTERSTATE_H
#define SAVE_MOTHERLETTERSTATE_H

#include "types.h"

class MotherLetterState {
public:
    void setBirthdayLetterYear(u32 v);
    u8 getBirthdayLetterYear();
    BOOL isSent(s32 i);
    void clearSent(s32 i);
    void setSent(s32 i);
    BOOL testFlag(u32 mask);
    void setFlag(u32 mask);
    void setLastDate(s32 *v);
    BOOL checkLastDate(s32 *v);
    void clear();

    /* 0x00 */ u8 lastDay;
    /* 0x01 */ u8 lastMonth;
    /* 0x02 */ u8 lastYear;
    /* 0x03 */ u8 birthdayYearFlags;
    /* 0x04 */ u8 sentBits[15];
    /* 0x13 */ u8 pad_13;
};

#endif
