#ifndef TALK_MSGSTRING25B_H
#define TALK_MSGSTRING25B_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString25B : public MsgString {
public:
    MsgString25B();
    virtual ~MsgString25B();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x19];
};

#endif
