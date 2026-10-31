#include "types.h"
#include "gfx/VecFx32.h"
#include "game/Unk_0201acf8.h"
#include "talk/TalkStartMsg.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "gfx/MatTexVramTask.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "player/PlayerData.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "item/ItemName.h"
#include "npc/NpcActionCtrl.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveCtrl.h"
#include "player/PlayerId.h"
#include "save/BlancaFaceRecord.h"
#include "save/Pattern.h"
#include "talk/ChoiceList.h"
#include "talk/TalkWindowState.h"
#include "gfx/Model.h"
#include "save/SaveData.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_0203c638.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov074/unk_ov074_022713c0.h"
#include "proto/main/unk_0204cc1c.h"


class ActorTalkRequest;
class SpNpcBlanca;
class SpNpcBlancaTalk;


class Camera;
extern Camera *gCamera;
extern SaveData gSaveData;

extern "C" {
extern u16 data_020c6cc8;
extern u32 data_020c6d1c;
extern s32 data_020c6cf0;
extern VecFx32 gCameraLookAt;
extern s16 data_02135f44[];

u32 Impression_Evaluate(PlayerData *a, s32 b, s32 c);
BOOL Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
BOOL TalkRequest_SetTargetDone(Character *c);
u8 Math_CountDownU8(u8 *p);
u32 Random_Next(u32 *seed);
s32 func_01ffcb0c(s32 a, s32 b);
BOOL TownMap_IsPosWalkable(void *a, s32 b);
}

static inline BlancaFaceRecord *SpNpcBlanca_FaceRecord() {
    return (BlancaFaceRecord *)gSaveData.blancaFace;
}

class SpNpcBlancaFaceTexture {
public:
    SpNpcBlancaFaceTexture();
    ~SpNpcBlancaFaceTexture();
    void release(Heap *heap);
    void apply(Model *mdl);
    void *getTextureData();
    void init(Heap *heap, Model *mdl);
    void *texBuffer;
    MatTexVramTask texTask;
};

class SpNpcBlancaTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcBlancaTalk::*Fn)();

    SpNpcBlancaTalk();
    virtual ~SpNpcBlancaTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);

    void attachOwner(SpNpcBlanca *o);
    void onConceptChosen();
    void onFaceDrawn();
    void setResultHandler(s32 idx);

    /* 0xac */ SpNpcBlanca *owner;
    /* 0xb0 */ Fn resultHandler;
};







class SpNpcBlanca : public SpNpcActor {
public:
    SpNpcBlanca() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual s32 getWalkAnimSpeedScale();

    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct02();
    BOOL setupAct02();

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcBlancaTalk talk;
    /* 0x710 */ SpNpcBlancaFaceTexture faceTexture;
};

struct SpNpcBlancaActEntry {
    BOOL (SpNpcBlanca::*enter)();
    BOOL (SpNpcBlanca::*exit)();
};


extern "C" {
SpNpcBlanca *SpNpcBlanca_Create();
void SpNpcBlanca_ChangeAct(SpNpcBlanca *self, s32 state);
s32 SpNpcBlanca_IsInCameraBox(SpNpcBlanca *self);
BOOL SpNpcBlanca_TryAvoidObstacle(SpNpcBlanca *self);
s32 SpNpcBlanca_SteerAroundObstacle(SpNpcBlanca *self);
s32 SpNpcBlanca_FindSidestepPos(SpNpcBlanca *self, VecFx32 *out, FxVec3 *offset);
s32 SpNpcBlanca_PickWanderTarget(SpNpcBlanca *self, s32 *a, s32 *b);
s32 SpNpcBlanca_IsInFocusBox(SpNpcBlanca *self, VecFx32 *a, VecFx32 *b);
extern u8 sSpNpcBlancaModelPath[];
extern SpNpcBlancaActEntry sSpNpcBlancaActTable[5];
extern FxVec3 sSpNpcBlancaSidestepOffsets[2];
extern ActorProfile sSpNpcBlancaProfile;
extern DebugColor data_ov074_022726e4;
extern DebugColor data_ov074_022726f4;
extern DebugColor data_ov074_022726e0;
extern DebugColor data_ov074_022726f8;
extern DebugColor data_ov074_022726e8;
extern DebugColor data_ov074_022726f0;
extern char sSpNpcBlancaFaceMaterialName[4];
}

