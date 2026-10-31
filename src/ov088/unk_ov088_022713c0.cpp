#include "types.h"
#include "gfx/VecFx32.h"
#include "town/VisitorPos.h"
#include "talk/TalkStartMsg.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "talk/MsgString9B.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/ChoiceString.h"
#include "talk/ChoiceList.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "game/Unk_0201acf8.h"
#include "player/PlayerData.h"
#include "talk/MsgString.h"
#include "game/Random.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020a8c9c.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov088/unk_ov088_022713c0.h"
#include "proto/main/unk_0204cc1c.h"


class ActorTalkRequest;
class SpNpcShrunk;
class SpNpcShrunkTalk;
class Camera;







extern "C" {
void EventWeekSlots_MarkPlayer(s32 v);
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
u32 Random_Next(u32 *seed);
u8 Math_CountDownU8(u8 *p);
extern u16 data_020c6cc8;
extern u32 data_020c6d1c;
extern s32 data_020c6cf0;
extern Camera *gCamera;
extern VecFx32 gCameraLookAt;
extern s16 data_02135f44[];
s32 func_01ffcb0c(s32 a, s32 b);
BOOL TownMap_IsPosWalkable(VecFx32 *a, s32 b);
void TalkRequest_SetTargetDone(void *p);
void MI_CpuFill8(void *p, s32 v, u32 n);
}






class SpNpcShrunkTalk : public SpNpcTalkRequest {
public:
    SpNpcShrunkTalk();
    virtual ~SpNpcShrunkTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);
    virtual void openEmotionPage(s32 v);

    void attachOwner(SpNpcShrunk *owner);
    void scriptWaitThenEnd();
    void scriptCheckTriggerReaction();
    void scriptOpenEmotionChoice();
    void scriptFirstLesson();
    void setScript(s32 state);
    s32 pickRandomUnlearnedEmotion(u8 *p, s32 n);
    s32 countUnlearnedEmotions(u8 *p, s32 n);

    s32 script;
    u8 scriptStep;
    u8 pad_b1[3];
    SpNpcShrunk *ownerNpc;
    u8 pendingEmotion;
    u8 emotionTaken[0x1e];
    u8 offeredEmotions[5];
};








class SpNpcShrunk : public SpNpcActor {
public:
    SpNpcShrunk() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 v, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual s32 getTeachableEmotion();
    virtual s32 getWalkAnimSpeedScale();

    void teachEmotion(s32 a, s32 b);
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct02();
    BOOL checkCollisionWhileMoving();
    BOOL handleCollision();
    BOOL getOffsetPosIfFree(VecFx32 *out, VecFx32 *p);
    BOOL findRandomWalkTarget(s32 *a, s32 *b);
    BOOL isNearCameraTarget();
    BOOL isInViewBox(VecFx32 *a, VecFx32 *b);
    BOOL setupAct02();
    BOOL mainAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    u8 pad_652[2];
    s32 act;
    SpNpcShrunkTalk talk;
    u8 waitTimer;
    u8 reactionWindow;
};

struct SpNpcShrunkTalkScript {
    void (SpNpcShrunkTalk::*fn)();
    u8 flag;
};

struct SpNpcShrunkActEntry {
    BOOL (SpNpcShrunk::*enter)();
    BOOL (SpNpcShrunk::*exit)();
};

extern "C" SpNpcShrunk *SpNpcShrunk_Create();


extern "C" {
extern SpNpcShrunkTalkScript sSpNpcShrunkTalkScripts[5];
extern SpNpcShrunkActEntry sSpNpcShrunkActTable[5];
extern FxVec3 sSpNpcShrunkSideStepOffsets[2];
extern u8 sSpNpcShrunkModelPath[];
extern u8 sSpNpcShrunkTexturePath[];
}

