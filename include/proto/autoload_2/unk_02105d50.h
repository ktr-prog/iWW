#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02105D50_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02105D50_H


#include "types.h"
#include "nnsys/g3d_rt.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NNS_G3dMdlSetMdlEmiAll
void NNS_G3dMdlSetMdlEmiAll(u8 *m, u32 x);
#endif
#ifndef PROTO_LOCAL_NNS_G3dMdlSetMdlLightEnableFlagAll
void NNS_G3dMdlSetMdlLightEnableFlagAll(u8 *m, u32 x);
#endif
#ifndef PROTO_LOCAL_NNS_G3dMdlSetMdlPolygonIDAll
void NNS_G3dMdlSetMdlPolygonIDAll(u8 *m, u32 x);
#endif
#ifndef PROTO_LOCAL_NNS_G3dMdlSetMdlAlphaAll
void NNS_G3dMdlSetMdlAlphaAll(u8 *m, u32 x);
#endif
#ifndef PROTO_LOCAL_NNS_G3dGetCurrentMtx
void NNS_G3dGetCurrentMtx(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_NNS_G3dGetResultMtx
BOOL NNS_G3dGetResultMtx(G3dRenderObj *obj, void *a, void *b, u32 idx);
#endif
#ifndef PROTO_LOCAL_NNS_G3dInit
void NNS_G3dInit(void);
#endif
#ifndef PROTO_LOCAL_NNS_G3dGetSbcCmdLen
s32 NNS_G3dGetSbcCmdLen(u8 *c);
#endif
#ifndef PROTO_LOCAL_data_02135d5c
extern const s8 data_02135d5c[256];
#endif
#ifdef __cplusplus
}
#endif

#endif
