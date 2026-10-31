#ifndef PROTO_PROTO_MAIN_UNK_0205D340_H
#define PROTO_PROTO_MAIN_UNK_0205D340_H


#include "types.h"
struct PlayerFaceTexPool;
#ifndef __cplusplus
typedef struct PlayerFaceTexPool PlayerFaceTexPool;
#endif
#ifdef __cplusplus
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerFaceTexPool_Destroy
void PlayerFaceTexPool_Destroy();
#endif
#ifndef PROTO_LOCAL_PlayerFaceTex_GetPath
char *PlayerFaceTex_GetPath(u32 x);
#endif
#ifndef PROTO_LOCAL_PlayerFaceTex_GetBufferSize
s32 PlayerFaceTex_GetBufferSize();
#endif
#ifndef PROTO_LOCAL_PlayerFaceTexPool_AllocBuffers
void PlayerFaceTexPool_AllocBuffers(void **arr);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerFaceTexPool_Create
void PlayerFaceTexPool_Create(Heap *parent);
#endif
}
#ifndef PROTO_LOCAL_sPlayerFaceTexPathBuf
extern char sPlayerFaceTexPathBuf[0x14];
#endif
#ifndef PROTO_LOCAL_sPlayerFaceTexPool
extern PlayerFaceTexPool sPlayerFaceTexPool;
#endif
#endif

#endif
