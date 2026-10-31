#ifndef PROTO_PROTO_OV003_UNK_OV003_02217908_H
#define PROTO_PROTO_OV003_UNK_OV003_02217908_H


#include "types.h"
#ifdef __cplusplus
#include "field/GroundSoundSrc.h"
#include "gfx/DebugColor.h"
#include "gfx/Model.h"
#include "gfx/VecFx32.h"
#include "snd/RainSndChannel.h"
#include "snd/SndEnvChannel.h"
struct BgAcreModel;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FieldGround_EndSoundSrc
void FieldGround_EndSoundSrc();
#endif
#ifndef PROTO_LOCAL_FieldGround_DestroyEnvChannel
void FieldGround_DestroyEnvChannel();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov003_02235460
extern DebugColor data_ov003_02235460;
#endif
#ifndef PROTO_LOCAL_data_ov003_02235474
extern DebugColor data_ov003_02235474;
#endif
#ifndef PROTO_LOCAL_data_ov003_02235470
extern DebugColor data_ov003_02235470;
#endif
#ifndef PROTO_LOCAL_data_ov003_0223546c
extern DebugColor data_ov003_0223546c;
#endif
#ifndef PROTO_LOCAL_data_ov003_02235468
extern DebugColor data_ov003_02235468;
#endif
#ifndef PROTO_LOCAL_data_ov003_02235464
extern DebugColor data_ov003_02235464;
#endif
#ifndef PROTO_LOCAL_FieldGround_DrawBackdrop
BOOL FieldGround_DrawBackdrop(Model *p);
#endif
#ifndef PROTO_LOCAL_FieldGround_ReleaseBackdrop
BOOL FieldGround_ReleaseBackdrop(Model *p);
#endif
#ifndef PROTO_LOCAL_FieldGround_GetBlockAcre
BgAcreModel *FieldGround_GetBlockAcre(GroundSoundSrc *r, u32 x, u32 y);
#endif
#ifndef PROTO_LOCAL_FieldGround_GetBlockBgObjects
void *FieldGround_GetBlockBgObjects(GroundSoundSrc *r, u32 x, u32 y);
#endif
#ifndef PROTO_LOCAL_FieldGround_FindSoundSrc
GroundSoundSrc *FieldGround_FindSoundSrc(GroundSoundSrc *out, VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_FieldGround_ConsiderSoundSrc
BOOL FieldGround_ConsiderSoundSrc(GroundSoundSrc *r, s32 d, VecFx32 *p, s32 k);
#endif
#ifndef PROTO_LOCAL_FieldGround_ResetSoundSrc
void FieldGround_ResetSoundSrc(GroundSoundSrc *r);
#endif
#ifndef PROTO_LOCAL_FieldGround_GetSoundSrcPos
VecFx32 *FieldGround_GetSoundSrcPos(GroundSoundSrc *r);
#endif
#ifndef PROTO_LOCAL_FieldGround_GetSoundSrcKind
s32 FieldGround_GetSoundSrcKind(GroundSoundSrc *r);
#endif
#ifndef PROTO_LOCAL_FieldGround_InitEnvChannel
void FieldGround_InitEnvChannel(RainSndChannel *p);
#endif
#ifndef PROTO_LOCAL_FieldGround_ResetEnvChannel
void FieldGround_ResetEnvChannel(SndEnvChannel *p);
#endif
#ifndef PROTO_LOCAL_FieldGround_PlayEnvSe
void FieldGround_PlayEnvSe(SndEnvChannel *p, VecFx32 *v, u32 a);
#endif
#ifndef PROTO_LOCAL_FieldGround_ReleaseEnvChannel
void FieldGround_ReleaseEnvChannel(SndEnvChannel *p);
#endif
}
#endif

#endif
