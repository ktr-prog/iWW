#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_0211802C_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_0211802C_H


#include "types.h"
#include "nitro/fs.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FSi_OpenFileFastCommand
int FSi_OpenFileFastCommand(FSFile *file);
#endif
#ifndef PROTO_LOCAL_FSi_OpenFileDirectCommand
int FSi_OpenFileDirectCommand(FSFile *file);
#endif
#ifndef PROTO_LOCAL_FSi_CloseFileCommand
int FSi_CloseFileCommand(void);
#endif
#ifndef PROTO_LOCAL_data_0213a388
extern int (*const data_0213a388[9]) (FSFile *);
#endif
#ifdef __cplusplus
}
#endif

#endif
