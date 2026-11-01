#include "types.h"
#include "host_labels.h"
#include "gfx/VecFx32.h"
#include "game/TouchPicker.h"
#include "item/ItemId.h"
#include "talk/TalkStartMsg.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
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
#include "actor/ActorProfile.h"
#include "net/CommManager.h"
#include "npc/NpcActionCtrl.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "room/FtrActorGrid.h"
#include "save/ReddLastSale.h"
#include "town/BlockMap.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b5e5c.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov004/unk_ov004_0223e9bc.h"
#include "proto/ov052/unk_ov052_02258de0.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_0204cc1c.h"


class ActorTalkRequest;
class SpNpcRedd;
class SpNpcReddTalk;

struct SpNpcReddVecLocal : VecFx32 {
    SpNpcReddVecLocal() {}
};



extern "C" {
BOOL Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
void TalkRequest_SetTargetDone(void *p);
void TalkRequest_AddPlayerTalk6(void *p, s32 v);
void Clock_GetDateTime(void *p);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *p, s32 a, s32 b);
extern u16 data_020c6cc8;
s32 Ground_IsOnLockedExit(void *p);
void Ground_UnlockExit();
void Ground_LockExit(s32 a);
s32 TalkRequest_IsActive();
s32 func_01ffcb0c(s32 a, s32 b);
BOOL TouchPick_GetGroundPos(TouchPickResult *a, VecFx32 *b);
s32 Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
s32 Item_GetPrice(u16 *p);
u8 Scene_GetPrevious();
void ReddShop_BuyAt(s32 a, s32 b, s32 c);
BOOL ReddShop_IsPurchaseSynced();
u16 *ReddShop_GetItem(void *tbl, s32 a, s32 b);
void NpcActor_FindFreeUnitNear(void *out, void *self, void *v);
u8 Math_CountDownU8(void *p);
s32 Math_AngleDiffAbs(s32 a, s32 b);
s32 Vec_NotEqual(void *a, void *b);
s32 Vec_Equal(void *a, void *b);
void MI_CpuFill8(void *p, s32 v, s32 n);
void *__cxa_vec_ctor(void *, u32, u32, void (*)(void *), void (*)(void *));
#define data_021ed284 HOST_LABEL(ReddLastSale *, data_021ed284)
#define data_021ed2c0 HOST_LABEL(u8 (*)[], data_021ed2c0)
extern u16 gPad[];
extern s16 data_02135f44[];
extern BlockMap *gSceneBlockMap;
extern void *gCommManager;
}






class SpNpcReddTalk : public SpNpcTalkRequest {
public:
    SpNpcReddTalk();
    virtual ~SpNpcReddTalk();
    virtual void resetMsg();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    s32 getTopic();
    void setTopic(s32 v);
    void attachOwner(SpNpcRedd *v);
    void completePurchase();

    s32 topic;
    SpNpcRedd *owner;
    s32 price;
    s32 redVaseSlot;
    u8 feeQuoted;
    u8 pad_bd[3];
};









class SpNpcRedd : public SpNpcActor {
public:
    SpNpcRedd() : selectedItem(0xfff1), selectedItemX(0), selectedItemZ(0) {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 cmd, u8 arg);
    virtual BOOL acceptsSelfRequestedInteraction(void *a);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL tryClosingTimeTalk();
    BOOL tryFarewellTalk();
    BOOL tryItemTalk();
    BOOL pickDisplayItem();
    BOOL mainAct0A();
    BOOL setupAct0A();
    BOOL mainAct09();
    BOOL setupAct09();
    BOOL mainAct08();
    BOOL setupAct08();
    BOOL mainAct07();
    BOOL setupAct07();
    BOOL mainAct06();
    BOOL setupAct06();
    BOOL mainAct05();
    BOOL setupAct05();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct02();
    BOOL setupAct02();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    s32 act;
    SpNpcReddTalk talk;
    u16 standBlend;
    u16 selectedItem;
    ItemId pitchedItems[3];
    s32 selectedItemX;
    s32 selectedItemZ;
    u8 purchaseSyncPending;
    u8 approachTimer;
    u8 boughtSomething;
    u8 usedPitchMsgs[5];
    u8 usedThanksMsgs[5];
};

struct SpNpcReddActEntry {
    BOOL (SpNpcRedd::*enter)();
    BOOL (SpNpcRedd::*exit)();
};


