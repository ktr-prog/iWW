#ifndef PROTO_PROTO_MAIN_UNK_020943DC_H
#define PROTO_PROTO_MAIN_UNK_020943DC_H


#include "types.h"
#include "gfx/Mtx43.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetSlotHeldItem
void PlayerActor_GetSlotHeldItem(u16 *out, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetHoldableItem
BOOL PlayerActor_SetHoldableItem(u32 a, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetClothing
BOOL PlayerActor_SetClothing(u16 *p, s32 kind, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetSwollenFace
BOOL PlayerActor_SetSwollenFace(s32 a, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetTan
BOOL PlayerActor_SetTan(u32 x, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetHeadTilt
BOOL PlayerActor_SetHeadTilt(u32 a, u32 b, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetHandMtx
void PlayerActor_GetHandMtx(Mtx43 *out, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetItemInFront
u16 *PlayerActor_GetItemInFront();
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetLocalExitId
void PlayerActor_SetLocalExitId(s32 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_SetLocalExitKind
void PlayerActor_SetLocalExitKind(u32 *p);
#endif
#ifndef PROTO_LOCAL_PlayerActor_OnChatOpenNop
void PlayerActor_OnChatOpenNop();
#endif
#ifndef PROTO_LOCAL_PlayerActor_OnChatCloseNop
void PlayerActor_OnChatCloseNop();
#endif
#ifndef PROTO_LOCAL_PlayerActor_PlayLocalSe
void PlayerActor_PlayLocalSe(u32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerActor_GetBodyPos
VecFx32 *PlayerActor_GetBodyPos(u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetHeadPos
BOOL PlayerActor_GetHeadPos(VecFx32Ctor *out, u32 idx);
#endif
}
#ifndef PROTO_LOCAL_sPlayerFrontItemDist
extern s32 sPlayerFrontItemDist;
#endif
#endif

#endif
