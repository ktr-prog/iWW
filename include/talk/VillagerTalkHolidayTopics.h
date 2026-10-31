#ifndef TALK_VILLAGERTALKHOLIDAYTOPICS_H
#define TALK_VILLAGERTALKHOLIDAYTOPICS_H

#include "types.h"
#include "talk/VillagerTalkHobbyTopics.h"

struct TalkTopicMsg;

class VillagerTalkHolidayTopics : public VillagerTalkHobbyTopics {
public:
    void updateEvBirthMove();
    void startEvBirthMove();
    void continueEvBirthMsg0();
    void selectEvBirthMsg0(TalkTopicMsg *out);
    void selectTsuFriendOnce(TalkTopicMsg *out);
    void selectTsuSpotOnce(TalkTopicMsg *out);
    void selectTsuAlwaysOnce(TalkTopicMsg *out);
    void openSmallTalkChoiceCountdown();
    void selectEtcConnectCountdown(TalkTopicMsg *out);
    void continueEvCountdownMsg18();
    void selectEvCountdownMsg18(TalkTopicMsg *out);
    void selectEvCountdownMsg16(TalkTopicMsg *out);
    void selectEvCountdownMsg14(TalkTopicMsg *out);
    void selectEvCountdownB(TalkTopicMsg *out);
    void selectEvCountdown(TalkTopicMsg *out);
    void openEvCountdownChoice();
    void selectEtcConnectCountdownB(TalkTopicMsg *out);
    void continueGreetingCountdown();
    void selectGreetingCountdown(TalkTopicMsg *out);
    void selectEvCountdownTalk(TalkTopicMsg *out);
    void openSmallTalkChoiceSnowfes();
    void selectEtcConnectSnowfes(TalkTopicMsg *out);
    void continueEvSnowfesC();
    void selectEvSnowfesC(TalkTopicMsg *out);
    void selectEvSnowfesB(TalkTopicMsg *out);
    void selectEvSnowfes(TalkTopicMsg *out);
};

#endif
