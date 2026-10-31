#ifndef PROTO_PROTO_OV004_UNK_OV004_02229660_H
#define PROTO_PROTO_OV004_UNK_OV004_02229660_H


#include "types.h"
#include "room/PhoneChoiceSet.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "room/RoomTelephone.h"
#include "room/RoomTelephoneActEntry.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e16c
extern u8 data_ov004_0224e16c[2];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e170
extern u8 data_ov004_0224e170[3];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e174
extern u8 data_ov004_0224e174[4];
#endif
#ifndef PROTO_LOCAL_sRoomTelephoneMsgFile2
extern char sRoomTelephoneMsgFile2[];
#endif
#ifndef PROTO_LOCAL_sRoomTelephoneArcPath
extern char sRoomTelephoneArcPath[];
#endif
#ifndef PROTO_LOCAL_sRoomTelephoneTexPath
extern char sRoomTelephoneTexPath[];
#endif
#ifndef PROTO_LOCAL_RoomTelephone_PlayAnimHold
void RoomTelephone_PlayAnimHold();
#endif
#ifndef PROTO_LOCAL_RoomTelephone_PlayAnimHangUp
void RoomTelephone_PlayAnimHangUp();
#endif
#ifndef PROTO_LOCAL_RoomTelephone_PlayAnimPickUp
void RoomTelephone_PlayAnimPickUp();
#endif
#ifndef PROTO_LOCAL_RoomTelephone_StartAct0A
BOOL RoomTelephone_StartAct0A();
#endif
#ifndef PROTO_LOCAL_RoomTelephone_IsTalking
BOOL RoomTelephone_IsTalking();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov004_02251294
extern DebugColor data_ov004_02251294;
#endif
#ifndef PROTO_LOCAL_data_ov004_02251284
extern DebugColor data_ov004_02251284;
#endif
#ifndef PROTO_LOCAL_data_ov004_0225128c
extern DebugColor data_ov004_0225128c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02251280
extern DebugColor data_ov004_02251280;
#endif
#ifndef PROTO_LOCAL_data_ov004_0225127c
extern DebugColor data_ov004_0225127c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02251290
extern DebugColor data_ov004_02251290;
#endif
#ifndef PROTO_LOCAL_sRoomTelephoneActTable
extern RoomTelephoneActEntry sRoomTelephoneActTable[15];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e298
extern PhoneChoiceSet data_ov004_0224e298;
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e2a0
extern PhoneChoiceSet data_ov004_0224e2a0;
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e2a8
extern PhoneChoiceSet data_ov004_0224e2a8;
#endif
#ifndef PROTO_LOCAL_sRoomTelephone
extern RoomTelephone *volatile sRoomTelephone;
#endif
#ifndef PROTO_LOCAL_sRoomTelephoneProfile
extern ActorProfile sRoomTelephoneProfile;
#endif
#ifndef PROTO_LOCAL_RoomTelephone_GetInstance
RoomTelephone *RoomTelephone_GetInstance();
#endif
#ifndef PROTO_LOCAL_RoomTelephone_Create
RoomTelephone *RoomTelephone_Create();
#endif
}
#endif

#endif
