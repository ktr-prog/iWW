#ifndef PROTO_PROTO_MAIN_UNK_020850E0_H
#define PROTO_PROTO_MAIN_UNK_020850E0_H


#include "types.h"
struct Unk_02085490_Pt;
#ifndef __cplusplus
typedef struct Unk_02085490_Pt Unk_02085490_Pt;
#endif
#ifdef __cplusplus
#include "save/ContestRecord.h"
#include "save/VillagerData.h"
#include "town/BlockMap.h"
#include "town/KatieVisitState.h"
#include "town/PeteFallState.h"
#include "town/ResettiVisitFlag.h"
#include "town/ShopClosingTime.h"
#include "town/TownSessionState.h"
#include "town/TownTravelState.h"
#include "town/VisitorSpawnFlags.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Contest_GetCatchSize
s32 Contest_GetCatchSize(u16 *p);
#endif
#ifndef PROTO_LOCAL_Contest_GetFlowerKind
s32 Contest_GetFlowerKind(u32 *out, u16 *p);
#endif
#ifndef PROTO_LOCAL_CountSetBits
s32 CountSetBits(u32 v);
#endif
#ifndef PROTO_LOCAL_Contest_IsNextToGroundAttr4
s32 Contest_IsNextToGroundAttr4(s32 *pos);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ContestRecord_SetItem
void ContestRecord_SetItem(ContestRecord *o, u16 *in);
#endif
#ifndef PROTO_LOCAL_ContestRecord_GetItem
void ContestRecord_GetItem(u16 *out, ContestRecord *o);
#endif
#ifndef PROTO_LOCAL_ContestRecord_BeginContestDay
void ContestRecord_BeginContestDay(ContestRecord *self, u32 mode);
#endif
#ifndef PROTO_LOCAL_ContestRecord_BeginFestival
void ContestRecord_BeginFestival(ContestRecord *self, u32 mode);
#endif
#ifndef PROTO_LOCAL_ContestRecord_ScoreVillagerGarden
s32 ContestRecord_ScoreVillagerGarden(VillagerData *obj, BlockMap *grid);
#endif
#ifndef PROTO_LOCAL_ContestRecord_ScorePlayerGarden
s32 ContestRecord_ScorePlayerGarden(ContestRecord *self, BlockMap *grid);
#endif
#ifndef PROTO_LOCAL_ContestRecord_JudgeGardens
void ContestRecord_JudgeGardens(ContestRecord *self);
#endif
#ifndef PROTO_LOCAL_TownSessionState_Reset
void TownSessionState_Reset(TownSessionState *self);
#endif
#ifndef PROTO_LOCAL_TownSessionState_TestFlag
BOOL TownSessionState_TestFlag(TownSessionState *self, u32 bit);
#endif
#ifndef PROTO_LOCAL_TownSessionState_SetFlag
void TownSessionState_SetFlag(TownSessionState *self, u32 bit);
#endif
#ifndef PROTO_LOCAL_TownSessionState_ClearFlag
void TownSessionState_ClearFlag(TownSessionState *self, u32 bit);
#endif
#ifndef PROTO_LOCAL_TownSessionState_GetClosingTime
ShopClosingTime *TownSessionState_GetClosingTime(TownSessionState *p);
#endif
#ifndef PROTO_LOCAL_TownSessionState_GetTravelState
TownTravelState *TownSessionState_GetTravelState(TownSessionState *p);
#endif
#ifndef PROTO_LOCAL_TownSessionState_GetResettiFlag
ResettiVisitFlag *TownSessionState_GetResettiFlag(TownSessionState *p);
#endif
#ifndef PROTO_LOCAL_TownSessionState_GetKatieState
KatieVisitState *TownSessionState_GetKatieState(TownSessionState *p);
#endif
#ifndef PROTO_LOCAL_TownSessionState_GetPeteFall
PeteFallState *TownSessionState_GetPeteFall(TownSessionState *p);
#endif
#ifndef PROTO_LOCAL_TownSessionState_GetVisitorFlags
VisitorSpawnFlags *TownSessionState_GetVisitorFlags(TownSessionState *p);
#endif
#ifndef PROTO_LOCAL_TownSessionState_GetVisitorPos
u8 *TownSessionState_GetVisitorPos(TownSessionState *p);
#endif
#ifndef PROTO_LOCAL_TownSessionState_CheckTortimerReward
void TownSessionState_CheckTortimerReward(TownSessionState *self);
#endif
#ifndef PROTO_LOCAL_TownSessionState_Get
TownSessionState *TownSessionState_Get();
#endif
}
#ifndef PROTO_LOCAL_sVillagerGardenOffsets
extern Unk_02085490_Pt sVillagerGardenOffsets[14];
#endif
#ifndef PROTO_LOCAL_sGardenNeighbourOffsets
extern Unk_02085490_Pt sGardenNeighbourOffsets[8];
#endif
#ifndef PROTO_LOCAL_gTownSessionState
extern TownSessionState gTownSessionState;
#endif
#endif

#endif
