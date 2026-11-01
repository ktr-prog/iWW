#include "gfx/Model.h"
#include "host_tick.h"
#include "host_labels.h"
#include "host_shared_calls.h"
#include "host_overlay_vars.h"
#include "npc/VillagerState.h"
#include "uptr.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"
#include "save/Pattern.h"
#include "gfx/Camera.h"
#include "actor/ActorProfile.h"
#include "player/HeldToolModel.h"
#include "sys/ProcBase.h"
#include "talk/MsgString11.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/EncodedString10.h"
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "actor/ActorCollider.h"
#include "game/GroundInfo.h"
#include "game/Unk_0201acf8.h"
#include "gfx/AnimFrameCtrl.h"
#include "npc/NpcActionCtrl.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcEmotionFx.h"
#include "npc/NpcFootstepFx.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/NpcTalkCtrl.h"
#include "npc/VillagerDataItemView.h"
#include "npc/VillagerId.h"
#include "npc/VillagerMood.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "npc/VillagerData.h"
#include "npc/VillagerPlan.h"
#include "npc/VillagerRoute.h"
extern "C" VillagerMemory *Villager_FindMemory(void *a, void *b);
#include "save/ContestRecord.h"
#include "talk/ActorTalkRequest.h"
#include "talk/MsgString.h"
#include "talk/VillagerTalk.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_02003008.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_0206fc44.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov003/unk_ov003_02204ce8.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/ov003/unk_ov003_022192b4.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/ov003/unk_ov003_02225800.h"
#include "proto/ov068/unk_ov068_0225f1a0.h"
#include "proto/ov068/unk_ov068_0226647c.h"
class FieldVillager;
class FieldVillagerAiLeaveHouse;
class FieldVillagerAi;
typedef void (FieldVillagerAiLeaveHouse::*Unk_ov068_02263b90_Fn)(FieldVillager *);
typedef void (FieldVillagerAi::*FieldVillagerAiStateFn)(FieldVillager *);
typedef BOOL (FieldVillager::*Unk_ov068_0226fb80_Fn)();
extern "C" Unk_ov068_0226fb80_Fn data_ov068_0226f870;
extern "C" Unk_ov068_0226fb80_Fn data_ov068_0226f910;
extern "C" Unk_ov068_0226fb80_Fn data_ov068_0226fa68;

extern "C" s32 func_01ffcb0c(s32, s32);
class FieldVillager;
class FieldVillagerAi;




typedef BOOL (FieldVillager::*Unk_ov068_0226fb80_Fn)();
typedef void (FieldVillagerAi::*FieldVillagerAiStateFn)(FieldVillager *);

struct FieldVillagerAiState {
    FieldVillagerAiStateFn enter;
    FieldVillagerAiStateFn exec;
};

class FieldVillagerLook {
public:
    void update(FieldVillager *o);
    void trackFish(FieldVillager *o);
    void startLookAtFish(FieldVillager *o, s32 a, s32 b, VecFx32 *v);
    BOOL isSameFish(s32 a, s32 b);
    s32 findFishNear(VecFx32 *v, s32 *out, VecFx32 *p, s32 lim);
    BOOL getFishPosIfNear(VecFx32 *v, s32 i, VecFx32 *p, s32 lim);
    void trackInsect(FieldVillager *o);
    void startLookAtInsect(FieldVillager *o, s32 a, s32 b, VecFx32 *v);
    BOOL isSameInsect(u32 a, s32 b);
    s32 findInsectNear(VecFx32 *v, s32 *out, VecFx32 *p, s32 lim);
    s32 getInsectIfNear(VecFx32 *v, s32 i, VecFx32 *p, s32 lim);
    void setLookMode(FieldVillager *o, u32 idx, s32 a, Character *target, void *v, s32 c, s32 d, u8 e);
    void tickLookTime();
    void setLookModeLocked(FieldVillager *o, u32 idx, s32 a, Character *target, void *v, s32 c, s32 d, u8 e);
    void resetLook(FieldVillager *o);
    void init(FieldVillager *o);
    ~FieldVillagerLook();
    void construct();

    /* 0x00 */ s32 isLocked;
    /* 0x04 */ s32 targetKind;
    /* 0x08 */ u8 lookMode;
    /* 0x09 */ u8 pad_09[3];
    /* 0x0c */ s32 targetSlot;
    /* 0x10 */ s32 targetId;
    /* 0x14 */ u16 lookTime;
    /* 0x16 */ u8 pad_16[2];
    /* 0x18 */ Unk_ov068_0226fb80_Fn drawFn;
};

class FieldVillagerFxTimer {
public:
    void setHoldCount(u32 v);
    u32 getHoldCount();
    void stop(FieldVillager *o);
    void update(FieldVillager *o);
    void clear();
    ~FieldVillagerFxTimer();
    void construct();

    /* 0x00 */ s8 fleaEffectTimer;
    /* 0x01 */ u8 pad_01;
    /* 0x02 */ u16 holdCount;
};

struct FieldVillagerFocusRange {
    s32 negX, posX, negZ, posZ;
};

class FieldVillagerAi {
public:
    ~FieldVillagerAi();
    FieldVillagerAi *initAi();

    /* 0x00 */ FieldVillagerFocusRange focusRange;
    /* 0x10 */ s32 state;
    /* 0x14 */ FieldVillagerAiState *stateEntry;
    /* 0x18 */ s32 resumeState;
    /* 0x1c */ u8 step;
    /* 0x1d */ u8 pad_1d[3];
    /* 0x20 */ s32 stateTimer;
    /* 0x24 */ s32 cooldown;
    /* 0x28 */ FieldVillager *chatTarget;
    /* 0x2c */ s16 pitfallTimer;
    /* 0x2e */ u8 pad_2e[2];
    /* 0x30 */ s32 pitfallAnimSpeed;
    /* 0x34 */ s16 activityTimer;
    /* 0x36 */ s16 heldItemCheckTimer;
    /* 0x38 */ u8 hitCount;
    /* 0x39 */ u8 pad_39;
    /* 0x3a */ u16 hitResetTimer;
    /* 0x3c */ VillagerRoute route;
    /* 0xd8 */ s16 routeTimeout;
    /* 0xda */ s16 routeStepTimer;
    /* 0xdc */ s16 lookStopTimer;
    /* 0xde */ s16 lookStopCooldown;
    /* 0xe0 */ u8 isAdmiringCatch;
    /* 0xe1 */ u8 pad_e1[3];
    /* 0xe4 */ Character *approachTarget;
    /* 0xe8 */ VecFx32 approachStart;
    /* 0xf4 */ s32 seekPlayerCooldown;
    /* 0xf8 */ s32 talkUrgeTimer;
};






class FieldVillager : public VillagerActor {
public:
    inline FieldVillager() {
        look.construct();
        ai.initAi();
        ((HeldToolModel *)(&heldTool))->init();
        fleaFx.construct();
    }
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 idx, u8 v);
    virtual BOOL acceptsInteractionOutOfRange(void *p);
    virtual BOOL onToolHit(u16 *p);
    virtual BOOL updateAct();
    virtual void onJoinTalk();
    virtual void onLeaveTalk();
    virtual BOOL isPickable();
    virtual BOOL consumeFleaRemoved();
    virtual BOOL canAcceptPartnerInvite();
    virtual BOOL acceptPartnerInvite(VillagerActor *partner);
    virtual BOOL endPartnerTalk();

    void refreshActivity();
    void chooseActivity();
    void updateStareTimer();
    BOOL isPlayerFacing();
    VillagerMemory *getPlayerMemory();
    void attachHeldItemModel();
    BOOL drawDefault();

    /* 0x894 */ FieldVillagerLook look;
    /* 0x8b4 */ FieldVillagerAi ai;
    /* 0x9b0 */ HeldToolModel heldTool;
    /* 0x9f0 */ FieldVillagerFxTimer fleaFx;
    /* 0x9f4 */ NpcActor *talkPartner;
    /* 0x9f8 */ s32 talkType;
    /* 0x9fc */ s32 pitfallEffect;
    /* 0xa00 */ u8 isInPitfall;
    /* 0xa01 */ u8 wasHitByNet;
    /* 0xa02 */ u16 pushFrames;
    /* 0xa04 */ u8 lastCatchSimMinute;
    /* 0xa05 */ u8 unk_a05;
    /* 0xa06 */ u8 pad_a06[2];
    /* 0xa08 */ s32 talkReason;
};

class FieldVillagerAiStates : public FieldVillagerAi {
public:
    s32 execAdmireCatch(FieldVillager *o);
    void admireCatchStep1(FieldVillager *o);
    void admireCatchStep0(FieldVillager *o);
    BOOL enterAdmireCatch(FieldVillager *o);
    s32 execPushTalk(FieldVillager *o);
    void pushTalkStep1(FieldVillager *o);
    void pushTalkStep0(FieldVillager *o);
    BOOL enterPushTalk(FieldVillager *o);
    s32 execHitTalk(FieldVillager *o);
    void hitTalkStep2(FieldVillager *o);
    void hitTalkStep1(FieldVillager *o);
    void hitTalkStep0(FieldVillager *o);
    BOOL enterHitTalk(FieldVillager *o);
    s32 execPushed(FieldVillager *o);
    void pushedStep1(FieldVillager *o);
    void pushedStep0(FieldVillager *o);
    BOOL enterPushed(FieldVillager *o);
    s32 execHitByNet(FieldVillager *o);
    void hitByNetStep2(FieldVillager *o);
    void hitByNetStep1(FieldVillager *o);
    void hitByNetStep0(FieldVillager *o);
    BOOL enterHitByNet(FieldVillager *o);
    s32 execPitfallClimbOut(FieldVillager *o);
    BOOL enterPitfallClimbOut(FieldVillager *o);
    s32 execPitfall(FieldVillager *o);
    void pitfallStep4(FieldVillager *o);
    void pitfallStep3(FieldVillager *o);
    void pitfallStep2(FieldVillager *o);
    void pitfallStep1(FieldVillager *o);
    void pitfallStep0(FieldVillager *o);
    BOOL enterPitfall(FieldVillager *o);
    BOOL enterInHouse(FieldVillager *o);
    s32 execGoInHouse(FieldVillager *o);
    void goInHouseStep2(FieldVillager *o);
    void goInHouseStep1(FieldVillager *o);
    void goInHouseStep0(FieldVillager *o);
    BOOL enterGoInHouse(FieldVillager *o);
    BOOL execOffscreen(FieldVillager *o);
    BOOL enterOffscreen(FieldVillager *o);
    BOOL enterWander(FieldVillager *o);
    BOOL execWander(FieldVillager *o);
    BOOL checkWanderEvents(FieldVillager *o);
};

struct FieldVillagerPosCopy : VecFx32 {
    FieldVillagerPosCopy() {}
    ~FieldVillagerPosCopy() {}
};

class FieldVillagerAiPutAway : public FieldVillagerAi {
public:
    s32 execPutAwayItem(FieldVillager *o);
    void putAwayItemStep1(FieldVillager *o);
    void putAwayItemStep0(FieldVillager *o);
    BOOL enterPutAwayItem(FieldVillager *o);
};

class FieldVillagerAiTakeOut : public FieldVillagerAi {
public:
    s32 execTakeOutItem(FieldVillager *o);
    void takeOutItemStep1(FieldVillager *o);
    void takeOutItemStep0(FieldVillager *o);
    BOOL enterTakeOutItem(FieldVillager *o);
};

class FieldVillagerAiBirthdayInvite : public FieldVillagerAi {
public:
    s32 execBirthdayInvite(FieldVillager *o);
    void birthdayInviteStep2(FieldVillager *o);
    void birthdayInviteStep1(FieldVillager *o);
    void birthdayInviteStep0(FieldVillager *o);
    BOOL enterBirthdayInvite(FieldVillager *o);
};

class FieldVillagerAiBirthdayWait : public FieldVillagerAi {
public:
    s32 execBirthdayWait(FieldVillager *o);
    BOOL enterBirthdayWait(FieldVillager *o);
};


struct FieldVillagerApproachFx {
    u16 effectId;
    u8 seIndex;
    u8 c;
};

class FieldVillagerAiPlayerStates : public FieldVillagerAi {
public:
    s32 execFleaRemoved(FieldVillager *o);
    void fleaRemovedStep1(FieldVillager *o);
    void fleaRemovedStep0(FieldVillager *o);
    BOOL enterFleaRemoved(FieldVillager *o);
    s32 execJoinTalk(FieldVillager *o);
    BOOL enterJoinTalk(FieldVillager *o);
    s32 execFaceTalker(FieldVillager *o);
    void faceTalkerStep0(FieldVillager *o);
    BOOL enterFaceTalker(FieldVillager *o);
    s32 execApproach(FieldVillager *o);
    void approachStep4(FieldVillager *o);
    void approachStep3(FieldVillager *o);
    void approachStep2(FieldVillager *o);
    void approachStep1(FieldVillager *o);
    void approachStep0(FieldVillager *o);
    BOOL isTargetInFront(FieldVillager *o, s32 r);
    BOOL isNearApproachStart(FieldVillager *o);
    BOOL enterApproach(FieldVillager *o);
};

class FieldVillagerAiReaction : public FieldVillagerAi {
public:
    void reactionStep1(FieldVillager *o);
    void reactionStep0(FieldVillager *o);
    BOOL enterReaction(FieldVillager *o);
    s32 execReaction(FieldVillager *o);
};

class FieldVillagerAiChat : public FieldVillagerAi {
public:
    s32 execChat(FieldVillager *o);
    void chatStep3(FieldVillager *o);
    void chatStep2(FieldVillager *o);
    void pickChatOutcome(FieldVillager *o);
    void chatStep1(FieldVillager *o);
    BOOL isEnemyPairWithPlayerNear(FieldVillager *o, s32 v);
    BOOL isStrangerPlayerNear(FieldVillager *o, s32 v);
    s32 getPlayerDistance(FieldVillager *o);
    BOOL isPartnerNear(FieldVillager *o);
    void chatStep0(FieldVillager *o);
    BOOL enterChat(FieldVillager *o);
    BOOL tryChatAdoptAblePattern(FieldVillager *o);
    BOOL tryChatRevertCatchphrase(FieldVillager *o);
    BOOL tryChatRevertClothes(FieldVillager *o);
    BOOL tryChatSpreadShirt(FieldVillager *o);
    BOOL tryChatSpreadCatchphrase(FieldVillager *o);
    BOOL tryChatNeutral(FieldVillager *o);
    BOOL tryChatMoodByRelation(FieldVillager *o);
};






struct Unk_ov068_02263aac_Bits {
    u32 lo : 12;
    u32 mid : 16;
    u32 hi : 4;
};

class FieldVillagerAiTalk : public FieldVillagerAi {
public:
    s32 execTalk(FieldVillager *o);
    void talkStep1(FieldVillager *o);
    void talkStep0(FieldVillager *o);
    BOOL enterTalk(FieldVillager *o);
};

class FieldVillagerAiLeaveHouse : public FieldVillagerAi {
public:
    s32 execLeaveHouse(FieldVillager *o);
    void leaveHouseStep1(FieldVillager *o);
    void leaveHouseStep0(FieldVillager *o);
    BOOL enterLeaveHouse(FieldVillager *o);
};

class FieldVillagerAiAbsent : public FieldVillagerAi {
public:
    s32 execAbsent(FieldVillager *o);
    void absentStep1(FieldVillager *o);
    void absentStep0(FieldVillager *o);
    BOOL enterAbsent(FieldVillager *o);
};

class FieldVillagerAiInHouse : public FieldVillagerAi {
public:
    s32 execInHouse(FieldVillager *o);
    void inHouseStep1(FieldVillager *o);
    void inHouseStep0(FieldVillager *o);
};


struct VillagerStateFlags {
    u8 pad : 1;
    u8 f1 : 1;
};






extern "C" {
extern s32 data_020c6d1c;
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
extern BlockMap *gSceneBlockMap;
extern s16 sFieldVillagerPushLimit;
extern u16 sFleaRemovedHoldFrames;
extern s32 sFieldVillagerAiCooldown;
extern s32 sRandomRouteTypes[];
extern s32 sChatDurations[];
extern FieldVillagerApproachFx sApproachAnimFx[];
void Npc_GetStateHeldItem(u16 *out, VillagerActor *obj);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
s32 Random_PickSetBit(u32 mask, s32 cnt, s32 n);
s32 Weather_GetFallingPrecip(void);
u16 *VillagerState_GetHeldItem(VillagerState *e);
void Villager_GetUmbrella(u16 *out, VillagerData *o);
s32 Villager_GetWhereabouts(VillagerData *a);
}

namespace ns_0225f1a0 {
extern "C" {
extern u8 gVec3Zero[];
s32 Vec_DistXZ(void *, void *);
s32 VillagerMemory_IsUsed(void *);
void TalkRepeat_Count(void *t);
void Villager_ClearTalkUrge(void *);
void FieldPos_FromUnitCenter(void *, u32, u32);
s32 VillagerStates_GetBirthdayHost();
s32 Villager_GetIndex(void *);
void TalkRepeat_StartWindow(void *t);
void Villager_AddTalkUrge(void *, s32);
void Villager_RemoveFlea(void *);
s32 Villager_HasFlea(void *);
}
}

namespace ns_0225fc60 {
extern "C" {
extern s16 data_020c6cc0;
extern u16 data_020c6cc8;
extern u8 gVec3Zero[];
void TalkRequest_SetTargetDone(void *);
void TalkRequest_AddPlayerTalk6(void *, s32);
void Villager_HalveTalkUrge(void *);
}
typedef void (FieldVillagerAiStates::*Fn_225fd54)(FieldVillager *);
extern "C" {
extern Fn_225fd54 sAdmireCatchSteps[2];
}
typedef void (FieldVillagerAiStates::*Fn_225ff18)(FieldVillager *);
extern "C" {
extern Fn_225ff18 sPushTalkSteps[2];
}
typedef void (FieldVillagerAiStates::*Fn_2260068)(FieldVillager *);
extern "C" {
extern Fn_2260068 sHitTalkSteps[3];
}
typedef void (FieldVillagerAiStates::*Fn_2260290)(FieldVillager *);
extern "C" {
extern Fn_2260290 sPushedSteps[2];
}
typedef void (FieldVillagerAiStates::*Fn_2260450)(FieldVillager *);
extern "C" {
extern Fn_2260450 sHitByNetSteps[3];
}
}

namespace ns_022605f4 {
extern "C" {
extern u16 data_020c6cc8;
extern s16 data_020c6cc0;
extern u8 gVec3Zero[];
void TalkRequest_AddPlayerTalk6(void *, s32);
void GroundInfo_Destruct(void *);
void FieldPos_SnapToUnitCenter(void *, void *);
}
typedef void (FieldVillagerAiStates::*Fn_226071c)(FieldVillager *);
extern "C" {
extern Fn_226071c sPitfallClimbOutSteps[1];
}
typedef void (FieldVillagerAiStates::*Fn_2260944)(FieldVillager *);
extern "C" {
extern Fn_2260944 sPitfallSteps[5];
}
}

namespace ns_02260f90 {
extern "C" {
extern u16 data_020c6cc8;
extern u8 gVec3Zero[];
void TalkRequest_SetTargetDone(void *);
void TalkRequestFlags_ClearEventWarpBlock(void);
void TalkRequest_AddPlayerTalk6(void *, s32);
void Camera_SetModeDefault(void);
s32 BlockMap_FindItemAllAttr(void *, s32 *, s32 *, s32 *, s32 *, u16 *, u16 *, s32, s32);
void FieldPos_FromBlockUnit(VecFx32 *, s32, s32, s32, s32);
void VillagerStates_SetBirthdayVisitor(s32);
void TalkRequestFlags_SetEventWarpBlock(void);
}
static inline BOOL Unk_ov068_02261118_InRange(volatile u16 *p) {
    BOOL r = FALSE;
    u16 a = *p;
    u16 b = *p;
    if (!(b < 0x1380 || a > 0x139f)) {
        r = TRUE;
    }
    return r;
}
typedef void (FieldVillagerAiPutAway::*Fn_2260f90)(FieldVillager *);
extern "C" {
extern Fn_2260f90 sPutAwayItemSteps[2];
}
typedef void (FieldVillagerAiTakeOut::*Fn_2261290)(FieldVillager *);
extern "C" {
extern Fn_2261290 sTakeOutItemSteps[2];
}
typedef void (FieldVillagerAiBirthdayInvite::*Fn_2261574)(FieldVillager *);
extern "C" {
extern Fn_2261574 sBirthdayInviteSteps[3];
}
}

namespace ns_02261900 {
extern "C" {
extern u16 data_020c6cc8;
extern u8 gVec3Zero[];
s32 Vec_Distance(void *, void *);
void Villager_HalveTalkUrge(void *);
void Villager_AddTalkUrge(void *, s32);
}
typedef void (FieldVillagerAiPlayerStates::*Fn_2261900)(FieldVillager *);
extern "C" {
extern Fn_2261900 sFleaRemovedSteps[2];
}
typedef void (FieldVillagerAiPlayerStates::*Fn_2261ae8)(FieldVillager *);
extern "C" {
extern Fn_2261ae8 sFaceTalkerSteps[1];
}
typedef void (FieldVillagerAiPlayerStates::*Fn_2261c38)(FieldVillager *);
extern "C" {
extern Fn_2261c38 sApproachSteps[5];
}
}

namespace ns_02262294 {
extern "C" {
extern u16 data_020c6cc8;
extern u8 gVec3Zero[];
extern u8 sChatNoPlayerMoods[];
extern u8 sChatTopicWeights[];
extern u8 sChatEmotions[];
void TalkRequest_SetTargetDone(void *);
s32 MI_CpuCopy8(void *, void *, s32);
s32 Talk_PickWeightedIndex(void *, s32);
s32 SaveVillagers_GetRelationLevelOf(void *, void *, void *);
s32 Vec_DistXZ(void *, void *);
}
typedef void (FieldVillagerAiReaction::*Fn_2262294)(FieldVillager *);
extern "C" {
extern Fn_2262294 sReactionSteps[2];
}
typedef void (FieldVillagerAiChat::*Fn_2262414)(FieldVillager *);
extern "C" {
extern Fn_2262414 sChatSteps[4];
}
typedef BOOL (FieldVillagerAiChat::*Fn_2262548)(FieldVillager *);
extern "C" {
extern Fn_2262548 sChatOutcomes[7];
}
}

namespace ns_02262c20 {
extern "C" {
extern u8 sChatBadMoods[];
extern u8 sChatClothesMoods[];
extern u8 sChatCatchphraseMoods[];
extern const s8 sChatRevertClothesDeltas[];
extern const s8 sChatMoodByRelationDeltas[];
extern const s8 sChatSpreadShirtDeltas[];
extern const s8 sChatNeutralDeltas[];
extern const s8 sChatRevertCatchphraseDeltas[];
extern const s8 sChatAblePatternDeltas[];
extern const s8 sChatSpreadCatchphraseDeltas[];
void Villager_ShareTrendWith(void *, void *);
void Villagers_ShareNickname(void *, void *, s32);
s32 Villager_GetDefaultCatchphraseEncoded(void *, s32);
void Villager_SetCatchphraseEncoded(void *, void *);
void Villager_SetCatchphraseFromMsg(void *, void *);
VillagerState *Villager_GetState(void *);
void Villager_GetDefaultUmbrella(u16 *, void *);
void Villager_GetDefaultShirt(u16 *, void *);
VillagerData *SaveVillagers_Get(void *base, s32 idx);
s32 SaveVillagers_IsValidIndex(s32);
s32 SaveVillagers_GetRelationLevelOf(void *, void *, void *);
}
static inline BOOL Unk_ov068_02262c20_InRange(u16 *p) {
    BOOL r = FALSE;
    if (*p >= 0x12a8 && *p <= 0x12af) {
        r = TRUE;
    }
    return r;
}
static inline BOOL Unk_ov068_02262e5c_InRange(u16 *p) {
    BOOL r = FALSE;
    if (*p >= 0x1380 && *p <= 0x139f) {
        r = TRUE;
    }
    return r;
}
}

namespace ns_02263600 {
extern "C" {
#define gSaveAbleSistersPatterns HOST_LABEL(u8 (*)[], gSaveAbleSistersPatterns)
extern u8 gVec3Zero[];
extern u16 data_020c6cc8;
void *SaveVillagers_PickRandomExcept(void *, void *, s32);
s32 SaveVillagers_FindIndex(void *, void *);
s32 SaveVillagers_GetRelationLevel(void *, s32, s32);
void SaveVillagers_AddRelation(void *, void *, void *, s32);
void TalkRequest_SetTargetDone(void *);
VillagerState *Villager_GetState(void *);
s32 Villager_GetIndex(void *);
void VillagerState_SetRole(void *, s32);
void VillagerState_SetPresence(void *, s32);
void FieldPos_FromUnitCenter(void *, u32, u32);
s32 VillagerState_GetRole(void *);
s32 Villager_IsAsleep(void *, s32);
void Villager_RaiseTalkUrge(void *, s32);
}
typedef void (FieldVillagerAiTalk::*Fn_22638c0)(FieldVillager *);
extern "C" {
extern Fn_22638c0 sTalkSteps[2];
}
typedef void (FieldVillagerAiLeaveHouse::*Fn_2263a40)(FieldVillager *);
extern "C" {
extern Fn_2263a40 sLeaveHouseSteps[2];
}
typedef void (FieldVillagerAiAbsent::*Fn_2263cf0)(FieldVillager *);
extern "C" {
extern Fn_2263cf0 sAbsentSteps[2];
}
typedef void (FieldVillagerAiInHouse::*Fn_2263e4c)(FieldVillager *);
extern "C" {
extern Fn_2263e4c sInHouseSteps[2];
}
}

