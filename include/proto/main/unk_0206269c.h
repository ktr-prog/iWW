#ifndef PROTO_PROTO_MAIN_UNK_0206269C_H
#define PROTO_PROTO_MAIN_UNK_0206269C_H


#include "types.h"
#ifdef __cplusplus
#include "item/ItemPickSpec.h"
#include "item/RandomSource.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ItemPick_GetClassWeight
u8 ItemPick_GetClassWeight(u32 idx);
#endif
#ifndef PROTO_LOCAL_ItemPick_CalcDateSeed
u32 ItemPick_CalcDateSeed(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_ItemList_MakeFurniture
s32 ItemList_MakeFurniture(s32 a);
#endif
#ifndef PROTO_LOCAL_ItemList_MakePaper
u16 ItemList_MakePaper(u32 a);
#endif
#ifndef PROTO_LOCAL_ItemList_GetNoSeason
s32 ItemList_GetNoSeason(void);
#endif
#ifndef PROTO_LOCAL_Item_FindInArray
s32 Item_FindInArray(u16 *c, u16 *arr, u32 n);
#endif
#ifndef PROTO_LOCAL_ItemPick_SeasonMatches
BOOL ItemPick_SeasonMatches(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_ItemPick_GetSeason
s32 ItemPick_GetSeason(s32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_ItemPick_IsCatalogued
BOOL ItemPick_IsCatalogued(void *p, u16 *q);
#endif
#ifndef PROTO_LOCAL_ItemList_Find
s32 ItemList_Find(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_GetTownClassRank
s32 ItemList_GetTownClassRank(u16 *p, s32 mode);
#endif
#ifndef PROTO_LOCAL_Item_IsClass4Furniture
BOOL Item_IsClass4Furniture(u16 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ItemPick_FromLists
u32 ItemPick_FromLists(u16 *out, u32 n, ItemPickSpec *tbl, u32 x3, u8 *a4, RandomSource *rng, u32 a6, u32 a7, s32 *outp);
#endif
#ifndef PROTO_LOCAL_ItemPick_One
void ItemPick_One(u16 *out, ItemPickSpec *o, u8 *a, RandomSource *b, u8 c, u32 d, s32 *e);
#endif
#ifndef PROTO_LOCAL_ItemPick_OneEx
void ItemPick_OneEx(u16 *out, s32 one, ItemPickSpec *o, u8 *a, RandomSource *b, u8 c, u32 d, s32 *e);
#endif
#ifndef PROTO_LOCAL_ItemPick_OneSimple
void ItemPick_OneSimple(u16 *out, ItemPickSpec *o);
#endif
#ifndef PROTO_LOCAL_ItemPick_FillFromRange
BOOL ItemPick_FillFromRange(u16 *arr, u32 n, s32 base, u32 cnt, void *a4, s32 a5, s32 a6, RandomSource *a7, s32 a8);
#endif
#ifndef PROTO_LOCAL_ItemPick_FromRange
void ItemPick_FromRange(u16 *out, s32 base, u32 cnt, u16 *list, u32 listLen, void *a5, s32 a6, s32 a7, RandomSource *rng, s32 a9);
#endif
#ifndef PROTO_LOCAL_ItemPick_FtrWallCarpetByClass
void ItemPick_FtrWallCarpetByClass(u16 *out, u8 *a, RandomSource *rng);
#endif
}
#endif

#endif
