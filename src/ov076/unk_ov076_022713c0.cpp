#include "types.h"
#include "gfx/VecFx32.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
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
#include "item/ItemPickSpec.h"
#include "actor/ActorProfile.h"
#include "npc/NpcLookAt.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/ov076/unk_ov076_022713c0.h"


class ActorTalkRequest;
class SpNpcPascal;
class SpNpcPascalTalk;


struct SpNpcPascalMsgLocal {
    u8 msgIndex;
    u8 pad_01;
    u16 item;
};

static inline u32 SpNpcPascal_FrameInt(s32 frame) {
    return ((u32)frame >> 12) & 0xffff;
}


extern "C" {
BOOL Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
BOOL Item_IsFurniture(u16 *);
s32 Item_GetFurnitureIndex(u16 *);
void EventWeekSlots_MarkPlayer(u32 id);
BOOL TalkRequest_SetTargetDone(Character *c);
BOOL Math_StepAngle(s16 *p, s16 target, s16 step);
extern u16 data_020c6cc8;
extern u32 data_020c6d1c;
}






class SpNpcPascalTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcPascalTalk::*Fn)();

    SpNpcPascalTalk();
    virtual ~SpNpcPascalTalk();
    virtual void resetMsg();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);

    void attachOwner(SpNpcPascal *o);
    void onScallopPicked();
    void setResultHandler(s32 i);

    s32 topic;
    SpNpcPascal *owner;
    u16 giftItem;
    Fn resultHandler;
};








class SpNpcPascal : public SpNpcActor {
public:
    SpNpcPascal() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 v, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct00();
    BOOL setupAct00();
    BOOL mainAct05();
    BOOL setupAct05();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct02();
    BOOL mainAct01();
    BOOL setupAct01();
    void changeAct(s32 state);

    u8 pad_652[2];
    s32 act;
    SpNpcPascalTalk talk;
    u8 giftGiven;
    u8 pad_719;
    u16 homeAngle;
    s32 diveStartZ;
    s16 spinSpeed;
    u8 pad_722[2];
};

struct SpNpcPascalActEntry {
    BOOL (SpNpcPascal::*enter)();
    BOOL (SpNpcPascal::*exit)();
};



static inline BOOL Unk_ov076_IsItem(u16 *p, u16 k) {
    BOOL ok;
    if (Item_IsFurniture(p)) {
        u16 v = k;
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&v)) {
            ok = TRUE;
        } else {
            ok = FALSE;
        }
    } else {
        if (*p == k) {
            ok = TRUE;
        } else {
            ok = FALSE;
        }
    }
    return ok;
}

extern "C" {
extern const TalkStartMsg sSpNpcPascalTopicMsgs[3];
}


SpNpcPascal *SpNpcPascal_Create() {
    return new SpNpcPascal();
}

BOOL SpNpcPascal::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcPascal::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    collider.groups |= 2;
    homeAngle = rotY;
    changeAct(0);
    return TRUE;
}

u8 *SpNpcPascal::getTexturePath() { return sSpNpcPascalTexturePath; }

u8 *SpNpcPascal::getModelPath() { return sSpNpcPascalModelPath; }

BOOL SpNpcPascal::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcPascalActTable[act].exit != NULL) {
        result = (this->*sSpNpcPascalActTable[act].exit)();
    }
    return result;
}

void SpNpcPascal::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcPascalActTable[state].enter != NULL) {
        ok = (this->*sSpNpcPascalActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcPascal::setupAct00() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcPascal::mainAct00() { return TRUE; }

BOOL SpNpcPascal::setupAct01() {
    void *p = talk.getTalkPlayer();
    u32 r = 0;
    if (p != NULL) {
        r = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, r, 0);
    return TRUE;
}

BOOL SpNpcPascal::mainAct01() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcPascal::mainAct02() { return TRUE; }

BOOL SpNpcPascal::setupAct03() {
    if (giftGiven == 1) {
        homeAngle = homeAngle + 0x8000;
    }
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, (s16)homeAngle, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcPascal::mainAct03() {
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            if (giftGiven == 0) {
                changeAct(0);
            } else {
                changeAct(4);
            }
        }
    }
    return TRUE;
}

BOOL SpNpcPascal::setupAct04() {
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0xf9, 1, 0, 0);
    Snd_SeEmitterPlayOneShotAlt(&seEmitter, 0x814, 0x7f, 0);
    rotY = rotY + 0x8000;
    moveAngleY = rotY;
    ((NpcMoveCtrl *)(&moveCtrl))->setTargetAngle(rotY);
    s32 t = -(rotY / 6);
    if (t < 0) {
        t = -t;
    }
    spinSpeed = t;
    lookAt.setTarget(0, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
    diveStartZ = position.z;
    return TRUE;
}

BOOL SpNpcPascal::mainAct04() {
    VecFx32 v;
    if (((NpcAnimCtrl *)(&animCtrl))->getAnimId(0) == 0xf9 &&
        ((NpcAnimCtrl *)(&animCtrl))->isAnimFinished((NpcActor *)(this))) {
        changeAct(5);
    } else {
        if (((NpcAnimCtrl *)(&animCtrl))->getAnimId(0) == 0xf9 && SpNpcPascal_FrameInt(model.curFrame) == 0xb) {
            shadowEnabled = 0;
            collisionEnabled = 0;
        }
        Math_StepAngle(&rotY, 0, spinSpeed);
        if (SpNpcPascal_FrameInt(model.curFrame) == 0x1b) {
            VecFx32 *pv = (VecFx32 *)&position;
            v.x = pv->x;
            v.y = pv->y;
            v.z = pv->z;
            v.y = 0;
            v.z = v.z + 0x3800;
            FieldFish_ScareAround(&v, 0x5000);
            Effect_Create(0x16, &v, 0, 0);
            Snd_SeEmitterPlayOneShotAlt(&seEmitter, 0x7ed, 0x7f, 0);
        }
    }
    moveAngleY = rotY;
    ((NpcMoveCtrl *)(&moveCtrl))->setTargetAngle(rotY);
    return TRUE;
}

BOOL SpNpcPascal::setupAct05() {
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0xfa, 0, 0, 0);
    ((NpcLookAt *)(&lookAt))->disable();
    rotY = 0;
    moveAngleY = 0;
    ((NpcMoveCtrl *)(&moveCtrl))->setTargetAngle(0);
    position.z += 0x4000;
    return TRUE;
}

