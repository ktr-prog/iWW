#ifndef PROTO_PROTO_OV072_UNK_OV072_022713C0_H
#define PROTO_PROTO_OV072_UNK_OV072_022713C0_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "town/BlockMap.h"
class SpNpcGulliver;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcGulliverKey
extern u8 sSpNpcGulliverKey[12];
#endif
#ifndef PROTO_LOCAL_sSpNpcGulliverTexturePath
extern u8 sSpNpcGulliverTexturePath[27];
#endif
#ifndef PROTO_LOCAL_sSpNpcGulliverModelPath
extern u8 sSpNpcGulliverModelPath[23];
#endif
#ifndef PROTO_LOCAL_SpNpcGulliver_TickTimer
s32 SpNpcGulliver_TickTimer(void *self, s32 *p);
#endif
#ifndef PROTO_LOCAL_SpNpcGulliver_ScatterShipParts
void SpNpcGulliver_ScatterShipParts();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcGulliverProfile
extern ActorProfile sSpNpcGulliverProfile;
#endif
#ifndef PROTO_LOCAL_SpNpcGulliver_Create
SpNpcGulliver *SpNpcGulliver_Create();
#endif
#ifndef PROTO_LOCAL_SpNpcGulliver_IsSpotClear
BOOL SpNpcGulliver_IsSpotClear(s32 *a, s32 *b, BlockMap *g);
#endif
#ifndef PROTO_LOCAL_SpNpcGulliver_PlaceShipPart
BOOL SpNpcGulliver_PlaceShipPart(u8 *cnt, s32 *pe, BlockMap *g);
#endif
}
#ifndef PROTO_LOCAL_data_ov072_02272590
extern DebugColor data_ov072_02272590;
#endif
#ifndef PROTO_LOCAL_data_ov072_02272580
extern DebugColor data_ov072_02272580;
#endif
#ifndef PROTO_LOCAL_data_ov072_0227258c
extern DebugColor data_ov072_0227258c;
#endif
#ifndef PROTO_LOCAL_data_ov072_02272594
extern DebugColor data_ov072_02272594;
#endif
#ifndef PROTO_LOCAL_data_ov072_02272584
extern DebugColor data_ov072_02272584;
#endif
#ifndef PROTO_LOCAL_data_ov072_02272588
extern DebugColor data_ov072_02272588;
#endif
#endif

#endif
