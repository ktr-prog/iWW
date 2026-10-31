#ifndef TALK_ENCODEDSTRING8B_H
#define TALK_ENCODEDSTRING8B_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString8B : public EncodedString {
public:
    EncodedString8B();
    virtual ~EncodedString8B();
    virtual u32 capacity();
    virtual u8 *data();
    void copyBytesTo(void *p, u32 n);

    /* 0x0e */ u8 text[10];
};

#endif
