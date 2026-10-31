#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020F7A5C_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020F7A5C_H


#include "types.h"
#include "snd/SndBgmViews.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_Init
void BgmSyncSnd_Init(Rb *r, u16 v);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_Release
void BgmSyncSnd_Release(Rb *r);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_SetState
void BgmSyncSnd_SetState(Rb *r, u32 mode);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_ReadBeat
u32 BgmSyncSnd_ReadBeat(void);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_SetStartBeat
void BgmSyncSnd_SetStartBeat(Rb *r, s8 v);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_PollStarted
s32 BgmSyncSnd_PollStarted(Rb *r);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_SelectStep
void BgmSyncSnd_SelectStep(Rb *r);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_ReadVars
void BgmSyncSnd_ReadVars(Rb *r);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_ReadHeader
void BgmSyncSnd_ReadHeader(Rb *r);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_CalcPhase
s32 BgmSyncSnd_CalcPhase(Rb *r);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_BgmSyncSnd_Update
s32 BgmSyncSnd_Update(Rb *r, VecFx32 *arg);
#endif
#ifndef PROTO_LOCAL_BgmSyncSnd_UpdatePosition
void BgmSyncSnd_UpdatePosition(Rb *r, VecFx32 *arg);
#endif
}
#ifndef PROTO_LOCAL_data_021f5c30
extern s16 data_021f5c30;
#endif
#ifndef PROTO_LOCAL_data_021f5c34
extern s16 data_021f5c34;
#endif
#endif

#endif
