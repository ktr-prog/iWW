#ifndef PROTO_PROTO_MAIN_UNK_02094810_H
#define PROTO_PROTO_MAIN_UNK_02094810_H


#include "types.h"
#ifdef __cplusplus
#include "actor/Character.h"
#include "gfx/VecFx32.h"
#include "player/PlayerActor.h"
class PlayerSessionTable;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetNetPosVar
u8 *PlayerActor_GetNetPosVar(s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetNetAngleVar
u8 *PlayerActor_GetNetAngleVar(s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetNetStateVar
u8 *PlayerActor_GetNetStateVar(s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetSlotPosXZ
BOOL PlayerActor_GetSlotPosXZ(u8 *outb, s32 *x, s32 *y, s32 mode, s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetSlotAngle
BOOL PlayerActor_GetSlotAngle(s16 *out, s32 a, s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetSlotAction
BOOL PlayerActor_GetSlotAction(u32 *out, s32 a, s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_PackNetState
void PlayerActor_PackNetState(void *dst, s32 x);
#endif
#ifndef PROTO_LOCAL_PlayerActor_PackClothesChange
void PlayerActor_PackClothesChange(u8 *p, u16 h, u8 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_UnpackClothesChange
void PlayerActor_UnpackClothesChange(u8 *p, u16 *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_PackHair
void PlayerActor_PackHair(u8 *p, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_UnpackHair
void PlayerActor_UnpackHair(u8 *src, u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_PlayerSession_ClearActor
void PlayerSession_ClearActor(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_SetDataIndex
void PlayerSession_SetDataIndex(s32 i, s32 v);
#endif
#ifndef PROTO_LOCAL_PlayerSession_ClearDataIndex
void PlayerSession_ClearDataIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_GetDataIndex
u8 PlayerSession_GetDataIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_GetTanTimer
u16 *PlayerSession_GetTanTimer();
#endif
#ifndef PROTO_LOCAL_PlayerSession_GetSessionFlags
u8 *PlayerSession_GetSessionFlags();
#endif
#ifndef PROTO_LOCAL_PlayerSession_GetLastAction
s32 *PlayerSession_GetLastAction(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_GetLastScene
u8 *PlayerSession_GetLastScene(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_GetLastAngle
s16 *PlayerSession_GetLastAngle(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_ResetLastState
void PlayerSession_ResetLastState(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_SetGfxSlot
void PlayerSession_SetGfxSlot(s32 i, s32 v);
#endif
#ifndef PROTO_LOCAL_PlayerSession_ClearGfxSlot
void PlayerSession_ClearGfxSlot(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_GetGfxSlot
u8 PlayerSession_GetGfxSlot(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSession_FindFreeGfxSlot
u32 PlayerSession_FindFreeGfxSlot();
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetActorNop
void PlayerActor_GetActorNop();
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetActor
void *PlayerActor_GetActor(s32 id);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetCharacterNop
void PlayerActor_GetCharacterNop();
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetCharacter
void *PlayerActor_GetCharacter(s32 id);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ParamGetSlot
u32 PlayerActor_ParamGetSlot(u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ParamGetAction
u32 PlayerActor_ParamGetAction(u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsStowFinished
BOOL PlayerActor_IsStowFinished();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsEnteringDoor
BOOL PlayerActor_IsEnteringDoor();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsScriptedWalking
BOOL PlayerActor_IsScriptedWalking(s32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsInAct05
BOOL PlayerActor_IsInAct05();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsInWaitMenu
BOOL PlayerActor_IsInWaitMenu();
#endif
#ifndef PROTO_LOCAL_PlayerActor_TestSlotFlag
BOOL PlayerActor_TestSlotFlag(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsInAction
BOOL PlayerActor_IsInAction(s32 v, s32 id);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetAction
s32 PlayerActor_GetAction(s32 id);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetActionOrSpawnAction
s32 PlayerActor_GetActionOrSpawnAction();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsChangingClothes
BOOL PlayerActor_IsChangingClothes();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsChangingHeldItem
BOOL PlayerActor_IsChangingHeldItem();
#endif
#ifndef PROTO_LOCAL_PlayerActor_CanAcceptTalk
s32 PlayerActor_CanAcceptTalk();
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetEventLock
BOOL PlayerActor_SetEventLock(s32 c);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetNoFaceTalkTarget
BOOL PlayerActor_SetNoFaceTalkTarget(s32 c, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetNetFollowPaused
BOOL PlayerActor_SetNetFollowPaused(s32 c, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_KeepAnimForNextAction
BOOL PlayerActor_KeepAnimForNextAction();
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetSlotFlag
BOOL PlayerActor_SetSlotFlag(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_ClearSlotFlag
BOOL PlayerActor_ClearSlotFlag(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_CanOpenMenu
BOOL PlayerActor_CanOpenMenu();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsInterruptibleByMenu
BOOL PlayerActor_IsInterruptibleByMenu();
#endif
#ifndef PROTO_LOCAL_PlayerActor_CanStartTalk
BOOL PlayerActor_CanStartTalk();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsEventIdle
BOOL PlayerActor_IsEventIdle();
#endif
#ifndef PROTO_LOCAL_PlayerActor_IsInterruptible
BOOL PlayerActor_IsInterruptible();
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestAct05
s32 PlayerActor_RequestAct05();
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestReturnToWait
s32 PlayerActor_RequestReturnToWait();
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestChangeClothes
s32 PlayerActor_RequestChangeClothes(u16 *p, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestWearShirt
s32 PlayerActor_RequestWearShirt(u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestWearFaceItem
s32 PlayerActor_RequestWearFaceItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestWearHat
s32 PlayerActor_RequestWearHat(u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestFaceChange
s32 PlayerActor_RequestFaceChange();
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestWearShirtAlt
s32 PlayerActor_RequestWearShirtAlt(u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestWearFaceItemAlt
s32 PlayerActor_RequestWearFaceItemAlt(u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestWearHatAlt
s32 PlayerActor_RequestWearHatAlt(u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestChangeHeldItem
s32 PlayerActor_RequestChangeHeldItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestHoldUpItem
s32 PlayerActor_RequestHoldUpItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestTurnTo
s32 PlayerActor_RequestTurnTo(s32 a, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestAct32
s32 PlayerActor_RequestAct32();
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestAct79
s32 PlayerActor_RequestAct79();
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestStowThenAct10
void PlayerActor_RequestStowThenAct10(u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestAct10
s32 PlayerActor_RequestAct10();
#endif
#ifndef PROTO_LOCAL_PlayerActor_LocalRequestExitWalkOut
s32 PlayerActor_LocalRequestExitWalkOut();
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestAct13
s32 PlayerActor_RequestAct13();
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestEmotion
s32 PlayerActor_RequestEmotion(u8 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerActor_Get
PlayerActor *PlayerActor_Get(s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_SetActor
void PlayerSessionTable_SetActor(PlayerSessionTable *p, s32 i, PlayerActor *v);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_ClearActor
void PlayerSessionTable_ClearActor(PlayerSessionTable *p, s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_GetActor
PlayerActor *PlayerSessionTable_GetActor(PlayerSessionTable *p, s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_SetDataIndex
void PlayerSessionTable_SetDataIndex(PlayerSessionTable *p, s32 i, s32 v);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_ClearDataIndex
void PlayerSessionTable_ClearDataIndex(PlayerSessionTable *p, s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_GetDataIndex
u8 PlayerSessionTable_GetDataIndex(PlayerSessionTable *p, s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_SetGfxSlot
void PlayerSessionTable_SetGfxSlot(PlayerSessionTable *p, s32 i, s32 v);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_ClearGfxSlot
void PlayerSessionTable_ClearGfxSlot(PlayerSessionTable *p, s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_GetGfxSlot
u8 PlayerSessionTable_GetGfxSlot(PlayerSessionTable *p, s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerSessionTable_FindFreeGfxSlot
u32 PlayerSessionTable_FindFreeGfxSlot(PlayerSessionTable *p);
#endif
#ifndef PROTO_LOCAL_PlayerSession_SetActor
void PlayerSession_SetActor(s32 i, PlayerActor *v);
#endif
#ifndef PROTO_LOCAL_PlayerSession_GetLastPos
VecFx32 *PlayerSession_GetLastPos(s32 i);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestWalkTo
s32 PlayerActor_RequestWalkTo(VecFx32Ctor *v, u32 b, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_RequestAct30
s32 PlayerActor_RequestAct30(u16 *a, u32 *b, u8 *c, u32 *d, Character *e);
#endif
}
#ifndef PROTO_LOCAL_gPlayerSessionTable
extern PlayerSessionTable gPlayerSessionTable;
#endif
#endif

#endif
