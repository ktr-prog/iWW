#ifndef TALK_ENCODEDSTRING512_H
#define TALK_ENCODEDSTRING512_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString512 : public EncodedString {
public:
    EncodedString512();
    virtual ~EncodedString512();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x0e */ u8 text[0x200];
};

#endif
