#ifndef PROTO_PROTO_MAIN_UNK_0206FC44_H
#define PROTO_PROTO_MAIN_UNK_0206FC44_H


#include "types.h"
#include "gfx/Mtx43.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CpuMtx_MultRot
void CpuMtx_MultRot(void *a);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_CpuMtx_MultRotTrans
void CpuMtx_MultRotTrans(void *a, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_CpuMtx_MultTrans
void CpuMtx_MultTrans(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_CpuMtx_MultRotScaledTrans
void CpuMtx_MultRotScaledTrans(void *a, VecFx32 *v, VecFx32 *w);
#endif
}
#ifndef PROTO_LOCAL_data_021cb69c
extern Mtx43 data_021cb69c;
#endif
#endif

#endif
