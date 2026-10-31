#ifndef PROTO_PROTO_OV001_UNK_OV001_0220864C_H
#define PROTO_PROTO_OV001_UNK_OV001_0220864C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcCursor
extern void * *sWfcCursor;
#endif
#ifndef PROTO_LOCAL_WfcCursor_Init
void WfcCursor_Init();
#endif
#ifndef PROTO_LOCAL_WfcCursor_Free
void WfcCursor_Free();
#endif
#ifndef PROTO_LOCAL_WfcCursor_ShowPair
void WfcCursor_ShowPair(s32 idx, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_WfcCursor_ShowCorners
void WfcCursor_ShowCorners(s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_WfcCursor_Clear
void WfcCursor_Clear();
#endif
#ifdef __cplusplus
}
#endif

#endif
