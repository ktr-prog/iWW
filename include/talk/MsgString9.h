#ifndef TALK_MSGSTRING9_H
#define TALK_MSGSTRING9_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString9 : public MsgString {
public:
    MsgString9();
    virtual ~MsgString9();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[9];
};

#endif
