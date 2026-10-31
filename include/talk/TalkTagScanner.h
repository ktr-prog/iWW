#ifndef TALK_TALKTAGSCANNER_H
#define TALK_TALKTAGSCANNER_H

#include "types.h"
#include "talk/MsgWalker.h"
#include "talk/MsgTag.h"

class TalkWindowState;

class TalkTagScanner : public MsgWalker {
public:
    TalkTagScanner(TalkWindowState *owner);
    virtual ~TalkTagScanner();
    virtual void onTag(u8 *p);

    void reportTag();
    void resetScan();
    void scan(u8 *p);

    /* 0x24 */ TalkWindowState *window;
    /* 0x28 */ u32 unk_28;
    /* 0x2c */ MsgTag tag;
};

#endif
