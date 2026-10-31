#ifndef TALK_VILLAGERTALKREQUESTREPLYTOPICS_H
#define TALK_VILLAGERTALKREQUESTREPLYTOPICS_H

#include "types.h"
#include "talk/VillagerTalkHolidayTopics.h"

struct TalkTopicMsg;

class VillagerTalkRequestReplyTopics : public VillagerTalkHolidayTopics {
public:
    void selectDeliveryLate(TalkTopicMsg *out);
    s32 getRequestKind();
    void acceptDeliveryRequest();
    void setDeliveryDeadline();
    void selectDeliveryAccepted(TalkTopicMsg *out);
    void continueQFull();
    void selectQFull(TalkTopicMsg *out);
    void cancelRequest();
    void selectQNoB(TalkTopicMsg *out);
    void openDeliveryAcceptChoice();
    void selectQTime(TalkTopicMsg *out);
    void gotoDeliveryTime();
    void pickDeliveryRecipient();
    void selectDeliveryRequest(TalkTopicMsg *out);
    void runChosenTopic(TalkTopicMsg *, u32 idx);
    void openConnectMenu();
    BOOL tryAddSickVillagerChoice(void *arg);
    BOOL tryOfferNewRequest(void *a, void *b);
};

#endif
