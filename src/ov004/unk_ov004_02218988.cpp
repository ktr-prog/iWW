#include "types.h"
#include "host_tick.h"
#include "npc/VillagerState.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "npc/VillagerClothModel.h"
#include "npc/VillagerMood.h"
#include "snd/SndSeEmitter.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/NpcMoveAnimSet.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "npc/NpcFaceAnim.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/VillagerTalk.h"
#include "talk/TalkTopicMsg.h"
#include "npc/VillagerId.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "room/FtrActorTable.h"
#include "talk/ChoiceList.h"
#include "talk/TalkWindowState.h"
#include "room/FtrActorGrid.h"
#include "save/VillagerData.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov004/unk_ov004_02218988.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/main/unk_020b4828.h"

class FleaMarketBuyerVillagerTalk;
class FleaMarketBuyerVillager;

typedef void (FleaMarketBuyerVillagerTalk::*Unk_ov004_0224c740_Fn)();
typedef BOOL (FleaMarketBuyerVillager::*Unk_ov004_0224c7d0_Fn)();

struct FleaMarketBuyerTalkScript {
    Unk_ov004_0224c740_Fn fn;
    u8 flag;
    u8 pad[3];
};

struct FleaMarketBuyerActEntry {
    Unk_ov004_0224c7d0_Fn a;
    Unk_ov004_0224c7d0_Fn b;
};

extern "C" {
extern u16 data_020c6cc8;
extern s16 data_02135f44[];
extern u8 gTalkMsgIndexEnd[];
extern u8 gFieldSceneKind[];
extern FleaMarketBuyerTalkScript sFleaMarketBuyerTalkScripts[2];
extern FleaMarketBuyerActEntry sFleaMarketBuyerActTable[9];

s32 FtrActor_GetFtrIndex(FtrActor *self);
void FtrActor_GetCenter(FtrActor *self, VecFx32 *out);
u16 Item_MakeFurniture(s32 a, s32 b);
s32 Item_IsFurniture(u16 *);
u32 Item_GetFurnitureIndex(u16 *);
s32 Item_FindMoneyBagForAmount(s32 a, BOOL up, s32 *out);
BOOL Ground_IsOnLockedExit(VecFx32 *p);
void Ground_UnlockExit();
void Ground_LockExit(s32);
void TalkRequest_AddPlayerTalk6(void *, s32);
s32 TalkRequest_IsActive();
void Clock_GetDateTime(ClockDateTime *p);
s32 DateTime_DiffMinutes(ClockDateTime *a, ClockDateTime *b);
void Villager_SetFleaMarketVisited(void *a, void *b);
VillagerMemory *Villager_FindOrCreateMemory(VillagerMemory *t, void *b);
void VillagerMemory_RecordTalk(VillagerMemory *self, void *a, u8 *b, u8 *c);
VillagerMemory *Villager_GetMemorySlotForNew(VillagerMemory *t);
void Villager_AddReceivedItem(VillagerData *self, u16 *val);
s32 Item_GetPrice(u16 *);
VillagerMemory *Villager_FindMemory(void *a, void *b);
s32 FX_Div(s32, s32);
s32 func_01ffcb0c(s32, s32);
void TalkRequest_SetTargetDone(void *);
s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
void NpcActor_FindFreeUnitNear(VecFx32 *out, NpcActor *self, VecFx32 *in);
s32 Vec_Equal(VecFx32 *a, VecFx32 *b);
s32 Vec_NotEqual(VecFx32 *a, VecFx32 *b);
s32 Math_AngleDiffAbs(s32, s32);
void FieldPos_ToUnit(s32 *x, s32 *y, VecFx32 *v);
u8 Math_CountDownU8(u8 *p);
void VillagerStates_SetFleaMarketBuyer(s32);
s32 VillagerState_ResetRole(void *);
VillagerState *Villager_GetState(void *);
void VillagerState_SetRole(void *, u32);
u8 Scene_GetPrevious();
s32 SceneId_IsTownUnk31(u32 scene);
}

class FleaMarketBuyerVillagerTalk : public VillagerTalk {
public:
    FleaMarketBuyerVillagerTalk();
    virtual ~FleaMarketBuyerVillagerTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void clearOffer();
    void completePurchase();
    void offerPrice();
    void setScript(s32 v);
    void attachOwner(VillagerActor *owner);

    /* 0x1a0 */ FleaMarketBuyerVillager *villager;
    /* 0x1a4 */ s32 offerAmount;
    /* 0x1a8 */ s32 scriptIndex;
};

class FleaMarketBuyerVillager : public VillagerActor {
public:
    FleaMarketBuyerVillager() : targetItem(0xfff1) {
        startTime.words[0] = 0;
        startTime.words[1] = 0;
    }
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL acceptsSelfRequestedInteraction(void *a);
    virtual BOOL updateAct();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();

