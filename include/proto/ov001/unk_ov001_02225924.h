#ifndef PROTO_PROTO_OV001_UNK_OV001_02225924_H
#define PROTO_PROTO_OV001_UNK_OV001_02225924_H


#include "types.h"
#include "net/WfcRect.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcHeap
extern void *sWfcHeap;
#endif
#ifndef PROTO_LOCAL_WfcHeap_Init
void WfcHeap_Init(void *buf);
#endif
#ifndef PROTO_LOCAL_WfcHeap_Destroy
void WfcHeap_Destroy();
#endif
#ifndef PROTO_LOCAL_WfcHeap_Alloc
void *WfcHeap_Alloc(u32 size, u32 b);
#endif
#ifndef PROTO_LOCAL_WfcHeap_AllocClear
void *WfcHeap_AllocClear(u32 size, u32 b);
#endif
#ifndef PROTO_LOCAL_WfcHeap_FreeAndClear
void WfcHeap_FreeAndClear(void **pp);
#endif
#ifndef PROTO_LOCAL_WfcHeap_Free
void WfcHeap_Free(void *p);
#endif
#ifndef PROTO_LOCAL_WfcGx_ShowPlanes
void WfcGx_ShowPlanes(u32 eng, u32 m);
#endif
#ifndef PROTO_LOCAL_WfcGx_HidePlanes
void WfcGx_HidePlanes(u32 eng, u32 m);
#endif
#ifndef PROTO_LOCAL_WfcGx_SetWindowRect
void WfcGx_SetWindowRect(u32 eng, u32 which, WfcRect *r);
#endif
#ifndef PROTO_LOCAL_WfcGx_SetWindowPlanes
void WfcGx_SetWindowPlanes(u32 eng, u32 which, u32 v, u32 on);
#endif
#ifndef PROTO_LOCAL_WfcUtil_SetPoint
void WfcUtil_SetPoint(u32 a, u32 b, WfcPoint *out);
#endif
#ifndef PROTO_LOCAL_WfcUtil_SetRect
void WfcUtil_SetRect(u32 a, u32 b, u32 c, u32 d, WfcRect *out);
#endif
#ifdef __cplusplus
}
#endif

#endif
