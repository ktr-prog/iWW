#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020EDE18_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020EDE18_H


#include "types.h"
#ifdef __cplusplus
#include "snd/PlayCtx.h"
#include "snd/Player.h"
#include "snd/SndSeGroup.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SndList_InitLink
void SndList_InitLink(void **p);
#endif
#ifndef PROTO_LOCAL_SndList_Append
void SndList_Append(void *list, void *obj);
#endif
#ifndef PROTO_LOCAL_SndList_Remove
void SndList_Remove(void *list, void *obj);
#endif
#ifndef PROTO_LOCAL_SndList_GetNext
void *SndList_GetNext(void *list, void *obj);
#endif
#ifndef PROTO_LOCAL_SndList_GetPrev
void *SndList_GetPrev(void *list, void *obj);
#endif
#ifndef PROTO_LOCAL_SndList_GetFirst
void *SndList_GetFirst(void **p);
#endif
#ifndef PROTO_LOCAL_SndList_GetLast
void *SndList_GetLast(void **p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SndSeGroup_StartVoice
void SndSeGroup_StartVoice(Group *g, s32 i, s32 v);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_ApplyVoiceParams
void SndSeGroup_ApplyVoiceParams(Group *g, s32 i);
#endif
#ifndef PROTO_LOCAL_Snd_SetListenerPanCallback
void Snd_SetListenerPanCallback(s32 (*f)(PlayCtx *));
#endif
#ifndef PROTO_LOCAL_Snd_SetListenerDistanceCallback
void Snd_SetListenerDistanceCallback(s32 (*f)(PlayCtx *));
#endif
#ifndef PROTO_LOCAL_Snd_SetListenerVolumeCallback
void Snd_SetListenerVolumeCallback(s32 (*f)(PlayCtx *));
#endif
#ifndef PROTO_LOCAL_SndSeGroup_EvalListener
void SndSeGroup_EvalListener(PlayCtx *p);
#endif
#ifndef PROTO_LOCAL_SndSeVoice_Init
void SndSeVoice_Init(Ent *e);
#endif
#ifndef PROTO_LOCAL_SndSeVoice_SetParams
void SndSeVoice_SetParams(Ent *e, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_SndSeVoice_Start
void SndSeVoice_Start(Ent *e, u32 a, u32 b, s32 c, s16 d);
#endif
#ifndef PROTO_LOCAL_SndSeVoice_StartHeld
void SndSeVoice_StartHeld(Ent *e, u32 a, u32 b, s32 c, s16 d);
#endif
#ifndef PROTO_LOCAL_SndSeVoice_IsPlayingId
BOOL SndSeVoice_IsPlayingId(Ent *e, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_SndSeVoice_Stop
void SndSeVoice_Stop(Ent *e, s32 x);
#endif
#ifndef PROTO_LOCAL_SndSeVoice_SetFlag
void SndSeVoice_SetFlag(Ent *e, s32 bit, s32 on);
#endif
#ifndef PROTO_LOCAL_SndSeVoice_IsHeld
BOOL SndSeVoice_IsHeld(Ent *e);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_SetFlag
void SndSeGroup_SetFlag(Group *g, s32 bit, s32 on);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_SetEnabled
void SndSeGroup_SetEnabled(Group *g, s32 x);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_FindFreeVoice
s32 SndSeGroup_FindFreeVoice(Group *g);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_Init
void SndSeGroup_Init(Group *g);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_Finish
void SndSeGroup_Finish(Group *g);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_Update
void SndSeGroup_Update(Group *g, void *src);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_Play
s32 SndSeGroup_Play(Group *g, u32 a, u32 b, s32 c, s16 d);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_PlayHeld
s32 SndSeGroup_PlayHeld(Group *g, u32 a, u32 b, s32 c, s16 d);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_Shutdown
void SndSeGroup_Shutdown(Group *g);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_ReleaseAll
void SndSeGroup_ReleaseAll(Group *g);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_StopVoice
void SndSeGroup_StopVoice(Group *g, s32 i, s32 a);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_StopAll
void SndSeGroup_StopAll(Group *g, s32 a);
#endif
#ifndef PROTO_LOCAL_SndSeGroup_StopHeld
void SndSeGroup_StopHeld(Group *g, s32 a);
#endif
#ifndef PROTO_LOCAL_SndSeSystem_LoadGroup
BOOL SndSeSystem_LoadGroup(Player *o);
#endif
}
#ifndef PROTO_LOCAL_gSndListenerPanCallback
extern s32 (*gSndListenerPanCallback) (PlayCtx *);
#endif
#ifndef PROTO_LOCAL_gSndListenerDistanceCallback
extern s32 (*gSndListenerDistanceCallback) (PlayCtx *);
#endif
#ifndef PROTO_LOCAL_gSndListenerVolumeCallback
extern s32 (*gSndListenerVolumeCallback) (PlayCtx *);
#endif
#endif

#endif
