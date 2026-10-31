#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_021096D4_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_021096D4_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NNS_SndLockChannel
BOOL NNS_SndLockChannel(u32 m);
#endif
#ifndef PROTO_LOCAL_NNS_SndUnlockChannel
void NNS_SndUnlockChannel(u32 m);
#endif
#ifndef PROTO_LOCAL_NNS_SndLockCapture
BOOL NNS_SndLockCapture(u32 m);
#endif
#ifndef PROTO_LOCAL_NNS_SndUnlockCapture
void NNS_SndUnlockCapture(u32 m);
#endif
#ifndef PROTO_LOCAL_NNS_SndAllocAlarm
s32 NNS_SndAllocAlarm(void);
#endif
#ifndef PROTO_LOCAL_NNS_SndFreeAlarm
void NNS_SndFreeAlarm(s32 n);
#endif
#ifndef PROTO_LOCAL_NNSi_SndInitResourceMgr
void NNSi_SndInitResourceMgr(void);
#endif
#ifdef __cplusplus
}
#endif

#endif