extern "C" {
extern const TalkStartMsg sSpNpcReddTopicMsgs[13];
extern SpNpcReddActEntry sSpNpcReddActTable[11];
#define MSG_ID(i) (sSpNpcReddTopicMsgs[i].msgIndex)
extern ActorProfile sSpNpcReddProfile;
}

static inline BOOL Unk_ov052_022595dc_Eq(u16 *p, u16 *k) {
    if (Item_IsFurniture(p)) {
        *k = 0xfff1;
        s32 a = Item_GetFurnitureIndex(p);
        if (a == Item_GetFurnitureIndex(k)) return TRUE;
        return FALSE;
    }
    if (*p == 0xfff1) return TRUE;
    return FALSE;
}

static inline BOOL Unk_ov052_022595dc_Eq2(u16 *p, u16 *q) {
    if (Item_IsFurniture(p)) {
        s32 a = Item_GetFurnitureIndex(p);
        return a == Item_GetFurnitureIndex(q) ? TRUE : FALSE;
    }
    return *p == *q ? TRUE : FALSE;
}

static inline BOOL Unk_ov052_022595dc_EqK(u16 *p, u16 *k) {
    if (Item_IsFurniture(p)) {
        *k = 0xfff1;
        s32 a = Item_GetFurnitureIndex(p);
        return a == Item_GetFurnitureIndex(k) ? TRUE : FALSE;
    }
    return *p == 0xfff1 ? TRUE : FALSE;
}

static inline BOOL Unk_ov052_02258f34_Flags() {
    if (gTouchPrevHeld && gTouchPrevChanged) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov052_02258f34_Eq(u16 *p, u16 *k) {
    if (Item_IsFurniture(p)) {
        *k = 0xfff1;
        s32 a = Item_GetFurnitureIndex(p);
        if (a == Item_GetFurnitureIndex(k)) return TRUE;
        return FALSE;
    }
    if (*p == 0xfff1) return TRUE;
    return FALSE;
}


SpNpcRedd *SpNpcRedd_Create() {
    return new SpNpcRedd();
}

BOOL SpNpcRedd::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    standBlend = data_020c6cc8;
    MI_CpuFill8(usedPitchMsgs, 0, 5);
    MI_CpuFill8(usedThanksMsgs, 0, 5);
    ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(2, 0x400, 0x133, 0x199);
    return TRUE;
}

BOOL SpNpcRedd::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    if (Scene_GetPrevious()) {
        changeAct(1);
    } else {
        changeAct(0);
    }
    Ground_LockExit(0);
    selectedItem = 0xfff1;
    for (s32 i = 0; i < 3; i++) {
        pitchedItems[i].id = 0xfff1;
    }
    return TRUE;
}

u8 *SpNpcRedd::getTexturePath() { return sSpNpcReddTexturePath; }

u8 *SpNpcRedd::getModelPath() { return sSpNpcReddModelPath; }

BOOL SpNpcRedd::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcReddActTable[act].exit != NULL) {
        r = (this->*sSpNpcReddActTable[act].exit)();
    }
    return r;
}

void SpNpcRedd::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcReddActTable[state].enter) {
        ok = (this->*sSpNpcReddActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcRedd::setupAct00() {
    talk.setTopic(0);
    return TRUE;
}

BOOL SpNpcRedd::mainAct00() {
    TalkRequest_AddPlayerTalk6(this, 0);
    return TRUE;
}

BOOL SpNpcRedd::setupAct01() {
    ((NpcActionCtrl *)(&actionCtrl))->requestStand(1, standBlend);
    standBlend = data_020c6cc8;
    return TRUE;
}

BOOL SpNpcRedd::mainAct01() {
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    s32 r6 = getDistanceToPlayer(4);
    s32 t = getAngleToPlayer(4);
    s32 r4 = Math_AngleDiffAbs(rotY, t);
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    if (r6 > 0x3000 && Vec_NotEqual(&out, &position)) {
        changeAct(3);
    } else if (r4 > 0x2000) {
        changeAct(2);
    }
    if (tryFarewellTalk()) {
        return TRUE;
    }
    if (tryClosingTimeTalk()) {
        return TRUE;
    }
    tryItemTalk();
    return TRUE;
}

BOOL SpNpcRedd::setupAct02() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcRedd::mainAct02() {
    if (tryFarewellTalk()) {
        return TRUE;
    }
    if (tryClosingTimeTalk()) {
        return TRUE;
    }
    if (tryItemTalk()) {
        return TRUE;
    }
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    s32 r6 = getDistanceToPlayer(4);
    s32 r4 = getAngleToPlayer(4);
    Math_AngleDiffAbs(rotY, r4);
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    if (r6 > 0x3000) {
        if (Vec_NotEqual(&out, &position)) {
            changeAct(3);
            return TRUE;
        }
    }
    ((NpcMoveCtrl *)(&moveCtrl))->setTargetAngle(r4);
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            changeAct(1);
        }
    }
    return TRUE;
}

