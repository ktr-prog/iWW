#ifndef TALK_MSGSTRINGBASE_H
#define TALK_MSGSTRINGBASE_H

#include "types.h"

class MsgStringBase {
public:
    virtual ~MsgStringBase() {}
    virtual u32 capacity() = 0;
    virtual u8 *data() = 0;
};

#endif