    void setViewDistance(FtrActor *arg);
    void pushViewedFurniture(u32 v);
    BOOL isFurnitureForSale(s32 idx);
    BOOL pickFurnitureToView();
    BOOL checkLeave();
    BOOL mainAct08();
    BOOL setupAct08();
    BOOL mainAct06();
    BOOL setupAct06();
    BOOL mainAct07();
    BOOL setupAct07();
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
    void playDoorChime();
    void changeAct(s32 idx);

    /* 0x894 */ u16 targetItem;
    /* 0x896 */ u8 pad_896[2];
    /* 0x898 */ VecFx32 targetPos;
    /* 0x8a4 */ s32 targetFtrIndex;
    /* 0x8a8 */ u8 viewedFurniture[100];
    /* 0x90c */ s32 act;
    /* 0x910 */ s32 prevAct;
    /* 0x914 */ FleaMarketBuyerVillagerTalk talk;
    /* 0xac0 */ u8 visitStage;
    /* 0xac1 */ u8 pad_ac1[3];
    /* 0xac4 */ s32 leaveTimer;
    /* 0xac8 */ ClockDateTimeWords startTime;
    /* 0xad0 */ s32 viewDistance;
    /* 0xad4 */ u8 entryTimer;
    /* 0xad5 */ u8 callTimer;
    /* 0xad6 */ u8 talkMelodyPlayed;
    /* 0xad7 */ u8 callCheckTimer;
    /* 0xad8 */ u8 purchaseCount;
    /* 0xad9 */ u8 pad_ad9[3];
    /* 0xadc */ s32 furnitureCount;
    /* 0xae0 */ s32 doorWaitFrames;
};

extern "C" ActorProfile sFleaMarketBuyerVillagerProfile = {(void *(*)())FleaMarketBuyerVillager_Create, 0x87, 0x8b, 2, 0x5000, 0x5000, 0x3e800};
extern "C" {
u8 data_ov004_02250828[0x28];
u8 data_ov004_022507b0[0x28];
u8 data_ov004_022507d8[0x28];
u8 data_ov004_02250800[0x28];
}
typedef FleaMarketBuyerVillager FMBV;
extern "C" FleaMarketBuyerTalkScript sFleaMarketBuyerTalkScripts[2] = {
    {0, 0, {0, 0, 0}},
    {&FleaMarketBuyerVillagerTalk::offerPrice, 0, {0, 0, 0}}};
extern "C" FleaMarketBuyerActEntry sFleaMarketBuyerActTable[9] = {
    {&FMBV::setupAct00, &FMBV::mainAct00},
    {&FMBV::setupAct01, &FMBV::mainAct01},
    {&FMBV::setupAct02, &FMBV::mainAct02},
    {&FMBV::setupAct03, &FMBV::mainAct03},
    {&FMBV::setupAct04, &FMBV::mainAct04},
    {&FMBV::setupAct05, &FMBV::mainAct05},
    {&FMBV::setupAct06, &FMBV::mainAct06},
    {&FMBV::setupAct07, &FMBV::mainAct07},
    {&FMBV::setupAct08, &FMBV::mainAct08}};

static inline BOOL Unk_ov004_02218a48_Range(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 a = *p;
    u32 b = *p;
    if (b >= lo && a <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov004_02218a48_Eq(u16 *p, u32 k) {
    u16 t;
    if (Item_IsFurniture(p)) {
        t = k;
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&t)) {
            return TRUE;
        }
        return FALSE;
    }
    if (*p == k) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov004_022191cc_Is1(u8 *p) {
    if (*p == 1) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov004_02219378_Chk(u16 *p) {
    BOOL r;
    if (Item_IsFurniture(p)) {
        u16 v = 0xfff1;
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&v)) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    } else {
        if (*p == 0xfff1) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    }
    return r;
}

static inline BOOL Unk_ov004_0221946c_Chk(u16 *p, u16 *vp) {
    BOOL r;
    if (Item_IsFurniture(p)) {
        *vp = 0xfff1;
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(vp)) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    } else {
        if (*p == 0xfff1) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    }
    return r;
}

extern "C" FleaMarketBuyerVillager *FleaMarketBuyerVillager_Create() {
    return new FleaMarketBuyerVillager;
}

