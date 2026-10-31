#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02107994_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02107994_H


#include "types.h"
#include "nnsys/g3d_rt.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_GetTexSRTAnm_
void GetTexSRTAnm_(u8 *res, u32 idx, u32 frame, G3dMatAnmResult *out);
#endif
#ifndef PROTO_LOCAL_NNSi_G3dAnmObjInitNsBta
void NNSi_G3dAnmObjInitNsBta(G3dAnmObj *obj, u8 *res, u8 *blk);
#endif
#ifndef PROTO_LOCAL_NNSi_G3dAnmCalcNsBta
void NNSi_G3dAnmCalcNsBta(G3dMatAnmResult *result, const G3dAnmObj *anm, u32 dataIdx);
#endif
#ifdef __cplusplus
}
#endif

#endif
