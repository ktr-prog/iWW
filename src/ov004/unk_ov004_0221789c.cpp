#include "types.h"
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
#include "room/FtrActor.h"
#include "talk/TalkWindowState.h"
#include "town/BlockMap.h"
#include "room/FtrActorGrid.h"
#include "game/TouchPicker.h"
#include "save/VillagerData.h"
#include "save/VillagerData.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_020b5e5c.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/ov004/unk_ov004_0221789c.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/main/unk_020b4828.h"

class FleaMarketSellerVillager;

typedef BOOL (FleaMarketSellerVillager::*Unk_ov004_022187b8_Fn)();

struct FleaMarketSellerActEntry {
    Unk_ov004_022187b8_Fn a;
    Unk_ov004_022187b8_Fn b;
};



extern "C" {
extern u16 data_020c6cc8;
extern void *gSceneBlockMap;
extern u8 gFieldSceneKind;
extern u16 gPad[];
extern s16 data_02135f44[];
extern FleaMarketSellerActEntry sFleaMarketSellerActTable[8];

void NpcActor_FindFreeUnitNear(VecFx32 *out, NpcActor *self, VecFx32 *in);
s32 Vec_Equal(VecFx32 *a, VecFx32 *b);
s32 Vec_NotEqual(VecFx32 *a, VecFx32 *b);
u8 Math_CountDownU8(u8 *p);
s32 Math_AngleDiffAbs(s32, s32);
s32 TalkRequest_SetTargetDone(void *);
void TalkRequest_AddPlayerTalk6(void *, u32);
BOOL Villager_RemoveFurnitureAt(VillagerData *a, u32 *b, u8 *c, s32 d);
BOOL Villager_HasShownFurnitureAt(VillagerData *a, u32 *b, u8 *c, s32 d);
s32 Villager_CountFurnitureLike(VillagerData *a, u16 *b);
s32 Item_IsFurniture(u16 *);
u32 Item_GetFurnitureIndex(u16 *);
u8 Scene_GetPrevious(void);
s32 SceneId_IsTownUnk31(u32 a);
void Ground_LockExit(u32);
void *FgData_GetVillagerLayout(s32 *size, s32 villager, void *heap);
BOOL Ground_IsOnLockedExit(VecFx32 *p);
s32 TalkRequest_IsActive();
s32 func_01ffcb0c(s32 a, s32 b);
s32 FX_Div(s32 a, s32 b);
void FieldPos_ToUnit(s32 *x, s32 *y, VecFx32 *v);
u16 Item_MakeFurniture(s32 a, s32 b);
VillagerMemory *Villager_FindOrCreateMemory(VillagerMemory *t, void *b);
VillagerMemory *Villager_FindMemory(void *a, void *b);
void VillagerMemory_RecordTalk(VillagerMemory *self, void *a, u8 *b, u8 *c);
s32 Item_GetPrice(u16 *o);
BOOL TouchPick_GetGroundPos(TouchPickResult *picker, VecFx32 *out);
s32 FtrActor_GetFtrIndex(FtrActor *self);
}

class FleaMarketSellerVillagerTalk : public VillagerTalk {
public:
    FleaMarketSellerVillagerTalk();
    virtual ~FleaMarketSellerVillagerTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void sellFurniture();
    void attachOwner(FleaMarketSellerVillager *owner);

    /* 0x1a0 */ FleaMarketSellerVillager *villager;
    /* 0x1a4 */ s32 salePrice;
};

class FleaMarketSellerVillager : public VillagerActor {
public:
    FleaMarketSellerVillager()
        : saleItem(0xfff1), saleUnitX(0), saleUnitY(0) {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL acceptsSelfRequestedInteraction(void *a);
    virtual BOOL updateAct();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();

    BOOL checkPlayerLeaving();
    BOOL requestTradeTalk();
    BOOL checkFurnitureTap();
    BOOL mainAct07();
    BOOL setupAct07();
    BOOL mainAct02();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct06();
    BOOL setupAct06();
    BOOL mainAct05();
    BOOL setupAct05();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 idx);