extern "C" DebugColor data_ov088_022727b4(31, 20, 20, 31);
extern "C" DebugColor data_ov088_022727a8(20, 20, 31, 31);
extern "C" DebugColor data_ov088_022727a4(31, 31, 20, 31);
extern "C" DebugColor data_ov088_022727a0(20, 31, 20, 31);
extern "C" u8 sSpNpcShrunkTexturePath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'u', 'p', 'a', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};
extern "C" u8 sSpNpcShrunkModelPath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'u', 'p', 'a', '.', 'n', 's', 'b', 'm', 'd', 0};
extern "C" DebugColor data_ov088_022727b0(20, 31, 31, 31);
extern "C" ActorProfile sSpNpcShrunkProfile = {(void *(*)())SpNpcShrunk_Create, 0x62, 0x69, 2, 0x5000, 0x5000, 0x3e800};
extern "C" DebugColor data_ov088_022727ac(20, 24, 24, 31);
SpNpcShrunkTalkScript sSpNpcShrunkTalkScripts[5] = {
    {NULL, 0},
    {&SpNpcShrunkTalk::scriptFirstLesson, 1},
    {&SpNpcShrunkTalk::scriptOpenEmotionChoice, 1},
    {&SpNpcShrunkTalk::scriptCheckTriggerReaction, 1},
    {&SpNpcShrunkTalk::scriptWaitThenEnd, 1},
};

SpNpcShrunkActEntry sSpNpcShrunkActTable[5] = {
    {&SpNpcShrunk::setupAct00, &SpNpcShrunk::mainAct00},
    {NULL, &SpNpcShrunk::mainAct01},
    {&SpNpcShrunk::setupAct02, &SpNpcShrunk::mainAct02},
    {&SpNpcShrunk::setupAct03, &SpNpcShrunk::mainAct03},
    {&SpNpcShrunk::setupAct04, &SpNpcShrunk::mainAct04},
};

FxVec3 sSpNpcShrunkSideStepOffsets[2] = {FxVec3(0x800, 0, 0x1000), FxVec3(-0x800, 0, 0x1000)};

extern "C" SpNpcShrunk *SpNpcShrunk_Create() {
    return new SpNpcShrunk();
}

s32 SpNpcShrunk::getWalkAnimSpeedScale() { return data_020c6cf0; }

BOOL SpNpcShrunk::preCreate() {
    if (SpNpcActor::preCreate() == 0) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcShrunk::onCreate() {
    if (SpNpcActor::onCreate() == 0) {
        return FALSE;
    }
    changeAct(3);
    return TRUE;
}

BOOL SpNpcShrunk::onDelete() {
    if (SpNpcActor::onDelete() == 0) {
        return FALSE;
    }
    if (EventAnnounce_IsBusy() == 0) {
        ((VisitorPos *)TownSessionState_GetVisitorPos(TownSessionState_Get()))->pickRandomPos();
    }
    return TRUE;
}

u8 *SpNpcShrunk::getTexturePath() { return sSpNpcShrunkTexturePath; }

u8 *SpNpcShrunk::getModelPath() { return sSpNpcShrunkModelPath; }

BOOL SpNpcShrunk::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcShrunkActTable[act].exit != NULL) {
        result = (this->*sSpNpcShrunkActTable[act].exit)();
    }
    return result;
}

