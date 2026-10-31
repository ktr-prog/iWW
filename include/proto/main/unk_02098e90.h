#ifndef PROTO_PROTO_MAIN_UNK_02098E90_H
#define PROTO_PROTO_MAIN_UNK_02098E90_H


#include "types.h"
#include "item/PocketMatches.h"
#include "sys/ClockDateTime.h"
struct ErrandKindSetup;
#ifndef __cplusplus
typedef struct ErrandKindSetup ErrandKindSetup;
#endif
#ifdef __cplusplus
#include "item/Letter.h"
#include "npc/ErrandRecord.h"
#include "npc/VillagerId.h"
#include "npc/VillagerPlan.h"
#include "player/PlayerErrands.h"
#include "player/PlayerId.h"
#include "talk/MsgString.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TopicWord_PickRandom
char *TopicWord_PickRandom(u32 *out, s32 idx);
#endif
#ifndef PROTO_LOCAL_TrendScores_Construct
void *TrendScores_Construct(void *p);
#endif
#ifndef PROTO_LOCAL_TrendScores_Destruct
void TrendScores_Destruct();
#endif
#ifndef PROTO_LOCAL_TrendScores_Clear
void TrendScores_Clear(void *p);
#endif
#ifndef PROTO_LOCAL_TrendScores_Copy
void TrendScores_Copy(void *p, void *q);
#endif
#ifndef PROTO_LOCAL_Trend_IsValid
BOOL Trend_IsValid(u32 x);
#endif
#ifndef PROTO_LOCAL_PlanState_GetGroup
s32 PlanState_GetGroup(u32 x);
#endif
#ifndef PROTO_LOCAL_PlanState_GetGroupIndex
s32 PlanState_GetGroupIndex(u8 *out, s32 x);
#endif
#ifndef PROTO_LOCAL_Trend_GetToolItem
void Trend_GetToolItem(u16 *out, s32 idx);
#endif
#ifndef PROTO_LOCAL_Errand_IsValidKind
BOOL Errand_IsValidKind(u32 x);
#endif
#ifndef PROTO_LOCAL_Errand_IsValidClass
BOOL Errand_IsValidClass(u32 x);
#endif
#ifndef PROTO_LOCAL_Errand_GetClass
s32 Errand_GetClass(u32 x);
#endif
#ifndef PROTO_LOCAL_Errand_GetClassIndex
BOOL Errand_GetClassIndex(s32 *out, s32 x);
#endif
#ifndef PROTO_LOCAL_Errand_IsValidGroup
BOOL Errand_IsValidGroup(u32 x);
#endif
#ifndef PROTO_LOCAL_Errand_GetGroup
s32 Errand_GetGroup(u32 x);
#endif
#ifndef PROTO_LOCAL_Errand_GetGroupIndex
BOOL Errand_GetGroupIndex(s32 *out, s32 x);
#endif
#ifndef PROTO_LOCAL_Errand_GetSlotIndex
s32 Errand_GetSlotIndex(u32 x);
#endif
#ifndef PROTO_LOCAL_Errand_GetSubGroup
s32 Errand_GetSubGroup(u32 x);
#endif
#ifndef PROTO_LOCAL_PlanErrand_GetStepCount
s32 PlanErrand_GetStepCount(s32 x);
#endif
#ifndef PROTO_LOCAL_FossilGroup_ToIndex
s32 FossilGroup_ToIndex(u32 v);
#endif
#ifndef PROTO_LOCAL_FossilGroup_PickMissing
u8 FossilGroup_PickMissing(u16 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_FossilGroup_GetItem
void FossilGroup_GetItem(u16 *out, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Furniture_ScoreAttribute
s32 Furniture_ScoreAttribute(u16 *self, u32 kind, s32 val);
#endif
#ifndef PROTO_LOCAL_VillagerPlanBlock_RollTrend
s32 VillagerPlanBlock_RollTrend(void *p, const u8 *trend, s32 flag);
#endif
#ifndef PROTO_LOCAL_Errand_CanOfferInPlanState
BOOL Errand_CanOfferInPlanState(s32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_IsPastStepLimit
s32 PlayerErrandSlot_IsPastStepLimit(void *self, s32 kind);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_IsStepDone
s32 PlayerErrandSlot_IsStepDone(void *self);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_SetPresentReaction
void PlayerErrandSlot_SetPresentReaction(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_GetPresentReaction
u8 *PlayerErrandSlot_GetPresentReaction(u8 *p);
#endif
#ifndef PROTO_LOCAL_ErrandSetup_RandomShirt
BOOL ErrandSetup_RandomShirt(void *p);
#endif
#ifndef PROTO_LOCAL_ErrandSetup_LetterBundle
BOOL ErrandSetup_LetterBundle(void *p);
#endif
#ifndef PROTO_LOCAL_ErrandSetup_FurnitureParcel
BOOL ErrandSetup_FurnitureParcel(void *p);
#endif
#ifndef PROTO_LOCAL_ErrandSetup_Carpet
BOOL ErrandSetup_Carpet(void *p);
#endif
#ifndef PROTO_LOCAL_ErrandSetup_WateringCan
BOOL ErrandSetup_WateringCan(void *p);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_CountPending
u8 ParcelErrand_CountPending(void *unused, s32 v);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_CountPendingRecipients
u8 ParcelErrand_CountPendingRecipients(void *unused, s32 v);
#endif
#ifndef PROTO_LOCAL_Arbeit_OnLetterWritten
void Arbeit_OnLetterWritten(void *p);
#endif
#ifndef PROTO_LOCAL_Arbeit_NotifyLetterWritten
void Arbeit_NotifyLetterWritten();
#endif
#ifndef PROTO_LOCAL_Threshold_FindIndex
s32 Threshold_FindIndex(u32 v, const u8 *tbl, s32 n);
#endif
#ifndef PROTO_LOCAL_InsectSpawn_GetWeightClass
s32 InsectSpawn_GetWeightClass(u32 v);
#endif
#ifndef PROTO_LOCAL_FishSpawn_GetWeightClass
s32 FishSpawn_GetWeightClass(u32 v);
#endif
#ifndef PROTO_LOCAL_Quat_Normalize
void Quat_Normalize(s32 *q);
#endif
#ifndef PROTO_LOCAL_Quat_ToMtx33
void Quat_ToMtx33(s32 *a, s32 *m);
#endif
#ifndef PROTO_LOCAL_Quat_ToMtx43
void Quat_ToMtx43(s32 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_Quat_Mul
void Quat_Mul(s32 *a, s32 *b, s32 *out);
#endif
#ifndef PROTO_LOCAL_Main_EmptyInitStub
void Main_EmptyInitStub();
#endif
#ifndef PROTO_LOCAL_Inventory_FindEmptyLetter
s32 Inventory_FindEmptyLetter();
#endif
#ifndef PROTO_LOCAL_Item_PickRandomPresent
u16 Item_PickRandomPresent();
#endif
#ifndef PROTO_LOCAL_Pocket_SetFoundItem
void Pocket_SetFoundItem(u16 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_Pocket_AddFoundItem
BOOL Pocket_AddFoundItem(u16 *a);
#endif
#ifndef PROTO_LOCAL_Pocket_SetItem
void Pocket_SetItem(u16 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Pocket_RemoveItem
void Pocket_RemoveItem(s32 c);
#endif
#ifndef PROTO_LOCAL_Pocket_GetItem
u16 Pocket_GetItem(s32 i);
#endif
#ifndef PROTO_LOCAL_Pocket_AddItem
BOOL Pocket_AddItem(u16 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_Pocket_FindEmpty
s32 Pocket_FindEmpty();
#endif
#ifndef PROTO_LOCAL_Pocket_CountKind
s32 Pocket_CountKind(PocketMatches *self, s32 v);
#endif
#ifndef PROTO_LOCAL_Pocket_CountMatching
s32 Pocket_CountMatching(PocketMatches *out, s32 (*fn)(u16 *));
#endif
#ifndef PROTO_LOCAL_Pocket_FindItem
s32 Pocket_FindItem(u16 *a);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_VillagerPlan_GetPlanTime
ClockDateTime *VillagerPlan_GetPlanTime(VillagerPlan *p);
#endif
#ifndef PROTO_LOCAL_VillagerPlan_GetStateDate
ClockDateTime *VillagerPlan_GetStateDate(VillagerPlan *p);
#endif
#ifndef PROTO_LOCAL_ErrandRecord_GetTime
ClockDateTime *ErrandRecord_GetTime(ErrandRecord *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_Construct
void *PlanErrand_Construct(PlanErrand *self);
#endif
#ifndef PROTO_LOCAL_PlanErrand_Destruct
void *PlanErrand_Destruct(PlanErrand *self);
#endif
#ifndef PROTO_LOCAL_PlanErrand_Clear
void PlanErrand_Clear(PlanErrand *self);
#endif
#ifndef PROTO_LOCAL_PlanErrand_SetKind
void PlanErrand_SetKind(PlanErrand *p, s32 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_PlanErrand_Begin
void PlanErrand_Begin(PlanErrand *self, s32 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_PlanErrand_ResetProgress
void PlanErrand_ResetProgress(PlanErrand *self);
#endif
#ifndef PROTO_LOCAL_PlanErrand_Assign
void PlanErrand_Assign(PlanErrand *self, s32 a1, u16 *p, void *obj, u8 flag);
#endif
#ifndef PROTO_LOCAL_PlanErrand_MarkReady
void PlanErrand_MarkReady(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_GetRecord
ErrandRecord *PlanErrand_GetRecord(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_GetStep
u8 PlanErrand_GetStep(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_SetStep
void PlanErrand_SetStep(PlanErrand *p, u8 v);
#endif
#ifndef PROTO_LOCAL_PlanErrand_GetPlayer
PlayerId *PlanErrand_GetPlayer(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_GetTime
ClockDateTime *PlanErrand_GetTime(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_GetShownItem
u16 *PlanErrand_GetShownItem(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_GetFossilGroup
u8 PlanErrand_GetFossilGroup(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_SetFossilGroup
void PlanErrand_SetFossilGroup(PlanErrand *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlanErrand_SetFlag
void PlanErrand_SetFlag(PlanErrand *p, s32 i);
#endif
#ifndef PROTO_LOCAL_PlanErrand_TestFlag
BOOL PlanErrand_TestFlag(PlanErrand *p, u32 i);
#endif
#ifndef PROTO_LOCAL_PlanErrand_ClearFlags
void PlanErrand_ClearFlags(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_GetCount
u8 PlanErrand_GetCount(PlanErrand *p);
#endif
#ifndef PROTO_LOCAL_PlanErrand_AddCount
u8 PlanErrand_AddCount(PlanErrand *p, s32 n);
#endif
#ifndef PROTO_LOCAL_PlanErrand_IsFurnitureGoalMet
BOOL PlanErrand_IsFurnitureGoalMet(PlanErrand *self);
#endif
#ifndef PROTO_LOCAL_VillagerPlanBlock_Construct
VillagerPlanBlock *VillagerPlanBlock_Construct(VillagerPlanBlock *p);
#endif
#ifndef PROTO_LOCAL_VillagerPlanBlock_Destruct
VillagerPlanBlock *VillagerPlanBlock_Destruct(VillagerPlanBlock *p);
#endif
#ifndef PROTO_LOCAL_VillagerPlanBlock_Clear
void VillagerPlanBlock_Clear(VillagerPlanBlock *p);
#endif
#ifndef PROTO_LOCAL_VillagerPlanBlock_GetPlan
VillagerPlan *VillagerPlanBlock_GetPlan(void *p);
#endif
#ifndef PROTO_LOCAL_VillagerPlanBlock_GetErrand
PlanErrand *VillagerPlanBlock_GetErrand(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_Construct
PlayerErrandSlot *PlayerErrandSlot_Construct(PlayerErrandSlot *self);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_Destruct
PlayerErrandSlot *PlayerErrandSlot_Destruct(PlayerErrandSlot *self);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_Clear
void PlayerErrandSlot_Clear(PlayerErrandSlot *self);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_Start
BOOL PlayerErrandSlot_Start(PlayerErrandSlot *self, s32 kind, VillagerId *r6, VillagerId *r3);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_GetRecord
ErrandRecord *PlayerErrandSlot_GetRecord(PlayerErrandSlot *p);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_GetVillager
VillagerIdCtorDtor *PlayerErrandSlot_GetVillager(PlayerErrandSlot *p, s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlot_ComposeLetter
void PlayerErrandSlot_ComposeLetter(PlayerErrandSlot *self, void *arg);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_Clear
void ParcelErrand_Clear(ParcelErrand *p);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_PickRecipient
s32 ParcelErrand_PickRecipient(ParcelErrand *z, s32 m);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_RemoveRecipient
void ParcelErrand_RemoveRecipient(ParcelErrand *z, s32 i);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_Start
void ParcelErrand_Start(ParcelErrand *z);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_GetRecord
ErrandRecord *ParcelErrand_GetRecord(ParcelErrand *z);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_GetRecipientName
BOOL ParcelErrand_GetRecipientName(ParcelErrand *z, MsgString *v);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_NextRecipient
BOOL ParcelErrand_NextRecipient(ParcelErrand *z);
#endif
#ifndef PROTO_LOCAL_ParcelErrand_IsFor
BOOL ParcelErrand_IsFor(ParcelErrand *z, u16 *p);
#endif
#ifndef PROTO_LOCAL_HouseVisitInvite_Clear
void HouseVisitInvite_Clear(HouseVisitInvite *x);
#endif
#ifndef PROTO_LOCAL_HouseVisitInvite_IsFrom
BOOL HouseVisitInvite_IsFrom(HouseVisitInvite *x, VillagerId *p);
#endif
#ifndef PROTO_LOCAL_HouseVisitInvite_Set
void HouseVisitInvite_Set(HouseVisitInvite *x, VillagerId *r, void *src);
#endif
#ifndef PROTO_LOCAL_PlayerErrands_Clear
void PlayerErrands_Clear(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_PlayerErrands_GetSlot
PlayerErrandSlot *PlayerErrands_GetSlot(PlayerErrands *m, s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerErrandSlots_FindByVillager
PlayerErrandSlot *PlayerErrandSlots_FindByVillager(PlayerErrandSlot *arr, VillagerId *p, s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerErrands_GetDeliveryRecipientName
BOOL PlayerErrands_GetDeliveryRecipientName(PlayerErrands *m, MsgString *a, u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerErrands_ClearJobVillagers
void PlayerErrands_ClearJobVillagers(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_PlayerErrands_IsJobActive
BOOL PlayerErrands_IsJobActive(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_Start
void Arbeit_Start(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_SetOnDuty
void Arbeit_SetOnDuty(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_ClearOnDuty
void Arbeit_ClearOnDuty(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_IsOnDuty
BOOL Arbeit_IsOnDuty(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_StartPlanting
void Arbeit_StartPlanting(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_StartGreetings
void Arbeit_StartGreetings(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_StartFurnitureDelivery
void Arbeit_StartFurnitureDelivery(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_StartLetterTask
void Arbeit_StartLetterTask(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_OnLetterSent
BOOL Arbeit_OnLetterSent(PlayerErrands *m, void *p);
#endif
#ifndef PROTO_LOCAL_Arbeit_StartCarpetDelivery
void Arbeit_StartCarpetDelivery(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_StartWateringCanDelivery
void Arbeit_StartWateringCanDelivery(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_StartBbsTask
void Arbeit_StartBbsTask(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_OnBbsPosted
void Arbeit_OnBbsPosted(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_Finish
void Arbeit_Finish(PlayerErrands *m);
#endif
#ifndef PROTO_LOCAL_Arbeit_IsLetterRecipient
BOOL Arbeit_IsLetterRecipient(PlayerErrands *m, VillagerId *r);
#endif
#ifndef PROTO_LOCAL_Inventory_GetEmptyLetter
Letter *Inventory_GetEmptyLetter();
#endif
#ifndef PROTO_LOCAL_Player_GetDeliveryRecipientName
BOOL Player_GetDeliveryRecipientName(MsgString *a, u16 *b);
#endif
}
#ifndef PROTO_LOCAL_data_020e2190
extern void *data_020e2190[2];
#endif
#ifndef PROTO_LOCAL_data_020e21a0
extern void *data_020e21a0[2];
#endif
#ifndef PROTO_LOCAL_data_020e21c0
extern char data_020e21c0[9];
#endif
#ifndef PROTO_LOCAL_data_020e218c
extern u8 data_020e218c[1];
#endif
#ifndef PROTO_LOCAL_data_020e21b8
extern void *data_020e21b8[2];
#endif
#ifndef PROTO_LOCAL_data_020e21f0
extern char data_020e21f0[10];
#endif
#ifndef PROTO_LOCAL_data_020e21d8
extern char data_020e21d8[9];
#endif
#ifndef PROTO_LOCAL_data_020e21e4
extern char data_020e21e4[10];
#endif
#ifndef PROTO_LOCAL_data_020e21b0
extern char data_020e21b0[8];
#endif
#ifndef PROTO_LOCAL_data_020e21a8
extern void *data_020e21a8[2];
#endif
#ifndef PROTO_LOCAL_data_020e21cc
extern char data_020e21cc[9];
#endif
#ifndef PROTO_LOCAL_data_020e2198
extern void *data_020e2198[2];
#endif
#ifndef PROTO_LOCAL_sErrandKindSetups
extern ErrandKindSetup sErrandKindSetups[10];
#endif
#endif

#endif
