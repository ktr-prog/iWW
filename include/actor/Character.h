#ifndef ACTOR_CHARACTER_H
#define ACTOR_CHARACTER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/Actor.h"
#include "actor/CharacterListNode.h"

class TalkMsgRequest;

class Character : public Actor {
public:
    Character();
    virtual ~Character();
    virtual BOOL preCreate();
    virtual void postCreate(s32 status);
    virtual BOOL preDelete();
    virtual BOOL preExecute();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual VecFx32 *getInteractionPos();
    virtual BOOL acceptsInteractionOutOfRange(void *other);
    virtual BOOL acceptsSelfRequestedInteraction(void *a);
    virtual BOOL getHeldItemPos(VecFx32 *out);

    void clearCharFlags(u32 mask);
    void setCharFlags(u32 mask);
    BOOL testCharFlags(u32 mask);
    BOOL isAreaSynced();
    void setAreaSynced();
    s32 getTalkStartMode();
    void clearTalkStartMode();
    void setTalkStartMode1();
    void setTalkStartMode0();
    void setInteractionRange(s32 v);
    void detachTalkRequest(TalkMsgRequest *req);
    void attachTalkRequest(TalkMsgRequest *req);
    BOOL checkInteraction(Character *other);
    BOOL isInInteractionRange(Character *other);
    BOOL isInFacingArcOf(Character *other, s16 lo, s16 hi);
    void setCharId(u32 a);
    u32 getCharId();

    /* 0xd4 */ CharacterListNode charNode;
    /* 0xe4 */ s32 interactionRangeSq;
    /* 0xe8 */ u16 charFlags;
    MWCC_LAYOUT
};

#endif
