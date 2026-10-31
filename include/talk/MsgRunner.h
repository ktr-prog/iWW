#ifndef TALK_MSGRUNNER_H
#define TALK_MSGRUNNER_H

#include "types.h"

class MsgWalker;

class MsgRunner {
public:
    MsgRunner(MsgWalker *obj);
    void start(u8 *p);
    BOOL advance();
    void reset();

    /* 0x00 */ MsgWalker *walker;
    /* 0x04 */ u8 *text;
    /* 0x08 */ u8 *stopPos;
};

#endif
