#ifndef TALK_TALKTOPICMSG_H
#define TALK_TALKTOPICMSG_H

#include "types.h"


struct TalkTopicMsg {
    /* 0x0 */ const char *fileName;
    /* 0x4 */ u8 msgIndex;
};

#endif
