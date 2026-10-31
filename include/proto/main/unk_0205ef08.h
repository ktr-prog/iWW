#ifndef PROTO_PROTO_MAIN_UNK_0205EF08_H
#define PROTO_PROTO_MAIN_UNK_0205EF08_H


#include "types.h"
struct PlayerPalettePool;
#ifndef __cplusplus
typedef struct PlayerPalettePool PlayerPalettePool;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ItemSync_Apply
BOOL ItemSync_Apply(u8 *p);
#endif
#ifndef PROTO_LOCAL_ItemSync_ApplyAndBroadcast
void ItemSync_ApplyAndBroadcast(u8 *p);
#endif
#ifndef PROTO_LOCAL_ItemSync_SetAtUnit
void ItemSync_SetAtUnit(s32 a, s32 b, s32 c, s32 d, s32 e);
#endif
#ifndef PROTO_LOCAL_PlayerPalettePool_Destroy
void PlayerPalettePool_Destroy();
#endif
#ifndef PROTO_LOCAL_PlayerPalette_GetPath
char *PlayerPalette_GetPath(u32 x);
#endif
#ifndef PROTO_LOCAL_PlayerPalette_GetSkinSize
s32 PlayerPalette_GetSkinSize();
#endif
#ifndef PROTO_LOCAL_PlayerPalette_GetHairSize
s32 PlayerPalette_GetHairSize();
#endif
#ifndef PROTO_LOCAL_PlayerPalette_GetSlotSize
s32 PlayerPalette_GetSlotSize();
#endif
#ifndef PROTO_LOCAL_PlayerPalettePool_AllocBuffers
void PlayerPalettePool_AllocBuffers(u8 **out);
#endif
#ifndef PROTO_LOCAL_PlayerPalettePool_FreeBuffers
void PlayerPalettePool_FreeBuffers(u8 **a);
#endif
#ifndef PROTO_LOCAL_PlayerPalettePool_GetBuffer
u8 *PlayerPalettePool_GetBuffer(u8 **a, u32 i);
#endif
#ifndef PROTO_LOCAL_PlayerPaletteRef_Assign
void PlayerPaletteRef_Assign(u8 *p, u8 v);
#endif
#ifndef PROTO_LOCAL_PlayerPaletteRef_SetSlot
void PlayerPaletteRef_SetSlot(u8 *p, u8 v);
#endif
#ifndef PROTO_LOCAL_PlayerPaletteRef_GetSkin
u8 *PlayerPaletteRef_GetSkin(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerPaletteRef_GetHair
u8 *PlayerPaletteRef_GetHair(u8 *p);
#endif
#ifndef PROTO_LOCAL_PlayerPaletteRef_LoadSkin
void PlayerPaletteRef_LoadSkin(u8 *x, u32 y);
#endif
#ifndef PROTO_LOCAL_PlayerPaletteRef_LoadHair
void PlayerPaletteRef_LoadHair(u8 *x, u32 y);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Fishing_StepArc
BOOL Fishing_StepArc(VecFx32 *a, s32 k, VecFx32 *b, s32 *c, u8 flag);
#endif
#ifndef PROTO_LOCAL_PlayerPalettePool_Create
void PlayerPalettePool_Create(Heap *parent);
#endif
}
#ifndef PROTO_LOCAL_sPlayerPalettePool
extern PlayerPalettePool sPlayerPalettePool;
#endif
#ifndef PROTO_LOCAL_sPlayerPalettePathBuf
extern char sPlayerPalettePathBuf[0x14];
#endif
#endif

#endif
