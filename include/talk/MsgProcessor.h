#ifndef TALK_MSGPROCESSOR_H
#define TALK_MSGPROCESSOR_H

#include "types.h"
#include "talk/MsgParser.h"

class MsgTextLabel;

class MsgProcessor : public MsgParser {
public:
    MsgProcessor(u8 flag);
    virtual ~MsgProcessor();

    void clearStopAtNewline();
    void setStopAtNewline();
    void clearLabel();
    void setLabel(MsgTextLabel *p);
    u32 run(u8 *p);

    /* 0x24 */ MsgTextLabel *label;
    /* 0x28 */ u8 stopAtNewline;
};

#endif
