#ifndef PROTO_PROTO_OV003_UNK_OV003_02217BE8_H
#define PROTO_PROTO_OV003_UNK_OV003_02217BE8_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "gfx/DebugColor.h"
#include "gfx/Model.h"
#include "gfx/NNSG3dRS.h"
class FieldGround;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov003_02235490
extern u8 data_ov003_02235490;
#endif
#ifndef PROTO_LOCAL_data_ov003_02235494
extern s32 data_ov003_02235494;
#endif
#ifndef PROTO_LOCAL_data_ov003_022323f4
extern char data_ov003_022323f4[0xc];
#endif
#ifndef PROTO_LOCAL_data_ov003_02232400
extern char data_ov003_02232400[0x10];
#endif
#ifndef PROTO_LOCAL_sWaterMatNames
extern char *sWaterMatNames[2];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov003_022354a4
extern DebugColor data_ov003_022354a4;
#endif
#ifndef PROTO_LOCAL_data_ov003_022354a8
extern DebugColor data_ov003_022354a8;
#endif
#ifndef PROTO_LOCAL_data_ov003_02235498
extern DebugColor data_ov003_02235498;
#endif
#ifndef PROTO_LOCAL_data_ov003_022354a0
extern DebugColor data_ov003_022354a0;
#endif
#ifndef PROTO_LOCAL_data_ov003_0223549c
extern DebugColor data_ov003_0223549c;
#endif
#ifndef PROTO_LOCAL_data_ov003_022354ac
extern DebugColor data_ov003_022354ac;
#endif
#ifndef PROTO_LOCAL_sFieldGroundProfile
extern ProcProfile sFieldGroundProfile;
#endif
#ifndef PROTO_LOCAL_FieldGround_Create
FieldGround *FieldGround_Create();
#endif
#ifndef PROTO_LOCAL_FieldGround_OnBeachMaterial
void FieldGround_OnBeachMaterial(NNSG3dRS *rs);
#endif
#ifndef PROTO_LOCAL_FieldGround_OnModelInit
void FieldGround_OnModelInit(NNSG3dRS *rs);
#endif
#ifndef PROTO_LOCAL_FieldGround_SetWaterMatFlags
void FieldGround_SetWaterMatFlags(Model *o, s32 flag);
#endif
}
#endif

#endif
