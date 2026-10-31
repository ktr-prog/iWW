#ifndef PROTO_PROTO_OV001_UNK_OV001_02222E84_H
#define PROTO_PROTO_OV001_UNK_OV001_02222E84_H


#include "types.h"
#include "net/WfcMoveParams.h"
#include "nitro/wm.h"
struct WfcMoveWork;
#ifndef __cplusplus
typedef struct WfcMoveWork WfcMoveWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcMove_RequestCancel
BOOL WfcMove_RequestCancel();
#endif
#ifndef PROTO_LOCAL_WfcMove_ResetSession
void WfcMove_ResetSession();
#endif
#ifndef PROTO_LOCAL_WfcMove_Start
BOOL WfcMove_Start();
#endif
#ifndef PROTO_LOCAL_WfcMove_StartDownload
BOOL WfcMove_StartDownload();
#endif
#ifndef PROTO_LOCAL_WfcMove_Update
void WfcMove_Update();
#endif
#ifndef PROTO_LOCAL_WfcMove_GetState
void WfcMove_GetState(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_WfcMove_GetChildUser
u8 *WfcMove_GetChildUser();
#endif
#ifndef PROTO_LOCAL_WfcMove_StepMeasureChannel
void WfcMove_StepMeasureChannel();
#endif
#ifndef PROTO_LOCAL_WfcMove_StepInitMb
void WfcMove_StepInitMb();
#endif
#ifndef PROTO_LOCAL_WfcMove_StepMb
void WfcMove_StepMb();
#endif
#ifndef PROTO_LOCAL_WfcMove_StepStartDataShare
void WfcMove_StepStartDataShare();
#endif
#ifndef PROTO_LOCAL_WfcMove_StepDataShare
void WfcMove_StepDataShare();
#endif
#ifndef PROTO_LOCAL_WfcMove_SetDone
void WfcMove_SetDone();
#endif
#ifndef PROTO_LOCAL_WfcMove_TryEnd
s32 WfcMove_TryEnd();
#endif
#ifndef PROTO_LOCAL_WfcMove_JudgeChild
s32 WfcMove_JudgeChild(WMStartParentCallback *a);
#endif
#ifndef PROTO_LOCAL_WfcMove_ClearBuffers
void WfcMove_ClearBuffers();
#endif
#ifndef PROTO_LOCAL_WfcMove_SendBlock
void WfcMove_SendBlock(u32 a, u32 b, void *src);
#endif
#ifndef PROTO_LOCAL_WfcMove_ProcessRecv
void WfcMove_ProcessRecv();
#endif
#ifndef PROTO_LOCAL_WfcMove_GetChildReply
s32 WfcMove_GetChildReply();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcMove
extern WfcMoveWork *sWfcMove;
#endif
#ifndef PROTO_LOCAL_WfcMove_Init
void WfcMove_Init(WfcMoveWork *self, const WfcMoveParams *a);
#endif
}
#endif

#endif
