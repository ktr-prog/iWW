#ifndef ROOM_FTRPHONE_H
#define ROOM_FTRPHONE_H

#include "types.h"
#include "room/FtrActor.h"

class FtrPhone : public FtrActor {
public:
    FtrPhone();
    virtual BOOL onDelete();
    virtual ~FtrPhone();
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL changeAct(u32 a, u8 b);
    virtual u8 getActSwitchState(u32 a);
    virtual BOOL initModel();
    virtual BOOL updateActive();

    void execTalkAct04();
    BOOL enterTalkAct04();
    void execTalkAct03();
    BOOL enterTalkAct03();
    void execTalkAct02();
    BOOL enterTalkAct02();
    void execTalkAct01();
    BOOL enterTalkAct01();
    void execTalkAct00();
    BOOL enterTalkAct00();
    void execTalkAct();
    BOOL setTalkAct(s32 idx);
    void execFtrAct03();
    BOOL enterFtrAct03();
    void execFtrAct02();
    BOOL enterFtrAct02();
    void execFtrAct01();
    BOOL enterFtrAct01();
    void execFtrAct00();
    BOOL enterFtrAct00();
    void execFtrAct();

    /* 0x840 */ s32 contactPoint;
    /* 0x844 */ s32 contactPointY;
    /* 0x848 */ s32 contactPointZ;
    /* 0x84c */ u16 pushAngle;
    /* 0x84e */ u16 talkDelay;
    /* 0x850 */ u8 ftrAct;
    /* 0x851 */ u8 pad_851[3];
    /* 0x854 */ s32 talkAct;
};

#endif
