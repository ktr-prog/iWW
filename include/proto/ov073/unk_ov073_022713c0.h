#ifndef PROTO_PROTO_OV073_UNK_OV073_022713C0_H
#define PROTO_PROTO_OV073_UNK_OV073_022713C0_H


#include "types.h"
struct SpNpcJoanActEntry;
#ifndef __cplusplus
typedef struct SpNpcJoanActEntry SpNpcJoanActEntry;
#endif
#ifdef __cplusplus
#include "game/FxVec3.h"
#include "gfx/DebugColor.h"
class SpNpcJoan;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcJoan_IsEmptyItem
s32 SpNpcJoan_IsEmptyItem(u16 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcJoan_Create
SpNpcJoan *SpNpcJoan_Create();
#endif
}
#ifndef PROTO_LOCAL_data_ov073_02272584
extern DebugColor data_ov073_02272584;
#endif
#ifndef PROTO_LOCAL_data_ov073_02272598
extern DebugColor data_ov073_02272598;
#endif
#ifndef PROTO_LOCAL_data_ov073_0227258c
extern DebugColor data_ov073_0227258c;
#endif
#ifndef PROTO_LOCAL_data_ov073_02272594
extern DebugColor data_ov073_02272594;
#endif
#ifndef PROTO_LOCAL_data_ov073_02272580
extern DebugColor data_ov073_02272580;
#endif
#ifndef PROTO_LOCAL_data_ov073_02272588
extern DebugColor data_ov073_02272588;
#endif
#ifndef PROTO_LOCAL_sSpNpcJoanActTable
extern SpNpcJoanActEntry sSpNpcJoanActTable[5];
#endif
#ifndef PROTO_LOCAL_sSpNpcJoanSidestepOffsets
extern FxVec3 sSpNpcJoanSidestepOffsets[2];
#endif
#endif

#endif
