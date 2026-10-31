#ifndef PROTO_PROTO_OV004_UNK_OV004_0222A374_H
#define PROTO_PROTO_OV004_UNK_OV004_0222A374_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
class PlayerBedSetter;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Room_PlacePlayerBeds
void Room_PlacePlayerBeds();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sPlayerBedSetterProfile
extern ProcProfile sPlayerBedSetterProfile;
#endif
#ifndef PROTO_LOCAL_PlayerBedSetter_Create
PlayerBedSetter *PlayerBedSetter_Create();
#endif
}
#endif

#endif
