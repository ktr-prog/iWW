#ifndef PROTO_PROTO_MAIN_UNK_0205EDFC_H
#define PROTO_PROTO_MAIN_UNK_0205EDFC_H


#include "types.h"
struct PlayerBodyWorkPool;
#ifndef __cplusplus
typedef struct PlayerBodyWorkPool PlayerBodyWorkPool;
#endif
#ifdef __cplusplus
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerBodyWorkPool_Destroy
void PlayerBodyWorkPool_Destroy(void);
#endif
#ifndef PROTO_LOCAL_PlayerBodyWork_GetHeapSize
u32 PlayerBodyWork_GetHeapSize(void);
#endif
#ifndef PROTO_LOCAL_PlayerBodyWorkRef_Destruct
void PlayerBodyWorkRef_Destruct(void);
#endif
#ifndef PROTO_LOCAL_PlayerBodyWorkRef_Assign
void PlayerBodyWorkRef_Assign(u8 *p, u8 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerBodyWorkPool_Create
void PlayerBodyWorkPool_Create(Heap *parent);
#endif
#ifndef PROTO_LOCAL_PlayerBodyWorkPool_CreateHeaps
void PlayerBodyWorkPool_CreateHeaps(Heap **tbl);
#endif
#ifndef PROTO_LOCAL_PlayerBodyWorkPool_DestroyHeaps
void PlayerBodyWorkPool_DestroyHeaps(Heap **tbl);
#endif
#ifndef PROTO_LOCAL_PlayerBodyWorkPool_GetHeap
Heap *PlayerBodyWorkPool_GetHeap(Heap **base, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerBodyWorkRef_GetHeap
Heap *PlayerBodyWorkRef_GetHeap(u8 *p);
#endif
}
#ifndef PROTO_LOCAL_sPlayerBodyWorkPool
extern PlayerBodyWorkPool sPlayerBodyWorkPool;
#endif
#endif

#endif
