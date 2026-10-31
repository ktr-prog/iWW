#ifndef PROTO_PROTO_MAIN_UNK_02037358_H
#define PROTO_PROTO_MAIN_UNK_02037358_H


#include "types.h"
#include "game/Unk_02037674_V3.h"
struct Marker1;
#ifndef __cplusplus
typedef struct Marker1 Marker1;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "town/MapBlock.h"
struct BgAcreModel;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_MapBlock_SetItem
BOOL MapBlock_SetItem(void *cell, u16 *t, u32 x, u32 y, u8 z);
#endif
#ifndef PROTO_LOCAL_MapBlock_GetItemPtr
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
#endif
#ifndef PROTO_LOCAL_Unit_SplitIndex
void Unit_SplitIndex(s32 *a, s32 *b, s32 v);
#endif
#ifndef PROTO_LOCAL_BuriedMask_Construct
void BuriedMask_Construct();
#endif
#ifndef PROTO_LOCAL_BuriedMask_Destruct
void BuriedMask_Destruct();
#endif
#ifndef PROTO_LOCAL_BuriedMask_Reset
void BuriedMask_Reset(void *p);
#endif
#ifndef PROTO_LOCAL_Bits16_Set
BOOL Bits16_Set(void *, u16 *p, s32 bit);
#endif
#ifndef PROTO_LOCAL_Bits16_Clear
BOOL Bits16_Clear(void *, u16 *p, s32 bit);
#endif
#ifndef PROTO_LOCAL_BuriedMask_Set
BOOL BuriedMask_Set(void *base, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_BuriedMask_Clear
BOOL BuriedMask_Clear(void *base, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_AcreAttr_Load
BOOL AcreAttr_Load();
#endif
#ifndef PROTO_LOCAL_AcreAttr_Unload
BOOL AcreAttr_Unload();
#endif
#ifndef PROTO_LOCAL_AcreAttr_GetType
u32 AcreAttr_GetType(u32 i);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_MapBlock_Init
void MapBlock_Init(MapBlock *self, s32 a, VecFx32 *v, u16 *layer0, u16 *layer1, u16 *buriedMask, BgAcreModel *k2, void *bcl, Unk_02037638_S8 *k45, u32 mapSlot);
#endif
#ifndef PROTO_LOCAL_MapBlock_NewArray
MapBlock *MapBlock_NewArray(s32 n, void *heap, s32 x);
#endif
#ifndef PROTO_LOCAL_MapBlock_FindItemInRange
BOOL MapBlock_FindItemInRange(void *cell, s32 *a, s32 *b, Marker1 *m, Marker1 *c, u8 d);
#endif
#ifndef PROTO_LOCAL_MapBlock_GetAttr
u32 MapBlock_GetAttr(MapBlock *o);
#endif
#ifndef PROTO_LOCAL_MapBlock_HasAllAttr
BOOL MapBlock_HasAllAttr(MapBlock *o, u32 mask);
#endif
#ifndef PROTO_LOCAL_MapBlock_HasAnyAttr
BOOL MapBlock_HasAnyAttr(MapBlock *o, u32 mask);
#endif
#ifndef PROTO_LOCAL_MapBlock_SetBuried
BOOL MapBlock_SetBuried(MapBlock *o, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_MapBlock_ClearBuried
BOOL MapBlock_ClearBuried(MapBlock *o, u32 a, u32 b);
#endif
}
#ifndef PROTO_LOCAL_sAcreAttrData
extern u8 *sAcreAttrData;
#endif
#ifndef PROTO_LOCAL_sAcreAttrSize
extern u32 sAcreAttrSize;
#endif
#endif

#endif
