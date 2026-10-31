#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02119434_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02119434_H


#include "types.h"
#include "nitro/fs.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FS_InitFile
void FS_InitFile(FSFile *file);
#endif
#ifndef PROTO_LOCAL_FS_CancelFile
void FS_CancelFile(FSFile *file);
#endif
#ifndef PROTO_LOCAL_FSi_NextCommand
FSFile *FSi_NextCommand(volatile FSArc *arc);
#endif
#ifndef PROTO_LOCAL_FSi_ExecuteAsyncCommand
void FSi_ExecuteAsyncCommand(FSFile *file);
#endif
#ifndef PROTO_LOCAL_FSi_ExecuteSyncCommand
int FSi_ExecuteSyncCommand(FSFile *file);
#endif
#ifdef __cplusplus
}
#endif

#endif
