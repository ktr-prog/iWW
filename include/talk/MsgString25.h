#ifndef TALK_MSGSTRING25_H
#define TALK_MSGSTRING25_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString25 : public MsgString {
public:
    MsgString25();
    virtual ~MsgString25();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x19];
};

#endif
