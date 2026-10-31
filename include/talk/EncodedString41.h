#ifndef TALK_ENCODEDSTRING41_H
#define TALK_ENCODEDSTRING41_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString41 : public EncodedString {
public:
    EncodedString41();
    virtual ~EncodedString41();
    virtual u32 capacity();
    virtual u8 *data();

    s32 getLength();

    /* 0x0e */ u8 text[0x29];
};

#endif
