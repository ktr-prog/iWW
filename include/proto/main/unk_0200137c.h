#ifndef PROTO_PROTO_MAIN_UNK_0200137C_H
#define PROTO_PROTO_MAIN_UNK_0200137C_H


#include "types.h"
struct Gfx2dAffine;
struct Gfx2dOffset;
struct Gfx2dState;
struct Gfx2dWindowRect;
#ifndef __cplusplus
typedef struct Gfx2dAffine Gfx2dAffine;
typedef struct Gfx2dOffset Gfx2dOffset;
typedef struct Gfx2dState Gfx2dState;
typedef struct Gfx2dWindowRect Gfx2dWindowRect;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Gfx2d_GetLayerBgIndex
s32 Gfx2d_GetLayerBgIndex(u32 n);
#endif
#ifndef PROTO_LOCAL_Gfx2d_GetLayerPlaneMask
s32 Gfx2d_GetLayerPlaneMask(u32 n);
#endif
#ifndef PROTO_LOCAL_Gfx2d_GetLayerBlendMask
s32 Gfx2d_GetLayerBlendMask(u32 n);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadPaletteFile
s32 Gfx2d_LoadPaletteFile(const char *p0, void *p1, u32 p2, s32 p3, u8 e, u8 f);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadPaletteFileSlot
s32 Gfx2d_LoadPaletteFileSlot(const char *p0, void *p1, u32 p2, s32 p3, u8 e);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadScreenFile
s32 Gfx2d_LoadScreenFile(const char *p0, void *p1, u32 p2);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadCharFile
s32 Gfx2d_LoadCharFile(const char *p0, void *p1, u32 p2, s32 p3, s32 e, s32 f);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadCharFile8bpp
s32 Gfx2d_LoadCharFile8bpp(const char *p0, void *p1, u32 p2, s32 p3, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadPaletteRange
s32 Gfx2d_LoadPaletteRange(u8 *dst, u32 n, s32 a, s32 b, u8 c);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadScreen
s32 Gfx2d_LoadScreen(u8 *dst, u32 n, s32 size, s32 x);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadCharRange
s32 Gfx2d_LoadCharRange(u8 *dst, u32 n, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetLayerPriority
void Gfx2d_SetLayerPriority(u32 n, u32 v);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetLayerControl
void Gfx2d_SetLayerControl(u32 n, u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetLayerOffset
void Gfx2d_SetLayerOffset(u32 n, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetWindowRect
void Gfx2d_SetWindowRect(u32 n, u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Gfx2d_ResetLayer
void Gfx2d_ResetLayer(u32 n);
#endif
#ifndef PROTO_LOCAL_Gfx2d_HideLayer
void Gfx2d_HideLayer(u32 n);
#endif
#ifndef PROTO_LOCAL_Gfx2d_ShowLayer
void Gfx2d_ShowLayer(u32 n);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LinearToTiles4bppBytes
void Gfx2d_LinearToTiles4bppBytes(u8 *src, u8 *dst, s32 w, s32 h);
#endif
#ifndef PROTO_LOCAL_Gfx2d_TilesInRow32ToLinear
void Gfx2d_TilesInRow32ToLinear(u32 *src, u32 *dst, s32 x, s32 w, s32 h);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LinearToTilesInRow32
void Gfx2d_LinearToTilesInRow32(u32 *src, u32 *dst, s32 x, s32 w, s32 h);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LinearToTiles4bpp
void Gfx2d_LinearToTiles4bpp(u32 *src, u32 *dst, s32 w, s32 h);
#endif
#ifndef PROTO_LOCAL_Gfx2d_TilesToLinear4bpp
void Gfx2d_TilesToLinear4bpp(u32 *src, u32 *dst, s32 w, s32 h);
#endif
#ifndef PROTO_LOCAL_Gfx2d_LoadBackdropColor
void Gfx2d_LoadBackdropColor(void);
#endif
#ifndef PROTO_LOCAL_Gfx2d_ResetState
void Gfx2d_ResetState();
#endif
#ifndef PROTO_LOCAL_Gfx2d_BeginFrame
void Gfx2d_BeginFrame();
#endif
#ifndef PROTO_LOCAL_Gfx2d_ApplyDisplayControl
void Gfx2d_ApplyDisplayControl();
#endif
#ifndef PROTO_LOCAL_Gfx2d_FlushRegisters
void Gfx2d_FlushRegisters();
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainBg1Offset
void Gfx2d_SetMainBg1Offset(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainBg2Offset
void Gfx2d_SetMainBg2Offset(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainBg3Offset
void Gfx2d_SetMainBg3Offset(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubBg0Offset
void Gfx2d_SetSubBg0Offset(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubBg1Offset
void Gfx2d_SetSubBg1Offset(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubBg2Offset
void Gfx2d_SetSubBg2Offset(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubBg3Offset
void Gfx2d_SetSubBg3Offset(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainWin0Planes
void Gfx2d_SetMainWin0Planes(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainWin1Planes
void Gfx2d_SetMainWin1Planes(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubWin0Planes
void Gfx2d_SetSubWin0Planes(u32 a, BOOL b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubWin1Planes
void Gfx2d_SetSubWin1Planes(u32 a, BOOL b);
#endif
#ifndef PROTO_LOCAL_Gfx2d_MarkSubWin0PlanesDirty
void Gfx2d_MarkSubWin0PlanesDirty(BOOL a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_MarkSubWin1PlanesDirty
void Gfx2d_MarkSubWin1PlanesDirty(BOOL a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainWinOutPlanes
void Gfx2d_SetMainWinOutPlanes(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_RemoveMainWinOutPlanes
void Gfx2d_RemoveMainWinOutPlanes(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubWinOutPlanes
void Gfx2d_SetSubWinOutPlanes(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainObjWinPlanes
void Gfx2d_SetMainObjWinPlanes(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubObjWinPlanes
void Gfx2d_SetSubObjWinPlanes(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainWin0Rect
void Gfx2d_SetMainWin0Rect(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainWin1Rect
void Gfx2d_SetMainWin1Rect(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubWin0Rect
void Gfx2d_SetSubWin0Rect(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubWin1Rect
void Gfx2d_SetSubWin1Rect(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainBgModeState
void Gfx2d_SetMainBgModeState(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubBgModeState
void Gfx2d_SetSubBgModeState(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainBgMode
void Gfx2d_SetMainBgMode(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubBgMode
void Gfx2d_SetSubBgMode(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_GetMainWindows
u32 Gfx2d_GetMainWindows();
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainWindows
void Gfx2d_SetMainWindows(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_EnableMainWindows
void Gfx2d_EnableMainWindows(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_DisableMainWindows
void Gfx2d_DisableMainWindows(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_GetSubWindows
u32 Gfx2d_GetSubWindows();
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubWindows
void Gfx2d_SetSubWindows(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_EnableSubWindows
void Gfx2d_EnableSubWindows(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_DisableSubWindows
void Gfx2d_DisableSubWindows(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_GetMainPlanes
u8 Gfx2d_GetMainPlanes(void);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainPlanes
void Gfx2d_SetMainPlanes(u8 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_ShowMainPlanes
void Gfx2d_ShowMainPlanes(u8 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_HideMainPlanes
void Gfx2d_HideMainPlanes(u8 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_GetSubPlanes
u8 Gfx2d_GetSubPlanes(void);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubPlanes
void Gfx2d_SetSubPlanes(u8 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_ShowSubPlanes
void Gfx2d_ShowSubPlanes(u8 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_HideSubPlanes
void Gfx2d_HideSubPlanes(u8 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetBrightness
void Gfx2d_SetBrightness(u32 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_BeginSubObjWinBrightness
void Gfx2d_BeginSubObjWinBrightness(void);
#endif
#ifndef PROTO_LOCAL_Gfx2d_EndSubObjWinBrightness
void Gfx2d_EndSubObjWinBrightness(void);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubBrightnessAllPlanes
void Gfx2d_SetSubBrightnessAllPlanes(void);
#endif
#ifndef PROTO_LOCAL_Gfx2d_ExcludeSubBrightnessPlanes
void Gfx2d_ExcludeSubBrightnessPlanes(u8 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubBrightness
void Gfx2d_SetSubBrightness(u8 a);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetSubAlphaBlend
void Gfx2d_SetSubAlphaBlend(u8 a, u8 b, u8 c);
#endif
#ifndef PROTO_LOCAL_Gfx2d_ResetSubBlend
void Gfx2d_ResetSubBlend(void);
#endif
#ifndef PROTO_LOCAL_Gfx2d_SetMainAlphaBlend
void Gfx2d_SetMainAlphaBlend(u8 a, u8 b, u8 c);
#endif
#ifndef PROTO_LOCAL_Gfx2d_ResetMainBlend
void Gfx2d_ResetMainBlend(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Gfx2d_InitBgOffset
void Gfx2d_InitBgOffset(Gfx2dOffset* p);
#endif
#ifndef PROTO_LOCAL_Gfx2d_InitBgAffine
void Gfx2d_InitBgAffine(Gfx2dAffine* p);
#endif
#ifndef PROTO_LOCAL_Gfx2d_InitWindowRect
void Gfx2d_InitWindowRect(Gfx2dWindowRect* p);
#endif
}
#ifndef PROTO_LOCAL_sGfx2dBackdropColor
extern u8 sGfx2dBackdropColor[4];
#endif
#ifndef PROTO_LOCAL_sGfx2d
extern Gfx2dState sGfx2d;
#endif
#endif

#endif