    /* 0x894 */ u16 saleItem;
    /* 0x896 */ u16 pad_896;
    /* 0x898 */ s32 saleUnitX;
    /* 0x89c */ s32 saleUnitY;
    /* 0x8a0 */ s32 act;
    /* 0x8a4 */ FleaMarketSellerVillagerTalk talk;
    /* 0xa4c */ u8 talkStage;
    /* 0xa4d */ u8 approachTimer;
    /* 0xa4e */ u8 talkMelodyPlayed;
    /* 0xa4f */ u8 pad_a4f;
    /* 0xa50 */ u8 *layoutData;
    /* 0xa54 */ s32 layoutSize;
};

extern "C" ActorProfile sFleaMarketSellerVillagerProfile = {(void *(*)())FleaMarketSellerVillager_Create, 0x86, 0x8a, 2, 0x5000, 0x5000, 0x3e800};
extern "C" {
u8 data_ov004_022506c8[0x28];
u8 data_ov004_022506f0[0x28];
}
typedef FleaMarketSellerVillager FMSV;
extern "C" FleaMarketSellerActEntry sFleaMarketSellerActTable[8] = {
    {&FMSV::setupAct00, &FMSV::mainAct00},
    {&FMSV::setupAct01, &FMSV::mainAct01},
    {0, &FMSV::mainAct02},
    {&FMSV::setupAct03, &FMSV::mainAct03},
    {&FMSV::setupAct04, &FMSV::mainAct04},
    {&FMSV::setupAct05, &FMSV::mainAct05},
    {&FMSV::setupAct06, &FMSV::mainAct06},
    {&FMSV::setupAct07, &FMSV::mainAct07}};

