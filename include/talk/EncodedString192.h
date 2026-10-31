#ifndef TALK_ENCODEDSTRING192_H
#define TALK_ENCODEDSTRING192_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString192 : public EncodedString {
public:
    EncodedString192();
    virtual ~EncodedString192();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x0e */ u8 text[0xb2];
};

#endif
