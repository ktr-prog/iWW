#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020EF150_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020EF150_H


#include "types.h"
struct SndEnt;
#ifndef __cplusplus
typedef struct SndEnt SndEnt;
#endif
#ifdef __cplusplus
#include "snd/BgmBeatPhase.h"
#include "snd/SndMgr.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SndVoice_GetSyllable
s32 SndVoice_GetSyllable(s32 a, s32 b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SndMgr_PlaySe
void SndMgr_PlaySe(SndMgr *self, s32 id);
#endif
#ifndef PROTO_LOCAL_SndMgr_PlaySeOnHandle
void SndMgr_PlaySeOnHandle(SndMgr *self, s32 a);
#endif
#ifndef PROTO_LOCAL_SndMgr_StopSe
void SndMgr_StopSe(SndMgr *self, s32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_SndMgr_SetVoiceType
void SndMgr_SetVoiceType(SndMgr *self, u32 v);
#endif
#ifndef PROTO_LOCAL_SndMgr_PlayVoice
void SndMgr_PlayVoice(SndMgr *self, s32 a, u8 x, s32 y);
#endif
#ifndef PROTO_LOCAL_SndMgr_LoadBank
void SndMgr_LoadBank(SndMgr *self, u32 bankNo);
#endif
#ifndef PROTO_LOCAL_SndMgr_Rand
u16 SndMgr_Rand(SndMgr *self, u32 n);
#endif
#ifndef PROTO_LOCAL_SndMgr_PlayBgm
void SndMgr_PlayBgm(SndMgr *self, u32 k);
#endif
#ifndef PROTO_LOCAL_SndMgr_StopBgm
void SndMgr_StopBgm(SndMgr *self, s32 v);
#endif
#ifndef PROTO_LOCAL_SndMgr_MoveBgmVolume
void SndMgr_MoveBgmVolume(SndMgr *self, s32 v, u32 w);
#endif
#ifndef PROTO_LOCAL_SndMgr_FadeOutBgmTracks
void SndMgr_FadeOutBgmTracks(SndMgr *self, s32 k);
#endif
#ifndef PROTO_LOCAL_SndMgr_FadeInBgmTracks
void SndMgr_FadeInBgmTracks(SndMgr *self, u32 k);
#endif
#ifndef PROTO_LOCAL_SndMgr_SetBgmTrackVariant
void SndMgr_SetBgmTrackVariant(SndMgr *self, u32 st);
#endif
#ifndef PROTO_LOCAL_SndMgr_StartBgmSeq
void SndMgr_StartBgmSeq(SndMgr *self, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_SndMgr_StopBgmSeq
void SndMgr_StopBgmSeq(SndMgr *self, s32 frames);
#endif
#ifndef PROTO_LOCAL_SndMgr_UpdateTrackRamps
void SndMgr_UpdateTrackRamps(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_UpdateVolumeRamps
void SndMgr_UpdateVolumeRamps(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_ApplyPan
void SndMgr_ApplyPan(SndMgr *self, u32 flag);
#endif
#ifndef PROTO_LOCAL_SndMgr_SetPlayerVolumes
void SndMgr_SetPlayerVolumes(SndMgr *self, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_SndMgr_SetSubPlayerVolume
void SndMgr_SetSubPlayerVolume(SndMgr *self, s32 v);
#endif
#ifndef PROTO_LOCAL_SndMgr_BeginMenuDuck
void SndMgr_BeginMenuDuck(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_EndMenuDuck
void SndMgr_EndMenuDuck(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_DuckSubPlayers
void SndMgr_DuckSubPlayers(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_RestoreSubPlayers
void SndMgr_RestoreSubPlayers(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_StartVolumeFadeIn
void SndMgr_StartVolumeFadeIn(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_GetBeatState
BgmBeatPhase *SndMgr_GetBeatState(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_UpdateVolumeCurve
void SndMgr_UpdateVolumeCurve(SndMgr *self, u32 a);
#endif
#ifndef PROTO_LOCAL_SndMgr_SetPanIfChanged
void SndMgr_SetPanIfChanged(SndMgr *self, u8 v);
#endif
#ifndef PROTO_LOCAL_SndMgr_SetPan
void SndMgr_SetPan(SndMgr *self, u8 v);
#endif
#ifndef PROTO_LOCAL_SndMgr_SetKeySeMode
void SndMgr_SetKeySeMode(SndMgr *self, u32 v);
#endif
#ifndef PROTO_LOCAL_SndMgr_PlayKeySe
void SndMgr_PlayKeySe(SndMgr *self, u32 id);
#endif
#ifndef PROTO_LOCAL_SndMgr_SetSeHandleVolumes
void SndMgr_SetSeHandleVolumes(SndMgr *self, s32 v);
#endif
#ifndef PROTO_LOCAL_SndMgr_PlayAuxSe
void SndMgr_PlayAuxSe(SndMgr *self, u32 a);
#endif
#ifndef PROTO_LOCAL_SndMgr_PlayAuxSeHeld
void SndMgr_PlayAuxSeHeld(SndMgr *self, u32 a);
#endif
#ifndef PROTO_LOCAL_SndMgr_StopAuxSe
void SndMgr_StopAuxSe(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_StartBellRollSe
void SndMgr_StartBellRollSe(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_StopBellRollSe
void SndMgr_StopBellRollSe(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_PlaySePanned
void SndMgr_PlaySePanned(SndMgr *self, u16 a, u32 b);
#endif
#ifndef PROTO_LOCAL_SndRamp_Set
void SndRamp_Set(SndRamp *r, s32 v);
#endif
#ifndef PROTO_LOCAL_SndRamp_Start
void SndRamp_Start(SndRamp *r, s16 target, u32 frames);
#endif
#ifndef PROTO_LOCAL_SndRamp_Step
s16 SndRamp_Step(SndRamp *r);
#endif
#ifndef PROTO_LOCAL_SndMgr_ClampVolume
u8 SndMgr_ClampVolume(SndMgr *self, u8 v);
#endif
#ifndef PROTO_LOCAL_SndMgr_UpdateVoice
void SndMgr_UpdateVoice(SndMgr *self);
#endif
#ifndef PROTO_LOCAL_SndMgr_GetVoiceSeqIndex
u16 SndMgr_GetVoiceSeqIndex(SndMgr *self, u16 id);
#endif
}
#ifndef PROTO_LOCAL_gSndPanTrackMask
extern u16 gSndPanTrackMask;
#endif
#ifndef PROTO_LOCAL_sBgmTrackVariantTable
extern SndEnt sBgmTrackVariantTable[24];
#endif
#endif

#endif
