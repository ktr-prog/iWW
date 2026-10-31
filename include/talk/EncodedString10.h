#ifndef TALK_ENCODEDSTRING10_H
#define TALK_ENCODEDSTRING10_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString10 : public EncodedString {
public:
    EncodedString10();
    virtual ~EncodedString10();
    virtual u32 capacity();
    virtual u8 *data();
    void copyTo(void *dst, s32 n);

    /* 0x0e */ u8 text[0xa];
};

#endif
