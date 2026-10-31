#include "uptr.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "game/TouchPicker.h"
#include "talk/TalkStartMsg.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "save/Pattern.h"
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
#include "net/CommManager.h"
#include "item/ItemName.h"
#include "npc/NpcActionCtrl.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveCtrl.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "save/PatternOrder.h"
#include "talk/ChoiceList.h"
#include "talk/TalkWindowState.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b5e5c.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov004/unk_ov004_0223e9bc.h"
#include "proto/ov049/unk_ov049_02258de0.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "game/FxVec3.h"
#include "town/BlockMap.h"
#include "save/SaveData.h"
#include "player/PlayerErrands.h"
#include "room/FtrActorGrid.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_0204cc1c.h"

extern SaveData gSaveData;

class SpNpcMabel;
class SpNpcMabelTalk;

struct PlayerIdInlineCopy;
struct TownIdInlineCopy;

struct SpNpcMabelChoiceMenu {
    const u8 *choices;
    u8 count;
};

extern "C" {
extern CommManager *gCommManager;
extern u16 gPad[];
extern s16 data_02135f44[];
extern u8 gU8None[];
extern s32 data_020c6d1c;
extern u16 data_020c6cc8;
extern s16 data_020c6cc0;
extern BlockMap *gSceneBlockMap;

s32 Math_AngleDiffAbs(s32 a, s32 b);
u8 Math_CountDownU8(u8 *p);
u16 Math_CountDownU16(u16 *p);

BOOL Ground_IsOnLockedExit(VecFx32 *p);
BOOL TalkRequest_AddPlayerTalk6(NpcActor *self, s32 a);
s32 TalkRequest_IsActive();
BOOL TalkRequest_SetTargetDone(NpcActor *self);
s32 func_01ffcb0c(s32 a, s32 b);
BOOL TouchPick_GetGroundPos(TouchPickResult *a, VecFx32 *b);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
void Item_FromPlacedForm(u16 *a, u16 *b);
s32 Item_GetPrice(u16 *p);
BOOL func_0204bab8(u16 *);
void AbleShop_BuyAt(s32 a, s32 b, s32 c);
BOOL AbleShop_IsPurchaseSynced();
s32 VillagerTrend_OnClothesBought();
s32 Talk_IsInOwnTown();
BOOL Talk_IsDramaPending(void *owner, void *buf, s32 n);
void Talk_AdvanceDrama(void *, void *);
BOOL Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
void Camera_RestorePrevMode();
void Camera_SetMode4();
u32 strlen(const char *s);
s32 strncmp(const char *a, const char *b, u32 n);
void NpcActor_FindFreeUnitNear(VecFx32 *out, NpcActor *self, VecFx32 *v);
BOOL Scene_GetPrevious();
void Ground_LockExit(s32 a);
}

struct TownIdInlineCopy {
    u16 id;
    EncodedName8 name;
    TownIdInlineCopy(const TownIdInlineCopy &o) {
        id = o.id;
        name = o.name;
    }
};

struct PlayerIdInlineCopy {
    u16 id0;
    EncodedName8 name0;
    u16 id1;
    EncodedName8 name1;
    s8 gender;
    u8 pad_15;
    PlayerIdInlineCopy(const PlayerIdInlineCopy &o) {
        id0 = o.id0;
        name0 = o.name0;
        id1 = o.id1;
        name1 = o.name1;
        gender = o.gender;
        pad_15 = o.pad_15;
    }
};





class SpNpcMabelTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcMabelTalk::*Fn)(u32);
    typedef void (SpNpcMabelTalk::*Fn0)();

    SpNpcMabelTalk();
    virtual ~SpNpcMabelTalk();
    virtual void onMessageEnd(u32 a);
    virtual void onChoice(u32 a);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void sellItemToPlayer();
    void openChoiceMenu(void *rec, s32 x);
    void onDeliveryItemChosen();
    void restoreTryOnDisplay();
    void waitTryOnDone();
    void onSellItemsChosen();
    void onTradePatternChosen();
    void onTakePatternChosen();
    void onDisplayPatternChosen();
    void onDesignNamed();
    void onDesignEditorDone();
    void setScript(s32 v);
    void onDramaMenuChoice();
    void onDeliveryChoice(u32 v);
    void onTryOnChoice(u32 v);
    void onItemPriceChoice(u32 v);
    void onDisposeChoice(u32 v);
    void onSellPriceChoice(u32 v);
    void onDesignConceptChoice(u32 a);
    void onDesignFeeChoice(u32 a);
    void onMenuChoice(u32 a);
    void dispatchShopChoice();
    void onOtherMessageEnd();
    void startTradePatternSelect();
    void startTakePatternSelect();
    void startDisplayPatternSelect();
    void openItemChoices();
    void payForSoldItems();
    void startSellItemSelect();
    void chargeDesignFee();
    void startDesignNameEntry();
    void startDesignEditor();
    void dispatchShopMessageEnd();
    s32 getTopic();
    void setTopic(s32 v);
    void attachOwner(SpNpcMabel *o);

    /* 0xac */ SpNpcMabel *owner;
    /* 0xb0 */ s32 topic;
    /* 0xb4 */ s32 script;
    /* 0xb8 */ s32 price;
    /* 0xbc */ s32 soldCount;
    /* 0xc0 */ u8 pad_c0[0xcc - 0xc0];
};









class SpNpcMabel : public SpNpcActor {
public:
    typedef BOOL (SpNpcMabel::*Fn)();

    SpNpcMabel() : selectedItemX(0), selectedItemZ(0), selectedItem(0xfff1) {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 cmd, u8 arg);
    virtual BOOL acceptsSelfRequestedInteraction(void *a);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual void onJoinTalk();
    virtual void onLeaveTalk();

    BOOL tryStartFarewellTalk();
    BOOL tryStartShopItemTalk();
    BOOL pickShopItemAtPlayer();
    void setDesignConcept(u32 y);
    BOOL mainAct0F();
    BOOL setupAct0F();
    BOOL mainAct0E();
    BOOL setupAct0E();
    BOOL mainAct0D();
    BOOL setupAct0D();
    BOOL mainAct0C();
    BOOL setupAct0C();
    BOOL mainAct0B();
    BOOL setupAct0B();
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

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcMabelTalk talk;
    /* 0x724 */ s32 selectedItemX;
    /* 0x728 */ s32 selectedItemZ;
    /* 0x72c */ u8 pad_72c[0x730 - 0x72c];
    /* 0x730 */ u16 tryOnPrevItem;
    /* 0x732 */ u16 tryOnRemovedItem;
    /* 0x734 */ u16 selectedItem;
    /* 0x736 */ u8 pad_736[2];
    /* 0x738 */ Pattern pattern;
    /* 0x960 */ u16 dramaTimer;
    /* 0x962 */ u16 standBlend;
    /* 0x964 */ u8 purchasePending;
    /* 0x965 */ u8 dramaPending;
    /* 0x966 */ u8 patternSlot;
    /* 0x967 */ u8 approachTimer;
};

struct SpNpcMabelActEntry {
    BOOL (SpNpcMabel::*enter)();
    BOOL (SpNpcMabel::*exit)();
};

struct SpNpcMabelTalkScript {
    SpNpcMabelTalk::Fn0 fn;
    u8 flag;
    u8 pad[3];
};

struct SpNpcMabelChoiceHandler {
    u32 id;
    SpNpcMabelTalk::Fn fn;
};

struct SpNpcMabelMessageEndHandler {
    u32 id;
    SpNpcMabelTalk::Fn0 fn;
};


