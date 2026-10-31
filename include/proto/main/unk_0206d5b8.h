#ifndef PROTO_PROTO_MAIN_UNK_0206D5B8_H
#define PROTO_PROTO_MAIN_UNK_0206D5B8_H


#include "types.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Fatal_ExceptionCallback
void Fatal_ExceptionCallback(void *arg, void *p);
#endif
#ifndef PROTO_LOCAL_Main_InitNop
void Main_InitNop(void);
#endif
#ifndef PROTO_LOCAL_Main_WaitVBlank
void Main_WaitVBlank(void);
#endif
#ifndef PROTO_LOCAL_Main_WaitFrame
void Main_WaitFrame(void);
#endif
#ifndef PROTO_LOCAL_Main_PreTaskUpdate
void Main_PreTaskUpdate(u32 r);
#endif
#ifndef PROTO_LOCAL_Main_PostTaskUpdate
void Main_PostTaskUpdate(u32 r);
#endif
#ifndef PROTO_LOCAL_Main_PostFrameUpdate
void Main_PostFrameUpdate(void);
#endif
#ifndef PROTO_LOCAL_Main_LateUpdate
void Main_LateUpdate(u32 r);
#endif
#ifndef PROTO_LOCAL_Main_PreTaskHook
void Main_PreTaskHook(void);
#endif
#ifndef PROTO_LOCAL_Main_PostTaskHook
void Main_PostTaskHook(void);
#endif
#ifndef PROTO_LOCAL_Main_Loop
void Main_Loop(void);
#endif
#ifndef PROTO_LOCAL_Main_InitDwc
u32 Main_InitDwc(void);
#endif
#ifndef PROTO_LOCAL_Main_TakeDwcInitResult
u8 Main_TakeDwcInitResult(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sDwcInitResult
extern u8 sDwcInitResult;
#endif
#endif

#endif
