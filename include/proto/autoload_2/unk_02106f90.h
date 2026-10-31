#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02106F90_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02106F90_H


#include "types.h"
#include "nnsys/g3d_rt.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NNSi_G3dAnmObjInitNsBca
void NNSi_G3dAnmObjInitNsBca(G3dAnmObj *o, u8 *res, u8 *src);
#endif
#ifndef PROTO_LOCAL_getMdlTrans_
void getMdlTrans_(G3dJntAnmResult *out);
#endif
#ifndef PROTO_LOCAL_getMdlScale_
void getMdlScale_(G3dJntAnmResult *out);
#endif
#ifndef PROTO_LOCAL_getMdlRot_
void getMdlRot_(G3dJntAnmResult *out);
#endif
#ifndef PROTO_LOCAL_getTransData_
void getTransData_(s32 *out, s32 frame, const u32 *ent, const void *base);
#endif
#ifndef PROTO_LOCAL_getTransDataEx_
void getTransDataEx_(s32 *out, s32 frame, const u32 *ent, const void *res);
#endif
#ifndef PROTO_LOCAL_data_02135e5c
extern const u8 data_02135e5c[9][4];
#endif
#ifdef __cplusplus
}
#endif

#endif