BOOL SpNpcRedd::setupAct03() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcRedd::mainAct03() {
    if (tryFarewellTalk()) {
        return TRUE;
    }
    if (tryClosingTimeTalk()) {
        return TRUE;
    }
    if (tryItemTalk()) {
        return TRUE;
    }
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    s32 t = getDistanceToPlayer(4);
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    if (t > 0x4000) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 2) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    ((NpcMoveCtrl *)(&moveCtrl))->setWaypoint((VecFx32 *)(&out));
    if (t <= 0x3000 || Vec_Equal(&out, &position) != 0) {
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcRedd::setupAct04() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcRedd::mainAct04() {
    if (tryFarewellTalk()) {
        return TRUE;
    }
    if (tryClosingTimeTalk()) {
        return TRUE;
    }
    if (tryItemTalk()) {
        return TRUE;
    }
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    s32 t = getDistanceToPlayer(4);
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    if (t > 0x4000) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 2) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    ((NpcMoveCtrl *)(&moveCtrl))->setWaypoint((VecFx32 *)(&out));
    if (t <= 0x3000 || Vec_Equal(&out, &position) != 0) {
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcRedd::setupAct05() {
    void *p = talk.getTalkPlayer();
    s32 r = 0;
    if (p) {
        r = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, r, 0);
    return TRUE;
}

BOOL SpNpcRedd::mainAct05() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy()) {
        return TRUE;
    }
    if (purchaseSyncPending != 0 && ReddShop_IsPurchaseSynced() == 0) {
        return TRUE;
    }
    TalkRequest_SetTargetDone(this);
    changeAct(7);
    return TRUE;
}

BOOL SpNpcRedd::setupAct06() {
    void *p = talk.getTalkPlayer();
    s32 r = 0;
    if (p) {
        r = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, r, 1);
    return TRUE;
}

BOOL SpNpcRedd::mainAct06() {
    VecFx32CtorDtor *pv = (VecFx32CtorDtor *)PlayerActor_GetBodyPos(4);
    VecFx32CtorDtor v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
        changeAct(7);
    }
    return TRUE;
}

BOOL SpNpcRedd::setupAct07() { return TRUE; }

BOOL SpNpcRedd::mainAct07() { return TRUE; }

BOOL SpNpcRedd::setupAct08() { return TRUE; }

BOOL SpNpcRedd::mainAct08() { return TRUE; }

BOOL SpNpcRedd::setupAct09() {
    approachTimer = 0x32;
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcRedd::mainAct09() {
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    s32 t = getDistanceToPlayer(4);
    gSceneBlockMap->getWalkLinksAtPos(&position);
    if (t > 0x4000) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 2) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    ((NpcMoveCtrl *)(&moveCtrl))->setWaypoint((VecFx32 *)(&out));
    if (t <= 0x3000 || Vec_Equal(&out, &position) != 0 || Math_CountDownU8(&approachTimer) == 0) {
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(5);
    }
    return TRUE;
}

BOOL SpNpcRedd::setupAct0A() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    ((NpcMoveCtrl *)(&moveCtrl))->setTargetAngle(getAngleToPlayer(4));
    return TRUE;
}

BOOL SpNpcRedd::mainAct0A() {
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            ((NpcActionCtrl *)(&actionCtrl))->requestStand(1, standBlend);
        }
    }
    TalkRequest_AddPlayerTalk6(this, 0);
    return TRUE;
}

extern "C" s32 SpNpcRedd_CountUnusedFlags(void *self, u8 *buf, s32 n) {
    s32 c = 0;
    s32 i;
    for (i = 0; i < n; buf++, i++) {
        if (*buf == 0) {
            c++;
        }
    }
    return c;
}

