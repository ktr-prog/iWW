#include "types.h"
#include "gfx/VecFx32.h"
#include "talk/TalkStartMsg.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "actor/Actor.h"
#include "actor/Character.h"
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
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveAnimSet.h"
#include "npc/NpcMoveCtrl.h"
#include "player/PlayerData.h"
#include "talk/ChoiceList.h"
#include "town/PeteFallState.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov075/unk_ov075_022713c0.h"
#include "proto/main/unk_0204cc1c.h"


class SpNpcPete;
class SpNpcPeteTalk;
struct TalkStartMsg;
class Camera;
extern Camera *gCamera;

extern "C" {
BOOL Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
BOOL TalkRequest_SetTargetDone(Character *c);
u8 Math_CountDownU8(u8 *p);
u32 Random_Next(u32 *seed);
s32 func_01ffcb0c(s32 a, s32 b);
s32 TownMap_IsPosWalkable(void *v, s32 a);
extern u16 data_020c6cc8;
extern s32 data_020c6d1c;
extern s32 data_020c6cf0;
extern VecFx32 gCameraLookAt;
extern s16 data_02135f44[];

void SpNpcPete_ChangeAct(SpNpcPete *self, s32 state);
s32 SpNpcPete_IsInFocusBox(SpNpcPete *self, VecFx32 *a, VecFx32 *b);
}

class SpNpcPeteTalk : public SpNpcTalkRequest {
public:
    SpNpcPeteTalk();
    virtual ~SpNpcPeteTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void attachOwner(SpNpcPete *owner);
    void scriptWakeUp();
    void setScript(s32 v);

    /* 0xac */ s32 script;
    /* 0xb0 */ u8 scriptStep;
    /* 0xb4 */ SpNpcPete *ownerNpc;
};




class ActorTalkRequest;




class SpNpcPete : public SpNpcActor {
public:
    SpNpcPete() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual s32 getWalkAnimSpeedScale();

    BOOL mainAct03();
    BOOL mainAct01();
    BOOL mainAct02();
    BOOL setupAct02();
    BOOL setupAct01();
    BOOL mainAct05();
    BOOL tryAvoidObstacle();
    BOOL steerAroundObstacle();
    BOOL findSidestepPos(VecFx32 *out, FxVec3 *offset);
    BOOL pickWanderTarget(s32 *px, s32 *pz);
    s32 isInCameraBox();
    BOOL setupAct05();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct00();
    BOOL setupAct00();

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcPeteTalk talk;
    /* 0x710 */ u32 unk_710;
    /* 0x714 */ u8 isUp;
    /* 0x715 */ u8 moveTimer;
};

struct SpNpcPeteActEntry {
    BOOL (SpNpcPete::*enter)();
    BOOL (SpNpcPete::*exit)();
};

struct SpNpcPeteTalkScript {
    void (SpNpcPeteTalk::*fn)();
    u8 flag;
};


extern "C" {
SpNpcPete *SpNpcPete_Create();
extern u8 sSpNpcPeteModelPath[];
extern u8 sSpNpcPeteTexturePath[];
extern DebugColor data_ov075_0227248c;
extern DebugColor data_ov075_02272494;
extern DebugColor data_ov075_02272490;
extern DebugColor data_ov075_02272484;
extern DebugColor data_ov075_02272488;
extern DebugColor data_ov075_02272480;
extern SpNpcPeteTalkScript sSpNpcPeteTalkScripts[2];
extern u8 data_ov075_022722f8[];
extern SpNpcPeteActEntry sSpNpcPeteActTable[6];
extern FxVec3 sSpNpcPeteSidestepOffsets[2];
extern ActorProfile sSpNpcPeteProfile;
}