extern "C" {
extern const u8 sSpNpcMabelDramaMenuMsgs[8];
extern const u8 sSpNpcMabelTopicMsgs[8];
extern const u8 sSpNpcMabelDramaMsgTable[28];
extern const u32 sSpNpcMabelDesignConcepts[10];
extern SpNpcMabelChoiceMenu sSpNpcMabelItemChoiceMenus[4];
extern SpNpcMabelTalkScript sSpNpcMabelTalkScripts[10];
extern SpNpcMabelActEntry sSpNpcMabelActTable[16];
}


extern "C" u8 data_ov049_0225ba48[4];
extern "C" const u8 sSpNpcMabelTopicMsgs[8];
extern "C" char sSpNpcMabelSequence4Key[];
extern "C" char sSpNpcMabelDramaKey[];
extern "C" u8 data_ov049_0225ba44[4];
extern "C" char *sSpNpcMabelMsgKeys[3];
extern "C" u8 data_ov049_0225ba4c[4];
extern "C" char sSpNpcMabelModelPath[];
extern "C" SpNpcMabelChoiceMenu sSpNpcMabelItemChoiceMenus[4];
extern "C" char sSpNpcMabelTexturePath[];
extern "C" u8 data_ov049_0225ba40[4];
extern "C" const u8 sSpNpcMabelDramaMenuMsgs[8];
extern "C" const u32 sSpNpcMabelDesignConcepts[10];
extern "C" SpNpcMabelTalkScript sSpNpcMabelTalkScripts[10];
extern "C" char sSpNpcMabelKey[];
extern "C" SpNpcMabelActEntry sSpNpcMabelActTable[16];
extern "C" const u8 sSpNpcMabelDramaMsgTable[28];
extern "C" ActorProfile sSpNpcMabelProfile;

extern "C" u8 data_ov049_0225ba48[4] = {0xd3, 0xe3, 0xd0, 0x00};

extern "C" const u8 sSpNpcMabelTopicMsgs[8] = {0x00, 0x01, 0x04, 0x02, 0x28, 0x31, 0x00, 0x00};

extern "C" char sSpNpcMabelSequence4Key[] = "sp_etc_sequence4";

extern "C" char sSpNpcMabelDramaKey[] = "sp_npc_drama4";





