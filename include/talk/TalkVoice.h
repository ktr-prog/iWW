#ifndef TALK_TALKVOICE_H
#define TALK_TALKVOICE_H

#include "types.h"

class TalkWindowState;

class TalkVoice {
public:
    TalkVoice(TalkWindowState *o);
    virtual ~TalkVoice();
    void shiftHistory();
    void updateVoiceType();
    u8 getSpeakerMoodIndex();
    u32 getVoiceStyle();
    void end();
    void begin();
    void setMsgMode(s32 v);
    void update();
    void pushChar(u32 c);
    void reset(s32 flag);
    void refreshVoiceType();
    void setVoiceType(s32 r);
    void clearMsgModeOverride();
    void setMsgModeOverride(s32 v);
    void clearVoiceOverride();
    void setVoiceOverride(s32 v);

    /* 0x04 */ TalkWindowState *window;
    /* 0x08 */ u16 charKeys[2];
    /* 0x0c */ u16 carryCharKey;
    /* 0x10 */ s32 numCharKeys, msgModeOverride, msgMode;
    /* 0x1c */ u8 instantByMsg, instantByTag, inWait;
    /* 0x20 */ s32 voiceOverride, voiceType, textColor;
};

#endif
