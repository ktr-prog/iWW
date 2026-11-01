#include "uptr.h"
#include "host_tick.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "game/FxVec3.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "talk/TalkWindowState.h"
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/VillagerTalk.h"
#include "npc/BirthdayHostVillager.h"
#include "item/ItemPickSpec.h"
#include "npc/NpcActionCtrl.h"
#include "npc/NpcFootstepFx.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/NpcTalkCtrl.h"
#include "npc/VillagerId.h"
#include "talk/ChoiceList.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov004/unk_ov004_02214948.h"
#include "proto/ov004/unk_ov004_02215f04.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "player/PlayerData.h"
#include "save/VillagerData.h"
#include "npc/VillagerPlan.h"
#include "npc/BirthdayGuestVillager.h"

extern "C" {
s16 Math_Atan2(s32 x, s32 y);
s32 Math_AngleDiffAbs(s32 a, s32 b);
s32 Vec_NotEqual(VecFx32 *a, VecFx32 *b);
s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
s32 TalkRequest_SetTargetDone(void *);
s32 TalkRequest_AddPlayerTalk6(void *, u32);
extern u16 data_020c6cc8;
extern s32 data_020c6d1c;
extern u8 gVec3Zero[];
extern u8 gTalkMsgIndexEnd[];
s32 Item_GetPrice(u16 *);
void *Villager_GetPlan(void *);
s32 Item_IsFurniture(u16 *);
void Camera_FocusOnPoint(VecFx32 *p);
void Camera_SetModeDefault();
VillagerMemory *Villager_FindOrCreateMemory(VillagerMemory *t, void *b);
void VillagerMemory_RecordTalk(VillagerMemory *self, void *a, u8 *b, u8 *c);
s32 Item_GetFurnitureIndex(u16 *p);
extern s32 data_020c8cb4;
extern s32 data_020c8cb8;
}

