#ifndef PROTO_PROTO_MAIN_UNK_0206D988_H
#define PROTO_PROTO_MAIN_UNK_0206D988_H


#include "types.h"
#include "snd/Melody.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_020ddf8c
extern s32 data_020ddf8c;
#endif
#ifndef PROTO_LOCAL_Melody_Pack
void Melody_Pack(u32 *dst, u8 *src);
#endif
#ifndef PROTO_LOCAL_Melody_Unpack
void Melody_Unpack(u32 *src, u8 *dst);
#endif
#ifndef PROTO_LOCAL_Melody_ResetToDefault
void Melody_ResetToDefault();
#endif
#ifndef PROTO_LOCAL_Melody_SetPacked
void Melody_SetPacked(u32 *a);
#endif
#ifndef PROTO_LOCAL_Melody_ApplyEditPattern
void Melody_ApplyEditPattern();
#endif
#ifndef PROTO_LOCAL_Melody_PlayEditPattern
void Melody_PlayEditPattern(u32 a);
#endif
#ifndef PROTO_LOCAL_Melody_Play
void Melody_Play(u32 a);
#endif
#ifndef PROTO_LOCAL_Melody_StartTrackA
void Melody_StartTrackA(s32 a);
#endif
#ifndef PROTO_LOCAL_Melody_PlayNote
void Melody_PlayNote(u32 a);
#endif
#ifndef PROTO_LOCAL_Melody_IsBusy
BOOL Melody_IsBusy();
#endif
#ifndef PROTO_LOCAL_Melody_PlayRandom
void Melody_PlayRandom(u32 a);
#endif
#ifndef PROTO_LOCAL_Melody_SaveRandomPattern
void Melody_SaveRandomPattern();
#endif
#ifndef PROTO_LOCAL_Melody_SaveDefaultPattern
void Melody_SaveDefaultPattern();
#endif
#ifndef PROTO_LOCAL_Melody_Init
void Melody_Init(void);
#endif
#ifndef PROTO_LOCAL_Melody_Update
void Melody_Update(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Melody_PlayAt
void Melody_PlayAt(VecFx32 *pos, u32 b);
#endif
}
#ifndef PROTO_LOCAL_sMelodyTimer
extern s32 sMelodyTimer;
#endif
#ifndef PROTO_LOCAL_gMelodyEditPattern
extern u8 gMelodyEditPattern[0x10];
#endif
#ifndef PROTO_LOCAL_gMelodyPlayer
extern MelodyPlayer gMelodyPlayer;
#endif
#endif

#endif
