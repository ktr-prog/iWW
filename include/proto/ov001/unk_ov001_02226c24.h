#ifndef PROTO_PROTO_OV001_UNK_OV001_02226C24_H
#define PROTO_PROTO_OV001_UNK_OV001_02226C24_H


#include "types.h"
struct WfcVramBankState;
#ifndef __cplusplus
typedef struct WfcVramBankState WfcVramBankState;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcGx_SaveVramBanks
void WfcGx_SaveVramBanks();
#endif
#ifndef PROTO_LOCAL_WfcGx_RestoreVramBanks
void WfcGx_RestoreVramBanks();
#endif
#ifndef PROTO_LOCAL_WfcGx_ClearVram
void WfcGx_ClearVram();
#endif
#ifndef PROTO_LOCAL_WfcUtil_UpdateLed
void WfcUtil_UpdateLed();
#endif
#ifndef PROTO_LOCAL_WfcUtil_RestoreLed
void WfcUtil_RestoreLed();
#endif
#ifndef PROTO_LOCAL_WfcUtil_StrNLen
s32 WfcUtil_StrNLen(u8 *s, s32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcSavedVramBanks
extern WfcVramBankState sWfcSavedVramBanks;
#endif
}
#endif

#endif
