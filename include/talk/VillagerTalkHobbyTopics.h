#ifndef TALK_VILLAGERTALKHOBBYTOPICS_H
#define TALK_VILLAGERTALKHOBBYTOPICS_H

#include "types.h"
#include "talk/VillagerTalkAcornTopics.h"

struct TalkTopicMsg;

class VillagerTalkHobbyTopics : public VillagerTalkAcornTopics {
public:
    void selectEtcConnectGardeniing(TalkTopicMsg *out);
    void continueEvGardeniingMsg10();
    void selectEvGardeniingMsg10(TalkTopicMsg *out);
    void selectEvGardeniingMsg13(TalkTopicMsg *out);
    void selectEvGardeniing(TalkTopicMsg *out);
    void selectEvGardeniingTalk(void *arg);
    void endEvInsect();
    void selectEvInsect(TalkTopicMsg *out);
    void endEvFishing();
    void selectEvFishing(TalkTopicMsg *out);
    void openSmallTalkChoiceAdmire();
    void selectEtcConnectAdmire(TalkTopicMsg *out);
    void continueEvAdmireMsg4();
    void selectEvAdmireMsg4(TalkTopicMsg *out);
    void selectEvAdmireMsg10(TalkTopicMsg *out);
    void selectEvAdmireMsg14(TalkTopicMsg *out);
    void onEvAdmireWordEnteredB();
    void openEvAdmireWordEntryB();
    void selectEvAdmireMsg12(TalkTopicMsg *out);
};

#endif
