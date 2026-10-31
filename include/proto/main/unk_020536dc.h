#ifndef PROTO_PROTO_MAIN_UNK_020536DC_H
#define PROTO_PROTO_MAIN_UNK_020536DC_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/GfxFrameHooks.h"
#include "gfx/ThreeLayerAnimModel.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Gfx_Init
void Gfx_Init();
#endif
#ifndef PROTO_LOCAL_Gfx_ResetScene
void Gfx_ResetScene();
#endif
#ifndef PROTO_LOCAL_GfxFrameHooks_PreTaskStub
void GfxFrameHooks_PreTaskStub();
#endif
#ifndef PROTO_LOCAL_Gfx_PreTaskUpdate
void Gfx_PreTaskUpdate();
#endif
#ifndef PROTO_LOCAL_GfxFrameHooks_PostTaskStub
void GfxFrameHooks_PostTaskStub();
#endif
#ifndef PROTO_LOCAL_Gfx_PostTaskUpdate
void Gfx_PostTaskUpdate();
#endif
#ifndef PROTO_LOCAL_Gfx_VBlankFlush
void Gfx_VBlankFlush();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gGfxFrameHooks
extern GfxFrameHooks *gGfxFrameHooks;
#endif
#ifndef PROTO_LOCAL_ThreeLayerAnimModel_ClearLayer3Mask
void ThreeLayerAnimModel_ClearLayer3Mask(ThreeLayerAnimModel *o);
#endif
}
#endif

#endif
