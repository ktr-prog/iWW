#ifndef PROTO_PROTO_MAIN_UNK_020B7F7C_H
#define PROTO_PROTO_MAIN_UNK_020B7F7C_H


#include "types.h"
#include "ds_stdarg.h"
#include "sys/DebugText.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_DebugText_PutChar
void DebugText_PutChar(u16 *dst, u32 base, s32 c);
#endif
#ifndef PROTO_LOCAL_DebugText_PutString
void DebugText_PutString(u16 *dst, u32 base, const char *s);
#endif
#ifndef PROTO_LOCAL_DebugText_VPrintf
void DebugText_VPrintf(u16 *a, u32 b, const char *fmt, DS_VA_LIST ap);
#endif
#ifndef PROTO_LOCAL_TexVram_Alloc4x4
void TexVram_Alloc4x4(u32 *o0, u32 *o1, u32 size);
#endif
#ifndef PROTO_LOCAL_TexVram_AllocNormal
void TexVram_AllocNormal(u32 *o, u32 size);
#endif
#ifndef PROTO_LOCAL_PlttVram_AllocRaw
u32 PlttVram_AllocRaw(u32 a);
#endif
#ifndef PROTO_LOCAL_TexVram_Alloc
u32 TexVram_Alloc(u32 a, BOOL b, u32 opt);
#endif
#ifndef PROTO_LOCAL_PlttVram_Alloc
u32 PlttVram_Alloc(u32 a, BOOL is4pltt, u32 opt);
#endif
#ifndef PROTO_LOCAL_TexVram_InitManagers
void TexVram_InitManagers(void);
#endif
#ifndef PROTO_LOCAL_TexVram_OnAllocFail
void TexVram_OnAllocFail(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_DebugText_Print
void DebugText_Print(DebugText *self, u16 *dst, const char *s);
#endif
#ifndef PROTO_LOCAL_DebugText_Printf
void DebugText_Printf(DebugText *self, u16 *a, const char *fmt, ...);
#endif
}
#ifndef PROTO_LOCAL_sTexVramTexelALo
extern u32 sTexVramTexelALo;
#endif
#ifndef PROTO_LOCAL_sTexVramIdxALo
extern u32 sTexVramIdxALo;
#endif
#ifndef PROTO_LOCAL_sTexVramIdxBLo
extern u32 sTexVramIdxBLo;
#endif
#ifndef PROTO_LOCAL_sTexVramTexelBLo
extern u32 sTexVramTexelBLo;
#endif
#ifndef PROTO_LOCAL_sTexVramTexelAHi
extern u32 sTexVramTexelAHi;
#endif
#ifndef PROTO_LOCAL_sTexVramIdxAHi
extern u32 sTexVramIdxAHi;
#endif
#ifndef PROTO_LOCAL_sTexVramIdxBHi
extern u32 sTexVramIdxBHi;
#endif
#ifndef PROTO_LOCAL_sTexVramTexelBHi
extern u32 sTexVramTexelBHi;
#endif
#ifndef PROTO_LOCAL_sPlttVramUsed
extern u32 sPlttVramUsed;
#endif
#ifndef PROTO_LOCAL_sPlttVramSize
extern u32 sPlttVramSize;
#endif
#endif

#endif
