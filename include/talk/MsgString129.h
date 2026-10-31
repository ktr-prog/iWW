#ifndef TALK_MSGSTRING129_H
#define TALK_MSGSTRING129_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString129 : public MsgString {
public:
    MsgString129();
    virtual ~MsgString129();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x81];
};

#endif
