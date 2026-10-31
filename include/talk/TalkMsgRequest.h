#ifndef TALK_TALKMSGREQUEST_H
#define TALK_TALKMSGREQUEST_H

#include "types.h"
#include "talk/MsgRequest.h"
#include "talk/MsgString9.h"

class TalkWindowState;

class TalkMsgRequest : public MsgRequest {
public:
    TalkMsgRequest();
    virtual ~TalkMsgRequest();
    virtual void resetMsg();
    virtual const char *getMsgDir();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void onSignalTag(s32 id);
    virtual void onActionTag0();
    virtual void onActionTag1(u32 arg);
    virtual void onActionTag2(u32 arg);
    virtual void onActionTag3(u32 arg);
    virtual void onActionTag4(u32 arg);
    virtual void onConditionTag(u32 condition, u32 branchCount);
    virtual void onEventTag(u32 id);
    virtual void onTag09_0();
    virtual void onTag09_1();
    virtual void onTag09_2();
    virtual void onTag09_3();
    virtual void onTag09_4();
    virtual void onTag09_5();
    virtual void onTag09_6();
    virtual void onTag09_7();
    virtual void onTag09_8();
    virtual void onTag09_9();
    virtual void onScannedTag(u32 tag);
    virtual void *getSpeakerData();
    virtual s32 getVoiceType();
    virtual void onWindowClose();
    virtual void onTalkEnd();

    void detachWindow();
    void attachWindow(TalkWindowState *w);
    u32 getNameKind();
    u32 isNoSpeakerName();
    MsgString9 *getSpeakerName();
    void changeSpeakerName(MsgString *p, u32 v);
    void setNoSpeakerName(u32 v);
    void setSpeakerNameStr(MsgString *p, u32 v);
    void setSpeakerName(u8 *p, u32 v);

    /* 0x20 */ MsgString9 speakerName;
    /* 0x3c */ TalkWindowState *window;
    /* 0x40 */ u8 noSpeakerName;
};

#endif
