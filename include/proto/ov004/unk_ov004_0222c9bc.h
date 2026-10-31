#ifndef PROTO_PROTO_OV004_UNK_OV004_0222C9BC_H
#define PROTO_PROTO_OV004_UNK_OV004_0222C9BC_H


#include "types.h"
#include "sys/ProcProfile.h"
struct PairFn;
#ifndef __cplusplus
typedef struct PairFn PairFn;
#endif
#ifdef __cplusplus
#include "game/FxVec3.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e638
extern void *data_ov004_0224e638[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e600
extern void *data_ov004_0224e600[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e610
extern void *data_ov004_0224e610[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e6d0
extern void *data_ov004_0224e6d0[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e670
extern void *data_ov004_0224e670[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e668
extern void *data_ov004_0224e668[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e680
extern void *data_ov004_0224e680[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e6a0
extern void *data_ov004_0224e6a0[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e5f8
extern void *data_ov004_0224e5f8[2];
#endif
#ifndef PROTO_LOCAL_MuseumAquarium_Create
void *MuseumAquarium_Create();
#endif
#ifndef PROTO_LOCAL_Aquarium_StepX
void Aquarium_StepX(s32 *p, s32 a, u32 ang);
#endif
#ifndef PROTO_LOCAL_Aquarium_StepZ
void Aquarium_StepZ(s32 *p, s32 a, u32 ang);
#endif
#ifndef PROTO_LOCAL_Aquarium_RandFx
s32 Aquarium_RandFx(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Aquarium_RandAngle
s16 Aquarium_RandAngle(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Aquarium_RandRange
s32 Aquarium_RandRange(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Aquarium_ProbeTurnSide
BOOL Aquarium_ProbeTurnSide(s32 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_Aquarium_Oscillate
void Aquarium_Oscillate(s16 *out, u8 *flag, s32 *cnt, s32 max, s32 mul);
#endif
#ifndef PROTO_LOCAL_AquariumFish_StateNone
void AquariumFish_StateNone();
#endif
#ifndef PROTO_LOCAL_MuseumAquarium_FishStateNone
void MuseumAquarium_FishStateNone();
#endif
#ifndef PROTO_LOCAL_Aquarium_ApplyCorrection
void Aquarium_ApplyCorrection(void *self, s32 *p, s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e6d8
extern void *data_ov004_0224e6d8[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e618
extern void *data_ov004_0224e618[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e688
extern void *data_ov004_0224e688[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e620
extern void *data_ov004_0224e620[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e628
extern void *data_ov004_0224e628[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e648
extern void *data_ov004_0224e648[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e630
extern void *data_ov004_0224e630[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e640
extern void *data_ov004_0224e640[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e650
extern void *data_ov004_0224e650[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e658
extern void *data_ov004_0224e658[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e6c8
extern void *data_ov004_0224e6c8[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e6b8
extern void *data_ov004_0224e6b8[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e690
extern void *data_ov004_0224e690[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e6b0
extern void *data_ov004_0224e6b0[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e6a8
extern void *data_ov004_0224e6a8[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e698
extern void *data_ov004_0224e698[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e608
extern void *data_ov004_0224e608[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e678
extern void *data_ov004_0224e678[2];
#endif
#ifndef PROTO_LOCAL_sAquariumFirstFish
extern u8 sAquariumFirstFish;
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e660
extern void *data_ov004_0224e660[2];
#endif
#ifndef PROTO_LOCAL_sAquariumRoom
extern u8 sAquariumRoom;
#endif
#ifndef PROTO_LOCAL_sAquariumEndFish
extern u8 sAquariumEndFish;
#endif
#ifndef PROTO_LOCAL_sAquariumObstacleCount
extern u8 sAquariumObstacleCount;
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sAquariumTankCenterA
extern FxVec3 sAquariumTankCenterA;
#endif
#ifndef PROTO_LOCAL_sAquariumTankCenterB
extern FxVec3 sAquariumTankCenterB;
#endif
#ifndef PROTO_LOCAL_Aquarium_StepXZ
void Aquarium_StepXZ(VecFx32 *p, s32 a, s16 ang);
#endif
#ifndef PROTO_LOCAL_Aquarium_TurnTowardHome
BOOL Aquarium_TurnTowardHome(void *obj, VecFx32 *a, VecFx32 *b, s32 max);
#endif
#ifndef PROTO_LOCAL_Aquarium_TestHeight800At
BOOL Aquarium_TestHeight800At(VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_AquariumFish_JointCalcPre
void AquariumFish_JointCalcPre(NNSG3dRS *c);
#endif
#ifndef PROTO_LOCAL_AquariumFish_JointCalcPost
void AquariumFish_JointCalcPost(NNSG3dRS *c);
#endif
#ifndef PROTO_LOCAL_AquariumFish_InstallJointCallbacks
void AquariumFish_InstallJointCallbacks(NNSG3dRS *c);
#endif
#ifndef PROTO_LOCAL_sAquariumSwimFishRoomFns
extern PairFn sAquariumSwimFishRoomFns[2];
#endif
#ifndef PROTO_LOCAL_sMuseumAquariumProfile
extern ProcProfile sMuseumAquariumProfile;
#endif
}
#endif

#endif
