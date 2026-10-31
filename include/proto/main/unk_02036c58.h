#ifndef PROTO_PROTO_MAIN_UNK_02036C58_H
#define PROTO_PROTO_MAIN_UNK_02036C58_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/BgModelCache.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BgModel_LoadFile
void *BgModel_LoadFile(const char *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_BgModel_GetGrassType
s32 BgModel_GetGrassType(void *);
#endif
#ifndef PROTO_LOCAL_BgModel_LoadBcl
void *BgModel_LoadBcl(s32 id, void *heap);
#endif
#ifndef PROTO_LOCAL_BgMgt_GetCount
s32 BgMgt_GetCount(s16 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_BgModelCache_Get
BgModelCache *BgModelCache_Get(void);
#endif
}
#ifndef PROTO_LOCAL_BgMgt_GetEntry
VecFx32 BgMgt_GetEntry(u8 *base, s32 idx);
#endif
#ifndef PROTO_LOCAL_gBgModelCache
extern BgModelCache gBgModelCache;
#endif
#endif

#endif
