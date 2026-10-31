#ifndef TALK_ENCODEDSTRING16_H
#define TALK_ENCODEDSTRING16_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString16 : public EncodedString {
public:
    EncodedString16();
    virtual ~EncodedString16();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x0e */ u8 text[0x10];
};

#endif
