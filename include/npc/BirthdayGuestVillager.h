#ifndef NPC_BIRTHDAYGUESTVILLAGER_H
#define NPC_BIRTHDAYGUESTVILLAGER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/VillagerActor.h"
#include "talk/VillagerTalk.h"
#include "talk/TalkStartMsg.h"

struct VillagerMemory;
class BirthdayGuestVillager;

class BirthdayGuestVillagerTalk : public VillagerTalk {
public:
    BirthdayGuestVillagerTalk() {}
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void attachOwner(VillagerActor *owner);
    void setTalked();
    BOOL isNotTalkedYet();
    VillagerMemory *getPlayerMemory();

    /* 0x1a0 */ BirthdayGuestVillager *villager;
};

typedef void (BirthdayGuestVillager::*Unk_ov004_0224c228_VFn)();
typedef BOOL (BirthdayGuestVillager::*Unk_ov004_0224c228_BFn)();

class BirthdayGuestVillager : public VillagerActor {
public:
    BirthdayGuestVillager() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL preDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();

    void mainAct06();
    void mainAct05();
    void mainAct04();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void mainAct00();
    void execAct();
    BOOL setupAct06();
    BOOL setupAct02();
    BOOL setupAct05();
    BOOL setupAct03();
    BOOL setupAct04();
    BOOL setupAct01();
    BOOL setupAct00();
    BOOL changeAct(s32 idx);
    void recordPlayerTalk();
    void blockFurnitureCells();
    BOOL drawModel();

    /* 0x894 */ s32 act;
    /* 0x898 */ BirthdayGuestVillagerTalk talk;
    /* 0xa3c */ Unk_ov004_0224c228_BFn drawFn;
    /* 0xa44 */ u8 emotionTimer;
    /* 0xa45 */ u8 pad_a45;
    /* 0xa46 */ u16 chatCooldown;
    /* 0xa48 */ s16 walkAngle;
    /* 0xa4a */ u16 walkTimer;
    /* 0xa4c */ VecFx32 waypoint;
    /* 0xa58 */ VecFx32 walkTarget;
};

#endif
