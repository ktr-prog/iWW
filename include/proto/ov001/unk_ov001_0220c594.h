#ifndef PROTO_PROTO_OV001_UNK_OV001_0220C594_H
#define PROTO_PROTO_OV001_UNK_OV001_0220C594_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcLanguage
extern u8 sWfcLanguage;
#endif
#ifndef PROTO_LOCAL_sWfcParams
extern u32 sWfcParams;
#endif
#ifndef PROTO_LOCAL_sWfcExitRequested
extern u8 sWfcExitRequested;
#endif
#ifndef PROTO_LOCAL_sWfcWorkArea
extern void *sWfcWorkArea;
#endif
#ifndef PROTO_LOCAL_sWfcSceneFunc
extern void (*sWfcSceneFunc) ();
#endif
#ifndef PROTO_LOCAL_sWfcScreenFlags
extern u32 sWfcScreenFlags[4];
#endif
#ifndef PROTO_LOCAL_WfcUtil_Run
s32 WfcUtil_Run(void *a, s32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_WfcUtil_CheckParams
s32 WfcUtil_CheckParams(s32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_WfcUtil_InitSystem
void WfcUtil_InitSystem();
#endif
#ifndef PROTO_LOCAL_WfcUtil_InitDisplay
void WfcUtil_InitDisplay();
#endif
#ifndef PROTO_LOCAL_WfcUtil_Shutdown
void WfcUtil_Shutdown();
#endif
#ifndef PROTO_LOCAL_WfcUtil_SetScene
void WfcUtil_SetScene(void (*f)());
#endif
#ifndef PROTO_LOCAL_WfcUtil_SetScreenFlags
void WfcUtil_SetScreenFlags(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_WfcUtil_GetScreenFlags
void WfcUtil_GetScreenFlags(u32 *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_WfcUtil_SetEditParams
void WfcUtil_SetEditParams(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_WfcUtil_GetEditParams
void WfcUtil_GetEditParams(u32 *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_WfcUtil_GetLanguage
u32 WfcUtil_GetLanguage();
#endif
#ifndef PROTO_LOCAL_WfcUtil_GetStartMode
u32 WfcUtil_GetStartMode();
#endif
#ifndef PROTO_LOCAL_WfcUtil_TestOptionFlag
BOOL WfcUtil_TestOptionFlag(u32 m);
#endif
#ifndef PROTO_LOCAL_WfcUtil_RequestExit
void WfcUtil_RequestExit();
#endif
#ifdef __cplusplus
}
#endif

#endif