u8 sSpNpcPeteTexturePath[] = "npc_sp/model/plb_tex.nsbtx";
ActorProfile sSpNpcPeteProfile = {(void *(*)())SpNpcPete_Create, 0x54, 0x5b, 2, 0x5000, 0x5000, 0x3e800};
DebugColor data_ov075_0227248c(31, 20, 20, 31);
DebugColor data_ov075_02272494(20, 20, 31, 31);
u8 sSpNpcPeteModelPath[] = "npc_sp/model/plb.nsbmd";
DebugColor data_ov075_02272490(31, 31, 20, 31);
DebugColor data_ov075_02272484(20, 31, 20, 31);
DebugColor data_ov075_02272488(20, 31, 31, 31);
DebugColor data_ov075_02272480(20, 24, 24, 31);
SpNpcPeteTalkScript sSpNpcPeteTalkScripts[2] = {
    {NULL, 0},
    {&SpNpcPeteTalk::scriptWakeUp, 1},
};
SpNpcPeteActEntry sSpNpcPeteActTable[6] = {
    {&SpNpcPete::setupAct00, &SpNpcPete::mainAct00},
    {&SpNpcPete::setupAct01, &SpNpcPete::mainAct01},
    {&SpNpcPete::setupAct02, &SpNpcPete::mainAct02},
    {NULL, &SpNpcPete::mainAct03},
    {&SpNpcPete::setupAct04, &SpNpcPete::mainAct04},
    {&SpNpcPete::setupAct05, &SpNpcPete::mainAct05},
};
FxVec3 sSpNpcPeteSidestepOffsets[2] = {FxVec3(0x800, 0, 0x1000), FxVec3(-0x800, 0, 0x1000)};

extern "C" SpNpcPete *SpNpcPete_Create() {
    return new SpNpcPete();
}

BOOL SpNpcPete::preCreate() {
    if (SpNpcActor::preCreate() == 0) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcPete::onCreate() {
    if (SpNpcActor::onCreate() == 0) {
        return FALSE;
    }
    if (TownSessionState_GetPeteFall(TownSessionState_Get())->hasFallPos() != 0) {
        SpNpcPete_ChangeAct(this, 0);
    } else {
        SpNpcPete_ChangeAct(this, 4);
    }
    collider.groups |= 2;
    return TRUE;
}

s32 SpNpcPete::getWalkAnimSpeedScale() { return data_020c6cf0; }

BOOL SpNpcPete::onDelete() {
    if (SpNpcActor::onDelete() == 0) {
        return FALSE;
    }
    if (EventAnnounce_IsBusy() == 0) {
        TownSessionState_GetPeteFall(TownSessionState_Get())->clear();
    }
    return TRUE;
}

u8 *SpNpcPete::getTexturePath() { return sSpNpcPeteTexturePath; }

u8 *SpNpcPete::getModelPath() { return sSpNpcPeteModelPath; }

BOOL SpNpcPete::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcPeteActTable[act].exit != NULL) {
        result = (this->*sSpNpcPeteActTable[act].exit)();
    }
    return result;
}

extern "C" void SpNpcPete_ChangeAct(SpNpcPete *o, s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcPeteActTable[state].enter != NULL) {
        ok = (o->*sSpNpcPeteActTable[state].enter)();
    }
    if (ok) {
        o->act = state;
    }
}

BOOL SpNpcPete::setupAct00() {
    lookAt.setTarget(0, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0xef, 1, data_020c6cc8, 0);
    ((NpcMoveAnimSet *)(&moveAnimSet))->setStandAnim(0xef);
    return TRUE;
}

BOOL SpNpcPete::mainAct00() {
    return TRUE;
}

BOOL SpNpcPete::setupAct04() {
    updateEnabled = 0;
    return TRUE;
}

BOOL SpNpcPete::mainAct04() {
    PeteFallState *r5 = TownSessionState_GetPeteFall(TownSessionState_Get());
    if (r5->hasFallPos() != 0) {
        r5->getPos(&position);
        VecFx32 *s = (VecFx32 *)&position;
        VecFx32 *d = (VecFx32 *)&prevPosition;
        d->x = position.x;
        d->y = s->y;
        d->z = s->z;
        updateEnabled = 1;
        SpNpcPete_ChangeAct(this, 0);
    }
    return TRUE;
}

