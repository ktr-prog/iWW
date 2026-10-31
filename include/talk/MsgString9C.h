#ifndef TALK_MSGSTRING9C_H
#define TALK_MSGSTRING9C_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString9C : public MsgString {
public:
    MsgString9C();
    virtual ~MsgString9C();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[9];
};

#endif
