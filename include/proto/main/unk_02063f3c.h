#ifndef PROTO_PROTO_MAIN_UNK_02063F3C_H
#define PROTO_PROTO_MAIN_UNK_02063F3C_H


#include "types.h"
#include "ds_stdarg.h"
#include "nitro/fs.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_File_LoadOverlayEx
BOOL File_LoadOverlayEx(s32 target, u32 id);
#endif
#ifndef PROTO_LOCAL_File_Open
BOOL File_Open(void *file, const char *path);
#endif
#ifndef PROTO_LOCAL_File_OpenOrPanic
void File_OpenOrPanic(void *file, const char *path);
#endif
#ifndef PROTO_LOCAL_File_LoadToBuffer
s32 File_LoadToBuffer(const char *buf, void *a, u32 b);
#endif
#ifndef PROTO_LOCAL_File_ReadAll
s32 File_ReadAll(FSFile *f, void *dst, u32 n);
#endif
#ifndef PROTO_LOCAL_File_LoadF
void *File_LoadF(const char *fmt, ...);
#endif
#ifndef PROTO_LOCAL_File_GetDecodedSize
s32 File_GetDecodedSize(FSFile *f);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_File_LoadAlloc
void *File_LoadAlloc(const char *path, void *heapArg, s32 align, u32 *outSize);
#endif
#ifndef PROTO_LOCAL_File_Load
void *File_Load(const char *path);
#endif
#ifndef PROTO_LOCAL_File_LoadAllocV
void *File_LoadAllocV(void *heap, s32 align, u32 *outSize, const char *fmt, va_list va);
#endif
#ifndef PROTO_LOCAL_File_LoadAllocF
void *File_LoadAllocF(void *heap, s32 align, const char *fmt, ...);
#endif
#ifndef PROTO_LOCAL_File_LoadToBufferF
s32 File_LoadToBufferF(void *dst, u32 n, const char *fmt, ...);
#endif
#ifndef PROTO_LOCAL_File_GetDecodedSizeByPath
s32 File_GetDecodedSizeByPath(const char *path);
#endif
#endif

#endif
