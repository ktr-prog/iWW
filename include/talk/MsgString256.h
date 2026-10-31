#ifndef TALK_MSGSTRING256_H
#define TALK_MSGSTRING256_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString256 : public MsgString {
public:
    MsgString256();
    virtual ~MsgString256();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x100];
};

#endif
