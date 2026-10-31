#ifndef TALK_MSGSTRINGATTR_H
#define TALK_MSGSTRINGATTR_H

#include "types.h"

class MsgStringAttr {
public:
    MsgStringAttr();
    virtual ~MsgStringAttr();
    void reset();
    void copyFrom(MsgStringAttr *other);

    /* 0x04 */ s32 form;
    /* 0x08 */ u8 attrA;
    /* 0x09 */ u8 attrB;
};

#endif
