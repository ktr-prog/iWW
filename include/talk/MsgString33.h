#ifndef TALK_MSGSTRING33_H
#define TALK_MSGSTRING33_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString33 : public MsgString {
public:
    MsgString33();
    virtual ~MsgString33();
    virtual u32 capacity();
    virtual u8 *data();
    void initEmpty();

    /* 0x12 */ u8 text[0x21];
};

#endif