extern "C" DebugColor data_ov004_022503c0(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov004_022503dc(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_022503c4(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_022503bc(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_022503cc(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_022503d0(0x14, 0x18, 0x18, 0x1f);
extern "C" ActorProfile sBirthdayHostVillagerProfile = { (void *(*)())BirthdayHostVillager_Create, 0x80, 0x84, 2, 0x5000, 0x5000, 0x3e800 };
extern "C" {
BirthdayHostVillager *sBirthdayHostVillager;
}


static inline BOOL Unk_ov004_022158c4_Range(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}

typedef void (BirthdayHostVillager::*Unk_ov004_022150f0_Fn)();
typedef BOOL (BirthdayHostVillager::*Unk_ov004_02215208_Fn)();

extern "C" BirthdayHostVillager *BirthdayHostVillager_Create() {
    return new BirthdayHostVillager();
}

extern "C" BirthdayHostVillager *BirthdayHostVillager_Get() { return sBirthdayHostVillager; }

extern "C" BOOL BirthdayHostVillager_HasReceivedGift() {
    BirthdayHostVillager *o = sBirthdayHostVillager;
    if (o) {
        return o->talk.hasReceivedGift();
    }
    return FALSE;
}

extern "C" BOOL BirthdayHost_GiftFilter(u16 *p, s32 flag) {
    if (flag == 0) {
        BOOL eq;
        if (Item_IsFurniture(p)) {
            u16 v = 0xfff1;
            s32 a = Item_GetFurnitureIndex(p);
            if (a == Item_GetFurnitureIndex(&v)) {
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
        if (eq == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

FxVec3 BirthdayHostVillager_preCreate_vs[6] = {
        FxVec3(0, 0, 0), FxVec3(-0x2000, 0, 0), FxVec3(-0x4000, 0, 0),
        FxVec3(0x2000, 0, 0), FxVec3(0, 0, 0x2000), FxVec3(-0x2000, 0, 0x2000)
    };
BOOL BirthdayHostVillager::preCreate() {
    if (!VillagerActor::preCreate()) {
        return FALSE;
    }
    position.x = data_020c8cb4 + 0x1000;
    position.z = data_020c8cb8 - 0x7000;
    u32 i;
    for (i = 0; i < 6; i++) {
        VecFx32 t;
        Vec_Add(&t, &position, &BirthdayHostVillager_preCreate_vs[i]);
        if (!FtrMgr_GetSurfaceHeightAtPos(&t)) {
            position.x = t.x;
            position.y = t.y;
            position.z = t.z;
            break;
        }
    }
    rotY = 0;
    setTalkRequest(&talk);
    talk.attachOwner(this);
    if (!talk.isPartyNotGreeted()) {
        changeAct(0);
    } else {
        changeAct(7);
        talk.setPartyGreeted();
    }
    sBirthdayHostVillager = this;
    return TRUE;
}

extern "C" Unk_ov004_0224c034_Fn data_ov004_0224befc = &BirthdayHostVillager::drawModel;
extern "C" {
u8 sBirthdayHostMsgFile[0x28];
}

BOOL BirthdayHostVillager::onCreate() {
    if (!VillagerActor::onCreate()) {
        return FALSE;
    }
    drawFn = data_ov004_0224befc;
    footstepFx.enableFootsteps();
    return TRUE;
}

BOOL BirthdayHostVillager::drawModel() {
    if (NpcActor::onDraw()) {
        return TRUE;
    }
    return FALSE;
}

BOOL BirthdayHostVillager::onDraw() {
    if (drawFn) {
        return (this->*drawFn)();
    }
    return TRUE;
}

BOOL BirthdayHostVillager::preDelete() {
    if (!VillagerActor::preDelete()) {
        return FALSE;
    }
    sBirthdayHostVillager = NULL;
    return TRUE;
}

BOOL BirthdayHostVillager::updateAct() {
    execAct();
    return TRUE;
}

void BirthdayHostVillager::recordPlayerTalk() {
    PlayerData *o = PlayerData_GetCurrent();
    if (o != NULL && villagerData != NULL) {
        PlayerId *r = o->getPlayerId();
        VillagerMemory *p = Villager_FindOrCreateMemory(((VillagerData *)villagerData)->memories, r);
        VillagerMemory_RecordTalk(p, 0, 0, 0);
    }
}

BOOL BirthdayHostVillager::acceptsInteraction(void *) {
    if (talkCtrl.isBusy()) {
        return FALSE;
    }
    if (act <= 3) {
        return TRUE;
    }
    return FALSE;
}

BOOL BirthdayHostVillager::acceptsSelfRequestedInteraction(void *) {
    if (talkCtrl.isBusy() == 0) {
        return TRUE;
    }
    return FALSE;
}

void BirthdayHostVillager::onInteractionEvent(u32 a, u8 b) {
    VecFx32 v;
    v.x = position.x;
    v.y = position.y;
    v.z = position.z;
    v.y = v.y + 0x2000;
    switch (a) {
    case 3:
        partnerPlayer = b;
        changeAct(4);
        break;
    case 0:
        partnerPlayer = b;
        talk.setTalkPlayer(getPlayerActor(4));
        Camera_FocusOnPoint(&v);
        changeAct(5);
        break;
    case 1:
        partnerPlayer = b;
        talk.setTalkPlayer(getPlayerActor(4));
        Camera_FocusOnPoint(&v);
        changeAct(8);
        break;
    case 8:
        Camera_SetModeDefault();
        recordPlayerTalk();
        changeAct(0);
        break;
    case 4:
        changeAct(0);
        break;
    case 2:
    case 5:
    case 6:
    case 7:
        break;
    }
}

VillagerMemory *BirthdayHostVillagerTalk::getPlayerMemory() {
    if (villager != NULL && villager->villagerData != NULL) {
        PlayerId *r = PlayerData_GetCurrent()->getPlayerId();
        return Villager_FindOrCreateMemory(((VillagerData *)villager->villagerData)->memories, r);
    }
    return NULL;
}

BOOL BirthdayHostVillagerTalk::isPartyNotGreeted() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        if (p->isPartyGreeted() == 0) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

void BirthdayHostVillagerTalk::setPartyGreeted() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        p->setPartyGreeted();
    }
}

BOOL BirthdayHostVillagerTalk::isNotTalkedYet() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        if (p->isTalkedToday() == 0) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

void BirthdayHostVillagerTalk::setTalked() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        p->setTalkedToday();
    }
}

u32 BirthdayHostVillagerTalk::hasReceivedGift() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        return p->isPartyGiftReceived();
    }
    return 0;
}

void BirthdayHostVillagerTalk::setReceivedGift() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        p->setPartyGiftReceived();
    }
}

BOOL BirthdayHostVillagerTalk::isLikedGift(u16 *p) {
    BOOL r;
    if (villager && villager->villagerData) {
        u32 c = ((VillagerPlan *)VillagerPlanBlock_GetPlan(Villager_GetPlan(villager->villagerData)))->getState();
        r = FALSE;
        switch (c) {
        case 0:
            if (*p >= 0x12b0 && *p <= 0x12e7) r = TRUE;
            break;
        case 1:
            if (*p >= 0x12e8 && *p <= 0x131f) r = TRUE;
            break;
        case 2:
            if (*p >= 0x450c && *p <= 0x45db) r = TRUE;
            break;
        case 3:
            if (*p >= 0x11a8 && *p <= 0x12a7) r = TRUE;
            break;
        case 4:
            if (Item_IsFurniture(p)) {
                if (!Unk_ov004_022158c4_Range(p, 0x450c, 0x45db)) r = TRUE;
            }
            break;
        }
        return r;
    }
    return FALSE;
}

void BirthdayHostVillagerTalk::addFriendship(s32 v) {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        p->addFriendship(v);
    }
}

s32 BirthdayHostVillagerTalk::getFriendship() {
    VillagerMemory *p = getPlayerMemory();
    if (p) {
        return p->getFriendship();
    }
    return 0;
}

void BirthdayHostVillagerTalk::onTaskDone(u32) {
    if (villager->act == 0xc) {
        window->nextState = 1;
    }
}

void BirthdayHostVillagerTalk::update() {
    u8 b0, b1, b2;
    u16 x;
    if (villager->act == 0xb) {
        if (MenuCtrl_IsFinished()) {
            if (MenuCtrl_IsResultOk() == 0) {
                window->nextState = 1;
                b0 = Random_GlobalBelow(2) + 7;
                window->setNextMessage((u8 *)(&b0), (void *)(0));
                villager->changeAct(6);
            } else {
                u32 r6 = MenuCtrl_GetIndex();
                x = Pocket_GetItem(r6);
                s32 r4 = Item_GetPrice(&x);
                Pocket_RemoveItem(r6);
                setItemNameSlot(&x, 0, 7);
                if (isLikedGift(&x)) {
                    b1 = Random_GlobalBelow(2) + 0xd;
                    window->setNextMessage((u8 *)(&b1), (void *)(0));
                    addFriendship(5);
                    if (r4 >= 1000) addFriendship(5);
                    if (r4 >= 2000) addFriendship(10);
                    requestTakeItem((u16 *)(&x), 0, 5, 0);
                    villager->changeAct(12);
                } else {
                    b2 = Random_GlobalBelow(2) + 0xb;
                    window->setNextMessage((u8 *)(&b2), (void *)(0));
                    addFriendship(2);
                    if (r4 >= 1000) addFriendship(5);
                    if (r4 >= 2000) addFriendship(5);
                    requestTakeItem((u16 *)(&x), 0, 5, 0);
                    villager->changeAct(12);
                }
            }
        }
    }
}

void BirthdayHostVillagerTalk::attachOwner(BirthdayHostVillager *owner) {
    begin(owner, 0x11);
    villager = owner;
}

void BirthdayHostVillagerTalk::start(TalkStartMsg *arg) {
    ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(sBirthdayHostMsgFile, 0x28, "ev_nbirth");
    arg->msgKey = (const char *)sBirthdayHostMsgFile;
    if (villager->act == 9) {
        arg->msgIndex = Random_GlobalBelow(2);
    } else {
        s32 k = 3;
        if (this->isNotTalkedYet()) {
            k = 1;
        } else if (this->hasReceivedGift()) {
            k = 2;
        }
        this->setTalked();
        switch (k) {
        case 1:
            arg->msgIndex = Random_GlobalBelow(2) + 2;
            break;
        case 2:
            arg->msgIndex = Random_GlobalBelow(4) + 0x13;
            break;
        default:
            arg->msgIndex = Random_GlobalBelow(2) + 4;
            break;
        }
        BirthdayHostVillager *p = villager;
        if (p->talk.window) {
            if (p && p->villagerData) {
                villager->talk.setVillagerNameSlot(((VillagerData *)p->villagerData)->getVillagerId(), 1);
            }
            s32 i = 0;
            BirthdayHostVillager **pp = &villager;
            goto test;
            for (;;) {
                VillagerActor *q;
                q = (VillagerActor *)NpcRegistry_GetVillager(i);
                if (q && q != *pp) {
                    villager->talk.setVillagerNameSlot(((VillagerData *)q->villagerData)->getVillagerId(), 0);
                    break;
                }
                i++;
            test:
                if (i >= NpcRegistry_GetSlotCount()) break;
            }
            u16 w = 0x1100;
            setItemNameSlot(&w, 0, 7);
            setItemNameSlot(&w, 1, 7);
        }
    }
}

extern "C" u16 BirthdayHost_PickReturnGift(s32 n) {
    u16 w0, w1, w2, w3, w4;
    if (n <= 0) {
        ItemPickSpec o;
        o.set(1, 0);
        ItemPick_One(&w1, &o, 0, 0, 1, 1, 0);
        return w1;
    }
    if (n <= 0x3f) {
        if (Random_GlobalBelow(2) == 0) {
            ItemPickSpec o;
            o.set(0, 0);
            ItemPick_One(&w2, &o, 0, 0, 1, 1, 0);
            return w2;
        } else {
            ItemPickSpec o;
            o.set(2, 0);
            ItemPick_One(&w3, &o, 0, 0, 1, 1, 0);
            return w3;
        }
    }
    ItemPick_FtrWallCarpetByClass(&w0, (u8 *)PlayerData_GetCurrent(), 0);
    if (w0 == 0xfff1) {
        ItemPickSpec o;
        o.set(0, 0);
        ItemPick_One(&w4, &o, 0, 0, 1, 1, 0);
        return w4;
    }
    return w0;
}

void BirthdayHostVillagerTalk::onMessageStart(u32) {
    switch (msgIndex) {
    case 0xf:
    case 0x10: {
        volatile u16 v;
        v = BirthdayHost_PickReturnGift(getFriendship());
        villager->returnGift = v;
        setItemNameSlot((u16 *)&v, 1, 7);
        break;
    }
    }
}

void BirthdayHostVillagerTalk::onMessageEnd(u32) {
    u8 b[3];
    switch (msgIndex) {
    case 4:
    case 5:
    case 6:
        break;
    case 7:
    case 8:
        b[0] = gTalkMsgIndexEnd[0];
        window->setNextMessageIfUnset((u8 *)(&b[0]), (void *)(0));
        break;
    case 9:
    case 10:
        villager->changeAct(10);
        break;
    case 11:
    case 12:
    case 13:
    case 14:
        b[1] = Random_GlobalBelow(2) + 0xf;
        villager->talk.window->setNextMessage((u8 *)(&b[1]), (void *)(0));
        break;
    case 15:
    case 16:
        requestGiveItem((u16 *)(&villager->returnGift), 0, 5, 0);
        Pocket_AddItem(&villager->returnGift, 0);
        villager->changeAct(13);
        break;
    case 17:
    case 18:
        this->setReceivedGift();
        break;
    case 19:
    case 20:
    case 21:
    case 22:
        b[2] = gTalkMsgIndexEnd[0];
        window->setNextMessageIfUnset((u8 *)(&b[2]), (void *)(0));
        break;
    }
}

void BirthdayHostVillagerTalk::onChoice(u32) {
    u8 b[3];
    s32 r = villager->talk.window->getChoiceList()->getResult();
    switch (msgIndex) {
    case 4:
    case 5:
        if (r == 0) {
            if (MenuCtrl_BuildPocketMask(BirthdayHost_GiftFilter)) {
                b[0] = Random_GlobalBelow(2) + 9;
                villager->talk.window->setNextMessage((u8 *)(&b[0]), (void *)(0));
            } else {
                b[1] = 6;
                villager->talk.window->setNextMessage((u8 *)(&b[1]), (void *)(0));
            }
        } else {
            b[2] = Random_GlobalBelow(2) + 7;
            villager->talk.window->setNextMessage((u8 *)(&b[2]), (void *)(0));
        }
        break;
    }
}

BOOL BirthdayHostVillager::changeAct(s32 idx) {
    static Unk_ov004_02215208_Fn tbl[14] = {
        &BirthdayHostVillager::setupAct00,
        &BirthdayHostVillager::setupAct01,
        &BirthdayHostVillager::setupAct02,
        &BirthdayHostVillager::setupAct03,
        &BirthdayHostVillager::setupAct04,
        &BirthdayHostVillager::setupAct05,
        &BirthdayHostVillager::setupAct06,
        &BirthdayHostVillager::setupAct07,
        &BirthdayHostVillager::setupAct08,
        &BirthdayHostVillager::setupAct09,
        &BirthdayHostVillager::setupAct0A,
        &BirthdayHostVillager::setupAct0B,
        &BirthdayHostVillager::setupAct0C,
        &BirthdayHostVillager::setupAct0D,
    };
    if (idx < 14) {
        if ((this->*tbl[idx])()) {
            act = idx;
            return TRUE;
        }
    }
    return FALSE;
}

void BirthdayHostVillager::execAct() {
    static Unk_ov004_022150f0_Fn tbl[14] = {
        &BirthdayHostVillager::mainAct00,
        &BirthdayHostVillager::mainAct01,
        &BirthdayHostVillager::mainAct02,
        &BirthdayHostVillager::mainAct03,
        &BirthdayHostVillager::mainAct04,
        &BirthdayHostVillager::mainAct05,
        &BirthdayHostVillager::mainAct06,
        &BirthdayHostVillager::mainAct07,
        &BirthdayHostVillager::mainAct08,
        &BirthdayHostVillager::mainAct09,
        &BirthdayHostVillager::mainAct0A,
        &BirthdayHostVillager::mainAct0B,
        &BirthdayHostVillager::mainAct0C,
        &BirthdayHostVillager::mainAct0D,
    };
    if (act < 14) {
        (this->*tbl[act])();
    }
}

BOOL BirthdayHostVillager::setupAct00() {
    if (actionCtrl.requestStand(1, data_020c6cc8)) {
        lookAt.setTarget(1, 0, NULL, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
        return TRUE;
    }
    return FALSE;
}

void BirthdayHostVillager::mainAct00() {
    VecFx32 c;
    if (collider.isHit != 0 && actionCtrl.getAction() == 1) {
        actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        return;
    }
    if (actionCtrl.getAction() == 0) {
        if (walkTimer != 0) {
            walkTimer -= TICK_STEP_ENDS() ? 1 : 0;
        }
        if (walkTimer == 0) {
            walkAngle = Room_PickRandomWalkTarget(&walkTarget, &position, rotY);
            waypoint.x = walkTarget.x;
            waypoint.y = walkTarget.y;
            waypoint.z = walkTarget.z;
            if (walkAngle != rotY) {
                if (actionCtrl.requestAction(3, 1, 0, 0, 0, walkAngle, 0, 0, data_020c6cc8, 0) != 0) {
                    walkTimer = Random_GlobalBelow(0x46) + 0x14;
                }
            } else {
                if (actionCtrl.requestAction(1, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0) != 0) {
                    walkTimer = Random_GlobalBelow(0x50) + 0x14;
                }
            }
        } else {
            if (actionCtrl.isActionDone() != 0) {
                actionCtrl.requestStand(1, data_020c6cc8);
            }
        }
    } else if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone() != 0) {
            actionCtrl.requestAction(1, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    } else if (actionCtrl.getAction() == 1) {
        switch (findAvoidPos(&c)) {
        case 1:
            actionCtrl.requestStand(1, data_020c6cc8);
            break;
        case 2:
            waypoint.x = c.x;
            waypoint.y = c.y;
            waypoint.z = c.z;
            moveCtrl.setWaypoint(&waypoint);
            break;
        default:
            if (Vec_NotEqual(&waypoint, &walkTarget) != 0) {
                waypoint.x = walkTarget.x;
                waypoint.y = walkTarget.y;
                waypoint.z = walkTarget.z;
                moveCtrl.setWaypoint(&walkTarget);
            } else if (Vec_DistXZ(&walkTarget, &position) < 0x200) {
                actionCtrl.requestStand(1, data_020c6cc8);
            }
            break;
        }
    }
}

BOOL BirthdayHostVillager::setupAct01() {
    Actor *o = BirthdayGuestVillager_Get();
    if (o != 0) {
        s32 dx = o->position.x - position.x;
        s32 dz = o->position.z - position.z;
        s32 ang = Math_Atan2(dx, dz);
        actionCtrl.requestAction(3, 1, 0, 0, 0, ang, 0, 0, data_020c6cc8, 0);
        lookAt.setTarget(2, 0, (Character *)o, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
        return TRUE;
    }
    return FALSE;
}

void BirthdayHostVillager::mainAct01() {}

BOOL BirthdayHostVillager::setupAct02() {
    emotionTimer = 0x1e;
    return TRUE;
}

void BirthdayHostVillager::mainAct02() {
    if (emotionTimer != 0) {
        emotionTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    switch (emotionTimer) {
    case 0x14:
        actionCtrl.requestEmotion(1, 3, data_020c6cc8);
        break;
    case 1:
        actionCtrl.requestEmotion(1, 0, data_020c6cc8);
        break;
    case 0:
        changeAct(0);
        break;
    }
}

BOOL BirthdayHostVillager::setupAct03() {
    emotionTimer = 0x32;
    return TRUE;
}

void BirthdayHostVillager::mainAct03() {
    if (emotionTimer != 0) {
        emotionTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    switch (emotionTimer) {
    case 0x28:
        if (Random_GlobalBelow(2) == 0) {
            actionCtrl.requestEmotion(1, 0xa, data_020c6cc8);
        } else {
            actionCtrl.requestEmotion(1, 0x17, data_020c6cc8);
        }
        break;
    case 1:
        actionCtrl.requestEmotion(1, 0, data_020c6cc8);
        break;
    case 0:
        changeAct(0);
        break;
    }
}

BOOL BirthdayHostVillager::setupAct04() {
    if ((u32)(act - 1) <= 2) {
        actionCtrl.requestEmotion(2, 0, data_020c6cc8);
    }
    return TRUE;
}

void BirthdayHostVillager::mainAct04() {}

BOOL BirthdayHostVillager::setupAct05() {
    BOOL r;
    void *o = PlayerActor_GetActor(4);
    if (o != 0) {
        talkCtrl.requestTurnAndTalk(0, getAngleTo((NpcActor *)(o)), 0);
        r = TRUE;
    } else {
        r = FALSE;
    }
    return r;
}

void BirthdayHostVillager::mainAct05() {
    changeAct(6);
}

BOOL BirthdayHostVillager::setupAct06() { return TRUE; }

void BirthdayHostVillager::mainAct06() {
    TalkWindowState *o = talk.window;
    if (o != 0) {
        if (o->state == 0) {
            TalkRequest_SetTargetDone(this);
        }
    }
}

BOOL BirthdayHostVillager::setupAct07() { return TRUE; }

void BirthdayHostVillager::mainAct07() {
    TalkRequest_AddPlayerTalk6(this, 0);
}

BOOL BirthdayHostVillager::setupAct08() {
    approachTimer = 0x32;
    actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

void BirthdayHostVillager::mainAct08() {
    VecFx32 a, b;
    s32 v, r4, r0;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    a.x = p->x;
    a.y = p->y;
    a.z = p->z;
    b.x = a.x;
    b.y = a.y;
    b.z = a.z;
    v = getDistanceToPlayer(4);
    if (v > 0x4000) {
        if (actionCtrl.getAction() == 1) {
            actionCtrl.requestAction(2, 1, 0, 0, 0x800, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (actionCtrl.getAction() == 2) {
            actionCtrl.requestAction(1, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    moveCtrl.setWaypoint(&b);
    if (approachTimer != 0) {
        approachTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    r4 = Math_AngleXZ(&position, &a);
    r0 = Math_AngleDiffAbs(rotY, r4);
    if (v <= 0x3000 || approachTimer == 0) {
        talkCtrl.requestTurnAndTalk(0, r4, 0);
        changeAct(9);
    } else if (r0 > 0x2000) {
        actionCtrl.requestAction(4, 2, b.x, b.z, 0, r4, 0, 0, data_020c6cc8, 0);
    }
}

BOOL BirthdayHostVillager::setupAct09() { return TRUE; }

void BirthdayHostVillager::mainAct09() {
    TalkWindowState *o = talk.window;
    if (o != 0) {
        if (o->state == 0) {
            TalkRequest_SetTargetDone(this);
        }
    }
}

BOOL BirthdayHostVillager::setupAct0A() {
    talk.window->openMode = 1;
    return TRUE;
}

void BirthdayHostVillager::mainAct0A() {
    if (talk.window->state == 5) {
        if (MenuCtrl_OpenPocketSelect(MenuCtrl_BuildPocketMask(BirthdayHost_GiftFilter), 0xd) != 0) {
            changeAct(0xb);
        }
    }
}

BOOL BirthdayHostVillager::setupAct0B() { return TRUE; }

void BirthdayHostVillager::mainAct0B() {}

BOOL BirthdayHostVillager::setupAct0C() { return TRUE; }

void BirthdayHostVillager::mainAct0C() {}

BOOL BirthdayHostVillager::setupAct0D() { return TRUE; }

void BirthdayHostVillager::mainAct0D() {
    u8 buf[1];
    buf[0] = Random_GlobalBelow(2) + 0x11;
    talk.window->setNextMessage(buf, 0);
    changeAct(6);
}

void BirthdayHostVillager::onTalkMelodyPlayed() {
    talkMelodyPlayed = 1;
}

BOOL BirthdayHostVillager::canPlayTalkMelody() {
    if (talkMelodyPlayed == 0) {
        return TRUE;
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02214948) {
    HOST_OVERLAY_VAR(data_ov004_022503c0),
    HOST_OVERLAY_VAR(data_ov004_022503dc),
    HOST_OVERLAY_VAR(data_ov004_022503c4),
    HOST_OVERLAY_VAR(data_ov004_022503bc),
    HOST_OVERLAY_VAR(data_ov004_022503cc),
    HOST_OVERLAY_VAR(data_ov004_022503d0),
    HOST_OVERLAY_VAR(sBirthdayHostVillagerProfile),
    HOST_OVERLAY_VAR(sBirthdayHostVillager),
    HOST_OVERLAY_VAR(BirthdayHostVillager_preCreate_vs),
    HOST_OVERLAY_VAR(data_ov004_0224befc),
    HOST_OVERLAY_VAR(sBirthdayHostMsgFile),
    HOST_OVERLAY_VARS_END
};