extern "C" SpNpcBlanca *SpNpcBlanca_Create() {
    return new SpNpcBlanca();
}

s32 SpNpcBlanca::getWalkAnimSpeedScale() { return data_020c6cf0; }

BOOL SpNpcBlanca::preCreate() {
    if (SpNpcActor::preCreate() == 0) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcBlanca::onCreate() {
    if (SpNpcActor::onCreate() == 0) {
        return FALSE;
    }
    faceTexture.init(gCurrentHeap, &model);
    SpNpcBlanca_ChangeAct(this, 3);
    return TRUE;
}

BOOL SpNpcBlanca::onDelete() {
    if (SpNpcActor::onDelete() == 0) {
        return FALSE;
    }
    faceTexture.release(gCurrentHeap);
    return TRUE;
}

u8 *SpNpcBlanca::getTexturePath() { return 0; }

u8 *SpNpcBlanca::getModelPath() { return sSpNpcBlancaModelPath; }

BOOL SpNpcBlanca::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcBlancaActTable[act].exit != NULL) {
        result = (this->*sSpNpcBlancaActTable[act].exit)();
    }
    return result;
}

extern "C" void SpNpcBlanca_ChangeAct(SpNpcBlanca *self, s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcBlancaActTable[state].enter != NULL) {
        ok = (self->*sSpNpcBlancaActTable[state].enter)();
    }
    if (ok) {
        self->act = state;
    }
}

