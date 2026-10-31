#ifndef TALK_VILLAGERTALKREQUESTSTARTTOPICS_H
#define TALK_VILLAGERTALKREQUESTSTARTTOPICS_H

#include "types.h"
#include "talk/VillagerTalkRequestItemTopics.h"

struct TalkTopicMsg;

class VillagerTalkRequestStartTopics : public VillagerTalkRequestItemTopics {
public:
    void gotoQ05Talk();
    void selectQCon(TalkTopicMsg *out);
    void registerRequestDeclined();
    void selectQNo(TalkTopicMsg *out);
    void registerRequestAccepted();
    void selectQStart(TalkTopicMsg *out);
    void registerRequestDeferred();
    void openRequestChoice();
    void prepareRequestItem();
};

#endif
