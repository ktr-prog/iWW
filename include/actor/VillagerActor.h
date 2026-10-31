#ifndef ACTOR_VILLAGERACTOR_H
#define ACTOR_VILLAGERACTOR_H

#include "types.h"
#include "actor/NpcActor.h"
#include "npc/VillagerClothModel.h"
#include "talk/VillagerTalk.h"
#include "npc/NpcResHandle.h"
#include "npc/VillagerMood.h"

union ClockDateTimeWords;
struct PlanErrand;
struct VillagerData;


class VillagerActor : public NpcActor {
public:
    VillagerActor();
    virtual ~VillagerActor();
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL preDelete();
    virtual void *getVillagerData();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual void getName(MsgString *buf);
    virtual u32 getGender();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();
    virtual u16 getSpecies();
    virtual void setShirt(u16 *p, BOOL flag);
    virtual void addMood(u32 a, s32 b);
    /* 0xa8 */ virtual BOOL isPickable();
    /* 0xac */ virtual BOOL vfunc_ac();
    /* 0xb0 */ virtual BOOL consumeFleaRemoved();
    /* 0xb4 */ virtual s32 canAcceptPartnerInvite();
    /* 0xb8 */ virtual s32 acceptPartnerInvite(VillagerActor *partner);
    /* 0xbc */ virtual s32 endPartnerTalk();

    BOOL isFlag834();
    void clearFlag834();
    void setFlag834();
    BOOL loadAnimSet();
    s32 getSpeciesOrNone();
    void attachVillagerData();
    void updateCatchPlans(u8 *a, void *b, u32 c);
    void updateFishCatchPlan(PlanErrand *s1, u8 *tbl, void *p2, u8 p3, ClockDateTimeWords *arr);

    /* 0x640 */ u8 eventKind;
    /* 0x644 */ VillagerActor *talkPartner;
    /* 0x648 */ u8 invitedByPartner;
    /* 0x64c */ VillagerClothModel clothModel;
    /* 0x680 */ VillagerTalk villagerTalk;
    /* 0x820 */ u8 habitTopicKind;
    /* 0x821 */ u8 pad_821[3];
    /* 0x824 */ VillagerAnimHeapHandle animHeapHandle;
    /* 0x82c */ VillagerData *villagerData;
    /* 0x830 */ void *villagerState;
    /* 0x834 */ u8 unk_834;
    /* 0x838 */ VillagerMood mood;
};

#endif
