#ifndef TALK_MSGSTRING9B_H
#define TALK_MSGSTRING9B_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString9B : public MsgString {
public:
    MsgString9B();
    virtual ~MsgString9B();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[9];
};

#endif
