#ifndef TALK_MSGSTRING17_H
#define TALK_MSGSTRING17_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString17 : public MsgString {
public:
    MsgString17();
    virtual ~MsgString17();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x11];
};

#endif
