#ifndef TALK_MSGWALKER_H
#define TALK_MSGWALKER_H

#include "types.h"
#include "talk/MsgParser.h"

class MsgWalker : public MsgParser {
public:
    MsgWalker() {}
    virtual ~MsgWalker() {}
    virtual BOOL canContinue();
    u8 *run(u8 *end);
};

#endif
