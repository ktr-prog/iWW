#ifndef TALK_ENCODEDSTRING16B_H
#define TALK_ENCODEDSTRING16B_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString16B : public EncodedString {
public:
    EncodedString16B();
    virtual ~EncodedString16B();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x0e */ u8 text[0x10];
};

#endif
