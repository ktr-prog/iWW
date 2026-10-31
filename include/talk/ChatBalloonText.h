#ifndef TALK_CHATBALLOONTEXT_H
#define TALK_CHATBALLOONTEXT_H

#include "types.h"
#include "talk/MsgString.h"

class ChatBalloonText : public MsgString {
public:
    ChatBalloonText();
    virtual ~ChatBalloonText();
    virtual u32 capacity();
    virtual u8 *data();
    /* 0x12 */ u8 text[0x20];
};

#endif
