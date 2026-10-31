#ifndef PROTO_PROTO_OV001_UNK_OV001_0221E930_H
#define PROTO_PROTO_OV001_UNK_OV001_0221E930_H


#include "types.h"
struct WfcSound;
#ifndef __cplusplus
typedef struct WfcSound WfcSound;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcSound_Init
void WfcSound_Init();
#endif
#ifndef PROTO_LOCAL_WfcSound_Shutdown
void WfcSound_Shutdown();
#endif
#ifndef PROTO_LOCAL_WfcSound_Play
s32 WfcSound_Play(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcSound_SetVolume
void WfcSound_SetVolume(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcSound_SetTrackPitch
void WfcSound_SetTrackPitch(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcSound_Stop
void WfcSound_Stop();
#endif
#ifndef PROTO_LOCAL_WfcSound_MainTask
void WfcSound_MainTask();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sWfcSound
extern WfcSound *sWfcSound;
#endif
#endif

#endif
