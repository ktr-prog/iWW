#include "item/ItemName.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "talk/TalkStartMsg.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
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
#include "npc/NpcLookAt.h"
#include "player/PlayerData.h"
#include "save/Pattern.h"
#include "save/PatternOrder.h"
#include "town/VisitorPos.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_02060b9c.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov079/unk_ov079_022713c0.h"
#include "proto/main/unk_0204cc1c.h"


class ActorTalkRequest;
class SpNpcWendell;
class SpNpcWendellTalk;





extern "C" {
BOOL TalkRequest_SetTargetDone(Character *c);
BOOL Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
extern u16 data_020c6cc8;
}






class SpNpcWendellTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcWendellTalk::*Fn)();

    SpNpcWendellTalk();
    virtual ~SpNpcWendellTalk();
    virtual void resetMsg();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);

    void attachOwner(SpNpcWendell *owner);
    void onPatternSlotPicked();
    void resultHandler01();
    void onFoodPicked();
    void setNextResultHandler(s32 idx);
    void setResultHandler(s32 idx);
    void loadResultHandler(Fn *dst, s32 idx);

    SpNpcWendell *ownerNpc;
    Fn resultHandler;
    Fn nextResultHandler;
    u16 foodItem;
    u8 pad_c2[2];
    s32 foodSlot;
};







class SpNpcWendell : public SpNpcActor {
public:
    SpNpcWendell() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 v, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual s32 getWalkAnimSpeedScale();

    BOOL mainAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct02();
    BOOL checkCollisionWhileMoving();
    BOOL handleCollision();
    BOOL getOffsetPosIfFree(VecFx32 *out, FxVec3 *offset);
    BOOL findRandomWalkTarget(s32 *x, s32 *z);
    BOOL isNearCameraTarget();
    BOOL isInViewBox(VecFx32 *a, VecFx32 *b);
    BOOL setupAct02();
    void changeAct(s32 state);

    u8 pad_652[2];
    s32 act;
    SpNpcWendellTalk talk;
};

struct SpNpcWendellActEntry {
    BOOL (SpNpcWendell::*enter)();
    BOOL (SpNpcWendell::*exit)();
};


extern "C" {
extern SpNpcWendellActEntry sSpNpcWendellActTable[5];
extern ActorProfile sSpNpcWendellProfile;
}

extern "C" {
void EventWeekSlots_MarkPlayer(u32 a);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
s32 Item_GetFishWaterClass(u16 *p);
u8 Math_CountDownU8(u8 *p);
u32 Random_Next(u32 *seed);
s32 func_01ffcb0c(s32 a, s32 b);
BOOL TownMap_IsPosWalkable(void *v, s32 a);
extern u32 data_020c6d1c;
extern s32 data_020c6cf0;
extern VecFx32 gCameraLookAt;
extern s16 data_02135f44[];
extern FxVec3 sSpNpcWendellSideStepOffsets[2];
}

class Camera;
extern Camera *gCamera;

struct SpNpcWendellMsgLocal {
    u8 msgIndex;
    u8 pad_01;
    u16 items[16];
};

static inline BOOL Unk_ov079_Rng(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov079_02271718_Chk(SpNpcWendellTalk *o, u16 *slot, u16 val) {
    BOOL r;
    if (Item_IsFurniture(&o->foodItem)) {
        *slot = val;
        if (Item_GetFurnitureIndex(&o->foodItem) == Item_GetFurnitureIndex(slot)) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    } else {
        if (o->foodItem == val) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    }
    return r;
}

SpNpcWendell *SpNpcWendell_Create() {
    return new SpNpcWendell();
}

s32 SpNpcWendell::getWalkAnimSpeedScale() { return data_020c6cf0; }

BOOL SpNpcWendell::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcWendell::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(3);
    return TRUE;
}

BOOL SpNpcWendell::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    if (EventAnnounce_IsBusy() == 0) {
        ((VisitorPos *)(TownSessionState_GetVisitorPos(TownSessionState_Get())))->pickRandomPos();
    }
    return TRUE;
}

