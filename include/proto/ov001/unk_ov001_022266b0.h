#ifndef PROTO_PROTO_OV001_UNK_OV001_022266B0_H
#define PROTO_PROTO_OV001_UNK_OV001_022266B0_H


#include "types.h"
#include "nitro/gxoam.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcOam_Init
void WfcOam_Init();
#endif
#ifndef PROTO_LOCAL_WfcOam_TransferTask
void WfcOam_TransferTask();
#endif
#ifndef PROTO_LOCAL_WfcOam_Shutdown
void WfcOam_Shutdown();
#endif
#ifndef PROTO_LOCAL_WfcOam_FreeEntry
void WfcOam_FreeEntry(GXOamAttr *p);
#endif
#ifndef PROTO_LOCAL_WfcList_Destroy
void WfcList_Destroy(void *a, ...);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_WfcOam_AllocEntry
GXOamAttr *WfcOam_AllocEntry(s32 idx, void *dst);
#endif
#ifndef PROTO_LOCAL_WfcOam_GetEntry
GXOamAttr *WfcOam_GetEntry(s32 a, s32 b);
#endif
#endif

#endif
