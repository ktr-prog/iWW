#ifndef PROTO_PROTO_MAIN_UNK_0205D7D8_H
#define PROTO_PROTO_MAIN_UNK_0205D7D8_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/TexVramSlot.h"
#include "gfx/TexVramTask.h"
#include "player/HeldItemModel.h"
#include "sys/Heap.h"
class PlayerHeadBank;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerHeadBank_Destroy
void PlayerHeadBank_Destroy(void);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetModelPath
char *PlayerHead_GetModelPath(u32 a);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetHairModelId
u32 PlayerHead_GetHairModelId(u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetHatHairModelId
u32 PlayerHead_GetHatHairModelId(u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetHatModelId
u32 PlayerHead_GetHatModelId(u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetFullHeadwearModelId
u32 PlayerHead_GetFullHeadwearModelId(u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetFlowerModelId
u32 PlayerHead_GetFlowerModelId(u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetModelIds
void PlayerHead_GetModelIds(s32 flag, u32 a, u16 *p, u32 *o1, u32 *o2);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetBufferSize
s32 PlayerHead_GetBufferSize(void);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetTexVramSize
s32 PlayerHead_GetTexVramSize(void);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetTex4x4VramSize
s32 PlayerHead_GetTex4x4VramSize(void);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetPlttVramSize
s32 PlayerHead_GetPlttVramSize(void);
#endif
#ifndef PROTO_LOCAL_PlayerHead_SetSlot
void PlayerHead_SetSlot(u8 *p, u8 v);
#endif
#ifndef PROTO_LOCAL_PlayerHead_Release
void PlayerHead_Release(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerHead_CancelTexUpload
void PlayerHead_CancelTexUpload(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerHead_Load
s32 PlayerHead_Load(u8 *p, s32 a, s32 b, u16 *c, void *d);
#endif
#ifndef PROTO_LOCAL_PlayerHead_RelocateTextures
void PlayerHead_RelocateTextures(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerHead_PollTexUpload
BOOL PlayerHead_PollTexUpload(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetBuffer
void *PlayerHead_GetBuffer(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetModelFile
void *PlayerHead_GetModelFile(u8 *p, s32 j);
#endif
#ifndef PROTO_LOCAL_PlayerHead_SetModelFile
void PlayerHead_SetModelFile(u8 *p, s32 j, void *v);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetModelId
s32 PlayerHead_GetModelId(u8 *p, s32 j);
#endif
#ifndef PROTO_LOCAL_PlayerHead_SetModelId
void PlayerHead_SetModelId(u8 *p, s32 j, u32 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_HeldItemModel_IsBobberLanded
BOOL HeldItemModel_IsBobberLanded(HeldItemModel *p);
#endif
#ifndef PROTO_LOCAL_PlayerHeadBank_Init
void PlayerHeadBank_Init(Heap *parent);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetVramSlot
TexVramSlot *PlayerHead_GetVramSlot(u8 *p, s32 j);
#endif
#ifndef PROTO_LOCAL_PlayerHead_GetTexTask
TexVramTask *PlayerHead_GetTexTask(u8 *p, s32 j);
#endif
}
#ifndef PROTO_LOCAL_sPlayerHeadPathBuf
extern char sPlayerHeadPathBuf[0x14];
#endif
#ifndef PROTO_LOCAL_sPlayerHeadBank
extern PlayerHeadBank sPlayerHeadBank;
#endif
#endif

#endif