BOOL FleaMarketBuyerVillager::preCreate() {
    if (!VillagerActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest(&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL FleaMarketBuyerVillager::onCreate() {
    if (!VillagerActor::onCreate()) {
        return FALSE;
    }
    targetItem = 0xfff1;
    footstepFx.enableFootsteps();
    targetPos.x = position.x;
    targetPos.y = position.y;
    targetPos.z = position.z;
    viewDistance = 0x3000;
    s32 i;
    for (i = 0; i < 100; i++) {
        viewedFurniture[i] = 0xff;
    }
    lookAt.disable();
    PlayerId *o;
    if (PlayerData_GetCurrent()) {
        o = PlayerData_GetCurrent()->getPlayerId();
    } else {
        o = 0;
    }
    if (SceneId_IsTownUnk31(Scene_GetPrevious()) != 0 ||
        (getVillagerData() && o && o->isValid() && Villager_FindMemory(getVillagerData(), o) &&
         Villager_FindMemory(getVillagerData(), o)->isFleaMarketVisited())) {
        furnitureCount = FtrActorTable_GetInstance()->countUsed();
        HouseVisitor_SetPresent();
        Ground_LockExit(0);
        FtrMgr_SetSaleMode();
        Clock_GetDateTime(&startTime.dt);
        visitStage = 2;
        changeAct(3);
    } else {
        position.x = 0x10000;
        prevPosition.x = 0x10000;
        position.z = 0x23000;
        prevPosition.z = 0x23000;
        callCheckTimer = 100;
        doorWaitFrames = 1;
        changeAct(0);
    }
    if (getVillagerData()) {
        VillagerState_SetRole(Villager_GetState(getVillagerData()), 2);
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::onDelete() {
    if (!VillagerActor::onDelete()) {
        return FALSE;
    }
    if (visitStage == 6 || visitStage == 4) {
        HouseVisitor_ClearPresent();
        VillagerStates_SetFleaMarketBuyer(-1);
    }
    if (getVillagerData()) {
        VillagerState_ResetRole(Villager_GetState(getVillagerData()));
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::onDraw() {
    if (visitStage != 0) {
        NpcActor::onDraw();
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::updateAct() {
    BOOL r = FALSE;
    if (sFleaMarketBuyerActTable[act].b) {
        r = (this->*sFleaMarketBuyerActTable[act].b)();
    }
    return r;
}

void FleaMarketBuyerVillager::changeAct(s32 idx) {
    BOOL ok = TRUE;
    if (sFleaMarketBuyerActTable[idx].a) {
        ok = (this->*sFleaMarketBuyerActTable[idx].a)();
    }
    if (ok) {
        prevAct = act;
        act = idx;
    }
}

void FleaMarketBuyerVillager::playDoorChime() {
    Snd_SeEmitterPlayOneShot(&seEmitter, 0x4cb, 0x7f, 0);
    Building_PlayDoorChime();
}

BOOL FleaMarketBuyerVillager::setupAct00() {
    visitStage = 0;
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketBuyerVillager::mainAct00() {
    if (callTimer == 0) {
        if (Math_CountDownU8(&callCheckTimer)) {
            return TRUE;
        }
        if (Random_GlobalBelow(0x65) > 0x19) {
            callCheckTimer = 100;
            return TRUE;
        }
        Actor *p = (Actor *)PlayerActor_GetActor(4);
        if (p) {
            VecFx32 v;
            VecFx32 *pv = (VecFx32 *)&p->position;
            v.x = p->position.x;
            v.y = pv->y;
            v.z = pv->z;
            if (Vec_DistXZ(&v, &position) > 0x8000) {
                Snd_SeEmitterPlayOneShot(&seEmitter, 0x4ca, 0x7f, 0);
                callTimer = 0x1e;
            }
        }
    }
    if (callTimer != 0) {
        TalkRequest_AddPlayerTalk6(this, 0);
        if (callTimer > 1) {
            Math_CountDownU8(&callTimer);
        }
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::setupAct01() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketBuyerVillager::mainAct01() {
    TalkWindowState *p = TalkWindow_Get(0);
    if (p) {
        if (p->state != 0) {
            return TRUE;
        }
    }
    if (entryTimer == 0x28) {
        playDoorChime();
    }
    rotX = 0;
    rotY = -0x8000;
    rotZ = 0;
    moveAngleX = 0;
    moveAngleY = -0x8000;
    moveAngleZ = 0;
    if (Math_CountDownU8(&entryTimer)) {
        if (entryTimer == 8) {
            position.x = 0x10000;
            prevPosition.x = 0x10000;
            position.z = 0x1f000;
            prevPosition.z = 0x1f000;
        }
        return TRUE;
    }
    changeAct(2);
    return TRUE;
}

BOOL FleaMarketBuyerVillager::setupAct02() {
    entryTimer = 0;
    return TRUE;
}

BOOL FleaMarketBuyerVillager::mainAct02() {
    rotX = 0;
    rotY = -0x8000;
    rotZ = 0;
    moveAngleX = 0;
    moveAngleY = -0x8000;
    moveAngleZ = 0;
    u8 c = entryTimer;
    if (c == 1) {
        actionCtrl.requestAction(0, 2, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        TalkRequest_SetTargetDone(this);
        changeAct(8);
        return TRUE;
    } else if (c == 0) {
        VecFx32CtorDtor v;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        s32 g = func_01ffcb0c(0x4000, data_02135f44[((u16)rotY >> 4) * 2]);
        v.x = g + position.x;
        g = func_01ffcb0c(0x4000, data_02135f44[((u16)rotY >> 4) * 2 + 1]);
        v.z = g + position.z;
        actionCtrl.requestAction(1, 2, v.x, v.z, 0, 0, 0, 0, data_020c6cc8, 0);
        entryTimer = 30;
        return TRUE;
    } else {
        entryTimer = c - 1;
        return TRUE;
    }
}

BOOL FleaMarketBuyerVillager::setupAct03() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketBuyerVillager::mainAct03() {
    if (checkLeave()) {
        return TRUE;
    }
    if (visitStage != 2) {
        return TRUE;
    }
    if (pickFurnitureToView()) {
        s32 r6 = Vec_DistXZ(&position, &targetPos);
        VecFx32 loc0;
        NpcActor_FindFreeUnitNear(&loc0, this, &targetPos);
        s32 r1 = Math_AngleXZ(&position, &targetPos);
        s32 r4 = Math_AngleDiffAbs(rotY, r1);
        if (r6 > viewDistance && Vec_NotEqual(&loc0, &position)) {
            changeAct(5);
        } else if (r4 > 0x2000) {
            changeAct(4);
        }
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::setupAct04() {
    Vec_DistXZ(&position, &targetPos);
    VecFx32 loc1c;
    NpcActor_FindFreeUnitNear(&loc1c, this, &targetPos);
    s32 r = Math_AngleXZ(&position, &targetPos);
    actionCtrl.requestAction(3, 1, 0, 0, 0, r, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketBuyerVillager::mainAct04() {
    if (checkLeave()) {
        return TRUE;
    }
    if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone()) {
            changeAct(3);
        }
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::setupAct05() {
    actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketBuyerVillager::mainAct05() {
    s32 xy[2];
    VecFx32 loc24;
    VecFx32CtorDtor v;
    if (checkLeave()) {
        return TRUE;
    }
    s32 r4 = Vec_DistXZ(&position, &targetPos);
    NpcActor_FindFreeUnitNear(&loc24, this, &targetPos);
    if (r4 > viewDistance + 0x1000) {
        if (actionCtrl.getAction() == 1) {
            actionCtrl.requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (actionCtrl.getAction() == 2) {
            actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    moveCtrl.setWaypoint(&loc24);
    if (r4 <= viewDistance || Vec_Equal(&loc24, &position)) {
        changeAct(3);
    }
    v.x = position.x;
    v.y = position.y;
    v.z = position.z;
    s32 h = (u16)rotY;
    xy[0] = 0;
    xy[1] = 0;
    s32 idx = (h >> 4) * 2;
    s32 g = func_01ffcb0c(0x2000, data_02135f44[idx]);
    v.x = v.x + g;
    g = func_01ffcb0c(0x2000, data_02135f44[idx + 1]);
    v.z = v.z + g;
    FieldPos_ToUnit(&xy[0], &xy[1], &v);
    s32 r4b = FtrActorGrid_GetInstance()->getIndex(xy[0], xy[1], 0);
    s32 r6 = FtrActorGrid_GetInstance()->getIndex(xy[0], xy[1], 1);
    if (isFurnitureForSale(r6)) {
        FtrActor *o = FtrActorTable_GetInstance()->get(r6);
        targetItem = Item_MakeFurniture(FtrActor_GetFtrIndex(o), 0);
        FtrActor_GetCenter(o, &targetPos);
        setViewDistance(o);
        pushViewedFurniture(r6);
        targetFtrIndex = r6;
    } else if (isFurnitureForSale(r4b)) {
        FtrActor *o = FtrActorTable_GetInstance()->get(r4b);
        targetItem = Item_MakeFurniture(FtrActor_GetFtrIndex(o), 0);
        FtrActor_GetCenter(o, &targetPos);
        setViewDistance(o);
        pushViewedFurniture(r4b);
        targetFtrIndex = r4b;
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::setupAct07() {
    void *a = talk.getTalkPlayer();
    s32 b = 0;
    if (a) {
        b = getAngleTo((NpcActor *)a);
    }
    talkCtrl.requestTurnAndTalk(0, b, 1);
    return TRUE;
}

BOOL FleaMarketBuyerVillager::mainAct07() {
    VecFx32CtorDtor v;
    VecFx32 *q = (VecFx32 *)PlayerActor_GetBodyPos(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    if (!talkCtrl.isBusy()) {
        if (visitStage == 5) {
            SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
        } else {
            Scene_SavePlayerPos(Scene_GetWarpRequest(), 0);
            SceneWarp_RequestExit(Scene_GetWarpRequest(), 6);
        }
        changeAct(8);
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::setupAct06() {
    void *a = talk.getTalkPlayer();
    s32 b = 0;
    if (a) {
        b = getAngleTo((NpcActor *)a);
    }
    s32 z = 0;
    leaveTimer = z;
    if (visitStage) {
        talkCtrl.requestTurnAndTalk(z, b, z);
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::mainAct06() {
    u8 s = callTimer;
    if (s != 0) {
        if (s == 1) {
            void *a = talk.getTalkPlayer();
            s32 b = 0;
            if (a) {
                b = getAngleTo((NpcActor *)a);
            }
            talkCtrl.requestTurnAndTalk(0, b, 1);
        }
        Math_CountDownU8(&callTimer);
        return TRUE;
    }
    Clock_GetDateTime(&startTime.dt);
    if (!talkCtrl.isBusy()) {
        TalkRequest_SetTargetDone(this);
        if (visitStage == 1) {
            visitStage = 2;
            doorWaitFrames = 0;
        }
        changeAct(8);
    }
    return TRUE;
}

BOOL FleaMarketBuyerVillager::setupAct08() { return TRUE; }

BOOL FleaMarketBuyerVillager::mainAct08() { return TRUE; }

FleaMarketBuyerVillagerTalk::FleaMarketBuyerVillagerTalk() {}

FleaMarketBuyerVillagerTalk::~FleaMarketBuyerVillagerTalk() {}

void FleaMarketBuyerVillagerTalk::attachOwner(VillagerActor *owner) {
    resetMsg();
    begin(owner, 0x11);
    villager = static_cast<FleaMarketBuyerVillager *>(owner);
}

void FleaMarketBuyerVillagerTalk::update() {
    s32 i = scriptIndex;
    if (sFleaMarketBuyerTalkScripts[i].flag != 0) {
        if (sFleaMarketBuyerTalkScripts[i].fn) {
            (this->*sFleaMarketBuyerTalkScripts[i].fn)();
        }
    }
}

void FleaMarketBuyerVillagerTalk::onTaskDone(u32) {
    s32 i = scriptIndex;
    if (sFleaMarketBuyerTalkScripts[i].flag == 0) {
        if (sFleaMarketBuyerTalkScripts[i].fn) {
            (this->*sFleaMarketBuyerTalkScripts[i].fn)();
            setScript(0);
        }
    }
}

void FleaMarketBuyerVillagerTalk::setScript(s32 v) { scriptIndex = v; }

void FleaMarketBuyerVillagerTalk::offerPrice() {
    TalkWindowState *sp8 = window;
    u16 buf[2];
    ((u8 *)buf)[0] = Random_GlobalBelow(2) + 8;
    offerAmount = 0;
    if (MenuCtrl_IsFinished()) {
        if (MenuCtrl_IsResultOk()) {
            VillagerMemory *r6 = 0;
            s32 r4 = 0;
            u16 *p = &villager->targetItem;
            if (!Unk_ov004_0221946c_Chk(p, &buf[1])) {
                offerAmount = Item_GetPrice(&villager->targetItem);
                if (PlayerData_GetCurrent()) {
                    r6 = Villager_FindMemory(villager->villagerData, PlayerData_GetCurrent()->getPlayerId());
                }
                if (r6) {
                    r4 = r6->getFriendship();
                }
                r4 += 0xff;
                float f;
                if (r4 > 0) {
                    f = 0.5f + (float)(r4 << 12);
                } else {
                    f = (float)(r4 << 12) - 0.5f;
                }
                r4 = FX_Div((s32)f, 0x200000);
                setNumberSlot(MenuCtrl_GetAmount(), 0, 10, 1, 0);
                r4 = func_01ffcb0c(offerAmount, r4);
                if (r4 <= 10) {
                    r4 = 10;
                }
                if (MenuCtrl_GetAmount() > r4) {
                    ((u8 *)buf)[0] = Random_GlobalBelow(2) + 10;
                } else {
                    offerAmount = MenuCtrl_GetAmount();
                    ((u8 *)buf)[0] = Random_GlobalBelow(2) + 12;
                    Hud_Hide();
                }
            }
        }
        ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName((data_ov004_022507b0), 0x28, "ev_fmarket3");
        sp8->setNextMessage((u8 *)buf, data_ov004_022507b0);
        setScript(0);
    }
}

void FleaMarketBuyerVillagerTalk::completePurchase() {
    u16 *p = &villager->targetItem;
    if (!Unk_ov004_02219378_Chk(p)) {
        if (villager->targetFtrIndex != -1) {
            if (((VillagerData *)villager->villagerData)->getVillagerId()) {
                VillagerMemory *t = Villager_GetMemorySlotForNew(((VillagerData *)villager->villagerData)->memories);
                if (t) {
                    t->setReceivedItem(&villager->targetItem);
                }
                Villager_AddReceivedItem((VillagerData *)villager->villagerData, &villager->targetItem);
            }
            FtrMgr_RemoveActorByIndex(villager->targetFtrIndex);
            s32 i = 0;
            s32 m1 = ~i;
            villager->targetFtrIndex = m1;
            villager->targetItem = 0xfff1;
            villager->purchaseCount++;
            for (; i < 100; i++) {
                villager->viewedFurniture[i] = 0xff;
            }
        }
    }
}

void FleaMarketBuyerVillagerTalk::start(TalkStartMsg *out) {
    u16 tmp;
    PlayerId *q = PlayerData_GetCurrent()->getPlayerId();
    VillagerMemory *o = Villager_FindOrCreateMemory(((VillagerData *)villager->villagerData)->memories, q);
    if (o != 0) {
        VillagerMemory_RecordTalk(o, 0, 0, 0);
    }
    FleaMarketBuyerVillager *b = villager;
    u32 st = b->visitStage;
    if (st == 5) {
        ((VillagerData *)b->villagerData)->getVillagerId()->makeFileName((data_ov004_02250800), 0x28, "q10_wait");
        out->msgKey = (const char *)data_ov004_02250800;
        out->msgIndex = Random_GlobalBelow(3);
    } else if (st == 3) {
        ((VillagerData *)b->villagerData)->getVillagerId()->makeFileName((data_ov004_02250800), 0x28, "ev_fmarket3");
        out->msgKey = (const char *)data_ov004_02250800;
        out->msgIndex = Random_GlobalBelow(2) + 2;
    } else {
        switch (st) {
        case 0:
            ((VillagerData *)b->villagerData)->getVillagerId()->makeFileName((data_ov004_02250800), 0x28, "q10_call");
            out->msgIndex = Random_GlobalBelow(3);
            break;
        case 1:
            ((VillagerData *)b->villagerData)->getVillagerId()->makeFileName((data_ov004_02250800), 0x28, "ev_fmarket3");
            out->msgIndex = Random_GlobalBelow(2);
            break;
        case 2: {
            ((VillagerData *)b->villagerData)->getVillagerId()->makeFileName((data_ov004_02250800), 0x28, "ev_fmarket3");
            u16 *p = &villager->targetItem;
            BOOL eq;
            if (Item_IsFurniture(p)) {
                tmp = 0xfff1;
                if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&tmp)) {
                    eq = TRUE;
                } else {
                    eq = FALSE;
                }
            } else {
                if (*p == 0xfff1) {
                    eq = TRUE;
                } else {
                    eq = FALSE;
                }
            }
            if (eq || villager->prevAct == 5) {
                out->msgIndex = Random_GlobalBelow(2) + 4;
            } else {
                setItemNameSlot(&villager->targetItem, 0, 7);
                out->msgIndex = Random_GlobalBelow(2) + 6;
            }
            break;
        }
        }
        out->msgKey = (const char *)data_ov004_02250800;
    }
}

BOOL FleaMarketBuyerVillager::canPlayTalkMelody() {
    if (Unk_ov004_022191cc_Is1(gFieldSceneKind) == 0 || talkMelodyPlayed == 0) {
        return TRUE;
    }
    return FALSE;
}

void FleaMarketBuyerVillager::onTalkMelodyPlayed() {
    talkMelodyPlayed = 1;
}

void FleaMarketBuyerVillagerTalk::onMessageEnd(u32) {
    u8 buf;
    FleaMarketBuyerVillager *b = villager;
    u32 st = b->visitStage;
    if (st == 5 || st == 3) {
        if (st == 5) {
            b->visitStage = 6;
        } else {
            b->visitStage = 4;
        }
        ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName((data_ov004_02250828), 0x28, "q_bye");
        buf = Random_GlobalBelow(3);
        window->setNextMessage(&buf, data_ov004_02250828);
    } else {
        switch (msgIndex) {
        case 0:
        case 1:
        case 2:
            if (st == 6 || st == 1) {
                window->setNextMessage(gTalkMsgIndexEnd, 0);
            } else if (st == 0) {
                PlayerId *q;
                if (PlayerData_GetCurrent() != 0) {
                    q = PlayerData_GetCurrent()->getPlayerId();
                } else {
                    q = 0;
                }
                void *o = villager->villagerData;
                if (o != 0 && q != 0) {
                    Villager_SetFleaMarketVisited(o, q);
                }
                FleaMarketBuyerVillager **pp = &villager;
                (*pp)->visitStage = 1;
                (*pp)->entryTimer = 0x28;
                window->setNextMessage(gTalkMsgIndexEnd, 0);
                villager->changeAct(1);
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 10:
        case 11:
        case 12:
        case 13:
            break;
        case 8:
        case 9:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            Hud_Show();
            break;
        }
    }
}

void FleaMarketBuyerVillagerTalk::clearOffer() {
    villager->targetItem = 0xfff1;
}

void FleaMarketBuyerVillagerTalk::onChoice(u32) {
    u8 buf;
    u16 tmp;
    u32 sel;
    s32 st;
    st = getChoiceList()->getResult();
    sel = 0xff;
    FleaMarketBuyerVillager *b = villager;
    if (b->visitStage == 2) {
        switch (msgIndex) {
        case 6:
        case 7:
        case 10:
        case 11:
            ((VillagerData *)b->villagerData)->getVillagerId()->makeFileName((data_ov004_022507d8), 0x28, "ev_fmarket3");
            if (st == 0) {
                setSubSceneKind(0x38, 0);
                openSubScene(2);
                setScript(1);
            } else {
                sel = (u8)(Random_GlobalBelow(2) + 8);
                clearOffer();
            }
            break;
        case 8:
        case 9:
            break;
        case 12:
        case 13:
            ((VillagerData *)b->villagerData)->getVillagerId()->makeFileName((data_ov004_022507d8), 0x28, "ev_fmarket3");
            if (st == 0) {
                void *r7 = PlayerData_GetCurrent()->getInventory();
                st = NpcActor_CheckPayoutFits(villager, offerAmount, 0);
                tmp = Item_FindMoneyBagForAmount(offerAmount, 0, 0);
                if (tmp == 0xfff1) {
                    tmp = 0x1492;
                }
                if (PlayerInventory_CanAddBells((u8 *)r7, offerAmount, 1, 0) == 0) {
                    sel = (u8)(Random_GlobalBelow(2) + 0x12);
                } else {
                    switch (st) {
                    case 0:
                        requestGiveItem(&tmp, 0, 5, 0);
                        NpcActor_PayPlayer(villager, offerAmount);
                        sel = (u8)(Random_GlobalBelow(2) + 0xe);
                        completePurchase();
                        break;
                    case 1:
                        requestGiveItem(&tmp, 0, 5, 0);
                        sel = (u8)(Random_GlobalBelow(2) + 0xe);
                        NpcActor_PayPlayer(villager, offerAmount);
                        completePurchase();
                        break;
                    case 2:
                        break;
                    }
                }
            } else {
                sel = (u8)(Random_GlobalBelow(2) + 0x10);
                clearOffer();
            }
            break;
        }
        if (sel != 0xff) {
            buf = sel;
            window->setNextMessage(&buf, data_ov004_022507d8);
        }
    }
}

BOOL FleaMarketBuyerVillager::acceptsInteraction(void *) {
    if (talkCtrl.isBusy() == 0) {
        return TRUE;
    }
    return FALSE;
}

BOOL FleaMarketBuyerVillager::acceptsSelfRequestedInteraction(void *) {
    if (talkCtrl.isBusy() == 0) {
        return TRUE;
    }
    return FALSE;
}

void FleaMarketBuyerVillager::onInteractionEvent(u32 cmd, u8 b) {
    switch (cmd) {
    case 1:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        if (visitStage == 5 || visitStage == 3) {
            changeAct(7);
        } else {
            changeAct(6);
        }
        if (visitStage == 0) {
            furnitureCount = FtrActorTable_GetInstance()->countUsed();
            HouseVisitor_SetPresent();
            Ground_LockExit(0);
            FtrMgr_SetSaleMode();
            Clock_GetDateTime(&startTime.dt);
        }
        break;
    case 0:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(6);
        break;
    case 8:
        if (visitStage == 6) {
            VecFx32 rec;
            VecFx32 *src = (VecFx32 *)PlayerActor_GetBodyPos(4);
            rec.x = src->x;
            rec.y = src->y;
            rec.z = src->z;
            if (Ground_IsOnLockedExit(&rec)) {
                Ground_UnlockExit();
                break;
            }
        }
        changeAct(3);
        break;
    }
}

BOOL FleaMarketBuyerVillager::checkLeave() {
    VecFx32 rec;
    ClockDateTimeWords z;
    VecFx32 *src = (VecFx32 *)PlayerActor_GetBodyPos(4);
    rec.x = src->x;
    rec.y = src->y;
    rec.z = src->z;
    if (Ground_IsOnLockedExit(&rec)) {
        visitStage = 5;
        TalkRequest_AddPlayerTalk6(this, 0);
        return TRUE;
    }
    if (TalkRequest_IsActive()) {
        return FALSE;
    }
    {
        if (leaveTimer != 0) {
            leaveTimer = leaveTimer - (TICK_STEP_ENDS() ? 1 : 0);
            if (leaveTimer == 1) {
                visitStage = 3;
                TalkRequest_AddPlayerTalk6(this, 0);
                return TRUE;
            }
        }
    }
    z.words[0] = 0;
    z.words[1] = 0;
    Clock_GetDateTime(&z.dt);
    s32 n = DateTime_DiffMinutes(&startTime.dt, &z.dt);
    {
        if (doorWaitFrames != 0) {
            doorWaitFrames = doorWaitFrames + (TICK_STEP_ENDS() ? 1 : 0);
        }
    }
    if (n >= 0x3c || doorWaitFrames > 0x258) {
        visitStage = 3;
        TalkRequest_AddPlayerTalk6(this, 0);
        return TRUE;
    }
    return FALSE;
}

BOOL FleaMarketBuyerVillager::pickFurnitureToView() {
    if (!Unk_ov004_02218a48_Eq(&targetItem, 0xfff1)) {
        return TRUE;
    }
    if (furnitureCount == 0 || purchaseCount >= 3) {
        if (leaveTimer == 0) {
            leaveTimer = 0x258;
        }
        return FALSE;
    }
    s32 start = Random_GlobalBelow(furnitureCount);
    s32 i = start;
    do {
        if (isFurnitureForSale(i)) {
            FtrActor *e = FtrActorTable_GetInstance()->get(i);
            targetItem = Item_MakeFurniture(FtrActor_GetFtrIndex(e), 0);
            FtrActor_GetCenter(e, &targetPos);
            setViewDistance(e);
            pushViewedFurniture(i);
            targetFtrIndex = i;
            goto ok;
        }
        i++;
        if (i >= furnitureCount) {
            i = 0;
        }
    } while (i != start);
    if (leaveTimer == 0) {
        leaveTimer = 0x258;
    }
    return FALSE;
ok:
    return TRUE;
}

BOOL FleaMarketBuyerVillager::isFurnitureForSale(s32 idx) {
    u16 v;
    FtrActor *p = FtrActorTable_GetInstance()->get(idx);
    if (p == 0) {
        return FALSE;
    }
    if (FtrMgr_IsPickableByIndex(idx) == 0) {
        return FALSE;
    }
    v = Item_MakeFurniture(FtrActor_GetFtrIndex(p), 0);
    BOOL r0 = FALSE;
    volatile u16 *pv = &v;
    u32 w = *pv;
    u32 w2 = *pv;
    if (w2 >= 0x3d84 && w <= 0x3e03) {
        r0 = TRUE;
    }
    if (r0 || (w >= 0x3ea4 && w <= 0x3f23) || (w >= 0x4224 && w <= 0x42a3) ||
        (w >= 0x3f24 && w <= 0x3fa3) || Unk_ov004_02218a48_Eq(&v, 0x409c) || Unk_ov004_02218a48_Eq(&v, 0x40a0) ||
        Unk_ov004_02218a48_Eq(&v, 0x3820)) {
        return FALSE;
    }
    {
        s32 i;
        for (i = 0; i < 100; i++) {
            if (idx == viewedFurniture[i]) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

void FleaMarketBuyerVillager::pushViewedFurniture(u32 v) {
    s32 i;
    for (i = 0; i < 99; i++) {
        viewedFurniture[i] = viewedFurniture[i + 1];
    }
    viewedFurniture[99] = v;
}

void FleaMarketBuyerVillager::setViewDistance(FtrActor *arg) {
    switch (FtrInfo_GetUnk05(FtrActor_GetFtrIndex(arg))) {
    case 0:
        viewDistance = 0x3000;
        break;
    case 1:
        viewDistance = 0x4000;
        break;
    case 2:
        viewDistance = 0x4000;
        break;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02218988) {
    HOST_OVERLAY_VAR(sFleaMarketBuyerVillagerProfile),
    HOST_OVERLAY_VAR(data_ov004_02250828),
    HOST_OVERLAY_VAR(data_ov004_022507b0),
    HOST_OVERLAY_VAR(data_ov004_022507d8),
    HOST_OVERLAY_VAR(data_ov004_02250800),
    HOST_OVERLAY_VAR(sFleaMarketBuyerTalkScripts),
    HOST_OVERLAY_VAR(sFleaMarketBuyerActTable),
    HOST_OVERLAY_VARS_END
};
