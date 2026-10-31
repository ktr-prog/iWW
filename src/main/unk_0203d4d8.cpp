#include "types.h"
#include "sys/ProcProfile.h"
#include "sys/ProcBase.h"
#include "talk/TalkRequestQueue.h"
#include "talk/TalkRequestEntry.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "talk/TalkWindowState.h"
#include "net/CommManager.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_0203d4d8.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_0203e7d0.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_02065e88.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_0206e54c.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_02094810.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_020a427c.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/main/unk_020b4828.h"

struct TalkRequestList {
    TalkRequestEntry *head;
    u32 tail;
    TalkRequestList() {
        head = 0;
        tail = 0;
    }
};

typedef BOOL (*TalkRequestFn)(TalkRequestEntry *);

extern TalkRequestEntry *gTalkRequestCurrent;
extern u32 sTalkTargetId;
extern u32 sTalkRequestFlags;
extern TalkRequestList sTalkRequestList;
extern TalkRequestFn sTalkRequestRunFns[];
extern TalkRequestFn sTalkRequestStartFns[];
extern TalkRequestFn sTalkRequestBeginFns[];
extern TalkRequestFn sTalkRequestEndFns[];

extern "C" {
extern CommManager *gCommManager;

Character *Character_FindByCharId(u32 id);
TalkRequestEntry *TalkRequestPool_Alloc();
void PrioList_Insert(TalkRequestList *l, TalkRequestEntry *t);
void TalkRequestList_FreeAll(TalkRequestList *l);
void List_Remove(void *l, void *t);
BOOL TalkRequest_IsActive();
void TalkRequest_SetTalkTarget(u32 v);
void TalkRequest_FinishCurrent();
Character *Character_FindInteractionTarget(Character *o);
BOOL TalkRequest_AcquireHostLock(TalkRequestEntry *t);

void TalkRequestFlags_Set(u32 mask);
BOOL TalkRequestFlags_Test(u32 mask);
BOOL TalkRequest_AddPlayerExclusive(u32 x);
void TalkRequestEntry_Free(void *p);
void TalkRequestQueue_Reset(void);
void PrioList_Init(void *p);
void TalkRequestPool_Reset(void);
BOOL TalkRequest_Add(u32 a, u32 b, u32 c, u32 d, u8 e);
BOOL TalkRequest_IsCurrentKind(u32 x);
BOOL TalkRequestFlags_IsEventWarpBlock();
BOOL TalkRequestFlags_IsResetti();
BOOL TalkRequestFlags_IsSceneHold();
void TalkRequestFlags_SetEventWarpReady();
void TalkRequestFlags_SetEventWarpStarted();
void TalkRequestFlags_Clear(u32 mask);
void TalkRequest_NotifyTarget(Character *o, u32 v);
BOOL TalkRequest_AcquireTarget(TalkRequestEntry *t);
BOOL TalkRequest_AcquireAreaTarget(TalkRequestEntry *t);
void TalkRequest_ReleaseTarget(TalkRequestEntry *t, u32 v);
void TalkRequestQueue_StepEnd(TalkRequestEntry *t);
void TalkRequestQueue_StepRun(TalkRequestEntry *t);
void TalkRequestQueue_StepBegin(TalkRequestEntry *t);
void TalkRequestQueue_StartNext(TalkRequestEntry *t);

}


extern "C" BOOL TalkRequest_FinishExclusive(u32 x);
extern "C" BOOL TalkRequest_IsExclusiveRunning(u32 x);

extern "C" void TalkRequestFlags_Set(u32 mask);
extern "C" BOOL TalkRequestFlags_Test(u32 mask);

void Character::clearTalkStartMode() { clearCharFlags(3); }

s32 Character::getTalkStartMode() {
    if (testCharFlags(1)) {
        return 0;
    }
    if (testCharFlags(2)) {
        return 1;
    }
    return 2;
}

void Character::setAreaSynced() { setCharFlags(4); }

BOOL Character::isAreaSynced() { return testCharFlags(4); }

