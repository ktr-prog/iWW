#ifndef TALK_MSGSTRING193_H
#define TALK_MSGSTRING193_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString193 : public MsgString {
public:
    MsgString193();
    virtual ~MsgString193();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0xc1];
};

#endif