static inline BOOL Unk_ov004_02217954_Both() {
    if (gTouchPrevHeld != 0 && gTouchPrevChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" FleaMarketSellerVillager *FleaMarketSellerVillager_Create() {
    return new FleaMarketSellerVillager;
}

BOOL FleaMarketSellerVillager::preCreate() {
    if (!VillagerActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest(&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL FleaMarketSellerVillager::onCreate() {
    if (!VillagerActor::onCreate()) {
        return FALSE;
    }
    FtrMgr_SetSaleMode();
    saleItem = 0xfff1;
    footstepFx.enableFootsteps();
    if (SceneId_IsTownUnk31(Scene_GetPrevious())) {
        changeAct(4);
    } else {
        changeAct(0);
    }
    Ground_LockExit(0);
    layoutSize = 0;
    layoutData = (u8 *)FgData_GetVillagerLayout(&layoutSize, getNpcIndex(), gCurrentHeap);
    return TRUE;
}

BOOL FleaMarketSellerVillager::onDelete() {
    if (!VillagerActor::onDelete()) {
        return FALSE;
    }
    if (layoutData != 0) {
        Mem_Free(layoutData);
        layoutData = 0;
        layoutSize = 0;
    }
    return TRUE;
}

BOOL FleaMarketSellerVillager::updateAct() {
    BOOL r = FALSE;
    if (sFleaMarketSellerActTable[act].b) {
        r = (this->*sFleaMarketSellerActTable[act].b)();
    }
    return r;
}

void FleaMarketSellerVillager::changeAct(s32 idx) {
    BOOL r = TRUE;
    if (sFleaMarketSellerActTable[idx].a) {
        r = (this->*sFleaMarketSellerActTable[idx].a)();
    }
    if (r) {
        act = idx;
    }
}

BOOL FleaMarketSellerVillager::setupAct00() {
    talkStage = 0;
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketSellerVillager::mainAct00() {
    TalkRequest_AddPlayerTalk6(this, 0);
    return TRUE;
}

BOOL FleaMarketSellerVillager::setupAct04() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketSellerVillager::mainAct04() {
    VecFx32 a, b;
    s32 r4, r6;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    r6 = getDistanceToPlayer(4);
    r4 = Math_AngleDiffAbs(rotY, getAngleToPlayer(4));
    NpcActor_FindFreeUnitNear(&b, this, &a);
    if (r6 > 0x3000 && Vec_NotEqual(&b, &position) != 0) {
        changeAct(6);
    } else {
        if (r4 > 0x2000) {
            changeAct(5);
        }
    }
    if (checkPlayerLeaving()) {
        return TRUE;
    }
    requestTradeTalk();
    return TRUE;
}

BOOL FleaMarketSellerVillager::setupAct05() {
    actionCtrl.requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketSellerVillager::mainAct05() {
    VecFx32 a, b;
    s32 r4, r6;
    if (checkPlayerLeaving()) {
        return TRUE;
    }
    if (requestTradeTalk()) {
        return TRUE;
    }
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    r4 = getDistanceToPlayer(4);
    r6 = getAngleToPlayer(4);
    NpcActor_FindFreeUnitNear(&b, this, &a);
    if (r4 > 0x3000 && Vec_NotEqual(&b, &position) != 0) {
        changeAct(6);
        return TRUE;
    }
    moveCtrl.setTargetAngle(r6);
    if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone() != 0) {
            changeAct(4);
        }
    }
    return TRUE;
}

BOOL FleaMarketSellerVillager::setupAct06() {
    actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL FleaMarketSellerVillager::mainAct06() {
    VecFx32 a, b;
    s32 r4;
    if (checkPlayerLeaving()) {
        return TRUE;
    }
    if (requestTradeTalk()) {
        return TRUE;
    }
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    r4 = getDistanceToPlayer(4);
    NpcActor_FindFreeUnitNear(&b, this, &a);
    if (r4 > 0x4000) {
        if (actionCtrl.getAction() == 1) {
            actionCtrl.requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (actionCtrl.getAction() == 2) {
            actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    moveCtrl.setWaypoint(&b);
    if (r4 <= 0x3000 || Vec_Equal(&b, &position) != 0) {
        changeAct(4);
    }
    return TRUE;
}

BOOL FleaMarketSellerVillager::setupAct03() {
    void *t = talk.getTalkPlayer();
    s32 r = 0;
    if (t != 0) {
        r = getAngleTo((NpcActor *)t);
    }
    talkCtrl.requestTurnAndTalk(0, r, 1);
    return TRUE;
}

BOOL FleaMarketSellerVillager::mainAct03() {
    VecFx32CtorDtor a;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    if (talkCtrl.isBusy() == 0) {
        SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
        changeAct(2);
    }
    return TRUE;
}

BOOL FleaMarketSellerVillager::setupAct01() {
    void *t = talk.getTalkPlayer();
    s32 r = 0;
    if (t != 0) {
        r = getAngleTo((NpcActor *)t);
    }
    talkCtrl.requestTurnAndTalk(0, r, 0);
    return TRUE;
}

BOOL FleaMarketSellerVillager::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        if (talkStage == 0) {
            talkStage = 1;
        }
        saleItem = 0xfff1;
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL FleaMarketSellerVillager::mainAct02() {
    return TRUE;
}

BOOL FleaMarketSellerVillager::setupAct07() {
    approachTimer = 0x32;
    actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}


BOOL FleaMarketSellerVillager::mainAct07() {
    VecFx32 a, b;
    s32 r4;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    NpcActor_FindFreeUnitNear(&b, this, &a);
    r4 = getDistanceToPlayer(4);
    ((BlockMap *)gSceneBlockMap)->getWalkLinksAtPos(&position);
    if (r4 > 0x4000) {
        if (actionCtrl.getAction() == 1) {
            actionCtrl.requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (actionCtrl.getAction() == 2) {
            actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    moveCtrl.setWaypoint(&b);
    if (r4 <= 0x3000 || Vec_Equal(&b, &position) != 0 || Math_CountDownU8(&approachTimer) == 0) {
        VillagerTalk *pb = &talk;
        pb->resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(1);
    }
    return TRUE;
}

FleaMarketSellerVillagerTalk::FleaMarketSellerVillagerTalk() {
}

FleaMarketSellerVillagerTalk::~FleaMarketSellerVillagerTalk() {
}

void FleaMarketSellerVillagerTalk::attachOwner(FleaMarketSellerVillager *owner) {
    resetMsg();
    begin(owner, 0x11);
    villager = owner;
}


void FleaMarketSellerVillagerTalk::sellFurniture() {
    u16 *p = &villager->saleItem;
    BOOL same;
    if (Item_IsFurniture(p)) {
        u16 t = 0xfff1;
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&t)) {
            same = TRUE;
        } else {
            same = FALSE;
        }
    } else {
        if (*p == 0xfff1) {
            same = TRUE;
        } else {
            same = FALSE;
        }
    }
    if (!same) {
        NpcActor_ChargePlayer(villager, salePrice);
        Pocket_AddItem(&villager->saleItem, 0);
        FleaMarketSellerVillager *o = villager;
        s32 idx = FtrActorGrid_GetInstance()->getIndex(o->saleUnitX, o->saleUnitY, 0);
        if (idx != -1) {
            FtrMgr_RemoveActorByIndex(idx);
            if (villager->getVillagerData()) {
                FleaMarketSellerVillager *q = villager;
                Villager_RemoveFurnitureAt((VillagerData *)q->getVillagerData(), (u32 *)&q->saleUnitX, q->layoutData, q->layoutSize);
            }
        }
        villager->saleItem = 0xfff1;
    }
}

void FleaMarketSellerVillagerTalk::start(TalkStartMsg *out) {
    VillagerMemory *r7 = Villager_FindOrCreateMemory(((VillagerData *)villager->villagerData)->memories, PlayerData_GetCurrent()->getPlayerId());
    if (r7) {
        VillagerMemory_RecordTalk(r7, 0, 0, 0);
    }
    if (villager->talkStage == 3) {
        ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506f0, 0x28, "ev_fmarket2");
        out->msgKey = (const char *)data_ov004_022506f0;
        out->msgIndex = Random_GlobalBelow(3) + 3;
        return;
    }
    u16 *q = &villager->saleItem;
    u16 w;
    u16 t;
    BOOL eq;
    if (Item_IsFurniture(q)) {
        t = 0xfff1;
        eq = Item_GetFurnitureIndex(q) == Item_GetFurnitureIndex(&t) ? TRUE : FALSE;
    } else {
        eq = *q == 0xfff1 ? TRUE : FALSE;
    }
    if (!eq) {
        s32 r6 = 0;
        setItemNameSlot(&villager->saleItem, r6, 7);
        salePrice = Item_GetPrice(&villager->saleItem);
        if (salePrice < 10) {
            salePrice = 10;
        }
        if (PlayerData_GetCurrent()) {
            r7 = Villager_FindMemory(villager->villagerData, PlayerData_GetCurrent()->getPlayerId());
        }
        if (r7) {
            r6 = r7->getFriendship();
        }
        s32 d = 0xff - r6;
        float f;
        if (d > 0) {
            f = 0.5f + (float)(d << 12);
        } else {
            f = (float)(d << 12) - 0.5f;
        }
        s32 v = (s32)f;
        salePrice = FX_Div(func_01ffcb0c(salePrice, v), 0x200000);
        r6 = salePrice;
        s32 k = r6 / 10 * 10;
        if (r6 - k >= 5) {
            k += 10;
        }
        salePrice = k;
        setNumberSlot(salePrice, 3, 10, 1, 0);
        r6 = 0;
        if (villager->villagerData) {
            w = 0xfff1;
            r6 = 10 - Villager_CountFurnitureLike((VillagerData *)villager->villagerData, &w);
        }
        if (!(villager->saleUnitX != -1 && Pocket_FindEmpty() != -1 && r6 > 3 && NpcActor_CanPlayerPay(villager, salePrice))) {
            ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506f0, 0x28, "q11_trade4");
        } else {
            ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506f0, 0x28, "q11_trade3");
        }
        out->msgKey = (const char *)data_ov004_022506f0;
        out->msgIndex = Random_GlobalBelow(3);
    } else {
        switch (villager->talkStage) {
        case 0:
            ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506f0, 0x28, "ev_fmarket2");
            out->msgIndex = Random_GlobalBelow(3);
            break;
        case 1:
            ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506f0, 0x28, "q11_trade1");
            out->msgIndex = Random_GlobalBelow(3);
            break;
        case 2:
            ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506f0, 0x28, "ev_fmarket2");
            out->msgIndex = Random_GlobalBelow(3) + 6;
            break;
        }
        out->msgKey = (const char *)data_ov004_022506f0;
    }
}

BOOL FleaMarketSellerVillager::canPlayTalkMelody() {
    BOOL f = gFieldSceneKind == 1 ? TRUE : FALSE;
    if (!f || talkMelodyPlayed == 0) {
        return TRUE;
    }
    return FALSE;
}

void FleaMarketSellerVillager::onTalkMelodyPlayed() { talkMelodyPlayed = 1; }

void FleaMarketSellerVillagerTalk::onMessageEnd(u32) {}

void FleaMarketSellerVillagerTalk::onChoice(u32) {
    s32 r6 = getChoiceList()->getResult();
    u32 r4 = 0xff;
    u8 *s;
    if (villager->talkStage == 1) {
        switch (msgIndex) {
        case 0:
        case 1:
        case 2:
            s = data_ov004_022506c8;
            r4 = (u8)Random_GlobalBelow(3);
            if (r6 == 0) {
                ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506c8, 0x28, "q11_trade2");
                Hud_Hide();
                villager->talkStage = 2;
            } else {
                ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506c8, 0x28, "q_no");
            }
            break;
        }
    } else if (villager->talkStage == 2) {
        switch (msgIndex) {
        case 0:
        case 1:
        case 2:
            if (r6 == 0) {
                ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506c8, 0x28, "q11_yes");
                sellFurniture();
            } else {
                ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022506c8, 0x28, "q11_no");
            }
            s = data_ov004_022506c8;
            r4 = (u8)Random_GlobalBelow(3);
            break;
        }
    }
    if (r4 != 0xff) {
        u8 b = r4;
        window->setNextMessage(&b, s);
    }
}

