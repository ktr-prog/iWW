#ifndef PROTO_PROTO_MAIN_UNK_0205C66C_H
#define PROTO_PROTO_MAIN_UNK_0205C66C_H


#include "types.h"
struct PlayerBodyModelPool;
#ifndef __cplusplus
typedef struct PlayerBodyModelPool PlayerBodyModelPool;
#endif
#ifdef __cplusplus
#include "gfx/TexVramTask.h"
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelPool_Destroy
void PlayerBodyModelPool_Destroy();
#endif
#ifndef PROTO_LOCAL_PlayerBodyModel_GetPath
char *PlayerBodyModel_GetPath(u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModel_GetBufferSize
u32 PlayerBodyModel_GetBufferSize();
#endif
#ifndef PROTO_LOCAL_PlayerBodyModel_GetTexVramSize
u32 PlayerBodyModel_GetTexVramSize();
#endif
#ifndef PROTO_LOCAL_PlayerBodyModel_GetTex4x4VramSize
u32 PlayerBodyModel_GetTex4x4VramSize();
#endif
#ifndef PROTO_LOCAL_PlayerBodyModel_GetPlttVramSize
u32 PlayerBodyModel_GetPlttVramSize();
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_Init
void PlayerBodyModelRef_Init(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_Destruct
void PlayerBodyModelRef_Destruct();
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_SetSlot
void PlayerBodyModelRef_SetSlot(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_CancelTexUpload
void PlayerBodyModelRef_CancelTexUpload(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_Load
s32 PlayerBodyModelRef_Load(u8 *p, u32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_RelocateTexture
void PlayerBodyModelRef_RelocateTexture(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_PollTexUpload
s32 PlayerBodyModelRef_PollTexUpload(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_GetBuffer
void *PlayerBodyModelRef_GetBuffer(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_GetVramSlot
void *PlayerBodyModelRef_GetVramSlot(u8 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerBodyModelPool_Create
void PlayerBodyModelPool_Create(Heap *parent);
#endif
#ifndef PROTO_LOCAL_PlayerBodyModelRef_GetTexTask
TexVramTask *PlayerBodyModelRef_GetTexTask(u8 *p);
#endif
}
#ifndef PROTO_LOCAL_sPlayerBodyModelPool
extern PlayerBodyModelPool sPlayerBodyModelPool;
#endif
#ifndef PROTO_LOCAL_sPlayerBodyModelPaths
extern char *sPlayerBodyModelPaths[];
#endif
#endif

#endif