extern "C" s32 SpNpcRedd_PickUnusedFlag(void *self, u8 *buf, s32 n) {
    s32 k, i;
    s32 cnt = SpNpcRedd_CountUnusedFlags(self, buf, n);
    s32 r = 0;
    k = Random_GlobalBelow(cnt);
    for (i = r; i < n; buf++, i++) {
        if (*buf == 0) {
            if (k == 0) {
                r = i;
                break;
            }
            k--;
        }
    }
    return r;
}

SpNpcReddTalk::SpNpcReddTalk() {}

SpNpcReddTalk::~SpNpcReddTalk() {}

void SpNpcReddTalk::resetMsg() { ActorTalkRequest::resetMsg(); }

void SpNpcReddTalk::attachOwner(SpNpcRedd *v) {
    resetMsg();
    owner = v;
    redVaseSlot = -1;
    feeQuoted = 0;
}

void SpNpcReddTalk::setTopic(s32 v) { topic = v; }

s32 SpNpcReddTalk::getTopic() { return topic; }

extern "C" BOOL SpNpcRedd_IsSoldOut(void *self) {
    s32 i;
    for (i = 0; (u32)i < 3; i++) {
        u16 *p = ReddShop_GetItem(data_021ed2c0, i, 0);
        BOOL r;
        if (Item_IsFurniture(p)) {
            u16 t = 0x1547;
            r = (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&t)) ? TRUE : FALSE;
        } else {
            r = (*p == 0x1547) ? TRUE : FALSE;
        }
        if (!r) {
            return FALSE;
        }
    }
    return TRUE;
}

void SpNpcReddTalk::start(TalkStartMsg *out) {
    u16 x, b, c, k1, k4, k2, k3;
    void *h = PlayerData_GetCurrent();
    if (topic == 0xc) {
        out->msgIndex = MSG_ID(topic);
        out->msgKey = (const char *)sSpNpcReddTopicMsgs[topic].msgKey;
        return;
    }
    if (topic != 0 && topic != 1 && topic != 2) {
        u16 *pp = &owner->selectedItem;
        if (Unk_ov052_022595dc_Eq(pp, &k1)) {
            if (((PlayerData *)(h))->testFlag(0xc) != 0) {
                if (((CommManager *)(gCommManager))->isOnline() == 0 && redVaseSlot == -1) {
                    x = 0x34a8;
                    redVaseSlot = Pocket_FindItem(&x);
                }
                if (redVaseSlot >= 0) {
                    topic = 5;
                } else if (SpNpcRedd_IsSoldOut(this)) {
                    topic = 6;
                } else if (Talk_CheckAndSetPlayerFlag(1, 1) == 0) {
                    topic = 7;
                } else {
                    if (((PlayerId *)(ReddLastSale_GetBuyer(&data_021ed284)))->isValid() != 0 &&
                        (b = data_021ed284.item, !Unk_ov052_022595dc_Eq(&b, &k2))) {
                        c = data_021ed284.item;
                        ((ActorTalkRequest *)(this))->setItemNameSlot(&c, 0, 7);
                        u16 *r6 = (u16 *)PlayerData_GetCurrent()->getPlayerId();
                        u16 *r7 = (u16 *)ReddLastSale_GetBuyer(&data_021ed284);
                        if (!(r7[0] == r6[0] && memcmp(r7 + 1, r6 + 1, 8) == 0 && ((PlayerId *)(r7))->equals((PlayerId *)(r6)) != 0)) {
                            ((ActorTalkRequest *)(this))->setPlayerNameSlot((PlayerId *)ReddLastSale_GetBuyer(&data_021ed284), 1);
                            topic = 8;
                        } else {
                            ((ActorTalkRequest *)(this))->setPlayerNameSlot(((PlayerData *)(h))->getPlayerId(), 1);
                            topic = 9;
                        }
                    } else {
                        topic = 0xa;
                    }
                }
            }
        }
    }
    if (topic < 0 || topic >= 0xd) {
        return;
    }
    out->msgIndex = MSG_ID(topic);
    if (((PlayerData *)(h))->testFlag(0xc) != 0) {
        if (topic == 0xa) {
            out->msgIndex = Random_GlobalBelow(4) + 0x17;
            if (out->msgIndex == 0x1a) {
                out->msgIndex = 0x30;
            }
        }
        s32 hit = 0;
        if (!Unk_ov052_022595dc_Eq(&owner->selectedItem, &k3)) {
            price = Item_GetPrice(&owner->selectedItem) * 2;
            ((ActorTalkRequest *)(this))->setItemNameSlot(&owner->selectedItem, 1, 7);
            ((ActorTalkRequest *)(this))->setNumberSlot(price, 2, 10, 1, 0);
            s32 i;
            for (i = 0; i < 3; i++) {
                u16 *p, *q1;
                q1 = &owner->pitchedItems[i].id;
                p = &owner->selectedItem;
                if (Unk_ov052_022595dc_Eq2(p, q1)) {
                    out->msgIndex = 0x1d;
                    break;
                }
                u16 *q = &owner->pitchedItems[i].id;
                if (Unk_ov052_022595dc_EqK(q, &k4)) {
                    hit = i;
                }
            }
            if (out->msgIndex != 0x1d) {
                s32 idx = SpNpcRedd_PickUnusedFlag(owner, owner->usedPitchMsgs, 5);
                if (owner->usedPitchMsgs[idx] == 0) {
                    owner->usedPitchMsgs[idx] = 1;
                    owner->pitchedItems[hit].id = owner->selectedItem;
                }
                if (SpNpcRedd_CountUnusedFlags(owner, owner->usedPitchMsgs, 5) == 0) {
                    MI_CpuFill8(owner->usedPitchMsgs, 0, 5);
                    owner->usedPitchMsgs[idx] = 1;
                    owner->pitchedItems[hit].id = owner->selectedItem;
                }
                out->msgIndex = idx + 0x1e;
            }
        }
    }
    out->msgKey = (const char *)sSpNpcReddTopicMsgs[topic].msgKey;
}

