#ifndef PROTO_PROTO_MAIN_UNK_0203C23C_H
#define PROTO_PROTO_MAIN_UNK_0203C23C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Catalog_GetBit
u8 *Catalog_GetBit(u8 *base, u8 *out, u16 *p);
#endif
#ifndef PROTO_LOCAL_Catalog_HasItem
BOOL Catalog_HasItem(u8 *base, u16 *p);
#endif
#ifndef PROTO_LOCAL_Catalog_SetItem
BOOL Catalog_SetItem(u8 *base, u16 *p, s32 skip, s32 set);
#endif
#ifndef PROTO_LOCAL_Catalog_AddItem
BOOL Catalog_AddItem(void *a, u16 *p, s32 c);
#endif
#ifndef PROTO_LOCAL_Catalog_CountRange
s32 Catalog_CountRange(u16 base, u32 n);
#endif
#ifndef PROTO_LOCAL_Catalog_HasAllFish
BOOL Catalog_HasAllFish();
#endif
#ifndef PROTO_LOCAL_Catalog_HasAllInsects
BOOL Catalog_HasAllInsects();
#endif
#ifndef PROTO_LOCAL_Catalog_GetFishTotal
s32 Catalog_GetFishTotal();
#endif
#ifndef PROTO_LOCAL_Catalog_GetInsectTotal
s32 Catalog_GetInsectTotal();
#endif
#ifndef PROTO_LOCAL_Catalog_CountFish
s32 Catalog_CountFish();
#endif
#ifndef PROTO_LOCAL_Catalog_CountInsects
s32 Catalog_CountInsects();
#endif
#ifndef PROTO_LOCAL_Catalog_AddCreature
BOOL Catalog_AddCreature(u16 *p);
#endif
#ifndef PROTO_LOCAL_CarpetTex_Init
void *CarpetTex_Init(void *p);
#endif
#ifndef PROTO_LOCAL_CarpetTex_Load
BOOL CarpetTex_Load(void *a, u16 *p);
#endif
#ifdef __cplusplus
}
#endif

#endif
