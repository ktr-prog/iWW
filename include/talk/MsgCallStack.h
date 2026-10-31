#ifndef TALK_MSGCALLSTACK_H
#define TALK_MSGCALLSTACK_H

#include "types.h"

class MsgCallStack {
public:
    MsgCallStack();
    ~MsgCallStack();
    BOOL isEmpty();
    void push(u8 *const &value);
    u8 **top();
    void pop();

    /* 0x00 */ u8 *entries[6];
    /* 0x18 */ u32 depth;
};

#endif
