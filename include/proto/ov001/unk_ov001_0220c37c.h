#ifndef PROTO_PROTO_OV001_UNK_OV001_0220C37C_H
#define PROTO_PROTO_OV001_UNK_OV001_0220C37C_H


#include "types.h"
#include "net/AossParam.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcAossSucceeded
extern volatile u8 sWfcAossSucceeded;
#endif
#ifndef PROTO_LOCAL_sWfcAossConfig
extern AossParam *sWfcAossConfig;
#endif
#ifndef PROTO_LOCAL_WfcAoss_Begin
void WfcAoss_Begin();
#endif
#ifndef PROTO_LOCAL_WfcAoss_End
void WfcAoss_End(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcAoss_Run
u32 WfcAoss_Run();
#endif
#ifndef PROTO_LOCAL_WfcAoss_Alloc
void *WfcAoss_Alloc(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcAoss_Free
void WfcAoss_Free(void *p);
#endif
#ifdef __cplusplus
}
#endif

#endif
