#include "uptr.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/CharacterListNode.h"
#include "talk/TalkRequestEntry.h"
#include "game/CharacterList.h"
#include "net/CommManager.h"
#include "sys/ProcBase.h"
#include "talk/TalkRequestQueue.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_0203e438.h"
#include "proto/main/unk_0203e7d0.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b0e60.h"

extern "C" const s16 data_020c905c;


class Character;


extern CharacterList gCharacterList;


extern "C" {
void PrioList_Init(void *);
void List_Remove(void *, void *);
s32 func_01ffcb0c(s32 v1, s32 v2);
void Talk_DetachRequest(TalkMsgRequest *req);
void Talk_AttachRequestToWindow0(TalkMsgRequest *req);
long long Vec_MagSqXZ(VecFx32 *);
void *PrioList_FindById(void *, u32);
void PrioList_PushBack(void *, void *);
Character *Character_FindByCharId(u32 id);
}


CharacterList gCharacterList;

Character::Character() {
    charNode.prev = 0;
    charNode.next = 0;
    charNode.charId = 0;
}

Character::~Character() {}

extern "C" void Character_ResetList(void) {
    PrioList_Init(&gCharacterList);
}

BOOL Character::preCreate() {
    if (!Actor::preCreate()) {
        return FALSE;
    }
    charNode.charId = 0;
    charNode.owner = this;
    setInteractionRange(0x3000);
    charFlags = 0;
    setTalkStartMode1();
    return TRUE;
}

void Character::postCreate(s32 a) {
    if (a == 2) {
        PrioList_PushBack(&gCharacterList, &charNode);
    }
    Actor::postCreate(a);
}

BOOL Character::preDelete() {
    if (!Actor::preDelete()) {
        return FALSE;
    }
    List_Remove(&gCharacterList, &charNode);
    return TRUE;
}

BOOL Character::preExecute() {
    if (Actor::preExecute()) {
        return TRUE;
    }
    return FALSE;
}

u32 Character::getCharId() { return charNode.charId; }

void Character::setCharId(u32 a) {
    charNode.charId = a | (profile << 16);
}

extern "C" Character *Character_FindByCharId(u32 id) {
    CharacterListNode *n = (CharacterListNode *)PrioList_FindById(&gCharacterList, id);
    if (n) {
        return n->owner;
    }
    return 0;
}

extern "C" Character *Character_FindInteractionTarget(Character *self) {
    for (CharacterListNode *n = gCharacterList.head; n; n = n->next) {
        Character *o = n->owner;
        if (o == self) {
            continue;
        }
        if (o->checkInteraction(self)) {
            return o;
        }
    }
    return 0;
}

BOOL Character::isInFacingArcOf(Character *other, s16 lo, s16 hi) {
    VecFx32 a, b;
    a = *other->getInteractionPos();
    b = *getInteractionPos();
    s16 d = Math_AngleXZ(&a, &b) - other->rotY;
    if (d >= lo && d <= hi) {
        return TRUE;
    }
    return FALSE;
}

BOOL Character::isInInteractionRange(Character *other) {
    VecFx32 d;
    if (interactionRangeSq == 0) {
        return TRUE;
    }
    d.x = other->getInteractionPos()->x - getInteractionPos()->x;
    d.y = other->getInteractionPos()->y - getInteractionPos()->y;
    d.z = other->getInteractionPos()->z - getInteractionPos()->z;
    if (Vec_MagSqXZ(&d) < (long long)interactionRangeSq) {
        return TRUE;
    }
    return FALSE;
}

BOOL Character::acceptsInteraction(void *a) { return FALSE; }

BOOL Character::checkInteraction(Character *other) {
    if (isInInteractionRange(other)) {
        s16 t = data_020c905c;
        if (isInFacingArcOf(other, -t, t)) {
            return acceptsInteraction(other);
        }
    }
    return FALSE;
}

void Character::onInteractionEvent(u32 a, u8 b) {}

VecFx32 *Character::getInteractionPos() { return &position; }

BOOL Character::acceptsInteractionOutOfRange(void *a) { return FALSE; }

BOOL Character::acceptsSelfRequestedInteraction(void *a) { return FALSE; }

BOOL Character::getHeldItemPos(VecFx32 *out) { return FALSE; }

void Character::attachTalkRequest(TalkMsgRequest *req) { Talk_AttachRequestToWindow0(req); }

void Character::detachTalkRequest(TalkMsgRequest *req) { Talk_DetachRequest(req); }

void Character::setInteractionRange(s32 v) { interactionRangeSq = func_01ffcb0c(v, v); }

void Character::setTalkStartMode0() {
    clearCharFlags(3);
    setCharFlags(1);
}

void Character::setTalkStartMode1() {
    clearCharFlags(3);
    setCharFlags(2);
}


const s16 data_020c905c = 0x2aaa;
