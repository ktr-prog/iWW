#ifndef PLAYER_PLAYEROPTIONS_H
#define PLAYER_PLAYEROPTIONS_H

#include "types.h"

class PlayerOptions {
public:
    PlayerOptions();
    ~PlayerOptions();
    void markTalkVoiceChanged();
    void markStereoChanged();
    void markHiraganaChanged();
    BOOL isTalkVoiceChanged();
    BOOL isStereoChanged();
    BOOL isHiraganaChanged();
    void reset();
    void setTalkVoice(u32 v);
    u32 getTalkVoice();
    void clearStereo();
    void setStereo();
    BOOL isStereo();
    void clearHiragana();
    void setHiragana();
    BOOL isHiragana();
    void resetValues();

    /* 0x00 */ u8 options;
    /* 0x01 */ u8 changedMask;
};

#endif
