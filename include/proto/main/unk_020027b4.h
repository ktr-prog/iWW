#ifndef PROTO_PROTO_MAIN_UNK_020027B4_H
#define PROTO_PROTO_MAIN_UNK_020027B4_H


#include "types.h"
#include "gfx/Mtx43.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Gfx3d_InitEngine
void Gfx3d_InitEngine(void);
#endif
#ifndef PROTO_LOCAL_Gfx3d_Init
void Gfx3d_Init(void);
#endif
#ifndef PROTO_LOCAL_Gfx3d_BeginFrame
void Gfx3d_BeginFrame(void);
#endif
#ifndef PROTO_LOCAL_Gfx3d_LoadDefaultToonTable
void Gfx3d_LoadDefaultToonTable(void);
#endif
#ifndef PROTO_LOCAL_Gfx3d_SetClearDepth
void Gfx3d_SetClearDepth(u32 v);
#endif
#ifndef PROTO_LOCAL_Gfx3d_SetClearColor
void Gfx3d_SetClearColor(u16 v);
#endif
#ifndef PROTO_LOCAL_Gfx3d_ApplyClearColor
void Gfx3d_ApplyClearColor(void);
#endif
#ifndef PROTO_LOCAL_Gfx2d_IsMainScreenLayer
BOOL Gfx2d_IsMainScreenLayer(u32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Gfx3d_SetViewMatrix
void Gfx3d_SetViewMatrix(Mtx43 *src);
#endif
}
#ifndef PROTO_LOCAL_sGfx3dClearColor
extern u16 sGfx3dClearColor;
#endif
#ifndef PROTO_LOCAL_sGfx3dClearDepth
extern u32 sGfx3dClearDepth;
#endif
#ifndef PROTO_LOCAL_gViewMtxInv
extern u8 gViewMtxInv[0x30];
#endif
#ifndef PROTO_LOCAL_gViewMtx
extern Mtx43 gViewMtx;
#endif
#endif

#endif
