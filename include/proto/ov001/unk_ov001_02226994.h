#ifndef PROTO_PROTO_OV001_UNK_OV001_02226994_H
#define PROTO_PROTO_OV001_UNK_OV001_02226994_H


#include "types.h"
struct WfcVramBlock;
#ifndef __cplusplus
typedef struct WfcVramBlock WfcVramBlock;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcVram_Init
void WfcVram_Init();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_WfcVram_AllocObjChar
WfcVramBlock *WfcVram_AllocObjChar(s32 idx, s32 size, s32 flag, u32 *out);
#endif
#ifndef PROTO_LOCAL_WfcVram_FreeObjChar
void WfcVram_FreeObjChar(WfcVramBlock *p);
#endif
}
#endif

#endif
