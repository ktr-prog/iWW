#ifndef TALK_VILLAGERTALKKARAOKETOPICS_H
#define TALK_VILLAGERTALKKARAOKETOPICS_H

#include "types.h"
#include "talk/VillagerTalkRequestStartTopics.h"

struct TalkTopicMsg;

class VillagerTalkKaraokeTopics : public VillagerTalkRequestStartTopics {
public:
    void openEvAdmireChoice();
    void selectEvAdmireMsg7(TalkTopicMsg *out);
    void selectEvAdmireMsg2(TalkTopicMsg *out);
    void onEvAdmireWordEntered();
    void saveEnteredCompliment();
    void openEvAdmireWordEntry();
    void selectEvAdmire(TalkTopicMsg *out);
    void selectEvAdmireTalk(TalkTopicMsg *out);
    void endEvFirework();
    void selectEvFirework(TalkTopicMsg *out);
    void openSmallTalkChoice();
    void selectEvKaraokeMsg17(TalkTopicMsg *out);
    void selectEvKaraokeMsg14(TalkTopicMsg *out);
    void selectEvKaraokeMsg12(TalkTopicMsg *out);
    void selectEvKaraokeMsg10(TalkTopicMsg *out);
    void endEvKaraokeMsg8();
    void selectEvKaraokeMsg8(TalkTopicMsg *out);
    void openEvKaraokeMsg6Choice();
    void selectEvKaraokeMsg6(TalkTopicMsg *out);
    void continueEvKaraokeAction();
    void waitEvKaraokeAction();
    void startEvKaraokeAction();
    void continueEvKaraokeMsg20();
    void selectEvKaraokeMsg20(TalkTopicMsg *out);
};

#endif
