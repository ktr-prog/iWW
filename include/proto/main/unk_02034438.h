#ifndef PROTO_PROTO_MAIN_UNK_02034438_H
#define PROTO_PROTO_MAIN_UNK_02034438_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "snd/BgmManager.h"
#include "snd/BgmSceneFade.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BgmClock_Exit
void BgmClock_Exit(void);
#endif
#ifndef PROTO_LOCAL_Bgm_GetSceneBgmId
s32 Bgm_GetSceneBgmId(s32 a);
#endif
#ifndef PROTO_LOCAL_Bgm_IsSameSceneBgm
s32 Bgm_IsSameSceneBgm(void);
#endif
#ifndef PROTO_LOCAL_BgmSceneFade_Update
void BgmSceneFade_Update(void *p);
#endif
#ifndef PROTO_LOCAL_FaintBgm_Update
void FaintBgm_Update(void);
#endif
#ifndef PROTO_LOCAL_BgmTracks_FadeOutForScene
void BgmTracks_FadeOutForScene(void);
#endif
#ifndef PROTO_LOCAL_BgmTracks_FadeInForScene
void BgmTracks_FadeInForScene(void);
#endif
#ifndef PROTO_LOCAL_BgmTracks_FadeOutScene22
void BgmTracks_FadeOutScene22(void);
#endif
#ifndef PROTO_LOCAL_BgmTracks_FadeInScene22
void BgmTracks_FadeInScene22(void);
#endif
#ifndef PROTO_LOCAL_BgmTracks_ApplySceneMask
void BgmTracks_ApplySceneMask(void);
#endif
#ifndef PROTO_LOCAL_Bgm_Request
void Bgm_Request(s32 a, s32 b, s32 c, u8 d);
#endif
#ifndef PROTO_LOCAL_Bgm_RequestSilence
void Bgm_RequestSilence(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Bgm_RequestTransient
void Bgm_RequestTransient(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Bgm_Release
void Bgm_Release(s32 a);
#endif
#ifndef PROTO_LOCAL_Bgm_ReleasePriority
void Bgm_ReleasePriority(s32 a);
#endif
#ifndef PROTO_LOCAL_Bgm_ReleaseTransient
void Bgm_ReleaseTransient(s32 a);
#endif
#ifndef PROTO_LOCAL_Bgm_GetCurrent
u16 Bgm_GetCurrent(void);
#endif
#ifndef PROTO_LOCAL_Bgm_EnableHourChime
void Bgm_EnableHourChime(void);
#endif
#ifndef PROTO_LOCAL_Bgm_DisableHourChime
void Bgm_DisableHourChime(void);
#endif
#ifndef PROTO_LOCAL_Bgm_ResetAll
void Bgm_ResetAll();
#endif
#ifndef PROTO_LOCAL_Bgm_StartSceneBgm
void Bgm_StartSceneBgm();
#endif
#ifndef PROTO_LOCAL_Bgm_EndSceneBgm
void Bgm_EndSceneBgm();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_BgmClock_Init
void BgmClock_Init(BgmClock *p);
#endif
#ifndef PROTO_LOCAL_BgmClock_Update
void BgmClock_Update(BgmClock *p);
#endif
#ifndef PROTO_LOCAL_BgmClock_Reset
void BgmClock_Reset(BgmClock *p);
#endif
#ifndef PROTO_LOCAL_Bgm_GetClock
BgmClock *Bgm_GetClock(void);
#endif
#ifndef PROTO_LOCAL_Bgm_GetTracks
BgmTracks *Bgm_GetTracks(void);
#endif
#ifndef PROTO_LOCAL_Bgm_GetFieldBgm
FieldBgm *Bgm_GetFieldBgm(void);
#endif
#ifndef PROTO_LOCAL_Bgm_GetRoomBgm
RoomBgm *Bgm_GetRoomBgm(void);
#endif
#ifndef PROTO_LOCAL_BgmSceneFade_Reset
void BgmSceneFade_Reset(BgmSceneFade *p);
#endif
#ifndef PROTO_LOCAL_Bgm_GetSceneFade
BgmSceneFade *Bgm_GetSceneFade(void);
#endif
#ifndef PROTO_LOCAL_BgmTracks_OnBgmStart
void BgmTracks_OnBgmStart(BgmTracks *a, s32 b);
#endif
#ifndef PROTO_LOCAL_BgmTracks_Update
void BgmTracks_Update(BgmTracks *a);
#endif
#ifndef PROTO_LOCAL_BgmTracks_UpdateWeatherVariant
void BgmTracks_UpdateWeatherVariant(BgmTracks *x);
#endif
#ifndef PROTO_LOCAL_Bgm_GetPlayingRequest
BgmRequest *Bgm_GetPlayingRequest();
#endif
}
#ifndef PROTO_LOCAL_sNewYearEveDate
extern u16 sNewYearEveDate[2];
#endif
#ifndef PROTO_LOCAL_sNewYearEveTime
extern u16 sNewYearEveTime[2];
#endif
#ifndef PROTO_LOCAL_sNewYearDayDate
extern u16 sNewYearDayDate[2];
#endif
#ifndef PROTO_LOCAL_sBgmProcProfile
extern ProcProfile sBgmProcProfile;
#endif
#endif

#endif
