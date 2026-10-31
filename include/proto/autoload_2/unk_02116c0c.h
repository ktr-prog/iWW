#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02116C0C_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02116C0C_H


#include "types.h"
#include "uptr.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SND_Init
void SND_Init(void);
#endif
#ifndef PROTO_LOCAL_SNDi_LockMutex
void SNDi_LockMutex(void);
#endif
#ifndef PROTO_LOCAL_SNDi_UnlockMutex
void SNDi_UnlockMutex(void);
#endif
#ifndef PROTO_LOCAL_SND_StopSeq
void SND_StopSeq(u32 a);
#endif
#ifndef PROTO_LOCAL_SND_PrepareSeq
void SND_PrepareSeq(u32 a, uptr b, u32 c, uptr d);
#endif
#ifndef PROTO_LOCAL_SND_StartPreparedSeq
void SND_StartPreparedSeq(u32 a);
#endif
#ifndef PROTO_LOCAL_SND_SetPlayerTempoRatio
void SND_SetPlayerTempoRatio(u32 a, u32 b);
#endif
#ifdef __cplusplus
}
#endif

#endif
