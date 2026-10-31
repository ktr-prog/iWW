#ifndef NPC_BIRTHDAYHOSTVILLAGER_H
#define NPC_BIRTHDAYHOSTVILLAGER_H

#include "types.h"
#include "actor/VillagerActor.h"
#include "talk/VillagerTalk.h"
#include "talk/TalkStartMsg.h"

class BirthdayHostVillager;
struct VillagerMemory;

class BirthdayHostVillagerTalk : public VillagerTalk {
public:
    BirthdayHostVillagerTalk() {}
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void attachOwner(BirthdayHostVillager *owner);
    s32 getFriendship();
    void addFriendship(s32 v);
    BOOL isLikedGift(u16 *p);
    VillagerMemory *getPlayerMemory();
    void setReceivedGift();
    u32 hasReceivedGift();
    void setTalked();
    BOOL isNotTalkedYet();
    void setPartyGreeted();
    BOOL isPartyNotGreeted();

    /* 0x1a0 */ BirthdayHostVillager *villager;
};

typedef BOOL (BirthdayHostVillager::*Unk_ov004_0224c034_Fn)();

class BirthdayHostVillager : public VillagerActor {
public:
    BirthdayHostVillager() : returnGift(0xfff1) {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL preDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL acceptsSelfRequestedInteraction(void *a);
    virtual BOOL updateAct();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();

    BOOL drawModel();
    void recordPlayerTalk();
    BOOL changeAct(s32 idx);
    void execAct();
    BOOL setupAct00();

    void mainAct0D();
    BOOL setupAct0D();
    void mainAct0C();
    BOOL setupAct0C();
    void mainAct0B();
    BOOL setupAct0B();
    void mainAct0A();
    BOOL setupAct0A();
    void mainAct09();
    BOOL setupAct09();
    void mainAct08();
    BOOL setupAct08();
    void mainAct07();
    BOOL setupAct07();
    void mainAct06();
    BOOL setupAct06();
    void mainAct05();
    BOOL setupAct05();
    void mainAct04();
    BOOL setupAct04();
    void mainAct03();
    BOOL setupAct03();
    void mainAct02();
    BOOL setupAct02();
    void mainAct01();
    BOOL setupAct01();
    void mainAct00();

    /* 0x894 */ s32 act;
    /* 0x898 */ u8 talkMelodyPlayed;
    /* 0x899 */ u8 pad_899[3];
    /* 0x89c */ BirthdayHostVillagerTalk talk;
    /* 0xa40 */ Unk_ov004_0224c034_Fn drawFn;
    /* 0xa48 */ u16 returnGift;
    /* 0xa4a */ u8 approachTimer;
    /* 0xa4b */ u8 emotionTimer;
    /* 0xa4c */ s16 walkAngle;
    /* 0xa4e */ u16 walkTimer;
    /* 0xa50 */ VecFx32 waypoint;
    /* 0xa5c */ VecFx32 walkTarget;
};

#endif
