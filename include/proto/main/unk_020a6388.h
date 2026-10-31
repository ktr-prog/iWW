#ifndef PROTO_PROTO_MAIN_UNK_020A6388_H
#define PROTO_PROTO_MAIN_UNK_020A6388_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NetArea_IsBusyStubB
s32 NetArea_IsBusyStubB();
#endif
#ifndef PROTO_LOCAL_NetArea_IsBusyStubA
s32 NetArea_IsBusyStubA();
#endif
#ifndef PROTO_LOCAL_NetArea_OnSceneCreateNop
void NetArea_OnSceneCreateNop();
#endif
#ifndef PROTO_LOCAL_NetArea_QueueMoveRequest
void NetArea_QueueMoveRequest(u32 a, u8 b);
#endif
#ifndef PROTO_LOCAL_NetArea_SetSlotStatus
void NetArea_SetSlotStatus(s32 idx, u32 b, u32 c, u32 d, u32 e);
#endif
#ifndef PROTO_LOCAL_NetArea_SetMoveReady
void NetArea_SetMoveReady(s32 idx, u32 v);
#endif
#ifndef PROTO_LOCAL_NetArea_SetPendingStatus
void NetArea_SetPendingStatus(u32 idx, u32 a, u32 b, u32 c, u32 d);
#endif
#ifdef __cplusplus
}
#endif

#endif
