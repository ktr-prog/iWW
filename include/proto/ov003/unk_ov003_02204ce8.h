#ifndef PROTO_PROTO_OV003_UNK_OV003_02204CE8_H
#define PROTO_PROTO_OV003_UNK_OV003_02204CE8_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "player/PlayerActor.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerActor_TestSlotFlag9
BOOL PlayerActor_TestSlotFlag9(s32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsLocalReleaseWaiting
s32 PlayerActor_IsLocalReleaseWaiting();
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetLocalShownItem
u16 PlayerActor_GetLocalShownItem();
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalReleaseCatch
s32 PlayerActor_LocalReleaseCatch(u8 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestDoorApproach
s32 PlayerActor_LocalRequestDoorApproach(s32 *a, s32 *b, s16 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestDoorEnter
s32 PlayerActor_LocalRequestDoorEnter(u32 a, s32 *b, s32 *c, s32 d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestDoorExit
s32 PlayerActor_LocalRequestDoorExit();
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestMailboxWaitOrClose
s32 PlayerActor_LocalRequestMailboxWaitOrClose(s32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalFaint
s32 PlayerActor_LocalFaint(s32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalBeeSting
s32 PlayerActor_LocalBeeSting();
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestAct11
s32 PlayerActor_LocalRequestAct11();
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestThrowBottle
s32 PlayerActor_LocalRequestThrowBottle();
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetWatchMode
s32 PlayerActor_SetWatchMode(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalEndWatch
s32 PlayerActor_LocalEndWatch();
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestReleaseCreature
s32 PlayerActor_LocalRequestReleaseCreature(u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ConfirmReleaseCreature
BOOL PlayerActor_ConfirmReleaseCreature();
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalPlayAnim99
void PlayerActor_LocalPlayAnim99();
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalHoldsNet
BOOL PlayerActor_LocalHoldsNet();
#endif
#ifndef PROTO_LOCAL_PlayerActor_ReleaseCreatureSetNetItem
void PlayerActor_ReleaseCreatureSetNetItem(u8 *p, s32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ReleaseCreatureGetNetItem
void PlayerActor_ReleaseCreatureGetNetItem(u8 *p, u16 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ReleaseCreatureSetNetState
void PlayerActor_ReleaseCreatureSetNetState(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ReleaseCreatureGetNetState
u8 PlayerActor_ReleaseCreatureGetNetState(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_Act11SetArgs
void PlayerActor_Act11SetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetPluck
void PlayerActor_NetPluck();
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorApproachSetNetData
void PlayerActor_DoorApproachSetNetData(u8 *p, s32 a, s32 b, s16 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorApproachGetNetData
void PlayerActor_DoorApproachGetNetData(u8 *p, s32 *a, s32 *b, s16 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorEnterSetNetData
void PlayerActor_DoorEnterSetNetData(u8 *p, u32 a, s32 b, s32 c, s16 e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorEnterGetNetData
void PlayerActor_DoorEnterGetNetData(u8 *p, u8 *a, s32 *b, s32 *c, u16 *e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_MainDoorEntered
void PlayerActor_MainDoorEntered();
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorExitSetNetData
void PlayerActor_DoorExitSetNetData(u8 *p, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DoorExitGetNetData
void PlayerActor_DoorExitGetNetData(u8 *p, u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_MainAct3C
void PlayerActor_MainAct3C();
#endif
#ifndef PROTO_LOCAL_PlayerActor_StowItemSetNetData
void PlayerActor_StowItemSetNetData(u8 *p, u32 a, u32 b, u32 c, s16 d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StowItemGetNetData
void PlayerActor_StowItemGetNetData(u8 *p, u8 *a, s32 *b, s32 *c, s16 *d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StowUmbrellaSetNetData
void PlayerActor_StowUmbrellaSetNetData(u8 *p, u32 id, s32 x, s32 y, s32 h);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StowUmbrellaGetNetData
void PlayerActor_StowUmbrellaGetNetData(u8 *p, u8 *a, s32 *b, s32 *c, s16 *d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_UmbrellaSpinInitWork
void PlayerActor_UmbrellaSpinInitWork(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeSwingSetArgs
void PlayerActor_AxeSwingSetArgs(s32 *p, s32 a, s32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeSwingSetNetData
void PlayerActor_AxeSwingSetNetData(u8 *p, s32 a, s32 b, u8 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeSwingGetNetData
void PlayerActor_AxeSwingGetNetData(u8 *p, s32 *a, s32 *b, u8 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeStrikeSetArgs
void PlayerActor_AxeStrikeSetArgs(u8 *d, u32 x, u32 y, s32 *s);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeStrikeSetWork
void PlayerActor_AxeStrikeSetWork(u8 *d, u32 x, u32 y, s32 *s);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeStrikeSetNetData
void PlayerActor_AxeStrikeSetNetData(u8 *d, u8 a, u8 b, u8 c, u8 e, u8 f);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeStrikeGetNetData
void PlayerActor_AxeStrikeGetNetData(u8 *s, u8 *a, u8 *b, u8 *c, u8 *d, u8 *e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeBreakSetNetData
void PlayerActor_AxeBreakSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_AxeBreakGetNetData
void PlayerActor_AxeBreakGetNetData(u8 *src, u8 *dst);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishCastSetNetData
void PlayerActor_FishCastSetNetData(u8 *p, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishCastGetNetData
void PlayerActor_FishCastGetNetData(u8 *p, s32 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishReelInSetArgs
void PlayerActor_FishReelInSetArgs(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishReelInSetWork
void PlayerActor_FishReelInSetWork(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishReelInSetNetData
void PlayerActor_FishReelInSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishReelInGetNetData
void PlayerActor_FishReelInGetNetData(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishShowCatchSetNetData
void PlayerActor_FishShowCatchSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishShowCatchGetNetData
void PlayerActor_FishShowCatchGetNetData(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishStoreSetNetState
void PlayerActor_FishStoreSetNetState(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishStoreGetNetState
u32 PlayerActor_FishStoreGetNetState(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectShowCatchSetNetData
void PlayerActor_InsectShowCatchSetNetData(u8 *p, u32 a, u32 b, u32 c, u8 d, s16 e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectShowCatchSetNetState
void PlayerActor_InsectShowCatchSetNetState(u8 *p, u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectShowCatchSetNetAngle
void PlayerActor_InsectShowCatchSetNetAngle(void *p, s32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectShowCatchGetNetData
void PlayerActor_InsectShowCatchGetNetData(u8 *p, u8 *a, u8 *b, u8 *c, u8 *d, u16 *e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectShowCatchGetNetState
u32 PlayerActor_InsectShowCatchGetNetState(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectShowCatchGetNetAngle
u32 PlayerActor_InsectShowCatchGetNetAngle(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectStoreSetNetData
void PlayerActor_InsectStoreSetNetData(u8 *p, u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectStoreSetNetState
void PlayerActor_InsectStoreSetNetState(u8 *p, u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectStoreSetNetAngle
void PlayerActor_InsectStoreSetNetAngle(u8 *p, u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectStoreGetNetData
void PlayerActor_InsectStoreGetNetData(u8 *p, u8 *a, u8 *b, u16 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectStoreGetNetState
u32 PlayerActor_InsectStoreGetNetState(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InsectStoreGetNetAngle
u32 PlayerActor_InsectStoreGetNetAngle(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ShovelReadySetArgs
void PlayerActor_ShovelReadySetArgs(u8 *p, u8 a, u8 b, u32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ShovelReadySetNetData
void PlayerActor_ShovelReadySetNetData(u8 *p, u8 a, u8 b, u32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ShovelReadyGetNetData
void PlayerActor_ShovelReadyGetNetData(u8 *src, u8 *a, u8 *b, u8 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ShovelStrikeSetNetData
void PlayerActor_ShovelStrikeSetNetData(u8 *d, u8 a, u8 b, u8 c, u8 e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ShovelStrikeGetNetData
void PlayerActor_ShovelStrikeGetNetData(u8 *s, u8 *a, u8 *b, u8 *c, u8 *d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DigUpItemGetNetData
void PlayerActor_DigUpItemGetNetData(u8 *p, s32 *xy, u16 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DugItemStoreSetNetData
void PlayerActor_DugItemStoreSetNetData(u8 *s, u8 a, u8 b, u8 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DugItemStoreGetNetData
void PlayerActor_DugItemStoreGetNetData(u8 *s, u8 *a, u8 *b, u8 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_BuryItemSetNetData
void PlayerActor_BuryItemSetNetData(u8 *s, u32 v, u8 a, u8 b, u8 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetBuryItem
void PlayerActor_NetBuryItem();
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetFillHole
void PlayerActor_NetFillHole();
#endif
#ifndef PROTO_LOCAL_PlayerActor_WateringCanSetNetData
void PlayerActor_WateringCanSetNetData(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_WateringCanGetNetData
void PlayerActor_WateringCanGetNetData(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetSlingshotWatch
void PlayerActor_NetSlingshotWatch();
#endif
#ifndef PROTO_LOCAL_PlayerActor_TreeShakeSetArgs
void PlayerActor_TreeShakeSetArgs(void *p, s32 a, s32 b, u8 c, u8 d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_TreeShakeSetNetData
void PlayerActor_TreeShakeSetNetData(u8 *p, s32 a, s32 b, u8 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_TreeShakeGetNetData
void PlayerActor_TreeShakeGetNetData(u8 *p, s32 *a, s32 *b, u8 *c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_TreeShakeReleaseSetArgs
void PlayerActor_TreeShakeReleaseSetArgs(void *p, s32 a, s32 b, u8 c, u8 d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_TreeShakeReleaseSetWork
void PlayerActor_TreeShakeReleaseSetWork(void *p, s16 a, s32 b, s32 c, u8 d, u8 e);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetTreeShakeRelease
void PlayerActor_NetTreeShakeRelease();
#endif
#ifndef PROTO_LOCAL_PlayerActor_PitfallFallSetNetData
void PlayerActor_PitfallFallSetNetData(u8 *p, u8 a, u8 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_PitfallFallGetNetData
void PlayerActor_PitfallFallGetNetData(u8 *s, u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetBeeSting
void PlayerActor_NetBeeSting();
#endif
#ifndef PROTO_LOCAL_data_ov003_02230af0
extern s32 data_ov003_02230af0;
#endif
#ifndef PROTO_LOCAL_sFishEscapeSpeed
extern s32 sFishEscapeSpeed;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230ae8
extern s32 data_ov003_02230ae8;
#endif
#ifndef PROTO_LOCAL_sFishCastFarDist
extern s32 sFishCastFarDist;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230ae0
extern s32 data_ov003_02230ae0;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230adc
extern s32 data_ov003_02230adc;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230ad8
extern s32 data_ov003_02230ad8;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230ad4
extern s32 data_ov003_02230ad4;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230ad0
extern s32 data_ov003_02230ad0;
#endif
#ifndef PROTO_LOCAL_sFishCastNearDist
extern s32 sFishCastNearDist;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230ac8
extern s32 data_ov003_02230ac8;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230ac4
extern s32 data_ov003_02230ac4;
#endif
#ifndef PROTO_LOCAL_data_ov003_02230ac0
extern s32 data_ov003_02230ac0;
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishReleaseSetNetData
void PlayerActor_FishReleaseSetNetData(u8 *p, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FishReleaseGetNetData
void PlayerActor_FishReleaseGetNetData(u8 *src, u8 *a, u8 *b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerActor_GetTrackTarget
VecFx32 *PlayerActor_GetTrackTarget(u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FieldUseTool
BOOL PlayerActor_FieldUseTool(PlayerActor *self);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FieldStartToolAction
BOOL PlayerActor_FieldStartToolAction(PlayerActor *self, s32 mode, VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_PlayerActor_FieldInteractAt
BOOL PlayerActor_FieldInteractAt(PlayerActor *self, s32 a);
#endif
}
#endif

#endif
