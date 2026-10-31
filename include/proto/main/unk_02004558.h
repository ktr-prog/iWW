#ifndef PROTO_PROTO_MAIN_UNK_02004558_H
#define PROTO_PROTO_MAIN_UNK_02004558_H


#include "types.h"
#include "player/PlayerPickUpFanfareArgs.h"
#include "player/Unk_02006d14_Pair.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "actor/Character.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/VecFx32.h"
#include "player/PlayerAct30Args.h"
#include "player/PlayerActor.h"
#include "player/PlayerPickUpArgs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerActor_Create
void *PlayerActor_Create();
#endif
#ifndef PROTO_LOCAL_PlayerActor_CheckSceneExit
void PlayerActor_CheckSceneExit(s32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ApproachCoord
void PlayerActor_ApproachCoord(s32 *p, s32 target);
#endif
#ifndef PROTO_LOCAL_PlayerActor_TurnAngleSlow
s32 PlayerActor_TurnAngleSlow(s16 *p, s32 target);
#endif
#ifndef PROTO_LOCAL_PlayerActor_Accelerate
s32 PlayerActor_Accelerate(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DecreaseClamped
s32 PlayerActor_DecreaseClamped(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_Decelerate
s32 PlayerActor_Decelerate(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_DecelerateSkid
s32 PlayerActor_DecelerateSkid(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetSendFaceChange
void PlayerActor_NetSendFaceChange();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsWaitingForSlots
BOOL PlayerActor_IsWaitingForSlots();
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetArgsWait
void PlayerActor_SetArgsWait(u16 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetArgsWalk
void PlayerActor_SetArgsWalk(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_InitAct32Work
void PlayerActor_InitAct32Work(u32* p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetWriteChangeHeldItem
void PlayerActor_NetWriteChangeHeldItem(void* p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetReadChangeHeldItem
void PlayerActor_NetReadChangeHeldItem(void* p, u16* out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_LevelTiltForAction
void PlayerActor_LevelTiltForAction(void *p, u32 i, s32 force);
#endif
#ifndef PROTO_LOCAL_data_020d5e34
extern s32 data_020d5e34;
#endif
#ifndef PROTO_LOCAL_data_020d5e38
extern s32 data_020d5e38;
#endif
#ifndef PROTO_LOCAL_data_020d5e3c
extern s32 data_020d5e3c;
#endif
#ifndef PROTO_LOCAL_data_020d5e40
extern s32 data_020d5e40;
#endif
#ifndef PROTO_LOCAL_data_020d5e44
extern s32 data_020d5e44;
#endif
#ifndef PROTO_LOCAL_data_020d5e48
extern s32 data_020d5e48;
#endif
#ifndef PROTO_LOCAL_data_020d5e4c
extern u32 data_020d5e4c;
#endif
#ifndef PROTO_LOCAL_data_020d5e50
extern s32 data_020d5e50;
#endif
#ifndef PROTO_LOCAL_sPlayerActorErrorMsgFile
extern char sPlayerActorErrorMsgFile[];
#endif
#ifndef PROTO_LOCAL_sPlayerActorMsgFile
extern char sPlayerActorMsgFile[];
#endif
#ifndef PROTO_LOCAL_sPlayerActorGetInsectMsgFile
extern char sPlayerActorGetInsectMsgFile[];
#endif
#ifndef PROTO_LOCAL_sPlayerActorGetFishMsgFile
extern char sPlayerActorGetFishMsgFile[];
#endif
#ifndef PROTO_LOCAL_sPlayerClothTexName
extern char sPlayerClothTexName[];
#endif
#ifndef PROTO_LOCAL_sPlayerSkinPalName
extern char sPlayerSkinPalName[];
#endif
#ifndef PROTO_LOCAL_sPlayerEyeTexName
extern char sPlayerEyeTexName[];
#endif
#ifndef PROTO_LOCAL_sPlayerMouthTexName
extern char sPlayerMouthTexName[];
#endif
#ifndef PROTO_LOCAL_sPlayerHairPalName
extern char sPlayerHairPalName[];
#endif
#ifndef PROTO_LOCAL_sPlayerShirtTexName
extern char sPlayerShirtTexName[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerActor_GetGender
BOOL PlayerActor_GetGender(PlayerActor *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetShirt
void PlayerActor_GetShirt(u16 *out, PlayerActor *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetHat
void PlayerActor_GetHat(u16 *out, PlayerActor *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetFaceItem
void PlayerActor_GetFaceItem(u16 *out, PlayerActor *x);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetFaceAltFlag
u32 PlayerActor_GetFaceAltFlag(PlayerActor *x);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetFaceTexIndex
u32 PlayerActor_GetFaceTexIndex(PlayerActor *x);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StepTowardPoseFast
void PlayerActor_StepTowardPoseFast(PlayerActor *o, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_StepTowardXZ
void PlayerActor_StepTowardXZ(PlayerActor *o, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_OffsetByAngle
void PlayerActor_OffsetByAngle(VecFx32 *out, void *o, const VecFx32 *in, const s16 *ang, const s32 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_CompareLastPlayDateNow
s32 PlayerActor_CompareLastPlayDateNow(PlayerActor *o);
#endif
#ifndef PROTO_LOCAL_PlayerActor_CompareLastPlayDate
s32 PlayerActor_CompareLastPlayDate(PlayerActor *o, void *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_CalcHandItemPos
void PlayerActor_CalcHandItemPos(VecFx32 *dst, PlayerActor *o, u32 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_CalcNetFollowAngle
BOOL PlayerActor_CalcNetFollowAngle(PlayerActor *unused, s32 a, s32 b, s32 c, s16 d, s16 *out);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetArgsPickUp
void PlayerActor_SetArgsPickUp(PlayerPickUpArgs* out, Vec2* pos, s32 a, s32 b, u8 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetWritePickUp
void PlayerActor_NetWritePickUp(PlayerNetPickUpArgs* dst, Vec2* pos, s8 a, u16 b, u8 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetReadPickUp
void PlayerActor_NetReadPickUp(PlayerNetPickUpArgs* src, Vec2* pos, s8* a, u16* b, u8* c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetArgsPickUpFanfare
void PlayerActor_SetArgsPickUpFanfare(PlayerPickUpFanfareArgs* s, Unk_02006d14_Pair* p, u16 h, u8 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetWritePickUpFanfare
void PlayerActor_NetWritePickUpFanfare(PlayerNetPickUpFanfareArgs* s, Unk_02006d14_Pair* p, u16 h, u8 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetReadPickUpFanfare
void PlayerActor_NetReadPickUpFanfare(PlayerNetPickUpFanfareArgs* s, Unk_02006d14_Pair* out, u16* h, u8* b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetArgsPickUpFanfareStow
void PlayerActor_SetArgsPickUpFanfareStow(PlayerPickUpFanfareStowArgs* dst, Unk_02006d14_Pair* p, u8 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetWritePickUpFanfareStow
void PlayerActor_NetWritePickUpFanfareStow(PlayerNetPickUpFanfareStowArgs* dst, Unk_02006d14_Pair* p, u8 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_NetReadPickUpFanfareStow
void PlayerActor_NetReadPickUpFanfareStow(PlayerNetPickUpFanfareStowArgs* src, Unk_02006d14_Pair* out, u8* b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetArgsAct30
void PlayerActor_SetArgsAct30(PlayerAct30Args* p, u32 a, u32 b, u32 c, Character *d);
#endif
#ifndef PROTO_LOCAL_PlayerActor_CalcHeldUpItemPos
void PlayerActor_CalcHeldUpItemPos(VecFx32 *out, PlayerActor *obj, s32 n);
#endif
#ifndef PROTO_LOCAL_PlayerActor_JointCbPre
void PlayerActor_JointCbPre(NNSG3dRS *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_JointCbPost
void PlayerActor_JointCbPost(NNSG3dRS *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_JointCbStart
void PlayerActor_JointCbStart(NNSG3dRS *p);
#endif
#ifndef PROTO_LOCAL_sPlayerActorProfile
extern ActorProfile sPlayerActorProfile;
#endif
}
#endif

#endif
