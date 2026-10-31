#include "types.h"
#include "gfx/VecFx32.h"
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
#include "npc/NpcMoveCtrl.h"
#include "save/SaveData.h"
#include "talk/ChoiceList.h"
#include "talk/TalkWindowState.h"
#include "town/VisitorPos.h"
#include "item/PocketMatches.h"
#include "game/TurnipMarket.h"
#include "save/SaveData.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_02098e90.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/ov073/unk_ov073_022713c0.h"
#include "proto/main/unk_0204cc1c.h"


class ActorTalkRequest;

class SpNpcJoan;
class SpNpcJoanTalk;

extern "C" {
extern u16 data_020c6cc8;
extern u32 data_020c6d1c;
extern s32 data_020c6cf0;
extern VecFx32 gCameraLookAt;
extern s16 data_02135f44[];

s32 Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
BOOL TalkRequest_SetTargetDone(Character *c);
u8 Math_CountDownU8(u8 *p);
u32 Random_Next(u32 *seed);
s32 func_01ffcb0c(s32 a, s32 b);
s32 TownMap_IsPosWalkable(void *p, s32 v);
}

class Camera;
extern Camera *gCamera;
extern SaveData gSaveData;





class SpNpcJoanTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcJoanTalk::*Fn)();

    SpNpcJoanTalk();
    virtual ~SpNpcJoanTalk();
    virtual void resetMsg();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);

    void attachOwner(SpNpcJoan *v);
    BOOL giveTurnips();
    void onAmountEntered();
    void setResultHandler(s32 i);

    /* 0xac */ s32 topic;
    /* 0xb0 */ SpNpcJoan *owner;
    /* 0xb4 */ Fn resultHandler;
    /* 0xbc */ s32 price;
    /* 0xc0 */ s32 amount;
    /* 0xc4 */ u8 boughtSeeds;
};








class SpNpcJoan : public SpNpcActor {
public:
    SpNpcJoan() {}
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
    BOOL tryAvoidObstacle();
    BOOL steerAroundObstacle();
    BOOL findSidestepPos(VecFx32 *out, FxVec3 *offset);
    BOOL pickWanderTarget(s32 *a, s32 *b);
    BOOL isInCameraBox();
    BOOL isInFocusBox(VecFx32 *a, VecFx32 *b);
    BOOL setupAct02();
    void changeAct(s32 state);

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcJoanTalk talk;
};

struct SpNpcJoanActEntry {
    BOOL (SpNpcJoan::*enter)();
    BOOL (SpNpcJoan::*exit)();
};


extern "C" {
extern char sSpNpcJoanKey[12];
extern u8 sSpNpcJoanModelPath[23];
extern u8 sSpNpcJoanTexturePath[27];
extern const TalkStartMsg sSpNpcJoanTopicMsgs[3];
s32 SpNpcJoan_IsEmptyItem(u16 *p);
SpNpcJoan *SpNpcJoan_Create();
}
typedef BOOL (SpNpcJoan::*SpNpcJoanActFn)();
extern SpNpcJoanActEntry sSpNpcJoanActTable[5];
extern FxVec3 sSpNpcJoanSidestepOffsets[2];
extern "C" {
extern ActorProfile sSpNpcJoanProfile;
}

extern "C" SpNpcJoan *SpNpcJoan_Create() {
    return new SpNpcJoan();
}

s32 SpNpcJoan::getWalkAnimSpeedScale() { return data_020c6cf0; }

BOOL SpNpcJoan::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcJoan::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    ((VisitorPos *)(TownSessionState_GetVisitorPos(TownSessionState_Get())))->setPos(position.x, position.z);
    return TRUE;
}

BOOL SpNpcJoan::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(3);
    return TRUE;
}

u8 *SpNpcJoan::getTexturePath() { return sSpNpcJoanTexturePath; }

u8 *SpNpcJoan::getModelPath() { return sSpNpcJoanModelPath; }

BOOL SpNpcJoan::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcJoanActTable[act].exit != NULL) {
        result = (this->*sSpNpcJoanActTable[act].exit)();
    }
    return result;
}

