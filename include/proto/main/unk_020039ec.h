#ifndef PROTO_PROTO_MAIN_UNK_020039EC_H
#define PROTO_PROTO_MAIN_UNK_020039EC_H


#include "types.h"
#include "snd/Melody.h"
#include "snd/SndBgmViews.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "snd/SndSceneBase.h"
#include "snd/SndSeEmitter.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Snd_Init
void Snd_Init();
#endif
#ifndef PROTO_LOCAL_Snd_Update
void Snd_Update();
#endif
#ifndef PROTO_LOCAL_func_020044dc
void func_020044dc();
#endif
#ifndef PROTO_LOCAL_Snd_CreateScene
void Snd_CreateScene();
#endif
#ifndef PROTO_LOCAL_Snd_DestroyScene
void Snd_DestroyScene();
#endif
#ifndef PROTO_LOCAL_Snd_VolumeOff
void Snd_VolumeOff();
#endif
#ifndef PROTO_LOCAL_Snd_VolumeOn
void Snd_VolumeOn();
#endif
#ifndef PROTO_LOCAL_Snd_FadeOutScene
void Snd_FadeOutScene();
#endif
#ifndef PROTO_LOCAL_Snd_PlaySe
void Snd_PlaySe(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_PlaySePanned
void Snd_PlaySePanned(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Snd_PlaySeOnHandle
void Snd_PlaySeOnHandle(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_StopSe
void Snd_StopSe(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Snd_SetOutputMode
void Snd_SetOutputMode(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_BeginTalk
void Snd_BeginTalk(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_PlayTalkVoice
void Snd_PlayTalkVoice(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Snd_EndTalk
void Snd_EndTalk();
#endif
#ifndef PROTO_LOCAL_Snd_SetVoiceType
void Snd_SetVoiceType(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_SetSceneBankVariant
void Snd_SetSceneBankVariant(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_SetSeHandleVolumes
void Snd_SetSeHandleVolumes(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_SetKeySeMode
void Snd_SetKeySeMode(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_PlayKeySe
void Snd_PlayKeySe(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_PlayAuxSe
void Snd_PlayAuxSe(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_PlayAuxSeHeld
void Snd_PlayAuxSeHeld(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_StopAuxSe
void Snd_StopAuxSe();
#endif
#ifndef PROTO_LOCAL_Snd_StartBellRollSe
void Snd_StartBellRollSe();
#endif
#ifndef PROTO_LOCAL_Snd_StopBellRollSe
void Snd_StopBellRollSe();
#endif
#ifndef PROTO_LOCAL_Snd_SeEmitterPlayAlternate
void Snd_SeEmitterPlayAlternate(void *e, u16 s);
#endif
#ifndef PROTO_LOCAL_Snd_PosListInit
void Snd_PosListInit(void *l);
#endif
#ifndef PROTO_LOCAL_Snd_PosListUpdate
void Snd_PosListUpdate(void *l);
#endif
#ifndef PROTO_LOCAL_Snd_PosNodeInit
void Snd_PosNodeInit(void *n, void *l);
#endif
#ifndef PROTO_LOCAL_Snd_PosNodeRelease
void Snd_PosNodeRelease(void *n);
#endif
#ifndef PROTO_LOCAL_Snd_PosNodeSetPitch
void Snd_PosNodeSetPitch(void *n, s32 v);
#endif
#ifndef PROTO_LOCAL_Snd_PosListCanInit
s32 Snd_PosListCanInit();
#endif
#ifndef PROTO_LOCAL_Snd_PlayBgm
void Snd_PlayBgm(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_StopBgm
void Snd_StopBgm(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_MoveBgmVolume
void Snd_MoveBgmVolume(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Snd_FadeOutBgmTracks
void Snd_FadeOutBgmTracks(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_FadeInBgmTracks
void Snd_FadeInBgmTracks(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_SetBgmTrackVariant
void Snd_SetBgmTrackVariant(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_GetBeatState
void *Snd_GetBeatState();
#endif
#ifndef PROTO_LOCAL_Snd_BeginMenuDuck
void Snd_BeginMenuDuck();
#endif
#ifndef PROTO_LOCAL_Snd_EndMenuDuck
void Snd_EndMenuDuck();
#endif
#ifndef PROTO_LOCAL_Snd_DuckSubPlayers
void Snd_DuckSubPlayers();
#endif
#ifndef PROTO_LOCAL_Snd_RestoreSubPlayers
void Snd_RestoreSubPlayers();
#endif
#ifndef PROTO_LOCAL_Snd_SetPanIfChanged
void Snd_SetPanIfChanged(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_SetPan
void Snd_SetPan(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyInit
void Snd_MelodyInit(void *c);
#endif
#ifndef PROTO_LOCAL_Snd_MelodySetPattern
void Snd_MelodySetPattern(void *c, u8 *src);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyPlayPattern
void Snd_MelodyPlayPattern(void *c, u32 v, u8 *pat);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyPlay
void Snd_MelodyPlay(void *c, u32 v);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyStartTrackA
void Snd_MelodyStartTrackA(void *c);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyPlayNote
void Snd_MelodyPlayNote(void *c, u32 idx);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyUpdate
s32 Snd_MelodyUpdate(void *c);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyIsPlaying
u8 Snd_MelodyIsPlaying(void *c);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyPlayRandom
void Snd_MelodyPlayRandom(void *c, u32 v);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyApplyRandomPattern
u8 *Snd_MelodyApplyRandomPattern(void *c);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyGetDefaultPattern
u8 *Snd_MelodyGetDefaultPattern();
#endif
#ifndef PROTO_LOCAL_Snd_BgmSyncInit
void Snd_BgmSyncInit(void *r, u16 v);
#endif
#ifndef PROTO_LOCAL_Snd_BgmSyncSetState
void Snd_BgmSyncSetState(void *r, u32 mode);
#endif
#ifndef PROTO_LOCAL_Snd_BgmSyncRelease
void Snd_BgmSyncRelease(void *r);
#endif
#ifndef PROTO_LOCAL_Snd_BgmSyncSetStartBeat
void Snd_BgmSyncSetStartBeat(void *r, s8 v);
#endif
#ifndef PROTO_LOCAL_Snd_BgmSyncReadBeat
u32 Snd_BgmSyncReadBeat();
#endif
#ifndef PROTO_LOCAL_Snd_BgmSyncPollStarted
s32 Snd_BgmSyncPollStarted(void *r);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyBeatInit
void Snd_MelodyBeatInit(void *s);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyBeatStart
void Snd_MelodyBeatStart(void *s, u16 id);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyBeatStop
void Snd_MelodyBeatStop(void *s);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Snd_SeEmitterPlayOneShot
void Snd_SeEmitterPlayOneShot(SndSeEmitter *a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Snd_SeEmitterPlayHeld
void Snd_SeEmitterPlayHeld(SndSeEmitter *a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Snd_SeEmitterPlayOneShotAlt
void Snd_SeEmitterPlayOneShotAlt(SndSeEmitter *a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Snd_PosNodePlay
void Snd_PosNodePlay(void *a, u32 b, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Snd_PosNodePlayOnce
void Snd_PosNodePlayOnce(void *a, u32 b, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Snd_SetBgmPan
void Snd_SetBgmPan(void *a, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyPlayAt
void Snd_MelodyPlayAt(void *a, VecFx32 *v, u32 c);
#endif
#ifndef PROTO_LOCAL_Snd_BgmSyncUpdate
s32 Snd_BgmSyncUpdate(Rb *a, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Snd_MelodyBeatUpdate
void Snd_MelodyBeatUpdate(MelodyBeat *a, VecFx32 *v);
#endif
}
#ifndef PROTO_LOCAL_gSndScene
extern SndSceneBase *gSndScene;
#endif
#ifndef PROTO_LOCAL_gSndHeapBuffer
extern u8 gSndHeapBuffer[0x80000];
#endif
#endif

#endif
