#ifndef PROTO_PROTO_OV001_UNK_OV001_02223FC4_H
#define PROTO_PROTO_OV001_UNK_OV001_02223FC4_H


#include "types.h"
#include "nitro/fs.h"
struct WfcFsWork;
#ifndef __cplusplus
typedef struct WfcFsWork WfcFsWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcFs_MountArchive
void WfcFs_MountArchive();
#endif
#ifndef PROTO_LOCAL_WfcFs_UnmountArchive
void WfcFs_UnmountArchive();
#endif
#ifndef PROTO_LOCAL_WfcFs_ArchiveProc
int WfcFs_ArchiveProc(FSFile *file, u32 cmd);
#endif
#ifndef PROTO_LOCAL_WfcFs_ReadCallback
int WfcFs_ReadCallback(FSArc *arc, void *dst, u32 pos, u32 size);
#endif
#ifndef PROTO_LOCAL_WfcFs_OnReadDone
void WfcFs_OnReadDone(void *arc);
#endif
#ifndef PROTO_LOCAL_WfcFs_WriteCallback
int WfcFs_WriteCallback(FSArc *arc, void *src, u32 pos, u32 size);
#endif
#ifndef PROTO_LOCAL_WfcFs_LoadFile
void *WfcFs_LoadFile(void *name, u32 *outSize, s32 c);
#endif
#ifndef PROTO_LOCAL_WfcFs_FreeFile
void WfcFs_FreeFile(void *p, ...);
#endif
#ifndef PROTO_LOCAL_WfcUtil_StrEndsWith
BOOL WfcUtil_StrEndsWith(const void *a, const void *b, s32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcFs
extern WfcFsWork *sWfcFs;
#endif
}
#endif

#endif
