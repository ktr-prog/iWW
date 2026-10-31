#ifndef TALK_MSGSTRING17B_H
#define TALK_MSGSTRING17B_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString17B : public MsgString {
public:
    MsgString17B();
    virtual ~MsgString17B();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x11];
};

#endif