void SpNpcJoan::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcJoanActTable[state].enter != NULL) {
        ok = (this->*sSpNpcJoanActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcJoan::setupAct02() {
    actCounter = 0;
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcJoan::isInFocusBox(VecFx32 *a, VecFx32 *b) {
    BOOL r = FALSE, f2 = FALSE, f1 = FALSE;
    s32 ax = a->x;
    s32 bx = b->x;
    if (bx > ax - 0x10000 && bx < ax + 0x10000) {
        f1 = TRUE;
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

BOOL SpNpcJoan::isInCameraBox() {
    VecFx32 *p = (VecFx32 *)&position;
    BOOL r = FALSE;
    if (gCamera != 0) {
        VecFx32 v;
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        r = isInFocusBox(&v, p);
    }
    return r;
}

BOOL SpNpcJoan::pickWanderTarget(s32 *a, s32 *b) {
    BOOL r = FALSE;
    VecFx32 v;
    s32 i;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    for (i = r; i < 6; i++) {
        s32 idx = ((u16)(s16)Random_Next(&gRandom.seed) >> 4) * 2;
        s32 t = func_01ffcb0c(0xc000, data_02135f44[idx]);
        v.x = t + position.x;
        t = func_01ffcb0c(0xc000, data_02135f44[idx + 1]);
        v.z = t + position.z;
        FieldPos_SnapToUnitCenter(&v, &v);
        if (TownMap_IsPosWalkable(&v, 0)) {
            *a = v.x;
            *b = v.z;
            r = TRUE;
            break;
        }
    }
    return r;
}

BOOL SpNpcJoan::findSidestepPos(VecFx32 *out, FxVec3 *offset) {
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

BOOL SpNpcJoan::steerAroundObstacle() {
    VecFx32 v;
    void *q = &actionCtrl;
    void *s = &moveCtrl;
    s32 k = ((NpcLookAt *)(&obstacleProbe))->getObstacleBits();
    BOOL r = FALSE;
    if (((NpcMoveCtrl *)(s))->hasArrived((Character *)(this), 1) == 0) {
        switch (k) {
        case 3:
            ((NpcActionCtrl *)(q))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            r = TRUE;
            break;
        case 1:
            if (findSidestepPos(&v, &sSpNpcJoanSidestepOffsets[1])) {
                ((NpcMoveCtrl *)(s))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(q))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            r = TRUE;
            break;
        case 2:
            if (findSidestepPos(&v, &sSpNpcJoanSidestepOffsets[0])) {
                ((NpcMoveCtrl *)(s))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(q))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            r = TRUE;
            break;
        }
    } else if (((NpcMoveCtrl *)(s))->hasNextLeg()) {
        ((NpcMoveCtrl *)(s))->resetDestination();
    }
    return r;
}

BOOL SpNpcJoan::tryAvoidObstacle() {
    if (speed != 0 && steerAroundObstacle()) {
        return TRUE;
    }
    return FALSE;
}

#define ZERO_CALL(p) (p)->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0)

BOOL SpNpcJoan::mainAct02() {
    VecFx32 va;
    VecFx32 vb;
    NpcActionCtrl *r4 = &actionCtrl;
    BOOL r6 = isInCameraBox();
    Math_CountDownU8(&actCounter);
    if (r6 != 0) {
        if (tryAvoidObstacle() == 0) {
            if (((NpcActionCtrl *)(r4))->isActionDone()) {
                if (((Unk_0201acf8 *)(&unk_3aa))->getLevel() == 2) {
                    ZERO_CALL(r4);
                } else if ((Random_Next(&gRandom.seed) & 7) == 0) {
                    va = gVec3Zero;
                    if (pickWanderTarget(&va.x, &va.z)) {
                        s32 t = Math_AngleXZ(&position, &va);
                        if (NpcActor_IsFrontAngle(t - rotY)) {
                            u32 k = 1;
                            if (Random_GlobalBelow(4) == 0) {
                                k = 2;
                            }
                            if (k != ((NpcActionCtrl *)(&actionCtrl))->getAction()) {
                                ((NpcActionCtrl *)(r4))->requestAction(k, 1, va.x, va.z, 0, 0, 0, 0, data_020c6cc8, 0);
                                actCounter = 100;
                            }
                        } else if (((NpcActionCtrl *)(&actionCtrl))->getAction() != 4) {
                            ((NpcActionCtrl *)(r4))->requestAction(4, 1, va.x, va.z, 0, t, 0, 0, data_020c6cc8, 0);
                            actCounter = 0x50;
                        }
                    } else {
                        ZERO_CALL(r4);
                    }
                } else {
                    ZERO_CALL(r4);
                }
            } else if (speed != 0) {
                if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1 || ((NpcActionCtrl *)(&actionCtrl))->getAction() == 2 || ((NpcActionCtrl *)(&actionCtrl))->getAction() == 4) {
                    if (actCounter == 0) {
                        ZERO_CALL(r4);
                    } else {
                        vb = *((NpcMoveCtrl *)(&moveCtrl))->getDestination();
                        s32 t = Math_AngleXZ(&position, &vb);
                        if (NpcActor_IsFrontAngle(t - rotY) == 0) {
                            ZERO_CALL(r4);
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

BOOL SpNpcJoan::setupAct03() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    actCounter = 0;
    ((NpcFootstepFx *)(&footstepFx))->disableFootsteps();
    return TRUE;
}

BOOL SpNpcJoan::mainAct03() {
    if (isInCameraBox()) {
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcJoan::setupAct00() {
    return TRUE;
}

BOOL SpNpcJoan::mainAct00() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        Hud_Show();
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcJoan::mainAct01() {
    return TRUE;
}

BOOL SpNpcJoan::setupAct04() {
    void *p = talk.getTalkPlayer();
    s32 x = rotY;
    if (p != NULL) {
        x = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcJoan::mainAct04() {
    return TRUE;
}

void SpNpcJoanTalk::onTaskDone(u32) {
    if (resultHandler) {
        (this->*resultHandler)();
        resultHandler = NULL;
    }
}

DebugColor data_ov073_02272584(31, 20, 20, 31);

void SpNpcJoanTalk::setResultHandler(s32 i) {
    static Fn tbl[1] = { &SpNpcJoanTalk::onAmountEntered };
    resultHandler = tbl[i];
}

DebugColor data_ov073_02272598(20, 20, 31, 31);
u8 sSpNpcJoanTexturePath[27] = "npc_sp/model/boa_tex.nsbtx";
char sSpNpcJoanKey[12] = "sp_npc_boar";
u8 sSpNpcJoanModelPath[23] = "npc_sp/model/boa.nsbmd";
DebugColor data_ov073_0227258c(31, 31, 20, 31);
ActorProfile sSpNpcJoanProfile = {(void *(*)())SpNpcJoan_Create, 0x6f, 0x75, 2, 0x5000, 0x5000, 0x3e800};
DebugColor data_ov073_02272594(20, 31, 20, 31);
DebugColor data_ov073_02272580(20, 31, 31, 31);
DebugColor data_ov073_02272588(20, 24, 24, 31);
SpNpcJoanActEntry sSpNpcJoanActTable[5] = {
    {&SpNpcJoan::setupAct00, &SpNpcJoan::mainAct00},
    {NULL, &SpNpcJoan::mainAct01},
    {&SpNpcJoan::setupAct02, &SpNpcJoan::mainAct02},
    {&SpNpcJoan::setupAct03, &SpNpcJoan::mainAct03},
    {&SpNpcJoan::setupAct04, &SpNpcJoan::mainAct04},
};
const TalkStartMsg sSpNpcJoanTopicMsgs[3] = {
    {sSpNpcJoanKey, 0},
    {sSpNpcJoanKey, 4},
    {NULL, 0},
};
FxVec3 sSpNpcJoanSidestepOffsets[2] = {FxVec3(0x800, 0, 0x1000), FxVec3(-0x800, 0, 0x1000)};

void SpNpcJoanTalk::onAmountEntered() {
    void *obj = window;
    u8 buf[2];
    buf[0] = 0x11;
    if (MenuCtrl_IsResultOk()) {
        s32 a = MenuCtrl_GetAmount() * 10;
        amount = MenuCtrl_GetAmount();
        price = a * ((TurnipMarket *)gSaveData.turnipMarket)->getPrice();
        ((ActorTalkRequest *)(this))->setNumberSlot(a, 1, 3, 1, 0);
        ((ActorTalkRequest *)(this))->setNumberSlot(price, 2, 10, 1, 0);
        buf[0] = 0x13;
    }
    ((TalkWindowState *)(obj))->setNextMessage((u8 *)(buf), (void *)(void *)(sSpNpcJoanKey));
}

SpNpcJoanTalk::SpNpcJoanTalk() {}

SpNpcJoanTalk::~SpNpcJoanTalk() {}

void SpNpcJoanTalk::resetMsg() {
    ActorTalkRequest::resetMsg();
    resultHandler = NULL;
}

extern "C" s32 SpNpcJoan_IsEmptyItem(u16 *p) {
    if (*p == 0xfff1) {
        return TRUE;
    }
    return FALSE;
}

BOOL SpNpcJoanTalk::giveTurnips() {
    s32 n = 0;
    s32 t = Pocket_FindEmpty();
    s32 i = 0;
    s32 m;
    PocketMatches buf;
    u16 a, b;
    for (; i < 10; i++) {
        if (amount >= 10) {
            amount = amount - 10;
            n++;
        }
    }
    m = n;
    if (amount != 0) {
        m = n + 1;
    }
    Pocket_CountMatching(&buf, SpNpcJoan_IsEmptyItem);
    if (t < 0 || buf.count < m) {
        return FALSE;
    }
    while (n > 0) {
        a = 0x153a;
        Pocket_AddItem(&a, 0);
        n--;
    }
    if (amount > 0) {
        amount = amount - 1;
        b = amount + 0x1531;
        Pocket_AddItem(&b, 0);
    }
    return TRUE;
}

void SpNpcJoanTalk::attachOwner(SpNpcJoan *v) {
    resetMsg();
    owner = v;
    topic = 0;
    price = 0;
    amount = 0;
    boughtSeeds = 0;
}

void SpNpcJoanTalk::start(TalkStartMsg *p) {
    TalkStartMsg *out = (TalkStartMsg *)p;
    if (topic == 0) {
        if (Talk_CheckAndSetPlayerFlag(3, 1)) {
            topic = 1;
        }
    }
    if (topic >= 0 && topic < 3) {
        out->msgIndex = sSpNpcJoanTopicMsgs[topic].msgIndex;
        out->msgKey = sSpNpcJoanTopicMsgs[topic].msgKey;
    }
}

void SpNpcJoanTalk::onMessageEnd(u32) {
    u8 buf[2];
    s32 cmd;
    const char *str = sSpNpcJoanKey;
    cmd = 0xff;
    switch (msgIndex) {
    case 0x12:
        Hud_Hide();
        setSubSceneKind(0x3a, 0);
        openSubScene(2);
        setResultHandler(0);
        break;
    case 0x15:
        if (boughtSeeds != 0) {
            cmd = 0x1a;
        } else {
            cmd = 0x16;
        }
        break;
    }
    if (cmd != 0xff) {
        buf[0] = cmd;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)(buf), (void *)(void *)(str));
    }
}

void SpNpcJoanTalk::onChoice(u32) {
    u8 buf[2];
    u16 a, b, c;
    s32 res;
    s32 cmd;
    s32 x;
    const char *str;
    res = ((ChoiceList *)(((ActorTalkRequest *)(this))->getChoiceList()))->getResult();
    str = sSpNpcJoanKey;
    cmd = 0xff;
    x = msgIndex;
    if (x > 19) {
        goto hi;
    }
    if (x >= 19) {
        goto b19;
    }
    if (x > 12) {
        goto mid;
    }
    {
        switch ((unsigned char)x) {
        case 0:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 11:
            goto end;
        case 1:
            goto b1;
        case 3:
            goto b3;
        case 8:
            goto b8;
        case 10:
            goto b10;
        case 12:
            goto b12;
        default:
            goto end;
        }
    }
    goto end;
mid:
    if (x == 16) {
        goto b16;
    }
    goto end;
hi:
    switch (x) {
    case 23:
        goto b23;
    case 25:
        goto b25;
    default:
        goto end;
    }
b1:
    if (res == 0) {
        cmd = 6;
    } else {
        cmd = 2;
    }
    goto end;
b3:
    if (res == 0) {
        ((ActorTalkRequest *)(this))->setNumberSlot(((TurnipMarket *)gSaveData.turnipMarket)->getPrice(), 0, 10, 1, 0);
        cmd = 0x10;
    } else if (res == 1) {
        cmd = 0x17;
    }
    goto end;
b8:
    if (res == 0) {
        cmd = 9;
    }
    goto end;
b10:
    if (res == 0) {
        cmd = 0xb;
    }
    goto end;
b12:
    if (res == 0) {
        cmd = 0xd;
    }
    goto end;
b16:
    if (res == 0) {
        cmd = 0x12;
    } else if (res == 1) {
        cmd = 7;
    }
    goto end;
b19:
    if (res == 0) {
        s32 t = Pocket_FindEmpty();
        if (NpcActor_CanPlayerPay(owner, price) == 0) {
            cmd = 0x1b;
        } else if (t < 0) {
            cmd = 0x1c;
        } else if (giveTurnips() == 0) {
            cmd = 0x14;
        } else {
            NpcActor_ChargePlayer(owner, price);
            a = 0x1531;
            ((ActorTalkRequest *)(this))->requestGiveItem(&a, 0, 5, 0);
            boughtSeeds = 0;
            cmd = 0x15;
        }
    }
    goto end;
b23:
    if (res == 0) {
        if (gSaveData.testFlag(4)) {
            cmd = 0x18;
        } else {
            Hud_Hide();
            cmd = 0x19;
        }
    }
    goto end;
b25:
    if (res == 0) {
        if (NpcActor_CanPlayerPay(owner, 0x3e8) == 0) {
            cmd = 0x1b;
        } else {
            b = 0x1567;
            if (Pocket_AddItem(&b, 0)) {
                cmd = 0x15;
                NpcActor_ChargePlayer(owner, 0x3e8);
                gSaveData.setFlag(4);
                boughtSeeds = 1;
                c = 0x1567;
                ((ActorTalkRequest *)(this))->requestGiveItem(&c, 0, 5, 0);
            } else {
                cmd = 0x1c;
            }
        }
    }
    goto end;
end:
    if (cmd != 0xff) {
        buf[0] = cmd;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)(buf), (void *)(void *)(str));
    }
}

BOOL SpNpcJoan::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcJoan::onInteractionEvent(u32 a, u8) {
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

HOST_OVERLAY_VARS(unk_ov073_022713c0) {
    HOST_OVERLAY_VAR(data_ov073_02272584),
    HOST_OVERLAY_VAR(data_ov073_02272598),
    HOST_OVERLAY_VAR(sSpNpcJoanTexturePath),
    HOST_OVERLAY_VAR(sSpNpcJoanKey),
    HOST_OVERLAY_VAR(sSpNpcJoanModelPath),
    HOST_OVERLAY_VAR(data_ov073_0227258c),
    HOST_OVERLAY_VAR(sSpNpcJoanProfile),
    HOST_OVERLAY_VAR(data_ov073_02272594),
    HOST_OVERLAY_VAR(data_ov073_02272580),
    HOST_OVERLAY_VAR(data_ov073_02272588),
    HOST_OVERLAY_VAR(sSpNpcJoanActTable),
    HOST_OVERLAY_VAR(sSpNpcJoanSidestepOffsets),
    HOST_OVERLAY_VARS_END
};
