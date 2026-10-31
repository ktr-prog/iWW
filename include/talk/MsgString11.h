#ifndef TALK_MSGSTRING11_H
#define TALK_MSGSTRING11_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString11 : public MsgString {
public:
    MsgString11();
    virtual ~MsgString11();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0xb];
};

#endif