BOOL SpNpcPascal::mainAct05() {
    moveAngleY = 0;
    rotY = 0;
    ((NpcMoveCtrl *)(&moveCtrl))->setTargetAngle(0);
    position.z += 0xeb;
    if (position.z > diveStartZ + 0x14000) {
        ProcBase_RequestDelete(this);
    }
    return TRUE;
}

void SpNpcPascalTalk::onTaskDone(u32) {
    if (resultHandler) {
        (this->*resultHandler)();
        resultHandler = NULL;
    }
}

void SpNpcPascalTalk::setResultHandler(s32 i) {
    static Fn tbl[1] = {&SpNpcPascalTalk::onScallopPicked};
    resultHandler = tbl[i];
}

extern "C" BOOL SpNpcPascal_IsScallop(u16 *p, s32 x) {
    if (x == 0) {
        return Unk_ov076_IsItem(p, 0x1559);
    }
    return FALSE;
}

void SpNpcPascalTalk::onScallopPicked() {
    TalkWindowState *r4 = window;
    SpNpcPascalMsgLocal m;
    m.msgIndex = 5;
    if (MenuCtrl_IsResultOk()) {
        s32 i = MenuCtrl_GetIndex();
        if (i >= 0) {
            Pocket_RemoveItem(i);
        }
        m.item = 0x1559;
        ((ActorTalkRequest *)(this))->requestTakeItem(&m.item, 0, 5, 0);
        m.msgIndex = 6;
    }
    r4->setNextMessage(&m.msgIndex, sSpNpcPascalKey);
}

SpNpcPascalTalk::SpNpcPascalTalk() {
    giftItem = 0xfff1;
}

SpNpcPascalTalk::~SpNpcPascalTalk() {}

void SpNpcPascalTalk::resetMsg() {
    ActorTalkRequest::resetMsg();
    resultHandler = NULL;
}

void SpNpcPascalTalk::attachOwner(SpNpcPascal *o) {
    resetMsg();
    owner = o;
    owner->giftGiven = 0;
    topic = 0;
}

void SpNpcPascalTalk::start(TalkStartMsg *a) {
    TalkStartMsg *out = (TalkStartMsg *)a;
    if (MenuCtrl_BuildPocketMask(SpNpcPascal_IsScallop)) {
        topic = 0;
    } else if (Random_GlobalBelow(2) == 0) {
        topic = 1;
    } else {
        topic = 2;
    }
    if (topic >= 0 && topic < 3) {
        out->msgIndex = sSpNpcPascalTopicMsgs[topic].msgIndex;
        out->msgKey = sSpNpcPascalTopicMsgs[topic].msgKey;
    }
}

