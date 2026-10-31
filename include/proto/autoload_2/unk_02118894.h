#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02118894_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02118894_H


#include "types.h"
#include "nitro/fs.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FS_UnloadArchiveTables
void *FS_UnloadArchiveTables(FSArc *arc);
#endif
#ifndef PROTO_LOCAL_FSi_ReadFileCommand
int FSi_ReadFileCommand(FSFile *file);
#endif
#ifndef PROTO_LOCAL_FSi_WriteFileCommand
int FSi_WriteFileCommand(FSFile *file);
#endif
#ifndef PROTO_LOCAL_FSi_SeekDirCommand
int FSi_SeekDirCommand(FSFile *file);
#endif
#ifndef PROTO_LOCAL_FSi_ReadDirCommand
int FSi_ReadDirCommand(FSFile *file);
#endif
#ifdef __cplusplus
}
#endif

#endif
