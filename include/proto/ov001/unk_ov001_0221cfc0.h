#ifndef PROTO_PROTO_OV001_UNK_OV001_0221CFC0_H
#define PROTO_PROTO_OV001_UNK_OV001_0221CFC0_H


#include "types.h"
struct WfcScrollBar;
#ifndef __cplusplus
typedef struct WfcScrollBar WfcScrollBar;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_Create
void WfcScrollBar_Create(u32 a, u32 b, s32 c, s32 d, u32 e);
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_Destroy
void WfcScrollBar_Destroy();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_GetPos
u32 WfcScrollBar_GetPos();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_GetEvent
u32 WfcScrollBar_GetEvent();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_SetPos
void WfcScrollBar_SetPos(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_Enable
void WfcScrollBar_Enable();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_Disable
void WfcScrollBar_Disable();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_Task
void WfcScrollBar_Task();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_UpdateDrag
void WfcScrollBar_UpdateDrag();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_UpdateDragSound
void WfcScrollBar_UpdateDragSound(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_StartArrow
void WfcScrollBar_StartArrow(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_JumpToTouch
void WfcScrollBar_JumpToTouch();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_HitTest
s32 WfcScrollBar_HitTest();
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_HitTestArrowHeld
s32 WfcScrollBar_HitTestArrowHeld(s32 unused);
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_GetPartRect
void WfcScrollBar_GetPartRect(s32 a, u16 *out);
#endif
#ifndef PROTO_LOCAL_WfcScrollBar_SetThumbPos
void WfcScrollBar_SetThumbPos(u32 a);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sWfcScrollBar
extern WfcScrollBar *sWfcScrollBar;
#endif
#endif

#endif
