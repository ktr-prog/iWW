#include "uptr.h"
#include "host_tick.h"
#include "npc/VillagerState.h"
#include "types.h"
#include "actor/ActorProfile.h"
#include "npc/VillagerClothModel.h"
#include "room/RoomFreeUnitMap.h"
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
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "net/CommManager.h"
#include "npc/VillagerId.h"
#include "talk/ActorTalkRequest.h"
#include "talk/VillagerTalk.h"
#include "save/VillagerData.h"
#include "save/VillagerData.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov004/unk_ov004_02216ccc.h"

class HouseOwnerVillager;

class HouseOwnerAi;

typedef BOOL (HouseOwnerAi::*Unk_ov004_02216ff4_Fn)(HouseOwnerVillager *);
typedef void (HouseOwnerAi::*Unk_ov004_02216ff4_VFn)(HouseOwnerVillager *);

struct HouseOwnerStepDir {
    s32 dx;
    s32 dy;
    constexpr HouseOwnerStepDir(s32 a, s32 b) : dx(a), dy(b) {}
};

struct HouseOwnerAiState {
    Unk_ov004_02216ff4_Fn enter;
    Unk_ov004_02216ff4_Fn update;
};


extern "C" {
extern HouseOwnerStepDir sHouseOwnerStepDirs[4];
extern HouseOwnerAiState sHouseOwnerAiStates[];
extern CommManager *gCommManager;
extern u16 data_020c6cc8;
extern const u8 data_ov004_02240090[4];
extern const u8 data_ov004_02240094[5];

s32 Villager_GetResidentStatus(void *);
void TalkRequest_SetTargetDone(void *);
void FieldPos_ToUnit(s32 *ox, s32 *oz, VecFx32 *v);
void FieldPos_FromUnitCenter(VecFx32 *v, s32 x, s32 z);
s32 Item_IsFurniture(u16 *p);
u32 Item_GetFurnitureIndex(u16 *p);
VillagerState *Villager_GetState(void *o);
u32 VillagerState_GetRole(void *o);
void VillagerState_SetRole(void *o, u32 a);
void *VillagerState_GetTalkRepeat(void *o);
void TalkRepeat_Reset(void *o);
}









class HouseOwnerAi {
public:
    BOOL enterState04(HouseOwnerVillager *o);
    void updateState01Step01(HouseOwnerVillager *o);
    BOOL updateState00(HouseOwnerVillager *o);
    BOOL updateState04(HouseOwnerVillager *o);
    BOOL enterState02(HouseOwnerVillager *o);
    BOOL updateState03(HouseOwnerVillager *o);
    BOOL enterState03(HouseOwnerVillager *o);
    BOOL updateState02(HouseOwnerVillager *o);
    void updateState01Step00(HouseOwnerVillager *o);
    BOOL updateState01(HouseOwnerVillager *o);
    BOOL enterState01(HouseOwnerVillager *o);
    void updateState02Step00(HouseOwnerVillager *o);
    BOOL enterState00(HouseOwnerVillager *o);
    BOOL findStepTarget(s32 *o1, s32 *o2, HouseOwnerVillager *o);
    BOOL applyPendingState(HouseOwnerVillager *o);
    void clearPendingState();
    void changeState(HouseOwnerVillager *o, s32 idx);
    void update(HouseOwnerVillager *o);

    /* 0x00 */ s32 state;
    /* 0x04 */ HouseOwnerAiState *entry;
    /* 0x08 */ s32 pendingState;
    /* 0x0c */ u8 step;
    /* 0x0d */ u8 pad_0d[3];
    /* 0x10 */ s32 timer;
};

class HouseOwnerAiMember : public HouseOwnerAi {
public:
    HouseOwnerAiMember();
    ~HouseOwnerAiMember();
};


class HouseOwnerVillager : public VillagerActor {
public:
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 idx, u8 v);
    virtual BOOL updateAct();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();

    BOOL drawModel();

    typedef BOOL (HouseOwnerVillager::*Fn)();
    /* 0x894 */ Fn drawFn;
    /* 0x89c */ HouseOwnerAiMember ai;
    /* 0x8b0 */ RoomFreeUnitMap freeUnitMap;
    /* 0x8d0 */ u8 talkMelodyPlayed;
    /* 0x8d4 */ s32 talkKind;
};

extern "C" ActorProfile sHouseOwnerVillagerProfile = {(void *(*)())HouseOwnerVillager_Create, 0x85, 0x89, 2, 0x5000, 0x5000, 0x3e800};
extern "C" const u8 data_ov004_02240090[4] = {0x28, 0x1e, 0x14, 0x0a};

extern "C" HouseOwnerVillager *HouseOwnerVillager_Create() {
    return new HouseOwnerVillager;
}

