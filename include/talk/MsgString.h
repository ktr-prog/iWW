#ifndef TALK_MSGSTRING_H
#define TALK_MSGSTRING_H

#include "types.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"

class EncodedString;

class MsgString : public MsgStringBase {
public:
    MsgString();
    virtual ~MsgString();
    virtual u32 capacity() = 0;
    virtual u8 *data() = 0;
    BOOL appendRange(u8 *start, u8 *end);
    BOOL assignRange(u8 *start, u8 *end);
    BOOL equals(MsgString *other);
    u8 appendString(MsgString *other);
    u8 append(u8 *str);
    u8 setLine(u8 *str);
    BOOL fromEncoded(EncodedString *src, BOOL a, BOOL b);
    u8 copy(MsgString *other);
    u8 set(u8 *str);
    void clear();

    /* 0x04 */ u32 length;
    /* 0x08 */ MWCC_TAIL MsgStringAttr attr;
};

#endif
