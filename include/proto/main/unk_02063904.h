#ifndef PROTO_PROTO_MAIN_UNK_02063904_H
#define PROTO_PROTO_MAIN_UNK_02063904_H


#include "types.h"
#include "ds_stdarg.h"
#include "nitro/fs.h"
struct FileBlockCache;
#ifndef __cplusplus
typedef struct FileBlockCache FileBlockCache;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_File_Exists
BOOL File_Exists(const char *a);
#endif
#ifndef PROTO_LOCAL_File_ReadRangeByPath
void File_ReadRangeByPath(const char *a, void *dst, u32 size, u32 off);
#endif
#ifndef PROTO_LOCAL_File_ReadRangeById
void File_ReadRangeById(FSFileID id, void *dst, u32 size, u32 off);
#endif
#ifndef PROTO_LOCAL_File_ReadRange
void File_ReadRange(FSFile *f, void *dst, u32 size, u32 off);
#endif
#ifndef PROTO_LOCAL_File_LoadOverlay
s32 File_LoadOverlay(s32 x);
#endif
#ifndef PROTO_LOCAL_File_UnloadOverlay
s32 File_UnloadOverlay(s32 x);
#endif
#ifndef PROTO_LOCAL_BlinkTimer_Construct
void BlinkTimer_Construct();
#endif
#ifndef PROTO_LOCAL_BlinkTimer_Destruct
void BlinkTimer_Destruct();
#endif
#ifndef PROTO_LOCAL_BlinkTimer_StartBlink
void BlinkTimer_StartBlink(u8 *p);
#endif
#ifndef PROTO_LOCAL_BlinkTimer_Update
BOOL BlinkTimer_Update(u8 *p);
#endif
#ifndef PROTO_LOCAL_BlinkTimer_Clear
void BlinkTimer_Clear(u8 *p);
#endif
#ifndef PROTO_LOCAL_BlinkTimer_BlinkNow
void BlinkTimer_BlinkNow(u8 *p);
#endif
#ifndef PROTO_LOCAL_Math_AngleToSide
s32 Math_AngleToSide(s32 x);
#endif
#ifndef PROTO_LOCAL_Math_AngleToDir4
s32 Math_AngleToDir4(s32 x);
#endif
#ifndef PROTO_LOCAL_Math_AngleToDir8
s32 Math_AngleToDir8(s32 x);
#endif
#ifndef PROTO_LOCAL_Random_GlobalBelow
u32 Random_GlobalBelow(u32 n);
#endif
#ifndef PROTO_LOCAL_Random_GlobalBelow2
u32 Random_GlobalBelow2(u32 n);
#endif
#ifndef PROTO_LOCAL_Math_EaseRampProgress
s32 Math_EaseRampProgress(s32 x, s32 lo, s32 hi, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_G3dRes_CopyTexByName
void G3dRes_CopyTexByName(void *a, void *b, const char *c, const char *d);
#endif
#ifndef PROTO_LOCAL_G3dRes_CopyPlttByName
void G3dRes_CopyPlttByName(void *a, void *b, const char *c, const char *d);
#endif
#ifndef PROTO_LOCAL_Mem_Differs
BOOL Mem_Differs(const void *a, const void *b, u32 n);
#endif
#ifndef PROTO_LOCAL_Str_SPrintf
s32 Str_SPrintf(char *buf, const char *fmt, ...);
#endif
#ifndef PROTO_LOCAL_Str_VSPrintf
s32 Str_VSPrintf(char *buf, const char *fmt, va_list va);
#endif
#ifndef PROTO_LOCAL_Str_VSNPrintf
s32 Str_VSNPrintf(char *buf, u32 n, const char *fmt, va_list va);
#endif
#ifndef PROTO_LOCAL_TownId_Construct
void TownId_Construct();
#endif
#ifndef PROTO_LOCAL_TownId_Destruct
void TownId_Destruct();
#endif
#ifndef PROTO_LOCAL_TownId_Clear
void TownId_Clear(u16 *p);
#endif
#ifndef PROTO_LOCAL_TownId_Assign
void TownId_Assign(void *dst, void *src);
#endif
#ifndef PROTO_LOCAL_TownId_CopyFrom
void TownId_CopyFrom(u16 *dst, u16 *src);
#endif
#ifndef PROTO_LOCAL_TownId_CopyTo
void TownId_CopyTo(u16 *src, u16 *dst);
#endif
#ifndef PROTO_LOCAL_TownId_GetName
u16 *TownId_GetName(u16 *p);
#endif
#ifndef PROTO_LOCAL_TownId_IsValid
BOOL TownId_IsValid(u16 *p);
#endif
#ifndef PROTO_LOCAL_TownId_SetId
void TownId_SetId(u16 *p, u16 v);
#endif
#ifndef PROTO_LOCAL_TownId_GenerateId
u16 TownId_GenerateId(void *p);
#endif
#ifndef PROTO_LOCAL_TownId_InitWithName
void TownId_InitWithName(u16 *p, const void *src);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sFileBlockCacheIndex
extern u8 sFileBlockCacheIndex;
#endif
#ifndef PROTO_LOCAL_sFileBlockCacheFileId
extern u16 sFileBlockCacheFileId;
#endif
#ifndef PROTO_LOCAL_sFileBlockCache
extern FileBlockCache sFileBlockCache;
#endif
#endif

#endif
