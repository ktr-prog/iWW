#ifndef PROTO_PROTO_OV001_UNK_OV001_02226F68_H
#define PROTO_PROTO_OV001_UNK_OV001_02226F68_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcTask_Init
void WfcTask_Init();
#endif
#ifndef PROTO_LOCAL_WfcTask_Shutdown
void WfcTask_Shutdown();
#endif
#ifndef PROTO_LOCAL_WfcTask_RunList
void WfcTask_RunList(u32 i);
#endif
#ifndef PROTO_LOCAL_WfcTask_Add
void *WfcTask_Add(u32 i, void *a, void *b, u32 c);
#endif
#ifndef PROTO_LOCAL_WfcTask_AddEx
void *WfcTask_AddEx(u32 i, void *a, void *b, u32 c, u8 d);
#endif
#ifndef PROTO_LOCAL_WfcTask_RequestDelete
void WfcTask_RequestDelete(u32 i, void *p);
#endif
#ifndef PROTO_LOCAL_WfcTask_Delete
void WfcTask_Delete(u32 i, void *p);
#endif
#ifndef PROTO_LOCAL_WfcTask_Release
void WfcTask_Release(u32 i, void *p);
#endif
#ifndef PROTO_LOCAL_WfcTask_SetListActive
void WfcTask_SetListActive(u32 i, u32 v);
#endif
#ifdef __cplusplus
}
#endif

#endif
