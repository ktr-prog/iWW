#ifndef PROTO_PROTO_MAIN_UNK_020AFEB4_H
#define PROTO_PROTO_MAIN_UNK_020AFEB4_H


#include "types.h"
#include "types64.h"
#ifdef __cplusplus
#include "game/SceneInfo.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sConstellationColumns
extern u32 sConstellationColumns[2];
#endif
#ifndef PROTO_LOCAL_Constellation_ClearColumns
void Constellation_ClearColumns(void);
#endif
#ifndef PROTO_LOCAL_Constellation_MarkColumn
void Constellation_MarkColumn(s32 n);
#endif
#ifndef PROTO_LOCAL_Constellation_TestColumn
BOOL Constellation_TestColumn(s32 n);
#endif
#ifndef PROTO_LOCAL_Constellation_CalcCentre
void Constellation_CalcCentre(u16 *p, s32 *outA, s32 *outB);
#endif
#ifndef PROTO_LOCAL_Constellation_FindFreeSlot
s32 Constellation_FindFreeSlot(void);
#endif
#ifndef PROTO_LOCAL_Constellation_CountFreeSlots
s32 Constellation_CountFreeSlots(void);
#endif
#ifndef PROTO_LOCAL_Constellation_Erase
void Constellation_Erase(s32 idx);
#endif
#ifndef PROTO_LOCAL_Constellation_SetCreator
void Constellation_SetCreator(u8 *dst);
#endif
#ifndef PROTO_LOCAL_Constellation_SetName
void Constellation_SetName(u8 *src, s32 idx);
#endif
#ifndef PROTO_LOCAL_Constellation_CopyName
void Constellation_CopyName(u8 *dst, s32 idx);
#endif
#ifndef PROTO_LOCAL_Constellation_GetName
BOOL Constellation_GetName(void *self, s32 idx);
#endif
#ifndef PROTO_LOCAL_Constellation_GetNewStatus
s32 Constellation_GetNewStatus(s32 *out);
#endif
#ifndef PROTO_LOCAL_Constellation_ClearNewFlags
void Constellation_ClearNewFlags(void);
#endif
#ifndef PROTO_LOCAL_Constellation_GetViewingTime
void Constellation_GetViewingTime(void *a, s32 idx);
#endif
#ifndef PROTO_LOCAL_Constellation_IsInView
BOOL Constellation_IsInView(s32 x, s32 y, s32 px, s32 py);
#endif
#ifndef PROTO_LOCAL_Constellation_FindVisibleNow
s32 Constellation_FindVisibleNow(void);
#endif
#ifndef PROTO_LOCAL_Constellation_AcquireSkyOverlay
void Constellation_AcquireSkyOverlay(void);
#endif
#ifndef PROTO_LOCAL_Constellation_ReleaseSkyOverlay
void Constellation_ReleaseSkyOverlay(void);
#endif
#ifndef PROTO_LOCAL_Constellation_PrepareExchange
void Constellation_PrepareExchange(void);
#endif
#ifndef PROTO_LOCAL_Constellation_ImportExchanged
void Constellation_ImportExchanged(void);
#endif
#ifndef PROTO_LOCAL_Constellation_IsNameTaken
BOOL Constellation_IsNameTaken(const u8 *name, s32 skip);
#endif
#ifndef PROTO_LOCAL_Constellation_IsLineTile
BOOL Constellation_IsLineTile(s32 n);
#endif
#ifndef PROTO_LOCAL_Constellation_CellToScreenIndex
s32 Constellation_CellToScreenIndex(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Constellation_SetLinePalette
void Constellation_SetLinePalette(u16 *p, u32 slot, s32 r);
#endif
#ifndef PROTO_LOCAL_Constellation_HighlightAll
void Constellation_HighlightAll(u16 *p);
#endif
#ifndef PROTO_LOCAL_Constellation_MaskSkyScreen
void Constellation_MaskSkyScreen(u16 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SceneSpawnGroup_SpawnActors
BOOL SceneSpawnGroup_SpawnActors(SceneSpawnGroup *self, u8 *idxp, u64 start);
#endif
}
#endif

#endif
