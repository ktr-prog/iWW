#ifndef PROTO_PROTO_MAIN_UNK_0205D480_H
#define PROTO_PROTO_MAIN_UNK_0205D480_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/TexVramSlot.h"
#include "gfx/TexVramTask.h"
#include "sys/Heap.h"
class PlayerGlassesModelPool;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelPool_Destroy
void PlayerGlassesModelPool_Destroy();
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModel_GetPath
char *PlayerGlassesModel_GetPath(s32 x);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModel_GetBufferSize
s32 PlayerGlassesModel_GetBufferSize();
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModel_GetAccessoryModelId
u8 PlayerGlassesModel_GetAccessoryModelId(u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModel_GetFlowerModelId
u8 PlayerGlassesModel_GetFlowerModelId(u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModel_GetTexVramSize
s32 PlayerGlassesModel_GetTexVramSize();
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModel_GetTex4x4VramSize
s32 PlayerGlassesModel_GetTex4x4VramSize();
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModel_GetPlttVramSize
s32 PlayerGlassesModel_GetPlttVramSize();
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_Init
void PlayerGlassesModelRef_Init(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_Destruct
void PlayerGlassesModelRef_Destruct();
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_SetSlot
void PlayerGlassesModelRef_SetSlot(u8 *p, u8 v);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_Release
void PlayerGlassesModelRef_Release(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_CancelTexUpload
void PlayerGlassesModelRef_CancelTexUpload(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_Load
void PlayerGlassesModelRef_Load(u8 *p, s32 idx);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_RelocateTexture
void PlayerGlassesModelRef_RelocateTexture(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_PollTexUpload
BOOL PlayerGlassesModelRef_PollTexUpload(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_GetBuffer
void *PlayerGlassesModelRef_GetBuffer(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_GetModelId
u8 PlayerGlassesModelRef_GetModelId(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_SetModelId
void PlayerGlassesModelRef_SetModelId(u8 *p, s32 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerGlassesModelPool_Create
void PlayerGlassesModelPool_Create(Heap *parent);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_GetVramSlot
TexVramSlot *PlayerGlassesModelRef_GetVramSlot(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerGlassesModelRef_GetTexTask
TexVramTask *PlayerGlassesModelRef_GetTexTask(u8 *p);
#endif
}
#ifndef PROTO_LOCAL_sPlayerGlassesModelPathBuf
extern char sPlayerGlassesModelPathBuf[0x14];
#endif
#ifndef PROTO_LOCAL_sPlayerGlassesModelPool
extern PlayerGlassesModelPool sPlayerGlassesModelPool;
#endif
#endif

#endif
