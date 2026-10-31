#ifndef TALK_TALKREQUESTLIST_H
#define TALK_TALKREQUESTLIST_H

#include "types.h"


struct TalkRequestEntry;

struct TalkRequestList {
    /* 0x00 */ TalkRequestEntry *head;
    /* 0x04 */ TalkRequestEntry *tail;
};

#endif