void SpNpcShrunk::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcShrunkActTable[state].enter != NULL) {
        ok = (this->*sSpNpcShrunkActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcShrunk::setupAct00() { return TRUE; }

BOOL SpNpcShrunk::mainAct00() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcShrunk::mainAct01() { return TRUE; }

BOOL SpNpcShrunk::setupAct02() {
    waitTimer = 0;
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, (VecFx32 *)(&gVec3Zero), 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcShrunk::isInViewBox(VecFx32 *a, VecFx32 *b) {
    BOOL r = FALSE;
    BOOL f1 = FALSE;
    BOOL f2 = FALSE;
    s32 ax = a->x;
    s32 bx = b->x;
    if (bx > ax - 0x10000) {
        if (bx < ax + 0x10000) {
            f2 = TRUE;
        }
    }
    if (f2) {
        s32 bz = b->z;
        s32 az = a->z;
        if (bz > az - 0x1a000) {
            f1 = TRUE;
        }
    }
    if (f1) {
        s32 bz = b->z;
        s32 az = a->z;
        if (bz < az + 0xa000) {
            r = TRUE;
        }
    }
    return r;
}

BOOL SpNpcShrunk::isNearCameraTarget() {
    VecFx32 *pos = (VecFx32 *)&position;
    BOOL r = FALSE;
    if (gCamera != 0) {
        VecFx32 v;
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        r = isInViewBox(&v, pos);
    }
    return r;
}

BOOL SpNpcShrunk::findRandomWalkTarget(s32 *a, s32 *b) {
    BOOL r = FALSE;
    VecFx32 v;
    s32 i;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    for (i = 0; i < 6; i++) {
        s32 idx = ((u16)(s16)Random_Next(&gRandom.seed) >> 4) * 2;
        s32 g = func_01ffcb0c(0xc000, data_02135f44[idx]);
        v.x = g + position.x;
        g = func_01ffcb0c(0xc000, data_02135f44[idx + 1]);
        v.z = g + position.z;
        FieldPos_SnapToUnitCenter(&v, &v);
        if (TownMap_IsPosWalkable(&v, r)) {
            *a = v.x;
            *b = v.z;
            r = TRUE;
            break;
        }
    }
    return r;
}

BOOL SpNpcShrunk::getOffsetPosIfFree(VecFx32 *out, VecFx32 *p) {
    BOOL r = FALSE;
    VecFx32 t;
    Npc_RotateOffsetXZ(&t, (VecFx32 *)&position, p, moveAngleY);
    if (Npc_IsPosBlocked(&t) != 1) {
        out->x = t.x;
        out->y = t.y;
        out->z = t.z;
        r = TRUE;
    }
    return r;
}

BOOL SpNpcShrunk::handleCollision() {
    NpcActionCtrl *p = &actionCtrl;
    NpcMoveCtrl *q = &moveCtrl;
    s32 r6 = ((NpcLookAt *)(&obstacleProbe))->getObstacleBits();
    BOOL r = FALSE;
    VecFx32 v;
    if (((NpcMoveCtrl *)(q))->hasArrived((Character *)(this), 1) == 0) {
        switch (r6) {
        case 3:
            ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            r = TRUE;
            break;
        case 1:
            if (getOffsetPosIfFree(&v, (VecFx32 *)&sSpNpcShrunkSideStepOffsets[1])) {
                ((NpcMoveCtrl *)(q))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            r = TRUE;
            break;
        case 2:
            if (getOffsetPosIfFree(&v, (VecFx32 *)&sSpNpcShrunkSideStepOffsets[0])) {
                ((NpcMoveCtrl *)(q))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            r = TRUE;
            break;
        }
    } else {
        if (((NpcMoveCtrl *)(q))->hasNextLeg()) {
            ((NpcMoveCtrl *)(q))->resetDestination();
        }
    }
    return r;
}

BOOL SpNpcShrunk::checkCollisionWhileMoving() {
    if (speed != 0) {
        if (handleCollision()) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL SpNpcShrunk::mainAct02() {
    NpcActionCtrl *p = &actionCtrl;
    VecFx32 v, w;
    s32 r6 = isNearCameraTarget();
    Math_CountDownU8(&waitTimer);
    if (r6 != 0) {
        if (checkCollisionWhileMoving() == 0) {
            if (p->isActionDone() != 0) {
                if (((Unk_0201acf8 *)(&unk_3aa))->getLevel() == 2) {
                    ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                } else if ((Random_Next(&gRandom.seed) & 7) == 0) {
                    v.x = gVec3Zero.x;
                    v.y = gVec3Zero.y;
                    v.z = gVec3Zero.z;
                    if (findRandomWalkTarget(&v.x, &v.z)) {
                        r6 = Math_AngleXZ(&position, &v);
                        if (NpcActor_IsFrontAngle((s16)(r6 - rotY))) {
                            r6 = 1;
                            if (Random_GlobalBelow(4) == 0) {
                                r6 = 2;
                            }
                            if (r6 != actionCtrl.getAction()) {
                                ((NpcActionCtrl *)(p))->requestAction(r6, 1, v.x, v.z, 0, 0, 0, 0, data_020c6cc8, 0);
                                waitTimer = 0x64;
                            }
                        } else if (actionCtrl.getAction() != 4) {
                            ((NpcActionCtrl *)(p))->requestAction(4, 1, v.x, v.z, 0, r6, 0, 0, data_020c6cc8, 0);
                            waitTimer = 0x50;
                        }
                    } else {
                        ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                    }
                } else {
                    ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                }
            } else if (speed != 0) {
                if (actionCtrl.getAction() == 1 || actionCtrl.getAction() == 2 || actionCtrl.getAction() == 4) {
                    if (waitTimer == 0) {
                        ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                    } else {
                        VecFx32 *q = ((NpcMoveCtrl *)(&moveCtrl))->getDestination();
                        w.x = q->x;
                        w.y = q->y;
                        w.z = q->z;
                        if (NpcActor_IsFrontAngle((s16)(Math_AngleXZ(&position, &w) - rotY)) == 0) {
                            ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                        }
                    }
                }
            }
        }
    } else if (speed != 0) {
        changeAct(3);
    }
    return FALSE;
}

BOOL SpNpcShrunk::setupAct03() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    waitTimer = 0;
    ((NpcFootstepFx *)(&footstepFx))->disableFootsteps();
    return TRUE;
}

BOOL SpNpcShrunk::mainAct03() {
    if (isNearCameraTarget()) {
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcShrunk::setupAct04() {
    Character *p = talk.getTalkPlayer();
    s32 x = rotY;
    if (p != NULL) {
        x = getAngleTo((NpcActor *)(p));
    }
    talkCtrl.requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcShrunk::mainAct04() { return TRUE; }

s32 SpNpcShrunkTalk::countUnlearnedEmotions(u8 *p, s32 n) {
    s32 c = 0;
    s32 i;
    for (i = 0; i < n; p++, i++) {
        if (*p == 0) {
            c++;
        }
    }
    return c;
}

s32 SpNpcShrunkTalk::pickRandomUnlearnedEmotion(u8 *p, s32 n) {
    s32 r;
    s32 c = countUnlearnedEmotions(p, n);
    r = 0;
    if (c <= 0) {
        return -1;
    }
    s32 k = Random_GlobalBelow(c);
    s32 i;
    for (i = 0; i <= n; p++, i++) {
        if (*p == 0) {
            if (k == 0) {
                r = i;
                break;
            }
            k--;
        }
    }
    return r;
}

void SpNpcShrunkTalk::openEmotionPage(s32 mode) {
    ChoiceList *g;
    ChoiceEntry *slot;
    s32 z;
    u8 b[2];
    s32 i;
    u32 r6;
    PlayerData_GetCurrent();
    g = window->getChoiceList();
    b[0] = 0;
    MsgString9B o;
    b[1] = 5;
    ChoiceString str;
    g->clear();
    r6 = 1;
    emotionTaken[0] = r6;
    for (i = 0; i < Emotion_CountLearned(); i++) {
        emotionTaken[Emotion_GetSlot(i)] = r6;
    }
    i = 0;
    z = 0;
    do {
        if (mode == 0) {
            r6 = pickRandomUnlearnedEmotion(&emotionTaken[0], 0x1e);
            if (r6 != -1) {
                if (emotionTaken[r6] == 0) {
                    emotionTaken[r6] = 1;
                }
            } else {
                r6 = 1;
            }
            offeredEmotions[i] = r6;
        } else if (mode == 1) {
            r6 = offeredEmotions[i];
        } else {
            r6 = Emotion_GetSlot(i);
        }
        slot = g->getEntry(i);
        b[1] = r6;
        if (mode != 2) {
            String_Load(&str, &b[1], "st_learn_talk");
        } else {
            String_Load(&str, &b[1], "st_learn");
        }
        ((MsgString *)(slot->getText()))->copy((MsgString *)(&str));
        i++;
    } while (i < 4);
    if (mode == 2) {
        slot = g->getEntry(i);
        b[1] = 5;
        slot->setMsgIndex(&b[1]);
        slot->setBmgName(Choice_GetBmgName(1));
        slot->loadText();
        g->setCount(i + 1);
        g->setCancelToLast();
    } else {
        g->setCount(i);
    }
    window->openChoices(1);
}

void SpNpcShrunkTalk::update() {
    if (sSpNpcShrunkTalkScripts[script].flag != 0) {
        if (sSpNpcShrunkTalkScripts[script].fn != NULL) {
            (this->*sSpNpcShrunkTalkScripts[script].fn)();
        }
    }
}

void SpNpcShrunkTalk::onTaskDone(u32) {
    if (sSpNpcShrunkTalkScripts[script].flag == 0) {
        if (sSpNpcShrunkTalkScripts[script].fn != NULL) {
            (this->*sSpNpcShrunkTalkScripts[script].fn)();
            setScript(0);
        }
    }
}

void SpNpcShrunkTalk::setScript(s32 state) {
    script = state;
    scriptStep = 0;
}

void SpNpcShrunkTalk::scriptFirstLesson() {
    TalkWindowState *r4 = window;
    if (r4->state == 5) {
        u8 b[2];
        ownerNpc->reactionWindow = 0x14;
        if (((NpcActor *)(ownerNpc))->getLastTaughtEmotion() != -1) {
            b[1] = 0x17;
            ((TalkWindowState *)(window))->setSlotFromString(0, &b[1], "st_learn");
            ownerNpc->reactionWindow = 0;
            ownerNpc->waitTimer = 0x14;
            PlayerData_GetCurrent()->setFlag(0x10);
            b[0] = 0xc;
            ownerNpc->teachEmotion(0, 0x17);
            r4->setNextMessage(&b[0], (void *)"sp_npc_reaction");
            Talk_CheckAndSetPlayerFlag(0xe, 1);
            setScript(4);
        }
    }
}

void SpNpcShrunkTalk::scriptOpenEmotionChoice() {
    if (pendingEmotion == 0x17) {
        openEmotionPage(0);
    } else {
        openEmotionPage(1);
    }
    pendingEmotion = 0xff;
    setScript(0);
}

void SpNpcShrunkTalk::scriptCheckTriggerReaction() {
    TalkWindowState *r4 = window;
    if (r4->state == 5) {
        u8 b[2];
        if (ownerNpc->reactionWindow == 0) {
            ownerNpc->reactionWindow = 0x34;
        }
        if (((NpcActor *)(ownerNpc))->getLastTaughtEmotion() == -1) {
            if (Math_CountDownU8(&ownerNpc->reactionWindow) > 2) {
                return;
            }
        }
        b[0] = 0x19;
        if (ownerNpc->reactionWindow <= 2) {
            b[0] = 0x18;
        } else {
            Talk_CheckAndSetPlayerFlag(0xe, 1);
            if (Emotion_FindFreeSlot() == -1) {
                b[0] = 0x1a;
            }
        }
        b[1] = pendingEmotion;
        ((TalkWindowState *)(window))->setSlotFromString(0, &b[1], "st_learn");
        ownerNpc->reactionWindow = 0;
        ownerNpc->waitTimer = 0x14;
        r4->setNextMessage(&b[0], (void *)"sp_npc_reaction");
        setScript(4);
    }
}

void SpNpcShrunkTalk::scriptWaitThenEnd() {
    if (Math_CountDownU8(&ownerNpc->waitTimer) == 0) {
        setScript(0);
        requestReopenWindow();
    }
}

SpNpcShrunkTalk::SpNpcShrunkTalk() {}

SpNpcShrunkTalk::~SpNpcShrunkTalk() {}

void SpNpcShrunkTalk::attachOwner(SpNpcShrunk *owner) {
    resetMsg();
    ownerNpc = owner;
    ownerNpc->reactionWindow = 0;
    MI_CpuFill8(&emotionTaken[0], 0, 0x1e);
    MI_CpuFill8(&offeredEmotions[0], 0xff, 5);
}

void SpNpcShrunkTalk::start(TalkStartMsg *out) {
    out->msgKey = "sp_npc_reaction";
    out->msgIndex = 1;
    if (PlayerData_GetCurrent()->testFlag(0x10) == 1) {
        if (Talk_CheckAndSetPlayerFlag(0xe, 0) == 0) {
            out->msgIndex = Random_GlobalBelow(2) + 0x13;
        } else if (Emotion_CountLearned() == 1) {
            out->msgIndex = Random_GlobalBelow(3) + 0xd;
        } else {
            out->msgIndex = Random_GlobalBelow(3) + 0x10;
        }
    }
}

void SpNpcShrunkTalk::onMessageEnd(u32) {
    s32 t = msgIndex;
    if (t >= 0x1d && t <= 0x39) {
        window->openMode = 0;
        setScript(3);
    }
    switch (msgIndex) {
    case 0xb:
        window->openMode = 0;
        setScript(1);
        break;
    case 0x17:
    case 0x18:
        pendingEmotion = msgIndex;
        setScript(2);
        break;
    case 0x19: {
        s32 r = Emotion_FindFreeSlot();
        if (r != -1) {
            ownerNpc->teachEmotion(r, pendingEmotion);
        }
        break;
    }
    case 0x1a:
        openEmotionPage(2);
        break;
    }
}

void SpNpcShrunkTalk::onChoice(u32) {
    u8 b[3];
    u8 *s;
    s32 t = getChoiceList()->getResult();
    u32 msg;
    s = (u8 *)"sp_npc_reaction";
    msg = 0xff;
    switch (msgIndex) {
    case 0x17:
    case 0x18: {
        u8 v = offeredEmotions[t];
        msg = (u8)(v + 0x1c);
        pendingEmotion = v;
        break;
    }
    case 0x1a:
        if (t == 4) {
            msg = 0x1b;
        } else {
            b[0] = Emotion_GetSlot(t);
            ((TalkWindowState *)(window))->setSlotFromString(1, &b[0], "st_learn");
            ownerNpc->teachEmotion(t, pendingEmotion);
            b[1] = pendingEmotion;
            ((TalkWindowState *)(window))->setSlotFromString(0, &b[1], "st_learn");
            msg = 0x1c;
        }
        break;
    }
    if (msg != 0xff) {
        b[2] = msg;
        window->setNextMessage(&b[2], s);
    }
}

BOOL SpNpcShrunk::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (talkCtrl.isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcShrunk::onInteractionEvent(u32 v, u8) {
    switch (v) {
    case 0:
        changeAct(0);
        break;
    case 3:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(4);
        break;
    case 8:
        changeAct(2);
        break;
    }
}

s32 SpNpcShrunk::getTeachableEmotion() {
    if (reactionWindow != 0) {
        return getNewEmotionToLearn();
    }
    return -1;
}

void SpNpcShrunk::teachEmotion(s32 a, s32 b) {
    Emotion_SetSlot(a, b);
    EventWeekSlots_MarkPlayer(0x43);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov088_022713c0) {
    HOST_OVERLAY_VAR(data_ov088_022727b4),
    HOST_OVERLAY_VAR(data_ov088_022727a8),
    HOST_OVERLAY_VAR(data_ov088_022727a4),
    HOST_OVERLAY_VAR(data_ov088_022727a0),
    HOST_OVERLAY_VAR(sSpNpcShrunkTexturePath),
    HOST_OVERLAY_VAR(sSpNpcShrunkModelPath),
    HOST_OVERLAY_VAR(data_ov088_022727b0),
    HOST_OVERLAY_VAR(sSpNpcShrunkProfile),
    HOST_OVERLAY_VAR(data_ov088_022727ac),
    HOST_OVERLAY_VAR(sSpNpcShrunkTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcShrunkActTable),
    HOST_OVERLAY_VAR(sSpNpcShrunkSideStepOffsets),
    HOST_OVERLAY_VARS_END
};