BOOL Character::testCharFlags(u32 mask) {
    if (charFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void Character::setCharFlags(u32 mask) { charFlags = charFlags | mask; }

void Character::clearCharFlags(u32 mask) { charFlags = charFlags & ~mask; }

extern "C" TalkRequestQueue *TalkRequestQueue_Create(void) {
    return new TalkRequestQueue();
}

extern "C" void TalkRequestQueue_Reset(void) {
    PrioList_Init(&sTalkRequestList);
    TalkRequestPool_Reset();
    gTalkRequestCurrent = 0;
    sTalkTargetId = 0;
    TalkRequestFlags_Clear(6);
}

extern "C" void TalkRequestQueue_StartInitial(void) {
    TalkRequestQueue_Reset();
    TalkRequestEntry *s = TalkRequestPool_Alloc();
    s32 r = Field_GetExitedBuildingKey();
    if (r != 0) {
        s->requesterId = (u32)r;
        s->targetId = 0;
        s->kind = 0xc;
        s->phase = 2;
        s->state = 7;
    } else {
        s->requesterId = 0;
        s->targetId = 0;
        s->kind = 4;
        s->phase = 3;
        s->state = 5;
    }
    s->priority = 1;
    s->result = 5;
    gTalkRequestCurrent = s;
}

extern "C" BOOL TalkRequest_IsActive(void) {
    if (gTalkRequestCurrent) {
        return TRUE;
    }
    return FALSE;
}

BOOL TalkRequestQueue::onCreate() {
    TalkRequestQueue_Reset();
    CharInteractSync_Reset();
    sTalkRequestFlags = 0;
    return TRUE;
}

BOOL TalkRequestQueue::onDelete() { return TRUE; }

extern "C" BOOL TalkRequest_StartMenu(TalkRequestEntry *s) {
    if (!MenuCtrl_IsIdle()) {
        return FALSE;
    }
    if (!PlayerActor_CanOpenMenu()) {
        return FALSE;
    }
    if (!PlayerActor_RequestAct05()) {
        return FALSE;
    }
    MenuCtrl_RequestOpen(s->state);
    return TRUE;
}

extern "C" u32 TalkRequest_RunMenu(u32 a) {
    return MenuCtrl_IsFinished();
}

extern "C" BOOL TalkRequest_EndMenu(void) {
    if (PlayerActor_RequestReturnToWait()) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_AcquireHostLock(TalkRequestEntry *s) {
    switch (CharInteractSync_Check(s->targetId)) {
    case 2:
        s->state = 2;
        break;
    case 1:
        s->state = 1;
        break;
    case 0:
        return FALSE;
    }
    if (s->kind != 7 && !PlayerActor_RequestAct10()) {
        return FALSE;
    }
    TalkRequest_SetTalkTarget(s->targetId);
    CharInteractSync_RequestLock(s->targetId);
    return TRUE;
}

extern "C" BOOL TalkRequest_AcquireAreaTarget(TalkRequestEntry *t) {
    s32 r = CharInteractSync_CheckArea();
    switch (r) {
    case 2:
        if (gCommManager->isOnline()) {
            Character *o = Character_FindByCharId(t->targetId);
            if ((o)->isAreaSynced()) {
                if (t->result == 1) {
                    if (!o->acceptsSelfRequestedInteraction((Character *)PlayerActor_GetActor(4))) {
                        return FALSE;
                    }
                }
            }
        }
        t->state = 2;
        break;
    case 1:
        t->state = 0;
        break;
    case 0:
        return FALSE;
    }
    if (t->kind != 7) {
        if (!PlayerActor_RequestAct10()) {
            return FALSE;
        }
    }
    TalkRequest_SetTalkTarget(t->targetId);
    if (r == 1) {
        CharInteractSync_SendQuery(t->targetId, t->result);
    }
    return TRUE;
}

extern "C" BOOL TalkRequest_AcquireTarget(TalkRequestEntry *t) {
    Character *o = Character_FindByCharId(t->targetId);
    if ((o)->isAreaSynced()) {
        if (!TalkRequest_AcquireAreaTarget(t)) {
            return FALSE;
        }
    } else {
        if (!TalkRequest_AcquireHostLock(t)) {
            return FALSE;
        }
    }
    return TRUE;
}

extern "C" void TalkRequest_NotifyTarget(Character *o, u32 v) {
    if ((o)->isAreaSynced()) {
        if (CharInteractSync_CheckArea() == 1) {
            CharInteractSync_SendEvent((o)->getCharId(), v);
        }
    }
    o->onInteractionEvent(v, 4);
}

extern "C" void TalkRequest_ReleaseTarget(TalkRequestEntry *t, u32 v) {
    Character *o = Character_FindByCharId(t->targetId);
    if (o != NULL) {
        if ((o)->isAreaSynced()) {
            if (CharInteractSync_CheckArea() == 1) {
                CharInteractSync_SendEvent(t->targetId, v);
            }
        }
        o->onInteractionEvent(v, 4);
    }
    TalkRequest_SetTalkTarget(0);
    if (t->kind == 7) {
        PlayerActor_SetEventLock(0);
    }
}

extern "C" BOOL TalkRequest_StartTalk(TalkRequestEntry *t) {
    Character *a = Character_FindByCharId(t->targetId);
    Character *b = Character_FindByCharId(t->requesterId);
    if (!PlayerActor_CanStartTalk()) {
        return FALSE;
    }
    t->result = 0;
    if (a == NULL) {
        Character *n = Character_FindInteractionTarget(b);
        if (n == NULL) {
            return FALSE;
        }
        t->targetId = (n)->getCharId();
    } else if (!(a)->checkInteraction(b)) {
        if (a->acceptsInteractionOutOfRange(b)) {
            t->result = 5;
        } else {
            return FALSE;
        }
    }
    if (TalkRequest_AcquireTarget(t)) {
        PlayerActor_RequestAct10();
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_BeginTalk(TalkRequestEntry *t) {
    Character *o = Character_FindByCharId(t->targetId);
    switch (t->state) {
    case 0:
    case 1:
        switch (sCharInteractSyncResult) {
        case 1:
            if (t->kind == 7) {
                t->state = 8;
            } else {
                t->state = 2;
            }
            break;
        case 2:
            t->state = 3;
            break;
        }
        break;
    }
    if (t->state == 8) {
        if (!PlayerActor_CanStartTalk()) {
            return FALSE;
        }
        if (!PlayerActor_RequestAct10()) {
            return FALSE;
        }
        t->state = 2;
    }
    switch (t->state) {
    case 2: {
        o->onInteractionEvent(3, 4);
        s32 r = (o)->getTalkStartMode();
        if (t->result == 5) {
            r = 2;
        }
        if (r == 2) {
            PlayerActor_RequestAct10();
            TalkRequest_NotifyTarget(o, t->result);
            t->state = 5;
        } else {
            PlayerActor_RequestStowThenAct10(r);
            t->state = 4;
        }
        return TRUE;
    }
    case 3:
        if (PlayerActor_RequestReturnToWait()) {
            TalkRequest_ReleaseTarget(t, 4);
            TalkRequest_FinishCurrent();
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_StartTalk6(TalkRequestEntry *t) {
    Character_FindByCharId(t->requesterId);
    if (!PlayerActor_CanStartTalk()) {
        return FALSE;
    }
    t->result = 1;
    if (TalkRequest_AcquireTarget(t)) {
        PlayerActor_RequestAct10();
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_RunTalk(TalkRequestEntry *t) {
    Character *o = Character_FindByCharId(t->targetId);
    switch (t->state) {
    case 4:
        if (PlayerActor_IsStowFinished()) {
            TalkRequest_NotifyTarget(o, t->result);
            t->state = 5;
        }
        break;
    case 5:
        break;
    case 6:
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_EndTalk(TalkRequestEntry *t) {
    if (PlayerActor_RequestReturnToWait()) {
        TalkRequest_ReleaseTarget(t, 8);
        CharInteractSync_ReleaseLock();
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_StartTalk7(TalkRequestEntry *t) {
    if (Character_FindByCharId(t->requesterId) == NULL) {
        return FALSE;
    }
    if (!PlayerActor_CanAcceptTalk()) {
        return FALSE;
    }
    if (!PlayerActor_SetEventLock(1)) {
        return FALSE;
    }
    t->result = 1;
    return TalkRequest_AcquireTarget(t);
}

extern "C" BOOL TalkRequest_StartSceneExit(TalkRequestEntry *t) {
    Character *o = Character_FindByCharId(t->requesterId);
    if (!PlayerActor_CanStartTalk()) {
        return FALSE;
    }
    if (!PlayerActor_LocalRequestExitWalkOut()) {
        return FALSE;
    }
    if (o != NULL) {
        o->onInteractionEvent(2, 4);
    }
    SceneWarp_RequestExit(Scene_GetWarpRequest(), t->state);
    return TRUE;
}

extern "C" BOOL TalkRequest_StartEventWarp(TalkRequestEntry *) {
    if (!PlayerActor_CanAcceptTalk()) {
        return FALSE;
    }
    PlayerActor_SetEventLock(1);
    TalkRequestFlags_SetEventWarpStarted();
    return TRUE;
}

extern "C" BOOL TalkRequest_BeginEventWarp(TalkRequestEntry *) {
    if (!PlayerActor_IsEventIdle()) {
        return FALSE;
    }
    TalkRequestFlags_SetEventWarpReady();
    return TRUE;
}

extern "C" BOOL TalkRequest_BeginSceneEntryChar(TalkRequestEntry *t) {
    Character *o = Character_FindByCharId(t->requesterId);
    if (o == NULL) {
        return FALSE;
    }
    if (t->state == 7) {
        switch (CharInteractSync_Check(t->requesterId)) {
        case 2:
            t->state = 2;
            break;
        case 1:
            t->state = 1;
            CharInteractSync_RequestLock(t->requesterId);
            break;
        }
    }
    if (t->state == 1) {
        switch (sCharInteractSyncResult) {
        case 1:
            t->state = 2;
            break;
        case 2:
            CharInteractSync_RequestLock(t->requesterId);
            break;
        }
    }
    if (t->state == 2) {
        o->onInteractionEvent(6, 4);
        t->state = 5;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_EndSceneEntryChar(TalkRequestEntry *) {
    CharInteractSync_ReleaseLock();
    return TRUE;
}

extern "C" BOOL TalkRequest_RunSceneEntry(TalkRequestEntry *t) {
    if (TalkRequestFlags_IsSceneHold()) {
        return FALSE;
    }
    BOOL b = gScreenTransition.state == 2 ? TRUE : FALSE;
    if (!b) {
        return FALSE;
    }
    if (t->result == 6) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_StartExclusive(TalkRequestEntry *t) {
    if (!PlayerActor_CanStartTalk()) {
        return FALSE;
    }
    if (!PlayerActor_RequestAct10()) {
        return FALSE;
    }
    t->state = 5;
    return TRUE;
}

extern "C" BOOL TalkRequest_RunExclusive(TalkRequestEntry *t) {
    if (t->state == 6) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_EndExclusive(TalkRequestEntry *) {
    if (PlayerActor_RequestReturnToWait()) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_StartLeaveRoom(TalkRequestEntry *t) {
    if (!PlayerActor_IsInterruptible()) {
        return FALSE;
    }
    if (!PlayerActor_LocalRequestLeaveRoom()) {
        return FALSE;
    }
    t->state = 5;
    return TRUE;
}

extern "C" BOOL TalkRequest_RunLeaveRoom(TalkRequestEntry *t) {
    if (t->state == 6) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_StartSimple(TalkRequestEntry *t) {
    t->state = 5;
    return TRUE;
}

extern "C" BOOL TalkRequest_RunSimple(TalkRequestEntry *t) {
    if (t->state == 6) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_RunNetSyncHold(TalkRequestEntry *t) {
    if (t->state == 6) {
        PlayerActor_SetEventLock(0);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_StepUnused(TalkRequestEntry *) { return FALSE; }

extern "C" BOOL TalkRequest_StepPass(TalkRequestEntry *) { return TRUE; }

extern "C" BOOL TalkRequest_StepBlock(TalkRequestEntry *) { return FALSE; }

extern "C" void TalkRequestQueue_StartNext(TalkRequestEntry *) {
    TalkRequestEntry *t = sTalkRequestList.head;
    TalkRequestFn *tbl = sTalkRequestStartFns;
    for (; t != NULL; t = t->next) {
        if (tbl[t->kind](t)) {
            List_Remove(&sTalkRequestList, t);
            gTalkRequestCurrent = t;
            t->phase = 2;
            break;
        }
    }
}

extern "C" void TalkRequestQueue_StepBegin(TalkRequestEntry *) {
    TalkRequestEntry *t = gTalkRequestCurrent;
    if (t->phase == 2) {
        if (sTalkRequestBeginFns[t->kind](t)) {
            gTalkRequestCurrent->phase = 3;
        }
    }
}

extern "C" void TalkRequestQueue_StepRun(TalkRequestEntry *) {
    TalkRequestEntry *t = gTalkRequestCurrent;
    if (t->phase == 3) {
        if (sTalkRequestRunFns[t->kind](t)) {
            gTalkRequestCurrent->phase = 4;
        }
    }
}

extern "C" void TalkRequestQueue_StepEnd(TalkRequestEntry *) {
    TalkRequestEntry *t = gTalkRequestCurrent;
    if (t->phase == 4) {
        if (sTalkRequestEndFns[t->kind](t)) {
            TalkRequest_FinishCurrent();
        }
    }
}

BOOL TalkRequestQueue::onExecute() {
    if (TalkRequest_IsActive()) {
        TalkRequestQueue_StepRun((TalkRequestEntry *)this);
        TalkRequestQueue_StepEnd((TalkRequestEntry *)this);
    }
    if (!TalkRequest_IsActive()) {
        TalkRequestQueue_StartNext((TalkRequestEntry *)this);
    }
    if (TalkRequest_IsActive()) {
        TalkRequestQueue_StepBegin((TalkRequestEntry *)this);
    }
    TalkRequestList_FreeAll(&sTalkRequestList);
    return TRUE;
}

BOOL TalkRequestQueue::onDraw() {
    return TRUE;
}

BOOL TalkRequestQueue::postExecute(u32 b) {
    NetArea_SendStateToNewOwner();
    NetArea_SendStateToRequester();
    if (gActorDefaultParent != 0) {
        Scene_CheckExit(gActorDefaultParent);
    }
    return ProcBase::postExecute(b);
}

extern "C" BOOL TalkRequest_IsCurrentKind(u32 x) {
    if (gTalkRequestCurrent == NULL) {
        return FALSE;
    }
    if (gTalkRequestCurrent->kind == x) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_Add(u32 a, u32 b, u32 c, u32 d, u8 e) {
    TalkRequestEntry *t = TalkRequestPool_Alloc();
    if (t == NULL) {
        return FALSE;
    }
    t->requesterId = a;
    t->targetId = b;
    t->kind = c;
    t->priority = d;
    t->state = e;
    t->result = 0;
    t->unk_18 = 0;
    t->unk_19 = 0;
    t->phase = 1;
    PrioList_Insert(&sTalkRequestList, t);
    return TRUE;
}

extern "C" BOOL TalkRequest_AddSceneExit(Character *o, s32 v) {
    u32 id;
    if (v < 0) {
        return FALSE;
    }
    id = 0;
    if (o != NULL) {
        id = (o)->getCharId();
    }
    return TalkRequest_Add(id, 0, 3, 1, (u8)v);
}

extern "C" BOOL TalkRequest_AddLeaveRoom() {
    return TalkRequest_Add(0, ((Character *)PlayerActor_GetActor(4))->getCharId(), 8, 1, 0);
}

extern "C" BOOL TalkRequest_FinishLeaveRoom() {
    if (!TalkRequest_IsCurrentKind(8)) {
        return FALSE;
    }
    gTalkRequestCurrent->state = 6;
    return TRUE;
}

extern "C" BOOL TalkRequest_AddMenu(u8 x) {
    Character *o = (Character *)PlayerActor_GetActor(4);
    if (o == NULL) {
        return FALSE;
    }
    return TalkRequest_Add(0, (o)->getCharId(), 1, 2, x);
}

extern "C" BOOL TalkRequest_AddEventWarp() {
    if (TalkRequestFlags_IsResetti() || TalkRequestFlags_IsEventWarpBlock()) {
        return FALSE;
    }
    Character *o = (Character *)PlayerActor_GetActor(4);
    if (o == NULL) {
        return FALSE;
    }
    TalkRequestFlags_Clear(6);
    return TalkRequest_Add(0, (o)->getCharId(), 0xb, 1, 0);
}

extern "C" BOOL TalkRequestFlags_IsEventWarpStarted() { return TalkRequestFlags_Test(2); }

extern "C" BOOL TalkRequestFlags_IsEventWarpReady() { return TalkRequestFlags_Test(4); }

extern "C" void TalkRequestFlags_SetEventWarpStarted() { TalkRequestFlags_Set(2); }

extern "C" void TalkRequestFlags_SetEventWarpReady() { TalkRequestFlags_Set(4); }

extern "C" BOOL TalkRequestFlags_IsSceneHold() { return TalkRequestFlags_Test(1); }

extern "C" void TalkRequestFlags_SetSceneHold() { TalkRequestFlags_Set(1); }

extern "C" void TalkRequestFlags_ClearSceneHold() { TalkRequestFlags_Clear(1); }

extern "C" BOOL TalkRequestFlags_IsResetti() { return TalkRequestFlags_Test(8); }

extern "C" void TalkRequestFlags_SetResetti() { TalkRequestFlags_Set(8); }

extern "C" void TalkRequestFlags_ClearResetti() { TalkRequestFlags_Clear(8); }

extern "C" BOOL TalkRequestFlags_IsEventWarpBlock() { return TalkRequestFlags_Test(0x20); }

extern "C" void TalkRequestFlags_SetEventWarpBlock() { TalkRequestFlags_Set(0x20); }

extern "C" void TalkRequestFlags_ClearEventWarpBlock() { TalkRequestFlags_Clear(0x20); }

extern "C" BOOL TalkRequestFlags_Test(u32 mask) {
    if ((sTalkRequestFlags & mask) != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void TalkRequestFlags_Set(u32 mask) {
    sTalkRequestFlags |= mask;
}

extern "C" void TalkRequestFlags_Clear(u32 mask) {
    sTalkRequestFlags &= ~mask;
}

extern "C" BOOL TalkRequest_AddPlayerExclusive(u32 x) {
    return TalkRequest_Add(0, ((Character *)PlayerActor_GetActor(4))->getCharId(), x, 4, 0);
}

extern "C" BOOL TalkRequest_IsExclusiveRunning(u32 x) {
    if (TalkRequest_IsCurrentKind(x) && gTalkRequestCurrent->state != 6) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_FinishExclusive(u32 x) {
    if (!TalkRequest_IsCurrentKind(x)) {
        return FALSE;
    }
    gTalkRequestCurrent->state = 6;
    return TRUE;
}

extern "C" BOOL TalkRequest_AddSaveMenu(void) { return TalkRequest_AddPlayerExclusive(5); }

extern "C" BOOL TalkRequest_IsSaveMenuRunning(void) { return TalkRequest_IsExclusiveRunning(5); }

extern "C" BOOL TalkRequest_FinishSaveMenu(void) { return TalkRequest_FinishExclusive(5); }

extern "C" BOOL TalkRequest_AddCameraView(void) { return TalkRequest_AddPlayerExclusive(0xa); }

extern "C" BOOL TalkRequest_IsCameraViewRunning(void) { return TalkRequest_IsExclusiveRunning(0xa); }

extern "C" BOOL TalkRequest_FinishCameraView(void) { return TalkRequest_FinishExclusive(0xa); }

extern "C" BOOL TalkRequest_AddPlayerMessage(void) {
    if (gTalkRequestCurrent != 0) {
        return FALSE;
    }
    return TalkRequest_Add(0, 0, 9, 0, 0);
}

extern "C" BOOL TalkRequest_FinishPlayerMessage(void) {
    if (!TalkRequest_IsCurrentKind(9)) {
        return FALSE;
    }
    gTalkRequestCurrent->state = 6;
    return TRUE;
}

extern "C" BOOL TalkRequest_IsPlayerMessage(void) {
    return TalkRequest_IsCurrentKind(9);
}

extern "C" BOOL TalkRequest_AddSlingshot(void) {
    if (gTalkRequestCurrent != 0) {
        return FALSE;
    }
    return TalkRequest_Add(0, 0, 0xe, 0, 0);
}

extern "C" BOOL TalkRequest_FinishSlingshot(void) {
    if (!TalkRequest_IsCurrentKind(0xe)) {
        return FALSE;
    }
    gTalkRequestCurrent->state = 6;
    return TRUE;
}

extern "C" BOOL TalkRequest_FinishSceneEntry(void) {
    if (!TalkRequest_IsCurrentKind(4) && !TalkRequest_IsCurrentKind(0xc)) {
        return FALSE;
    }
    gTalkRequestCurrent->result = 6;
    return TRUE;
}

extern "C" BOOL TalkRequest_AddTalk(Character *a, Character *b) {
    u32 t = 0;
    if (b != NULL) {
        t = b->getCharId();
    }
    return TalkRequest_Add(a->getCharId(), t, 2, 3, 0);
}

extern "C" BOOL TalkRequest_AddPlayerTalk6(Character *a, s32 b) {
    if (b == 0) {
        u32 t = ((Character *)PlayerActor_GetActor(4))->getCharId();
        return TalkRequest_Add(t, a->getCharId(), 6, 3, 0);
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_AddPlayerTalk7(Character *a, s32 b) {
    if (b == 0) {
        u32 t = ((Character *)PlayerActor_GetActor(4))->getCharId();
        return TalkRequest_Add(t, a->getCharId(), 7, 3, 0);
    }
    return FALSE;
}

extern "C" BOOL TalkRequest_SetTargetDone(Character *x) {
    if (!TalkRequest_IsCurrentKind(2) && !TalkRequest_IsCurrentKind(6) && !TalkRequest_IsCurrentKind(7)) {
        return FALSE;
    }
    TalkRequestEntry *p = gTalkRequestCurrent;
    u32 v = x->getCharId();
    if (p->targetId != v) {
        return FALSE;
    }
    p->state = 6;
    return TRUE;
}

extern "C" BOOL TalkRequest_IsTalking(void) {
    if (TalkRequest_IsCurrentKind(2) || TalkRequest_IsCurrentKind(6) || TalkRequest_IsCurrentKind(7)) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void TalkRequest_SetTalkTarget(u32 p) {
    sTalkTargetId = p;
}

extern "C" Character *TalkRequest_GetTalkTarget(void) {
    if (TalkRequest_IsCurrentKind(2) || TalkRequest_IsCurrentKind(6) || TalkRequest_IsCurrentKind(7)) {
        return Character_FindByCharId(sTalkTargetId);
    }
    return NULL;
}

extern "C" void Talk_AttachRequestToWindow0(TalkMsgRequest *x) {
    TalkWindow_Get(0)->attachRequest(x);
}

extern "C" void Talk_DetachRequest(TalkMsgRequest *p) {
    p->window->detachRequest();
}

extern "C" void TalkRequest_FinishCurrent(void) {
    TalkRequestEntry_Free(gTalkRequestCurrent);
    gTalkRequestCurrent = 0;
}

extern "C" BOOL TalkRequest_BeginNetSyncHold(void) {
    if (!PlayerActor_GetActor(4)) {
        return FALSE;
    }
    if (TalkRequest_IsActive()) {
        MenuCtrl_RequestForceClose();
        return FALSE;
    }
    if (!PlayerActor_CanAcceptTalk()) {
        return FALSE;
    }
    PlayerActor_SetEventLock(1);
    TalkRequestEntry *p = TalkRequestPool_Alloc();
    p->requesterId = 0;
    p->targetId = 0;
    p->kind = 0xd;
    p->phase = 3;
    p->state = 5;
    gTalkRequestCurrent = p;
    return TRUE;
}

extern "C" BOOL TalkRequest_EndNetSyncHold(void) {
    if (TalkRequest_IsCurrentKind(0xd)) {
        gTalkRequestCurrent->state = 6;
        return TRUE;
    }
    return FALSE;
}

extern "C" s32 TalkRequestFlags_IsTitleTimeout(void) { return TalkRequestFlags_Test(0x10); }

extern "C" void TalkRequestFlags_SetTitleTimeout(void) { return TalkRequestFlags_Set(0x10); }

extern "C" void TalkRequestFlags_ClearTitleTimeout(void) { return TalkRequestFlags_Clear(0x10); }

extern TalkRequestFn sTalkRequestBeginFns[15];
extern TalkRequestEntry *gTalkRequestCurrent;
extern u32 sTalkRequestFlags;
extern TalkRequestFn sTalkRequestRunFns[15];
extern TalkRequestFn sTalkRequestStartFns[15];
extern TalkRequestFn sTalkRequestEndFns[15];
extern u32 sTalkTargetId;
extern TalkRequestList sTalkRequestList;

extern ProcProfile data_020d9520;
extern TalkRequestFn sTalkRequestBeginFns[15];
extern u32 sTalkRequestFlags;
extern TalkRequestEntry *gTalkRequestCurrent;
extern TalkRequestFn sTalkRequestRunFns[15];
extern TalkRequestFn sTalkRequestStartFns[15];
extern TalkRequestFn sTalkRequestEndFns[15];
extern TalkRequestList sTalkRequestList;
extern u32 sTalkTargetId;

ProcProfile data_020d9520 = {(void *(*)())TalkRequestQueue_Create, 0xd7, 0xd6};

TalkRequestFn sTalkRequestBeginFns[15] = {
    (TalkRequestFn)TalkRequest_StepUnused, (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_BeginTalk,
    (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_StepPass,
    (TalkRequestFn)TalkRequest_BeginTalk, (TalkRequestFn)TalkRequest_BeginTalk, (TalkRequestFn)TalkRequest_StepPass,
    (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_BeginEventWarp,
    (TalkRequestFn)TalkRequest_BeginSceneEntryChar, (TalkRequestFn)TalkRequest_StepBlock, (TalkRequestFn)TalkRequest_StepPass
};

u32 sTalkRequestFlags;

TalkRequestEntry *gTalkRequestCurrent;

TalkRequestFn sTalkRequestRunFns[15] = {
    (TalkRequestFn)TalkRequest_StepUnused, (TalkRequestFn)TalkRequest_RunMenu, (TalkRequestFn)TalkRequest_RunTalk,
    (TalkRequestFn)TalkRequest_StepBlock, (TalkRequestFn)TalkRequest_RunSceneEntry, (TalkRequestFn)TalkRequest_RunExclusive,
    (TalkRequestFn)TalkRequest_RunTalk, (TalkRequestFn)TalkRequest_RunTalk, (TalkRequestFn)TalkRequest_RunLeaveRoom,
    (TalkRequestFn)TalkRequest_RunSimple, (TalkRequestFn)TalkRequest_RunExclusive, (TalkRequestFn)TalkRequest_StepBlock,
    (TalkRequestFn)TalkRequest_RunSceneEntry, (TalkRequestFn)TalkRequest_RunNetSyncHold, (TalkRequestFn)TalkRequest_RunSimple
};

TalkRequestFn sTalkRequestStartFns[15] = {
    (TalkRequestFn)TalkRequest_StepUnused, (TalkRequestFn)TalkRequest_StartMenu, (TalkRequestFn)TalkRequest_StartTalk,
    (TalkRequestFn)TalkRequest_StartSceneExit, (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_StartExclusive,
    (TalkRequestFn)TalkRequest_StartTalk6, (TalkRequestFn)TalkRequest_StartTalk7, (TalkRequestFn)TalkRequest_StartLeaveRoom,
    (TalkRequestFn)TalkRequest_StartSimple, (TalkRequestFn)TalkRequest_StartExclusive, (TalkRequestFn)TalkRequest_StartEventWarp,
    (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_StepBlock, (TalkRequestFn)TalkRequest_StartSimple
};

TalkRequestFn sTalkRequestEndFns[15] = {
    (TalkRequestFn)TalkRequest_StepUnused, (TalkRequestFn)TalkRequest_EndMenu, (TalkRequestFn)TalkRequest_EndTalk,
    (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_EndExclusive,
    (TalkRequestFn)TalkRequest_EndTalk, (TalkRequestFn)TalkRequest_EndTalk, (TalkRequestFn)TalkRequest_StepPass,
    (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_EndExclusive, (TalkRequestFn)TalkRequest_StepPass,
    (TalkRequestFn)TalkRequest_EndSceneEntryChar, (TalkRequestFn)TalkRequest_StepPass, (TalkRequestFn)TalkRequest_StepPass
};

TalkRequestList sTalkRequestList;

u32 sTalkTargetId;