void SpNpcReddTalk::onMessageEnd(u32) {
    char *tbl = sSpNpcReddKey;
    u32 msg = 0xff;
    u16 v[4];
    void *h = PlayerData_GetCurrent();
    switch (msgIndex) {
    case 0x2e:
        v[1] = 0x36fc;
        ((ActorTalkRequest *)(this))->requestGiveItem(&v[1], 0, 5, 0);
        v[2] = 0x36fc;
        Pocket_AddItem(&v[2], 0);
        msg = 0x2f;
    case 0x2d:
        redVaseSlot = -2;
        break;
    case 6:
        if (((PlayerData *)(h))->testFlag(0xc) == 0) {
            setTopic(3);
        } else {
            setTopic(10);
        }
        break;
    case 7:
        setTopic(4);
        break;
    case 0x10:
        v[3] = 0x149d;
        ((ActorTalkRequest *)(this))->requestTakeItem(&v[3], 0, 5, 0);
        owner->selectedItem = 0xfff1;
        msg = 0x11;
        NpcActor_ChargePlayer(owner, 0xbb8);
        setTopic(7);
        ((PlayerData *)(h))->setFlag(0xc);
        Talk_CheckAndSetPlayerFlag(1, 1);
        break;
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
        completePurchase();
        break;
    }
    if (msg != 0xff) {
        *(u8 *)v = msg;
        window->setNextMessage((u8 *)v, tbl);
    }
}

void SpNpcReddTalk::onChoice(u32) {
    s32 t = getChoiceList()->getResult();
    char *tbl = sSpNpcReddKey;
    u32 msg = 0xff;
    u16 v[2];
    switch (msgIndex) {
    case 0x2c:
        if (t == 0) {
            if (redVaseSlot >= 0) {
                Pocket_RemoveItem(redVaseSlot);
                v[1] = 0x34a8;
                ((ActorTalkRequest *)(this))->requestTakeItem(&v[1], 0, 5, 0);
            }
            msg = 0x2e;
        }
        break;
    case 7:
    case 0x12:
        if (t != 0) {
            if (NpcActor_CanPlayerPay(owner, 0xbb8) == 0) {
                msg = 0xa;
            } else if (feeQuoted == 0) {
                msg = 8;
            } else {
                msg = 0xc;
            }
        }
        break;
    case 9:
        feeQuoted = 1;
        if (t == 0) {
            msg = 0xc;
        }
        break;
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
        if (t == 0) {
            if (NpcActor_CanPlayerPay(owner, price) != 0) {
                if (Pocket_FindEmpty() >= 0) {
                    s32 idx = SpNpcRedd_PickUnusedFlag(owner, owner->usedThanksMsgs, 5);
                    owner->usedThanksMsgs[idx] = 1;
                    if (SpNpcRedd_CountUnusedFlags(owner, owner->usedThanksMsgs, 5) == 0) {
                        MI_CpuFill8(owner->usedThanksMsgs, 0, 5);
                        owner->usedThanksMsgs[idx] = 1;
                    }
                    msg = (u8)(idx + 0x24);
                    break;
                }
                msg = 0x2a;
            } else {
                msg = 0x29;
            }
        }
        owner->selectedItem = 0xfff1;
        break;
    }
    if (msg != 0xff) {
        *(u8 *)v = msg;
        window->setNextMessage((u8 *)v, tbl);
    }
}

