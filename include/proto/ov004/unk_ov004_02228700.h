#ifndef PROTO_PROTO_OV004_UNK_OV004_02228700_H
#define PROTO_PROTO_OV004_UNK_OV004_02228700_H


#include "types.h"
struct ClothTex;
#ifndef __cplusplus
typedef struct ClothTex ClothTex;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SewingMachine;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SewingMachine_Start
BOOL SewingMachine_Start();
#endif
#ifndef PROTO_LOCAL_SewingMachine_Stop
BOOL SewingMachine_Stop();
#endif
#ifndef PROTO_LOCAL_SewingMachine_IsStopped
BOOL SewingMachine_IsStopped();
#endif
#ifndef PROTO_LOCAL_SewingMachine_SetFrame
void SewingMachine_SetFrame(u32 x);
#endif
#ifndef PROTO_LOCAL_SewingMachine_GetFrame
u32 SewingMachine_GetFrame();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSewingMachineProfile
extern ActorProfile sSewingMachineProfile;
#endif
#ifndef PROTO_LOCAL_sSewingMachine
extern SewingMachine *sSewingMachine;
#endif
#ifndef PROTO_LOCAL_SewingMachine_Create
SewingMachine *SewingMachine_Create();
#endif
}
#ifndef PROTO_LOCAL_sSewingMachineCloth
extern ClothTex sSewingMachineCloth;
#endif
#endif

#endif
