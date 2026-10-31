#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02119020_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02119020_H


#include "types.h"
#include "nitro/fs.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FS_InitArchive
void FS_InitArchive(FSArc *arc);
#endif
#ifndef PROTO_LOCAL_FS_FindArchive
FSArc *FS_FindArchive(const char *name, int len);
#endif
#ifndef PROTO_LOCAL_FS_ReleaseArchiveName
void FS_ReleaseArchiveName(FSArc *arc);
#endif
#ifdef __cplusplus
}
#endif

#endif
