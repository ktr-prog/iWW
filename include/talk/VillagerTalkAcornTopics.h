#ifndef TALK_VILLAGERTALKACORNTOPICS_H
#define TALK_VILLAGERTALKACORNTOPICS_H

#include "types.h"
#include "talk/VillagerTalkKaraokeTopics.h"

struct TalkTopicMsg;

class VillagerTalkAcornTopics : public VillagerTalkKaraokeTopics {
public:
    void selectEvSnowfesTalk(void *arg);
    void selectEvAcornMsg15(TalkTopicMsg *out);
    void giveAcornReward();
    void selectEvAcornMsg19(TalkTopicMsg *out);
    void rollAcornReward();
    void selectEvAcornMsg17(TalkTopicMsg *out);
    void continueAcornReceived();
    void onAcornPicked();
    void openAcornPicker();
    void openEvAcornGiveChoice();
    void selectEvAcornMsg13(TalkTopicMsg *out);
    void openSmallTalkChoiceAcorn();
    void selectEtcConnectAcorn(TalkTopicMsg *out);
    void continueEvAcornMsg7();
    void selectEvAcornMsg7(TalkTopicMsg *out);
    void selectEvAcornMsg10(TalkTopicMsg *out);
    void selectEvAcorn(TalkTopicMsg *out);
    void selectEvAcornTalk(void *arg);
    void openSmallTalkChoiceGardeniing();
};

#endif