void SpNpcPascalTalk::onMessageEnd(u32) {
    u8 *tag = sSpNpcPascalKey;
    u8 code = 0xff;
    u8 msg;
    u16 oa, ob, oc, v;
    s32 t0 = msgIndex;
    if (t0 == 0xfe || (t0 >= 0xf && t0 <= 0xfd)) {
        code = (u8)(Random_GlobalBelow(2) + 0xd);
    }
    switch (msgIndex) {
    case 4:
        ((ActorTalkRequest *)(this))->setPocketFilter(SpNpcPascal_IsScallop, 0xd, 0);
        ((ActorTalkRequest *)(this))->openSubScene(0);
        setResultHandler(0);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    case 10:
    case 11:
        if (msgIndex == 10) {
            giftItem = 0x4a38;
        } else {
            giftItem = 0x1373;
        }
        ((ActorTalkRequest *)(this))->requestGiveItem(&giftItem, 0, 5, 0);
        Pocket_AddItem(&giftItem, 0);
        owner->giftGiven = 1;
        Talk_CheckAndSetPlayerFlag(0x18, 1);
        code = 0xc;
        break;
    case 12:
        BOOL ok;
        if (Item_IsFurniture(&giftItem)) {
            v = 0x4a38;
            if (Item_GetFurnitureIndex(&giftItem) == Item_GetFurnitureIndex(&v)) {
                ok = TRUE;
            } else {
                ok = FALSE;
            }
        } else {
            if (giftItem == 0x4a38) {
                ok = TRUE;
            } else {
                ok = FALSE;
            }
        }
        if (ok) {
            code = 0x33;
        } else {
            code = 0xfd;
        }
        break;
    case 13:
    case 14:
        if (owner->giftGiven == 0) {
            if (Pocket_FindEmpty() >= 0) {
                s32 t = Random_GlobalBelow(9);
                if (t <= 6) {
                    ItemPickSpec o0;
                    o0.set(0, 0x15);
                    ItemPick_One(&oa, &o0, 0, 0, 1, 1, 0);
                    giftItem = oa;
                } else if (t == 7) {
                    ItemPickSpec o1;
                    o1.set(4, 0x15);
                    ItemPick_One(&ob, &o1, 0, 0, 1, 1, 0);
                    giftItem = ob;
                } else {
                    ItemPickSpec o2;
                    o2.set(3, 0x15);
                    ItemPick_One(&oc, &o2, 0, 0, 1, 1, 0);
                    giftItem = oc;
                }
                ((ActorTalkRequest *)(this))->requestGiveItem(&giftItem, 0, 5, 0);
                Pocket_AddItem(&giftItem, 0);
                Talk_CheckAndSetPlayerFlag(0x18, 1);
            }
            owner->giftGiven = 1;
        }
        EventWeekSlots_MarkPlayer(0x42);
        break;
    }
    if (code != 0xff) {
        msg = code;
        window->setNextMessage(&msg, tag);
    }
}

void SpNpcPascalTalk::onChoice(u32) {
    s32 mode = getChoiceList()->getResult();
    u8 *tag = sSpNpcPascalKey;
    u8 code = 0xff;
    switch (msgIndex) {
    case 0:
    case 1:
        if (mode == 0) {
            code = (u8)(Random_GlobalBelow(0xef) + 0xf);
        } else {
            code = 5;
        }
        break;
    case 2:
        if (mode == 2) {
            code = 4;
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    case 8:
        if (mode == 0) {
            code = 0xb;
        } else if (mode == 1) {
            code = 9;
        } else {
            code = 0xa;
        }
        break;
    }
    if (code != 0xff) {
        u8 b = code;
        window->setNextMessage(&b, tag);
    }
}

BOOL SpNpcPascal::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (Talk_CheckAndSetPlayerFlag(0x18, r) == 1) {
        return r;
    }
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcPascal::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 0:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(1);
        break;
    case 8:
        if (giftGiven != 0) {
            changeAct(4);
        } else {
            changeAct(3);
        }
        break;
    }
}

extern "C" const TalkStartMsg sSpNpcPascalTopicMsgs[3] = {
    {(const char *)sSpNpcPascalKey, 2}, {(const char *)sSpNpcPascalKey, 0}, {(const char *)sSpNpcPascalKey, 1},
};

extern "C" u8 sSpNpcPascalKey[16] = {'s', 'p', '_', 'n', 'p', 'c', '_', 'o', 't', 't', 'e', 'r', 0};

extern "C" u8 sSpNpcPascalModelPath[24] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 's', 'e', 'o', '.', 'n', 's', 'b', 'm', 'd', 0};

extern "C" ActorProfile sSpNpcPascalProfile = {(void *(*)())SpNpcPascal_Create, 0x68, 0x6e, 2, 0x5000, 0x5000, 0x3e800};

extern "C" u8 sSpNpcPascalTexturePath[28] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 's', 'e', 'o', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};


SpNpcPascalActEntry sSpNpcPascalActTable[6] = {
    {&SpNpcPascal::setupAct00, &SpNpcPascal::mainAct00},
    {&SpNpcPascal::setupAct01, &SpNpcPascal::mainAct01},
    {NULL, &SpNpcPascal::mainAct02},
    {&SpNpcPascal::setupAct03, &SpNpcPascal::mainAct03},
    {&SpNpcPascal::setupAct04, &SpNpcPascal::mainAct04},
    {&SpNpcPascal::setupAct05, &SpNpcPascal::mainAct05},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov076_022713c0) {
    HOST_OVERLAY_VAR(sSpNpcPascalKey),
    HOST_OVERLAY_VAR(sSpNpcPascalModelPath),
    HOST_OVERLAY_VAR(sSpNpcPascalProfile),
    HOST_OVERLAY_VAR(sSpNpcPascalTexturePath),
    HOST_OVERLAY_VAR(sSpNpcPascalActTable),
    HOST_OVERLAY_VARS_END
};
