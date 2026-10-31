#ifndef TALK_MSGSTRING3_H
#define TALK_MSGSTRING3_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString3 : public MsgString {
public:
    MsgString3();
    virtual ~MsgString3();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[3];
};

#endif
