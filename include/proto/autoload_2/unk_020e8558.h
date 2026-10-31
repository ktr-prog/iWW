#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020E8558_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020E8558_H


#include "types.h"
#ifdef __cplusplus
#include "sys/Heap.h"
class ExpHeap;
class FrameHeap;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Heap_OnThreadSwitch
void Heap_OnThreadSwitch(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_Heap_InstallThreadSwitchCallback
void Heap_InstallThreadSwitchCallback(void);
#endif
#ifndef PROTO_LOCAL_Heap_InitSystem
void Heap_InitSystem(void);
#endif
#ifndef PROTO_LOCAL_ExpHeap_FreeBlockVisitor
void ExpHeap_FreeBlockVisitor(void *block, void *heap, u32 param);
#endif
#ifndef PROTO_LOCAL_Heap_SaveCurrent
void Heap_SaveCurrent(void);
#endif
#ifndef PROTO_LOCAL_Heap_RestoreCurrent
void Heap_RestoreCurrent(void);
#endif
#ifndef PROTO_LOCAL_Mem_AllocAligned
void *Mem_AllocAligned(u32 size, s32 align);
#endif
#ifndef PROTO_LOCAL_Mem_AllocTail
void *Mem_AllocTail(u32 size);
#endif
#ifndef PROTO_LOCAL_Mem_Alloc
void *Mem_Alloc(u32 size);
#endif
#ifndef PROTO_LOCAL_Mem_Free
void Mem_Free(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Heap_SetThreadHeap
void Heap_SetThreadHeap(void *thread, Heap *heap);
#endif
#ifndef PROTO_LOCAL_Heap_CreateRootHeap
ExpHeap *Heap_CreateRootHeap(void *p, u32 n);
#endif
#ifndef PROTO_LOCAL_ExpHeap_CreateInPlace
ExpHeap *ExpHeap_CreateInPlace(void *p, u32 n);
#endif
#ifndef PROTO_LOCAL_ExpHeap_Create
ExpHeap *ExpHeap_Create(u32 size, Heap *parent);
#endif
#ifndef PROTO_LOCAL_FrameHeap_Create
FrameHeap *FrameHeap_Create(u32 size, Heap *parent);
#endif
#ifndef PROTO_LOCAL_Heap_SetCurrent
Heap *Heap_SetCurrent(Heap *heap);
#endif
#ifndef PROTO_LOCAL_FrameHeap_CreateAsCurrent
Heap *FrameHeap_CreateAsCurrent(u32 size, Heap *parent);
#endif
#ifndef PROTO_LOCAL_Heap_AllocAligned
void *Heap_AllocAligned(Heap *heap, u32 size, s32 align);
#endif
#ifndef PROTO_LOCAL_Heap_AllocTail
void *Heap_AllocTail(Heap *heap, u32 size);
#endif
#ifndef PROTO_LOCAL_Heap_Alloc
void *Heap_Alloc(Heap *heap, u32 size);
#endif
#ifndef PROTO_LOCAL_Heap_Free
void Heap_Free(Heap *heap, void *p);
#endif
#ifndef PROTO_LOCAL_Heap_CreateProcHeap
void Heap_CreateProcHeap(u32 size, Heap *parent);
#endif
}
#ifndef PROTO_LOCAL_sRootHeapSize
extern u32 sRootHeapSize;
#endif
#ifndef PROTO_LOCAL_sHeapSystemReady
extern u8 sHeapSystemReady;
#endif
#ifndef PROTO_LOCAL_sRootHeapArenaId
extern u32 sRootHeapArenaId;
#endif
#ifndef PROTO_LOCAL_gCurrentHeap
extern Heap *gCurrentHeap;
#endif
#ifndef PROTO_LOCAL_gHeapCreateOption
extern u16 gHeapCreateOption;
#endif
#ifndef PROTO_LOCAL_sSavedCurrentHeap
extern Heap *sSavedCurrentHeap[16];
#endif
#ifndef PROTO_LOCAL_gProcHeap
extern Heap *gProcHeap;
#endif
#ifndef PROTO_LOCAL_gRootHeap
extern Heap *gRootHeap;
#endif
#endif

#endif
