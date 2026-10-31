#ifndef PROTO_PROTO_OV068_UNK_OV068_0225F1A0_H
#define PROTO_PROTO_OV068_UNK_OV068_0225F1A0_H


#include "types.h"
struct FieldVillagerAiState;
struct FieldVillagerFocusRange;
#ifndef __cplusplus
typedef struct FieldVillagerAiState FieldVillagerAiState;
typedef struct FieldVillagerFocusRange FieldVillagerFocusRange;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/VecFx32.h"
#include "save/Pattern.h"
class FieldVillager;
class FieldVillagerAi;
class FieldVillagerAiStates;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sReactionStepsGuard
extern u32 sReactionStepsGuard;
#endif
#ifndef PROTO_LOCAL_sHitTalkStepsGuard
extern u32 sHitTalkStepsGuard;
#endif
#ifndef PROTO_LOCAL_sChatStepsGuard
extern u32 sChatStepsGuard;
#endif
#ifndef PROTO_LOCAL_sTalkStepsGuard
extern u32 sTalkStepsGuard;
#endif
#ifndef PROTO_LOCAL_sApproachStepsGuard
extern u32 sApproachStepsGuard;
#endif
#ifndef PROTO_LOCAL_sFaceTalkerStepsGuard
extern u32 sFaceTalkerStepsGuard;
#endif
#ifndef PROTO_LOCAL_sTakeOutItemStepsGuard
extern u32 sTakeOutItemStepsGuard;
#endif
#ifndef PROTO_LOCAL_sAbsentStepsGuard
extern u32 sAbsentStepsGuard;
#endif
#ifndef PROTO_LOCAL_sInHouseStepsGuard
extern u32 sInHouseStepsGuard;
#endif
#ifndef PROTO_LOCAL_sSeePlayerArc
extern s16 sSeePlayerArc;
#endif
#ifndef PROTO_LOCAL_sPutAwayItemStepsGuard
extern u32 sPutAwayItemStepsGuard;
#endif
#ifndef PROTO_LOCAL_sGoInHouseStepsGuard
extern u32 sGoInHouseStepsGuard;
#endif
#ifndef PROTO_LOCAL_sChatOutcomesGuard
extern u32 sChatOutcomesGuard;
#endif
#ifndef PROTO_LOCAL_sAdmireCatchStepsGuard
extern u32 sAdmireCatchStepsGuard;
#endif
#ifndef PROTO_LOCAL_sFleaRemovedStepsGuard
extern u32 sFleaRemovedStepsGuard;
#endif
#ifndef PROTO_LOCAL_sHitByNetStepsGuard
extern u32 sHitByNetStepsGuard;
#endif
#ifndef PROTO_LOCAL_sBirthdayInviteStepsGuard
extern u32 sBirthdayInviteStepsGuard;
#endif
#ifndef PROTO_LOCAL_sLeaveHouseStepsGuard
extern u32 sLeaveHouseStepsGuard;
#endif
#ifndef PROTO_LOCAL_sPitfallClimbOutStepsGuard
extern u32 sPitfallClimbOutStepsGuard;
#endif
#ifndef PROTO_LOCAL_sPushTalkStepsGuard
extern u32 sPushTalkStepsGuard;
#endif
#ifndef PROTO_LOCAL_sPitfallStepsGuard
extern u32 sPitfallStepsGuard;
#endif
#ifndef PROTO_LOCAL_sPushedStepsGuard
extern u32 sPushedStepsGuard;
#endif
#ifndef PROTO_LOCAL_sTalkFacingArc
extern s16 sTalkFacingArc;
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_PathCrossesPlayerTalk
s32 FieldVillagerAi_PathCrossesPlayerTalk(void *self, void *a, void *b);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_IsNearPlayerTalkSpot
BOOL FieldVillagerAi_IsNearPlayerTalkSpot(void *self, void *v, s32 lim);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_IsPlayerShowingCatch
s32 FieldVillagerAi_IsPlayerShowingCatch(void *self);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_GetRelationLevel
s32 FieldVillagerAi_GetRelationLevel(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_GetPartnerRelationLevel
s32 FieldVillagerAi_GetPartnerRelationLevel(void *a, void *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_AddRelationByLevel
void FieldVillagerAi_AddRelationByLevel(void *a, void *r1, void *r2, const s8 *t);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_AddPartnerRelation
void FieldVillagerAi_AddPartnerRelation(void *a, void *o, const s8 *t);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_AddMood
void FieldVillagerAi_AddMood(void *a, void *o, s32 x, s32 y, u8 flag);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_AddRandomMood
void FieldVillagerAi_AddRandomMood(void *a, void *b, u8 *tbl, s32 n, u8 p5, u8 p6);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_OrderByFriendship
s32 FieldVillagerAi_OrderByFriendship(void *unused, void **a, void **b, void *c, void *d);
#endif
#ifndef PROTO_LOCAL_FieldVillager_StepToward
void FieldVillager_StepToward(s32 *p, s32 target, s32 a, s32 spd, s32 min);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sFieldVillagerAiTable
extern FieldVillagerAiState sFieldVillagerAiTable[0x18];
#endif
#ifndef PROTO_LOCAL_sFieldVillagerProfile
extern ActorProfile sFieldVillagerProfile;
#endif
#ifndef PROTO_LOCAL_FieldVillager_Create
FieldVillager *FieldVillager_Create();
#endif
#ifndef PROTO_LOCAL_FieldVillager_UpdateUmbrella
void FieldVillager_UpdateUmbrella(FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillager_CanSimulateCatch
s32 FieldVillager_CanSimulateCatch(FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillager_SimulateInsectCatch
void FieldVillager_SimulateInsectCatch(FieldVillager *o, u8 *b);
#endif
#ifndef PROTO_LOCAL_FieldVillager_SimulateFishCatch
void FieldVillager_SimulateFishCatch(FieldVillager *o, u8 *b);
#endif
#ifndef PROTO_LOCAL_FieldVillager_UpdateCatchSim
void FieldVillager_UpdateCatchSim(FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillager_StopEmotion
void FieldVillager_StopEmotion(FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillager_GetMood
u32 FieldVillager_GetMood(FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillager_GetTalkRepeat
void *FieldVillager_GetTalkRepeat(FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_Update
void FieldVillagerAi_Update(FieldVillagerAi *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_ChangeState
void FieldVillagerAi_ChangeState(FieldVillagerAi *self, FieldVillager *o, s32 idx);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_SetResumeState
void FieldVillagerAi_SetResumeState(FieldVillagerAi *self, s32 v);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_SaveResumeState
void FieldVillagerAi_SaveResumeState(FieldVillagerAi *self);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_ClearResumeState
void FieldVillagerAi_ClearResumeState(FieldVillagerAi *self);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_Resume
s32 FieldVillagerAi_Resume(FieldVillagerAi *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_CanSeePlayer
s32 FieldVillagerAi_CanSeePlayer(FieldVillagerAi *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_IsFreeIdle
s32 FieldVillagerAi_IsFreeIdle(FieldVillagerAi *self);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_StartCooldown
void FieldVillagerAi_StartCooldown(FieldVillagerAi *self);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_IsState
s32 FieldVillagerAi_IsState(FieldVillagerAi *self, s32 v);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_InitTimers
void FieldVillagerAi_InitTimers(FieldVillagerAi *self);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_EnterWander
s32 FieldVillagerAi_EnterWander(FieldVillagerAi *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillager_IsInRect
s32 FieldVillager_IsInRect(FieldVillagerFocusRange *r, VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_FieldVillager_IsNearCameraFocus
s32 FieldVillager_IsNearCameraFocus(FieldVillagerFocusRange *r, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_PickRandomRouteType
s32 FieldVillagerAi_PickRandomRouteType(FieldVillagerAi *self);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_StartRoute
void FieldVillagerAi_StartRoute(FieldVillagerAi *self, s32 a, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_ShouldGoHome
BOOL FieldVillagerAi_ShouldGoHome(void *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_IsAtHomeDoor
BOOL FieldVillagerAi_IsAtHomeDoor(FieldVillagerAiStates *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_DirCrossesPlayerTalk
BOOL FieldVillagerAi_DirCrossesPlayerTalk(void *self, void *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_HeadingCrossesPlayerTalk
s32 FieldVillagerAi_HeadingCrossesPlayerTalk(void *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_GetRouteTarget
BOOL FieldVillagerAi_GetRouteTarget(FieldVillagerAiStates *self, VecFx32 *out, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_HandleBlockedMove
BOOL FieldVillagerAi_HandleBlockedMove(void *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_FindChatPartner
void *FieldVillagerAi_FindChatPartner(void *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_TryStartChat
BOOL FieldVillagerAi_TryStartChat(FieldVillagerAiStates *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_CheckHeldItemChange
BOOL FieldVillagerAi_CheckHeldItemChange(FieldVillagerAiStates *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_IsBuriedPitfallAt
BOOL FieldVillagerAi_IsBuriedPitfallAt(void *self, Vec2 *v);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_TryFallInPitfall
BOOL FieldVillagerAi_TryFallInPitfall(void *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_WasHitByNet
s32 FieldVillagerAi_WasHitByNet(void *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_ShouldAdmireCatch
BOOL FieldVillagerAi_ShouldAdmireCatch(FieldVillagerAiStates *self, FieldVillager *o);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_AddRandomPairRelation
void FieldVillagerAi_AddRandomPairRelation(void *a, FieldVillager *unused, const s8 *t);
#endif
#ifndef PROTO_LOCAL_FieldVillagerAi_PickOtherAblePattern
Pattern *FieldVillagerAi_PickOtherAblePattern(void *unused, Pattern *x);
#endif
}
#endif

#endif
