#ifndef TOWN_REDDTENT_H
#define TOWN_REDDTENT_H

#include "types.h"
#include "town/BuildingActor.h"

class ReddTent : public BuildingActor {
public:
    ReddTent();
    virtual ~ReddTent();
    virtual BOOL onExecute();
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL initBuilding();
    virtual void onMessageEnd(u32 attr);
    virtual BOOL isOpen();
    virtual void onMessageStart(u32 attr);
    virtual void onChoice(u32 attr);
    virtual s32 getVoiceType();

    void execTentIdle();
    void execTentCheck();
    void execTentTalkOpen();
    void execTentTalk();
    void execTentMenuWait();
    void execTentMenu();
    void execTentGoIn();
    void execTentEntry07();
    void execTentWalkIn();
    void execTentWarp();
    BOOL enterTentIdle();
    BOOL enterTentCheck();
    BOOL enterTentTalkOpen();
    BOOL enterTentTalk();
    BOOL enterTentMenuWait();
    BOOL enterTentMenu();
    BOOL enterTentGoIn();
    BOOL enterTentEntry07();
    BOOL enterTentWalkIn();
    BOOL enterTentWarp();
    void updateTentState();
    BOOL setTentState(s32 i);

    /* 0x2b0 */ s32 tentState;
    /* 0x2b4 */ u16 warpFrames;
    /* 0x2b6 */ u8 doorEnterRequested;
    /* 0x2b7 */ u8 createHour;
};

#endif