BOOL SpNpcBlanca::setupAct02() {
    actCounter = 0;
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    footstepFx.enableFootsteps();
    footstepFx.enableFootsteps();
    lookAt.setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

extern "C" s32 SpNpcBlanca_IsInFocusBox(SpNpcBlanca *self, VecFx32 *pa, VecFx32 *pb) {
    BOOL r = FALSE;
    BOOL f6 = FALSE;
    BOOL f5 = FALSE;
    if (pb->x > pa->x - 0x10000) {
        if (pb->x < pa->x + 0x10000) {
            f5 = TRUE;
        }
    }
    if (f5) {
        if (pb->z > pa->z - 0x1a000) {
            f6 = TRUE;
        }
    }
    if (f6) {
        if (pb->z < pa->z + 0xa000) {
            r = TRUE;
        }
    }
    return r;
}

extern "C" s32 SpNpcBlanca_IsInCameraBox(SpNpcBlanca *self) {
    VecFx32 *pos = &self->position;
    s32 r = 0;
    VecFx32 v;
    if (gCamera != NULL) {
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        r = SpNpcBlanca_IsInFocusBox(self, &v, pos);
    }
    return r;
}

extern "C" s32 SpNpcBlanca_PickWanderTarget(SpNpcBlanca *self, s32 *a, s32 *b) {
    s32 r6 = 0;
    s32 i;
    VecFx32 v;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    for (i = 0; i < 6; i++) {
        s16 ang = Random_Next(&gRandom.seed);
        s32 idx = ((u16)ang >> 4) * 2;
        s32 t = func_01ffcb0c(0xc000, data_02135f44[idx]);
        v.x = t + self->position.x;
        t = func_01ffcb0c(0xc000, data_02135f44[idx + 1]);
        v.z = t + self->position.z;
        FieldPos_SnapToUnitCenter(&v, &v);
        if (TownMap_IsPosWalkable(&v, r6) != 0) {
            *a = v.x;
            *b = v.z;
            r6 = 1;
            break;
        }
    }
    return r6;
}

extern "C" s32 SpNpcBlanca_FindSidestepPos(SpNpcBlanca *self, VecFx32 *o, FxVec3 *offset) {
    VecFx32 t;
    s32 r = 0;
    Npc_RotateOffsetXZ(&t, &self->position, offset, self->moveAngleY);
    if (Npc_IsPosBlocked(&t) != 1) {
        o->x = t.x;
        o->y = t.y;
        o->z = t.z;
        r = 1;
    }
    return r;
}

extern "C" s32 SpNpcBlanca_SteerAroundObstacle(SpNpcBlanca *self) {
    NpcActionCtrl *r1c = &self->actionCtrl;
    NpcMoveCtrl *r4 = &self->moveCtrl;
    s32 r6 = ((NpcLookAt *)(&self->obstacleProbe))->getObstacleBits();
    s32 r7 = 0;
    VecFx32 v;

    if (((NpcMoveCtrl *)(r4))->hasArrived((Character *)(self), 1) == 0) {
        switch (r6) {
        case 3:
            ((NpcActionCtrl *)(r1c))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            r7 = 1;
            break;
        case 1:
            if (SpNpcBlanca_FindSidestepPos(self, &v, &sSpNpcBlancaSidestepOffsets[1]) != 0) {
                ((NpcMoveCtrl *)(r4))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(r1c))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            r7 = 1;
            break;
        case 2:
            if (SpNpcBlanca_FindSidestepPos(self, &v, sSpNpcBlancaSidestepOffsets) != 0) {
                ((NpcMoveCtrl *)(r4))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(r1c))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            r7 = 1;
            break;
        }
    } else {
        if (((NpcMoveCtrl *)(r4))->hasNextLeg() != 0) {
            ((NpcMoveCtrl *)(r4))->resetDestination();
        }
    }
    return r7;
}

extern "C" BOOL SpNpcBlanca_TryAvoidObstacle(SpNpcBlanca *self) {
    if (self->speed != 0 && SpNpcBlanca_SteerAroundObstacle(self) != 0) {
        return TRUE;
    }
    return FALSE;
}

BOOL SpNpcBlanca::mainAct02() {
    s32 r6;
    VecFx32 v;
    VecFx32 w;
    NpcActionCtrl *r4 = &actionCtrl;

    r6 = SpNpcBlanca_IsInCameraBox(this);
    Math_CountDownU8(&actCounter);
    if (r6 != 0) {
        if (SpNpcBlanca_TryAvoidObstacle(this) == 0) {
            if (((NpcActionCtrl *)(r4))->isActionDone() != 0) {
                if (((Unk_0201acf8 *)&unk_3aa)->getLevel() == 2) {
                    ((NpcActionCtrl *)(r4))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                } else if ((Random_Next(&gRandom.seed) & 7) == 0) {
                    v.x = gVec3Zero.x;
                    v.y = gVec3Zero.y;
                    v.z = gVec3Zero.z;
                    if (SpNpcBlanca_PickWanderTarget(this, &v.x, &v.z) != 0) {
                        r6 = Math_AngleXZ(&position, &v);
                        if (NpcActor_IsFrontAngle(r6 - rotY) != 0) {
                            r6 = 1;
                            if (Random_GlobalBelow(4) == 0) {
                                r6 = 2;
                            }
                            if (r6 != actionCtrl.getAction()) {
                                ((NpcActionCtrl *)(r4))->requestAction(r6, 1, v.x, v.z, 0, 0, 0, 0, data_020c6cc8, 0);
                                actCounter = 0x64;
                            }
                        } else {
                            if (actionCtrl.getAction() != 4) {
                                ((NpcActionCtrl *)(r4))->requestAction(4, 1, v.x, v.z, 0, r6, 0, 0, data_020c6cc8, 0);
                                actCounter = 0x50;
                            }
                        }
                    } else {
                        ((NpcActionCtrl *)(r4))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                    }
                } else {
                    ((NpcActionCtrl *)(r4))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                }
            } else {
                if (speed != 0) {
                    if (actionCtrl.getAction() == 1 || actionCtrl.getAction() == 2 || actionCtrl.getAction() == 4) {
                        if (actCounter == 0) {
                            ((NpcActionCtrl *)(r4))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                        } else {
                            VecFx32 *src = moveCtrl.getDestination();
                            w.x = src->x;
                            w.y = src->y;
                            w.z = src->z;
                            if (NpcActor_IsFrontAngle(Math_AngleXZ(&position, &w) - rotY) == 0) {
                                ((NpcActionCtrl *)(r4))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (speed != 0) {
            SpNpcBlanca_ChangeAct(this, 3);
        }
    }
    return FALSE;
}

BOOL SpNpcBlanca::setupAct03() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    actCounter = 0;
    footstepFx.disableFootsteps();
    return TRUE;
}

BOOL SpNpcBlanca::mainAct03() {
    if (SpNpcBlanca_IsInCameraBox(this) != 0) {
        SpNpcBlanca_ChangeAct(this, 2);
    }
    return TRUE;
}

BOOL SpNpcBlanca::setupAct00() { return TRUE; }

BOOL SpNpcBlanca::mainAct00() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        SpNpcBlanca_ChangeAct(this, 1);
    }
    return TRUE;
}

BOOL SpNpcBlanca::mainAct01() { return TRUE; }

BOOL SpNpcBlanca::setupAct04() {
    Character *a = talk.getTalkPlayer();
    s32 b = rotY;
    if (a != NULL) {
        b = ((NpcActor *)(this))->getAngleTo((NpcActor *)(a));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, b, 0);
    return TRUE;
}

BOOL SpNpcBlanca::mainAct04() { return TRUE; }

void SpNpcBlancaTalk::onTaskDone(u32) {
    if (resultHandler != 0) {
        (this->*resultHandler)();
        resultHandler = NULL;
    }
}

extern u8 sSpNpcBlancaModelPath[];
extern ActorProfile sSpNpcBlancaProfile;
extern SpNpcBlancaActEntry sSpNpcBlancaActTable[5];
extern FxVec3 sSpNpcBlancaSidestepOffsets[2];


















DebugColor data_ov074_022726e4(31, 20, 20, 31);
DebugColor data_ov074_022726f4(20, 20, 31, 31);
DebugColor data_ov074_022726e0(31, 31, 20, 31);
DebugColor data_ov074_022726f8(20, 31, 20, 31);
ActorProfile sSpNpcBlancaProfile = {(void *(*)())SpNpcBlanca_Create, 0x67, 0x6d, 2, 0x5000, 0x5000, 0x3e800};
DebugColor data_ov074_022726e8(20, 31, 31, 31);
DebugColor data_ov074_022726f0(20, 24, 24, 31);
char sSpNpcBlancaFaceMaterialName[4] = "f";
u8 sSpNpcBlancaModelPath[] = "npc_sp/model/mka.nsbmd";
SpNpcBlancaActEntry sSpNpcBlancaActTable[5] = {
    {&SpNpcBlanca::setupAct00, &SpNpcBlanca::mainAct00},
    {NULL, &SpNpcBlanca::mainAct01},
    {&SpNpcBlanca::setupAct02, &SpNpcBlanca::mainAct02},
    {&SpNpcBlanca::setupAct03, &SpNpcBlanca::mainAct03},
    {&SpNpcBlanca::setupAct04, &SpNpcBlanca::mainAct04},
};
FxVec3 sSpNpcBlancaSidestepOffsets[2] = {FxVec3(0x800, 0, 0x1000), FxVec3(-0x800, 0, 0x1000)};

void SpNpcBlancaTalk::setResultHandler(s32 idx) {
    static Fn tbl[2] = {&SpNpcBlancaTalk::onFaceDrawn, &SpNpcBlancaTalk::onConceptChosen};
    resultHandler = tbl[idx];
}

void SpNpcBlancaTalk::onFaceDrawn() {
    void *p = window;
    u8 buf[1];
    buf[0] = 0xf;
    if (MenuCtrl_IsResultOk() != 0) {
        buf[0] = 0x1c;
        owner->faceTexture.apply(&owner->model);
    }
    ((TalkWindowState *)(p))->setNextMessage(buf, (void *)(((char *)"sp_npc_mysterycat")));
}

void SpNpcBlancaTalk::onConceptChosen() {
    if (MenuCtrl_IsResultOk() != 0) {
        void *p = window;
        BlancaFaceRecord *const g = SpNpcBlanca_FaceRecord();
        u8 buf[1];
        g->setConcept(Impression_Evaluate(PlayerData_GetCurrent(), 0, 0));
        g->setState(3);
        buf[0] = Random_GlobalBelow(3) + 5;
        Talk_CheckAndSetPlayerFlag(0x2b, 1);
        ((TalkWindowState *)(p))->setNextMessage(buf, (void *)(((char *)"sp_npc_mysterycat")));
    }
end:;
}

SpNpcBlancaTalk::SpNpcBlancaTalk() {}

SpNpcBlancaTalk::~SpNpcBlancaTalk() {}

void SpNpcBlancaTalk::attachOwner(SpNpcBlanca *o) {
    resetMsg();
    owner = o;
}

void SpNpcBlancaTalk::start(TalkStartMsg *out) {
    u8 buf[1];
    ItemName title;

    out->msgKey = "sp_npc_mysterycat";
    BlancaFaceRecord *const g = SpNpcBlanca_FaceRecord();
    PatternInfo *info = ((Pattern *)g->getPattern())->getInfo();
    PlayerId *author = (PlayerId *)info->getAuthor();
    if (Random_GlobalBelow(2) == 0 || Talk_CheckAndSetPlayerFlag(0x2b, 0) == 0) {
        out->msgIndex = 3;
    } else {
        if (author->isValid() != 0) {
            PlayerData *p = PlayerData_GetCurrent();
            PlayerId *q = p->getPlayerId();
            if (author->townId == q->townId && memcmp(author->townName, q->townName, 8) == 0 && author->equals(q) != 0) {
                out->msgIndex = Random_GlobalBelow(4) + 0x18;
                goto next;
            }
        }
        out->msgIndex = Random_GlobalBelow(4) + 0x11;
    }
next:
    if (author->isValid() != 0) {
        setPlayerNameSlot(author, 1);
        setTownNameSlot(PlayerId_GetTownId(author), 0);
        buf[0] = g->getConcept();
        ((TalkWindowState *)(window))->setSlotFromString(2, buf, "st_impress");
        info->getTitle(&title);
        ((TalkWindowState *)(window))->setSlot(3, &title);
    }
}

void SpNpcBlancaTalk::onMessageEnd(u32) {
    u8 buf[1];
    char *name = ((char *)"sp_npc_mysterycat");
    s32 t = 0xff;

    switch (msgIndex) {
    case 9:
    case 10:
    case 11:
    case 12:
        t = 0xd;
        break;
    case 13:
        break;
    case 14:
        owner->faceTexture.apply(&owner->model);
        setSubSceneKind(3, 0);
        openSubScene(2);
        setResultHandler(0);
        break;
    case 0x1c:
        setSubSceneKind(0x14, 0);
        openSubScene(2);
        setResultHandler(1);
        break;
    }
    if (t != 0xff) {
        buf[0] = t;
        ((TalkWindowState *)(window))->setNextMessage(buf, (void *)(name));
    }
}

void SpNpcBlancaTalk::onChoice(u32) {
    u8 buf[1];
    s32 t;
    s32 r5;

    r5 = ((ChoiceList *)(getChoiceList()))->getResult();
    PatternInfo *info = ((Pattern *)SpNpcBlanca_FaceRecord()->getPattern())->getInfo();
    PlayerId *author = (PlayerId *)info->getAuthor();
    char *name = ((char *)"sp_npc_mysterycat");
    t = 0xff;
    switch (msgIndex) {
    case 3:
        if (r5 == 0) {
            if (author->isValid() != 0) {
                PlayerData *p = PlayerData_GetCurrent();
                PlayerId *q = p->getPlayerId();
                if (author->townId == q->townId && memcmp(author->townName, q->townName, 8) == 0 && author->equals(q) != 0) {
                    t = 0xa;
                    break;
                }
            }
            t = 9;
        } else {
            if (author->isValid() != 0) {
                PlayerData *p = PlayerData_GetCurrent();
                PlayerId *q = p->getPlayerId();
                if (author->townId == q->townId && memcmp(author->townName, q->townName, 8) == 0 && author->equals(q) != 0) {
                    t = 0xc;
                    break;
                }
            }
            t = 0xb;
        }
        break;
    case 0xd:
        if (r5 != 0) {
            t = 0xe;
        }
        break;
    }
    if (t != 0xff) {
        buf[0] = t;
        ((TalkWindowState *)(window))->setNextMessage(buf, (void *)(name));
    }
}

BOOL SpNpcBlanca::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcBlanca::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 0:
        SpNpcBlanca_ChangeAct(this, 0);
        break;
    case 3:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        SpNpcBlanca_ChangeAct(this, 4);
        break;
    case 8:
        SpNpcBlanca_ChangeAct(this, 2);
        break;
    }
}

SpNpcBlancaFaceTexture::SpNpcBlancaFaceTexture() {}

SpNpcBlancaFaceTexture::~SpNpcBlancaFaceTexture() {}

void SpNpcBlancaFaceTexture::init(Heap *heap, Model *mdl) {
    texBuffer = Heap_Alloc(heap, ClothTex_GetBufferSize());
    apply(mdl);
}

void *SpNpcBlancaFaceTexture::getTextureData() {
    void *r = NULL;
    if (texBuffer != NULL) {
        r = ClothTex_GetTexThunk(texBuffer);
    }
    return r;
}

void SpNpcBlancaFaceTexture::apply(Model *ent) {
    void *t;
    void *h;
    t = SpNpcBlanca_FaceRecord()->getPattern();
    if (t != NULL) {
        if (ClothTex_LoadPatternThunk(texBuffer, t) != 0) {
            h = getTextureData();
            if (h != NULL) {
                texTask.request(ent->resMdl, sSpNpcBlancaFaceMaterialName, h, 0, 0);
            }
        }
    }
}

void SpNpcBlancaFaceTexture::release(Heap *heap) {
    texTask.cancel();
    if (texBuffer != NULL) {
        Heap_Free(heap, texBuffer);
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov074_022713c0) {
    HOST_OVERLAY_VAR(data_ov074_022726e4),
    HOST_OVERLAY_VAR(data_ov074_022726f4),
    HOST_OVERLAY_VAR(data_ov074_022726e0),
    HOST_OVERLAY_VAR(data_ov074_022726f8),
    HOST_OVERLAY_VAR(sSpNpcBlancaProfile),
    HOST_OVERLAY_VAR(data_ov074_022726e8),
    HOST_OVERLAY_VAR(data_ov074_022726f0),
    HOST_OVERLAY_VAR(sSpNpcBlancaFaceMaterialName),
    HOST_OVERLAY_VAR(sSpNpcBlancaModelPath),
    HOST_OVERLAY_VAR(sSpNpcBlancaActTable),
    HOST_OVERLAY_VAR(sSpNpcBlancaSidestepOffsets),
    HOST_OVERLAY_VARS_END
};
