#ifndef PROTO_PROTO_MAIN_UNK_0208F268_H
#define PROTO_PROTO_MAIN_UNK_0208F268_H


#include "types.h"
#include "uptr.h"
struct EffectSplArchive;
struct EffectSplPool;
#ifndef __cplusplus
typedef struct EffectSplArchive EffectSplArchive;
typedef struct EffectSplPool EffectSplPool;
#endif
#ifdef __cplusplus
#include "gfx/EffectSplEmitter.h"
#include "gfx/VecFx32.h"
#include "sys/Heap.h"
class EffectModel;
class EffectModelGroup;
class EffectSplProc;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_EffectSpl_Alloc
void *EffectSpl_Alloc(u32 size);
#endif
#ifndef PROTO_LOCAL_EffectSpl_LoadArchive
void *EffectSpl_LoadArchive(void *unused);
#endif
#ifndef PROTO_LOCAL_EffectSpl_GetSeasonTint
s16 EffectSpl_GetSeasonTint();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_EffectSplProc_Create
EffectSplProc *EffectSplProc_Create();
#endif
#ifndef PROTO_LOCAL_EffectSpl_LoadTextures
BOOL EffectSpl_LoadTextures(EffectSplProc *p);
#endif
#ifndef PROTO_LOCAL_EffectSpl_CopyResourceData
void *EffectSpl_CopyResourceData(void *unused, EffectSplArchive *p);
#endif
#ifndef PROTO_LOCAL_EffectSpl_ToCurvedPos
u16 EffectSpl_ToCurvedPos(VecFx32 *pos, VecFx32 v);
#endif
#ifndef PROTO_LOCAL_EffectSpl_GetSeasonTintVariant
s16 EffectSpl_GetSeasonTintVariant(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectSpl_ApplySceneTint
void EffectSpl_ApplySceneTint(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectSpl_InitEmitterAtPos
void EffectSpl_InitEmitterAtPos(EffectSplEmitter *o);
#endif
#ifndef PROTO_LOCAL_EffectCb_InitAtPos
void EffectCb_InitAtPos(EffectEmitterEntry *e);
#endif
#ifndef PROTO_LOCAL_EffectCb_UpdateTint
s32 EffectCb_UpdateTint(EffectEmitterEntry *e);
#endif
#ifndef PROTO_LOCAL_EffectSpl_CreateOneShot
s32 EffectSpl_CreateOneShot(s32 idx, VecFx32 *p1, s16 *p2, void (*const *p3)(EffectSplEmitter *));
#endif
#ifndef PROTO_LOCAL_EffectSpl_CreateTracked
s32 EffectSpl_CreateTracked(s32 idx, VecFx32 *p1, s16 *p2, EffectEmitterCbs *p3);
#endif
#ifndef PROTO_LOCAL_EffectModel_Start
void EffectModel_Start(s32 a, void (*b)(EffectModel *));
#endif
#ifndef PROTO_LOCAL_EffectSplEntry_Start
s32 EffectSplEntry_Start(EffectEmitterEntry *e, s32 id, VecFx32 *a2, s16 *a3, EffectEmitterCbs *cb, EffectEmitterTag tag);
#endif
#ifndef PROTO_LOCAL_EffectSplEntry_Release
void EffectSplEntry_Release(EffectEmitterEntry *e);
#endif
#ifndef PROTO_LOCAL_EffectSplPool_Update
void EffectSplPool_Update(EffectSplPool *p);
#endif
#ifndef PROTO_LOCAL_EffectSplPool_ReleaseAll
void EffectSplPool_ReleaseAll(EffectSplPool *p);
#endif
#ifndef PROTO_LOCAL_EffectSplPool_FindInactive
EffectEmitterEntry *EffectSplPool_FindInactive(EffectSplPool *p, s32 id);
#endif
#ifndef PROTO_LOCAL_EffectSplPool_Alloc
EffectEmitterEntry *EffectSplPool_Alloc(EffectSplPool *p, s32 id, VecFx32 *a2, s16 *a3, EffectEmitterCbs *cb, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_EffectModels_LoadAll
void EffectModels_LoadAll(EffectModelGroup *b);
#endif
#ifndef PROTO_LOCAL_EffectModels_UpdateAll
void EffectModels_UpdateAll(EffectModelGroup *b);
#endif
#ifndef PROTO_LOCAL_EffectModels_DrawAll
void EffectModels_DrawAll(EffectModelGroup *b);
#endif
#ifndef PROTO_LOCAL_EffectModels_UnloadAll
void EffectModels_UnloadAll(EffectModelGroup *b);
#endif
#ifndef PROTO_LOCAL_EffectModels_Start
void EffectModels_Start(EffectModelGroup *b, s32 idx, void (*a)(EffectModel *));
#endif
#ifndef PROTO_LOCAL_EffectModelGroup_Load
void EffectModelGroup_Load(EffectModelGroup *b, s32 a);
#endif
#ifndef PROTO_LOCAL_EffectModelGroup_Update
void EffectModelGroup_Update(EffectModelGroup *b);
#endif
#ifndef PROTO_LOCAL_EffectModelGroup_Draw
void EffectModelGroup_Draw(EffectModelGroup *b);
#endif
#ifndef PROTO_LOCAL_EffectModelGroup_Unload
void EffectModelGroup_Unload(EffectModelGroup *b);
#endif
#ifndef PROTO_LOCAL_EffectModelGroup_Start
void EffectModelGroup_Start(EffectModelGroup *b, void (*a)(EffectModel *));
#endif
}
#ifndef PROTO_LOCAL_sEffectSeasonTint0
extern s16 sEffectSeasonTint0[24];
#endif
#ifndef PROTO_LOCAL_sEffectSeasonTint1
extern s16 sEffectSeasonTint1[24];
#endif
#ifndef PROTO_LOCAL_sEffectSeasonTint2
extern s16 sEffectSeasonTint2[24];
#endif
#ifndef PROTO_LOCAL_sEffectSeasonTint3
extern s16 sEffectSeasonTint3[24];
#endif
#ifndef PROTO_LOCAL_sEffectSeasonTint
extern s16 sEffectSeasonTint[24];
#endif
#ifndef PROTO_LOCAL_sEffectModelAnimFiles
extern char *sEffectModelAnimFiles[4][3];
#endif
#ifndef PROTO_LOCAL_gEffectSplDefaultInitCbs
extern void (*gEffectSplDefaultInitCbs[10]) (EffectSplEmitter *);
#endif
#ifndef PROTO_LOCAL_sPathEfWaterColNsbca
extern char sPathEfWaterColNsbca[];
#endif
#ifndef PROTO_LOCAL_sPathEfWaterColNsbma
extern char sPathEfWaterColNsbma[];
#endif
#ifndef PROTO_LOCAL_sPathEfWaterColNsbmd
extern char sPathEfWaterColNsbmd[];
#endif
#ifndef PROTO_LOCAL_sPathCraRibbon1Nsbmd
extern char sPathCraRibbon1Nsbmd[];
#endif
#ifndef PROTO_LOCAL_sPathCraRibbon1Nsbca
extern char sPathCraRibbon1Nsbca[];
#endif
#ifndef PROTO_LOCAL_sPathCraRibbon1Nsbma
extern char sPathCraRibbon1Nsbma[];
#endif
#ifndef PROTO_LOCAL_sPathMpSiturenNsbma
extern char sPathMpSiturenNsbma[];
#endif
#ifndef PROTO_LOCAL_sPathMpSiturenNsbva
extern char sPathMpSiturenNsbva[];
#endif
#ifndef PROTO_LOCAL_sPathMpSiturenNsbmd
extern char sPathMpSiturenNsbmd[];
#endif
#ifndef PROTO_LOCAL_sPathMpSiturenNsbca
extern char sPathMpSiturenNsbca[];
#endif
#ifndef PROTO_LOCAL_sPathMpLoveNsbca
extern char sPathMpLoveNsbca[];
#endif
#ifndef PROTO_LOCAL_sPathMpLoveNsbma
extern char sPathMpLoveNsbma[];
#endif
#ifndef PROTO_LOCAL_sPathMpLoveNsbmd
extern char sPathMpLoveNsbmd[];
#endif
#ifndef PROTO_LOCAL_sEffectModelFiles
extern uptr sEffectModelFiles[4];
#endif
#ifndef PROTO_LOCAL_sEffectSeasonTintTables
extern s16 *sEffectSeasonTintTables[4];
#endif
#ifndef PROTO_LOCAL_sEffectSplEmitPos
extern s32 *sEffectSplEmitPos;
#endif
#ifndef PROTO_LOCAL_sEffectSplHeapMem
extern void *sEffectSplHeapMem;
#endif
#ifndef PROTO_LOCAL_sEffectSplFrmHeap
extern void *sEffectSplFrmHeap;
#endif
#ifndef PROTO_LOCAL_sEffectModelHeap
extern Heap *sEffectModelHeap;
#endif
#ifndef PROTO_LOCAL_sEffectSplProc
extern EffectSplProc *sEffectSplProc;
#endif
#endif

#endif
