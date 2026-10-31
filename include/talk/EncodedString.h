#ifndef TALK_ENCODEDSTRING_H
#define TALK_ENCODEDSTRING_H

#include "types.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgStringAttr.h"

class MsgString;

class EncodedString : public EncodedStringBase {
public:
    EncodedString();
    virtual ~EncodedString();
    virtual u32 capacity() = 0;
    virtual u8 *data() = 0;
    BOOL fromMsgString(MsgString *src);

    /* 0x04 */ MWCC_TAIL MsgStringAttr attr;
};

#endif