u8 *SpNpcWendell::getTexturePath() { return sSpNpcWendellTexturePath; }

u8 *SpNpcWendell::getModelPath() { return sSpNpcWendellModelPath; }

BOOL SpNpcWendell::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcWendellActTable[act].exit != NULL) {
        result = (this->*sSpNpcWendellActTable[act].exit)();
    }
    return result;
}

void SpNpcWendell::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcWendellActTable[state].enter != NULL) {
        ok = (this->*sSpNpcWendellActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcWendell::setupAct02() {
    actCounter = 0;
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcWendell::isInViewBox(VecFx32 *a, VecFx32 *b) {
    BOOL r = FALSE;
    BOOL f2 = FALSE;
    BOOL f1 = FALSE;
    s32 ax = a->x;
    s32 bx = b->x;
    if (bx > ax - 0x10000) {
        if (bx < ax + 0x10000) {
            f1 = TRUE;
        }
    }
    if (f1) {
        if (b->z > a->z - 0x1a000) {
            f2 = TRUE;
        }
    }
    if (f2) {
        if (b->z < a->z + 0xa000) {
            r = TRUE;
        }
    }
    return r;
}

BOOL SpNpcWendell::isNearCameraTarget() {
    VecFx32 *b = (VecFx32 *)&position;
    BOOL r = FALSE;
    VecFx32 v;
    if (gCamera != NULL) {
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        r = isInViewBox(&v, b);
    }
    return r;
}

BOOL SpNpcWendell::findRandomWalkTarget(s32 *px, s32 *pz) {
    VecFx32 v;
    BOOL r = FALSE;
    s32 i;
    v.x = r;
    v.y = r;
    v.z = r;
    for (i = 0; i < 6; i++) {
        s32 idx = ((u16)(s16)Random_Next(&gRandom.seed) >> 4) * 2;
        s32 t = func_01ffcb0c(0xc000, data_02135f44[idx]);
        v.x = t + position.x;
        t = func_01ffcb0c(0xc000, data_02135f44[idx + 1]);
        v.z = t + position.z;
        FieldPos_SnapToUnitCenter(&v, &v);
        if (TownMap_IsPosWalkable(&v, r)) {
            *px = v.x;
            *pz = v.z;
            r = TRUE;
            break;
        }
    }
    return r;
}

BOOL SpNpcWendell::getOffsetPosIfFree(VecFx32 *out, FxVec3 *offset) {
    BOOL r = FALSE;
    VecFx32 v;
    Npc_RotateOffsetXZ(&v, &position, offset, moveAngleY);
    if (Npc_IsPosBlocked(&v) != 1) {
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
        r = TRUE;
    }
    return r;
}

BOOL SpNpcWendell::handleCollision() {
    void *p564 = &actionCtrl;
    void *p350 = &moveCtrl;
    s32 k = ((NpcLookAt *)(&obstacleProbe))->getObstacleBits();
    BOOL r = FALSE;
    VecFx32 v;
    if (!((NpcMoveCtrl *)(p350))->hasArrived((Character *)(this), 1)) {
        switch (k) {
        case 3:
            ((NpcActionCtrl *)(p564))->requestAction(r, 1, r, r, r, r, r, r, data_020c6cc8, r);
            r = TRUE;
            break;
        case 1:
            if (getOffsetPosIfFree(&v, &sSpNpcWendellSideStepOffsets[1])) {
                ((NpcMoveCtrl *)(p350))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(p564))->requestAction(r, 1, r, r, r, r, r, r, data_020c6cc8, r);
            }
            r = TRUE;
            break;
        case 2:
            if (getOffsetPosIfFree(&v, sSpNpcWendellSideStepOffsets)) {
                ((NpcMoveCtrl *)(p350))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(p564))->requestAction(r, 1, r, r, r, r, r, r, data_020c6cc8, r);
            }
            r = TRUE;
            break;
        }
    } else if (((NpcMoveCtrl *)(p350))->hasNextLeg()) {
        ((NpcMoveCtrl *)(p350))->resetDestination();
    }
    return r;
}

BOOL SpNpcWendell::checkCollisionWhileMoving() {
    if (speed != 0) {
        if (handleCollision()) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL SpNpcWendell::mainAct02() {
    void *p = &actionCtrl;
    BOOL a = isNearCameraTarget();
    Math_CountDownU8(&actCounter);
    if (a) {
        if (checkCollisionWhileMoving() == 0) {
            if (((NpcActionCtrl *)(p))->isActionDone()) {
                if (((Unk_0201acf8 *)(&unk_3aa))->getLevel() == 2) {
                    ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                } else if ((Random_Next(&gRandom.seed) & 7) == 0) {
                    VecFx32 v;
                    v.x = gVec3Zero.x;
                    v.y = gVec3Zero.y;
                    v.z = gVec3Zero.z;
                    if (findRandomWalkTarget(&v.x, &v.z)) {
                        s32 t = Math_AngleXZ(&position, &v);
                        if (NpcActor_IsFrontAngle((s16)(t - rotY))) {
                            t = 1;
                            if (Random_GlobalBelow(4) == 0) {
                                t = 2;
                            }
                            if (t != ((NpcActionCtrl *)(&actionCtrl))->getAction()) {
                                ((NpcActionCtrl *)(p))->requestAction(t, 1, v.x, v.z, 0, 0, 0, 0, data_020c6cc8, 0);
                                actCounter = 0x64;
                            }
                        } else if (((NpcActionCtrl *)(&actionCtrl))->getAction() != 4) {
                            ((NpcActionCtrl *)(p))->requestAction(4, 1, v.x, v.z, 0, t, 0, 0, data_020c6cc8, 0);
                            actCounter = 0x50;
                        }
                    } else {
                        ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                    }
                } else {
                    ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                }
            } else if (speed != 0) {
                if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1 || ((NpcActionCtrl *)(&actionCtrl))->getAction() == 2 || ((NpcActionCtrl *)(&actionCtrl))->getAction() == 4) {
                    if (actCounter == 0) {
                        ((NpcActionCtrl *)(p))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                    } else {
                        VecFx32 *q = (VecFx32 *)((NpcMoveCtrl *)(&moveCtrl))->getDestination();
                        VecFx32 w;
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

BOOL SpNpcWendell::setupAct03() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    actCounter = 0;
    ((NpcFootstepFx *)(&footstepFx))->disableFootsteps();
    return TRUE;
}

BOOL SpNpcWendell::mainAct03() {
    if (isNearCameraTarget()) {
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcWendell::setupAct04() {
    void *p = talk.getTalkPlayer();
    s32 x = rotY;
    if (p != NULL) {
        x = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcWendell::mainAct04() { return TRUE; }

BOOL SpNpcWendell::setupAct00() { return TRUE; }

BOOL SpNpcWendell::mainAct00() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcWendell::mainAct01() { return TRUE; }

void SpNpcWendellTalk::onTaskDone(u32) {
    if (resultHandler != NULL) {
        (this->*resultHandler)();
        resultHandler = NULL;
        if (nextResultHandler != NULL) {
            resultHandler = nextResultHandler;
            nextResultHandler = NULL;
        }
    }
}



extern "C" u8 sSpNpcWendellTexturePath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'w', 'r', 'l', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};

extern "C" ActorProfile sSpNpcWendellProfile = {(void *(*)())SpNpcWendell_Create, 0x6b, 0x71, 2, 0x5000, 0x5000, 0x3e800};

extern "C" DebugColor data_ov079_02272b80(31, 20, 20, 31);

extern "C" DebugColor data_ov079_02272b8c(20, 20, 31, 31);

extern "C" DebugColor data_ov079_02272b94(31, 31, 20, 31);

extern "C" DebugColor data_ov079_02272b98(20, 31, 20, 31);

extern "C" DebugColor data_ov079_02272b88(20, 31, 31, 31);

extern "C" DebugColor data_ov079_02272b90(20, 24, 24, 31);

extern "C" SpNpcWendellActEntry sSpNpcWendellActTable[5] = {
    {&SpNpcWendell::setupAct00, &SpNpcWendell::mainAct00},
    {NULL, &SpNpcWendell::mainAct01},
    {&SpNpcWendell::setupAct02, &SpNpcWendell::mainAct02},
    {&SpNpcWendell::setupAct03, &SpNpcWendell::mainAct03},
    {&SpNpcWendell::setupAct04, &SpNpcWendell::mainAct04},
};

extern "C" u8 sSpNpcWendellModelPath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'w', 'r', 'l', '.', 'n', 's', 'b', 'm', 'd', 0};


void SpNpcWendellTalk::loadResultHandler(Fn *dst, s32 idx) {
    static Fn tbl[3] = {&SpNpcWendellTalk::onFoodPicked, &SpNpcWendellTalk::resultHandler01, &SpNpcWendellTalk::onPatternSlotPicked};
    *dst = tbl[idx];
}

extern "C" FxVec3 sSpNpcWendellSideStepOffsets[2] = {FxVec3(0x800, 0, 0x1000), FxVec3(-0x800, 0, 0x1000)};


void SpNpcWendellTalk::setResultHandler(s32 idx) {
    loadResultHandler(&resultHandler, idx);
}

void SpNpcWendellTalk::setNextResultHandler(s32 idx) {
    loadResultHandler(&nextResultHandler, idx);
}

BOOL SpNpcWendell_AcceptAnyItem(u16 *p, s32 x) {
    if (x == 0) {
        return TRUE;
    }
    return FALSE;
}

void SpNpcWendellTalk::onFoodPicked() {
    TalkWindowState *m = window;
    u8 v = 1;
    foodSlot = -1;
    if (MenuCtrl_IsResultOk()) {
        foodSlot = MenuCtrl_GetIndex();
        foodItem = Pocket_GetItem(foodSlot);
        v = 2;
        BOOL f = FALSE;
        u16 c = foodItem;
        if (c >= 0x12e8 && c <= 0x131f) {
            f = TRUE;
        }
        if (f || (c >= 0x1531 && c <= 0x153a) || (c >= 0x1518 && c <= 0x151c) || (c >= 0x1542 && c <= 0x1546) ||
            (c >= 0x1548 && c <= 0x1548) || (c >= 0x153b && c <= 0x1541)) {
            v = 3;
        }
        BOOL g = FALSE;
        c = foodItem;
        if (c >= 0x136a && c <= 0x136a) {
            g = TRUE;
        }
        if (g || (c >= 0x1373 && c <= 0x1373) || (c >= 0x1375 && c <= 0x1375) || (c >= 0x1377 && c <= 0x1377) ||
            (c >= 0x1379 && c <= 0x1379) || (c >= 0x137b && c <= 0x137b)) {
            v = 0xb;
            foodSlot = -1;
        }
        if (foodSlot >= 0) {
            Pocket_RemoveItem(foodSlot);
            foodSlot = -1;
        }
        ((ActorTalkRequest *)(this))->requestTakeItem(&foodItem, 0, 4, 0);
        setNextResultHandler(1);
    } else {
        ((ActorTalkRequest *)(this))->requestReopenWindow();
    }
    m->setNextMessage(&v, (u8 *)"sp_npc_walrus");
}

void SpNpcWendellTalk::resultHandler01() {
    ((ActorTalkRequest *)(this))->requestReopenWindow();
}

void SpNpcWendellTalk::onPatternSlotPicked() {
    TalkWindowState *m = window;
    SpNpcWendellMsgLocal buf;
    u32 r4;
    buf.msgIndex = 0xd;
    if (MenuCtrl_IsResultOk()) {
        void *g = PlayerData_GetCurrent();
        u32 a0 = MenuCtrl_GetIndex();
        u32 r6 = ((PatternOrder *)(((PlayerPatterns *)(((PlayerData *)(g))->getPatterns()))->getPatternOrder()))->getSlot(a0);
        r4 = 0;
        if (Unk_ov079_02271718_Chk(this, &buf.items[4], 0x131f)) {
            r4 = 0x15;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[5], 0x12ff)) {
            r4 = 0x16;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[6], 0x12f6)) {
            r4 = 0x17;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[7], 0x12f8)) {
            r4 = 0x18;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[8], 0x12fc)) {
            r4 = 0x19;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[9], 0x1309)) {
            r4 = 0x1a;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[10], 0x1312)) {
            r4 = 0x1b;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[11], 0x131c) ||
                   Unk_ov079_02271718_Chk(this, &buf.items[12], 0x131d) ||
                   Unk_ov079_02271718_Chk(this, &buf.items[13], 0x131e)) {
            r4 = 0x1d;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[14], 0x1302)) {
            r4 = 0x1e;
        } else if (Unk_ov079_02271718_Chk(this, &buf.items[15], 0x1303)) {
            r4 = 0x1f;
        } else {
            BOOL f = FALSE;
            u32 v = foodItem;
            if (v >= 0x1548 && v <= 0x1548) {
                f = TRUE;
            }
            if (f) {
                r4 = 0xb;
            } else if (v >= 0x1542 && v <= 0x1546) {
                r4 = 8;
            } else if (v >= 0x1531 && v <= 0x153a) {
                r4 = 0xa;
            } else if (Item_GetFishWaterClass(&foodItem) == 0) {
                r4 = (u8)Random_GlobalBelow(8);
            } else if (Item_GetFishWaterClass(&foodItem) == 1) {
                r4 = (u8)(Random_GlobalBelow(9) + 0xc);
            } else if (Item_GetFishWaterClass(&foodItem) == 2) {
                r4 = 0x1c;
            } else if (Unk_ov079_Rng(&foodItem, 0x1518, 0x151c)) {
                r4 = 9;
            }
        }
        PatternSrc_Copy(7, r4, 9, r6, 1);
        buf.msgIndex = 5;
        buf.items[0] = 0x3530;
        ((ActorTalkRequest *)(this))->requestGiveItem(&buf.items[0], 0, 5, 0);
        u32 a, b, c;
        if (r6 < 8) {
            a = (u16)(r6 + 0x12a8);
        } else {
            a = 0x12a8;
        }
        if (r6 < 8) {
            b = (u16)(r6 + 0x1429);
        } else {
            b = 0x1429;
        }
        if (r6 < 8) {
            c = (u16)(r6 + 0x13a0);
        } else {
            c = 0x13a0;
        }
        u32 x = *((PlayerData *)(g))->getShirt();
        u32 y = *((PlayerData *)(g))->getHat();
        u32 z = *((PlayerData *)(g))->getHeldItem();
        if (a == x) {
            if (Unk_ov079_Rng(((PlayerData *)(g))->getShirt(), 0x12a8, 0x12af)) {
                buf.items[1] = a;
                PlayerActor_RequestWearShirtAlt(&buf.items[1]);
            }
        }
        if (b == y) {
            if (Unk_ov079_Rng(((PlayerData *)(g))->getHat(), 0x1429, 0x1430)) {
                buf.items[2] = b;
                PlayerActor_RequestWearHatAlt(&buf.items[2]);
            }
        }
        if (c == z) {
            if (Unk_ov079_Rng(((PlayerData *)(g))->getHeldItem(), 0x13a0, 0x13a7)) {
                buf.items[3] = c;
                PlayerActor_RequestChangeHeldItem(&buf.items[3]);
            }
        }
        void *h = ((PlayerPatterns *)(((PlayerData *)(g))->getPatterns()))->getPattern(r6);
        ItemName title;
        ((Pattern *)h)->getInfo()->getTitle(&title);
        window->setNamedSlot(1, &title, 7);
    }
    m->setNextMessage(&buf.msgIndex, (u8 *)"sp_npc_walrus");
}

SpNpcWendellTalk::SpNpcWendellTalk() {
    foodItem = 0xfff1;
}

SpNpcWendellTalk::~SpNpcWendellTalk() {}

void SpNpcWendellTalk::resetMsg() {
    ActorTalkRequest::resetMsg();
    foodSlot = -1;
    foodItem = 0xfff1;
    resultHandler = NULL;
    nextResultHandler = NULL;
}

void SpNpcWendellTalk::attachOwner(SpNpcWendell *owner) {
    resetMsg();
    ownerNpc = owner;
    foodItem = 0xfff1;
    foodSlot = -1;
}

void SpNpcWendellTalk::start(TalkStartMsg *out) {
    out->msgKey = "sp_npc_walrus";
    if (!Talk_CheckAndSetPlayerFlag(0xa, 0)) {
        out->msgIndex = 0;
    } else {
        out->msgIndex = Random_GlobalBelow(3) + 6;
    }
}

void SpNpcWendellTalk::onMessageStart(u32) {
    if (msgIndex == 0xf) {
        ((ActorTalkRequest *)(this))->requestEatItem();
    }
}

void SpNpcWendellTalk::onMessageEnd(u32) {
    u8 *const str = (u8 *)"sp_npc_walrus";
    u8 r = 0xff;
    u8 v;
    switch (msgIndex) {
    case 3:
        r = 0xf;
        break;
    case 2:
        ((ActorTalkRequest *)(this))->requestKeepItem();
        break;
    case 15:
        r = 4;
        if (Unk_ov079_Rng(&foodItem, 0x153b, 0x1541)) {
            foodItem = 0x13ac;
            if (Random_GlobalBelow(2)) {
                foodItem = 0x3530;
            }
            r = 9;
            ((ActorTalkRequest *)(this))->setItemNameSlot(&foodItem, 0, 7);
        }
        EventWeekSlots_MarkPlayer(0x41);
        break;
    case 14:
        ((ActorTalkRequest *)(this))->setSubSceneKind(0xa, 0);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        setResultHandler(2);
        break;
    case 11:
        ((ActorTalkRequest *)(this))->requestReturnItem();
        break;
    case 9:
        if (Pocket_AddItem(&foodItem, 0)) {
            ((ActorTalkRequest *)(this))->requestGiveItem(&foodItem, 0, 5, 0);
        }
        r = 0xa;
        break;
    case 5:
    case 10:
    case 13:
        Talk_CheckAndSetPlayerFlag(0xa, 1);
        break;
    }
    if (r != 0xff) {
        v = r;
        window->setNextMessage(&v, str);
    }
}

void SpNpcWendellTalk::onChoice(u32) {
    u8 v;
    s32 t = getChoiceList()->getResult();
    u8 *const str = (u8 *)"sp_npc_walrus";
    u8 r = 0xff;
    switch (msgIndex) {
    case 0:
        if (t == 0) {
            ((ActorTalkRequest *)(this))->setPocketFilter(SpNpcWendell_AcceptAnyItem, 0xd, 1);
            ((ActorTalkRequest *)(this))->openSubScene(0);
            setResultHandler(0);
        }
        break;
    case 4:
        if (t == 0) {
            r = 0xe;
        }
        break;
    }
    if (r != 0xff) {
        v = r;
        window->setNextMessage(&v, str);
    }
}

BOOL SpNpcWendell::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcWendell::onInteractionEvent(u32 a, u8) {
    switch (a) {
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

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov079_022713c0) {
    HOST_OVERLAY_VAR(sSpNpcWendellTexturePath),
    HOST_OVERLAY_VAR(sSpNpcWendellProfile),
    HOST_OVERLAY_VAR(data_ov079_02272b80),
    HOST_OVERLAY_VAR(data_ov079_02272b8c),
    HOST_OVERLAY_VAR(data_ov079_02272b94),
    HOST_OVERLAY_VAR(data_ov079_02272b98),
    HOST_OVERLAY_VAR(data_ov079_02272b88),
    HOST_OVERLAY_VAR(data_ov079_02272b90),
    HOST_OVERLAY_VAR(sSpNpcWendellActTable),
    HOST_OVERLAY_VAR(sSpNpcWendellModelPath),
    HOST_OVERLAY_VAR(sSpNpcWendellSideStepOffsets),
    HOST_OVERLAY_VARS_END
};