BOOL HouseOwnerVillager::preCreate() {
    if (!VillagerActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest(&villagerTalk);
    villagerTalk.resetMsg();
    RoomFreeUnitMap_Build(freeUnitMap.rows);
    talkKind = 0;
    talkMelodyPlayed = 0;
    void *p = getVillagerData();
    if (p) {
        if (((VillagerData *)p)->getVillagerId()->isValid()) {
            void *t = Villager_GetState(p);
            if (t) {
                TalkRepeat_Reset(VillagerState_GetTalkRepeat(t));
            }
        }
    }
    return TRUE;
}

BOOL HouseOwnerVillager::onCreate() {
    if (!VillagerActor::onCreate()) {
        return FALSE;
    }
    drawFn = &HouseOwnerVillager::drawModel;
    footstepFx.enableFootsteps();
    if (isNetOwner()) {
        ai.changeState(this, 0);
        updateCatchPlans((u8 *)data_ov004_02240094, (void *)data_ov004_02240090, 0);
    } else {
        ai.changeState(this, 3);
    }
    CommManager *g = gCommManager;
    if (!g->isSlotActive(g->myAid)) {
        if (getVillagerData()) {
            if (VillagerState_GetRole(Villager_GetState(getVillagerData())) == 1) {
                VillagerState_SetRole(Villager_GetState(getVillagerData()), 0);
            }
        }
    }
    return TRUE;
}

BOOL HouseOwnerVillager::drawModel() {
    if (NpcActor::onDraw()) {
        return TRUE;
    }
    return FALSE;
}

BOOL HouseOwnerVillager::onDraw() {
    BOOL r = TRUE;
    if (drawFn) {
        r = (this->*drawFn)();
    }
    return r;
}

BOOL HouseOwnerVillager::canPlayTalkMelody() {
    if (talkMelodyPlayed == 0) {
        return TRUE;
    }
    return FALSE;
}

void HouseOwnerVillager::onTalkMelodyPlayed() { talkMelodyPlayed = 1; }

BOOL HouseOwnerVillager::updateAct() {
    ai.update(this);
    if (gCommManager->isOnline()) {
        if (animCtrl.getAnimId(0) != 6) {
            if (getVillagerData()) {
                u16 *p = ((VillagerData *)getVillagerData())->getShirt();
                u16 *q = clothModel.getItem();
                BOOL eq;
                if (Item_IsFurniture(q)) {
                    eq = Item_GetFurnitureIndex(q) == Item_GetFurnitureIndex(p) ? TRUE : FALSE;
                } else {
                    eq = *q == *p ? TRUE : FALSE;
                }
                if (!eq) {
                    u16 *w = ((VillagerData *)getVillagerData())->getShirt();
                    BOOL in = FALSE;
                    u16 v = *w;
                    if (v >= 0x11a8 && v <= 0x12a7) {
                        in = TRUE;
                    }
                    if (in) {
                        clothModel.change(this, ((VillagerData *)getVillagerData())->getShirt());
                    }
                }
            }
        }
    }
    mood.update(this);
    return TRUE;
}

HouseOwnerAiMember::HouseOwnerAiMember() {
    pendingState = 5;
    timer = 0;
}

HouseOwnerAiMember::~HouseOwnerAiMember() {}

void HouseOwnerAi::update(HouseOwnerVillager *o) {
    if (entry != 0) {
        (this->*entry->update)(o);
    }
    if (timer > 0) {
        timer -= TICK_STEP_ENDS() ? 1 : 0;
    }
}

void HouseOwnerAi::changeState(HouseOwnerVillager *o, s32 idx) {
    if (idx >= 0 && idx < 5) {
        state = idx;
        entry = &sHouseOwnerAiStates[state];
        step = 0;
        HouseOwnerAiState *e = entry;
        if (e != 0 && e->enter != 0) {
            (this->*e->enter)(o);
        }
    }
}

void HouseOwnerAi::clearPendingState() {
    pendingState = 5;
}

BOOL HouseOwnerAi::applyPendingState(HouseOwnerVillager *o) {
    BOOL r = FALSE;
    if (pendingState < 5) {
        changeState(o, pendingState);
        clearPendingState();
        r = TRUE;
    }
    return r;
}

BOOL HouseOwnerAi::findStepTarget(s32 *o1, s32 *o2, HouseOwnerVillager *o) {
    s32 x, y;
    VecFx32 v;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    x = 0;
    y = 0;
    u8 dir = (o->rotY >> 14) & 3;
    FieldPos_ToUnit(&x, &y, &o->position);
    s32 px = x;
    s32 py = y;
    px += sHouseOwnerStepDirs[dir].dx;
    py += sHouseOwnerStepDirs[dir].dy;
    if ((u32) * (volatile s32 *)&y < 0xe) {
        if (RoomFreeUnitMap_TestUpper(o->freeUnitMap.rows, px, py) != 0) {
            FieldPos_FromUnitCenter(&v, px, py);
            *o1 = v.x;
            *o2 = v.z;
            return TRUE;
        }
    } else {
        if (RoomFreeUnitMap_Test(o->freeUnitMap.rows, px, py) != 0) {
            FieldPos_FromUnitCenter(&v, px, py);
            *o1 = v.x;
            *o2 = v.z;
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" const u8 data_ov004_02240094[5] = {0x00, 0x0a, 0x32, 0x0f, 0x14};
extern "C" HouseOwnerAiState sHouseOwnerAiStates[5] = {
    {&HouseOwnerAi::enterState00, &HouseOwnerAi::updateState00},
    {&HouseOwnerAi::enterState01, &HouseOwnerAi::updateState01},
    {&HouseOwnerAi::enterState02, &HouseOwnerAi::updateState02},
    {&HouseOwnerAi::enterState03, &HouseOwnerAi::updateState03},
    {&HouseOwnerAi::enterState04, &HouseOwnerAi::updateState04}};
extern "C" HouseOwnerStepDir sHouseOwnerStepDirs[4] = {
    HouseOwnerStepDir(0, 1), HouseOwnerStepDir(1, 0), HouseOwnerStepDir(0, -1), HouseOwnerStepDir(-1, 0)};

BOOL HouseOwnerAi::enterState00(HouseOwnerVillager *o) {
    o->drawFn = &HouseOwnerVillager::drawModel;
    o->actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    timer = 0;
    return TRUE;
}

BOOL HouseOwnerAi::updateState00(HouseOwnerVillager *o) {
    s32 a, b;
    if (o->actionCtrl.isActionDone() != 0) {
        a = 0;
        b = 0;
        if (Random_GlobalBelow(7) == 0) {
            if ((o->rotY & 0x3fff) != 0) {
                s32 v = (s32)(Random_GlobalBelow(4) << 30) >> 16;
                if (v == o->rotY) {
                    v = (s16)(v + 0x4000);
                }
                o->actionCtrl.requestAction(3, 1, 0, 0, 0, v, 0, 0, data_020c6cc8, 0);
            } else {
                if (Random_GlobalBelow(3) != 0 && findStepTarget(&a, &b, o) != 0) {
                    o->actionCtrl.requestAction(1, 1, a, b, 0, 0, 0, 0, data_020c6cc8, 0);
                    timer = 0x3c;
                } else {
                    s32 v = (s32)(Random_GlobalBelow(4) << 30) >> 16;
                    if (v == o->rotY) {
                        v = (s16)(v + 0x4000);
                    }
                    o->actionCtrl.requestAction(3, 1, 0, 0, 0, v, 0, 0, data_020c6cc8, 0);
                }
            }
        } else {
            o->actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    } else {
        if (timer == 0 && o->actionCtrl.getAction() == 1) {
            o->actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    return FALSE;
}

BOOL HouseOwnerAi::enterState01(HouseOwnerVillager *o) {
    void *t = o->villagerTalk.getTalkPlayer();
    s32 r = 0;
    if (t != 0) {
        r = o->getAngleTo((NpcActor *)(t));
    }
    o->talkCtrl.requestTurnAndTalk(0, r, 0);
    return TRUE;
}

void HouseOwnerAi::updateState01Step00(HouseOwnerVillager *o) {
    if (o->talkCtrl.isBusy() == 0) {
        o->mood.requestApply();
        TalkRequest_SetTargetDone(o);
        step = 1;
    }
}

void HouseOwnerAi::updateState01Step01(HouseOwnerVillager *o) {}

BOOL HouseOwnerAi::updateState01(HouseOwnerVillager *o) {
    static Unk_ov004_02216ff4_VFn tbl[2] = {&HouseOwnerAi::updateState01Step00, &HouseOwnerAi::updateState01Step01};
    if (step < 2) {
        (this->*tbl[step])(o);
    }
    return FALSE;
}

BOOL HouseOwnerAi::enterState02(HouseOwnerVillager *o) {
    s32 t = o->getAngleToPlayer(o->partnerPlayer);
    o->actionCtrl.requestAction(3, 2, 0, 0, 0, t, 0, 0, data_020c6cc8, 0);
    step = 0;
    return TRUE;
}

void HouseOwnerAi::updateState02Step00(HouseOwnerVillager *o) {
    if (o->actionCtrl.getAction() == 3) {
        if (o->actionCtrl.isActionDone() != 0) {
            o->actionCtrl.requestStand(2, data_020c6cc8);
            step = 1;
        }
    }
}

BOOL HouseOwnerAi::updateState02(HouseOwnerVillager *o) {
    static Unk_ov004_02216ff4_VFn tbl[1] = {&HouseOwnerAi::updateState02Step00};
    if (step < 1) {
        (this->*tbl[step])(o);
    }
    return FALSE;
}

BOOL HouseOwnerAi::enterState03(HouseOwnerVillager *o) {
    return TRUE;
}

BOOL HouseOwnerAi::updateState03(HouseOwnerVillager *o) {
    if (o->isNetOwner() != 0) {
        s32 a = 4;
        s32 b = 4;
        s32 la;
        void *w = o->villagerData;
        s32 g;
        if (o->netGetSlots(&a, &b) != 0 && ((la = a), la == (g = gCommManager->myAid)) && la == b) {
            o->netSetSlotsIfOwner(1, g, g);
            if (w != 0 && Villager_GetResidentStatus(w) != 3) {
                o->talkKind = 12;
            } else {
                o->talkKind = 0;
            }
            o->villagerTalk.begin(o, o->talkKind);
            o->villagerTalk.setTalkPlayer(o->getPlayerActor(4));
            o->ai.changeState(o, 1);
        } else {
            if (NetArea_IsLocalOwner() != 0 && b == 4) {
                o->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                if (o->ai.applyPendingState(o) == 0) {
                    o->ai.changeState(o, 0);
                }
            }
        }
    }
    return FALSE;
}

BOOL HouseOwnerAi::enterState04(HouseOwnerVillager *o) {
    return TRUE;
}

BOOL HouseOwnerAi::updateState04(HouseOwnerVillager *o) {
    if (o->isNetOwner() != 0) {
        s32 a = 4;
        s32 b = 4;
        if (o->netGetSlots(&a, &b) != 0) {
            if (a == 4) {
                if (NetArea_IsLocalOwner() != 0) {
                    o->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                    if (o->ai.applyPendingState(o) == 0) {
                        o->ai.changeState(o, 0);
                    }
                }
            }
        }
    }
    return FALSE;
}

BOOL HouseOwnerVillager::acceptsInteraction(void *) {
    if (talkCtrl.isBusy() != 0 || netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

void HouseOwnerVillager::onInteractionEvent(u32 idx, u8 v) {
    switch (idx) {
    case 3:
        partnerPlayer = v;
        if (v != 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, v);
            ai.changeState(this, 2);
        } else {
            if (isNetOwner() == 0) {
                return;
            }
            s32 g = gCommManager->myAid;
            netSetSlotsIfOwner(1, g, g);
            if (villagerData != 0 && Villager_GetResidentStatus(villagerData) != 3) {
                talkKind = 12;
            } else {
                switch (reinterpret_cast<VillagerTalk *>(this)->getEventKind()) {
                case 1:
                    talkKind = 3;
                    break;
                case 0:
                    talkKind = 5;
                    break;
                case 8:
                case 9:
                    talkKind = 11;
                    break;
                default:
                    talkKind = 0;
                    break;
                }
            }
            ai.changeState(this, 2);
        }
        break;
    case 0:
        partnerPlayer = v;
        if (v != 4 && v != gCommManager->myAid) {
            netSetSlotsIfOwner(1, v, v);
            ai.changeState(this, 4);
        } else {
            if (isNetOwner() != 0) {
                s32 g = gCommManager->myAid;
                netSetSlotsIfOwner(1, g, g);
                villagerTalk.begin(this, talkKind);
                villagerTalk.setTalkPlayer(getPlayerActor(4));
                ai.changeState(this, 1);
                talkKind = 0;
            }
        }
        break;
    case 8:
        if (v == 4) {
            if (NetArea_IsLocalOwner() != 0) {
                netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                if (ai.applyPendingState(this) == 0) {
                    ai.changeState(this, 0);
                }
            } else {
                netSetSlotsIfOwner(1, 4, gCommManager->myAid);
                ai.changeState(this, 3);
            }
        }
        break;
    case 4:
        if (netIsTalkLocked() != 0) {
            if (isNetOwner() != 0) {
                s32 a = 4;
                s32 b = 4;
                if (netGetSlots(&a, &b) != 0) {
                    if (v == 4) {
                        goto chk;
                    }
                    if (v == b) {
                        goto body;
                    }
                chk:
                    if (v != 4) {
                        break;
                    }
                body:
                    netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                    if (ai.applyPendingState(this) == 0) {
                        ai.changeState(this, 0);
                    }
                }
            }
        }
        break;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02216ccc) {
    HOST_OVERLAY_VAR(sHouseOwnerVillagerProfile),
    HOST_OVERLAY_VAR(sHouseOwnerAiStates),
    HOST_OVERLAY_VAR(sHouseOwnerStepDirs),
    HOST_OVERLAY_VARS_END
};
