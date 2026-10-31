#ifndef ROOM_ROOMTELEPHONE_H
#define ROOM_ROOMTELEPHONE_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "room/RoomObjActor.h"
#include "talk/TalkMsgRequest.h"
#include "game/BoxCollider.h"
#include "game/TouchPickTriangle.h"
#include "game/TouchPickSphere.h"

struct PhoneChoiceSet;

class RoomTelephone : public RoomObjActor, public TalkMsgRequest {
public:
    RoomTelephone();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~RoomTelephone();
    virtual BOOL acceptsInteraction(void *a);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual VecFx32 *getInteractionPos();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);

    void openTalk(const char *name, u32 flag);
    void execAct0E();
    void enterAct0E();
    void execAct0D();
    void enterAct0D();
    void execAct0C();
    void enterAct0C();
    void execAct0B();
    void enterAct0B();
    void execAct0A();
    void enterAct0A();
    void execAct09();
    void enterAct09(const char *name, u32 flag);
    void execAct08();
    void enterAct08();
    void execAct07();
    void enterAct07();
    void execAct06();
    void enterAct06();
    void execAct05();
    void enterAct05();
    void execAct04();
    void enterAct04();
    void execAct03();
    void enterAct03();
    void execAct02();
    void enterAct02();
    void execAct01();
    void enterAct01();
    void execAct00();
    void enterAct00();
    void changeAct(s32 state);
    void openChoices(PhoneChoiceSet *p, s32 v);

    /* 0x2d4 */ BoxCollider collider;
    /* 0x370 */ TouchPickBox touchBox;
    /* 0x618 */ TouchPickSphere touchSphere;
    /* 0x634 */ s32 act;
    /* 0x638 */ u8 isTalking;
    /* 0x639 */ u8 pad_639[3];
    /* 0x63c */ u32 prevTalkVoice;
};

#endif
