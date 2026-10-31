#ifndef PROTO_PROTO_MAIN_UNK_0209C390_H
#define PROTO_PROTO_MAIN_UNK_0209C390_H


#include "types.h"
#include "game/NibblePair.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SoftReset_Update
void SoftReset_Update();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_RoomObjSync_OnRecv
BOOL RoomObjSync_OnRecv(NibblePair *p);
#endif
}
#ifndef PROTO_LOCAL_gSoftResetRequested
extern u8 gSoftResetRequested;
#endif
#ifndef PROTO_LOCAL_sSoftResetHeld
extern u8 sSoftResetHeld;
#endif
#endif

#endif
