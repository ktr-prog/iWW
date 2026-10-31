#ifndef PROTO_PROTO_OV001_UNK_OV001_02225F40_H
#define PROTO_PROTO_OV001_UNK_OV001_02225F40_H


#include "types.h"
#include "net/WfcRect.h"
struct WfcInputState;
#ifndef __cplusplus
typedef struct WfcInputState WfcInputState;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcTouchRepeatCounter
extern u8 sWfcTouchRepeatCounter;
#endif
#ifndef PROTO_LOCAL_sWfcKeyRepeatCounters
extern u8 sWfcKeyRepeatCounters[16];
#endif
#ifndef PROTO_LOCAL_WfcInput_Init
void WfcInput_Init();
#endif
#ifndef PROTO_LOCAL_WfcInput_Shutdown
void WfcInput_Shutdown();
#endif
#ifndef PROTO_LOCAL_WfcInput_Update
void WfcInput_Update();
#endif
#ifndef PROTO_LOCAL_WfcInput_UpdateKeys
void WfcInput_UpdateKeys();
#endif
#ifndef PROTO_LOCAL_WfcInput_UpdateTouch
void WfcInput_UpdateTouch();
#endif
#ifndef PROTO_LOCAL_WfcInput_IsKeyHeld
BOOL WfcInput_IsKeyHeld(u32 m);
#endif
#ifndef PROTO_LOCAL_WfcInput_IsKeyPressed
BOOL WfcInput_IsKeyPressed(u32 m);
#endif
#ifndef PROTO_LOCAL_WfcInput_IsKeyRepeat
BOOL WfcInput_IsKeyRepeat(u32 m);
#endif
#ifndef PROTO_LOCAL_WfcInput_IsKeyReleased
BOOL WfcInput_IsKeyReleased(u32 m);
#endif
#ifndef PROTO_LOCAL_WfcInput_IsTouchHeldIn
BOOL WfcInput_IsTouchHeldIn(WfcRect *r);
#endif
#ifndef PROTO_LOCAL_WfcInput_IsTouchPressedIn
BOOL WfcInput_IsTouchPressedIn(WfcRect *r);
#endif
#ifndef PROTO_LOCAL_WfcInput_IsTouchRepeatIn
BOOL WfcInput_IsTouchRepeatIn(WfcRect *r);
#endif
#ifndef PROTO_LOCAL_WfcInput_IsTouchReleasedIn
BOOL WfcInput_IsTouchReleasedIn(WfcRect *r);
#endif
#ifndef PROTO_LOCAL_WfcInput_IsTouchPressedInBox
BOOL WfcInput_IsTouchPressedInBox(WfcPosSize *r);
#endif
#ifndef PROTO_LOCAL_WfcInput_GetTouchPos
BOOL WfcInput_GetTouchPos(WfcPoint *out);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcInput
extern WfcInputState *sWfcInput;
#endif
}
#endif

#endif
