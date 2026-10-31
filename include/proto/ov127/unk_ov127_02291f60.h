#ifndef PROTO_PROTO_OV127_UNK_OV127_02291F60_H
#define PROTO_PROTO_OV127_UNK_OV127_02291F60_H


#include "types.h"
#include "nitro/gxoam.h"
#ifdef __cplusplus
#include "game/ConstellationRecord.h"
#include "game/StarSkyView.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_StarSky_LoadObjGraphics
void StarSky_LoadObjGraphics();
#endif
#ifndef PROTO_LOCAL_StarSky_GetStarAt
s32 StarSky_GetStarAt(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_StarSky_GetStarAtCellIndex
s32 StarSky_GetStarAtCellIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_StarSky_GetLineAt
s32 StarSky_GetLineAt(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_StarSky_GetLineAtCellIndex
s32 StarSky_GetLineAtCellIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_StarSky_GetLinesAround
s32 StarSky_GetLinesAround(u16 *out, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_StarSky_GetStarX
u32 StarSky_GetStarX(s32 i);
#endif
#ifndef PROTO_LOCAL_StarSky_GetStarY
u32 StarSky_GetStarY(s32 i);
#endif
#ifndef PROTO_LOCAL_StarSky_GetLineStars
const u8 *StarSky_GetLineStars(u16 i);
#endif
#ifndef PROTO_LOCAL_StarSky_FindConstellationByLine
s32 StarSky_FindConstellationByLine(u16 v);
#endif
#ifndef PROTO_LOCAL_data_ov127_02293fa4
extern GXOamAttr data_ov127_02293fa4[1];
#endif
#ifndef PROTO_LOCAL_data_ov127_02293fac
extern GXOamAttr data_ov127_02293fac[1];
#endif
#ifndef PROTO_LOCAL_data_ov127_02293fb4
extern s32 data_ov127_02293fb4[4];
#endif
#ifndef PROTO_LOCAL_data_ov127_02293fc4
extern s32 data_ov127_02293fc4[4];
#endif
#ifndef PROTO_LOCAL_data_ov127_02293fd4
extern GXOamAttr data_ov127_02293fd4[4];
#endif
#ifndef PROTO_LOCAL_sTestedConstellationStars
extern u8 sTestedConstellationStars[0x11];
#endif
#ifndef PROTO_LOCAL_sSavedConstellationStars
extern u8 sSavedConstellationStars[0x11];
#endif
#ifndef PROTO_LOCAL_data_ov127_02293fa0
extern u8 data_ov127_02293fa0[4];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_StarSky_Reset
void StarSky_Reset(StarSkyView *s);
#endif
#ifndef PROTO_LOCAL_StarSky_LoadSkyBg
void StarSky_LoadSkyBg(StarSkyView *s, u32 v);
#endif
#ifndef PROTO_LOCAL_StarSky_LoadScopeBg
void StarSky_LoadScopeBg(StarSkyView *s, u32 v);
#endif
#ifndef PROTO_LOCAL_StarSky_Update
void StarSky_Update(StarSkyView *s);
#endif
#ifndef PROTO_LOCAL_StarSky_CancelUpload
void StarSky_CancelUpload(StarSkyView *s);
#endif
#ifndef PROTO_LOCAL_StarSky_DrawArrows
void StarSky_DrawArrows(StarSkyView *s, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_StarSky_DrawScopeSprite
void StarSky_DrawScopeSprite(StarSkyView *s, s32 y);
#endif
#ifndef PROTO_LOCAL_StarSky_DrawStarMarker
void StarSky_DrawStarMarker(StarSkyView *s, s32 i);
#endif
#ifndef PROTO_LOCAL_StarSky_HitArrow
s32 StarSky_HitArrow(StarSkyView *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_StarSky_ScrollByDir
void StarSky_ScrollByDir(StarSkyView *s, s32 mode, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_StarSky_ScrollInDir
void StarSky_ScrollInDir(StarSkyView *s, s32 d, s32 e);
#endif
#ifndef PROTO_LOCAL_StarSky_StartBounce
void StarSky_StartBounce(StarSkyView *s, s32 d);
#endif
#ifndef PROTO_LOCAL_StarSky_UpdateBounce
BOOL StarSky_UpdateBounce(StarSkyView *s);
#endif
#ifndef PROTO_LOCAL_StarSky_ScrollX
void StarSky_ScrollX(StarSkyView *s, s32 a);
#endif
#ifndef PROTO_LOCAL_StarSky_ScrollY
BOOL StarSky_ScrollY(StarSkyView *s, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_StarSky_SetScroll
void StarSky_SetScroll(StarSkyView *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_StarSky_ScreenToCell
BOOL StarSky_ScreenToCell(StarSkyView *s, s32 x, s32 y, s32 *ox, s32 *oy);
#endif
#ifndef PROTO_LOCAL_StarSky_ScreenToCellInScope
s32 StarSky_ScreenToCellInScope(StarSkyView *s, s32 x, s32 y, s32 *ox, s32 *oy);
#endif
#ifndef PROTO_LOCAL_StarSky_RebuildScreen
void StarSky_RebuildScreen(StarSkyView *s, u32 slot, s32 r);
#endif
#ifndef PROTO_LOCAL_StarSky_SetScrollTarget
void StarSky_SetScrollTarget(StarSkyView *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_StarSky_StepToTarget
void StarSky_StepToTarget(StarSkyView *s);
#endif
#ifndef PROTO_LOCAL_StarSky_GetOverscroll
s32 StarSky_GetOverscroll(StarSkyView *s);
#endif
#ifndef PROTO_LOCAL_StarSky_GetScrollX
s32 StarSky_GetScrollX(StarSkyView *s);
#endif
#ifndef PROTO_LOCAL_StarSky_GetScrollY
s32 StarSky_GetScrollY(StarSkyView *s);
#endif
#ifndef PROTO_LOCAL_StarSky_HasFlags
BOOL StarSky_HasFlags(StarSkyView *s, u32 m);
#endif
#ifndef PROTO_LOCAL_StarSky_SetFlags
void StarSky_SetFlags(StarSkyView *s, u32 m);
#endif
#ifndef PROTO_LOCAL_StarSky_ClearFlags
void StarSky_ClearFlags(StarSkyView *s, u32 m);
#endif
#ifndef PROTO_LOCAL_StarSky_CollectStars
void StarSky_CollectStars(ConstellationRecord *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_StarSky_IsConstellationFree
BOOL StarSky_IsConstellationFree(ConstellationRecord *p);
#endif
}
#endif

#endif