namespace ns_02264000 {
extern "C" {
extern u16 data_020c6cc8;
extern u8 gVec3Zero[];
extern u8 data_ov068_0226f13c[];
extern u8 data_ov068_0226f0f4[];
extern u32 __ptmf_null[];
}
extern "C" {
VillagerState *Villager_GetState(void *);
void VillagerState_SetRole(void *, s32);
void VillagerState_SetPresence(void *, s32);
s32 Villager_IsAsleep(void *, s32);
void Villager_PlaceReceivedItems(void *);
void FieldPos_FromUnitCenter(void *, u32, u32);
void Math_StepS32(void *, s32, s32);
s32 Villager_GetIndex(void *);
void Villager_RaiseTalkUrge(void *, s32);
s32 Random_Next(void *);
}
typedef void (FieldVillagerAiStates::*Fn_226410c)(FieldVillager *);
extern "C" {
extern Fn_226410c sGoInHouseSteps[3];
}
}

namespace ns_022649f4 {
extern "C" {
extern u16 data_020c6cc8;
extern s16 data_020c6cc0;
extern u8 gVec3Zero[];
void FieldPos_ToUnit(s32 *, s32 *, void *);
void FieldPos_SnapToUnitCenter(void *, void *);
s32 Vec_DistXZ(void *, void *);
s32 FieldAction_RequestPitfallAt(s32, void *);
s32 FieldAction_PollResult(s32 idx);
void FieldAction_Release(s32);
void *BlockMap_GetItemPtr(void *, s32, s32, s32, s32, s32);
s32 BlockMap_IsBuriedAtUnit(void *, s32, s32);
VillagerState *Villager_GetState(void *);
s32 TalkRequest_IsTalking();
void *TalkRequest_GetTalkTarget();
void Vec_Sub(void *, void *, void *);
void Vec_ShiftRight(void *, s32);
void Vec_RotateY(void *, s32);
s32 Vec_NotEqual(void *, void *);
s32 func_01ffcb0c(s32, s32);
void FieldPos_FromUnitCenter(void *, u32, u32);
s32 Villager_IsAsleep(void *, s32);
s32 VillagerState_GetActivity(void *);
void Clock_GetDateTime(void *);
}
static inline BOOL Unk_ov068_02264b30_InRange(u16 *p) {
    BOOL r = FALSE;
    if (*p >= 0x1566 && *p <= 0x1566) {
        r = TRUE;
    }
    return r;
}
static inline BOOL Unk_ov068_02264b9c_InRange(u16 *p, s32 i, u32 lo, u32 hi) {
    BOOL r = FALSE;
    volatile u16 *q = p;
    u32 h = q[i];
    u32 l = q[i];
    if (l >= lo && h <= hi) {
        r = TRUE;
    }
    return r;
}
static inline BOOL Unk_ov068_02264b9c_Same(u16 *a, u16 *b) {
    if (Item_IsFurniture(a) != 0) {
        if (Item_GetFurnitureIndex(a) == Item_GetFurnitureIndex(b)) {
            return TRUE;
        }
        return FALSE;
    }
    if (*a == *b) {
        return TRUE;
    }
    return FALSE;
}
static inline BOOL Unk_ov068_022652d0_B(BOOL v) {
    if (v != 0) {
        return TRUE;
    }
    return FALSE;
}
}

namespace ns_02265324 {
extern "C" {
extern u8 gVec3Zero[];
s32 Vec_DistXZ(void *, void *);
s32 VillagerMemory_IsUsed(void *);
void TalkRepeat_Count(void *t);
void Villager_ClearTalkUrge(void *);
void FieldPos_FromUnitCenter(void *, u32, u32);
s32 VillagerStates_GetBirthdayHost();
s32 Villager_GetIndex(void *);
void TalkRepeat_StartWindow(void *t);
void Villager_AddTalkUrge(void *, s32);
void Villager_RemoveFlea(void *);
s32 Villager_HasFlea(void *);
extern Camera *gCamera;
extern VecFx32 gCameraLookAt;
extern u16 data_020c6cc8;
extern u8 sSimCatchClassWeights[];
extern u8 sSimCatchClassWeightsPlanned[];
#define gContestRecord HOST_LABEL(ContestRecord *, gContestRecord)
VillagerState *Villager_GetState(void *);
void Clock_GetDateTime(void *);
s32 Personality_IsAsleep(s32, void *);
s32 VillagerState_GetActivity(void *);
s32 Villager_IsTalkUrgeFull(void *, s32);
s32 Scene_InTownUnk31();
void TalkRepeat_Tick(void *, s32);
void *VillagerState_GetTalkRepeat(void *);
s32 VillagerState_GetMood(void *);
s32 TalkRequest_IsTalking();
void *Villager_GetPlan(void *);
s32 Talk_PickWeightedIndex(void *, s32);
s32 FishPick_PickForDate(void *, s32, s32, s32, s32, s32, s32);
s32 InsectPick_PickForMonth(void *, s32, s32, s32, s32, s32);
BOOL BlockMap_BlockHasAllAttr(BlockMap *g, s32 hx, s32 hy, s32 a);
void VillagerState_SetHeldItem(void *, void *);
}
static inline BOOL Unk_ov068_02265a40_R(volatile u16 *p, u32 lo, u32 hi) {
    u32 a = *p;
    u32 b = *p;
    BOOL r = FALSE;
    if (b >= lo && a <= hi) {
        r = TRUE;
    }
    return r;
}
static inline BOOL Unk_ov068_02265c24_R(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}
}

namespace ns_02265d34 {
extern "C" {
extern u16 data_020c6cc8;
extern CameraSwayPattern kCameraSwayPatterns[];
extern s16 data_02135f44[];
VillagerState *Villager_GetState(void *);
s32 VillagerState_GetActivity(void *);
void *Villager_GetPlan(void *);
void Clock_GetDateTime(void *);
void VillagerState_SetActivity(void *, s32);
void Villager_HalveTalkUrge(void *);
s32 Villager_HasFlea(void *);
s32 VillagerStates_GetBirthdayVisitor();
s32 Villager_GetIndex(void *);
s32 VillagerStates_GetBirthdayHost();
s32 VillagerState_GetRole(void *);
u16 Math_CountDownU16(void *);
s32 func_01ffcb0c(s32, s32);
}
static inline BOOL Unk_ov068_02266320_IsZero(s32 v) {
    return v == 0 ? TRUE : FALSE;
}
}

