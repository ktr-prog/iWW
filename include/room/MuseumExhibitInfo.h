#ifndef ROOM_MUSEUMEXHIBITINFO_H
#define ROOM_MUSEUMEXHIBITINFO_H

#include "types.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "game/TouchPickSphere.h"

class MuseumExhibitInfo : public Character, public TalkMsgRequest {
public:
    MuseumExhibitInfo();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~MuseumExhibitInfo();
    virtual BOOL acceptsInteraction(void *a);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);

    void mainAct03();
    BOOL setupAct03();
    void mainAct02();
    BOOL setupAct02();
    void mainAct01();
    BOOL setupAct01();
    void mainAct00();
    BOOL setupAct00();
    void execAct();
    BOOL changeAct(s32 idx);
    BOOL isAutoTalkKind();
    void advanceToNextDonated();
    u32 countDonatedFromCursor();
    BOOL isAllDonated();
    BOOL isAnyDonated();
    BOOL buildItemList();
    BOOL unregisterSelf();
    BOOL registerSelf();

    /* 0x130 */ s32 act;
    /* 0x134 */ TouchPickSphere touchSphere;
    /* 0x150 */ u8 index;
    /* 0x151 */ u8 cursor;
    /* 0x152 */ u8 pad_152[2];
    /* 0x154 */ s32 facingArc;
    /* 0x158 */ u32 kind;
    /* 0x15c */ s16 infoMsgIndex;
    /* 0x15e */ u8 pad_15e[2];
    /* 0x160 */ u16 *items;
    /* 0x164 */ u32 itemCount;
    /* 0x168 */ u8 talkCount;
};

#endif