BOOL SpNpcPete::setupAct05() {
    moveTimer = 0;
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    lookAt.setTarget(1, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

extern "C" s32 SpNpcPete_IsInFocusBox(SpNpcPete *self, VecFx32 *pa, VecFx32 *pb) {
    s32 r = 0;
    BOOL f2 = FALSE;
    BOOL f1 = FALSE;
    s32 ax = pa->x;
    s32 bx = pb->x;
    if (bx > ax - 0x10000 && bx < ax + 0x10000) {
        f1 = TRUE;
    }
    if (f1) {
        s32 bz = pb->z;
        s32 az = pa->z;
        if (bz > az - 0x1a000) {
            f2 = TRUE;
        }
    }
    if (f2) {
        s32 bz = pb->z;
        s32 az = pa->z;
        if (bz < az + 0xa000) {
            r = 1;
        }
    }
    return r;
}

s32 SpNpcPete::isInCameraBox() {
    VecFx32 *p = (VecFx32 *)&position;
    s32 r = 0;
    if (gCamera != NULL) {
        VecFx32 v;
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        r = SpNpcPete_IsInFocusBox(this, &v, p);
    }
    return r;
}

BOOL SpNpcPete::pickWanderTarget(s32 *px, s32 *pz) {
    BOOL r = FALSE;
    VecFx32 v;
    s32 i;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    for (i = 0; i < 6; i++) {
        s32 idx = ((u16)(s16)Random_Next(&gRandom.seed) >> 4) * 2;
        s32 t = func_01ffcb0c(0xc000, data_02135f44[idx]);
        v.x = t + position.x;
        t = func_01ffcb0c(0xc000, data_02135f44[idx + 1]);
        v.z = t + position.z;
        FieldPos_SnapToUnitCenter(&v, &v);
        if (TownMap_IsPosWalkable(&v, r) != 0) {
            *px = v.x;
            *pz = v.z;
            r = TRUE;
            break;
        }
    }
    return r;
}

BOOL SpNpcPete::findSidestepPos(VecFx32 *out, FxVec3 *offset) {
    BOOL r = FALSE;
    VecFx32 t;
    Npc_RotateOffsetXZ(&t, &position, offset, moveAngleY);
    if (Npc_IsPosBlocked(&t) != 1) {
        out->x = t.x;
        out->y = t.y;
        out->z = t.z;
        r = TRUE;
    }
    return r;
}

BOOL SpNpcPete::steerAroundObstacle() {
    void *a = &actionCtrl;
    void *b = &moveCtrl;
    s32 r6 = ((NpcLookAt *)(&obstacleProbe))->getObstacleBits();
    BOOL r = FALSE;
    VecFx32 t;
    if (((NpcMoveCtrl *)(b))->hasArrived((Character *)(this), 1) == 0) {
        switch (r6) {
        case 3:
            ((NpcActionCtrl *)(a))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            r = TRUE;
            break;
        case 1:
            if (findSidestepPos(&t, &sSpNpcPeteSidestepOffsets[1])) {
                ((NpcMoveCtrl *)(b))->setDestination((VecFx32 *)(&t));
            } else {
                ((NpcActionCtrl *)(a))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            r = TRUE;
            break;
        case 2:
            if (findSidestepPos(&t, &sSpNpcPeteSidestepOffsets[0])) {
                ((NpcMoveCtrl *)(b))->setDestination((VecFx32 *)(&t));
            } else {
                ((NpcActionCtrl *)(a))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            r = TRUE;
            break;
        }
    } else {
        if (((NpcMoveCtrl *)(b))->hasNextLeg()) {
            ((NpcMoveCtrl *)(b))->resetDestination();
        }
    }
    return r;
}

BOOL SpNpcPete::tryAvoidObstacle() {
    if (speed != 0) {
        if (steerAroundObstacle()) {
            return TRUE;
        }
    }
    return FALSE;
}


BOOL SpNpcPete::mainAct05() {
    NpcActionCtrl *r4 = &actionCtrl;
    s32 r6 = isInCameraBox();
    Math_CountDownU8(&moveTimer);
    if (r6 != 0) {
        if (tryAvoidObstacle() == 0) {
            if (((NpcActionCtrl *)(r4))->isActionDone() != 0) {
                if (((Unk_0201acf8 *)(&unk_3aa))->getLevel() == 2) {
                    r4->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                } else if ((Random_Next(&gRandom.seed) & 7) == 0) {
                    VecFx32 a;
                    a.x = gVec3Zero.x;
                    a.y = gVec3Zero.y;
                    a.z = gVec3Zero.z;
                    if (pickWanderTarget(&a.x, &a.z) != 0) {
                        r6 = Math_AngleXZ(&position, &a);
                        if (NpcActor_IsFrontAngle((s16)(r6 - rotY)) != 0) {
                            r6 = 1;
                            if (Random_GlobalBelow(4) == 0) {
                                r6 = 2;
                            }
                            ((NpcActionCtrl *)(r4))->requestAction(r6, 1, a.x, a.z, 0, 0, 0, 0, data_020c6cc8, 0);
                            moveTimer = 100;
                        } else {
                            ((NpcActionCtrl *)(r4))->requestAction(4, 1, a.x, a.z, 0, r6, 0, 0, data_020c6cc8, 0);
                            moveTimer = 80;
                        }
                    } else {
                        r4->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                    }
                } else {
                    r4->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                }
            } else {
                if (speed != 0) {
                    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1 || ((NpcActionCtrl *)(&actionCtrl))->getAction() == 2 || ((NpcActionCtrl *)(&actionCtrl))->getAction() == 4) {
                        if (moveTimer == 0) {
                            r4->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                        } else {
                            VecFx32 b;
                            VecFx32 *q = ((NpcMoveCtrl *)(&moveCtrl))->getDestination();
                            b.x = q->x;
                            b.y = q->y;
                            b.z = q->z;
                            if (NpcActor_IsFrontAngle((s16)(Math_AngleXZ(&position, &b) - rotY)) == 0) {
                                r4->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                            }
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

BOOL SpNpcPete::setupAct01() {
    Character *r4 = talk.getTalkPlayer();
    s32 r6 = rotY;
    if (isUp != 0) {
        lookAt.setTarget(1, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
        collider.groups &= ~2;
    }
    if (r4 != NULL) {
        r6 = ((NpcActor *)(this))->getAngleTo((NpcActor *)(r4));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, r6, 0);
    return TRUE;
}

BOOL SpNpcPete::mainAct01() {
    return TRUE;
}

BOOL SpNpcPete::setupAct02() {
    if (isUp == 0) {
        ((NpcTalkCtrl *)(&talkCtrl))->requestTalk(0, 0);
    }
    return TRUE;
}

BOOL SpNpcPete::mainAct02() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        SpNpcPete_ChangeAct(this, 3);
    }
    return TRUE;
}

BOOL SpNpcPete::mainAct03() {
    return TRUE;
}

void SpNpcPeteTalk::update() {
    if (sSpNpcPeteTalkScripts[script].flag != 0) {
        SpNpcPeteTalkScript *e = &sSpNpcPeteTalkScripts[script];
        if (e->fn != 0) {
            (this->*e->fn)();
        }
    }
}

void SpNpcPeteTalk::onTaskDone(u32) {
    if (sSpNpcPeteTalkScripts[script].flag == 0) {
        SpNpcPeteTalkScript *e = &sSpNpcPeteTalkScripts[script];
        if (e->fn != 0) {
            (this->*e->fn)();
            setScript(0);
        }
    }
}

void SpNpcPeteTalk::setScript(s32 v) {
    script = v;
    scriptStep = 0;
}

void SpNpcPeteTalk::scriptWakeUp() {
    switch (scriptStep) {
    case 0:
        if (window->state == 5) {
            ownerNpc->actionCtrl.requestPlayAnim(2, 0xd5, 1, data_020c6cc8, 0);
            ownerNpc->moveAnimSet.setStandAnim(0);
            scriptStep = scriptStep + 1;
        }
        break;
    case 1:
        if (ownerNpc->animCtrl.getAnimId(0) == 0xd5) {
            if (ownerNpc->actionCtrl.isActionDone() != 0) {
                u32 r = ownerNpc->getAngleToPlayer(4);
                ownerNpc->actionCtrl.requestAction(3, 2, 0, 0, 0, r, 0, 0, data_020c6cc8, 0);
                scriptStep = scriptStep + 1;
            }
        }
        break;
    case 2:
        if (ownerNpc->actionCtrl.getAction() == 3) {
            if (ownerNpc->actionCtrl.isActionDone() != 0) {
                void *p = PlayerData_GetCurrent();
                u8 buf[2];
                ownerNpc->isUp = 1;
                ((ActorTalkRequest *)(this))->requestReopenWindow();
                if (((PlayerData *)(p))->testFlag(6) == 0) {
                    ((PlayerData *)(p))->setFlag(6);
                    Talk_CheckAndSetPlayerFlag(0x12, 1);
                    buf[0] = 0x10;
                    window->setNextMessage(buf, (void *)"sp_npc_mpelican");
                } else {
                    Talk_CheckAndSetPlayerFlag(0x12, 1);
                    buf[1] = Random_GlobalBelow(12);
                    window->setNextMessage(&buf[1], (void *)"sp_npc_mpelican");
                }
                setScript(0);
            }
        }
        break;
    }
}

SpNpcPeteTalk::SpNpcPeteTalk() {}

SpNpcPeteTalk::~SpNpcPeteTalk() {}

void SpNpcPeteTalk::attachOwner(SpNpcPete *owner) {
    resetMsg();
    ownerNpc = owner;
}

void SpNpcPeteTalk::start(TalkStartMsg *out) {
    out->msgIndex = 0x1a;
    if (ownerNpc->isUp != 0) {
        if (PlayerData_GetCurrent()->testFlag(6) != 0) {
            out->msgIndex = Random_GlobalBelow(4) + 12;
        }
    }
    out->msgKey = "sp_npc_mpelican";
}

void SpNpcPeteTalk::onMessageEnd(u32) {
    PlayerData_GetCurrent();
    if (msgIndex == 0x1a) {
        ((ActorTalkRequest *)(this))->requestCloseWindow(0);
        setScript(1);
    }
}

void SpNpcPeteTalk::onChoice(u32) {
    s32 r = (getChoiceList())->getResult();
}

BOOL SpNpcPete::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (updateEnabled != 0) {
        if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
            r = TRUE;
        }
    }
    return r;
}

void SpNpcPete::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 0:
        SpNpcPete_ChangeAct(this, 2);
        break;
    case 3:
        talk.resetMsg();
        talk.setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
        if (isUp != 0) {
            SpNpcPete_ChangeAct(this, 1);
        }
        break;
    case 8:
        if (isUp == 0) {
            SpNpcPete_ChangeAct(this, 0);
        } else {
            SpNpcPete_ChangeAct(this, 5);
        }
        break;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov075_022713c0) {
    HOST_OVERLAY_VAR(sSpNpcPeteTexturePath),
    HOST_OVERLAY_VAR(sSpNpcPeteProfile),
    HOST_OVERLAY_VAR(data_ov075_0227248c),
    HOST_OVERLAY_VAR(data_ov075_02272494),
    HOST_OVERLAY_VAR(sSpNpcPeteModelPath),
    HOST_OVERLAY_VAR(data_ov075_02272490),
    HOST_OVERLAY_VAR(data_ov075_02272484),
    HOST_OVERLAY_VAR(data_ov075_02272488),
    HOST_OVERLAY_VAR(data_ov075_02272480),
    HOST_OVERLAY_VAR(sSpNpcPeteTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcPeteActTable),
    HOST_OVERLAY_VAR(sSpNpcPeteSidestepOffsets),
    HOST_OVERLAY_VARS_END
};
