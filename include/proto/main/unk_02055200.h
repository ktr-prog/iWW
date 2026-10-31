#ifndef PROTO_PROTO_MAIN_UNK_02055200_H
#define PROTO_PROTO_MAIN_UNK_02055200_H


#include "types.h"
#include "gfx/Mtx43.h"
struct ResCacheEntry;
#ifndef __cplusplus
typedef struct ResCacheEntry ResCacheEntry;
#endif
#ifdef __cplusplus
#include "gfx/Model.h"
#include "gfx/NNSG3dResTex.h"
#include "gfx/TexVramSlot.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ResCache_Init
void ResCache_Init(void);
#endif
#ifndef PROTO_LOCAL_ResCache_Destroy
void ResCache_Destroy(void);
#endif
#ifndef PROTO_LOCAL_ResCache_FindModel
void *ResCache_FindModel(u32 key);
#endif
#ifndef PROTO_LOCAL_ResCache_FindTex
void *ResCache_FindTex(u32 key);
#endif
#ifndef PROTO_LOCAL_Gfx3d_CopyModel
void *Gfx3d_CopyModel(u32 *a, void *heap);
#endif
#ifndef PROTO_LOCAL_ResCache_GetModel
void *ResCache_GetModel(u32 *a, u32 key);
#endif
#ifndef PROTO_LOCAL_Gfx3d_CopyTex
void *Gfx3d_CopyTex(void *a, void *heap);
#endif
#ifndef PROTO_LOCAL_ResCache_GetTex
void *ResCache_GetTex(void *a, u32 key);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Gfx3d_LoadTexWithKeys
BOOL Gfx3d_LoadTexWithKeys(NNSG3dResTex *a, u32 y, u32 z);
#endif
#ifndef PROTO_LOCAL_Gfx3d_LoadTex
BOOL Gfx3d_LoadTex(NNSG3dResTex *a, TexVramSlot *b);
#endif
#ifndef PROTO_LOCAL_Gfx3d_LoadPlttWithKey
BOOL Gfx3d_LoadPlttWithKey(NNSG3dResTex *a, u32 x);
#endif
#ifndef PROTO_LOCAL_Gfx3d_LoadPltt
BOOL Gfx3d_LoadPltt(NNSG3dResTex *a, TexVramSlot *b);
#endif
#ifndef PROTO_LOCAL_Gfx3d_LoadTexAndPltt
BOOL Gfx3d_LoadTexAndPltt(NNSG3dResTex *a, TexVramSlot *b);
#endif
#ifndef PROTO_LOCAL_Model_GetJointWorldMtx
BOOL Model_GetJointWorldMtx(Model *p, Mtx43 *a, s32 b);
#endif
}
#ifndef PROTO_LOCAL_sResCacheModelCount
extern s32 sResCacheModelCount;
#endif
#ifndef PROTO_LOCAL_sResCacheTexCount
extern s32 sResCacheTexCount;
#endif
#ifndef PROTO_LOCAL_sResCacheTexs
extern ResCacheEntry sResCacheTexs[0x3c];
#endif
#ifndef PROTO_LOCAL_sResCacheModels
extern ResCacheEntry sResCacheModels[0x96];
#endif
#endif

#endif
