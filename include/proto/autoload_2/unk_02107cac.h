#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02107CAC_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02107CAC_H


#include "types.h"
#include "nnsys/g3d_rt.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NNSi_G3dSendTexSRTSi3d
void NNSi_G3dSendTexSRTSi3d(const G3dMatAnmResult *a);
#endif
#ifndef PROTO_LOCAL_NNSi_G3dSendJointSRTBasic
void NNSi_G3dSendJointSRTBasic(G3dJntAnmResult *r);
#endif
#ifndef PROTO_LOCAL_NNSi_G3dGetJointScaleBasic
void NNSi_G3dGetJointScaleBasic(G3dJntAnmResult *obj, const s32 *src, const u8 *info, u32 flags);
#endif
#ifndef PROTO_LOCAL_NNSi_G3dAnmObjInitNsBva
void NNSi_G3dAnmObjInitNsBva(G3dAnmObj *out, void *res, u8 *blk);
#endif
#ifndef PROTO_LOCAL_NNSi_G3dAnmCalcNsBva
void NNSi_G3dAnmCalcNsBva(G3dVisAnmResult *out, const G3dAnmObj *a, u32 dataIdx);
#endif
#ifndef PROTO_LOCAL_NNSi_G3dAnmObjInitNsBtp
void NNSi_G3dAnmObjInitNsBtp(G3dAnmObj *obj, u8 *res, u8 *blk);
#endif
#ifndef PROTO_LOCAL_SetTexParamaters_
s32 SetTexParamaters_(u8 *A, const u8 *name, G3dMatAnmResult *out);
#endif
#ifndef PROTO_LOCAL_SetPlttParamaters_
u32 SetPlttParamaters_(u8 *A, const u8 *name, G3dMatAnmResult *out);
#endif
#ifndef PROTO_LOCAL_NNSi_G3dAnmCalcNsBtp
u32 NNSi_G3dAnmCalcNsBtp(G3dMatAnmResult *obj, const G3dAnmObj *a, u32 dataIdx);
#endif
#ifndef PROTO_LOCAL_GetTexSRTAnmVectorVal_
s32 GetTexSRTAnmVectorVal_(u8 *base, u32 info, u32 offs, u32 frame);
#endif
#ifdef __cplusplus
}
#endif

#endif
