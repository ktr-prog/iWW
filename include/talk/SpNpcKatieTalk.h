#ifndef TALK_SPNPCKATIETALK_H
#define TALK_SPNPCKATIETALK_H

#include "types.h"
#include "talk/SpNpcTalkRequest.h"
#include "talk/TalkStartMsg.h"

class SpNpcKatie;

class SpNpcKatieTalk : public SpNpcTalkRequest {
public:
    SpNpcKatieTalk();
    virtual ~SpNpcKatieTalk();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void onEventTag(u32 id);
    virtual void start(TalkStartMsg *out);

    s32 getTopic();
    void setTopic(s32 v);
    void attachOwner(SpNpcKatie *owner);

    /* 0xac */ SpNpcKatie *katie;
    /* 0xb0 */ s32 topic;
};

#endif
