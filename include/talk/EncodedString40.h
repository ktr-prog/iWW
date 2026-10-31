#ifndef TALK_ENCODEDSTRING40_H
#define TALK_ENCODEDSTRING40_H

#include "types.h"
#include "talk/EncodedString.h"

class EncodedString40 : public EncodedString {
public:
    EncodedString40() {}
    virtual ~EncodedString40() {}
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x0e */ u8 text[0x28];
};

#endif