static inline BOOL Unk_ov049_02258ee0_Flags() {
    if (gTouchPrevHeld && gTouchPrevChanged) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov049_02258ee0_Eq(u16 *p, u16 *k) {
    if (Item_IsFurniture(p)) {
        *k = 0xfff1;
        s32 a = Item_GetFurnitureIndex(p);
        if (a == Item_GetFurnitureIndex(k)) return TRUE;
        return FALSE;
    }
    if (*p == 0xfff1) return TRUE;
    return FALSE;
}


static inline BOOL Unk_ov049_02259774_R(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov049_02259dd8_VR(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 h = *p;
    u32 l = *p;
    if (l >= lo && h <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov049_0225a434_R2(SpNpcMabel *o, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (o->selectedItem >= lo && o->selectedItem <= hi) {
        r = TRUE;
    }
    return r;
}

struct Unk_ov049_0225a714_Bits {
    u8 lo : 2;
    u8 mid : 3;
    u8 hi : 3;
};

extern "C" SpNpcMabel *SpNpcMabel_Create() { return new SpNpcMabel; }

BOOL SpNpcMabel::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    setColliderSize(0x119a, 0x2000);
    setCollisionRadius(0xf00);
    standBlend = data_020c6cc8;
    moveCtrl.setSpeedPreset(2, 0x333, 0xcc, 0x133);
    return TRUE;
}

BOOL SpNpcMabel::onCreate() {
    s32 v;
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    if (gCommManager->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
        if (NetArea_IsLocalOwner()) {
            collider.groups |= 2;
            position.x = 0xd000;
            position.z = 0x19000;
            rotY = 0;
            moveAngleY = 0;
            changeAct(10);
        } else {
            collider.groups |= 2;
            changeAct(8);
        }
    } else {
        if (Scene_GetPrevious() == 0) {
            changeAct(0);
        } else {
            changeAct(1);
        }
        Ground_LockExit(0);
        if (Talk_IsDramaPending(this, &v, 2)) {
            dramaPending = 1;
        }
    }
    return TRUE;
}

u8 *SpNpcMabel::getTexturePath() { return (u8 *)sSpNpcMabelTexturePath; }

u8 *SpNpcMabel::getModelPath() { return (u8 *)sSpNpcMabelModelPath; }

BOOL SpNpcMabel::updateAct() {
    BOOL r = FALSE;
    if (((SpNpcMabelActEntry *)&sSpNpcMabelActTable[0].exit)[act].enter) {
        r = (this->*sSpNpcMabelActTable[act].exit)();
    }
    return r;
}

void SpNpcMabel::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcMabelActTable[state].enter) {
        ok = (this->*sSpNpcMabelActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcMabel::setupAct00() {
    if (Talk_CheckAndSetPlayerFlag(0xf, 1)) {
        talk.setTopic(1);
    } else {
        talk.setTopic(0);
    }
    return TRUE;
}

BOOL SpNpcMabel::mainAct00() {
    TalkRequest_AddPlayerTalk6(this, 0);
    return TRUE;
}


BOOL SpNpcMabel::setupAct01() {
    s32 v;
    actionCtrl.requestStand(1, standBlend);
    standBlend = data_020c6cc8;
    dramaTimer = Random_GlobalBelow(5) * 20 + 100;
    if (Talk_IsDramaPending(this, &v, 2)) {
        dramaPending = 1;
    } else {
        dramaPending = 0;
    }
    return TRUE;
}

BOOL SpNpcMabel::mainAct01() {
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    s32 r6 = getDistanceToPlayer(4);
    s32 t = getAngleToPlayer(4);
    s32 r4 = Math_AngleDiffAbs(rotY, t);
    gSceneBlockMap->getWalkLinksAtPos(&position);
    if (r6 > 0x5000 && Vec_NotEqual(&out, &position)) {
        changeAct(3);
    } else if (r4 > 0x2000) {
        changeAct(2);
    }
    if (tryStartFarewellTalk()) {
        return TRUE;
    }
    if (tryStartShopItemTalk()) {
        return TRUE;
    }
    if (dramaPending != 0) {
        if (Math_CountDownU16(&dramaTimer) == 0) {
            changeAct(7);
        }
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct02() {
    actionCtrl.requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcMabel::mainAct02() {
    if (tryStartFarewellTalk()) {
        return TRUE;
    }
    if (tryStartShopItemTalk()) {
        return TRUE;
    }
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    s32 r6 = getDistanceToPlayer(4);
    s32 r4 = getAngleToPlayer(4);
    Math_AngleDiffAbs(rotY, r4);
    gSceneBlockMap->getWalkLinksAtPos(&position);
    if (r6 > 0x5000) {
        if (Vec_NotEqual(&out, &position)) {
            changeAct(3);
        }
    }
    moveCtrl.setTargetAngle(r4);
    if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone()) {
            changeAct(1);
        }
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct03() {
    actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcMabel::mainAct03() {
    if (tryStartFarewellTalk()) {
        return TRUE;
    }
    if (tryStartShopItemTalk()) {
        return TRUE;
    }
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    s32 t = getDistanceToPlayer(4);
    gSceneBlockMap->getWalkLinksAtPos(&position);
    if (t > 0x6000) {
        if (actionCtrl.getAction() == 1) {
            actionCtrl.requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (actionCtrl.getAction() == 2) {
            actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    moveCtrl.setWaypoint(&out);
    if (t <= 0x5000 || Vec_Equal(&out, &position) != 0) {
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct04() {
    NpcActor *p = (NpcActor *)talk.getTalkPlayer();
    s32 r = 0;
    if (p) {
        r = getAngleTo(p);
    }
    talkCtrl.requestTurnAndTalk(0, r, 0);
    return TRUE;
}

BOOL SpNpcMabel::mainAct04() {
    if (talkCtrl.isBusy()) {
        return TRUE;
    }
    if (purchasePending != 0 && AbleShop_IsPurchaseSynced() == 0) {
        return TRUE;
    }
    TalkRequest_SetTargetDone(this);
    changeAct(6);
    return TRUE;
}

BOOL SpNpcMabel::setupAct05() {
    NpcActor *p = (NpcActor *)talk.getTalkPlayer();
    s32 r = 0;
    if (p) {
        r = getAngleTo(p);
    }
    talkCtrl.requestTurnAndTalk(0, r, 1);
    return TRUE;
}

BOOL SpNpcMabel::mainAct05() {
    if (talkCtrl.isBusy() == 0) {
        SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
        changeAct(6);
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct06() { return TRUE; }

BOOL SpNpcMabel::mainAct06() { return TRUE; }

BOOL SpNpcMabel::setupAct07() {
    actionCtrl.requestAction(0xa, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcMabel::mainAct07() {
    if (tryStartFarewellTalk()) {
        return TRUE;
    }
    if (tryStartShopItemTalk()) {
        return TRUE;
    }
    if (actionCtrl.getAction() == 0xa) {
        if (actionCtrl.isActionDone()) {
            standBlend = 0x18;
            changeAct(1);
        }
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct08() { return TRUE; }

BOOL SpNpcMabel::mainAct08() {
    if (isNetOwner()) {
        s32 a = 4;
        s32 b = 4;
        u32 x, t;
        if (netGetSlots(&a, &b) && ((x = a), x == (t = gCommManager->myAid)) && x == b) {
            netSetSlotsIfOwner(1, t, t);
            talk.resetMsg();
            talk.setTalkPlayer(getPlayerActor(4));
            BOOL r;
            if (Item_IsFurniture(&selectedItem)) {
                u16 tmp = 0xfff1;
                s32 p = Item_GetFurnitureIndex(&selectedItem);
                if (p == Item_GetFurnitureIndex(&tmp)) {
                    r = TRUE;
                } else {
                    r = FALSE;
                }
            } else {
                if (selectedItem == 0xfff1) {
                    r = TRUE;
                } else {
                    r = FALSE;
                }
            }
            if (r) {
                talk.setTopic(2);
            }
            changeAct(4);
        } else if (NetArea_IsLocalOwner() && b == 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(0xa);
        }
    } else {
        tryStartShopItemTalk();
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct09() { return TRUE; }

BOOL SpNpcMabel::mainAct09() {
    if (isNetOwner()) {
        s32 a = 4;
        s32 b = 4;
        if (netGetSlots(&a, &b) && a == 4 && NetArea_IsLocalOwner()) {
            netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(0xa);
        }
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct0A() {
    actionCtrl.requestStand(1, standBlend);
    return TRUE;
}

BOOL SpNpcMabel::mainAct0A() {
    s32 t = getAngleToPlayer(4);
    if (Math_AngleDiffAbs(rotY, t) >= data_020c6cc0) {
        changeAct(0xb);
    } else {
        tryStartShopItemTalk();
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct0B() {
    s32 f = getAngleToPlayer(4);
    actionCtrl.requestAction(3, 1, 0, 0, 0, f, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcMabel::mainAct0B() {
    if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone()) {
            changeAct(0xa);
        }
    }
    return TRUE;
}

BOOL SpNpcMabel::setupAct0C() { return TRUE; }

BOOL SpNpcMabel::mainAct0C() { return TRUE; }

BOOL SpNpcMabel::setupAct0D() {
    approachTimer = 0x32;
    actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcMabel::mainAct0D() {
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    VecFx32 out;
    NpcActor_FindFreeUnitNear(&out, this, &v);
    s32 t = getDistanceToPlayer(4);
    gSceneBlockMap->getWalkLinksAtPos(&position);
    if (t > 0x6000) {
        if (actionCtrl.getAction() == 1) {
            actionCtrl.requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (actionCtrl.getAction() == 2) {
            actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    moveCtrl.setWaypoint(&out);
    if (t <= 0x5000 || Vec_Equal(&out, &position) != 0 || Math_CountDownU8(&approachTimer) == 0) {
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(4);
    }
    return TRUE;
}

void SpNpcMabel::onJoinTalk() { changeAct(0xe); }

void SpNpcMabel::onLeaveTalk() {
    lookAt.setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    changeAct(1);
}

BOOL SpNpcMabel::setupAct0E() { return setupAct01(); }

BOOL SpNpcMabel::mainAct0E() { return TRUE; }

BOOL SpNpcMabel::setupAct0F() {
    actionCtrl.requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}


BOOL SpNpcMabel::mainAct0F() {
    if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone()) {
            actionCtrl.requestStand(1, standBlend);
        }
    }
    moveCtrl.setTargetAngle(getAngleToPlayer(4));
    TalkRequest_AddPlayerTalk6(this, 0);
    return TRUE;
}

SpNpcMabelTalk::SpNpcMabelTalk() {}

SpNpcMabelTalk::~SpNpcMabelTalk() {}

void SpNpcMabelTalk::attachOwner(SpNpcMabel *o) {
    resetMsg();
    owner = o;
}

void SpNpcMabelTalk::setTopic(s32 v) { topic = v; }


s32 SpNpcMabelTalk::getTopic() { return topic; }

void SpNpcMabelTalk::start(TalkStartMsg *out) {
    PlayerData *r7 = PlayerData_GetCurrent();
    ParcelErrand *r6 = &(r7->getErrands())->parcelErrand;
    u8 buf[4];
    if (GameStart_IsActive() != 0 && getTopic() == 2) {
        out->msgKey = (const char *)sSpNpcMabelMsgKeys[2];
        out->msgIndex = 6;
        return;
    }
    if (getTopic() == 2 && ParcelErrand_IsFor(r6, &owner->npcHandle) != 0) {
        out->msgIndex = 0x2e;
        out->msgKey = (const char *)sSpNpcMabelMsgKeys[0];
        return;
    }
    if (getTopic() == 2 && Talk_IsDramaPending(owner, buf, 2) != 0) {
        owner->dramaPending = 1;
        Unk_ov049_0225a714_Bits *b = (Unk_ov049_0225a714_Bits *)buf;
        out->msgIndex = *(sSpNpcMabelDramaMsgTable + b->mid * 7 + b->hi);
        out->msgKey = (const char *)sSpNpcMabelMsgKeys[1];
        return;
    }
    out->msgIndex = sSpNpcMabelTopicMsgs[topic];
    out->msgKey = (const char *)sSpNpcMabelMsgKeys[0];
    if (getTopic() == 4) {
        price = (s32)Item_GetPrice(&owner->selectedItem);
        setNumberSlot(price, 0, 0xa, 1, 0);
        setItemNameSlot(&owner->selectedItem, 0, 7);
        if (GameStart_IsActive() != 0) {
            out->msgKey = (const char *)sSpNpcMabelMsgKeys[2];
            out->msgIndex = 0x1e;
        }
    } else if (getTopic() == 5) {
                SpNpcMabel *o = owner;
        BOOL f = FALSE;
        if (o->selectedItem >= 0x3e04 && o->selectedItem <= 0x3e23) {
            f = TRUE;
        }
        u32 v = o->selectedItem;
        s32 t;
        if (f) {
            t = (s32)(v - 0x3e04) >> 2;
        } else {
            t = -1;
        }
        owner->patternSlot = t;
        void *q6 = ((AbleSistersPatterns *)gSaveData.ableSistersPatterns)->getPattern(owner->patternSlot);
        ItemName q;
        ((PatternInfo *)(((Pattern *)(q6))->getInfo()))->getTitle(&q);
        window->setNamedSlot(2, &q, 7);
        PlayerIdInlineCopy a(*(const PlayerIdInlineCopy *)((Pattern *)(q6))->getInfo()->getAuthor());
        PlayerIdInlineCopy b(*(const PlayerIdInlineCopy *)r7->getPlayerId());
        TownIdInlineCopy c(*(const TownIdInlineCopy *)PlayerId_GetTownId(&a));
        TownIdInlineCopy d(*(const TownIdInlineCopy *)PlayerId_GetTownId(&b));
        if (GameStart_IsActive() != 0) {
            out->msgKey = (const char *)sSpNpcMabelMsgKeys[2];
            out->msgIndex = 0x1d;
        } else if (c.id != d.id || memcmp(&c.name, &d.name, 8) != 0) {
            setPlayerNameSlot((PlayerId *)&a, 2);
            setTownNameSlot(&c, 3);
            out->msgIndex = 0x33;
        } else if (a.id0 == b.id0 && memcmp(&a.name0, &b.name0, 8) == 0 && ((PlayerId *)(void *)(&a))->equals((PlayerId *)(void *)(&b)) != 0) {
        } else {
            setPlayerNameSlot((PlayerId *)&a, 2);
            out->msgIndex = 0x32;
        }
        TownId_Destruct();
        TownId_Destruct();
        new (&b) PlayerId();
        new (&a) PlayerId();
    }
}

void SpNpcMabelTalk::onMessageEnd(u32 a) {
    if (getTopic() != 2 || !GameStart_IsActive()) {
        static SpNpcMabelTalk::Fn0 tbl[2] = {
            &SpNpcMabelTalk::dispatchShopMessageEnd,
            &SpNpcMabelTalk::onOtherMessageEnd,
        };
        char *s = sSpNpcMabelMsgKeys[0];
        u32 n = strlen(s);
        BOOL r;
        if (strncmp(fileName, s, n) != 0) {
            r = TRUE;
        } else {
            r = FALSE;
        }
        (this->*tbl[r])();
    }
}

extern "C" u8 data_ov049_0225ba44[4] = {0xd3, 0xe2, 0xd0, 0x00};

extern "C" char *sSpNpcMabelMsgKeys[3] = {sSpNpcMabelKey, sSpNpcMabelDramaKey, sSpNpcMabelSequence4Key};

extern "C" u8 data_ov049_0225ba4c[4] = {0xd3, 0xe1, 0xd0, 0x00};

void SpNpcMabelTalk::dispatchShopMessageEnd() {
    static SpNpcMabelMessageEndHandler tbl[9] = {
        {0xe, &SpNpcMabelTalk::startDesignEditor},
        {0x11, &SpNpcMabelTalk::startDesignNameEntry},
        {0x12, &SpNpcMabelTalk::chargeDesignFee},
        {0x14, &SpNpcMabelTalk::startSellItemSelect},
        {0x1e, &SpNpcMabelTalk::payForSoldItems},
        {0x28, &SpNpcMabelTalk::openItemChoices},
        {0x36, &SpNpcMabelTalk::startDisplayPatternSelect},
        {0x26, &SpNpcMabelTalk::startTakePatternSelect},
        {0x23, &SpNpcMabelTalk::startTradePatternSelect},
    };
    u32 i = 0;
    u8 *idp = &msgIndex;
    goto test0;
loop0:
    u32 id;
    id = tbl[i].id;
    if (id == *idp) {
        (this->*tbl[i].fn)();
    }
    i++;
test0:
    if (i < 9) goto loop0;
}

void SpNpcMabelTalk::startDesignEditor() {
    setSubSceneKind(4, 0);
    openSubScene(2);
    setScript(1);
}

void SpNpcMabelTalk::startDesignNameEntry() {
    setSubSceneKind(0xb, 0);
    openSubScene(2);
    setScript(2);
}

void SpNpcMabelTalk::chargeDesignFee() {
    NpcActor_ChargePlayer(owner, 0x15e);
}

void SpNpcMabelTalk::startSellItemSelect() {
    setSubSceneKind(0x1e, 0);
    openSubScene(2);
    setScript(6);
}

void SpNpcMabelTalk::payForSoldItems() {
    NpcActor_PayPlayer(owner, price);
}

void SpNpcMabelTalk::openItemChoices() {
    BOOL f = Unk_ov049_0225a434_R2(owner, 0x11a8, 0x12a7);
    u32 v = owner->selectedItem;
    if (f) {
        openChoiceMenu(sSpNpcMabelItemChoiceMenus, sSpNpcMabelItemChoiceMenus[0].count - 1);
    } else if ((v >= 0x13c8 && v <= 0x1407) || (v >= 0x13a8 && v <= 0x13c7)) {
        openChoiceMenu(&sSpNpcMabelItemChoiceMenus[1], sSpNpcMabelItemChoiceMenus[1].count - 1);
    } else if (v >= 0x1431 && v <= 0x1470) {
        openChoiceMenu(&sSpNpcMabelItemChoiceMenus[2], sSpNpcMabelItemChoiceMenus[2].count - 1);
    } else if (v >= 0x1380 && v <= 0x139f) {
        openChoiceMenu(&sSpNpcMabelItemChoiceMenus[3], sSpNpcMabelItemChoiceMenus[3].count - 1);
    }
}

void SpNpcMabelTalk::startDisplayPatternSelect() {
    setSubSceneKind(5, 0);
    openSubScene(2);
    setScript(3);
}

void SpNpcMabelTalk::startTakePatternSelect() {
    setSubSceneKind(7, 0);
    openSubScene(2);
    setScript(4);
}

void SpNpcMabelTalk::startTradePatternSelect() {
    setSubSceneKind(8, 0);
    openSubScene(2);
    setScript(5);
}

void SpNpcMabelTalk::onOtherMessageEnd() {}

extern "C" char sSpNpcMabelModelPath[] = "npc_sp/model/hgh.nsbmd";

extern "C" SpNpcMabelChoiceMenu sSpNpcMabelItemChoiceMenus[4] = {
    {data_ov049_0225ba4c, 3},
    {data_ov049_0225ba44, 3},
    {data_ov049_0225ba48, 3},
    {data_ov049_0225ba40, 2},
};

void SpNpcMabelTalk::onChoice(u32 a) {
    if (getTopic() != 2 || !GameStart_IsActive()) {
        static SpNpcMabelTalk::Fn0 tbl[2] = {
            &SpNpcMabelTalk::dispatchShopChoice,
            &SpNpcMabelTalk::onDramaMenuChoice,
        };
        char *s = sSpNpcMabelMsgKeys[0];
        u32 n = strlen(s);
        BOOL r;
        if (strncmp(fileName, s, n) != 0) {
            r = TRUE;
        } else {
            r = FALSE;
        }
        (this->*tbl[r])();
    }
}

extern "C" char sSpNpcMabelTexturePath[] = "npc_sp/model/hgh_tex.nsbtx";

extern "C" u8 data_ov049_0225ba40[4] = {0xd3, 0xd0, 0x00, 0x00};

extern "C" const u8 sSpNpcMabelDramaMenuMsgs[8] = {0x0b, 0x14, 0x00, 0x05, 0x06, 0x00, 0x00, 0x00};

extern "C" const u32 sSpNpcMabelDesignConcepts[10] = {8, 2, 6, 3, 4, 9, 1, 0, 5, 7};

void SpNpcMabelTalk::dispatchShopChoice() {
    static SpNpcMabelChoiceHandler tbl[11] = {
        {4, &SpNpcMabelTalk::onMenuChoice},
        {0x15, &SpNpcMabelTalk::onMenuChoice},
        {0x1a, &SpNpcMabelTalk::onMenuChoice},
        {0xb, &SpNpcMabelTalk::onDesignFeeChoice},
        {0x10, &SpNpcMabelTalk::onDesignConceptChoice},
        {0x1b, &SpNpcMabelTalk::onSellPriceChoice},
        {0x17, &SpNpcMabelTalk::onDisposeChoice},
        {0x28, &SpNpcMabelTalk::onItemPriceChoice},
        {0x2d, &SpNpcMabelTalk::onTryOnChoice},
        {0x2e, &SpNpcMabelTalk::onDeliveryChoice},
        {0x38, &SpNpcMabelTalk::onMenuChoice},
    };
    u32 i = 0;
    u8 *idp = &msgIndex;
    goto test0;
loop0:
    u32 id;
    id = tbl[i].id;
    if (id == *idp) {
        u32 arg = window->getChoiceList()->getResult();
        (this->*tbl[i].fn)(arg);
    }
    i++;
test0:
    if (i < 0xb) goto loop0;
}

void SpNpcMabelTalk::onMenuChoice(u32 a) {
    u8 buf[2];
    void *g = gCommManager;
    if (((CommManager *)(g))->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0) {
        if (a == 2) {
            buf[0] = 0x1c;
            window->setNextMessage((u8 *)(&buf[0]), sSpNpcMabelMsgKeys[0]);
        } else if (a == 0) {
            buf[1] = 0x37;
            window->setNextMessage((u8 *)(&buf[1]), sSpNpcMabelMsgKeys[0]);
        }
    }
    if (((CommManager *)(g))->isOnline() == 0 && *DebugVar_GetPtr(0, 0x4a) == 0) {
        NpcActor *r = NpcRegistry_FindSpNpc(5);
        if (r != NULL) {
            setPartnerActor(r);
        }
    }
}

void SpNpcMabelTalk::onDesignFeeChoice(u32 a) {
    u8 buf[2];
    if (a == 0) {
        if (NpcActor_CanPlayerPay(owner, 0x15e) == 0) {
            buf[0] = 0xd;
            window->setNextMessage((u8 *)(&buf[0]), sSpNpcMabelMsgKeys[0]);
        } else {
            buf[1] = 0xe;
            window->setNextMessage((u8 *)(&buf[1]), sSpNpcMabelMsgKeys[0]);
        }
    }
}


void SpNpcMabelTalk::onDesignConceptChoice(u32 a) {
    s32 idx = 0;
    switch (a) {
    case 0:
        idx = Random_GlobalBelow(3);
        break;
    case 1:
        idx = Random_GlobalBelow(3) + 3;
        break;
    case 2:
        idx = Random_GlobalBelow(4) + 6;
        break;
    }
    owner->setDesignConcept(sSpNpcMabelDesignConcepts[idx]);
}

void SpNpcMabelTalk::onSellPriceChoice(u32 v) {
    u8 m[3];
    switch (v) {
    case 0:
        switch (NpcActor_CheckPayoutFits(owner, price, soldCount)) {
        case 0:
            NpcActor_PayPlayer(owner, price);
            m[0] = 0x1a;
            window->setNextMessage((u8 *)(m), sSpNpcMabelMsgKeys[0]);
            break;
        case 1:
            m[1] = 0x1e;
            window->setNextMessage((u8 *)(&m[1]), sSpNpcMabelMsgKeys[0]);
            break;
        case 2:
            m[2] = 0x38;
            window->setNextMessage((u8 *)(&m[2]), sSpNpcMabelMsgKeys[0]);
            MenuCtrl_ReturnChosenItems(0);
            break;
        }
        break;
    case 1:
        MenuCtrl_ReturnChosenItems(0);
        break;
    }
}

void SpNpcMabelTalk::onDisposeChoice(u32 v) {
    if (v == 1) {
        MenuCtrl_ReturnChosenItems(0);
    }
}

void SpNpcMabelTalk::onItemPriceChoice(u32 v) {
    u8 m[3];
    u16 A[2];
    u16 B[2];
    u16 C[2];
    PlayerData *h = PlayerData_GetCurrent();
    if (v == 0) {
        s32 r = Pocket_FindEmpty();
        if (r == -1) {
            m[0] = 0x2c;
            window->setNextMessage((u8 *)(m), sSpNpcMabelMsgKeys[0]);
        } else if (!NpcActor_CanPlayerPay(owner, price)) {
            m[1] = 0x2b;
            window->setNextMessage((u8 *)(&m[1]), sSpNpcMabelMsgKeys[0]);
        } else {
            m[2] = 0x29;
            window->setNextMessage((u8 *)(&m[2]), sSpNpcMabelMsgKeys[0]);
            sellItemToPlayer();
        }
    } else if (v == 1) {
        owner->tryOnRemovedItem = 0xfff1;
        if (Unk_ov049_02259774_R(&owner->selectedItem, 0x11a8, 0x12a7)) {
        } else if (owner->selectedItem >= 0x13c8 && owner->selectedItem <= 0x1407) {
        } else if (owner->selectedItem >= 0x13a8 && owner->selectedItem <= 0x13c7) {
        } else if (owner->selectedItem >= 0x1431 && owner->selectedItem <= 0x1470) {
        } else {
            return;
        }
        if (owner->selectedItem >= 0x11a8 && owner->selectedItem <= 0x12a7) {
            owner->tryOnPrevItem = *h->getShirt();
            A[1] = owner->selectedItem;
            PlayerActor_RequestWearShirtAlt(&A[1]);
        } else if ((owner->selectedItem >= 0x13c8 && owner->selectedItem <= 0x1407) || (owner->selectedItem >= 0x13a8 && owner->selectedItem <= 0x13c7)) {
            if (owner->selectedItem >= 0x13a8 && owner->selectedItem <= 0x13c7) {
                if (!func_0204bab8(&owner->selectedItem)) {
                    owner->tryOnRemovedItem = *h->getFaceItem();
                    B[0] = 0xfff1;
                    PlayerActor_RequestWearFaceItemAlt(&B[0]);
                }
            }
            owner->tryOnPrevItem = *h->getHat();
            B[1] = owner->selectedItem;
            PlayerActor_RequestWearHatAlt(&B[1]);
        } else if (owner->selectedItem >= 0x1431 && owner->selectedItem <= 0x1470) {
            owner->tryOnPrevItem = *h->getFaceItem();
            C[0] = owner->selectedItem;
            PlayerActor_RequestWearFaceItemAlt(&C[0]);
            A[0] = 0xfff1;
            A[0] = *h->getHat();
            if (Unk_ov049_02259dd8_VR(&A[0], 0x13a8, 0x13c7)) {
                if (!func_0204bab8(&A[0])) {
                    owner->tryOnRemovedItem = *h->getHat();
                    C[1] = 0xfff1;
                    PlayerActor_RequestWearHatAlt(&C[1]);
                }
            }
        }
        PlayerActor_SetNoFaceTalkTarget(1, 4);
        Camera_SetMode4();
        window->lockAdvance();
        setScript(7);
    }
}

void SpNpcMabelTalk::onTryOnChoice(u32 v) {
    u8 m[3];
    volatile u16 A[2];
    u16 B[2];
    u16 C[2];
    if (Unk_ov049_02259774_R(&owner->selectedItem, 0x11a8, 0x12a7)) {
        A[1] = owner->tryOnPrevItem;
        PlayerActor_RequestWearShirtAlt((u16 *)&A[1]);
    }
    if (Unk_ov049_02259774_R(&owner->selectedItem, 0x13c8, 0x1407) || (owner->selectedItem >= 0x13a8 && owner->selectedItem <= 0x13c7)) {
        B[0] = owner->tryOnPrevItem;
        PlayerActor_RequestWearHatAlt(&B[0]);
    }
    if (Unk_ov049_02259774_R(&owner->selectedItem, 0x1431, 0x1470)) {
        B[1] = owner->tryOnPrevItem;
        PlayerActor_RequestWearFaceItemAlt(&B[1]);
    }
    if (owner->tryOnRemovedItem != 0xfff1) {
        A[0] = owner->tryOnRemovedItem;
        BOOL r = FALSE;
        u32 h = A[0];
        u32 l = A[0];
        if (l >= 0x13a8 && h <= 0x13c7) {
            r = TRUE;
        }
        if (r || (h >= 0x13c8 && h <= 0x1407)) {
            C[0] = owner->tryOnRemovedItem;
            PlayerActor_RequestWearHatAlt((u16 *)&C[0]);
        } else if (h >= 0x1431 && h <= 0x1470) {
            C[1] = owner->tryOnRemovedItem;
            PlayerActor_RequestWearFaceItemAlt((u16 *)&C[1]);
        }
    }
    PlayerActor_SetNoFaceTalkTarget(0, 4);
    setScript(8);
    Camera_RestorePrevMode();
    if (v == 0) {
        s32 r = Pocket_FindEmpty();
        if (r == -1) {
            m[0] = 0x2c;
            window->setNextMessage((u8 *)(m), sSpNpcMabelMsgKeys[0]);
        } else if (!NpcActor_CanPlayerPay(owner, price)) {
            m[1] = 0x2b;
            window->setNextMessage((u8 *)(&m[1]), sSpNpcMabelMsgKeys[0]);
        } else {
            m[2] = 0x29;
            window->setNextMessage((u8 *)(&m[2]), sSpNpcMabelMsgKeys[0]);
            sellItemToPlayer();
        }
    }
}

extern "C" BOOL SpNpcMabel_IsDeliveryItem(u16 *p, s32 v) {
    if (v == 2) {
        return Unk_ov049_02259774_R(p, 0x155f, 0x1560);
    }
    return FALSE;
}

void SpNpcMabelTalk::onDeliveryChoice(u32 v) {
    if (v == 0) {
        setPocketFilter(SpNpcMabel_IsDeliveryItem, 0xd, 0);
        openSubScene(0);
        setScript(9);
    }
}

void SpNpcMabelTalk::onDramaMenuChoice() {
    u8 m[2];
    if ((s32)msgIndex >= 0 && (s32)msgIndex <= 0x11) {
        s32 t = window->getChoiceList()->getResult();
        if (t != 2) {
            m[1] = sSpNpcMabelDramaMenuMsgs[t];
            window->setNextMessage((u8 *)(&m[1]), sSpNpcMabelMsgKeys[0]);
        } else {
            if (Talk_IsDramaPending(owner, m, 2)) {
                Talk_AdvanceDrama(owner, m);
            }
        }
    }
    if (!gCommManager->isOnline()) {
        if (*DebugVar_GetPtr(0, 0x4a) == 0) {
            NpcActor *r = NpcRegistry_FindSpNpc(5);
            if (r) {
                setPartnerActor(r);
            }
        }
    }
}

void SpNpcMabelTalk::update() {
    s32 i = script;
    if (sSpNpcMabelTalkScripts[i].flag != 0) {
        if (sSpNpcMabelTalkScripts[i].fn != 0) {
            (this->*sSpNpcMabelTalkScripts[i].fn)();
        }
    }
}

void SpNpcMabelTalk::onTaskDone(u32) {
    s32 i = script;
    if (sSpNpcMabelTalkScripts[i].flag == 0) {
        if (sSpNpcMabelTalkScripts[i].fn != 0) {
            (this->*sSpNpcMabelTalkScripts[i].fn)();
            setScript(0);
        }
    }
}

void SpNpcMabelTalk::setScript(s32 v) {
    script = v;
}

void SpNpcMabelTalk::onDesignEditorDone() {
    u8 m[2];
    if (MenuCtrl_IsResultOk()) {
        m[0] = 0x10;
        window->setNextMessage((u8 *)(m), sSpNpcMabelMsgKeys[0]);
    } else {
        m[1] = 0xf;
        window->setNextMessage((u8 *)(&m[1]), sSpNpcMabelMsgKeys[0]);
    }
}

void SpNpcMabelTalk::onDesignNamed() {
    u8 m[1];
    m[0] = 0x12;
    window->setNextMessage((u8 *)(m), sSpNpcMabelMsgKeys[0]);
}

void SpNpcMabelTalk::onDisplayPatternChosen() {
    u8 m[2];
    if (MenuCtrl_IsResultOk()) {
        PlayerData *h = PlayerData_GetCurrent();
        s32 a = MenuCtrl_GetIndex();
        u32 t = ((PlayerPatterns *)h->getPatterns())->getPatternOrder()->getSlot(a);
        PatternSrc_Copy(9, t, 4, owner->patternSlot, 1);
        m[0] = 0x24;
        window->setNextMessage((u8 *)(m), sSpNpcMabelMsgKeys[0]);
    } else {
        m[1] = 0x22;
        window->setNextMessage((u8 *)(&m[1]), sSpNpcMabelMsgKeys[0]);
    }
}

void SpNpcMabelTalk::onTakePatternChosen() {
    u8 m[2];
    u16 v[2];
    if (MenuCtrl_IsResultOk()) {
        PlayerData *h = PlayerData_GetCurrent();
        s32 a = MenuCtrl_GetIndex();
        u32 t = ((PlayerPatterns *)h->getPatterns())->getPatternOrder()->getSlot(a);
        u16 lo, hi;
        PatternSrc_Copy(4, owner->patternSlot, 9, t, 1);
        if (t < 8) {
            lo = t + 0x12a8;
        } else {
            lo = 0x12a8;
        }
        if (t < 8) {
            hi = t + 0x1429;
        } else {
            hi = 0x1429;
        }
        u32 x = *h->getShirt();
        u32 y = *h->getHat();
        if (lo == x) {
            if (Unk_ov049_02259774_R(h->getShirt(), 0x12a8, 0x12af)) {
                v[0] = lo;
                PlayerActor_RequestWearShirtAlt(&v[0]);
            }
        }
        if (hi == y) {
            if (Unk_ov049_02259774_R(h->getHat(), 0x1429, 0x1430)) {
                v[1] = hi;
                PlayerActor_RequestWearHatAlt(&v[1]);
            }
        }
        m[0] = 0x27;
        window->setNextMessage((u8 *)(m), sSpNpcMabelMsgKeys[0]);
    } else {
        m[1] = 0x22;
        window->setNextMessage((u8 *)(&m[1]), sSpNpcMabelMsgKeys[0]);
    }
}

void SpNpcMabelTalk::onTradePatternChosen() {
    u8 m[2];
    u16 v[2];
    if (MenuCtrl_IsResultOk()) {
        PlayerData *h = PlayerData_GetCurrent();
        s32 a = MenuCtrl_GetIndex();
        u32 t = ((PlayerPatterns *)h->getPatterns())->getPatternOrder()->getSlot(a);
        u16 lo, hi;
        PatternSrc_Swap(9, t, 4, owner->patternSlot, 1);
        if (t < 8) {
            lo = t + 0x12a8;
        } else {
            lo = 0x12a8;
        }
        if (t < 8) {
            hi = t + 0x1429;
        } else {
            hi = 0x1429;
        }
        u32 x = *h->getShirt();
        u32 y = *h->getHat();
        if (lo == x) {
            if (Unk_ov049_02259774_R(h->getShirt(), 0x12a8, 0x12af)) {
                v[0] = lo;
                PlayerActor_RequestWearShirtAlt(&v[0]);
            }
        }
        if (hi == y) {
            if (Unk_ov049_02259774_R(h->getHat(), 0x1429, 0x1430)) {
                v[1] = hi;
                PlayerActor_RequestWearHatAlt(&v[1]);
            }
        }
        m[0] = 0x21;
        window->setNextMessage((u8 *)(m), sSpNpcMabelMsgKeys[0]);
    } else {
        m[1] = 0x22;
        window->setNextMessage((u8 *)(&m[1]), sSpNpcMabelMsgKeys[0]);
    }
}

void SpNpcMabelTalk::onSellItemsChosen() {
    u8 msg;
    u16 v[1];
    void *ctx;
    s32 i;
    price = 0;
    soldCount = 0;
    ctx = window;
    msg = gU8None[0];
    if (MenuCtrl_IsResultOk()) {
        u16 *tbl = MenuCtrl_GetChosenItems();
        v[0] = 0xfff1;
        for (i = 0; i < 15; i++) {
            u16 t = tbl[i];
            if (t == 0xfff1) break;
            v[0] = t;
            price += Item_GetPrice(v) / 4;
        }
        soldCount = i;
        if (price == 0) {
            msg = 0x17;
        } else {
            setNumberSlot(price, 1, 10, 1, 0);
            msg = 0x1b;
        }
    } else {
        msg = 0x15;
    }
    ((TalkWindowState *)(ctx))->setNextMessage((u8 *)(&msg), sSpNpcMabelMsgKeys[0]);
}

void SpNpcMabelTalk::waitTryOnDone() {
    if (PlayerActor_TestLocalFlag0F()) {
        FtrMgr_TakeDisplayedWearableAt(owner->selectedItemX, owner->selectedItemZ);
    }
    if (PlayerActor_IsInAction(0x10, 4)) {
        void *ctx = window;
        u8 msg;
        ((TalkWindowState *)(ctx))->unlockAdvance();
        msg = 0x2d;
        ((TalkWindowState *)(ctx))->setNextMessage((u8 *)(&msg), sSpNpcMabelMsgKeys[0]);
        setScript(0);
    }
}

void SpNpcMabelTalk::restoreTryOnDisplay() {
    if (PlayerActor_TestLocalFlag0F()) {
        FtrMgr_RestoreDisplayedWearableAt(owner->selectedItemX, owner->selectedItemZ);
        setScript(0);
    }
}

void SpNpcMabelTalk::onDeliveryItemChosen() {
    void *ctx = window;
    char *tbl = sSpNpcMabelMsgKeys[0];
    u32 msg = 0x30;
    u16 v[3];
    ParcelErrand *hh;
    if (MenuCtrl_IsResultOk()) {
        hh = &(PlayerData_GetCurrent()->getErrands())->parcelErrand;
        if (Talk_IsInOwnTown()) {
            s32 n = (s32)MenuCtrl_GetIndex();
            v[1] = Pocket_GetItem(n);
            if (n >= 0) {
                Pocket_RemoveItem(n);
            }
            if (!Unk_ov049_02258ee0_Eq(&v[1], &v[2])) {
                requestTakeItem(&v[1], 2, 5, 0);
                msg = 0x2f;
                ((ErrandRecord *)ParcelErrand_GetRecord(hh))->setStep(1);
            }
        }
    }
    *(u8 *)v = msg;
    ((TalkWindowState *)(ctx))->setNextMessage((u8 *)(v), tbl);
}

void SpNpcMabelTalk::openChoiceMenu(void *rec, s32 x) {
    void *ctx = window;
    ChoiceList *h = window->getChoiceList();
    SpNpcMabelChoiceMenu *r = (SpNpcMabelChoiceMenu *)rec;
    u8 *p = (u8 *)r->choices;
    s32 n = r->count;
    s32 z = 0;
    s32 i;
    if (x != -1) {
        h->reset(n, x);
    } else {
        h->reset(n, -1);
    }
    i = z;
    for (; i < n; i++) {
        u8 buf[2];
        buf[0] = p[i];
        buf[1] = 6;
        h->setEntry(i, (const u8 *)(buf), z, (const u8 *)(&buf[1]), (const char *)(sSpNpcMabelMsgKeys[0]), z);
    }
    h->loadTexts();
    ((TalkWindowState *)(ctx))->openChoices(1);
}


void SpNpcMabelTalk::sellItemToPlayer() {
    owner->purchasePending = 1;
    NpcActor_ChargePlayer(owner, price);
    Pocket_AddItem(&owner->selectedItem, 0);
    AbleShop_BuyAt(owner->selectedItemX, owner->selectedItemZ, 10);
    VillagerTrend_OnClothesBought();
}

BOOL SpNpcMabel::acceptsInteraction(void *) {
    if (talkCtrl.isBusy() != 0 || netIsTalkLocked() != 0 || tryStartShopItemTalk() != 0) {
        return FALSE;
    }
    return TRUE;
}

BOOL SpNpcMabel::acceptsSelfRequestedInteraction(void *) {
    if (talkCtrl.isBusy() != 0 || netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

void SpNpcMabel::onInteractionEvent(u32 cmd, u8 arg) {
    CommManager *g;
    s32 a, b;
    switch (cmd) {
    case 3:
        *(u8 *)&partnerPlayer = arg;
        if (arg != 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, arg);
            changeAct(0xc);
        } else if (isNetOwner()) {
            u32 t = gCommManager->myAid;
            netSetSlotsIfOwner(1, t, t);
            changeAct(0xc);
        }
        break;
    case 1:
        partnerPlayer = arg;
        if (arg != 4 && arg != gCommManager->myAid) {
            netSetSlotsIfOwner(1, arg, arg);
            changeAct(9);
        } else if (isNetOwner()) {
            g = gCommManager;
            netSetSlotsIfOwner(1, g->myAid, g->myAid);
            if (talk.getTopic() == 1 || talk.getTopic() == 0) {
                talk.resetMsg();
                talk.setTalkPlayer(getPlayerActor(4));
                changeAct(4);
            } else if (talk.getTopic() == 3) {
                talk.resetMsg();
                talk.setTalkPlayer(getPlayerActor(4));
                changeAct(5);
            } else if (((CommManager *)(g))->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0) {
                talk.resetMsg();
                talk.setTalkPlayer(getPlayerActor(4));
                changeAct(4);
            } else {
                changeAct(0xd);
            }
        }
        break;
    case 0:
        partnerPlayer = arg;
        if (arg != 4 && arg != gCommManager->myAid) {
            netSetSlotsIfOwner(1, arg, arg);
            changeAct(9);
        } else if (isNetOwner()) {
            netSetSlotsIfOwner(1, gCommManager->myAid, gCommManager->myAid);
            talk.resetMsg();
            talk.setTalkPlayer(getPlayerActor(4));
            talk.setTopic(2);
            changeAct(4);
        }
        break;
    case 8:
        if (arg == 4) {
            if (NetArea_IsLocalOwner()) {
                g = gCommManager;
                netSetSlotsIfOwner(1, g->myAid, 4);
                if (((CommManager *)(g))->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0) {
                    changeAct(0xa);
                } else if (talk.getTopic() != 3) {
                    changeAct(1);
                }
            } else {
                netSetSlotsIfOwner(1, 4, gCommManager->myAid);
                changeAct(8);
            }
        }
        break;
    case 4:
        if (netIsTalkLocked()) {
            if (isNetOwner()) {
                a = 4;
                b = 4;
                if (netGetSlots(&a, &b)) {
                    if (arg == 4) goto x4;
                    if (arg == b) goto y4;
                x4:
                    if (arg != 4) break;
                y4:
                    netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                    changeAct(0xa);
                }
            }
        }
        break;
    }
    NpcActor::onInteractionEvent(cmd, arg);
}

void SpNpcMabel::setDesignConcept(u32 y) {
    PlayerData *h = PlayerData_GetCurrent();
    s32 n = MenuCtrl_GetIndex();
    ((PatternInfo *)(((Pattern *)(((PlayerPatterns *)(h->getPatterns()))->getPatternByOrder((s32)n)))->getInfo()))->setTaste(y);
}

BOOL SpNpcMabel::pickShopItemAtPlayer() {
    u16 t[3];
    s32 bx, by;
    VecFx32 v;
    Character *p = (Character *)PlayerActor_GetActor(4);
    BOOL f = Unk_ov049_02258ee0_Flags() ? TRUE : FALSE;
    if (p == 0 || TalkRequest_IsActive() != 0 || talkCtrl.isBusy() != 0 || ((gPad[1] & 1) == 0 && f == 0)) {
        return FALSE;
    }
    selectedItem = 0xfff1;
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
    t[0] = *ShopStock_GetItemAtTile(bx, by);
    if (Unk_ov049_02258ee0_Eq(&t[0], &t[2])) {
        return FALSE;
    }
    {
        BOOL r = FALSE;
        volatile u16 *pv = &t[0];
        u32 x = *pv;
        u32 y = *pv;
        if (y < 0x3984 || x > 0x3d83) {
        } else {
            r = TRUE;
        }
        if (r != 0 || (x >= 0x3fa4 && x <= 0x40a3) || (x >= 0x40a4 && x <= 0x4123) || (x >= 0x4124 && x <= 0x4223) ||
            (x >= 0x3e24 && x <= 0x3ea3)) {
            Item_FromPlacedForm(&t[1], &t[0]);
            t[0] = t[1];
            talk.setTopic(4);
        } else if (x >= 0x3e04 && x <= 0x3e23) {
            talk.setTopic(5);
        } else {
            return FALSE;
        }
    }
    selectedItem = t[0];
    selectedItemX = bx;
    selectedItemZ = by;
    purchasePending = 0;
    return TRUE;
}

BOOL SpNpcMabel::tryStartShopItemTalk() {
    if (pickShopItemAtPlayer()) {
        TalkRequest_AddPlayerTalk6(this, 0);
        return TRUE;
    }
    return FALSE;
}


BOOL SpNpcMabel::tryStartFarewellTalk() {
    if (gCommManager->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0) {
        return FALSE;
    }
    VecFx32 *src = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;
    if (Ground_IsOnLockedExit(&v)) {
        talk.setTopic(3);
        TalkRequest_AddPlayerTalk6(this, 0);
        changeAct(0xf);
        return TRUE;
    }
    return FALSE;
}

extern "C" SpNpcMabelTalkScript sSpNpcMabelTalkScripts[10] = {
    {0, 0},
    {&SpNpcMabelTalk::onDesignEditorDone, 0},
    {&SpNpcMabelTalk::onDesignNamed, 0},
    {&SpNpcMabelTalk::onDisplayPatternChosen, 0},
    {&SpNpcMabelTalk::onTakePatternChosen, 0},
    {&SpNpcMabelTalk::onTradePatternChosen, 0},
    {&SpNpcMabelTalk::onSellItemsChosen, 0},
    {&SpNpcMabelTalk::waitTryOnDone, 1},
    {&SpNpcMabelTalk::restoreTryOnDisplay, 1},
    {&SpNpcMabelTalk::onDeliveryItemChosen, 0},
};

extern "C" char sSpNpcMabelKey[] = "sp_npc_ysister";

extern "C" SpNpcMabelActEntry sSpNpcMabelActTable[16] = {
    {&SpNpcMabel::setupAct00, &SpNpcMabel::mainAct00},
    {&SpNpcMabel::setupAct01, &SpNpcMabel::mainAct01},
    {&SpNpcMabel::setupAct02, &SpNpcMabel::mainAct02},
    {&SpNpcMabel::setupAct03, &SpNpcMabel::mainAct03},
    {&SpNpcMabel::setupAct04, &SpNpcMabel::mainAct04},
    {&SpNpcMabel::setupAct05, &SpNpcMabel::mainAct05},
    {&SpNpcMabel::setupAct06, &SpNpcMabel::mainAct06},
    {&SpNpcMabel::setupAct07, &SpNpcMabel::mainAct07},
    {&SpNpcMabel::setupAct08, &SpNpcMabel::mainAct08},
    {&SpNpcMabel::setupAct09, &SpNpcMabel::mainAct09},
    {&SpNpcMabel::setupAct0A, &SpNpcMabel::mainAct0A},
    {&SpNpcMabel::setupAct0B, &SpNpcMabel::mainAct0B},
    {&SpNpcMabel::setupAct0C, &SpNpcMabel::mainAct0C},
    {&SpNpcMabel::setupAct0D, &SpNpcMabel::mainAct0D},
    {&SpNpcMabel::setupAct0E, &SpNpcMabel::mainAct0E},
    {&SpNpcMabel::setupAct0F, &SpNpcMabel::mainAct0F},
};

extern "C" const u8 sSpNpcMabelDramaMsgTable[28] = {0x00, 0x01, 0x02, 0x03, 0xfe, 0xfe, 0xfe, 0x04, 0x05, 0x06, 0xfe, 0xfe, 0xfe, 0xfe, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xfe, 0xfe, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11};

extern "C" ActorProfile sSpNpcMabelProfile = {(void *(*)())SpNpcMabel_Create, 0x79, 0x7d, 2, 0x5000, 0x5000, 0x3e800};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov049_02258de0) {
    HOST_OVERLAY_VAR(data_ov049_0225ba48),
    HOST_OVERLAY_VAR(sSpNpcMabelSequence4Key),
    HOST_OVERLAY_VAR(sSpNpcMabelDramaKey),
    HOST_OVERLAY_VAR(data_ov049_0225ba44),
    HOST_OVERLAY_VAR(sSpNpcMabelMsgKeys),
    HOST_OVERLAY_VAR(data_ov049_0225ba4c),
    HOST_OVERLAY_VAR(sSpNpcMabelModelPath),
    HOST_OVERLAY_VAR(sSpNpcMabelItemChoiceMenus),
    HOST_OVERLAY_VAR(sSpNpcMabelTexturePath),
    HOST_OVERLAY_VAR(data_ov049_0225ba40),
    HOST_OVERLAY_VAR(sSpNpcMabelTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcMabelKey),
    HOST_OVERLAY_VAR(sSpNpcMabelActTable),
    HOST_OVERLAY_VAR(sSpNpcMabelProfile),
    HOST_OVERLAY_VARS_END
};
