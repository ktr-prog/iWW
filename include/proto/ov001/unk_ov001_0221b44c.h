#ifndef PROTO_PROTO_OV001_UNK_OV001_0221B44C_H
#define PROTO_PROTO_OV001_UNK_OV001_0221B44C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcConnTestSucceeded
extern u8 sWfcConnTestSucceeded;
#endif
#ifndef PROTO_LOCAL_WfcConnTest_Enter
void WfcConnTest_Enter();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_LoadBg
void WfcConnTest_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_Start
void WfcConnTest_Start();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_FadeIn
void WfcConnTest_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_WaitFadeIn
void WfcConnTest_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_Idle
void WfcConnTest_Idle();
#endif
#ifndef PROTO_LOCAL_func_ov001_0221b60c
void func_ov001_0221b60c();
#endif
#ifndef PROTO_LOCAL_func_ov001_0221b608
void func_ov001_0221b608();
#endif
#ifndef PROTO_LOCAL_func_ov001_0221b604
void func_ov001_0221b604();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_FadeOut
void WfcConnTest_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_WaitFadeOut
void WfcConnTest_WaitFadeOut();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_Exit
void WfcConnTest_Exit();
#endif
#ifndef PROTO_LOCAL_WfcConnTest_PollTask
void WfcConnTest_PollTask(void *task, void *work);
#endif
#ifndef PROTO_LOCAL_WfcConnTest_Alloc
void *WfcConnTest_Alloc(u32 name, u32 size);
#endif
#ifndef PROTO_LOCAL_WfcConnTest_Free
void WfcConnTest_Free(u32 name, void *p, u32 size);
#endif
#ifdef __cplusplus
}
#endif

#endif