namespace nsD {
extern "C" {
extern s16 data_020c6cc0;
extern s16 data_020c905c;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sReactionStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
extern const s8 sChatRevertClothesDeltas[8] = {-56, -68, -40, -20, 0, 0, 0, 0};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u8 sChatNoPlayerMoods[4] = {0x02, 0x03, 0x01, 0x00};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace ns_02265324 {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
Unk_ov068_0226fb80_Fn data_ov068_0226f910 = &FieldVillager::drawDefault;
}
}
namespace nsD {
extern "C" {
s16 sFieldVillagerPushLimit = 100;
}
}
namespace nsD {
extern "C" {
ns_02260f90::Fn_2261574 sBirthdayInviteSteps[3];
}
}
namespace nsD {
extern "C" {
ns_0225fc60::Fn_225ff18 sPushTalkSteps[2];
}
}
namespace nsD {
extern "C" {
u8 sSimCatchClassWeightsPlanned[8] = {0x0a, 0x0a, 0x05, 0x05, 0x46, 0x00, 0x00, 0x00};
}
}
namespace nsD {
extern "C" {
u32 sHitTalkStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
extern const s8 sChatRevertCatchphraseDeltas[8] = {-10, -18, -28, -14, -2, 0, 0, 0};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_02262294::Fn_2262414 sChatSteps[4];
}
}
namespace nsD {
extern "C" {
ns_02263600::Fn_22638c0 sTalkSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
FieldVillagerAiState sFieldVillagerAiTable[0x18];
}
}
namespace nsD {
extern "C" {
extern const s8 sChatMoodByRelationDeltas[8] = {2, 8, 16, 10, 6, 0, 0, 0};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sChatStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u8 sChatCatchphraseMoods[4] = {0x01, 0x03, 0x02, 0x00};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_022605f4::Fn_226071c sPitfallClimbOutSteps[1];
}
}
namespace nsD {
extern "C" {
s32 sFieldVillagerAiCooldown = 1200;
}
}
namespace nsD {
extern "C" {
ns_02260f90::Fn_2260f90 sPutAwayItemSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
Unk_ov068_0226fb80_Fn data_ov068_0226fa68 = &FieldVillager::drawDefault;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sTalkStepsGuard;
}
}
namespace nsD {
extern "C" {

extern "C" void StaticInit_unk_ov068_0225f1a0(void) {
    HOST_STATIC_INIT_ARRAY(sFieldVillagerAiTable, {
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterWander), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execWander)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterOffscreen), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execOffscreen)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterGoInHouse), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execGoInHouse)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterInHouse), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiInHouse::execInHouse)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiLeaveHouse::enterLeaveHouse), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiLeaveHouse::execLeaveHouse)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiTalk::enterTalk), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiTalk::execTalk)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiReaction::enterReaction), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiReaction::execReaction)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPlayerStates::enterApproach), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPlayerStates::execApproach)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPlayerStates::enterFaceTalker), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPlayerStates::execFaceTalker)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiChat::enterChat), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiChat::execChat)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPlayerStates::enterJoinTalk), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPlayerStates::execJoinTalk)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPlayerStates::enterFleaRemoved), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPlayerStates::execFleaRemoved)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiAbsent::enterAbsent), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiAbsent::execAbsent)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiBirthdayWait::enterBirthdayWait), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiBirthdayWait::execBirthdayWait)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiBirthdayInvite::enterBirthdayInvite), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiBirthdayInvite::execBirthdayInvite)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiTakeOut::enterTakeOutItem), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiTakeOut::execTakeOutItem)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPutAway::enterPutAwayItem), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiPutAway::execPutAwayItem)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterPitfall), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execPitfall)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterPitfallClimbOut), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execPitfallClimbOut)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterHitByNet), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execHitByNet)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterHitTalk), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execHitTalk)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterPushed), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execPushed)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterPushTalk), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execPushTalk)},
        {reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::enterAdmireCatch), reinterpret_cast<FieldVillagerAiStateFn>(&FieldVillagerAiStates::execAdmireCatch)}});
}
}
}
namespace nsD {
extern "C" {
ns_02262294::Fn_2262294 sReactionSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sApproachStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u8 sChatEmotions[8] = {0x14, 0x15, 0x16, 0x19, 0x1b, 0x04, 0x0b, 0x1d};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sFaceTalkerStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sTakeOutItemStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sAbsentStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sInHouseStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
extern const s8 sChatSpreadCatchphraseDeltas[8] = {2, 14, 28, 18, 10, 0, 0, 0};
}
}
namespace nsD {
extern "C" {
ns_02263600::Fn_2263cf0 sAbsentSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u8 data_ov068_0226f0f4[4] = {0x07, 0x0e, 0x24, 0x2b};
}
}
namespace nsD {
extern "C" {
u8 sChatBadMoods[4] = {0x02, 0x03, 0x00, 0x00};
}
}
namespace nsD {
extern "C" {
ns_02261900::Fn_2261c38 sApproachSteps[5];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
s16 sSeePlayerArc = 0x3000;
}
}
namespace nsD {
extern "C" {
extern const s8 sChatAblePatternDeltas[8] = {1, 2, 6, 4, 2, 0, 0, 0};
}
}
namespace nsD {
extern "C" {
extern const s8 sChatSpreadShirtDeltas[8] = {1, 2, 12, 4, 2, 0, 0, 0};
}
}
namespace nsD {
extern "C" {
ns_02264000::Fn_226410c sGoInHouseSteps[3];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_0225fc60::Fn_2260450 sHitByNetSteps[3];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u8 data_ov068_0226f13c[8] = {0x00, 0x14, 0x46, 0x14, 0x1e, 0x00, 0x00, 0x00};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sPutAwayItemStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
extern const s8 sChatNeutralDeltas[8] = {-6, -10, -16, -8, -2, 0, 0, 0};
}
}
namespace nsD {
extern "C" {
u8 sChatTopicWeights[8] = {0x0f, 0x0a, 0x0f, 0x14, 0x0a, 0x0f, 0x0f, 0x00};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sGoInHouseStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sChatOutcomesGuard;
}
}
namespace nsD {
extern "C" {
ns_02260f90::Fn_2261290 sTakeOutItemSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_0225fc60::Fn_2260290 sPushedSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sAdmireCatchStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sFleaRemovedStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sHitByNetStepsGuard;
}
}
namespace nsD {
extern "C" {
ns_02262294::Fn_2262548 sChatOutcomes[7];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_02263600::Fn_2263a40 sLeaveHouseSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sBirthdayInviteStepsGuard;
}
}
namespace nsD {
extern "C" {
s32 sRandomRouteTypes[3] = {0, 2, 4};
}
}
namespace nsD {
extern "C" {
Unk_ov068_0226fb80_Fn data_ov068_0226f870 = &FieldVillager::drawDefault;
}
}
namespace ns_02265d34 {
extern "C" {
ActorProfile sFieldVillagerProfile = {(void *(*)())FieldVillager_Create, 0x84, 0x88, 2, 0x5000, 0x5000, 0x3e800};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
s32 sChatDurations[5] = {240, 160, 100, 60, 60};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sLeaveHouseStepsGuard;
}
}
namespace nsD {
extern "C" {
ns_0225fc60::Fn_2260068 sHitTalkSteps[3];
}
}
namespace nsD {
extern "C" {
ns_022605f4::Fn_2260944 sPitfallSteps[5];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
FieldVillagerApproachFx sApproachAnimFx[2] = {{0x45, 4, 0}, {0x4f, 0x1d, 0}};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_0225fc60::Fn_225fd54 sAdmireCatchSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sPitfallClimbOutStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_02263600::Fn_2263e4c sInHouseSteps[2];
}
}
namespace nsD {
extern "C" {
u8 sSimCatchClassWeights[8] = {0x0a, 0x05, 0x05, 0x00, 0x50, 0x00, 0x00, 0x00};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_02261900::Fn_2261900 sFleaRemovedSteps[2];
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sPushTalkStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u8 sChatClothesMoods[4] = {0x01, 0x03, 0x02, 0x00};
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
u32 sPitfallStepsGuard;
}
}
namespace nsD {
extern "C" {
u32 sPushedStepsGuard;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
ns_02261900::Fn_2261ae8 sFaceTalkerSteps[1];
}
}
namespace nsD {
extern "C" {
s16 sTalkFacingArc = 0x2aaa;
}
}
namespace nsD {
extern "C" {
u16 sFleaRemovedHoldFrames = 600;
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace nsD {
extern "C" {
}
}
namespace ns_02265d34 {
extern "C" {
extern "C" FieldVillager *FieldVillager_Create() {
    return new FieldVillager();
}
}
}

BOOL FieldVillager::isPickable() {
    using namespace ns_02265d34;
    BOOL r = FALSE;
    BOOL f = FALSE;
    if (villagerData != NULL) {
        if (Villager_GetState(villagerData) != NULL) {
            f = TRUE;
        }
    }
    if (f) {
        if (VillagerState_GetRole(Villager_GetState(villagerData)) == 1) {
            r = TRUE;
        }
    }
    return r;
}

BOOL FieldVillager::preCreate() {
    using namespace ns_02265d34;
    if (((VillagerActor *)(this))->VillagerActor::preCreate() == 0) {
        return FALSE;
    }
    ((NpcActor *)(this))->setTalkRequest((ActorTalkRequest *)(&villagerTalk));
    villagerTalk.resetMsg();
    talkPartner = NULL;
    talkType = 0;
    talkReason = 3;
    u16 buf = 0xfff1;
    if (Unk_ov068_02266320_IsZero(((HeldToolModel *)((&heldTool)))->load(&buf))) {
        return FALSE;
    }
    curHeldTool = (&heldTool);
    pitfallEffect = -1;
    isInPitfall = 0;
    wasHitByNet = 0;
    pushFrames = 0;
    lastCatchSimMinute = 0xff;
    unk_a05 = 0;
    refreshActivity();
    FieldVillager_UpdateUmbrella(this);
    return TRUE;
}

BOOL FieldVillager::onCreate() {
    using namespace ns_02265d34;
    VillagerData *a = static_cast<VillagerData *>(getVillagerData());
    if (((VillagerActor *)(this))->VillagerActor::onCreate() == 0) {
        return FALSE;
    }
    look.drawFn = data_ov068_0226f870;
    ((FieldVillagerLook *)((&look)))->init((FieldVillager *)(this));
    s32 t = VillagerStates_GetBirthdayVisitor();
    FieldVillagerAi_InitTimers((&ai));
    if (t == Villager_GetIndex(a)) {
        FieldVillagerAi_ChangeState((&ai), this, 0xd);
    } else if (VillagerStates_GetBirthdayHost() == Villager_GetIndex(a)) {
        FieldVillagerAi_ChangeState((&ai), this, 0xc);
    } else {
        switch (Villager_GetWhereabouts(a)) {
        case 0: {
            u16 buf;
            FieldVillagerAi_ChangeState((&ai), this, 0);
            Npc_GetStateHeldItem(&buf, this);
            if (buf != 0xfff1) {
                attachHeldItemModel();
            }
            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            FieldVillagerAi_ChangeState((&ai), this, 0xc);
            break;
        default:
            FieldVillagerAi_ChangeState((&ai), this, 3);
            break;
        }
    }
    ((FieldVillagerFxTimer *)((&fleaFx)))->clear();
    return TRUE;
}

BOOL FieldVillager::drawDefault() {
    using namespace ns_02265d34;
    data_021cb69c = MODEL_AT_MTX(&model);
    if (((NpcActor *)(this))->NpcActor::onDraw() == 0) {
        return FALSE;
    }
    ((HeldToolModel *)((&heldTool)))->draw(this);
    return TRUE;
}

BOOL FieldVillager::onDraw() {
    using namespace ns_02265d34;
    BOOL r = TRUE;
    if (look.drawFn != 0) {
        r = (this->*look.drawFn)();
    } else {
        VecFx32 *pv = (VecFx32 *)&position;
        jointPos[0].x = position.x;
        jointPos[0].y = pv->y;
        jointPos[0].z = pv->z;
        jointPos[1].x = position.x;
        jointPos[1].y = pv->y;
        jointPos[1].z = pv->z;
        jointPos[2].x = position.x;
        jointPos[2].y = pv->y;
        jointPos[2].z = pv->z;
    }
    return r;
}

BOOL FieldVillager::onDelete() {
    using namespace ns_02265d34;
    if (((VillagerActor *)(this))->VillagerActor::onDelete() == 0) {
        return FALSE;
    }
    ((HeldToolModel *)((&heldTool)))->release();
    curHeldTool = NULL;
    if (pitfallEffect != -1) {
        Effect_End(pitfallEffect);
        pitfallEffect = -1;
    }
    return TRUE;
}

BOOL FieldVillager::onToolHit(u16 *p) {
    using namespace ns_02265d34;
    BOOL result = FALSE;
    BOOL r = FALSE;
    u32 v = *p;
    if (v >= 0x1376 && v <= 0x1376) {
        r = TRUE;
    }
    if (r || (v >= 0x1377 && v <= 0x1377)) {
        if (getVillagerData() != NULL) {
            Villager_HalveTalkUrge(getVillagerData());
        }
        if (Villager_HasFlea(villagerData) != 0) {
            ((FieldVillagerFxTimer *)((&fleaFx)))->stop((FieldVillager *)(this));
            ((FieldVillagerFxTimer *)((&fleaFx)))->setHoldCount(sFleaRemovedHoldFrames);
            result = TRUE;
        } else if (getPlayerMemory() != 0) {
            wasHitByNet = 1;
        }
    }
    return result;
}

BOOL FieldVillager::consumeFleaRemoved() {
    using namespace ns_02265d34;
    if (((FieldVillagerFxTimer *)((&fleaFx)))->getHoldCount() != 0) {
        ((FieldVillagerFxTimer *)((&fleaFx)))->setHoldCount(0);
        return TRUE;
    }
    return FALSE;
}

void FieldVillager::attachHeldItemModel() {
    using namespace ns_02265d34;
    u16 a;
    u16 b;
    Npc_GetStateHeldItem(&a, this);
    if (a != 0xfff1) {
        Npc_GetStateHeldItem(&b, this);
        ((HeldToolModel *)((&heldTool)))->attach((NpcActor *)this, (u16 *)(&b), 0, 0);
        ((HeldToolModel *)((&heldTool)))->playIdleAnim(data_020c6cc8, 0);
        ((HeldToolModel *)((&heldTool)))->setAnimSpeed(0x1000);
        heldTool.visible = 1;
    }
}

VillagerMemory *FieldVillager::getPlayerMemory() {
    using namespace ns_02265d34;
    PlayerId *x;
    void *p;
    if (PlayerData_GetCurrent() != NULL) {
        x = PlayerData_GetCurrent()->getPlayerId();
    } else {
        x = NULL;
    }
    p = getVillagerData();
    if (x != NULL && static_cast<PlayerId *>(x)->isValid() && p != NULL && static_cast<VillagerId *>(static_cast<VillagerData *>(p)->getVillagerId())->isValid() != 0) {
        return Villager_FindMemory(p, x);
    }
    return 0;
}

BOOL FieldVillager::isPlayerFacing() {
    using namespace ns_02265d34;
    if (collider.isHit != 0 && ((ActorCollider *)(&collider))->isHitByGroup(4) != 0) {
        Character *p = (Character *)PlayerActor_GetCharacter(4);
        if (p != NULL && p->speed != 0) {
            s16 d = Math_AngleXZ(&p->position, &position) - p->moveAngleY;
            if (d < 0) {
                d = -d;
            }
            if (d < 0x31c6) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void FieldVillager::updateStareTimer() {
    using namespace ns_02265d34;
    if (drawEnabled != 0 && updateEnabled != 0 && look.drawFn != 0 && ((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0 && getPlayerMemory() != 0) {
        if (isPlayerFacing()) {
            pushFrames += TICK_STEP_ENDS() ? 1 : 0;
            if ((s32)pushFrames >= 100) {
                pushFrames = 100;
            }
        } else {
            pushFrames = 0;
        }
    } else {
        pushFrames = 0;
    }
}

void FieldVillager::chooseActivity() {
    using namespace ns_02265d34;
    void *a = getVillagerData();
    if (a != NULL) {
        if (static_cast<VillagerId *>(static_cast<VillagerData *>(a)->getVillagerId())->isValid() != 0) {
            s32 r5 = 8;
            void *p = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
            s32 r4 = static_cast<VillagerPlan *>(p)->getState();
            s32 r7 = Random_GlobalBelow(100);
            ClockDateTimeWords buf;
            buf.words[0] = 0;
            buf.words[1] = 0;
            Clock_GetDateTime(&buf.dt);
            if (r7 < 30) {
                if (static_cast<VillagerPlan *>(p)->isTrendOlderThan(&buf.dt, 3) != 0) {
                    r4 = (u8)Random_GlobalBelow(r5);
                }
            }
            if (Trend_IsValid(r4) != 0 || r4 == 8) {
                r5 = r4;
            }
            switch (((VillagerTalk *)(this))->getEventKind()) {
            case 3:
                r5 = 1;
                break;
            case 4:
                r5 = 0;
                break;
            case 5:
                r5 = 5;
                break;
            }
            VillagerState_SetActivity(Villager_GetState(a), r5);
        }
    }
}

void FieldVillager::refreshActivity() {
    using namespace ns_02265d34;
    void *a = getVillagerData();
    if (a != NULL) {
        if (static_cast<VillagerId *>(static_cast<VillagerData *>(a)->getVillagerId())->isValid() != 0) {
            s32 t = VillagerState_GetActivity(Villager_GetState(a));
            void *p = VillagerPlanBlock_GetPlan(Villager_GetPlan(a));
            ClockDateTimeWords buf;
            buf.words[0] = 0;
            buf.words[1] = 0;
            Clock_GetDateTime(&buf.dt);
            if (Trend_IsValid(t) != 0 || t == 8) {
                if (t == static_cast<VillagerPlan *>(p)->getState() || static_cast<VillagerPlan *>(p)->isTrendOlderThan(&buf.dt, 3) != 0) {
                    if (((VillagerTalk *)(this))->getEventKind() != 3 && ((VillagerTalk *)(this))->getEventKind() != 4 && ((VillagerTalk *)(this))->getEventKind() != 5) {
                        return;
                    }
                }
            }
            chooseActivity();
        }
    }
}

namespace ns_02265324 {
extern "C" {
void FieldVillager_UpdateUmbrella(FieldVillager *o) {
    VillagerData *p = static_cast<VillagerData *>(o->getVillagerData());
    if (p != 0 && static_cast<VillagerId *>(p->getVillagerId())->isValid() != 0) {
        u16 v;
        u16 w;
        u16 z;
        VillagerState *r4 = Villager_GetState(p);
        s32 r5 = VillagerState_GetActivity(r4);
        s32 r7 = Weather_GetFallingPrecip();
        if (r7 != 1) {
            if (Unk_ov068_02265c24_R(VillagerState_GetHeldItem(r4), 0x1380, 0x139f)) {
                w = 0xfff1;
                VillagerState_SetHeldItem(r4, &w);
            }
        }
        if (!Unk_ov068_02265c24_R(VillagerState_GetHeldItem(r4), 0x1380, 0x139f)) {
            Trend_GetToolItem(&v, r5);
            u16 *q = VillagerState_GetHeldItem(r4);
            BOOL eq;
            if (Item_IsFurniture(q) != 0) {
                s32 x = Item_GetFurnitureIndex(q);
                if (x == Item_GetFurnitureIndex(&v)) {
                    eq = TRUE;
                } else {
                    eq = FALSE;
                }
            } else {
                if (*q == v) {
                    eq = TRUE;
                } else {
                    eq = FALSE;
                }
            }
            if (eq == 0) {
                VillagerState_SetHeldItem(r4, &v);
            }
        }
        if (Unk_ov068_02265c24_R(VillagerState_GetHeldItem(r4), 0x1378, 0x1378) && r7 == 1) {
            Villager_GetUmbrella(&z, p);
            VillagerState_SetHeldItem(r4, &z);
        }
    }
}
}
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillager_CanSimulateCatch(FieldVillager *o) {
    s32 t = ((VillagerTalk *)(o))->getEventKind();
    if ((u8)(t + 0xfd) <= 1) {
        Character *p = (Character *)PlayerActor_GetCharacter(4);
        BlockMap *g = gSceneBlockMap;
        if (p != 0 && g != 0) {
            VecFx32CtorDtor v;
            v.x = p->position.x;
            v.y = p->position.y;
            v.z = p->position.z;
            if (BlockMap_BlockHasAllAttr(g, v.x >> 17, v.z >> 17, 0x200) == 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillager_SimulateInsectCatch(FieldVillager *o, u8 *b) {
    u8 *t = sSimCatchClassWeights;
    ContestRecord *g = &gContestRecord;
    if (static_cast<VillagerPlan *>(VillagerPlanBlock_GetPlan(Villager_GetPlan(o->getVillagerData())))->getState() == 0) {
        t = sSimCatchClassWeightsPlanned;
    }
    s32 idx = Talk_PickWeightedIndex(t, 5);
    if ((u32)idx < 4) {
        u16 v = 0xfff1;
        if (InsectPick_PickForMonth(&v, idx, idx + 1, b[2], b[2], b[4]) != 0) {
            BOOL k = FALSE;
            u32 v0 = v;
            if (*(volatile u16 *)&v >= 0x12b0 && v0 <= 0x12e7) {
                k = TRUE;
            }
            if (k) {
                s32 x = Contest_GetCatchSize(&v);
                s32 y = g->getSize();
                if ((x >> 12) > (y >> 12)) {
                    void *w = static_cast<VillagerData *>(o->getVillagerData())->getVillagerId();
                    g->setHolderVillager((VillagerId *)(w));
                    g->setSize(x);
                    ContestRecord_SetItem(g, &v);
                }
            }
        }
    }
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillager_SimulateFishCatch(FieldVillager *o, u8 *b) {
    u8 *t = sSimCatchClassWeights;
    ContestRecord *g = &gContestRecord;
    if (static_cast<VillagerPlan *>(VillagerPlanBlock_GetPlan(Villager_GetPlan(o->getVillagerData())))->getState() == 1) {
        t = sSimCatchClassWeightsPlanned;
    }
    s32 idx = Talk_PickWeightedIndex(t, 5);
    if ((u32)idx < 4) {
        u16 v = 0xfff1;
        if (FishPick_PickForDate(&v, idx, idx + 1, b[4], b[3], b[2], b[2]) != 0) {
            BOOL k = FALSE;
            u32 v0 = v;
            if (*(volatile u16 *)&v >= 0x12e8 && v0 <= 0x131f) {
                k = TRUE;
            }
            if (k) {
                s32 x = Contest_GetCatchSize(&v);
                s32 ty = g->getSize() * 10;
                s32 tx = x * 10;
                if ((tx >> 12) > (ty >> 12)) {
                    void *w = static_cast<VillagerData *>(o->getVillagerData())->getVillagerId();
                    g->setHolderVillager((VillagerId *)(w));
                    g->setSize(x);
                    ContestRecord_SetItem(g, &v);
                }
            }
        }
    }
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillager_UpdateCatchSim(FieldVillager *o) {
    u32 buf[2];
    buf[0] = 0;
    buf[1] = 0;
    Clock_GetDateTime(buf);
    if (o->lastCatchSimMinute != ((u8 *)buf)[1]) {
        if (TalkRequest_IsTalking() == 0) {
            if (FieldVillager_CanSimulateCatch(o) != 0) {
                s32 r = ((VillagerTalk *)(o))->getEventKind();
                if (r != 3) {
                    if (r == 4) {
                        FieldVillager_SimulateInsectCatch(o, (u8 *)buf);
                    }
                } else {
                    FieldVillager_SimulateFishCatch(o, (u8 *)buf);
                }
            }
        }
        o->lastCatchSimMinute = ((u8 *)buf)[1];
    }
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillager_StopEmotion(FieldVillager *o) {
    if (o->actionCtrl.getAction() == 8) {
        if (o->actionCtrl.getEmotionId() != 0) {
            const NpcEmotionEntry *r = Emotion_GetEntry(0);
            if (r != 0) {
                o->emotionFx.emotionId = 0;
                o->emotionFx.startEntry((const NpcEmotionPhase *)(r), 0);
            }
        }
    }
}
}
}

namespace ns_02265324 {
extern "C" {
u32 FieldVillager_GetMood(FieldVillager *o) {
    void *p;
    void *q;
    s32 r;
    if (o->getVillagerData() != 0 && static_cast<VillagerId *>(static_cast<VillagerData *>(o->getVillagerData())->getVillagerId())->isValid() != 0) {
        q = Villager_GetState(o->getVillagerData());
    } else {
        q = 0;
    }
    if (q != 0) {
        r = VillagerState_GetMood(q);
    } else {
        r = 0;
    }
    return (u8)r;
}
}
}

namespace ns_02265324 {
extern "C" {
void *FieldVillager_GetTalkRepeat(FieldVillager *o) {
    void *p = o->getVillagerData();
    void *q;
    void *r;
    if (p != 0 && static_cast<VillagerId *>(static_cast<VillagerData *>(p)->getVillagerId())->isValid() != 0 && (q = Villager_GetState(p)) != 0) {
        r = VillagerState_GetTalkRepeat(q);
    } else {
        r = 0;
    }
    return r;
}
}
}

BOOL FieldVillager::updateAct() {
    using namespace ns_02265324;
    updateStareTimer();
    void *p = FieldVillager_GetTalkRepeat(this);
    if (p != 0) {
        TalkRepeat_Tick(p, this->talkCtrl.isBusy());
    }
    FieldVillagerAi_Update(&ai, this);
    fleaFx.update(this);
    mood.update(this);
    look.update(this);
    this->wasHitByNet = 0;
    return TRUE;
}

FieldVillagerAi *FieldVillagerAi::initAi() {
    using namespace ns_02265324;
    route.resetTarget();
    approachTarget = 0;
    resumeState = 0x18;
    focusRange.negX = 0x10000;
    focusRange.posX = 0x10000;
    focusRange.negZ = 0x1a000;
    focusRange.posZ = 0xa000;
    cooldown = 0;
    route.reset();
    stateTimer = 0;
    routeTimeout = -1;
    routeStepTimer = 0;
    seekPlayerCooldown = 0;
    talkUrgeTimer = 0;
    chatTarget = 0;
    activityTimer = 0;
    heldItemCheckTimer = -1;
    pitfallTimer = 0;
    hitCount = 0;
    hitResetTimer = 0;
    lookStopTimer = 0;
    lookStopCooldown = 0;
    isAdmiringCatch = 0;
    return this;
}

FieldVillagerAi::~FieldVillagerAi() {
    using namespace ns_02265324;
    VillagerRoute_Destruct();
}

namespace ns_02265324 {
extern "C" {
void FieldVillagerAi_Update(FieldVillagerAi *self, FieldVillager *o) {
    if (self->isAdmiringCatch != 0) {
        if (FieldVillagerAi_IsPlayerShowingCatch(self) == 0) {
            self->isAdmiringCatch = 0;
        }
    }
    if (self->stateEntry != 0) {
        (self->*(self->stateEntry->exec))(o);
    }
    if (self->stateTimer > 0) {
        self->stateTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (self->routeTimeout > 0) {
        self->routeTimeout--;
    }
    if (self->routeStepTimer > 0) {
        self->routeStepTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (self->lookStopTimer > 0) {
        self->lookStopTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (self->lookStopCooldown > 0) {
        self->lookStopCooldown -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (self->cooldown > 0) {
        self->cooldown -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (self->hitResetTimer != 0) {
        self->hitResetTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (o->talkCtrl.isBusy() == 0) {
        if (self->seekPlayerCooldown > 0) {
            self->seekPlayerCooldown -= TICK_STEP_ENDS() ? 1 : 0;
        } else if (self->talkUrgeTimer > 0) {
            self->talkUrgeTimer -= TICK_STEP_ENDS() ? 1 : 0;
        }
        if (self->activityTimer > 0) {
            self->activityTimer -= TICK_STEP_ENDS() ? 1 : 0;
        }
        if (self->heldItemCheckTimer > 0) {
            self->heldItemCheckTimer -= TICK_STEP_ENDS() ? 1 : 0;
        }
    }
    if (self->pitfallTimer > 0) {
        self->pitfallTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillagerAi_ChangeState(FieldVillagerAi *self, FieldVillager *o, s32 idx) {
    if (idx >= 0 && idx < 0x18) {
        self->state = idx;
        self->stateEntry = &sFieldVillagerAiTable[self->state];
        self->step = 0;
        if (self->stateEntry != 0) {
            if (self->stateEntry->enter != 0) {
                (self->*(self->stateEntry->enter))(o);
            }
        }
    }
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillagerAi_SetResumeState(FieldVillagerAi *self, s32 v) {
    self->resumeState = v;
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillagerAi_SaveResumeState(FieldVillagerAi *self) {
    FieldVillagerAi_SetResumeState(self, self->state);
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillagerAi_ClearResumeState(FieldVillagerAi *self) {
    self->resumeState = 0x18;
}
}
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillagerAi_Resume(FieldVillagerAi *self, FieldVillager *o) {
    s32 r = 0;
    if (self->resumeState < 0x18) {
        FieldVillagerAi_ChangeState(self, o, self->resumeState);
        FieldVillagerAi_ClearResumeState(self);
        r = 1;
    }
    return r;
}
}
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillagerAi_CanSeePlayer(FieldVillagerAi *self, FieldVillager *o) {
    void *p = PlayerActor_GetCharacter(4);
    BOOL k;
    s32 kr;
    if (o->getVillagerData() != 0) {
        kr = Villager_IsTalkUrgeFull(o->getVillagerData(), 0);
    } else {
        kr = 0;
    }
    if (kr != 0) {
        k = TRUE;
    } else {
        k = FALSE;
    }
    s32 res = 0;
    if (Scene_InTownUnk31() == 0) {
        if (self->seekPlayerCooldown <= 0 && k != 0 && p != 0) {
            if (((NpcActor *)(o))->getDistanceTo((NpcActor *)(p)) <= 0x7000) {
                s32 d = ((NpcActor *)(o))->getRelativeAngleTo((NpcActor *)(p));
                s32 lim = sSeePlayerArc;
                if (d >= -lim && d <= lim) {
                    res = 1;
                }
            }
        }
    }
    return res;
}
}
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillagerAi_IsFreeIdle(FieldVillagerAi *self) {
    if (FieldVillagerAi_IsState(self, 0) != 0 && self->cooldown == 0) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillagerAi_StartCooldown(FieldVillagerAi *self) {
    self->cooldown = sFieldVillagerAiCooldown;
}
}
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillagerAi_IsState(FieldVillagerAi *self, s32 v) {
    if (self->state == v) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillagerAi_InitTimers(FieldVillagerAi *self) {
    self->activityTimer = Random_GlobalBelow(0x1770);
    self->heldItemCheckTimer = -1;
}
}
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillagerAi_EnterWander(FieldVillagerAi *self, FieldVillager *o) {
    FieldVillager_StopEmotion(o);
    o->look.drawFn = data_ov068_0226fa68;
    o->actionCtrl.requestStand(1, data_020c6cc8);
    o->footstepFx.enableFootsteps();
    o->look.resetLook((FieldVillager *)(o));
    if (self->route.isActive() != 0) {
        self->route.setStepMode(0);
    } else {
        FieldVillagerAi_StartRoute(self, 0, o);
        self->routeTimeout = -1;
        self->routeStepTimer = 0;
    }
    ((VillagerActor *)(o))->clearFlag834();
    o->updateEnabled = 1;
    o->drawEnabled = 1;
    self->talkUrgeTimer = -1;
    o->heldTool.visible = 1;
    o->mood.enableEffects();
    return TRUE;
}
}
}

BOOL FieldVillagerAiStates::enterWander(FieldVillager *o) {
    return ns_02265324::FieldVillagerAi_EnterWander(this, o);
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillager_IsInRect(FieldVillagerFocusRange *r, VecFx32 *a, VecFx32 *b) {
    s32 ret = 0;
    BOOL k2 = FALSE;
    BOOL k1 = FALSE;
    s32 ax = a->x;
    s32 bx = b->x;
    if (bx > ax - r->negX && bx < ax + r->posX) {
        k1 = TRUE;
    }
    if (k1) {
        if (b->z > a->z - r->negZ) {
            k2 = TRUE;
        }
    }
    if (k2) {
        if (b->z < a->z + r->posZ) {
            ret = 1;
        }
    }
    return ret;
}
}
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillager_IsNearCameraFocus(FieldVillagerFocusRange *r, FieldVillager *o) {
    VecFx32 *pb = (VecFx32 *)&o->position;
    s32 res = 0;
    if (gCamera != 0) {
        VecFx32 v;
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        res = FieldVillager_IsInRect(r, &v, pb);
    }
    return res;
}
}
}

namespace ns_02265324 {
extern "C" {
s32 FieldVillagerAi_PickRandomRouteType(FieldVillagerAi *self) {
    s32 k;
    if (self->route.isActive() != 0) {
        k = 2;
    } else {
        k = 3;
    }
    s32 i = Random_GlobalBelow(k);
    s32 r5 = sRandomRouteTypes[i];
    if (r5 == self->route.getStage()) {
        s32 n = i + 1;
        if (n >= 3) {
            n = 0;
        }
        r5 = sRandomRouteTypes[n];
    }
    return r5;
}
}
}

namespace ns_02265324 {
extern "C" {
void FieldVillagerAi_StartRoute(FieldVillagerAi *self, s32 a, FieldVillager *o) {
    void *x = o->getVillagerData();
    s32 r4 = 7;
    if (x != 0) {
        VillagerStateFlags *f = (VillagerStateFlags *)&Villager_GetState(x)->flags;
        if (f->f1 != 0) {
            r4 = 3;
        } else {
            s32 r6;
            void *t = PlayerData_GetCurrent();
            if (t != 0) {
                r6 = ((PlayerData *)(t))->testFlag(1);
            } else {
                r6 = 0;
            }
            u32 buf[2];
            buf[0] = 0;
            buf[1] = 0;
            Clock_GetDateTime(buf);
            if (!(r6 != 0 ? TRUE : FALSE)) {
                if (Personality_IsAsleep(VillagerId_GetPersonality(static_cast<VillagerId *>(static_cast<VillagerData *>(x)->getVillagerId())), buf) != 0) {
                    r4 = 3;
                    goto done;
                }
            }
            r6 = 7;
            if (static_cast<VillagerId *>(static_cast<VillagerData *>(x)->getVillagerId())->isValid() != 0) {
                if (Villager_GetState(x) != 0) {
                    r6 = VillagerState_GetActivity(Villager_GetState(x));
                }
            }
            if (r6 == 6) {
                r4 = 6;
            }
        }
    }
done:
    if (r4 == 7) {
        r4 = FieldVillagerAi_PickRandomRouteType(self);
    }
    self->route.start(&o->position, r4, a, o);
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_ShouldGoHome(void *self, FieldVillager *o) {
    void *a = PlayerData_GetCurrent();
    s32 t;
    if (a != 0) {
        t = ((PlayerData *)(a))->testFlag(1);
    } else {
        t = 0;
    }
    BOOL f = Unk_ov068_022652d0_B(t);
    void *p = o->getVillagerData();
    BOOL r = TRUE;
    VillagerStateFlags *fl = (VillagerStateFlags *)&Villager_GetState(p)->flags;
    if (fl->f1 == 0 && (f != 0 || Villager_IsAsleep(p, 0) == 0)) {
        r = FALSE;
    }
    return r;
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_IsAtHomeDoor(FieldVillagerAiStates *self, FieldVillager *o) {
    BOOL r;
    if (self->route.isActive() != 0 && self->route.getStage() == 3) {
        u8 *p = (u8 *)((VillagerDataItemView *)(o->getVillagerData()))->getHousePos();
        VecFx32 t;
        FieldPos_FromUnitCenter(&t, p[0], p[1] + 1);
        if (Vec_DistXZ(&t, &o->position) < 0x800) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    } else {
        r = FALSE;
    }
    return r;
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_DirCrossesPlayerTalk(void *self, void *a, VecFx32 *b) {
    if (TalkRequest_IsTalking() != 0) {
        if (Vec_NotEqual(b, gVec3Zero) != 0) {
            Character *p = (Character *)PlayerActor_GetCharacter(4);
            Character *q = (Character *)TalkRequest_GetTalkTarget();
            if (p != 0 && q != 0) {
                VecFx32 t1;
                VecFx32 t2;
                Vec_Sub(&t1, &p->position, a);
                Vec_Sub(&t2, &q->position, a);
                s32 x = func_01ffcb0c(b->x, t1.z);
                x -= func_01ffcb0c(b->z, t1.x);
                s32 y = func_01ffcb0c(b->x, t2.z);
                y -= func_01ffcb0c(b->z, t2.x);
                if (func_01ffcb0c(x, y) <= 0) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}
}
}

namespace ns_022649f4 {
extern "C" {
s32 FieldVillagerAi_HeadingCrossesPlayerTalk(void *self, FieldVillager *o) {
    if (o->speed != 0) {
        VecFx32 t;
        t.x = 0;
        t.y = 0;
        t.z = 0x1000;
        Vec_RotateY(&t, o->moveAngleY);
        return FieldVillagerAi_DirCrossesPlayerTalk(self, &o->position, &t);
    }
    return 0;
}
}
}

namespace ns_022649f4 {
extern "C" {
s32 FieldVillagerAi_PathCrossesPlayerTalk(void *self, void *a, void *b) {
    VecFx32 t;
    Vec_Sub(&t, a, b);
    return FieldVillagerAi_DirCrossesPlayerTalk(self, b, &t);
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_IsNearPlayerTalkSpot(void *self, void *v, s32 lim) {
    if (TalkRequest_IsTalking() != 0) {
        Character *a = (Character *)PlayerActor_GetCharacter(4);
        Character *b = (Character *)TalkRequest_GetTalkTarget();
        if (a != 0 && b != 0) {
            VecFx32 t1;
            VecFx32 t2;
            Vec_Sub(&t1, &a->position, &b->position);
            Vec_ShiftRight(&t1, 1);
            Vec_Add(&t2, &a->position, &t1);
            s32 d = Vec_DistXZ(v, &t2);
            if (d < 0) {
                d = -d;
            }
            if (d <= lim) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_GetRouteTarget(FieldVillagerAiStates *self, VecFx32 *out, FieldVillager *o) {
    if (o->getVillagerData() != 0) {
        VillagerStateFlags *fl = (VillagerStateFlags *)&Villager_GetState(o->getVillagerData())->flags;
        if (fl->f1 != 0) {
            if (self->route.getStage() != 3) {
                self->routeTimeout = 0;
            }
        }
    }
    if (self->route.isActive() == 0 || self->routeTimeout == 0) {
        FieldVillagerAi_StartRoute(self, 0, o);
        self->routeTimeout = -1;
        self->routeStepTimer = 0;
    }
    VecFx32 *pv = &o->position;
    out->x = pv->x;
    out->y = pv->y;
    out->z = pv->z;
    if (self->route.runStep(out) != 0) {
        if (self->routeTimeout == -1) {
            self->routeTimeout = 0x1770;
        }
    }
    return TRUE;
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_HandleBlockedMove(void *self, FieldVillager *o) {
    BOOL r;
    u8 *r7 = (u8 *)&o->actionCtrl;
    u8 *r6 = (u8 *)&o->moveCtrl;
    u8 buf[12];
    r = FALSE;
    if (((NpcMoveCtrl *)(r6))->hasArrived((Character *)(o), 1) == 0) {
        switch (((NpcActor *)(o))->findAvoidPos((VecFx32 *)(buf))) {
        case 1:
            ((NpcActionCtrl *)(r7))->requestStand(1, data_020c6cc8);
            r = TRUE;
            break;
        case 2:
            ((NpcMoveCtrl *)(r6))->setDestination((VecFx32 *)(buf));
            break;
        }
    } else {
        if (((NpcMoveCtrl *)(r6))->hasNextLeg() != 0) {
            ((NpcMoveCtrl *)(r6))->resetDestination();
        }
    }
    return r;
}
}
}

namespace ns_022649f4 {
extern "C" {
void *FieldVillagerAi_FindChatPartner(void *self, FieldVillager *o) {
    FieldVillager *s = o;
    VecFx32 *pos = &o->position;
    s16 lim = data_020c6cc0;
    FieldVillager *e;
    s32 i;
    for (i = 0; i < 8; i++) {
        e = (FieldVillager *)NpcRegistry_GetVillager(i);
        if (e == 0) {
            continue;
        }
        if (e->villagerData == 0) {
            continue;
        }
        u16 *a = (u16 *)static_cast<VillagerData *>(s->villagerData)->getVillagerId();
        u16 *b = (u16 *)static_cast<VillagerData *>(e->villagerData)->getVillagerId();
        if (b[0] == a[0]) {
            if (memcmp(b + 1, a + 1, 8) == 0) {
                if (((u8 *)b)[0xb] == ((u8 *)a)[0xb]) {
                    continue;
                }
            }
        }
        if (Vec_DistXZ(pos, &e->position) >= 0x3000) {
            continue;
        }
        s32 d = Math_AngleXZ(pos, &e->position);
        if (NpcLookAt_IsWithin((s16)(d - s->rotY), lim) != 0) {
            return e;
        }
    }
    return 0;
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_TryStartChat(FieldVillagerAiStates *self, FieldVillager *o) {
    if (Random_GlobalBelow(5) == 0) {
        if (o->canAcceptPartnerInvite() != 0) {
            FieldVillager *t = (FieldVillager *)FieldVillagerAi_FindChatPartner(self, o);
            if (t != 0) {
                if (t->acceptPartnerInvite(o) != 0) {
                    ((VillagerTalk *)(o))->setPartner(t);
                    ((VillagerTalk *)(o))->setInvitedByPartner(0);
                    FieldVillagerAi_SaveResumeState(self);
                    FieldVillagerAi_ChangeState(&o->ai, o, 9);
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_CheckHeldItemChange(FieldVillagerAiStates *self, FieldVillager *o) {
    struct {
        u16 h[13];
        s32 z[2];
    } l;
    s32 id;
#define W (*(volatile u16 *)&l.h[0])
    VillagerData *p;
    s32 m;

    if (((NpcActionCtrl *)(&o->actionCtrl))->getAction() != 0) {
        goto fail;
    }
    if (((NpcActionCtrl *)(&o->actionCtrl))->isActionDone() == 0) {
        goto fail;
    }
    p = static_cast<VillagerData *>(o->getVillagerData());
    l.z[0] = 0;
    l.z[1] = 0;
    id = 7;
    m = Weather_GetFallingPrecip();
    if (p != 0) {
        if (static_cast<VillagerId *>(static_cast<VillagerData *>(p)->getVillagerId())->isValid() != 0) {
            if (Villager_GetState(p) != 0) {
                id = VillagerState_GetActivity(Villager_GetState(p));
            }
        }
    }
    Clock_GetDateTime(l.z);
    s16 t;
    t = self->activityTimer;
    if (t == 0 || self->heldItemCheckTimer == 0) {
        if (t == 0) {
            ((FieldVillager *)(o))->chooseActivity();
            if (p != 0) {
                if (static_cast<VillagerId *>(static_cast<VillagerData *>(p)->getVillagerId())->isValid() != 0) {
                    if (Villager_GetState(p) != 0) {
                        id = VillagerState_GetActivity(Villager_GetState(p));
                    }
                }
            }
            self->activityTimer = 0x2ee0;
        }
        Npc_GetStateHeldItem(&l.h[1], o);
        if (l.h[1] == 0xfff1) {
            W = 0xfff1;
            if (Trend_IsValid(id) != 0) {
                Trend_GetToolItem(&l.h[2], id);
                W =l.h[2];
            }
            {
                u16 a0 = W;
                u16 b0 = W;
                if (b0 == 0xfff1 || (a0 >= 0x1378 && a0 <= 0x1378)) {
                    if (m == 1) {
                        Villager_GetUmbrella(&l.h[3], p);
                        W =l.h[3];
                    }
                }
            }
            self->heldItemCheckTimer = -1;
            if (W == 0xfff1) {
                goto fail;
            }
            ((VillagerTalk *)(o))->setSpeakerStateUnk((void *)(void *)(&l.h[0]));
            FieldVillagerAi_ChangeState(self, o, 0xf);
            FieldVillagerAi_SetResumeState(self, 0);
            return TRUE;
        }
        Npc_GetStateHeldItem(&l.h[4], o);
        if (Unk_ov068_02264b9c_InRange(l.h, 4, 0x1380, 0x139f)) {
            if (m == 1) {
                goto fail;
            }
            self->heldItemCheckTimer = 0x12c;
            FieldVillagerAi_ChangeState(self, o, 0x10);
            FieldVillagerAi_SetResumeState(self, 0);
            return TRUE;
        }
        Trend_GetToolItem(&l.h[5], id);
        Npc_GetStateHeldItem(&l.h[6], o);
        if (Unk_ov068_02264b9c_Same(&l.h[5], &l.h[6]) == 0) {
            FieldVillagerAi_ChangeState(self, o, 0x10);
            FieldVillagerAi_SetResumeState(self, 0);
            self->heldItemCheckTimer = 0x12c;
            return TRUE;
        }
        self->heldItemCheckTimer = -1;
    } else {
        Npc_GetStateHeldItem(&l.h[7], o);
        if (l.h[7] == 0xfff1) {
            if (m != 1) {
                goto fail;
            }
            Villager_GetUmbrella(&l.h[8], p);
            ((VillagerTalk *)(o))->setSpeakerStateUnk((void *)(void *)(&l.h[8]));
            FieldVillagerAi_ChangeState(self, o, 0xf);
            FieldVillagerAi_SetResumeState(self, 0);
            self->heldItemCheckTimer = -1;
            return TRUE;
        }
        Npc_GetStateHeldItem(&l.h[9], o);
        if (Unk_ov068_02264b9c_InRange(l.h, 9, 0x1380, 0x139f)) {
            if (m == 1) {
                goto fail;
            }
            self->heldItemCheckTimer = 0x12c;
            FieldVillagerAi_ChangeState(self, o, 0x10);
            FieldVillagerAi_SetResumeState(self, 0);
            return TRUE;
        }
        Npc_GetStateHeldItem(&l.h[10], o);
        BOOL f = FALSE;
        volatile u16 *q = l.h;
        u32 hh = q[10];
        u32 ll = q[10];
        if (ll >= 0x1378 && hh <= 0x1378) {
            f = TRUE;
        }
        if (f) {
            if (m == 1) {
                FieldVillagerAi_ChangeState(self, o, 0x10);
                FieldVillagerAi_SetResumeState(self, 0);
                self->heldItemCheckTimer = 0x12c;
                return TRUE;
            }
        }
        Npc_GetStateHeldItem(&l.h[11], o);
        Trend_GetToolItem(&l.h[12], id);
        if (Unk_ov068_02264b9c_Same(&l.h[11], &l.h[12])) {
            goto fail;
        }
        FieldVillagerAi_ChangeState(self, o, 0x10);
        FieldVillagerAi_SetResumeState(self, 0);
        self->heldItemCheckTimer = 0x12c;
        return TRUE;
    }
fail:
    return FALSE;
#undef W
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_IsBuriedPitfallAt(void *self, Vec2 *v) {
    void *g = gSceneBlockMap;
    if (g != 0) {
        s32 x = v->x;
        s32 y = v->y;
        s32 hx = x >> 4;
        s32 hy = y >> 4;
        u16 *c = (u16 *)BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (c != 0) {
            BOOL r = FALSE;
            if (Unk_ov068_02264b30_InRange(c)) {
                if (BlockMap_IsBuriedAtUnit(g, v->x, v->y) != 0) {
                    r = TRUE;
                }
            }
            return r;
        }
    }
    return FALSE;
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_TryFallInPitfall(void *self, FieldVillager *o) {
    BOOL r;
    VecFx32 *p = (VecFx32 *)&o->position;
    Vec2 u;
    Vec2 q;
    VecFx32 t;
    r = FALSE;
    u.x = r;
    u.y = r;
    FieldPos_ToUnit(&u.x, &u.y, p);
    if (FieldVillagerAi_IsBuriedPitfallAt(self, &u) != 0) {
        FieldPos_SnapToUnitCenter(&t, p);
        if (Vec_DistXZ(&t, p) <= 0xb00) {
            q.x = u.x;
            q.y = u.y;
            s32 idx = FieldAction_RequestPitfallAt((s8)((NpcActor *)(o))->getNpcIndex(), &q);
            if (idx >= 0) {
                if (FieldAction_PollResult(idx) == 1) {
                    r = TRUE;
                }
                FieldAction_Release(idx);
            }
        }
    }
    return r;
}
}
}

namespace ns_022649f4 {
extern "C" {
s32 FieldVillagerAi_WasHitByNet(void *self, FieldVillager *o) {
    if (o->wasHitByNet != 0) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace ns_022649f4 {
extern "C" {
s32 FieldVillagerAi_IsPlayerShowingCatch(void *self) {
    u32 v = PlayerActor_GetLocalShownItem();
    if ((v >= 0x12e8 && v <= 0x131f) || (v >= 0x12b0 && v <= 0x12e7)) {
        return TRUE;
    }
    return FALSE;
}
}
}

namespace ns_022649f4 {
extern "C" {
BOOL FieldVillagerAi_ShouldAdmireCatch(FieldVillagerAiStates *self, FieldVillager *o) {
    u32 r = FieldVillager_GetMood(o);
    if (self->isAdmiringCatch == 0) {
        switch (r) {
        case 0:
        case 1:
            if (FieldVillagerAi_IsPlayerShowingCatch(self) != 0) {
                if (o->lookAt.lookType == 1) {
                    if (((NpcActor *)(o))->getDistanceToPlayer(4) <= 0x6000) {
                        if (((NpcLookAt *)(&o->lookAt))->canSeeTarget((Character *)(o)) != 0) {
                            if (((NpcLookAt *)(&o->lookAt))->isOnTarget() != 0) {
                                return TRUE;
                            }
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}
}
}

BOOL FieldVillagerAiStates::checkWanderEvents(FieldVillager *o) {
    using namespace ns_02264000;
    BOOL r = FALSE;
    if (FieldVillagerAi_IsAtHomeDoor(this, o) != 0) {
        u16 v;
        Npc_GetStateHeldItem(&v, o);
        if (v != 0xfff1) {
            FieldVillagerAi_ChangeState(this, o, 0x10);
            FieldVillagerAi_SetResumeState(this, 2);
        } else {
            FieldVillagerAi_ChangeState(this, o, 2);
        }
        r = TRUE;
    } else if (FieldVillagerAi_TryFallInPitfall(this, o) != 0) {
        FieldVillagerAi_ChangeState(this, o, 0x11);
        r = TRUE;
    } else if (o->pushFrames >= sFieldVillagerPushLimit) {
        FieldVillagerAi_ChangeState(this, o, 0x15);
        r = TRUE;
    } else if (FieldVillagerAi_WasHitByNet(this, o) != 0) {
        FieldVillagerAi_ChangeState(this, o, 0x13);
        r = TRUE;
    } else if (FieldVillagerAi_CanSeePlayer(this, o) != 0) {
        FieldVillagerAi_ChangeState(this, o, 7);
        r = TRUE;
    } else if (FieldVillagerAi_TryStartChat(this, o) != 0) {
        r = TRUE;
    } else if (o->fleaFx.getHoldCount() != 0) {
        FieldVillagerAi_ChangeState(this, o, 0xb);
        r = TRUE;
    } else if (FieldVillagerAi_CheckHeldItemChange(this, o) != 0) {
        r = TRUE;
    } else if (FieldVillagerAi_ShouldAdmireCatch(this, o) != 0) {
        FieldVillagerAi_ChangeState(this, o, 0x17);
        r = TRUE;
    } else if (o->speed != 0) {
        if (FieldVillagerAi_HandleBlockedMove(this, o) != 0) {
            r = TRUE;
        }
    }
    return r;
}

BOOL FieldVillagerAiStates::execWander(FieldVillager *o) {
    using namespace ns_02264000;
    NpcActionCtrl *r6 = &o->actionCtrl;
    VecFx32 va, vb;
    if (FieldVillager_IsNearCameraFocus(&focusRange, o) != 0) {
    if (checkWanderEvents(o) != 0) {
        goto end;
    }
    if (r6->isActionDone() != 0) {
        if (lookStopTimer > 0) {
            u32 t;
            u32 u;
            if (o->look.isLocked != 0) {
                goto reset;
            }
            t = o->look.targetKind;
            if (t != 0 && t != 1) {
                goto reset;
            }
            u = o->look.lookTime;
            if ((s32)u < 0xf) {
                goto reset;
            }
            if (u == 0) {
                goto skip;
            }
            if (o->lookAt.canSeeTarget((Character *)(o)) != 0) {
                goto skip;
            }
        reset:
            lookStopTimer = 0;
            lookStopCooldown = 0x4b0;
            o->look.resetLook((FieldVillager *)(o));
        skip:;
        }
        if (r6->getAction() == 0 && lookStopTimer != 0) {
            goto end;
        }
        lookStopTimer = 0;
        if (o->unk_3aa.getLevel() == 2) {
            r6->requestStand(1, data_020c6cc8);
            goto end;
        }
        if ((Random_Next(&gRandom.seed) & 7) == 0) {
            VecFx32 *r7 = &o->position;
            va.x = *(s32 *)gVec3Zero;
            va.y = *(s32 *)(gVec3Zero + 4);
            va.z = *(s32 *)(gVec3Zero + 8);
            if (FieldVillagerAi_GetRouteTarget(this, &va, o) != 0) {
                if (FieldVillagerAi_IsNearPlayerTalkSpot(this, r7, 0xc000) != 0) {
                    if (FieldVillagerAi_PathCrossesPlayerTalk(this, &va, r7) != 0) {
                        goto fail;
                    }
                }
                s32 d = Math_AngleXZ(r7, &va);
                if (NpcActor_IsFrontAngle((s16)(d - o->rotY)) != 0) {
                    s32 m = 1;
                    if (Random_GlobalBelow(4) == 0 && FieldVillager_GetMood(o) == 0) {
                        m = 2;
                    }
                    r6->requestAction(m, 1, va.x, va.z, 0, 0, 0, 0, data_020c6cc8, 0);
                    stateTimer = 0x100;
                } else {
                    r6->requestAction(4, 1, va.x, va.z, 0, d, 0, 0, data_020c6cc8, 0);
                    stateTimer = 0x128;
                }
                goto end;
            }
        fail:
            r6->requestStand(1, data_020c6cc8);
            goto end;
        }
        r6->requestStand(1, data_020c6cc8);
        goto end;
    }
    if (o->speed != 0) {
        if (o->actionCtrl.getAction() == 1 || o->actionCtrl.getAction() == 2 ||
            o->actionCtrl.getAction() == 4) {
            if (stateTimer == 0) {
                r6->requestStand(1, data_020c6cc8);
                goto end;
            }
            if (lookStopCooldown == 0 && o->look.isLocked == 0 && (u32)o->look.targetKind <= 1 &&
                (s32)o->look.lookTime > 0xf) {
                r6->requestStand(1, data_020c6cc8);
                lookStopTimer = Random_GlobalBelow(200) + 0xa0;
                lookStopCooldown = 0x4b0;
                goto end;
            }
            if (FieldVillagerAi_IsNearPlayerTalkSpot(this, &o->position.x, 0x8000) != 0 && FieldVillagerAi_HeadingCrossesPlayerTalk(this, o) != 0) {
                r6->requestStand(1, data_020c6cc8);
                goto end;
            }
            s32 *pv = (s32 *)o->moveCtrl.getDestination();
            vb.x = pv[0];
            vb.y = pv[1];
            vb.z = pv[2];
            s32 d = Math_AngleXZ(&o->position, &vb);
            if (NpcActor_IsFrontAngle((s16)(d - o->rotY)) == 0) {
                r6->requestStand(1, data_020c6cc8);
            }
        }
    }
    } else {
        FieldVillagerAi_ChangeState(this, o, 1);
    }
end:
    return FALSE;
}

BOOL FieldVillagerAiStates::enterOffscreen(FieldVillager *o) {
    using namespace ns_02264000;
    FieldVillager_StopEmotion(o);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    o->actionCtrl.requestStand(1, data_020c6cc8);
    stateTimer = 0;
    o->look.drawFn = *(Unk_ov068_0226fb80_Fn *)__ptmf_null;
    o->footstepFx.disableFootsteps();
    routeStepTimer = 0;
    talkUrgeTimer = 0x384;
    if (route.isActive() != 0) {
        route.setStepMode(1);
    } else {
        FieldVillagerAi_StartRoute(this, 1, o);
        routeTimeout = -1;
        routeStepTimer = 0;
    }
    o->heldTool.visible = 0;
    o->mood.disableEffects();
    return TRUE;
}

BOOL FieldVillagerAiStates::execOffscreen(FieldVillager *o) {
    using namespace ns_02264000;
    if (FieldVillager_IsNearCameraFocus(&focusRange, o) != 0) {
        FieldVillagerAi_ChangeState(this, o, 0);
    } else {
        ((VillagerActor *)(o))->updateCatchPlans((u8 *)(data_ov068_0226f13c), data_ov068_0226f0f4, 1);
        FieldVillager_UpdateCatchSim(o);
        if (talkUrgeTimer == 0) {
            if (o->getVillagerData() != NULL) {
                Villager_RaiseTalkUrge((void *)o->getVillagerData(), 0);
            }
            talkUrgeTimer = 0x384;
        }
        if (route.isActive() == 0 || routeTimeout == 0) {
            FieldVillagerAi_StartRoute(this, 1, o);
            routeTimeout = -1;
            routeStepTimer = 0;
        }
        if (route.isActive() != 0) {
            if (FieldVillagerAi_IsAtHomeDoor(this, o) != 0) {
                FieldVillagerAi_ChangeState(this, o, 3);
            } else {
                if (route.getStage() != 3 && FieldVillagerAi_ShouldGoHome(this, o) != 0) {
                    route.start(&o->position, 3, 1, o);
                    routeStepTimer = 0;
                }
                if (routeStepTimer == 0) {
                    if (route.runStep(&o->position) != 0 && routeTimeout == -1) {
                        routeTimeout = 0x1770;
                    }
                    routeStepTimer = 0x28;
                }
            }
        }
    }
    return TRUE;
}

BOOL FieldVillagerAiStates::enterGoInHouse(FieldVillager *o) {
    using namespace ns_02264000;
    FieldVillager_StopEmotion(o);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    o->actionCtrl.requestAction(3, 2, 0, 0, 0, 0xffff8000, 0, 0, data_020c6cc8, 0);
    o->collider.groups |= 2;
    ((VillagerActor *)(o))->setFlag834();
    o->mood.disableEffects();
    return TRUE;
}

void FieldVillagerAiStates::goInHouseStep0(FieldVillager *o) {
    using namespace ns_02264000;
    if (o->actionCtrl.getAction() == 3) {
        if (o->actionCtrl.isActionDone() != 0) {
            if (VillagerHouse_TryOpenDoorForEntry(Villager_GetIndex(o->getVillagerData())) != 0) {
                ((VillagerDataItemView *)((void *)o->getVillagerData()))->getHousePos();
                o->actionCtrl.requestPlayAnim(2, 0x3b, 1, data_020c6cc8, 0);
                o->shadowEnabled = 0;
                step = 2;
            }
        }
    }
}

void FieldVillagerAiStates::goInHouseStep1(FieldVillager *o) {
    using namespace ns_02264000;
    if (o->actionCtrl.getAction() == 1) {
        if (o->actionCtrl.isActionDone() != 0) {
            if (VillagerHouse_TryOpenDoorForEntry(Villager_GetIndex(o->getVillagerData())) != 0) {
                ((VillagerDataItemView *)((void *)o->getVillagerData()))->getHousePos();
                o->actionCtrl.requestPlayAnim(2, 0x3b, 1, data_020c6cc8, 0);
                o->shadowEnabled = 0;
                step = 2;
            }
        }
    }
}

void FieldVillagerAiStates::goInHouseStep2(FieldVillager *o) {
    using namespace ns_02264000;
    VecFx32 v;
    if (o->animCtrl.getAnimId(0) == 0x3b) {
        if (o->actionCtrl.isActionDone() != 0) {
            FieldVillagerAi_ChangeState(this, o, 3);
            return;
        }
    }
    u8 *p = (u8 *)((VillagerDataItemView *)((void *)o->getVillagerData()))->getHousePos();
    FieldPos_FromUnitCenter(&v, p[0], p[1] + 1);
    Math_StepS32(&o->position.x, v.x, 0x400);
    Math_StepS32(&o->position.z, v.z, 0x400);
    if (o->animCtrl.getAnimId(0) == 0x3b) {
        s32 k = (s32)(((u32)o->model.curFrame << 4) >> 16);
        if (k > 22) goto hi;
        if (k >= 22) goto hit;
        if (k > 12) goto end;
        if (k < 8) goto end;
        switch (k) {
        case 8:
        case 12:
            goto hit;
        }
        goto end;
    hi:
        if (k > 27) goto hi2;
        switch (k) {
        case 27:
            goto hit;
        }
        goto end;
    hi2:
        if (k != 34) goto end;
    hit:
        o->footstepFx.playFootstepSe((NpcActor *)(o));
    }
end:;
}

s32 FieldVillagerAiStates::execGoInHouse(FieldVillager *o) {
    using namespace ns_02264000;
    u32 gv_ = sGoInHouseStepsGuard;
    if ((gv_ & 1) == 0) {
        sGoInHouseSteps[0] = &FieldVillagerAiStates::goInHouseStep0;
        sGoInHouseSteps[1] = &FieldVillagerAiStates::goInHouseStep1;
        sGoInHouseSteps[2] = &FieldVillagerAiStates::goInHouseStep2;
        sGoInHouseStepsGuard = gv_ | 1;
    }
    if (step < 3) {
        (this->*sGoInHouseSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiStates::enterInHouse(FieldVillager *o) {
    using namespace ns_02264000;
    void *p = PlayerData_GetCurrent();
    s32 r7;
    if (p != 0) {
        r7 = ((PlayerData *)(p))->testFlag(1);
    } else {
        r7 = 0;
    }
    void *a = (void *)o->getVillagerData();
    u8 *r4 = (u8 *)Villager_GetState(a);
    FieldVillager_StopEmotion(o);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    o->actionCtrl.requestStand(1, data_020c6cc8);
    VillagerState_SetRole(r4, 0);
    r4[0x1d] = r4[0x1d] & ~2;
    BOOL f;
    if (r7 != 0) {
        f = TRUE;
    } else {
        f = FALSE;
    }
    if (f == 0 && Villager_IsAsleep(a, 0) != 0) {
        VillagerState_SetPresence(r4, 2);
    } else {
        VillagerState_SetPresence(r4, 0);
    }
    Villager_PlaceReceivedItems(a);
    ((VillagerActor *)(o))->setFlag834();
    stateTimer = Random_GlobalBelow(0x28) + 0x258;
    o->drawEnabled = 0;
    talkUrgeTimer = 0x384;
    o->mood.disableEffects();
    o->heldTool.visible = 0;
    return TRUE;
}

void FieldVillagerAiInHouse::inHouseStep0(FieldVillager *o) {
    using namespace ns_02264000;
    step = 1;
}

void FieldVillagerAiInHouse::inHouseStep1(FieldVillager *o) {
    using namespace ns_02263600;
    VillagerData *ow = static_cast<VillagerData *>(o->getVillagerData());
    BOOL r = FALSE;
    o->updateEnabled = r;
    if (Villager_GetWhereabouts(ow) == 2) {
        if (Villager_IsAsleep(ow, r) == 0) {
            if (Villager_GetState(ow) != 0) {
                VillagerState_SetPresence(Villager_GetState(ow), r);
                stateTimer = Random_GlobalBelow(0x28) + 0x258;
            }
            r = TRUE;
        }
    } else if (stateTimer == 0) {
        r = TRUE;
    }
    if (r != 0) {
        if (FieldVillager_IsNearCameraFocus(&focusRange, o) != 0) {
            if (((NpcActor *)(o))->isNear((NpcActor *)(PlayerActor_GetCharacter(4)), 0x6000) == 0) {
                route.reset();
                FieldVillagerAi_ChangeState(this, o, 4);
            }
        } else {
            void *x = Villager_GetState(ow);
            u8 *y = (u8 *)((VillagerDataItemView *)(ow))->getHousePos();
            VillagerState_SetRole(x, 1);
            VillagerState_SetPresence(x, 0);
            FieldPos_FromUnitCenter(&o->position.x, y[0], y[1] + 1);
            VecFx32 *s = &o->position;
            VecFx32 *d = &o->prevPosition;
            *d = *s;
            route.reset();
            FieldVillagerAi_ChangeState(this, o, 0);
            u16 buf;
            Npc_GetStateHeldItem(&buf, o);
            if (buf != 0xfff1) {
                ((FieldVillager *)(o))->attachHeldItemModel();
            }
        }
    } else if (talkUrgeTimer == 0) {
        if (o->getVillagerData() != 0) {
            Villager_RaiseTalkUrge(o->getVillagerData(), 0);
        }
        talkUrgeTimer = 0x384;
    }
}

s32 FieldVillagerAiInHouse::execInHouse(FieldVillager *o) {
    using namespace ns_02263600;
    u32 gv_ = sInHouseStepsGuard;
    if ((gv_ & 1) == 0) {
        sInHouseSteps[0] = &FieldVillagerAiInHouse::inHouseStep0;
        sInHouseSteps[1] = &FieldVillagerAiInHouse::inHouseStep1;
        sInHouseStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sInHouseSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiAbsent::enterAbsent(FieldVillager *o) {
    using namespace ns_02263600;
    void *ow = o->getVillagerData();
    u8 *r4 = (u8 *)Villager_GetState(ow);
    u8 *t = (u8 *)((VillagerDataItemView *)(ow))->getHousePos();
    o->actionCtrl.requestStand(1, data_020c6cc8);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    if (VillagerState_GetRole(r4) == 1) {
        VillagerState_SetRole(r4, 0);
    }
    r4[0x1d] &= ~2;
    ((VillagerActor *)(o))->setFlag834();
    o->drawEnabled = 0;
    o->netSyncOff = 1;
    FieldPos_FromUnitCenter(&o->position.x, t[0], t[1]);
    VecFx32 *s = &o->position;
    VecFx32 *d = &o->prevPosition;
    *d = *s;
    o->heldTool.visible = 0;
    o->mood.disableEffects();
    return TRUE;
}

void FieldVillagerAiAbsent::absentStep0(FieldVillager *o) {
    using namespace ns_02263600;
    step = 1;
}

void FieldVillagerAiAbsent::absentStep1(FieldVillager *o) {
    using namespace ns_02263600;
    o->updateEnabled = 0;
    step = 2;
}

s32 FieldVillagerAiAbsent::execAbsent(FieldVillager *o) {
    using namespace ns_02263600;
    u32 gv_ = sAbsentStepsGuard;
    if ((gv_ & 1) == 0) {
        sAbsentSteps[0] = &FieldVillagerAiAbsent::absentStep0;
        sAbsentSteps[1] = &FieldVillagerAiAbsent::absentStep1;
        sAbsentStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sAbsentSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiLeaveHouse::enterLeaveHouse(FieldVillager *o) {
    using namespace ns_02263600;
    u8 *t = (u8 *)((VillagerDataItemView *)(o->getVillagerData()))->getHousePos();
    FieldVillager_StopEmotion(o);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    FieldPos_FromUnitCenter(&o->position.x, t[0], t[1] + 1);
    o->rotY = 0;
    o->moveAngleY = 0;
    o->moveCtrl.setTargetAngle(0);
    o->position.z += 0x1000;
    VecFx32 *s = &o->position;
    VecFx32 *d = &o->prevPosition;
    *d = *s;
    ((VillagerActor *)(o))->setFlag834();
    o->collider.groups |= 2;
    talkUrgeTimer = -1;
    o->heldTool.visible = 0;
    o->mood.disableEffects();
    return TRUE;
}

void FieldVillagerAiLeaveHouse::leaveHouseStep0(FieldVillager *o) {
    using namespace ns_02263600;
    void *ow = o->getVillagerData();
    void *r6 = Villager_GetState(ow);
    if (VillagerHouse_TryOpenDoorForExit(Villager_GetIndex(ow)) != 0) {
        o->actionCtrl.requestPlayAnim(2, 0x3d, 1, 1, 0);
        o->look.drawFn = data_ov068_0226f910;
        VillagerState_SetRole(r6, 1);
        VillagerState_SetPresence(r6, 0);
        o->updateEnabled = 1;
        o->drawEnabled = 1;
        ((NpcActor *)(o))->setCollisionRadius(0);
        step = 1;
    }
}

void FieldVillagerAiLeaveHouse::leaveHouseStep1(FieldVillager *o) {
    using namespace ns_02263600;
    if (o->animCtrl.getAnimId(0) == 0x3d) {
        if (o->actionCtrl.isActionDone() != 0) {
            u16 buf;
            o->shadowEnabled = 1;
            ((NpcActor *)(o))->setCollisionRadius(0xd00);
            o->collider.groups &= ~2;
            Npc_GetStateHeldItem(&buf, o);
            if (buf != 0xfff1) {
                FieldVillagerAi_ChangeState(this, o, 0xf);
                FieldVillagerAi_SetResumeState(this, 0);
                activityTimer += 0x12c;
            } else {
                FieldVillagerAi_ChangeState(this, o, 0);
            }
        } else {
            s32 t = (((u32)o->model.curFrame >> 12) & 0xffff);
            if (t <= 0x1c) {
                if (t >= 0x1c) goto hit;
                if (t <= 0x11) {
                    if (t < 0xd) goto done;
                    if (t == 0xd) goto hit;
                    switch (t) { case 0x11: goto hit; default: goto done; }
                } else {
                    switch (t) { case 0x17: goto hit; default: goto done; }
                }
            } else {
                if (t <= 0x25) {
                    switch (t) { case 0x25: goto hit; default: goto done; }
                }
                if (t != 0x28) goto done;
            }
        hit:
            o->footstepFx.playFootstepSe((NpcActor *)(o));
        done:;
        }
    }
}

s32 FieldVillagerAiLeaveHouse::execLeaveHouse(FieldVillager *o) {
    using namespace ns_02263600;
    u32 gv_ = sLeaveHouseStepsGuard;
    if ((gv_ & 1) == 0) {
        sLeaveHouseSteps[0] = &FieldVillagerAiLeaveHouse::leaveHouseStep0;
        sLeaveHouseSteps[1] = &FieldVillagerAiLeaveHouse::leaveHouseStep1;
        sLeaveHouseStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sLeaveHouseSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiTalk::enterTalk(FieldVillager *o) {
    using namespace ns_02263600;
    FieldVillager_StopEmotion(o);
    ((NpcActor *)(o))->resetLastTaughtEmotion();
    if (((VillagerTalk *)(o))->hasPartner() != 0) {
        o->talkCtrl.requestTalk(1, 0);
    } else if (o->isInPitfall != 0) {
        o->talkCtrl.requestTalk(0, 0);
        o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    } else {
        void *p = o->villagerTalk.getTalkPlayer();
        s32 v = 0;
        if (p != 0) {
            v = ((NpcActor *)(o))->getAngleTo((NpcActor *)(p));
        }
        o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
        o->talkCtrl.requestTurnAndTalk(0, v, 0);
    }
    return TRUE;
}

void FieldVillagerAiTalk::talkStep0(FieldVillager *o) {
    using namespace ns_02263600;
    if (o->talkCtrl.isBusy() == 0) {
        o->mood.requestApply();
        TalkRequest_SetTargetDone(o);
        ((VillagerTalk *)(o))->setPartner(0);
        ((VillagerTalk *)(o))->setInvitedByPartner(0);
        step = 1;
    }
}

void FieldVillagerAiTalk::talkStep1(FieldVillager *o) {
    using namespace ns_02263600;}

s32 FieldVillagerAiTalk::execTalk(FieldVillager *o) {
    using namespace ns_02263600;
    u32 gv_ = sTalkStepsGuard;
    if ((gv_ & 1) == 0) {
        sTalkSteps[0] = &FieldVillagerAiTalk::talkStep0;
        sTalkSteps[1] = &FieldVillagerAiTalk::talkStep1;
        sTalkStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sTalkSteps[step])(o);
    }
    return 0;
}

namespace ns_02263600 {
extern "C" {
s32 FieldVillagerAi_GetRelationLevel(void *a, void *b) {
    void *g = gSaveVillagers;
    s32 res = 2;
    if (g != 0) {
        s32 a1 = SaveVillagers_FindIndex(g, a);
        s32 a2 = SaveVillagers_FindIndex(g, b);
        s32 r = SaveVillagers_GetRelationLevel(g, a1, a2);
        if (r < 5) {
            res = r;
        }
    }
    return res;
}
}
}

namespace ns_02263600 {
extern "C" {
s32 FieldVillagerAi_GetPartnerRelationLevel(void *a, void *o) {
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    void *x = ((FieldVillager *)o)->getVillagerData();
    void *y = p->getVillagerData();
    void *a1 = (void *)static_cast<VillagerData *>(x)->getVillagerId();
    void *a2 = (void *)static_cast<VillagerData *>(y)->getVillagerId();
    return FieldVillagerAi_GetRelationLevel(a1, a2);
}
}
}

namespace ns_02263600 {
extern "C" {
void FieldVillagerAi_AddRelationByLevel(void *a, void *r1, void *r2, const s8 *t) {
    void *g = gSaveVillagers;
    if (g != 0) {
        s32 k = FieldVillagerAi_GetRelationLevel(r1, r2);
        if (k < 5) {
            SaveVillagers_AddRelation(g, r1, r2, t[k]);
        }
    }
}
}
}

namespace ns_02263600 {
extern "C" {
void FieldVillagerAi_AddPartnerRelation(void *a, void *o, const s8 *t) {
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    void *x = ((FieldVillager *)o)->getVillagerData();
    void *y = p->getVillagerData();
    void *a1 = static_cast<VillagerData *>(x)->getVillagerId();
    void *a2 = static_cast<VillagerData *>(y)->getVillagerId();
    FieldVillagerAi_AddRelationByLevel(a, a1, a2, t);
}
}
}

namespace ns_02263600 {
extern "C" {
void FieldVillagerAi_AddRandomPairRelation(void *a, FieldVillager *unused, const s8 *t) {
    void *g = gSaveVillagers;
    if (g != 0) {
        void *q = SaveVillagers_PickRandomExcept(g, 0, 0);
        if (q != 0) {
            void *r4 = (void *)static_cast<VillagerData *>(q)->getVillagerId();
            void *buf;
            func_02133ef8(&buf, sizeof(buf));
            buf = r4;
            void *q2 = SaveVillagers_PickRandomExcept(g, &buf, 1);
            if (q2 != 0) {
                FieldVillagerAi_AddRelationByLevel(a, r4, (void *)static_cast<VillagerData *>(q2)->getVillagerId(), t);
            }
        }
    }
}
}
}

namespace ns_02263600 {
extern "C" {
void FieldVillagerAi_AddMood(void *a, void *o, s32 x, s32 y, u8 flag) {
    ((VillagerMood *)(&((FieldVillager *)o)->mood))->addMood(x, y);
    if (flag != 0) {
        ((VillagerMood *)(&((FieldVillager *)o)->mood))->requestApply();
    }
}
}
}

namespace ns_02263600 {
extern "C" {
void FieldVillagerAi_AddRandomMood(void *a, void *b, u8 *tbl, s32 n, u8 p5, u8 p6) {
    u8 v = tbl[Random_GlobalBelow(n)];
    if (v == 0) {
        p5 = 0;
    }
    FieldVillagerAi_AddMood(a, b, v, p5, p6);
}
}
}

namespace ns_02263600 {
extern "C" {
s32 FieldVillagerAi_OrderByFriendship(void *unused, void **a, void **b, void *c, void *d) {
    void *g;
    if (PlayerData_GetCurrent() != 0) {
        g = PlayerData_GetCurrent()->getPlayerId();
    } else {
        g = 0;
    }
    if (g != 0 && static_cast<PlayerId *>(g)->isValid() != 0) {
        s32 va = -128;
        s32 vb = -128;
        VillagerMemory *p1 = Villager_FindMemory(c, g);
        VillagerMemory *p2 = Villager_FindMemory(d, g);
        if (p1 != 0) {
            va = static_cast<VillagerMemory *>(p1)->getFriendship();
        }
        if (p2 != 0) {
            vb = static_cast<VillagerMemory *>(p2)->getFriendship();
        }
        if (va > vb || (va == vb && Random_GlobalBelow(2) == 0)) {
            *a = c;
            *b = d;
            return 0;
        }
        *a = d;
        *b = c;
        return 1;
    }
    *a = c;
    *b = d;
    return 0;
}
}
}

namespace ns_02263600 {
extern "C" {
Pattern *FieldVillagerAi_PickOtherAblePattern(void *unused, Pattern *x) {
    if (gSaveAbleSistersPatterns != NULL) {
        u32 i; u16 mask; u32 cnt; mask = 0; cnt = 0; i = 0;
        goto test0;
    loop0:
        if (x == 0 || ((AbleSistersPatterns *)(gSaveAbleSistersPatterns))->getPattern(i)->equals(x) == 0) {
            mask |= 1 << i;
            cnt++;
        }
        i++;
    test0:
        if (i < 8) goto loop0;
        u32 r = Random_PickSetBit(mask, cnt, 8);
        if (r < 8) {
            return ((AbleSistersPatterns *)(gSaveAbleSistersPatterns))->getPattern(r);
        }
    }
    return 0;
}
}
}

BOOL FieldVillagerAiChat::tryChatMoodByRelation(FieldVillager *o) {
    using namespace ns_02262c20;
    void *a;
    void *b;
    FieldVillager *other = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    void *vx = o->getVillagerData();
    void *vy = other->getVillagerData();
    a = 0;
    b = 0;
    void *x = o->getVillagerData();
    void *y = other->getVillagerData();
    FieldVillagerAi_OrderByFriendship(this, &a, &b, x, y);
    Villager_ShareTrendWith(b, a);
    Villagers_ShareNickname(b, a, 0);
    FieldVillagerAi_AddRandomPairRelation(this, o, sChatMoodByRelationDeltas);
    switch (SaveVillagers_GetRelationLevelOf(gSaveVillagers, vx, vy)) {
    case 0:
    case 1:
        FieldVillagerAi_AddMood(this, o, 1, 2, 1);
        FieldVillagerAi_AddMood(this, other, 1, 2, 1);
        break;
    case 2:
        break;
    case 3:
    case 4:
        FieldVillagerAi_AddRandomMood(this, o, sChatBadMoods, 2, 2, 1);
        FieldVillagerAi_AddRandomMood(this, other, sChatBadMoods, 2, 2, 1);
        break;
    }
    step = 3;
    return TRUE;
}

BOOL FieldVillagerAiChat::tryChatNeutral(FieldVillager *o) {
    using namespace ns_02262c20;
    void *a;
    void *b;
    FieldVillager *other = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    a = 0;
    b = 0;
    void *x = o->getVillagerData();
    void *y = other->getVillagerData();
    FieldVillagerAi_OrderByFriendship(this, &a, &b, x, y);
    Villager_ShareTrendWith(b, a);
    Villagers_ShareNickname(b, a, 0);
    FieldVillagerAi_AddRandomPairRelation(this, o, sChatNeutralDeltas);
    FieldVillagerAi_AddMood(this, o, 0, 0, 1);
    FieldVillagerAi_AddMood(this, other, 0, 0, 1);
    step = 3;
    return TRUE;
}

BOOL FieldVillagerAiChat::tryChatSpreadCatchphrase(FieldVillager *o) {
    using namespace ns_02262c20;
    void *a;
    void *b;
    FieldVillager *other = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    a = 0;
    b = 0;
    void *x = o->getVillagerData();
    void *y = other->getVillagerData();
    FieldVillagerAi_OrderByFriendship(this, &a, &b, x, y);
    MsgString11 s1;
    MsgString11 s2;
    static_cast<VillagerData *>(a)->getCatchphrase(&s1, 0);
    static_cast<VillagerData *>(b)->getCatchphrase(&s2, 0);
    Villager_ShareTrendWith(b, a);
    Villagers_ShareNickname(b, a, 0);
    if (((MsgString *)(&s1))->equals((MsgString *)(&s2)) != 0) {
        u8 *r6 = reinterpret_cast<u8 *>(static_cast<VillagerData *>(a)->getVillagerId());
        u8 *r7 = reinterpret_cast<u8 *>(static_cast<VillagerData *>(b)->getVillagerId());
        b = 0;
        if (gSaveVillagers != NULL) {
            VillagerData *e;
            u32 mask = 0, cnt = 0;
            s32 i = 0;
            for (i = 0; i < 8; i++) {
                e = SaveVillagers_Get(gSaveVillagers, i);
                if (e != 0) {
                    u8 *q = reinterpret_cast<u8 *>(static_cast<VillagerData *>(e)->getVillagerId());
                    if (((VillagerId *)(q))->isValid() != 0) {
                        BOOL t1 = FALSE, t2 = FALSE;
                        u32 t = *(u16 *)q;
                        if (t == *(u16 *)r6) {
                            if (memcmp(q + 2, r6 + 2, 8) == 0) {
                                t2 = TRUE;
                            }
                        }
                        if (t2) {
                            if (q[0xb] == r6[0xb]) {
                                t1 = TRUE;
                            }
                        }
                        if (t1 == 0) {
                            if (t == *(u16 *)r7 && memcmp(q + 2, r7 + 2, 8) == 0 && q[0xb] == r7[0xb]) {
                            } else {
                                static_cast<VillagerData *>(e)->getCatchphrase(&s2, 0);
                                if (((MsgString *)(&s1))->equals((MsgString *)(&s2)) == 0) {
                                    mask |= 1 << i;
                                    mask = (u8)mask;
                                    cnt++;
                                }
                            }
                        }
                    }
                }
            }
            s32 m = Random_PickSetBit(mask, cnt, 8);
            if (SaveVillagers_IsValidIndex(m) != 0) {
                b = SaveVillagers_Get(gSaveVillagers, m);
            }
        }
    }
    if (b != 0) {
        Villager_SetCatchphraseFromMsg(b, &s1);
    }
    FieldVillagerAi_AddRandomPairRelation(this, o, sChatSpreadCatchphraseDeltas);
    FieldVillagerAi_AddMood(this, o, 1, 2, 1);
    FieldVillagerAi_AddMood(this, other, 1, 2, 1);
    step = 3;
    return TRUE;
}

BOOL FieldVillagerAiChat::tryChatSpreadShirt(FieldVillager *o) {
    using namespace ns_02262c20;
    u16 h0, h1;
    void *a;
    void *b;
    FieldVillager *other = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    a = 0;
    b = 0;
    void *x = o->getVillagerData();
    void *y = other->getVillagerData();
    if (FieldVillagerAi_OrderByFriendship(this, &a, &b, x, y) == 0) {
        chatTarget = other;
    } else {
        chatTarget = o;
    }
    BOOL ok = TRUE;
    if (Unk_ov068_02262c20_InRange(static_cast<VillagerData *>(a)->getShirt())) {
    Pattern *rec = static_cast<VillagerData *>(a)->getPattern();
    Villager_ShareTrendWith(b, a);
    Villagers_ShareNickname(b, a, 0);
    if (Unk_ov068_02262c20_InRange(static_cast<VillagerData *>(b)->getShirt()) && static_cast<VillagerData *>(b)->getPattern()->equals(rec) != 0) {
        u8 *r7 = reinterpret_cast<u8 *>(static_cast<VillagerData *>(a)->getVillagerId());
        u8 *p10 = reinterpret_cast<u8 *>(static_cast<VillagerData *>(b)->getVillagerId());
        ok = FALSE;
        b = 0;
        if (gSaveVillagers != NULL) {
            VillagerData *e;
            u32 mask = 0, cnt = 0;
            s32 i = 0;
            for (i = 0; i < 8; i++) {
                e = SaveVillagers_Get(gSaveVillagers, i);
                if (e != 0) {
                    u8 *q = reinterpret_cast<u8 *>(static_cast<VillagerData *>(e)->getVillagerId());
                    if (((VillagerId *)(q))->isValid() != 0) {
                        BOOL s1 = FALSE, s2 = FALSE;
                        u32 t = *(u16 *)q;
                        if (t == *(u16 *)r7) {
                            if (memcmp(q + 2, r7 + 2, 8) == 0) {
                                s2 = TRUE;
                            }
                        }
                        if (s2) {
                            if (q[0xb] == r7[0xb]) {
                                s1 = TRUE;
                            }
                        }
                        if (s1 == 0) {
                            if (t == *(u16 *)p10 && memcmp(q + 2, p10 + 2, 8) == 0 && q[0xb] == p10[0xb]) {
                            } else {
                                if (!Unk_ov068_02262c20_InRange(static_cast<VillagerData *>(e)->getShirt()) ||
                                    static_cast<VillagerData *>(e)->getPattern()->equals(rec) == 0) {
                                    if (Villager_GetWhereabouts(e) != 0) {
                                        mask |= 1 << i;
                                        mask = (u8)mask;
                                        cnt++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            s32 m = Random_PickSetBit(mask, cnt, 8);
            if (SaveVillagers_IsValidIndex(m) != 0) {
                b = SaveVillagers_Get(gSaveVillagers, m);
            }
        }
    }
    if (b != 0) {
        *static_cast<VillagerData *>(b)->getPattern() = *rec;
        h0 = 0x12a8;
        static_cast<VillagerData *>(b)->setShirt(&h0);
    }
    FieldVillagerAi_AddPartnerRelation(this, o, sChatSpreadShirtDeltas);
    if (ok && b != 0) {
        FieldVillagerAi_AddMood(this, o, 1, 2, 0);
        FieldVillagerAi_AddMood(this, other, 1, 2, 0);
        h1 = 0x12a8;
        chatTarget->actionCtrl.requestAct14(1, &h1);
        step = 2;
    } else {
        FieldVillagerAi_AddMood(this, o, 1, 2, 1);
        FieldVillagerAi_AddMood(this, other, 1, 2, 1);
        step = 3;
    }
    return TRUE;
    }
    return FALSE;
}

BOOL FieldVillagerAiChat::tryChatRevertClothes(FieldVillager *o) {
    using namespace ns_02262c20;
    u16 v0 = 0xfff1;
    u16 v1, v2;
    void *a = 0;
    void *b = 0;
    FieldVillager *other = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    void *x = o->getVillagerData();
    void *y = other->getVillagerData();
    s32 r = FieldVillagerAi_OrderByFriendship(this, &a, &b, x, y);
    Villager_ShareTrendWith(b, a);
    Villagers_ShareNickname(b, a, 0);
    if (r == 0) {
        chatTarget = o;
    } else {
        chatTarget = other;
    }
    FieldVillagerAi_AddRandomPairRelation(this, o, sChatRevertClothesDeltas);
    if (Unk_ov068_02262e5c_InRange(VillagerState_GetHeldItem(Villager_GetState(a))) == 0) {
        Villager_GetDefaultUmbrella(&v1, a);
        v0 = v1;
        static_cast<VillagerData *>(a)->setUmbrella(&v0);
    }
    Villager_GetDefaultShirt(&v2, a);
    v0 = v2;
    u16 *p = static_cast<VillagerData *>(a)->getShirt();
    BOOL same;
    if (Item_IsFurniture(p) != 0) {
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&v0)) {
            same = TRUE;
        } else {
            same = FALSE;
        }
    } else {
        if (*p == v0) {
            same = TRUE;
        } else {
            same = FALSE;
        }
    }
    if (same == 0) {
        FieldVillagerAi_AddRandomMood(this, o, sChatClothesMoods, 4, 2, 0);
        FieldVillagerAi_AddRandomMood(this, other, sChatClothesMoods, 4, 2, 0);
        static_cast<VillagerData *>(a)->setShirt(&v0);
        chatTarget->actionCtrl.requestAct14(1, &v0);
        step = 2;
    } else {
        FieldVillagerAi_AddRandomMood(this, o, sChatClothesMoods, 4, 2, 1);
        FieldVillagerAi_AddRandomMood(this, other, sChatClothesMoods, 4, 2, 1);
        step = 3;
    }
    return TRUE;
}

BOOL FieldVillagerAiChat::tryChatRevertCatchphrase(FieldVillager *o) {
    using namespace ns_02262c20;
    void *a;
    void *b;
    FieldVillager *other = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    a = 0;
    b = 0;
    void *x = o->getVillagerData();
    void *y = other->getVillagerData();
    FieldVillagerAi_OrderByFriendship(this, &a, &b, x, y);
    Villager_ShareTrendWith(b, a);
    Villagers_ShareNickname(b, a, 0);
    FieldVillagerAi_AddRandomPairRelation(this, o, sChatRevertCatchphraseDeltas);
    EncodedString10 obj;
    if (Villager_GetDefaultCatchphraseEncoded(&obj, VillagerId_GetSpecies((VillagerId *)static_cast<VillagerData *>(b)->getVillagerId())) != 0) {
        Villager_SetCatchphraseEncoded(b, &obj);
    }
    FieldVillagerAi_AddRandomMood(this, o, sChatCatchphraseMoods, 4, 2, 1);
    FieldVillagerAi_AddRandomMood(this, other, sChatCatchphraseMoods, 4, 2, 1);
    step = 3;
    return TRUE;
}

BOOL FieldVillagerAiChat::tryChatAdoptAblePattern(FieldVillager *o) {
    using namespace ns_02262c20;
    u16 h0, h1;
    void *a;
    void *b;
    FieldVillager *other = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    a = 0;
    b = 0;
    void *x = o->getVillagerData();
    void *y = other->getVillagerData();
    if (FieldVillagerAi_OrderByFriendship(this, &a, &b, x, y) == 0) {
        chatTarget = o;
    } else {
        chatTarget = other;
    }
    Pattern *rec = 0;
    if (Unk_ov068_02262c20_InRange(static_cast<VillagerData *>(a)->getShirt())) {
        rec = static_cast<VillagerData *>(a)->getPattern();
    }
    rec = FieldVillagerAi_PickOtherAblePattern(this, rec);
    if (rec != 0) {
    Villager_ShareTrendWith(b, a);
    Villagers_ShareNickname(b, a, 0);
    FieldVillagerAi_AddPartnerRelation(this, o, sChatAblePatternDeltas);
    FieldVillagerAi_AddMood(this, chatTarget, 1, 2, 0);
    *static_cast<VillagerData *>(a)->getPattern() = *rec;
    h0 = 0x12a8;
    static_cast<VillagerData *>(a)->setShirt(&h0);
    h1 = 0x12a8;
    chatTarget->actionCtrl.requestAct14(1, &h1);
    step = 2;
    return TRUE;
    }
    return FALSE;
}

BOOL FieldVillagerAiChat::enterChat(FieldVillager *o) {
    using namespace ns_02262294;
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    s32 v = ((NpcActor *)(o))->getAngleTo((NpcActor *)(p));
    FieldVillager_StopEmotion(o);
    o->actionCtrl.requestAction(3, 1, 0, 0, 0, v, 0, 0, data_020c6cc8, 0);
    o->look.setLookModeLocked(o, 2, 0, p, gVec3Zero, 4, data_020c6d1c, 1);
    step = 0;
    ((VillagerActor *)(o))->clearFlag834();
    FieldVillagerAi_AddMood(this, o, 0, 0, 1);
    o->mood.enableEffects();
    return TRUE;
}

void FieldVillagerAiChat::chatStep0(FieldVillager *o) {
    using namespace ns_02262294;
    if (o->actionCtrl.getAction() == 3 && o->actionCtrl.isActionDone() != 0) {
        o->actionCtrl.requestStand(1, data_020c6cc8);
        step = 1;
        s32 t = FieldVillagerAi_GetPartnerRelationLevel(this, o);
        if (t < 5) {
            stateTimer = sChatDurations[t];
        } else {
            stateTimer = 100;
        }
    } else if (FieldVillagerAi_WasHitByNet(this, o) != 0) {
        FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
        if (p != 0 && p->endPartnerTalk() != 0) {
            ((VillagerTalk *)(o))->setPartner(0);
            ((VillagerTalk *)(o))->setInvitedByPartner(0);
            FieldVillagerAi_ChangeState(this, o, 0x13);
            FieldVillagerAi_StartCooldown(this);
        }
    }
}

BOOL FieldVillagerAiChat::isPartnerNear(FieldVillager *o) {
    using namespace ns_02262294;
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    s32 d = 0;
    if (p != 0) {
        d = Vec_DistXZ(&o->position.x, &p->position.x);
    }
    if (d > 0 && d < 0x3c00) {
        return TRUE;
    }
    return FALSE;
}

s32 FieldVillagerAiChat::getPlayerDistance(FieldVillager *o) {
    using namespace ns_02262294;
    s32 r = 0;
    void *a = PlayerActor_GetCharacter(4);
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    if (a != 0 && p != 0) {
        r = ((NpcActor *)(o))->getDistanceTo((NpcActor *)(a));
        s32 b = ((NpcActor *)(p))->getDistanceTo((NpcActor *)(a));
        if (r >= b) {
            r = b;
        }
    }
    return r;
}

BOOL FieldVillagerAiChat::isStrangerPlayerNear(FieldVillager *o, s32 v) {
    using namespace ns_02262294;
    PlayerId *h;
    if (PlayerData_GetCurrent() != 0) {
        h = PlayerData_GetCurrent()->getPlayerId();
    } else {
        h = 0;
    }
    if (h != 0 && h->isValid() != 0) {
        FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
        VillagerMemory *a = Villager_FindMemory(o->getVillagerData(), h);
        VillagerMemory *b = Villager_FindMemory(p->getVillagerData(), h);
        if (a == 0 || b == 0) {
            if (v < 0x6000) {
                return TRUE;
            }
            return FALSE;
        }
    }
    return FALSE;
}

BOOL FieldVillagerAiChat::isEnemyPairWithPlayerNear(FieldVillager *o, s32 v) {
    using namespace ns_02262294;
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    void *a = o->getVillagerData();
    void *b = p->getVillagerData();
    if (SaveVillagers_GetRelationLevelOf(gSaveVillagers, a, b) >= 4) {
        if (v < 0x6000) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

void FieldVillagerAiChat::chatStep1(FieldVillager *o) {
    using namespace ns_02262294;
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    s32 a;
    s32 b;
    s32 t;
    if (FieldVillagerAi_WasHitByNet(this, o) != 0 && ((VillagerActor *)(o))->isFlag834() == 0 && p != 0 && p->endPartnerTalk() != 0) {
        ((VillagerTalk *)(o))->setPartner(0);
        ((VillagerTalk *)(o))->setInvitedByPartner(0);
        FieldVillagerAi_ChangeState(this, o, 0x13);
        FieldVillagerAi_StartCooldown(this);
        return;
    }
    if (((VillagerTalk *)(o))->isInvitedByPartner() == 0) {
        t = getPlayerDistance(o);
        if (isStrangerPlayerNear(o, t) != 0) {
            ((VillagerActor *)(o))->setFlag834();
            if (p != 0) {
                ((VillagerActor *)(p))->setFlag834();
            }
            step = 3;
            return;
        }
        if (isEnemyPairWithPlayerNear(o, t) != 0) {
            ((VillagerActor *)(o))->setFlag834();
            if (p != 0) {
                ((VillagerActor *)(p))->setFlag834();
            }
            step = 3;
            FieldVillagerAi_AddMood(this, o, 2, 1, 1);
            if (p != 0) {
                FieldVillagerAi_AddMood(this, p, 2, 1, 1);
            }
            return;
        }
        if (isPartnerNear(o) == 0) {
            ((VillagerActor *)(o))->setFlag834();
            if (p != 0) {
                ((VillagerActor *)(p))->setFlag834();
            }
            step = 3;
            return;
        }
        a = 0;
        if (o->actionCtrl.isActionDone() != 0) {
            if (o->actionCtrl.getAction() != 8 || o->actionCtrl.getEmotionId() == 0) {
                a = 1;
            }
        }
        b = 0;
        if (p->actionCtrl.isActionDone() != 0) {
            if (o->actionCtrl.getAction() != 8 || o->actionCtrl.getEmotionId() == 0) {
                b = 1;
            }
        }
        if (stateTimer == 0) {
            if (a != 0) {
                if (b == 0) {
                    return;
                }
                if (PlayerData_GetCurrent() == 0) {
                    if (Random_GlobalBelow(2) == 0) {
                        FieldVillagerAi_AddRandomMood(this, o, sChatNoPlayerMoods, 4, 2, 1);
                        FieldVillagerAi_AddRandomMood(this, p, sChatNoPlayerMoods, 4, 2, 1);
                    }
                    step = 3;
                } else {
                    pickChatOutcome(o);
                }
            } else {
                if (o->actionCtrl.getAction() != 8) {
                    return;
                }
                if (o->actionCtrl.getEmotionId() == 0) {
                    return;
                }
                if (o->model.playMode != 0 && o->actionCtrl.isActionDone() != 0) {
                    goto doit1;
                } else if (o->model.playMode == 0) {
                    if ((((u32)o->model.curFrame << 4) >> 16) == 0 || o->actionCtrl.isActionDone() != 0) {
                        goto doit1;
                    }
                }
                return;
            doit1:
                o->actionCtrl.requestEmotion(1, 0, data_020c6cc8);
            }
        } else {
            if (a != 0) {
                if (stateTimer >= 0x14 && Random_GlobalBelow(0x20) == 0) {
                    o->actionCtrl.requestEmotion(1, sChatEmotions[Random_GlobalBelow(8)], data_020c6cc8);
                }
            } else {
                if (o->actionCtrl.getAction() == 8 && o->actionCtrl.getEmotionId() != 0) {
                    if (o->model.playMode != 0 && o->actionCtrl.isActionDone() != 0) {
                        goto doit2;
                    } else if (o->model.playMode == 0) {
                        if ((((u32)o->model.curFrame << 4) >> 16) == 0 || o->actionCtrl.isActionDone() != 0) {
                            goto doit2;
                        }
                    }
                    goto skip2;
                doit2:
                    o->actionCtrl.requestEmotion(1, 0, data_020c6cc8);
                skip2:;
                }
            }
            if (b != 0 && stateTimer >= 0x14 && Random_GlobalBelow(0x20) == 0) {
                p->actionCtrl.requestEmotion(1, sChatEmotions[Random_GlobalBelow(8)], data_020c6cc8);
            }
        }
    } else {
        if (o->actionCtrl.getAction() == 8 && o->actionCtrl.getEmotionId() != 0) {
            if (o->model.playMode != 0 && o->actionCtrl.isActionDone() != 0) {
                goto doit3;
            } else if (o->model.playMode == 0) {
                if ((((u32)o->model.curFrame << 4) >> 16) == 0 || o->actionCtrl.isActionDone() != 0) {
                    goto doit3;
                }
            }
            return;
        doit3:
            o->actionCtrl.requestEmotion(1, 0, data_020c6cc8);
        }
    }
}

void FieldVillagerAiChat::pickChatOutcome(FieldVillager *o) {
    using namespace ns_02262294;
    u32 gv_ = sChatOutcomesGuard;
    if ((gv_ & 1) == 0) {
        sChatOutcomes[0] = &FieldVillagerAiChat::tryChatMoodByRelation;
        sChatOutcomes[1] = &FieldVillagerAiChat::tryChatNeutral;
        sChatOutcomes[2] = &FieldVillagerAiChat::tryChatSpreadCatchphrase;
        sChatOutcomes[3] = &FieldVillagerAiChat::tryChatSpreadShirt;
        sChatOutcomes[4] = &FieldVillagerAiChat::tryChatRevertClothes;
        sChatOutcomes[5] = &FieldVillagerAiChat::tryChatRevertCatchphrase;
        sChatOutcomes[6] = &FieldVillagerAiChat::tryChatAdoptAblePattern;
        sChatOutcomesGuard = gv_ | 1;
    }
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    ((VillagerActor *)(o))->setFlag834();
    ((VillagerActor *)(p))->setFlag834();
    u8 buf[7];
    MI_CpuCopy8(sChatTopicWeights, buf, 7);
    s32 z = 0;
    s32 i;
    for (i = 0; i < 7; i++) {
        u32 k = Talk_PickWeightedIndex(buf, 7);
        if (k < 7) {
            if ((this->*sChatOutcomes[k])(o) != 0) {
                break;
            }
            buf[k] = z;
        }
    }
    if (i == 7) {
        step = 3;
    }
}

void FieldVillagerAiChat::chatStep2(FieldVillager *o) {
    using namespace ns_02262294;
    if (chatTarget->actionCtrl.getAction() == 0x14 && chatTarget->actionCtrl.isActionDone() != 0) {
        o->mood.requestApply();
        static_cast<VillagerActor *>(o)->talkPartner->mood.requestApply();
        step = 3;
    }
}

void FieldVillagerAiChat::chatStep3(FieldVillager *o) {
    using namespace ns_02262294;
    FieldVillager *p = static_cast<FieldVillager *>(static_cast<VillagerActor *>(o)->talkPartner);
    if (p != 0) {
        if (p->endPartnerTalk() != 0) {
            ((VillagerTalk *)(o))->setPartner(0);
            ((VillagerTalk *)(o))->setInvitedByPartner(0);
            if (FieldVillagerAi_Resume(this, o) == 0) {
                FieldVillagerAi_ChangeState(this, o, 0);
            }
            FieldVillagerAi_StartCooldown(this);
        }
    }
}

s32 FieldVillagerAiChat::execChat(FieldVillager *o) {
    using namespace ns_02262294;
    u32 gv_ = sChatStepsGuard;
    if ((gv_ & 1) == 0) {
        sChatSteps[0] = &FieldVillagerAiChat::chatStep0;
        sChatSteps[1] = &FieldVillagerAiChat::chatStep1;
        sChatSteps[2] = &FieldVillagerAiChat::chatStep2;
        sChatSteps[3] = &FieldVillagerAiChat::chatStep3;
        sChatStepsGuard = gv_ | 1;
    }
    if (step < 4) {
        (this->*sChatSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiReaction::enterReaction(FieldVillager *o) {
    using namespace ns_02262294;
    void *p = PlayerActor_GetCharacter(4);
    s32 v = 0;
    void *data = o->villagerData;
    s32 st;
    VillagerMemory *q = o->getPlayerMemory();
    s32 x = v;
    s32 t;
    if (q != 0) {
        x = q->getFriendship();
    }
    if (x >= 0) {
        t = VillagerId_GetPersonality(static_cast<VillagerId *>(static_cast<VillagerData *>(data)->getVillagerId()));
        if (t == 0 || t == 3) {
            st = 1;
        } else {
            st = 0;
        }
    } else {
        t = VillagerId_GetPersonality(static_cast<VillagerId *>(static_cast<VillagerData *>(data)->getVillagerId()));
        switch (t) {
        case 0:
        case 3:
            st = 2;
            break;
        case 1:
        case 4:
            st = 3;
            break;
        case 2:
        default:
            st = 4;
            break;
        }
    }
    if (p != 0) {
        v = ((NpcActor *)(o))->getAngleTo((NpcActor *)(p));
    }
    FieldVillager_StopEmotion(o);
    PlayerActor_LocalRequestAct11();
    o->talkCtrl.requestState4(st, 0, v, 0);
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

void FieldVillagerAiReaction::reactionStep0(FieldVillager *o) {
    using namespace ns_02262294;
    if (o->talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(o);
        FieldVillagerAi_SetResumeState(this, 0);
        step = 1;
    }
}

void FieldVillagerAiReaction::reactionStep1(FieldVillager *o) {
    using namespace ns_02262294;}

s32 FieldVillagerAiReaction::execReaction(FieldVillager *o) {
    using namespace ns_02262294;
    u32 gv_ = sReactionStepsGuard;
    if ((gv_ & 1) == 0) {
        sReactionSteps[0] = &FieldVillagerAiReaction::reactionStep0;
        sReactionSteps[1] = &FieldVillagerAiReaction::reactionStep1;
        sReactionStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sReactionSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiPlayerStates::enterApproach(FieldVillager *o) {
    using namespace ns_02261900;
    FieldVillager_StopEmotion(o);
    approachTarget = (Character *)PlayerActor_GetCharacter(4);
    VecFx32 *pv = &o->position;
    approachStart.x = o->position.x;
    approachStart.y = pv->y;
    approachStart.z = pv->z;
    o->actionCtrl.requestPlayAnim(1, 0xdf, 1, data_020c6cc8, 0);
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    step = 0;
    ((VillagerActor *)(o))->clearFlag834();
    return TRUE;
}

BOOL FieldVillagerAiPlayerStates::isNearApproachStart(FieldVillager *o) {
    using namespace ns_02261900;
    if (Vec_Distance(&o->position.x, &approachStart) <= 0xc000) {
        return TRUE;
    }
    return FALSE;
}

BOOL FieldVillagerAiPlayerStates::isTargetInFront(FieldVillager *o, s32 r) {
    using namespace ns_02261900;
    BOOL res = FALSE;
    if (((NpcActor *)(o))->getDistanceTo((NpcActor *)(approachTarget)) <= r) {
        s32 v = ((NpcActor *)(o))->getRelativeAngleTo((NpcActor *)(approachTarget));
        s32 lim = sSeePlayerArc;
        if (v >= -lim && v <= lim) {
            res = TRUE;
        }
    }
    return res;
}

void FieldVillagerAiPlayerStates::approachStep0(FieldVillager *o) {
    using namespace ns_02261900;
    if (approachTarget != 0) {
        if (o->actionCtrl.isActionDone() != 0) {
            if (isTargetInFront(o, 0x3000) != 0) {
                o->actionCtrl.requestAction(0xb, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                step = 2;
                stateTimer = 0xc8;
            } else {
                Character *p = approachTarget;
                VecFx32 *pv = (VecFx32 *)(ACTOR_POS_AT(p));
                o->actionCtrl.requestAction(2, 1, pv->x, pv->z, 0, 0, 0, 0, data_020c6cc8, 0);
                step = 1;
                stateTimer = 0xc8;
            }
        } else if (o->animCtrl.getAnimId(0) == 0xdf && (((u32)o->model.curFrame << 4) >> 16) == 9) {
            VecFx32 v;
            s16 h;
            v.x = o->jointPos[0].x;
            v.y = o->jointPos[0].y;
            v.z = o->jointPos[0].z;
            h = o->rotY;
            FieldVillagerApproachFx *e = &sApproachAnimFx[Random_GlobalBelow(2)];
            Effect_Create(e->effectId, &v, &h, 0);
            Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, e->seIndex + 0x84, 0x7f, 0);
        }
    } else {
        FieldVillagerAi_ChangeState(this, o, 0);
        seekPlayerCooldown = 0x4b0;
        if (o->getVillagerData() != NULL) {
            Villager_AddTalkUrge(o->getVillagerData(), -1);
        }
    }
}

void FieldVillagerAiPlayerStates::approachStep1(FieldVillager *o) {
    using namespace ns_02261900;
    void *q = &o->moveCtrl.curSpeedPreset.x;
    if (approachTarget != 0) {
        if (isTargetInFront(o, 0x3000) != 0) {
            o->actionCtrl.requestAction(0xb, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            step = 2;
            stateTimer = 0xc8;
        } else if (o->pushFrames >= sFieldVillagerPushLimit) {
            FieldVillagerAi_ChangeState(this, o, 0x15);
        } else if (FieldVillagerAi_WasHitByNet(this, o) != 0) {
            FieldVillagerAi_ChangeState(this, o, 0x13);
        } else if (stateTimer == 0) {
            FieldVillagerAi_ChangeState(this, o, 0);
            seekPlayerCooldown = 0x4b0;
            if (o->getVillagerData() != NULL) {
                Villager_HalveTalkUrge(o->getVillagerData());
            }
        } else if (isNearApproachStart(o) != 0) {
            ((NpcMoveCtrl *)(q))->setWaypoint((VecFx32 *)(ACTOR_POS_AT(approachTarget)));
        } else {
            FieldVillagerAi_ChangeState(this, o, 0);
            seekPlayerCooldown = 0x4b0;
            if (o->getVillagerData() != NULL) {
                Villager_HalveTalkUrge(o->getVillagerData());
            }
        }
    } else {
        FieldVillagerAi_ChangeState(this, o, 0);
        seekPlayerCooldown = 0x4b0;
        if (o->getVillagerData() != NULL) {
            Villager_AddTalkUrge(o->getVillagerData(), -1);
        }
    }
}

void FieldVillagerAiPlayerStates::approachStep2(FieldVillager *o) {
    using namespace ns_02261900;
    if (approachTarget != 0) {
        if (isTargetInFront(o, 0x5000) == 0) {
            s32 t = ((NpcActor *)(o))->getAngleTo((NpcActor *)(approachTarget));
            o->actionCtrl.requestAction(3, 1, 0, 0, 0, t, 0, 0, data_020c6cc8, 0);
            step = 3;
        } else if (o->pushFrames >= sFieldVillagerPushLimit) {
            FieldVillagerAi_ChangeState(this, o, 0x15);
        } else if (FieldVillagerAi_WasHitByNet(this, o) != 0) {
            FieldVillagerAi_ChangeState(this, o, 0x13);
        } else if (stateTimer == 0) {
            FieldVillagerAi_ChangeState(this, o, 0);
            seekPlayerCooldown = 0x4b0;
            if (o->getVillagerData() != NULL) {
                Villager_HalveTalkUrge(o->getVillagerData());
            }
        }
    } else {
        FieldVillagerAi_ChangeState(this, o, 0);
        seekPlayerCooldown = 0x4b0;
        if (o->getVillagerData() != NULL) {
            Villager_AddTalkUrge(o->getVillagerData(), -1);
        }
    }
}

void FieldVillagerAiPlayerStates::approachStep3(FieldVillager *o) {
    using namespace ns_02261900;
    if (o->actionCtrl.getAction() == 3 && o->actionCtrl.isActionDone() != 0) {
        o->actionCtrl.requestStand(1, data_020c6cc8);
        step = 4;
        stateTimer = 10;
    } else if (FieldVillagerAi_WasHitByNet(this, o) != 0) {
        FieldVillagerAi_ChangeState(this, o, 0x13);
    }
}

void FieldVillagerAiPlayerStates::approachStep4(FieldVillager *o) {
    using namespace ns_02261900;
    if (o->pushFrames >= sFieldVillagerPushLimit) {
        FieldVillagerAi_ChangeState(this, o, 0x15);
    } else if (FieldVillagerAi_WasHitByNet(this, o) != 0) {
        FieldVillagerAi_ChangeState(this, o, 0x13);
    } else if (stateTimer == 0) {
        if (isTargetInFront(o, 0x3000) != 0) {
            o->actionCtrl.requestAction(0xb, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            step = 2;
            stateTimer = 0xc8;
        } else if (o->actionCtrl.getAction() == 0 && o->actionCtrl.isActionDone() != 0) {
            Character *p = approachTarget;
            VecFx32 *pv = (VecFx32 *)(ACTOR_POS_AT(p));
            o->actionCtrl.requestAction(2, 1, pv->x, pv->z, 0, 0, 0, 0, data_020c6cc8, 0);
            step = 1;
            stateTimer = 0xc8;
        }
    }
}

s32 FieldVillagerAiPlayerStates::execApproach(FieldVillager *o) {
    using namespace ns_02261900;
    u32 gv_ = sApproachStepsGuard;
    if ((gv_ & 1) == 0) {
        sApproachSteps[0] = &FieldVillagerAiPlayerStates::approachStep0;
        sApproachSteps[1] = &FieldVillagerAiPlayerStates::approachStep1;
        sApproachSteps[2] = &FieldVillagerAiPlayerStates::approachStep2;
        sApproachSteps[3] = &FieldVillagerAiPlayerStates::approachStep3;
        sApproachSteps[4] = &FieldVillagerAiPlayerStates::approachStep4;
        sApproachStepsGuard = gv_ | 1;
    }
    if (step < 5) {
        (this->*sApproachSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiPlayerStates::enterFaceTalker(FieldVillager *o) {
    using namespace ns_02261900;
    FieldVillager_StopEmotion(o);
    if (((VillagerTalk *)(o))->hasPartner() != 0 || o->talkReason != 3 || o->isInPitfall != 0) {
        step = 1;
    } else {
        s32 t = ((NpcActor *)(o))->getAngleToPlayer(o->partnerPlayer);
        o->actionCtrl.requestAction(3, 2, 0, 0, 0, t, 0, 0, data_020c6cc8, 0);
        o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
        step = 0;
    }
    return TRUE;
}

void FieldVillagerAiPlayerStates::faceTalkerStep0(FieldVillager *o) {
    using namespace ns_02261900;
    if (o->actionCtrl.getAction() == 3 && o->actionCtrl.isActionDone() != 0) {
        o->actionCtrl.requestStand(2, data_020c6cc8);
        step = 1;
    }
}

s32 FieldVillagerAiPlayerStates::execFaceTalker(FieldVillager *o) {
    using namespace ns_02261900;
    u32 gv_ = sFaceTalkerStepsGuard;
    if ((gv_ & 1) == 0) {
        sFaceTalkerSteps[0] = &FieldVillagerAiPlayerStates::faceTalkerStep0;
        sFaceTalkerStepsGuard = gv_ | 1;
    }
    if (step < 1) {
        (this->*sFaceTalkerSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiPlayerStates::enterJoinTalk(FieldVillager *o) {
    using namespace ns_02261900;
    FieldVillager_StopEmotion(o);
    o->actionCtrl.requestStand(2, data_020c6cc8);
    ((VillagerActor *)(o))->setFlag834();
    return TRUE;
}

s32 FieldVillagerAiPlayerStates::execJoinTalk(FieldVillager *o) {
    using namespace ns_02261900;
    return 0;
}

BOOL FieldVillagerAiPlayerStates::enterFleaRemoved(FieldVillager *o) {
    using namespace ns_02261900;
    s32 t = ((NpcActor *)(o))->getAngleToPlayer(4);
    FieldVillager_StopEmotion(o);
    o->actionCtrl.requestAction(3, 1, 0, 0, 0, t, 0, 0, data_020c6cc8, 0);
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    ((VillagerActor *)(o))->clearFlag834();
    o->mood.enableEffects();
    return TRUE;
}

void FieldVillagerAiPlayerStates::fleaRemovedStep0(FieldVillager *o) {
    using namespace ns_02261900;
    if (o->actionCtrl.getAction() == 3 && o->actionCtrl.isActionDone() != 0) {
        o->actionCtrl.requestStand(1, data_020c6cc8);
        step = 1;
    }
}

void FieldVillagerAiPlayerStates::fleaRemovedStep1(FieldVillager *o) {
    using namespace ns_02261900;
    if (o->fleaFx.getHoldCount() == 0) {
        step = 2;
        FieldVillagerAi_ChangeState(this, o, 0);
    } else if (o->pushFrames >= sFieldVillagerPushLimit) {
        o->fleaFx.setHoldCount(0);
        FieldVillagerAi_ChangeState(this, o, 0x15);
    } else if (FieldVillagerAi_WasHitByNet(this, o) != 0) {
        o->fleaFx.setHoldCount(0);
        FieldVillagerAi_ChangeState(this, o, 0x13);
    }
}

s32 FieldVillagerAiPlayerStates::execFleaRemoved(FieldVillager *o) {
    using namespace ns_02261900;
    u32 gv_ = sFleaRemovedStepsGuard;
    if ((gv_ & 1) == 0) {
        sFleaRemovedSteps[0] = &FieldVillagerAiPlayerStates::fleaRemovedStep0;
        sFleaRemovedSteps[1] = &FieldVillagerAiPlayerStates::fleaRemovedStep1;
        sFleaRemovedStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sFleaRemovedSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiBirthdayWait::enterBirthdayWait(FieldVillager *o) {
    using namespace ns_02260f90;
    void *g = gSceneBlockMap;
    u16 s[2];
    s32 a = 0, b = 0, c = 0, d = 0;
    if (g != 0) {
        s[0] = 0x5014;
        s[1] = 0x501a;
        if (BlockMap_FindItemAllAttr(g, &a, &b, &c, &d, &s[0], &s[1], 1, 0) != 0) {
            VecFx32 q, p;
            p.x = 0;
            p.y = 0;
            p.z = 0;
            FieldPos_FromBlockUnit(&p, a, b, c, d);
            q.x = p.x;
            q.y = p.y;
            q.z = p.z;
            q.x -= 0x2000;
            q.z += 0x8000;
            q.y = 0;
            VecFx32 *pv = &o->position;
            *pv = q;
            VecFx32 *pw = &o->prevPosition;
            *pw = *pv;
            o->rotY = Math_AngleXZ(&q, &p);
            o->moveAngleY = o->rotY;
            o->moveCtrl.setTargetAngle(o->rotY);
        }
    }
    o->talkReason = 0;
    o->actionCtrl.requestStand(1, data_020c6cc8);
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    Bgm_RequestSilence(0x12, 0xf, 0);
    VillagerStates_SetBirthdayVisitor(-1);
    o->mood.disableEffects();
    TalkRequestFlags_SetEventWarpBlock();
    return TRUE;
}

s32 FieldVillagerAiBirthdayWait::execBirthdayWait(FieldVillager *o) {
    using namespace ns_02260f90;
    TalkRequest_AddPlayerTalk6(o, 0);
    PlayerActor_SetSlotFlag(0x1d, 4);
    return 0;
}

BOOL FieldVillagerAiBirthdayInvite::enterBirthdayInvite(FieldVillager *o) {
    using namespace ns_02260f90;
    void *p = o->villagerTalk.getTalkPlayer();
    s32 v = 0;
    if (p != 0) {
        v = ((NpcActor *)(o))->getAngleTo((NpcActor *)(p));
    }
    o->footstepFx.enableFootsteps();
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    o->talkCtrl.requestTurnAndTalk(0, v, 1);
    o->mood.disableEffects();
    step = 0;
    return TRUE;
}

void FieldVillagerAiBirthdayInvite::birthdayInviteStep0(FieldVillager *o) {
    using namespace ns_02260f90;
    if (o->talkCtrl.isBusy() == 0) {
        Camera_SetModeDefault();
        o->actionCtrl.requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        step = 1;
    }
}

void FieldVillagerAiBirthdayInvite::birthdayInviteStep1(FieldVillager *o) {
    using namespace ns_02260f90;
    if (o->actionCtrl.getAction() == 3 && o->actionCtrl.isActionDone() != 0) {
        VecFx32CopyDtor *pv = (VecFx32CopyDtor *)&o->position;
        VecFx32CopyDtor vv(*pv);
        vv.x -= 0x2000;
        vv.z += 0x8000;
        o->actionCtrl.requestAction(2, 1, vv.x, vv.z, 0, 0, 0, 0, data_020c6cc8, 0);
        stateTimer = 0xc8;
        step = 2;
    }
}

void FieldVillagerAiBirthdayInvite::birthdayInviteStep2(FieldVillager *o) {
    using namespace ns_02260f90;
    if ((o->actionCtrl.getAction() == 2 && o->actionCtrl.isActionDone() != 0) || stateTimer == 0) {
        TalkRequest_SetTargetDone(o);
        o->actionCtrl.requestStand(1, data_020c6cc8);
        TalkRequestFlags_ClearEventWarpBlock();
        step = 3;
    }
}

s32 FieldVillagerAiBirthdayInvite::execBirthdayInvite(FieldVillager *o) {
    using namespace ns_02260f90;
    u32 gv_ = sBirthdayInviteStepsGuard;
    if ((gv_ & 1) == 0) {
        sBirthdayInviteSteps[0] = &FieldVillagerAiBirthdayInvite::birthdayInviteStep0;
        sBirthdayInviteSteps[1] = &FieldVillagerAiBirthdayInvite::birthdayInviteStep1;
        sBirthdayInviteSteps[2] = &FieldVillagerAiBirthdayInvite::birthdayInviteStep2;
        sBirthdayInviteStepsGuard = gv_ | 1;
    }
    if (step < 3) {
        (this->*sBirthdayInviteSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiTakeOut::enterTakeOutItem(FieldVillager *o) {
    using namespace ns_02260f90;
    u16 pos[2];
    Npc_GetStateHeldItem(pos, o);
    FieldVillager_StopEmotion(o);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    if (Unk_ov068_02261118_InRange(&pos[0])) {
        u16 w = data_020c6cc8;
        o->actionCtrl.requestPlayAnim(1, 0xcd, 1, w, 0);
        o->heldTool.attach((NpcActor *)o, (u16 *)(pos), 0xcd, w);
        o->heldTool.playAnim(0x26, w, 1);
        o->heldTool.setAnimSpeed(0x1000);
        o->heldTool.visible = 0;
        step = 1;
    } else {
        u16 w = data_020c6cc8;
        o->actionCtrl.requestPlayAnim(1, 0xd6, 3, w, 0);
        o->heldTool.attach((NpcActor *)o, (u16 *)(pos), 0xd6, w);
        o->heldTool.setAnimSpeed(0);
        o->heldTool.visible = 1;
        step = 0;
    }
    ((VillagerActor *)(o))->setFlag834();
    Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, 0x4f, 0x7f, 0);
    o->mood.disableEffects();
    return TRUE;
}

void FieldVillagerAiTakeOut::takeOutItemStep0(FieldVillager *o) {
    using namespace ns_02260f90;
    if (o->animCtrl.getAnimId(0) == 0xd6) {
        if (o->actionCtrl.isActionDone() != 0) {
            step = 2;
            if (FieldVillagerAi_Resume(this, o) == 0) {
                FieldVillagerAi_ChangeState(this, o, 0);
            }
        } else if ((((u32)o->model.curFrame << 4) >> 16) < 8) {
            s32 v = o->heldTool.getAnimSpeed();
            if ((((u32)o->model.curFrame << 4) >> 16) == 7) {
                o->animCtrl.playHoldItemPose((NpcActor *)(o), (u16 *)(&o->heldTool.heldItem), 0, 7);
            }
            if (v != 0x1000) {
                v += 0x249;
                if (v > 0x1000) {
                    v = 0x1000;
                }
            }
            o->heldTool.setAnimSpeed(v);
        }
    }
}

void FieldVillagerAiTakeOut::takeOutItemStep1(FieldVillager *o) {
    using namespace ns_02260f90;
    if (o->animCtrl.getAnimId(0) == 0xcd) {
        if (o->actionCtrl.isActionDone() != 0) {
            o->animCtrl.playHoldItemPose((NpcActor *)(o), (u16 *)(&o->heldTool.heldItem), 0, 7);
            step = 2;
            if (FieldVillagerAi_Resume(this, o) == 0) {
                FieldVillagerAi_ChangeState(this, o, 0);
            }
        } else if ((((u32)o->model.curFrame << 4) >> 16) == 7) {
            o->heldTool.visible = 1;
            Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, 0x857, 0x7f, 0);
        }
    }
}

s32 FieldVillagerAiTakeOut::execTakeOutItem(FieldVillager *o) {
    using namespace ns_02260f90;
    u32 gv_ = sTakeOutItemStepsGuard;
    if ((gv_ & 1) == 0) {
        sTakeOutItemSteps[0] = &FieldVillagerAiTakeOut::takeOutItemStep0;
        sTakeOutItemSteps[1] = &FieldVillagerAiTakeOut::takeOutItemStep1;
        sTakeOutItemStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sTakeOutItemSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiPutAway::enterPutAwayItem(FieldVillager *o) {
    using namespace ns_02260f90;
    u16 pos[2];
    Npc_GetStateHeldItem(pos, o);
    FieldVillager_StopEmotion(o);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    if (Unk_ov068_02261118_InRange(&pos[0])) {
        u16 w = data_020c6cc8;
        o->actionCtrl.requestPlayAnim(1, 0xcd, 3, w, 0);
        o->heldTool.attach((NpcActor *)o, (u16 *)(pos), 0xcd, w);
        o->heldTool.playAnim(0x26, 1, 3);
        BlendAnimModel *p = o->heldTool.getModel();
        if (p != 0) {
            AnimFrameCtrl *f = static_cast<AnimFrameCtrl *>(p);
            u32 bits = (f->numFrames << 4) >> 16;
            f->setup(bits, 3, 0x1000, (u16)(bits - 1));
        }
        o->heldTool.setAnimSpeed(0x1000);
        Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, 0x858, 0x7f, 0);
        step = 1;
    } else {
        u16 w = data_020c6cc8;
        o->actionCtrl.requestPlayAnim(1, 0xd6, 1, w, 0);
        o->heldTool.attach((NpcActor *)o, (u16 *)(pos), 0xd6, w);
        o->heldTool.setAnimSpeed(0x1000);
        o->heldTool.visible = 1;
        step = 0;
    }
    ((VillagerActor *)(o))->setFlag834();
    Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, 0x4f, 0x7f, 0);
    pos[1] = 0xfff1;
    ((VillagerTalk *)(o))->setSpeakerStateUnk(&pos[1]);
    o->mood.disableEffects();
    return TRUE;
}

void FieldVillagerAiPutAway::putAwayItemStep0(FieldVillager *o) {
    using namespace ns_02260f90;
    if (o->animCtrl.getAnimId(0) == 0xd6) {
        if (o->actionCtrl.isActionDone() != 0) {
            u16 t[1];
            t[0] = 0xfff1;
            o->heldTool.attach((NpcActor *)o, (u16 *)(t), 0, 3);
            step = 2;
            if (FieldVillagerAi_Resume(this, o) == 0) {
                FieldVillagerAi_ChangeState(this, o, 0);
            }
        } else {
            s32 v = o->heldTool.getAnimSpeed();
            if (v != 0) {
                v -= 0x249;
                if (v < 0) {
                    v = 0;
                }
            }
            o->heldTool.setAnimSpeed(v);
        }
    }
}

void FieldVillagerAiPutAway::putAwayItemStep1(FieldVillager *o) {
    using namespace ns_02260f90;
    if (o->animCtrl.getAnimId(0) == 0xcd) {
        if (o->actionCtrl.isActionDone() != 0) {
            step = 2;
            if (FieldVillagerAi_Resume(this, o) == 0) {
                FieldVillagerAi_ChangeState(this, o, 0);
            }
        } else if ((((u32)o->model.curFrame << 4) >> 16) == 5) {
            u16 t[1];
            t[0] = 0xfff1;
            o->heldTool.attach((NpcActor *)o, (u16 *)(t), 0, 3);
            o->heldTool.visible = 0;
        }
    }
}

s32 FieldVillagerAiPutAway::execPutAwayItem(FieldVillager *o) {
    using namespace ns_02260f90;
    u32 gv_ = sPutAwayItemStepsGuard;
    if ((gv_ & 1) == 0) {
        sPutAwayItemSteps[0] = &FieldVillagerAiPutAway::putAwayItemStep0;
        sPutAwayItemSteps[1] = &FieldVillagerAiPutAway::putAwayItemStep1;
        sPutAwayItemStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sPutAwayItemSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiStates::enterPitfall(FieldVillager *o) {
    using namespace ns_022605f4;
    FieldVillager_StopEmotion(o);
    u32 t = data_020c6cc8;
    o->actionCtrl.requestPlayAnim(1, 0x127, 0, t, 0);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    o->heldTool.playPitfallFallAnim(t, 0);
    o->collider.groups |= 2;
    ((VillagerActor *)(o))->setFlag834();
    o->footstepFx.disableFootsteps();
    Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, 0x7ee, 0x7f, 0);
    o->mood.disableEffects();
    return TRUE;
}

namespace ns_022605f4 {
extern "C" {
extern "C" void FieldVillager_StepToward(s32 *p, s32 target, s32 a, s32 spd, s32 min) {
    s32 cur = *p;
    if (cur != target) {
        s32 d = target - cur;
        s32 ad;
        if (d < 0) {
            ad = -d;
        } else {
            ad = d;
        }
        if (ad < min) {
            *p = target;
        } else {
            s32 q = func_01ffcb0c(d, a);
            s32 aq;
            if (q < 0) {
                aq = -q;
            } else {
                aq = q;
            }
            if (aq > spd) {
                if (q >= 0) {
                    *p = *p + spd;
                } else {
                    *p = *p - spd;
                }
            } else if (aq < min) {
                if (q >= 0) {
                    *p = *p + min;
                } else {
                    *p = *p - min;
                }
            } else {
                *p = *p + q;
            }
        }
    }
}
}
}

void FieldVillagerAiStates::pitfallStep0(FieldVillager *o) {
    using namespace ns_022605f4;
    if (o->animCtrl.getAnimId(0) == 0x127) {
        VecFx32 *pp = &o->position;
        VecFx32 loc;
        FieldPos_SnapToUnitCenter(&loc, pp);
        FieldVillager_StepToward(&pp->x, loc.x, 0xe66, 0x1ec, 0x31);
        FieldVillager_StepToward(&pp->z, loc.z, 0xe66, 0x1ec, 0x31);
        o->model.playMode = 1;
        if (pp->x == loc.x && pp->z == loc.z) {
            if (o->model.isFinished() != 0) {
                pitfallStep1(o);
            } else {
                step = 1;
            }
        }
    }
}

void FieldVillagerAiStates::pitfallStep1(FieldVillager *o) {
    using namespace ns_022605f4;
    if (o->animCtrl.getAnimId(0) == 0x127) {
        if (o->model.isFinished() != 0) {
            u32 t = data_020c6cc8;
            o->actionCtrl.requestPlayAnim(1, 0x128, 1, t, 0);
            FieldVillager *ow = o;
            VecFx32 *pv = &ow->position;
            VecFx32 v;
            v.x = ow->position.x;
            v.y = pv->y;
            v.z = pv->z;
            u32 obj[16];
            ((GroundInfo *)(obj))->initAtPos((VecFx32 *)(&v), 0, 0);
            s32 r = obj[13];
            VecFx32 v2;
            v2.x = v.x;
            v2.y = v.y;
            v2.z = v.z;
            FieldItemFx_StartPitfallHole(0, &v2);
            if (r == 0x13) {
                Effect_PlayById(0x8f, &v, 0, 0);
            } else {
                Effect_PlayById(0x8e, &v, 0, 0);
            }
            Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, 0x7e8, 0x7f, 0);
            o->heldTool.playPitfallHoleAnim(t, 1);
            o->animCtrl.playHoldItemPose((NpcActor *)(o), (u16 *)(&o->heldTool.heldItem), 0x128, 3);
            step = 2;
            GroundInfo_Destruct(obj);
        }
    }
}

void FieldVillagerAiStates::pitfallStep2(FieldVillager *o) {
    using namespace ns_022605f4;
    if (o->animCtrl.getAnimId(0) == 0x128) {
        if (o->actionCtrl.isActionDone() != 0) {
            pitfallAnimSpeed = 0x1400;
            u32 t = data_020c6cc8;
            o->actionCtrl.requestPlayAnim(1, 0x129, 0, t, 0);
            o->model.frameStep = pitfallAnimSpeed;
            o->animCtrl.setAnimSpeedFixed(1);
            o->heldTool.playPitfallStuckAnim(t, 0);
            o->heldTool.setModelAnimSpeed(pitfallAnimSpeed);
            pitfallTimer = 0x64;
            FieldVillager *ow = o;
            VecFx32 *pv = &ow->position;
            VecFx32 v;
            v.x = ow->position.x;
            v.y = pv->y;
            v.z = pv->z;
            o->pitfallEffect = Effect_Create(0x4c, &v, 0, 0);
            o->isInPitfall = 1;
            ((VillagerActor *)(o))->clearFlag834();
            step = 3;
        }
    }
}

void FieldVillagerAiStates::pitfallStep3(FieldVillager *o) {
    using namespace ns_022605f4;
    if (o->animCtrl.getAnimId(0) == 0x129) {
        if (pitfallTimer == 0) {
            o->animCtrl.setAnimSpeedFixed(0);
            ((VillagerActor *)(o))->setFlag834();
            o->isInPitfall = 0;
            if (o->pitfallEffect != -1) {
                Effect_End(o->pitfallEffect);
                o->pitfallEffect = -1;
            }
            u16 pos[2];
            Npc_GetStateHeldItem(pos, o);
            BOOL k = FALSE;
            u32 v0 = pos[0];
            if (*(volatile u16 *)&pos[0] >= 0x1376 && v0 <= 0x1376) {
                k = TRUE;
            }
            if (k || (v0 >= 0x1377 && v0 <= 0x1377) || (v0 >= 0x1380 && v0 <= 0x139f) ||
                (v0 >= 0x1374 && v0 <= 0x1374) || (v0 >= 0x1375 && v0 <= 0x1375)) {
                u32 t = data_020c6cc8;
                o->actionCtrl.requestPlayAnim(1, 0x12b, 1, t, 0);
                o->heldTool.playPitfallClimbOutAnim(t, 0);
            } else {
                o->actionCtrl.requestPlayAnim(1, 0x12a, 1, data_020c6cc8, 0);
            }
            FieldVillager *ow = o;
            VecFx32 *pv = &ow->position;
            VecFx32 v;
            v.x = ow->position.x;
            v.y = pv->y;
            v.z = pv->z;
            u32 obj[16];
            ((GroundInfo *)(obj))->initAtPos((VecFx32 *)(&v), 0, 0);
            s32 r = obj[13];
            VecFx32 v2;
            v2.x = v.x;
            v2.y = v.y;
            v2.z = v.z;
            FieldItemFx_StartPitfallClose(0, &v2);
            if (r == 0x13) {
                Effect_PlayById(0x91, &v, 0, 0);
            } else {
                Effect_PlayById(0x90, &v, 0, 0);
            }
            Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, 0x7e9, 0x7f, 0);
            step = 4;
            GroundInfo_Destruct(obj);
        } else {
            o->model.frameStep = pitfallAnimSpeed;
            if (o->pitfallEffect != -1) {
                Effect_SetPosition(o->pitfallEffect, &o->position, NULL, NULL);
            }
        }
    }
}

void FieldVillagerAiStates::pitfallStep4(FieldVillager *o) {
    using namespace ns_022605f4;
    if (o->animCtrl.getAnimId(0) == 0x12b || o->animCtrl.getAnimId(0) == 0x12a) {
        if (o->actionCtrl.isActionDone() != 0) {
            o->collider.groups &= ~2;
            step = 5;
            o->animCtrl.playHoldItemPose((NpcActor *)(o), (u16 *)(&o->heldTool.heldItem), 0, 3);
            FieldVillagerAi_ChangeState(this, o, 0);
        }
    }
}

s32 FieldVillagerAiStates::execPitfall(FieldVillager *o) {
    using namespace ns_022605f4;
    u32 gv_ = sPitfallStepsGuard;
    if ((gv_ & 1) == 0) {
        sPitfallSteps[0] = &FieldVillagerAiStates::pitfallStep0;
        sPitfallSteps[1] = &FieldVillagerAiStates::pitfallStep1;
        sPitfallSteps[2] = &FieldVillagerAiStates::pitfallStep2;
        sPitfallSteps[3] = &FieldVillagerAiStates::pitfallStep3;
        sPitfallSteps[4] = &FieldVillagerAiStates::pitfallStep4;
        sPitfallStepsGuard = gv_ | 1;
    }
    if (step < 5) {
        (this->*sPitfallSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiStates::enterPitfallClimbOut(FieldVillager *o) {
    using namespace ns_022605f4;
    FieldVillager_StopEmotion(o);
    o->animCtrl.setAnimSpeedFixed(0);
    o->look.setLookModeLocked(o, 0, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    o->collider.groups |= 2;
    o->footstepFx.disableFootsteps();
    ((VillagerActor *)(o))->setFlag834();
    o->isInPitfall = 0;
    if (o->pitfallEffect != -1) {
        Effect_End(o->pitfallEffect);
        o->pitfallEffect = -1;
    }
    u16 pos[2];
    Npc_GetStateHeldItem(pos, o);
    BOOL k = FALSE;
    u32 v0 = pos[0];
    if (*(volatile u16 *)&pos[0] >= 0x1376 && v0 <= 0x1376) {
        k = TRUE;
    }
    if (k || (v0 >= 0x1377 && v0 <= 0x1377) || (v0 >= 0x1380 && v0 <= 0x139f) ||
        (v0 >= 0x1374 && v0 <= 0x1374) || (v0 >= 0x1375 && v0 <= 0x1375)) {
        u32 t = data_020c6cc8;
        o->actionCtrl.requestPlayAnim(1, 0x12b, 1, t, 0);
        o->heldTool.playPitfallClimbOutAnim(t, 0);
    } else {
        o->actionCtrl.requestPlayAnim(1, 0x12a, 1, data_020c6cc8, 0);
    }
    FieldVillager *ow = o;
    VecFx32 *pv = &ow->position;
    VecFx32 v;
    v.x = ow->position.x;
    v.y = pv->y;
    v.z = pv->z;
    u32 obj[16];
    ((GroundInfo *)(obj))->initAtPos((VecFx32 *)(&v), 0, 0);
    s32 r = obj[13];
    VecFx32 v2;
    v2.x = v.x;
    v2.y = v.y;
    v2.z = v.z;
    FieldItemFx_StartPitfallClose(0, &v2);
    if (r == 0x13) {
        Effect_PlayById(0x91, &v, 0, 0);
    } else {
        Effect_PlayById(0x90, &v, 0, 0);
    }
    Snd_SeEmitterPlayOneShotAlt(&o->seEmitter, 0x7e9, 0x7f, 0);
    o->mood.disableEffects();
    GroundInfo_Destruct(obj);
    return TRUE;
}

s32 FieldVillagerAiStates::execPitfallClimbOut(FieldVillager *o) {
    using namespace ns_022605f4;
    u32 gv_ = sPitfallClimbOutStepsGuard;
    if ((gv_ & 1) == 0) {
        sPitfallClimbOutSteps[0] = &FieldVillagerAiStates::pitfallStep4;
        sPitfallClimbOutStepsGuard = gv_ | 1;
    }
    if (step < 1) {
        (this->*sPitfallClimbOutSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiStates::enterHitByNet(FieldVillager *o) {
    using namespace ns_022605f4;
    FieldVillager_StopEmotion(o);
    o->animCtrl.setAnimSpeedFixed(0);
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    ((VillagerActor *)(o))->clearFlag834();
    o->footstepFx.enableFootsteps();
    u32 r, t;
    t = data_020c6cc8;
    o->heldTool.playIdleAnim(t, 0);
    if (hitResetTimer == 0) {
        hitCount = 0;
    }
    hitCount = hitCount + 1;
    r = 0xeb;
    if (hitCount >= 3) {
        r = 0xec;
        TalkRequest_AddPlayerTalk6(o, 0);
        o->talkReason = 1;
        ((Character *)(o))->clearTalkStartMode();
        hitCount = 3;
    } else {
        FieldVillager *ow = o;
        VecFx32 *pv = &ow->position;
        FieldVillagerPosCopy v;
        v.x = ow->position.x;
        v.y = pv->y;
        v.z = pv->z;
        void *p = PlayerActor_GetCharacter(4);
        if (p != 0) {
            s32 d = ((NpcActor *)(o))->getRelativeAngleTo((NpcActor *)(p));
            if (d < 0) {
                d = (s16)-d;
            }
            if (d < data_020c6cc0) {
                r = 0xec;
            }
        }
    }
    o->actionCtrl.requestPlayAnim(1, r, 1, t, 0);
    o->mood.disableEffects();
    return TRUE;
}

void FieldVillagerAiStates::hitByNetStep0(FieldVillager *o) {
    using namespace ns_0225fc60;
    if (o->animCtrl.getAnimId(0) == 0xeb || o->animCtrl.getAnimId(0) == 0xec) {
        if (hitCount >= 3) {
            TalkRequest_AddPlayerTalk6(o, 0);
        }
        if (o->actionCtrl.isActionDone() != 0) {
            if (hitCount >= 3) {
                s32 t = ((NpcActor *)(o))->getAngleToPlayer(4);
                o->actionCtrl.requestAction(3, 1, 0, 0, 0, t, 0, 0, data_020c6cc8, 0);
                step = 1;
            } else {
                ((Character *)(o))->setTalkStartMode0();
                FieldVillagerAi_ChangeState(this, o, 0);
                hitResetTimer = 0x4b0;
            }
        }
    }
}

void FieldVillagerAiStates::hitByNetStep1(FieldVillager *o) {
    using namespace ns_0225fc60;
    TalkRequest_AddPlayerTalk6(o, 0);
    if (o->actionCtrl.getAction() == 3 && o->actionCtrl.isActionDone() != 0) {
        o->actionCtrl.requestStand(1, data_020c6cc8);
        stateTimer = 0x28;
        step = 2;
    }
}

void FieldVillagerAiStates::hitByNetStep2(FieldVillager *o) {
    using namespace ns_0225fc60;
    if (stateTimer == 0) {
        hitResetTimer = 0x4b0;
        FieldVillagerAi_ChangeState(this, o, 0);
        ((Character *)(o))->setTalkStartMode0();
    } else {
        TalkRequest_AddPlayerTalk6(o, 0);
    }
}

s32 FieldVillagerAiStates::execHitByNet(FieldVillager *o) {
    using namespace ns_0225fc60;
    u32 gv_ = sHitByNetStepsGuard;
    if ((gv_ & 1) == 0) {
        sHitByNetSteps[0] = &FieldVillagerAiStates::hitByNetStep0;
        sHitByNetSteps[1] = &FieldVillagerAiStates::hitByNetStep1;
        sHitByNetSteps[2] = &FieldVillagerAiStates::hitByNetStep2;
        sHitByNetStepsGuard = gv_ | 1;
    }
    if (step < 3) {
        (this->*sHitByNetSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiStates::enterPushed(FieldVillager *o) {
    using namespace ns_0225fc60;
    FieldVillager_StopEmotion(o);
    o->animCtrl.setAnimSpeedFixed(0);
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    ((VillagerActor *)(o))->clearFlag834();
    o->footstepFx.enableFootsteps();
    s32 t = ((NpcActor *)(o))->getAngleToPlayer(4);
    o->actionCtrl.requestAction(3, 1, 0, 0, 0, t, 0, 0, data_020c6cc8, 0);
    o->pushFrames = 0;
    TalkRequest_AddPlayerTalk6(o, 0);
    o->talkReason = 2;
    ((Character *)(o))->clearTalkStartMode();
    step = 0;
    o->mood.disableEffects();
    if (o->getVillagerData() != NULL) {
        Villager_HalveTalkUrge(o->getVillagerData());
    }
    return TRUE;
}

void FieldVillagerAiStates::pushedStep0(FieldVillager *o) {
    using namespace ns_0225fc60;
    TalkRequest_AddPlayerTalk6(o, 0);
    if (o->actionCtrl.getAction() == 3 && o->actionCtrl.isActionDone() != 0) {
        o->actionCtrl.requestStand(1, data_020c6cc8);
        stateTimer = 0x28;
        step = 1;
    }
}

void FieldVillagerAiStates::pushedStep1(FieldVillager *o) {
    using namespace ns_0225fc60;
    if (stateTimer == 0) {
        FieldVillagerAi_ChangeState(this, o, 0);
        ((Character *)(o))->setTalkStartMode0();
    } else {
        TalkRequest_AddPlayerTalk6(o, 0);
    }
}

s32 FieldVillagerAiStates::execPushed(FieldVillager *o) {
    using namespace ns_0225fc60;
    u32 gv_ = sPushedStepsGuard;
    if ((gv_ & 1) == 0) {
        sPushedSteps[0] = &FieldVillagerAiStates::pushedStep0;
        sPushedSteps[1] = &FieldVillagerAiStates::pushedStep1;
        sPushedStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sPushedSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiStates::enterHitTalk(FieldVillager *o) {
    using namespace ns_0225fc60;
    ((NpcActor *)(o))->resetLastTaughtEmotion();
    if (o->animCtrl.getAnimId(0) != 0xec || o->actionCtrl.isActionDone() != 0) {
        void *p = o->villagerTalk.getTalkPlayer();
        s32 v = 0;
        if (p != 0) {
            v = ((NpcActor *)(o))->getAngleTo((NpcActor *)(p));
        }
        o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
        o->talkCtrl.requestTurnAndTalk(0, v, 0);
        step = 1;
    } else {
        step = 0;
    }
    return TRUE;
}

void FieldVillagerAiStates::hitTalkStep0(FieldVillager *o) {
    using namespace ns_0225fc60;
    if (o->animCtrl.getAnimId(0) != 0xec || o->actionCtrl.isActionDone() != 0) {
        void *p = o->villagerTalk.getTalkPlayer();
        s32 v = 0;
        if (p != 0) {
            v = ((NpcActor *)(o))->getAngleTo((NpcActor *)(p));
        }
        o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
        o->talkCtrl.requestTurnAndTalk(0, v, 0);
        step = 1;
    }
}

void FieldVillagerAiStates::hitTalkStep1(FieldVillager *o) {
    using namespace ns_0225fc60;
    if (o->talkCtrl.isBusy() == 0) {
        FieldVillagerAi_AddMood(this, o, 4, 1, 1);
        ((Character *)(o))->setTalkStartMode0();
        TalkRequest_SetTargetDone(o);
        ((VillagerTalk *)(o))->setPartner(0);
        ((VillagerTalk *)(o))->setInvitedByPartner(0);
        FieldVillagerAi_SetResumeState(this, 0);
        hitCount = 0;
        hitResetTimer = 0;
        o->talkReason = 3;
        seekPlayerCooldown = 0x4b0;
        step = 2;
    }
}

void FieldVillagerAiStates::hitTalkStep2(FieldVillager *o) {
    using namespace ns_0225fc60;}

s32 FieldVillagerAiStates::execHitTalk(FieldVillager *o) {
    using namespace ns_0225fc60;
    u32 gv_ = sHitTalkStepsGuard;
    if ((gv_ & 1) == 0) {
        sHitTalkSteps[0] = &FieldVillagerAiStates::hitTalkStep0;
        sHitTalkSteps[1] = &FieldVillagerAiStates::hitTalkStep1;
        sHitTalkSteps[2] = &FieldVillagerAiStates::hitTalkStep2;
        sHitTalkStepsGuard = gv_ | 1;
    }
    if (step < 3) {
        (this->*sHitTalkSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiStates::enterPushTalk(FieldVillager *o) {
    using namespace ns_0225fc60;
    void *p = o->villagerTalk.getTalkPlayer();
    s32 v = 0;
    ((NpcActor *)(o))->resetLastTaughtEmotion();
    if (p != 0) {
        v = ((NpcActor *)(o))->getAngleTo((NpcActor *)(p));
    }
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    o->talkCtrl.requestTurnAndTalk(0, v, 0);
    return TRUE;
}

void FieldVillagerAiStates::pushTalkStep0(FieldVillager *o) {
    using namespace ns_0225fc60;
    if (o->talkCtrl.isBusy() == 0) {
        FieldVillagerAi_AddMood(this, o, 4, 1, 1);
        ((Character *)(o))->setTalkStartMode0();
        TalkRequest_SetTargetDone(o);
        ((VillagerTalk *)(o))->setPartner(0);
        FieldVillagerAi_SetResumeState(this, 0);
        ((VillagerTalk *)(o))->setInvitedByPartner(0);
        o->talkReason = 3;
        seekPlayerCooldown = 0x4b0;
        step = 1;
    }
}

void FieldVillagerAiStates::pushTalkStep1(FieldVillager *o) {
    using namespace ns_0225fc60;}

s32 FieldVillagerAiStates::execPushTalk(FieldVillager *o) {
    using namespace ns_0225fc60;
    u32 gv_ = sPushTalkStepsGuard;
    if ((gv_ & 1) == 0) {
        sPushTalkSteps[0] = &FieldVillagerAiStates::pushTalkStep0;
        sPushTalkSteps[1] = &FieldVillagerAiStates::pushTalkStep1;
        sPushTalkStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sPushTalkSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillagerAiStates::enterAdmireCatch(FieldVillager *o) {
    using namespace ns_0225fc60;
    FieldVillager_StopEmotion(o);
    o->animCtrl.setAnimSpeedFixed(0);
    o->look.setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    ((VillagerActor *)(o))->clearFlag834();
    o->footstepFx.enableFootsteps();
    s32 t = ((NpcActor *)(o))->getAngleToPlayer(4);
    o->actionCtrl.requestAction(3, 1, 0, 0, 0, t, 0, 0, data_020c6cc8, 0);
    o->mood.disableEffects();
    step = 0;
    isAdmiringCatch = 1;
    return TRUE;
}

void FieldVillagerAiStates::admireCatchStep0(FieldVillager *o) {
    using namespace ns_0225fc60;
    if (o->actionCtrl.getAction() == 3 && o->actionCtrl.isActionDone() != 0) {
        o->actionCtrl.requestEmotion(1, 0x1a, data_020c6cc8);
        stateTimer = 0x14;
        step = 1;
    }
}

void FieldVillagerAiStates::admireCatchStep1(FieldVillager *o) {
    using namespace ns_0225fc60;
    if (o->actionCtrl.getAction() == 8 && o->actionCtrl.getEmotionId() == 0x1a && stateTimer == 0 &&
        FieldVillagerAi_IsPlayerShowingCatch(this) == 0 && (((u32)o->model.curFrame << 4) >> 16) == 0) {
        o->actionCtrl.requestStand(1, data_020c6cc8);
        FieldVillagerAi_ChangeState(this, o, 0);
    }
}

s32 FieldVillagerAiStates::execAdmireCatch(FieldVillager *o) {
    using namespace ns_0225fc60;
    u32 gv_ = sAdmireCatchStepsGuard;
    if ((gv_ & 1) == 0) {
        sAdmireCatchSteps[0] = &FieldVillagerAiStates::admireCatchStep0;
        sAdmireCatchSteps[1] = &FieldVillagerAiStates::admireCatchStep1;
        sAdmireCatchStepsGuard = gv_ | 1;
    }
    if (step < 2) {
        (this->*sAdmireCatchSteps[step])(o);
    }
    return 0;
}

BOOL FieldVillager::acceptsInteraction(void *) {
    using namespace ns_0225fc60;
    if (talkCtrl.isBusy() != 0 || isFlag834() != 0) {
        return FALSE;
    }
    if (isInPitfall != 0) {
        void *p = PlayerActor_GetCharacter(4);
        if (p != 0) {
            s32 v = getRelativeAngleTo((NpcActor *)(p));
            if (v < 0) {
                v = (s16)-v;
            }
            if (v > data_020c6cc0) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

BOOL FieldVillager::acceptsInteractionOutOfRange(void *other) {
    using namespace ns_0225fc60;
    Character *x = (Character *)other;
    s16 k = sTalkFacingArc;
    u32 v = FieldVillager_GetMood(this);
    BOOL r = FALSE;
    if (acceptsInteraction(x) != 0 && isFlag834() == 0 && FieldVillagerAi_IsState(&ai, r) != 0 && v <= 1 &&
        isNear((NpcActor *)(x), 0x5000) == 0 && isNear((NpcActor *)(x), 0xe000) != 0 && isInFacingArcOf(x, (s16)-k, k) != 0) {
        r = TRUE;
    }
    return r;
}

void FieldVillager::onInteractionEvent(u32 idx, u8 v) {
    using namespace ns_0225f1a0;
    switch (idx) {
    case 3:
        partnerPlayer = v;
        if (((VillagerTalk *)(this))->hasPartner()) {
            talkType = 1;
            talkPartner = (NpcActor *)((VillagerTalk *)(this))->getPartner();
            talkPartner->onJoinTalk();
        } else if (FieldVillagerAi_IsState(&ai, 7)) {
            talkType = 2;
        } else if (isInPitfall) {
            talkType = 0xe;
        } else {
            switch (((VillagerTalk *)(this))->getEventKind()) {
            case 1:
                talkType = 3;
                break;
            case 2:
                talkType = 4;
                break;
            case 0:
                talkType = 5;
                break;
            case 3:
                talkType = 6;
                break;
            case 4:
                talkType = 7;
                break;
            case 5:
                talkType = 8;
                break;
            case 6:
                talkType = 9;
                break;
            case 7:
                talkType = 10;
                break;
            case 8:
            case 9:
                talkType = 11;
                break;
            default:
                talkType = 0;
                break;
            }
        }
        if (talkType == 0) {
            void *rep = FieldVillager_GetTalkRepeat(this);
            if (rep) {
                TalkRepeat_Count(rep);
            }
        }
        FieldVillagerAi_ChangeState(&ai, this, 8);
        break;
    case 1: {
        s32 r6 = 5;
        switch (talkReason) {
        case 0:
            r6 = 0xe;
            talkType = 0xd;
            break;
        case 1:
            r6 = 0x14;
            talkType = 0xf;
            break;
        case 2:
            r6 = 0x16;
            talkType = 0x10;
            break;
        }
        ((VillagerTalk *)((&villagerTalk)))->begin((VillagerActor *)(this), talkType);
        ((ActorTalkRequest *)((&villagerTalk)))->setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
        FieldVillagerAi_ChangeState(&ai, this, r6);
        break;
    }
    case 0:
        partnerPlayer = v;
        ((VillagerTalk *)((&villagerTalk)))->begin((VillagerActor *)(this), talkType);
        ((ActorTalkRequest *)((&villagerTalk)))->setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
        if (talkPartner) {
            ((ActorTalkRequest *)((&villagerTalk)))->setPartnerActor((NpcActor *)(talkPartner));
        }
        FieldVillagerAi_ChangeState(&ai, this, 5);
        if (talkType == 2) {
            if (getVillagerData()) {
                Villager_ClearTalkUrge(getVillagerData());
            }
        }
        talkPartner = NULL;
        talkType = 0;
        break;
    case 5:
        partnerPlayer = v;
        FieldVillagerAi_SaveResumeState(&ai);
        FieldVillagerAi_ChangeState(&ai, this, 6);
        break;
    case 8: {
        s32 t;
        void *q;
        s32 sv;
        if (talkReason == 0) {
            t = Villager_GetWhereabouts(static_cast<VillagerData *>(getVillagerData()));
            q = ((VillagerDataItemView *)(getVillagerData()))->getHousePos();
            FieldPos_FromUnitCenter(&position, ((u8 *)q)[0], ((u8 *)q)[1]);
            { VecFx32 *sp = (VecFx32 *)&position; VecFx32 *d = (VecFx32 *)&prevPosition; d->x = sp->x; d->y = sp->y; d->z = sp->z; }
            sv = VillagerStates_GetBirthdayHost();
            if (sv == Villager_GetIndex(getVillagerData()) || (u32)(t - 3) <= 4) {
                FieldVillagerAi_ChangeState(&ai, this, 0xc);
            } else {
                FieldVillagerAi_ChangeState(&ai, this, 3);
            }
            talkReason = 3;
        } else if (talkReason == 2) {
            FieldVillagerAi_ChangeState(&ai, this, 0);
            talkReason = 3;
        } else if (isInPitfall) {
            FieldVillagerAi_ChangeState(&ai, this, 0x12);
        } else {
            if (FieldVillagerAi_Resume(&ai, this) == 0) {
                FieldVillagerAi_ChangeState(&ai, this, 0);
            }
            void *rep = FieldVillager_GetTalkRepeat(this);
            if (rep) {
                TalkRepeat_StartWindow(rep);
            }
        }
        ((Character *)(this))->setTalkStartMode0();
        if (getVillagerData()) {
            Villager_AddTalkUrge(getVillagerData(), -3);
        }
        break;
    }
    case 4:
        if (isInPitfall) {
            FieldVillagerAi_ChangeState(&ai, this, 0x12);
        } else {
            if (FieldVillagerAi_Resume(&ai, this) == 0) {
                FieldVillagerAi_ChangeState(&ai, this, 0);
            }
        }
        break;
    }
    NpcActor::onInteractionEvent(idx, v);
}

void FieldVillagerFxTimer::construct() {
    using namespace ns_0225f1a0;
}

FieldVillagerFxTimer::~FieldVillagerFxTimer() {
    using namespace ns_0225f1a0;
}

void FieldVillagerFxTimer::clear() {
    using namespace ns_0225f1a0;
    fleaEffectTimer = -1;
    holdCount = 0;
}

void FieldVillagerFxTimer::update(FieldVillager *o) {
    using namespace ns_0225f1a0;
    VecFx32 buf;
    if (fleaEffectTimer > 0) {
        fleaEffectTimer = fleaEffectTimer - (TICK_STEP_ENDS() ? 1 : 0);
    }
    if (holdCount != 0) {
        holdCount = holdCount - 1;
    }
    if (fleaEffectTimer == 0) {
        buf.x = o->jointPos[0].x;
        buf.y = o->jointPos[0].y;
        buf.z = o->jointPos[0].z;
        Effect_PlayById(0x81, &buf, 0, 0);
        if (Villager_HasFlea(o->villagerData)) {
            fleaEffectTimer = Random_GlobalBelow(0xf) + 0xf;
        } else {
            fleaEffectTimer = -1;
        }
    } else if (fleaEffectTimer == -1) {
        if (Villager_HasFlea(o->villagerData)) {
            fleaEffectTimer = Random_GlobalBelow(10) + 0xf;
        }
    }
}

void FieldVillagerFxTimer::stop(FieldVillager *o) {
    using namespace ns_0225f1a0;
    fleaEffectTimer = -1;
    Villager_RemoveFlea(o->villagerData);
}

u32 FieldVillagerFxTimer::getHoldCount() {
    using namespace ns_0225f1a0;
    return holdCount;
}

void FieldVillagerFxTimer::setHoldCount(u32 v) {
    using namespace ns_0225f1a0;
    holdCount = v;
}

BOOL FieldVillager::canAcceptPartnerInvite() {
    using namespace ns_0225f1a0;
    void *p = (void *)getPlayerMemory();
    if (PlayerData_GetCurrent()) {
        p = (void *)getPlayerMemory();
    }
    if ((p == NULL && ((NpcActor *)(this))->isPlayerNear(0x6000, 4) == 0) || (p != NULL && VillagerMemory_IsUsed(p) != 0)) {
        if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
            if (FieldVillagerAi_IsFreeIdle(&ai) != 0) {
                if (((VillagerTalk *)(this))->hasPartner() == 0) {
                    if (((VillagerTalk *)(this))->getEventKind() == 0xb) {
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

BOOL FieldVillager::acceptPartnerInvite(VillagerActor *partner) {
    using namespace ns_0225f1a0;
    if (canAcceptPartnerInvite()) {
        ((VillagerTalk *)(this))->setPartner(partner);
        ((VillagerTalk *)(this))->setInvitedByPartner(1);
        FieldVillagerAi_SaveResumeState(&ai);
        FieldVillagerAi_ChangeState(&ai, this, 9);
        return TRUE;
    }
    return FALSE;
}

BOOL FieldVillager::endPartnerTalk() {
    using namespace ns_0225f1a0;
    if (((VillagerTalk *)(this))->hasPartner()) {
        FieldVillager_StopEmotion(this);
        if (FieldVillagerAi_Resume(&ai, this) == 0) {
            FieldVillagerAi_ChangeState(&ai, this, 0);
        }
        FieldVillagerAi_StartCooldown(&ai);
        ((VillagerTalk *)(this))->setPartner(0);
        ((VillagerTalk *)(this))->setInvitedByPartner(0);
        return TRUE;
    }
    return FALSE;
}

void FieldVillager::onJoinTalk() {
    using namespace ns_0225f1a0;
    FieldVillagerAi_ChangeState(&ai, this, 10);
}

void FieldVillager::onLeaveTalk() {
    using namespace ns_0225f1a0;
    ((VillagerMood *)(&mood))->requestApply();
    if (FieldVillagerAi_Resume(&ai, this) == 0) {
        FieldVillagerAi_ChangeState(&ai, this, 0);
    }
    ((VillagerTalk *)(this))->setPartner(0);
    ((VillagerTalk *)(this))->setInvitedByPartner(0);
    FieldVillagerAi_StartCooldown(&ai);
}

void FieldVillagerLook::construct() {
    using namespace ns_0225f1a0;
}

FieldVillagerLook::~FieldVillagerLook() {
    using namespace ns_0225f1a0;
}

void FieldVillagerLook::init(FieldVillager *o) {
    using namespace ns_0225f1a0;
    setLookModeLocked(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    targetKind = 2;
    targetSlot = -1;
    targetId = -1;
}

void FieldVillagerLook::resetLook(FieldVillager *o) {
    using namespace ns_0225f1a0;
    isLocked = 0;
    setLookMode(o, 1, 0, 0, gVec3Zero, 4, data_020c6d1c, 1);
    targetKind = 2;
    targetSlot = -1;
    targetId = -1;
    lookTime = 0;
}

void FieldVillagerLook::setLookModeLocked(FieldVillager *o, u32 idx, s32 a, Character *target, void *v, s32 c, s32 d, u8 e) {
    using namespace ns_0225f1a0;
    isLocked = 1;
    setLookMode(o, idx, a, target, v, c, d, e);
    targetKind = 3;
    targetSlot = -1;
    targetId = -1;
    lookTime = 0;
}

void FieldVillagerLook::tickLookTime() {
    using namespace ns_0225f1a0;
    lookTime++;
    if (lookTime > 0x960) {
        lookTime = 0x960;
    }
}

void FieldVillagerLook::setLookMode(FieldVillager *o, u32 idx, s32 a, Character *target, void *v, s32 c, s32 d, u8 e) {
    using namespace ns_0225f1a0;
    o->lookAt.setTarget(idx, a, target, (VecFx32 *)(v), c, d, e);
    lookMode = idx;
}

s32 FieldVillagerLook::getInsectIfNear(VecFx32 *v, s32 i, VecFx32 *p, s32 lim) {
    using namespace ns_0225f1a0;
    s32 t = Shared_FieldInsect_GetPosAndKind((VecFx32Ctor *)v, i);
    if (t != -1 && Vec_DistXZ(p, v) < lim) {
        return t;
    }
    return -1;
}

s32 FieldVillagerLook::findInsectNear(VecFx32 *v, s32 *out, VecFx32 *p, s32 lim) {
    using namespace ns_0225f1a0;
    s32 i;
    s32 t;
    for (i = 0; i < 8; i++) {
        t = getInsectIfNear(v, i, p, lim);
        if (t != -1) {
            *out = i;
            return t;
        }
    }
    return -1;
}

BOOL FieldVillagerLook::isSameInsect(u32 a, s32 b) {
    using namespace ns_0225f1a0;
    u8 buf[1];
    if (b != -1) {
        s32 t;
        buf[0] = 0;
        t = FieldInsect_GetKindAndAlarm(buf, a);
        if (t == b) {
            return TRUE;
        }
    }
    return FALSE;
}

void FieldVillagerLook::startLookAtInsect(FieldVillager *o, s32 a, s32 b, VecFx32 *v) {
    using namespace ns_0225f1a0;
    targetSlot = a;
    targetId = b;
    setLookMode(o, 3, 0, 0, v, 4, data_020c6d1c, 1);
    targetKind = 0;
    lookTime = 0;
}

void FieldVillagerLook::trackInsect(FieldVillager *o) {
    using namespace ns_0225f1a0;
    VecFx32 buf;
    if (isSameInsect(targetSlot, targetId)) {
        s32 r = getInsectIfNear(&buf, targetSlot, (VecFx32 *)&o->position, o->lookAt.maxDistance);
        if (r != -1 && r == targetId) {
            ((NpcLookAt *)(&o->lookAt))->setTargetPos((VecFx32 *)(&buf));
        } else {
            resetLook(o);
        }
    } else {
        resetLook(o);
    }
}

BOOL FieldVillagerLook::getFishPosIfNear(VecFx32 *v, s32 i, VecFx32 *p, s32 lim) {
    using namespace ns_0225f1a0;
    if (FishShadow_GetPos(v, i) && Vec_DistXZ(p, v) < lim) {
        return TRUE;
    }
    return FALSE;
}

s32 FieldVillagerLook::findFishNear(VecFx32 *v, s32 *out, VecFx32 *p, s32 lim) {
    using namespace ns_0225f1a0;
    s32 i;
    s32 t;
    for (i = 0; i < 6; i++) {
        t = FishShadow_GetFishId(i);
        if (t != -1) {
            if (getFishPosIfNear(v, i, p, lim)) {
                *out = i;
                return t;
            }
        }
    }
    return -1;
}

BOOL FieldVillagerLook::isSameFish(s32 a, s32 b) {
    using namespace ns_0225f1a0;
    s32 t = FishShadow_GetFishId(a);
    if (t != -1 && b == t) {
        return TRUE;
    }
    return FALSE;
}

void FieldVillagerLook::startLookAtFish(FieldVillager *o, s32 a, s32 b, VecFx32 *v) {
    using namespace ns_0225f1a0;
    targetSlot = a;
    targetId = b;
    setLookMode(o, 3, 0, 0, v, 4, data_020c6d1c, 1);
    targetKind = 1;
    lookTime = 0;
}

void FieldVillagerLook::trackFish(FieldVillager *o) {
    using namespace ns_0225f1a0;
    VecFx32 buf;
    if (isSameFish(targetSlot, targetId)) {
        if (getFishPosIfNear(&buf, targetSlot, (VecFx32 *)&o->position, o->lookAt.maxDistance)) {
            ((NpcLookAt *)(&o->lookAt))->setTargetPos((VecFx32 *)(&buf));
        } else {
            resetLook(o);
        }
    } else {
        resetLook(o);
    }
}

void FieldVillagerLook::update(FieldVillager *o) {
    using namespace ns_0225f1a0;
    s32 idx;
    VecFx32 buf;
    if (isLocked == 0) {
        u8 a = lookMode;
        u8 b = o->lookAt.lookType;
        if (a == b) {
            switch (a) {
            case 1:
                if (FieldVillager_GetMood(o) <= 1) {
                    if (((NpcLookAt *)(&o->lookAt))->canSeeTarget((Character *)(o)) == 0) {
                        s32 r;
                        idx = -1;
                        r = findInsectNear(&buf, &idx, (VecFx32 *)&o->position, 0x5000);
                        if (r != -1) {
                            startLookAtInsect(o, idx, r, &buf);
                        } else {
                            idx = -1;
                            r = findFishNear(&buf, &idx, (VecFx32 *)&o->position, 0x5000);
                            if (r != -1) {
                                startLookAtFish(o, idx, r, &buf);
                            }
                        }
                    }
                }
                break;
            case 3:
                if (((NpcLookAt *)(&o->lookAt))->canSeeTarget((Character *)(o))) {
                    tickLookTime();
                }
                switch (targetKind) {
                case 0:
                    trackInsect(o);
                    break;
                case 1:
                    trackFish(o);
                    break;
                default:
                    resetLook(o);
                    break;
                }
                break;
            }
        } else {
            isLocked = 1;
            targetKind = 3;
        }
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_0225f1a0) {
    HOST_OVERLAY_VAR(nsD::sReactionStepsGuard),
    HOST_OVERLAY_VAR(nsD::sChatNoPlayerMoods),
    HOST_OVERLAY_VAR(nsD::data_ov068_0226f910),
    HOST_OVERLAY_VAR(nsD::sFieldVillagerPushLimit),
    HOST_OVERLAY_VAR(nsD::sBirthdayInviteSteps),
    HOST_OVERLAY_VAR(nsD::sPushTalkSteps),
    HOST_OVERLAY_VAR(nsD::sSimCatchClassWeightsPlanned),
    HOST_OVERLAY_VAR(nsD::sHitTalkStepsGuard),
    HOST_OVERLAY_VAR(nsD::sChatSteps),
    HOST_OVERLAY_VAR(nsD::sTalkSteps),
    HOST_OVERLAY_VAR(nsD::sFieldVillagerAiTable),
    HOST_OVERLAY_VAR(nsD::sChatStepsGuard),
    HOST_OVERLAY_VAR(nsD::sChatCatchphraseMoods),
    HOST_OVERLAY_VAR(nsD::sPitfallClimbOutSteps),
    HOST_OVERLAY_VAR(nsD::sFieldVillagerAiCooldown),
    HOST_OVERLAY_VAR(nsD::sPutAwayItemSteps),
    HOST_OVERLAY_VAR(nsD::data_ov068_0226fa68),
    HOST_OVERLAY_VAR(nsD::sTalkStepsGuard),
    HOST_OVERLAY_VAR(nsD::sReactionSteps),
    HOST_OVERLAY_VAR(nsD::sApproachStepsGuard),
    HOST_OVERLAY_VAR(nsD::sChatEmotions),
    HOST_OVERLAY_VAR(nsD::sFaceTalkerStepsGuard),
    HOST_OVERLAY_VAR(nsD::sTakeOutItemStepsGuard),
    HOST_OVERLAY_VAR(nsD::sAbsentStepsGuard),
    HOST_OVERLAY_VAR(nsD::sInHouseStepsGuard),
    HOST_OVERLAY_VAR(nsD::sAbsentSteps),
    HOST_OVERLAY_VAR(nsD::data_ov068_0226f0f4),
    HOST_OVERLAY_VAR(nsD::sChatBadMoods),
    HOST_OVERLAY_VAR(nsD::sApproachSteps),
    HOST_OVERLAY_VAR(nsD::sSeePlayerArc),
    HOST_OVERLAY_VAR(nsD::sGoInHouseSteps),
    HOST_OVERLAY_VAR(nsD::sHitByNetSteps),
    HOST_OVERLAY_VAR(nsD::data_ov068_0226f13c),
    HOST_OVERLAY_VAR(nsD::sPutAwayItemStepsGuard),
    HOST_OVERLAY_VAR(nsD::sChatTopicWeights),
    HOST_OVERLAY_VAR(nsD::sGoInHouseStepsGuard),
    HOST_OVERLAY_VAR(nsD::sChatOutcomesGuard),
    HOST_OVERLAY_VAR(nsD::sTakeOutItemSteps),
    HOST_OVERLAY_VAR(nsD::sPushedSteps),
    HOST_OVERLAY_VAR(nsD::sAdmireCatchStepsGuard),
    HOST_OVERLAY_VAR(nsD::sFleaRemovedStepsGuard),
    HOST_OVERLAY_VAR(nsD::sHitByNetStepsGuard),
    HOST_OVERLAY_VAR(nsD::sChatOutcomes),
    HOST_OVERLAY_VAR(nsD::sLeaveHouseSteps),
    HOST_OVERLAY_VAR(nsD::sBirthdayInviteStepsGuard),
    HOST_OVERLAY_VAR(nsD::sRandomRouteTypes),
    HOST_OVERLAY_VAR(nsD::data_ov068_0226f870),
    HOST_OVERLAY_VAR(ns_02265d34::sFieldVillagerProfile),
    HOST_OVERLAY_VAR(nsD::sChatDurations),
    HOST_OVERLAY_VAR(nsD::sLeaveHouseStepsGuard),
    HOST_OVERLAY_VAR(nsD::sHitTalkSteps),
    HOST_OVERLAY_VAR(nsD::sPitfallSteps),
    HOST_OVERLAY_VAR(nsD::sApproachAnimFx),
    HOST_OVERLAY_VAR(nsD::sAdmireCatchSteps),
    HOST_OVERLAY_VAR(nsD::sPitfallClimbOutStepsGuard),
    HOST_OVERLAY_VAR(nsD::sInHouseSteps),
    HOST_OVERLAY_VAR(nsD::sSimCatchClassWeights),
    HOST_OVERLAY_VAR(nsD::sFleaRemovedSteps),
    HOST_OVERLAY_VAR(nsD::sPushTalkStepsGuard),
    HOST_OVERLAY_VAR(nsD::sChatClothesMoods),
    HOST_OVERLAY_VAR(nsD::sPitfallStepsGuard),
    HOST_OVERLAY_VAR(nsD::sPushedStepsGuard),
    HOST_OVERLAY_VAR(nsD::sFaceTalkerSteps),
    HOST_OVERLAY_VAR(nsD::sTalkFacingArc),
    HOST_OVERLAY_VAR(nsD::sFleaRemovedHoldFrames),
    HOST_OVERLAY_VARS_END
};
