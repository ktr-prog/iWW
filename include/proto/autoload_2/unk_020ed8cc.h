#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020ED8CC_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020ED8CC_H


#include "types.h"
#include "snd/SndSeqHandle.h"
#include "sys/FndList.h"
#ifdef __cplusplus
#include "snd/Player.h"
#include "sys/CmdSeq.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Snd_GetHeap
void *Snd_GetHeap(void);
#endif
#ifndef PROTO_LOCAL_Snd_InitSystem
void Snd_InitSystem(void *heapStart, u32 heapSize, const char *arcPath, void *arcMem);
#endif
#ifndef PROTO_LOCAL_Snd_CaptureBufferDisposeCallback
void Snd_CaptureBufferDisposeCallback(void *mem, u32 size, void *a, u32 b);
#endif
#ifndef PROTO_LOCAL_Snd_StartOutputEffect
void Snd_StartOutputEffect(s32 a);
#endif
#ifndef PROTO_LOCAL_Snd_AllocCaptureBuffer
void Snd_AllocCaptureBuffer(void);
#endif
#ifndef PROTO_LOCAL_Snd_Main
void Snd_Main(void);
#endif
#ifndef PROTO_LOCAL_Snd_StartSeqArcDefault
void Snd_StartSeqArcDefault(u32 idx, u32 arcNo);
#endif
#ifndef PROTO_LOCAL_Snd_StartSeqArc
void Snd_StartSeqArc(u32 idx, u32 arcNo, void *handle);
#endif
#ifndef PROTO_LOCAL_Snd_StartSeqArcEx
void Snd_StartSeqArcEx(void *handle, s32 player, s32 bank, s32 prio, u32 arcNo, u32 idx);
#endif
#ifndef PROTO_LOCAL_Snd_InitHandle
void Snd_InitHandle(void *a);
#endif
#ifndef PROTO_LOCAL_Snd_StopHandle
void Snd_StopHandle(void *a, s32 frames);
#endif
#ifndef PROTO_LOCAL_Snd_LoadGroup
s32 Snd_LoadGroup(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_RestoreHeapLevel
s32 Snd_RestoreHeapLevel(u32 a);
#endif
#ifndef PROTO_LOCAL_Snd_GetHeapLevel
s32 Snd_GetHeapLevel(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SndSeSystem_Shutdown
void SndSeSystem_Shutdown(Player *o, s32 flag);
#endif
#ifndef PROTO_LOCAL_SndSeSystem_UnloadGroup
void SndSeSystem_UnloadGroup(Player *o);
#endif
#ifndef PROTO_LOCAL_SndSeGroupList_StopAll
void SndSeGroupList_StopAll(FndList *o);
#endif
#ifndef PROTO_LOCAL_CmdSeq_Undo
void CmdSeq_Undo(CmdSeq *o);
#endif
}
#ifndef PROTO_LOCAL_gSndHeap
extern void *gSndHeap;
#endif
#ifndef PROTO_LOCAL_gSndDefaultHandle
extern SndSeqHandle gSndDefaultHandle;
#endif
#ifndef PROTO_LOCAL_gSndCaptureBuffer
extern void *gSndCaptureBuffer;
#endif
#ifndef PROTO_LOCAL_gSndSeSystem
extern Player gSndSeSystem;
#endif
#endif

#endif
