#ifndef PROTO_PROTO_MAIN_UNK_020B0A80_H
#define PROTO_PROTO_MAIN_UNK_020B0A80_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Footstep_AttrToSe
u32 Footstep_AttrToSe(u32 a);
#endif
#ifndef PROTO_LOCAL_GroundAttr_ResolveCarpet
u32 GroundAttr_ResolveCarpet(u32 a);
#endif
#ifndef PROTO_LOCAL_Footstep_GetSeForAttr
u32 Footstep_GetSeForAttr(u32 a);
#endif
#ifndef PROTO_LOCAL_Main_InitVBlank
void Main_InitVBlank(void);
#endif
#ifndef PROTO_LOCAL_Main_InitStub
void Main_InitStub(void);
#endif
#ifndef PROTO_LOCAL_Main_Init
void Main_Init(void);
#endif
#ifndef PROTO_LOCAL_Startup_OnWvrStartUp
void Startup_OnWvrStartUp(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Startup_SetupMainArena
void Startup_SetupMainArena(void);
#endif
#ifndef PROTO_LOCAL_Startup_FillOverlayArea
void Startup_FillOverlayArea(void);
#endif
#ifndef PROTO_LOCAL_NitroStartUp
void NitroStartUp(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_GroundAttr_GetAtPos
u32 GroundAttr_GetAtPos(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_Footstep_GetSeAtPos
u32 Footstep_GetSeAtPos(VecFx32 *a);
#endif
}
#ifndef PROTO_LOCAL_sWvrStartUpDone
extern volatile u8 sWvrStartUpDone;
#endif
#endif

#endif
