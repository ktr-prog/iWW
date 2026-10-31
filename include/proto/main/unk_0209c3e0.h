#ifndef PROTO_PROTO_MAIN_UNK_0209C3E0_H
#define PROTO_PROTO_MAIN_UNK_0209C3E0_H


#include "types.h"
#ifdef __cplusplus
#include "room/RoomObjActor.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sRoomObjSyncStates
extern u8 sRoomObjSyncStates[3];
#endif
#ifndef PROTO_LOCAL_RoomObjSync_Reset
void RoomObjSync_Reset();
#endif
#ifndef PROTO_LOCAL_RoomObjSync_GetState
u32 RoomObjSync_GetState(u32 idx);
#endif
#ifndef PROTO_LOCAL_RoomObjSync_SetState
BOOL RoomObjSync_SetState(u32 idx, u8 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_RoomObjSync_ChangeState
BOOL RoomObjSync_ChangeState(RoomObjActor *self, u8 v);
#endif
}
#endif

#endif
