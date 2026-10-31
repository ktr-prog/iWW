#ifndef TALK_CONSTELLATIONMSGSTRING17_H
#define TALK_CONSTELLATIONMSGSTRING17_H

#include "types.h"
#include "talk/MsgString.h"

class ConstellationMsgString17 : public MsgString {
public:
    ConstellationMsgString17();
    virtual ~ConstellationMsgString17();
    virtual u32 capacity();
    virtual u8 *data();
    /* 0x12 */ u8 text[0x11];
};

#endif