void SpNpcReddTalk::completePurchase() {
    NpcActor_ChargePlayer(owner, price);
    Pocket_AddItem(&owner->selectedItem, 0);
    ReddShop_BuyAt(owner->selectedItemX, owner->selectedItemZ, 0xf);
    ReddLastSale *const g = &data_021ed284;
    g->setBuyer(reinterpret_cast<const ReddLastSale *>(PlayerData_GetCurrent()->getPlayerId()));
    g->item = owner->selectedItem;
    ((ActorTalkRequest *)(this))->setNumberSlot(price, 2, 10, 1, 0);
    owner->selectedItem = 0xfff1;
    owner->boughtSomething = 1;
}

BOOL SpNpcRedd::acceptsInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || netIsTalkLocked() != 0 || tryItemTalk() != 0) {
        return FALSE;
    }
    return TRUE;
}

BOOL SpNpcRedd::acceptsSelfRequestedInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

void SpNpcRedd::onInteractionEvent(u32 cmd, u8 arg) {
    partnerPlayer = arg;
    switch (cmd) {
    case 3:
        changeAct(8);
        break;
    case 1:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        if (talk.getTopic() == 0) {
            changeAct(5);
        } else if (talk.getTopic() == 1 || talk.getTopic() == 2 ||
                   talk.getTopic() == 0xc) {
            changeAct(6);
        } else {
            changeAct(9);
        }
        break;
    case 0:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(5);
        break;
    case 8:
        if (talk.getTopic() == 1 || talk.getTopic() == 2) {
            VecFx32 v;
            VecFx32 *src = (VecFx32 *)PlayerActor_GetBodyPos(4);
            v = *src;
            if (Ground_IsOnLockedExit(&v)) {
                Ground_UnlockExit();
            } else {
                changeAct(1);
            }
        } else if (talk.getTopic() == 0xc) {
            SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
        } else {
            changeAct(1);
        }
        break;
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    }
}

