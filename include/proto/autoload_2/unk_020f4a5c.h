#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020F4A5C_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020F4A5C_H


#include "types.h"
#include "snd/Melody.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_MelodyTrack_Init
void MelodyTrack_Init(MelodyTrack *self);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_Start
void MelodyTrack_Start(MelodyTrack *self, u16 id, u8 *pat);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_StartPattern
void MelodyTrack_StartPattern(MelodyTrack *self, u8 *pat);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_PlayNote
void MelodyTrack_PlayNote(MelodyTrack *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_SetInstrument
void MelodyTrack_SetInstrument(MelodyTrack *s, u16 v);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_Stop
void MelodyTrack_Stop(MelodyTrack *p);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_Reset
void MelodyTrack_Reset(MelodyTrack *self);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_ReadParams
void MelodyTrack_ReadParams(MelodyTrack *self);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_GetStepNote
u8 MelodyTrack_GetStepNote(MelodyTrack *self, u8 idx);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_PlayStep
void MelodyTrack_PlayStep(MelodyTrack *self);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_CheckEnd
BOOL MelodyTrack_CheckEnd(MelodyTrack *self);
#endif
#ifndef PROTO_LOCAL_MelodyTrack_Update
s32 MelodyTrack_Update(MelodyTrack *self);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_Init
void MelodyPlayer_Init(MelodyPlayer *c);
#endif
#ifndef PROTO_LOCAL_Melody_GetDefaultPattern
u8 *Melody_GetDefaultPattern(void);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_SetPattern
void MelodyPlayer_SetPattern(MelodyPlayer *c, u8 *src);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_GetPattern
u8 *MelodyPlayer_GetPattern(MelodyPlayer *c);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_PlayPattern
void MelodyPlayer_PlayPattern(MelodyPlayer *c, u32 v, u8 *pat);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_Play
void MelodyPlayer_Play(MelodyPlayer *c, u32 v);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_PlayRandom
void MelodyPlayer_PlayRandom(MelodyPlayer *c, u32 v);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_ApplyRandomPattern
u8 *MelodyPlayer_ApplyRandomPattern(MelodyPlayer *c);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_StopTrackB
void MelodyPlayer_StopTrackB(MelodyPlayer *c);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_StartTrackA
void MelodyPlayer_StartTrackA(MelodyPlayer *c);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_PlayNote
void MelodyPlayer_PlayNote(MelodyPlayer *c, u32 idx);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_Update
s32 MelodyPlayer_Update(MelodyPlayer *c);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_IsPlaying
u8 MelodyPlayer_IsPlaying(MelodyPlayer *c);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_SetInstrument
void MelodyPlayer_SetInstrument(MelodyPlayer *c, u16 v);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_LoadBank
void MelodyPlayer_LoadBank(MelodyPlayer *c, u32 id);
#endif
#ifndef PROTO_LOCAL_MelodyPlayer_LoadSeqArc
void MelodyPlayer_LoadSeqArc(MelodyPlayer *c, u32 id);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_Construct
void MelodyBeat_Construct(void);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_Destruct
void MelodyBeat_Destruct(void);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_Init
void MelodyBeat_Init(MelodyBeat *self);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_Stop
void MelodyBeat_Stop(MelodyBeat *self);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_Start
void MelodyBeat_Start(MelodyBeat *self, u16 id);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_ReadParams
void MelodyBeat_ReadParams(MelodyBeat *self);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_EndStep
BOOL MelodyBeat_EndStep(MelodyBeat *self);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_MelodyPlayer_PlayAt
void MelodyPlayer_PlayAt(MelodyPlayer *c, VecFx32 *pos, u32 mode);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_Update
void MelodyBeat_Update(MelodyBeat *self, VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_PlayStep
void MelodyBeat_PlayStep(MelodyBeat *self, VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_MelodyBeat_ApplyPosition
void MelodyBeat_ApplyPosition(MelodyBeat *obj, VecFx32 *pos);
#endif
}
#ifndef PROTO_LOCAL_data_0213b9d8
extern u8 data_0213b9d8;
#endif
#ifndef PROTO_LOCAL_data_021f5c28
extern u16 data_021f5c28;
#endif
#ifndef PROTO_LOCAL_sMelodyBeatPattern
extern u8 *sMelodyBeatPattern;
#endif
#endif

#endif
