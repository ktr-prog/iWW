#ifndef PROTO_PROTO_OV004_UNK_OV004_022257E4_H
#define PROTO_PROTO_OV004_UNK_OV004_022257E4_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "gfx/NNSG3dRS.h"
class CheckInGate;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CheckInGate_Open
BOOL CheckInGate_Open();
#endif
#ifndef PROTO_LOCAL_CheckInGate_Close
BOOL CheckInGate_Close();
#endif
#ifndef PROTO_LOCAL_CheckInGate_IsOpen
BOOL CheckInGate_IsOpen();
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d7ac
extern char data_ov004_0224d7ac[];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d788
extern char data_ov004_0224d788[];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d7b8
extern char data_ov004_0224d7b8[];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d794
extern char data_ov004_0224d794[];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d7a0
extern char data_ov004_0224d7a0[];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d7c4
extern char data_ov004_0224d7c4[];
#endif
#ifndef PROTO_LOCAL_sCheckInGateGroundMats
extern char *sCheckInGateGroundMats[7];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d77c
extern char data_ov004_0224d77c[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_CheckInGate_Create
CheckInGate *CheckInGate_Create();
#endif
#ifndef PROTO_LOCAL_CheckInGate_MatCallback
void CheckInGate_MatCallback(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_CheckInGate_InitRenderObj
void CheckInGate_InitRenderObj(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_data_ov004_02250c48
extern DebugColor data_ov004_02250c48;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250c4c
extern DebugColor data_ov004_02250c4c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250c40
extern DebugColor data_ov004_02250c40;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250c44
extern DebugColor data_ov004_02250c44;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250c50
extern DebugColor data_ov004_02250c50;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250c38
extern DebugColor data_ov004_02250c38;
#endif
#ifndef PROTO_LOCAL_sCheckInGateProfile
extern ActorProfile sCheckInGateProfile;
#endif
}
#endif

#endif
