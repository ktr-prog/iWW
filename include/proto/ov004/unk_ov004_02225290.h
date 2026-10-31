#ifndef PROTO_PROTO_OV004_UNK_OV004_02225290_H
#define PROTO_PROTO_OV004_UNK_OV004_02225290_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class BarberMachine;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BarberMachine_Start
void BarberMachine_Start();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_BarberMachine_Create
BarberMachine *BarberMachine_Create();
#endif
#ifndef PROTO_LOCAL_sBarberMachineProfile
extern ActorProfile sBarberMachineProfile;
#endif
#ifndef PROTO_LOCAL_sBarberMachine
extern BarberMachine *volatile sBarberMachine;
#endif
}
#endif

#endif
