#ifndef TALK_TALKREQUESTENTRY_H
#define TALK_TALKREQUESTENTRY_H

#include "types.h"

struct TalkRequestEntry {
    TalkRequestEntry();

    /* 0x00 */ s32 prev;
    /* 0x04 */ TalkRequestEntry *next;
    /* 0x08 */ u8 priority;
    /* 0x09 */ u8 unk_09[3];
    /* 0x0c */ s32 requesterId;
    /* 0x10 */ s32 targetId;
    /* 0x14 */ u8 phase;
    /* 0x15 */ u8 kind;
    /* 0x16 */ u8 state;
    /* 0x17 */ u8 result;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1a */ u8 pad_1a[2];
};

#endif
