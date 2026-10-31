#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_0210DA28_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_0210DA28_H


#include "types.h"
#include "nnsys/fnd_list.h"
#include "nnsys/snd_arcstrm.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_OutputEffectMono
void OutputEffectMono(s16 *l, s16 *r, u32 len);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcStrmInit
void NNS_SndArcStrmInit(u32 prio, void *heap);
#endif
#ifndef PROTO_LOCAL_SetupStrmPlayers
BOOL SetupStrmPlayers(void *heap);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcStrmPrepare
BOOL NNS_SndArcStrmPrepare(NNSSndStrmPlayer **h, s32 strmNo, s32 len);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcStrmStartPrepared
void NNS_SndArcStrmStartPrepared(NNSSndStrmPlayer **h);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcStrmStart
BOOL NNS_SndArcStrmStart(NNSSndStrmPlayer **h, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcStrmStop
void NNS_SndArcStrmStop(NNSSndStrmPlayer **h, s32 frames);
#endif
#ifndef PROTO_LOCAL_NNS_SndArcStrmMoveVolume
void NNS_SndArcStrmMoveVolume(NNSSndStrmPlayer **h, s32 vol, s32 frames);
#endif
#ifndef PROTO_LOCAL_NNS_SndStrmHandleInit
void NNS_SndStrmHandleInit(NNSSndStrmPlayer **h);
#endif
#ifndef PROTO_LOCAL_NNS_SndStrmHandleRelease
void NNS_SndStrmHandleRelease(NNSSndStrmPlayer **h);
#endif
#ifndef PROTO_LOCAL_func_0210e648
u32 func_0210e648(NNSSndStrmPlayer **h);
#endif
#ifndef PROTO_LOCAL_func_0210e5fc
u32 func_0210e5fc(NNSSndStrmPlayer **h);
#endif
#ifndef PROTO_LOCAL_NNSi_SndArcStrmMain
void NNSi_SndArcStrmMain(void);
#endif
#ifndef PROTO_LOCAL_AllocPlayer
NNSSndStrmPlayer *AllocPlayer(NNSSndStrmPlayer **h, s32 idx, s32 prio);
#endif
#ifndef PROTO_LOCAL_FreePlayer
void FreePlayer(NNSSndStrmPlayer *c);
#endif
#ifndef PROTO_LOCAL_PrepareStrmCore
BOOL PrepareStrmCore(NNSSndStrmPlayer **h, NNSSndArcStrmInfo *info, s32 playerNo, s32 prio, s32 strmNo, u32 offset, NNSSndStrmCallback strmCallback, void *strmCallbackArg, NNSSndArcStrmCallback sndArcStrmCallback, void *sndArcStrmCallbackArg);
#endif
#ifndef PROTO_LOCAL_StopStrm
void StopStrm(NNSSndStrmPlayer *c, s32 frames);
#endif
#ifndef PROTO_LOCAL_ForceStopStrm__sndarc_stream
void ForceStopStrm__sndarc_stream(NNSSndStrmPlayer *c);
#endif
#ifndef PROTO_LOCAL_ShutdownPlayer__sndarc_stream
void ShutdownPlayer__sndarc_stream(NNSSndStrmPlayer *c);
#endif
#ifndef PROTO_LOCAL_AllocChannel
BOOL AllocChannel(NNSSndStrmPlayer *c, s32 n, u8 *x);
#endif
#ifndef PROTO_LOCAL_FreeChannel
void FreeChannel(NNSSndStrmPlayer *c);
#endif
#ifndef PROTO_LOCAL_CreateStrmThread
void CreateStrmThread(NNSSndStrmThread *t, u32 prio);
#endif
#ifndef PROTO_LOCAL_RemoveCommandByPlayer
void RemoveCommandByPlayer(NNSFndList *list, NNSSndStrmPlayer *c);
#endif
#ifndef PROTO_LOCAL_PopCommandBuffer
NNSSndStrmLoadCommand *PopCommandBuffer(NNSFndList *list);
#endif
#ifndef PROTO_LOCAL_AllocCommandBuffer
NNSSndStrmLoadCommand *AllocCommandBuffer(void);
#endif
#ifndef PROTO_LOCAL_FreeCommandBuffer
void FreeCommandBuffer(NNSSndStrmLoadCommand *job);
#endif
#ifndef PROTO_LOCAL_StrmBufDisposeCallback
void StrmBufDisposeCallback(void *mem, u32 size, void *arg, u32 unused);
#endif
#ifndef PROTO_LOCAL_StrmDataCallback
void StrmDataCallback(s32 ch, s32 n, NNSSndStrmBufAddr *bufs, u32 size, s32 unused, void *arg);
#endif
#ifndef PROTO_LOCAL_RequestNextStrm
void RequestNextStrm(NNSSndStrmPlayer *c);
#endif
#ifdef __cplusplus
}
#endif

#endif
