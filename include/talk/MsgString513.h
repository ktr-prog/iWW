#ifndef TALK_MSGSTRING513_H
#define TALK_MSGSTRING513_H

#include "types.h"
#include "talk/MsgString.h"

class MsgString513 : public MsgString {
public:
    MsgString513();
    virtual ~MsgString513();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x201];
};

#endif