BOOL FleaMarketSellerVillager::acceptsInteraction(void *) {
    if (talkCtrl.isBusy() != 0 || requestTradeTalk()) {
        return FALSE;
    }
    return TRUE;
}

BOOL FleaMarketSellerVillager::acceptsSelfRequestedInteraction(void *) {
    if (talkCtrl.isBusy() == 0) {
        return TRUE;
    }
    return FALSE;
}

void FleaMarketSellerVillager::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 1:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        if (talkStage == 0) {
            changeAct(1);
        } else if (talkStage == 3) {
            changeAct(3);
        } else {
            changeAct(7);
        }
        break;
    case 0:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(1);
        break;
    case 8:
        changeAct(4);
        break;
    }
}

BOOL FleaMarketSellerVillager::checkFurnitureTap() {
    u16 r[4];
    s32 hx, hy;
    s32 ax, ay;
    s32 x2, y2;
    VecFx32 v0;
    VecFx32 v1;
    Actor *p = (Actor *)PlayerActor_GetActor(4);
    BOOL flag = Unk_ov004_02217954_Both() ? TRUE : FALSE;
    if (talkStage != 2) {
        return FALSE;
    }
    if (p != NULL && TalkRequest_IsActive() == 0 && talkCtrl.isBusy() == 0 && ((gPad[1] & 1) != 0 || flag)) {
    } else {
        return FALSE;
    }
    VecFx32 *pv = &p->position;
    v0.x = p->position.x;
    v0.y = pv->y;
    v0.z = pv->z;
    s32 idx = ((u16)p->rotY >> 4) * 2;
    v0.x = v0.x + func_01ffcb0c(0x2000, data_02135f44[idx * 1]);
    v0.z = v0.z + func_01ffcb0c(0x2000, data_02135f44[idx + 1]);
    hx = 0;
    hy = 0;
    FieldPos_ToUnit(&hx, &hy, &v0);
    if (flag) {
        s32 t = FtrActorGrid_GetInstance()->getIndex(hx, hy, 0);
        BOOL z = FALSE;
        if (t == -1) {
            return z;
        }
        FtrActor *c = FtrActorGrid_GetInstance()->getActor(hx, hy, 0);
        if (c != NULL) {
            if (c != TouchPick_GetTargetObject(Scene_GetTouchPicker(), 0, 0)) {
                return FALSE;
            }
        } else {
            ax = 0;
            ay = 0;
            TouchPick_GetGroundPos(Scene_GetTouchPicker(), &v1);
            FieldPos_ToUnit(&ax, &ay, &v1);
            if (ax != hx || ay != hy) {
                return FALSE;
            }
        }
    }
    FtrActor *c2 = FtrActorGrid_GetInstance()->getActor(hx, hy, 0);
    if (c2 == NULL) {
        return FALSE;
    }
    r[0] = Item_MakeFurniture(FtrActor_GetFtrIndex(c2), 0);
    x2 = hx;
    y2 = hy;
    c2->findOwnTile(&x2, &y2, 0, 0);
    hx = x2;
    hy = y2;
    saleItem = r[0];
    if (getVillagerData()) {
        if (Villager_HasShownFurnitureAt((VillagerData *)getVillagerData(), (u32 *)&hx, layoutData, layoutSize)) {
            BOOL e1;
            if (Item_IsFurniture(&saleItem)) {
                r[1] = 0x409c;
                e1 = Item_GetFurnitureIndex(&saleItem) == Item_GetFurnitureIndex(&r[1]) ? TRUE : FALSE;
            } else {
                e1 = saleItem == 0x409c ? TRUE : FALSE;
            }
            if (e1) {
                goto fail;
            }
            BOOL e2;
            if (Item_IsFurniture(&saleItem)) {
                r[2] = 0x40a0;
                e2 = Item_GetFurnitureIndex(&saleItem) == Item_GetFurnitureIndex(&r[2]) ? TRUE : FALSE;
            } else {
                e2 = saleItem == 0x40a0 ? TRUE : FALSE;
            }
            if (e2) {
                goto fail;
            }
            BOOL e3;
            if (Item_IsFurniture(&saleItem)) {
                r[3] = 0x3820;
                e3 = Item_GetFurnitureIndex(&saleItem) == Item_GetFurnitureIndex(&r[3]) ? TRUE : FALSE;
            } else {
                e3 = saleItem == 0x3820 ? TRUE : FALSE;
            }
            if (e3) {
                goto fail;
            }
            saleUnitX = hx;
            saleUnitY = hy;
            goto done;
        }
    }
fail:
    saleUnitX = -1;
    saleUnitY = -1;
done:
    return TRUE;
}

BOOL FleaMarketSellerVillager::requestTradeTalk() {
    if (checkFurnitureTap()) {
        TalkRequest_AddPlayerTalk6(this, 0);
        return TRUE;
    }
    return FALSE;
}

BOOL FleaMarketSellerVillager::checkPlayerLeaving() {
    VecFx32 v;
    VecFx32 *s = (VecFx32 *)PlayerActor_GetBodyPos(4);
    v.x = s->x;
    v.y = s->y;
    v.z = s->z;
    if (Ground_IsOnLockedExit(&v)) {
        talkStage = 3;
        TalkRequest_AddPlayerTalk6(this, 0);
        return TRUE;
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0221789c) {
    HOST_OVERLAY_VAR(sFleaMarketSellerVillagerProfile),
    HOST_OVERLAY_VAR(data_ov004_022506c8),
    HOST_OVERLAY_VAR(data_ov004_022506f0),
    HOST_OVERLAY_VAR(sFleaMarketSellerActTable),
    HOST_OVERLAY_VARS_END
};
