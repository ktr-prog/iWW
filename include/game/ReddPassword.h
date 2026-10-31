#ifndef GAME_REDDPASSWORD_H
#define GAME_REDDPASSWORD_H

#include "types.h"

struct ReddPassword {
    /* 0x00 */ u32 bits;
    /* 0x04 */ volatile s8 slot;
    /* 0x05 */ u8 flags;

    ReddPassword();
    ~ReddPassword();
    inline s8 getSlot() { return slot; }
    void clear();
    void markUsed(u32 i);
    BOOL isUsed(u32 i);
    u32 countUnused();
    BOOL setVisitorKnows();
    void clearResidentKnows(u32 i);
    void setResidentKnows(u32 i);
    BOOL residentKnows(u32 i);
    void clearAllResidentKnows();
    void markLetterSent();
    BOOL needsLetter();
    u32 getAnswerText(void *w);
    u8 getAnswerIndex();
    u32 getPromptText(void *w);
    BOOL dropPassword();
    BOOL pickPassword();
};

#endif
