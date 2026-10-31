#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_0211C8E8_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_0211C8E8_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PMi_WaitBusy
void PMi_WaitBusy(void);
#endif
#ifndef PROTO_LOCAL_PMi_DummyCallback
void PMi_DummyCallback(u32 result, void *arg);
#endif
#ifndef PROTO_LOCAL_PMi_CallCallbackAndUnlock
void PMi_CallCallbackAndUnlock(u32 result);
#endif
#ifndef PROTO_LOCAL_PM_Init
void PM_Init(void);
#endif
#ifndef PROTO_LOCAL_PMi_CommonCallback
void PMi_CommonCallback(u32 tag, u32 data, u32 err);
#endif
#ifdef __cplusplus
}
#endif

#endif
