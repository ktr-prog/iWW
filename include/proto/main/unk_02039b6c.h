#ifndef PROTO_PROTO_MAIN_UNK_02039B6C_H
#define PROTO_PROTO_MAIN_UNK_02039B6C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_RecycleBin_Construct
void RecycleBin_Construct();
#endif
#ifndef PROTO_LOCAL_RecycleBin_Destruct
void RecycleBin_Destruct();
#endif
#ifndef PROTO_LOCAL_RecycleBin_Clear
void RecycleBin_Clear(u16 *p);
#endif
#ifndef PROTO_LOCAL_RecycleBin_AdvanceDays
void RecycleBin_AdvanceDays(u16 *arr, void *src, s32 n);
#endif
#ifdef __cplusplus
}
#endif

#endif
