#ifndef PROTO_PROTO_OV004_UNK_OV004_022136D0_H
#define PROTO_PROTO_OV004_UNK_OV004_022136D0_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
class RoomBoardSign;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sRoomBoardSigns
extern void *sRoomBoardSigns[0x40];
#endif
#ifndef PROTO_LOCAL_sRoomBoardSignSpawnRadius
extern s32 sRoomBoardSignSpawnRadius;
#endif
#ifndef PROTO_LOCAL_RoomBoardSign_ClearRegistry
void RoomBoardSign_ClearRegistry();
#endif
#ifndef PROTO_LOCAL_sRoomBoardSignSpawnMsg
extern s16 sRoomBoardSignSpawnMsg;
#endif
#ifndef PROTO_LOCAL_sRoomBoardSignCount
extern u8 sRoomBoardSignCount;
#endif
#ifndef PROTO_LOCAL_RoomBoardSign_GetByIndex
void *RoomBoardSign_GetByIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_RoomBoardSign_Spawn
void RoomBoardSign_Spawn(void *a, s32 b, s32 c, s32 d);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov004_0225017c
extern DebugColor data_ov004_0225017c;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250184
extern DebugColor data_ov004_02250184;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250188
extern DebugColor data_ov004_02250188;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250170
extern DebugColor data_ov004_02250170;
#endif
#ifndef PROTO_LOCAL_sRoomBoardSignProfile
extern ActorProfile sRoomBoardSignProfile;
#endif
#ifndef PROTO_LOCAL_RoomBoardSign_Create
RoomBoardSign *RoomBoardSign_Create();
#endif
#ifndef PROTO_LOCAL_data_ov004_02250180
extern DebugColor data_ov004_02250180;
#endif
#ifndef PROTO_LOCAL_data_ov004_02250174
extern DebugColor data_ov004_02250174;
#endif
}
#endif

#endif
