#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02109830_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02109830_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NNS_SndPlayerSetPlayerVolume
void NNS_SndPlayerSetPlayerVolume(s32 i, u8 v);
#endif
#ifndef PROTO_LOCAL_NNS_SndPlayerSetPlayableSeqCount
void NNS_SndPlayerSetPlayableSeqCount(s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_NNS_SndPlayerSetAllocatableChannel
void NNS_SndPlayerSetAllocatableChannel(s32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_NNS_SndPlayerCreateHeap
BOOL NNS_SndPlayerCreateHeap(s32 playerNo, void *heap, u32 size);
#endif
#ifndef PROTO_LOCAL_NNS_SndPlayerStopSeqByPlayerNo
void NNS_SndPlayerStopSeqByPlayerNo(s32 playerNo, s32 frames);
#endif
#ifndef PROTO_LOCAL_NNS_SndPlayerStopSeqBySeqNo
void NNS_SndPlayerStopSeqBySeqNo(u32 a, u32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_NNS_SndPlayerReadGlobalVariable
BOOL NNS_SndPlayerReadGlobalVariable(s32 a, u16 *out);
#endif
#ifndef PROTO_LOCAL_NNS_SndPlayerWriteGlobalVariable
BOOL NNS_SndPlayerWriteGlobalVariable(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_NNSi_SndPlayerInit
void NNSi_SndPlayerInit(void);
#endif
#ifndef PROTO_LOCAL_NNSi_SndPlayerMain
void NNSi_SndPlayerMain(void);
#endif
#ifdef __cplusplus
}
#endif

#endif
