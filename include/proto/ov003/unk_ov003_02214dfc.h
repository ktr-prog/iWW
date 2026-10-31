#ifndef PROTO_PROTO_OV003_UNK_OV003_02214DFC_H
#define PROTO_PROTO_OV003_UNK_OV003_02214DFC_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class GateHouse;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov003_02235228
extern char data_ov003_02235228[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_0223524c
extern char data_ov003_0223524c[0x24];
#endif
#ifndef PROTO_LOCAL_data_ov003_02235204
extern char data_ov003_02235204[0x24];
#endif
#ifndef PROTO_LOCAL_GateHouse_Create
void *GateHouse_Create();
#endif
#ifndef PROTO_LOCAL_GateHouse_GetDesign
s32 GateHouse_GetDesign();
#endif
#ifndef PROTO_LOCAL_GateHouse_GetModelName
char *GateHouse_GetModelName();
#endif
#ifndef PROTO_LOCAL_sGateHouseModelNames
extern char *sGateHouseModelNames[3];
#endif
#ifndef PROTO_LOCAL_data_ov003_022312a4
extern char data_ov003_022312a4[12];
#endif
#ifndef PROTO_LOCAL_data_ov003_022312b0
extern char data_ov003_022312b0[12];
#endif
#ifndef PROTO_LOCAL_data_ov003_022312bc
extern char data_ov003_022312bc[12];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sGateHouseProfile
extern ActorProfile sGateHouseProfile;
#endif
#ifndef PROTO_LOCAL_GateHouse_ApplyTownFlag
BOOL GateHouse_ApplyTownFlag(GateHouse *self);
#endif
}
#endif

#endif
