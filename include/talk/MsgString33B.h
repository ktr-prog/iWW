#ifndef TALK_MSGSTRING33B_H
#define TALK_MSGSTRING33B_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString33B : public MsgString {
public:
    MsgString33B();
    virtual ~MsgString33B();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x21];
};

#endif
