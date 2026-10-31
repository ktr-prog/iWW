#ifndef PROTO_PROTO_MAIN_UNK_0203C638_H
#define PROTO_PROTO_MAIN_UNK_0203C638_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ClothTex_Construct
void ClothTex_Construct();
#endif
#ifndef PROTO_LOCAL_ClothTex_Destruct
void ClothTex_Destruct();
#endif
#ifndef PROTO_LOCAL_ClothTex_LoadItem
BOOL ClothTex_LoadItem(void *self, u16 *p, void *q);
#endif
#ifndef PROTO_LOCAL_ClothTex_LoadPattern
BOOL ClothTex_LoadPattern(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_ClothTex_GetTexData
void *ClothTex_GetTexData(void *tex);
#endif
#ifndef PROTO_LOCAL_ClothTex_GetPlttData
void *ClothTex_GetPlttData(void *tex);
#endif
#ifndef PROTO_LOCAL_ClothTex_GetTex
void *ClothTex_GetTex(void *tex);
#endif
#ifndef PROTO_LOCAL_ClothTex_GetBufferSize
u32 ClothTex_GetBufferSize();
#endif
#ifndef PROTO_LOCAL_ClothTex_LoadItemThunk
BOOL ClothTex_LoadItemThunk(void *a, u16 *b, void *c);
#endif
#ifndef PROTO_LOCAL_ClothTex_LoadPatternThunk
BOOL ClothTex_LoadPatternThunk(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_ClothTex_GetTexThunk
void *ClothTex_GetTexThunk(void *tex);
#endif
#ifndef PROTO_LOCAL_Catalog_Construct
void Catalog_Construct();
#endif
#ifndef PROTO_LOCAL_Catalog_Destruct
void Catalog_Destruct();
#endif
#ifdef __cplusplus
}
#endif

#endif