BOOL SpNpcRedd::pickDisplayItem() {
    u16 t[2];
    s32 bx, by;
    VecFx32 v;
    Character *p = (Character *)PlayerActor_GetActor(4);
    BOOL f = Unk_ov052_02258f34_Flags() ? TRUE : FALSE;
    if (p == 0 || TalkRequest_IsActive() != 0 || ((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || ((gPad[1] & 1) == 0 && f == 0)) {
        return FALSE;
    }
    VecFx32 *pv = (VecFx32 *)&p->position;
    v.x = p->position.x;
    v.y = pv->y;
    v.z = pv->z;
    u32 ang = p->rotY;
    bx = 0;
    by = 0;
    s32 idx = ((u16)ang >> 4) * 2;
    v.x += func_01ffcb0c(0x2000, data_02135f44[idx]);
    v.z += func_01ffcb0c(0x2000, data_02135f44[idx + 1]);
    FieldPos_ToUnit(&bx, &by, &v);
    if (f) {
        void *o = FtrActorGrid_GetInstance()->getActor(bx, by, 0);
        if (o != 0) {
            if (o != TouchPick_GetTargetObject(Scene_GetTouchPicker(), 0, 0)) {
                return FALSE;
            }
        } else {
            s32 bx2 = 0, by2 = 0;
            VecFx32 v2;
            TouchPick_GetGroundPos(Scene_GetTouchPicker(), &v2);
            FieldPos_ToUnit(&bx2, &by2, &v2);
            if (bx2 != bx || by2 != by) {
                return FALSE;
            }
        }
    }
    t[0] = *ShopStock_GetItemAt(bx, by);
    if (Unk_ov052_02258f34_Eq(&t[0], &t[1])) {
        return FALSE;
    }
    selectedItem = t[0];
    selectedItemX = bx;
    selectedItemZ = by;
    purchaseSyncPending = 0;
    return TRUE;
}

BOOL SpNpcRedd::tryItemTalk() {
    if (pickDisplayItem()) {
        TalkRequest_AddPlayerTalk6(this, 0);
        return TRUE;
    }
    return FALSE;
}

BOOL SpNpcRedd::tryFarewellTalk() {
    SpNpcReddVecLocal v;
    VecFx32 *src = (VecFx32 *)PlayerActor_GetBodyPos(4);
    *(VecFx32 *)&v = *src;
    if (Ground_IsOnLockedExit(&v)) {
        if (boughtSomething == 0) {
            talk.setTopic(1);
        } else {
            talk.setTopic(2);
        }
        TalkRequest_AddPlayerTalk6(this, 0);
        changeAct(0xa);
        return TRUE;
    }
    return FALSE;
}

BOOL SpNpcRedd::tryClosingTimeTalk() {
    if (TalkRequest_IsActive()) {
        return FALSE;
    }
    u32 buf[2];
    buf[0] = 0;
    buf[1] = 0;
    Clock_GetDateTime(buf);
    if (((u8 *)buf)[2] < 6) {
        talk.setTopic(0xc);
        TalkRequest_AddPlayerTalk6(this, 0);
        return TRUE;
    }
    return FALSE;
}

extern "C" char sSpNpcReddKey[] = "sp_npc_fox";
extern "C" u8 sSpNpcReddModelPath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'f', 'o', 'x', '.', 'n', 's', 'b', 'm', 'd', 0};
extern "C" u8 sSpNpcReddTexturePath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'f', 'o', 'x', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};
extern "C" ActorProfile sSpNpcReddProfile = {(void *(*)())SpNpcRedd_Create, 0x55, 0x5c, 2, 0x5000, 0x5000, 0x3e800};

extern "C" const TalkStartMsg sSpNpcReddTopicMsgs[13] = {
    {sSpNpcReddKey, 0x06}, {sSpNpcReddKey, 0x1c}, {sSpNpcReddKey, 0x1b},
    {sSpNpcReddKey, 0x07}, {sSpNpcReddKey, 0x12}, {sSpNpcReddKey, 0x2c},
    {sSpNpcReddKey, 0x1a}, {sSpNpcReddKey, 0x14}, {sSpNpcReddKey, 0x16},
    {sSpNpcReddKey, 0x15}, {sSpNpcReddKey, 0x17}, {sSpNpcReddKey, 0x1e},
    {sSpNpcReddKey, 0x33},
};

extern "C" SpNpcReddActEntry sSpNpcReddActTable[11] = {
    {&SpNpcRedd::setupAct00, &SpNpcRedd::mainAct00},
    {&SpNpcRedd::setupAct01, &SpNpcRedd::mainAct01},
    {&SpNpcRedd::setupAct02, &SpNpcRedd::mainAct02},
    {&SpNpcRedd::setupAct03, &SpNpcRedd::mainAct03},
    {&SpNpcRedd::setupAct04, &SpNpcRedd::mainAct04},
    {&SpNpcRedd::setupAct05, &SpNpcRedd::mainAct05},
    {&SpNpcRedd::setupAct06, &SpNpcRedd::mainAct06},
    {&SpNpcRedd::setupAct07, &SpNpcRedd::mainAct07},
    {&SpNpcRedd::setupAct08, &SpNpcRedd::mainAct08},
    {&SpNpcRedd::setupAct09, &SpNpcRedd::mainAct09},
    {&SpNpcRedd::setupAct0A, &SpNpcRedd::mainAct0A},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov052_02258de0) {
    HOST_OVERLAY_VAR(sSpNpcReddKey),
    HOST_OVERLAY_VAR(sSpNpcReddModelPath),
    HOST_OVERLAY_VAR(sSpNpcReddTexturePath),
    HOST_OVERLAY_VAR(sSpNpcReddProfile),
    HOST_OVERLAY_VAR(sSpNpcReddActTable),
    HOST_OVERLAY_VARS_END
};
