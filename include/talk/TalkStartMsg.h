#ifndef TALK_TALKSTARTMSG_H
#define TALK_TALKSTARTMSG_H

#include "types.h"

struct TalkStartMsg {
    /* 0x0 */ const char *msgKey;
    /* 0x4 */ u8 msgIndex;
};

#endif
