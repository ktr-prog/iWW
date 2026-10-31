#ifndef PROTO_PROTO_MAIN_UNK_02039C08_H
#define PROTO_PROTO_MAIN_UNK_02039C08_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_LostAndFound_Add
void LostAndFound_Add(u16 v);
#endif
#ifndef PROTO_LOCAL_LostAndFound_HasAny
BOOL LostAndFound_HasAny();
#endif
#ifndef PROTO_LOCAL_LostAndFound_Count
s32 LostAndFound_Count();
#endif
#ifndef PROTO_LOCAL_RecycleBin_Add
BOOL RecycleBin_Add(u16 v);
#endif
#ifndef PROTO_LOCAL_RecycleBin_Get
u16 RecycleBin_Get(u32 i);
#endif
#ifndef PROTO_LOCAL_RecycleBin_Set
BOOL RecycleBin_Set(u32 i, u16 v);
#endif
#ifndef PROTO_LOCAL_ChestStorage_Construct
void ChestStorage_Construct();
#endif
#ifndef PROTO_LOCAL_ChestStorage_Destruct
void ChestStorage_Destruct();
#endif
#ifndef PROTO_LOCAL_ChestStorage_Clear
void ChestStorage_Clear(u16 *p);
#endif
#ifndef PROTO_LOCAL_ChestStorage_GetItems
u16 *ChestStorage_GetItems(u16 *p);
#endif
#ifndef PROTO_LOCAL_LostAndFound_Construct
void LostAndFound_Construct();
#endif
#ifndef PROTO_LOCAL_LostAndFound_Destruct
void LostAndFound_Destruct();
#endif
#ifndef PROTO_LOCAL_LostAndFound_Clear
void LostAndFound_Clear(u16 *p);
#endif
#ifndef PROTO_LOCAL_LostAndFound_InitRandom
void LostAndFound_InitRandom(u16 *p);
#endif
#ifndef PROTO_LOCAL_LostAndFound_AddDailyItems
void LostAndFound_AddDailyItems(u16 *arr, s32 n);
#endif
#ifdef __cplusplus
}
#endif

#endif
