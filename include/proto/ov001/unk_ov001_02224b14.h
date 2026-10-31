#ifndef PROTO_PROTO_OV001_UNK_OV001_02224B14_H
#define PROTO_PROTO_OV001_UNK_OV001_02224B14_H


#include "types.h"
#include "net/WfcObjGroup.h"
#include "nitro/gxoam.h"
struct WfcCellEntry;
#ifndef __cplusplus
typedef struct WfcCellEntry WfcCellEntry;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcCell_Load
void WfcCell_Load(s32 which, void *path);
#endif
#ifndef PROTO_LOCAL_WfcCell_Unload
void WfcCell_Unload(s32 which);
#endif
#ifndef PROTO_LOCAL_WfcCell_Copy
void WfcCell_Copy(s32 which, s32 idx, void *dst);
#endif
#ifndef PROTO_LOCAL_WfcObj_CreateSingle
GXOamAttr *WfcObj_CreateSingle(s32 which, s32 idx);
#endif
#ifndef PROTO_LOCAL_WfcObj_Create
WfcObjGroup *WfcObj_Create(s32 which, s32 idx, s32 flag);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcCellData
extern WfcCellEntry *sWfcCellData[2];
#endif
}
#endif

#endif
