#ifndef PROTO_PROTO_OV001_UNK_OV001_0220ABA4_H
#define PROTO_PROTO_OV001_UNK_OV001_0220ABA4_H


#include "types.h"
#include "net/WfcRect.h"
#include "ui/WfcTextKb.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcNumPad
extern WfcNumPad *sWfcNumPad;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aa58
extern WfcPosSize data_ov001_0222aa58;
#endif
#ifndef PROTO_LOCAL_WfcNumPad_Create
void WfcNumPad_Create();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_Close
void WfcNumPad_Close();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_GetKey
u32 WfcNumPad_GetKey();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SetDeleteEnabled
void WfcNumPad_SetDeleteEnabled(u32 v);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SetInsertEnabled
void WfcNumPad_SetInsertEnabled(u32 v);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SetDotEnabled
void WfcNumPad_SetDotEnabled(u32 v);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_Exists
BOOL WfcNumPad_Exists();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideInStep0
void WfcNumPad_SlideInStep0(void *self, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideInStep1
void WfcNumPad_SlideInStep1(void *self, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideInStep2
void WfcNumPad_SlideInStep2(void *self, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideInStep3
void WfcNumPad_SlideInStep3(void *self, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideInStep4
void WfcNumPad_SlideInStep4(void *self, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_InputTask
void WfcNumPad_InputTask();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_HandleTouchPress
void WfcNumPad_HandleTouchPress();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_HandleTouchRelease
void WfcNumPad_HandleTouchRelease();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_HandleTouchHold
void WfcNumPad_HandleTouchHold();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SetPressedKey
void WfcNumPad_SetPressedKey(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_HandlePad
void WfcNumPad_HandlePad();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SetRowY
void WfcNumPad_SetRowY(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SetKeyHighlight
void WfcNumPad_SetKeyHighlight(s32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_UpdateCursor
void WfcNumPad_UpdateCursor();
#endif
#ifndef PROTO_LOCAL_WfcNumPad_MoveCursor
void WfcNumPad_MoveCursor(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideOutStep0
void WfcNumPad_SlideOutStep0(void *a, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideOutStep1
void WfcNumPad_SlideOutStep1(void *a, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideOutStep2
void WfcNumPad_SlideOutStep2(void *a, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideOutStep3
void WfcNumPad_SlideOutStep3(void *a, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_SlideOutStep4
void WfcNumPad_SlideOutStep4(void *a, void *work);
#endif
#ifndef PROTO_LOCAL_WfcNumPad_Destroy
void WfcNumPad_Destroy(void *a, void *work);
#endif
#ifdef __cplusplus
}
#endif

#endif
