#ifndef PROTO_PROTO_MAIN_UNK_0203C92C_H
#define PROTO_PROTO_MAIN_UNK_0203C92C_H


#include "types.h"
#ifdef __cplusplus
#include "player/PlayerOptions.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerOptions_IsHiragana
BOOL PlayerOptions_IsHiragana();
#endif
#ifndef PROTO_LOCAL_PlayerOptions_SetHiragana
void PlayerOptions_SetHiragana(s32 x);
#endif
#ifndef PROTO_LOCAL_PlayerOptions_IsStereo
BOOL PlayerOptions_IsStereo();
#endif
#ifndef PROTO_LOCAL_PlayerOptions_SetStereo
void PlayerOptions_SetStereo(s32 x);
#endif
#ifndef PROTO_LOCAL_PlayerOptions_GetTalkVoice
u32 PlayerOptions_GetTalkVoice();
#endif
#ifndef PROTO_LOCAL_PlayerOptions_SetTalkVoice
void PlayerOptions_SetTalkVoice(u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerOptions_Commit
void PlayerOptions_Commit();
#endif
#ifndef PROTO_LOCAL_PlayerOptions_OnConstruct
void PlayerOptions_OnConstruct();
#endif
#ifndef PROTO_LOCAL_PlayerOptions_ConstructInPlayer
void PlayerOptions_ConstructInPlayer();
#endif
#ifndef PROTO_LOCAL_PlayerOptions_DestructInPlayer
void PlayerOptions_DestructInPlayer();
#endif
#ifndef PROTO_LOCAL_PlayerOptions_OnDestruct
void PlayerOptions_OnDestruct();
#endif
#ifndef PROTO_LOCAL_PlayerOptions_CopyOut
void PlayerOptions_CopyOut(void *src, void *dst);
#endif
#ifndef PROTO_LOCAL_PlayerOptions_CopyIn
void PlayerOptions_CopyIn(void *dst, void *src);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerOptions_Get
PlayerOptions *PlayerOptions_Get();
#endif
}
#ifndef PROTO_LOCAL_sPlayerOptions
extern PlayerOptions sPlayerOptions;
#endif
#endif

#endif
