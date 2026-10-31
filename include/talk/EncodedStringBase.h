#ifndef TALK_ENCODEDSTRINGBASE_H
#define TALK_ENCODEDSTRINGBASE_H

#include "types.h"

class EncodedStringBase {
public:
    virtual ~EncodedStringBase() {}
    virtual u32 capacity() = 0;
    virtual u8 *data() = 0;
};

#endif
