#ifndef PROTO_PROTO_OV001_UNK_OV001_0222449C_H
#define PROTO_PROTO_OV001_UNK_OV001_0222449C_H


#include "types.h"
#include "net/WfcObjGroup.h"
#include "nitro/gxoam.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcObj_Init
void WfcObj_Init();
#endif
#ifndef PROTO_LOCAL_WfcObj_Shutdown
void WfcObj_Shutdown();
#endif
#ifndef PROTO_LOCAL_WfcObj_Alloc
WfcObjGroup *WfcObj_Alloc(s32 which, s32 n, s32 flag);
#endif
#ifndef PROTO_LOCAL_WfcObj_Free
void WfcObj_Free(WfcObjGroup *p);
#endif
#ifndef PROTO_LOCAL_WfcObj_GetOam
GXOamAttr *WfcObj_GetOam(WfcObjGroup *p, s32 i);
#endif
#ifndef PROTO_LOCAL_WfcObj_GetCount
u32 WfcObj_GetCount(WfcObjGroup *p);
#endif
#ifndef PROTO_LOCAL_WfcObj_SetAffineMode
void WfcObj_SetAffineMode(WfcObjGroup *p, s32 idx, u32 v, u32 x);
#endif
#ifndef PROTO_LOCAL_WfcObj_SetModePalette
void WfcObj_SetModePalette(WfcObjGroup *p, s32 idx, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_WfcObj_SetPos
void WfcObj_SetPos(WfcObjGroup *self, s32 idx, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_WfcObj_SetPriority
void WfcObj_SetPriority(WfcObjGroup *self, s32 idx, s32 v);
#endif
#ifndef PROTO_LOCAL_WfcObj_GetPos
void WfcObj_GetPos(WfcObjGroup *self, s32 idx, u32 *o1, u32 *o2);
#endif
#ifdef __cplusplus
}
#endif

#endif
