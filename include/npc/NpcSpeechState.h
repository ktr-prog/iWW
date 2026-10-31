#ifndef NPC_NPCSPEECHSTATE_H
#define NPC_NPCSPEECHSTATE_H

#include "types.h"

struct NpcSpeechState {
    /* 0x0 */ u8 speaking;
    /* 0x4 */ s32 mouthType;

    NpcSpeechState();
    ~NpcSpeechState();
    s32 getMouthType();
    void setMouthType(s32 v);
    BOOL isSpeaking();
    void stopSpeaking();
    void startSpeaking();
    void reset();
};

#endif
