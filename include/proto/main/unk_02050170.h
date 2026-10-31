#ifndef PROTO_PROTO_MAIN_UNK_02050170_H
#define PROTO_PROTO_MAIN_UNK_02050170_H


#include "types.h"
#ifdef __cplusplus
#include "save/Backup.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Backup_InitDefault
void Backup_InitDefault(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Backup_Init
void Backup_Init(Backup *g, s32 n, const char *name);
#endif
}
#endif

#endif
