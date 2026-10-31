#ifndef TALK_REDDPASSWORDSTRING_H
#define TALK_REDDPASSWORDSTRING_H

#include "types.h"
#include "talk/MsgString.h"

class ReddPasswordString : public MsgString {
public:
    ReddPasswordString();
    virtual ~ReddPasswordString();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x21];
};

#endif
