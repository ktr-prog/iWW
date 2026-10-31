#ifndef PROTO_PROTO_MAIN_UNK_02000C2C_H
#define PROTO_PROTO_MAIN_UNK_02000C2C_H


#include "types.h"
#include "uptr.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sCrashContext
extern u32 *sCrashContext;
#endif
#ifndef PROTO_LOCAL_sCrashScreenState
extern u8 sCrashScreenState;
#endif
#ifndef PROTO_LOCAL_sCrashSP
extern u32 sCrashSP;
#endif
#ifndef PROTO_LOCAL_sCrashTimeMs
extern u32 sCrashTimeMs;
#endif
#ifndef PROTO_LOCAL_sPanicLine
extern u32 sPanicLine;
#endif
#ifndef PROTO_LOCAL_sCrashPC
extern u32 sCrashPC;
#endif
#ifndef PROTO_LOCAL_sCrashPrevKeys
extern u32 sCrashPrevKeys;
#endif
#ifndef PROTO_LOCAL_sCrashScreenMain
extern u16 *sCrashScreenMain;
#endif
#ifndef PROTO_LOCAL_sCrashScreenSub
extern u16 *sCrashScreenSub;
#endif
#ifndef PROTO_LOCAL_Fatal_PanicV
void Fatal_PanicV(const char *a, u32 b, const char *c, void *d);
#endif
#ifndef PROTO_LOCAL_Fatal_Panic
void Fatal_Panic(const char *fmt, ...);
#endif
#ifndef PROTO_LOCAL_CrashScreen_IsValidAddress
BOOL CrashScreen_IsValidAddress(uptr addr, u32 len);
#endif
#ifndef PROTO_LOCAL_CrashScreen_DumpWords
void CrashScreen_DumpWords(u16 *dst, uptr src, u32 size);
#endif
#ifndef PROTO_LOCAL_CrashScreen_DrawStack
void CrashScreen_DrawStack(void);
#endif
#ifndef PROTO_LOCAL_CrashScreen_DrawMain
void CrashScreen_DrawMain(void);
#endif
#ifndef PROTO_LOCAL_CrashScreen_Fill
void CrashScreen_Fill(u32 a, u16 *b, u32 c);
#endif
#ifndef PROTO_LOCAL_CrashScreen_Clear
void CrashScreen_Clear(void);
#endif
#ifndef PROTO_LOCAL_CrashScreen_InitDisplay
void CrashScreen_InitDisplay(void);
#endif
#ifndef PROTO_LOCAL_CrashScreen_WaitVBlank
void CrashScreen_WaitVBlank(void);
#endif
#ifndef PROTO_LOCAL_CrashScreen_Frame
void CrashScreen_Frame(void);
#endif
#ifndef PROTO_LOCAL_CrashScreen_Run
void CrashScreen_Run(void);
#endif
#ifndef PROTO_LOCAL_FxVec3_Construct
void FxVec3_Construct(void);
#endif
#ifndef PROTO_LOCAL_LitCedarPos_Construct
void LitCedarPos_Construct(u32 *p);
#endif
#ifndef PROTO_LOCAL_FxVec3_Destruct
void FxVec3_Destruct(void *);
#endif
#ifndef PROTO_LOCAL_NitroMain
void NitroMain(void);
#endif
#ifdef __cplusplus
}
#endif

#endif
