#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020EC848_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020EC848_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "sys/Heap.h"
#include "sys/ProcBase.h"
#include "sys/TreeNode.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_gProcCreateStep
extern u8 gProcCreateStep;
#endif
#ifndef PROTO_LOCAL_sProcCreateGroup
extern u8 sProcCreateGroup;
#endif
#ifndef PROTO_LOCAL_gProcCreateProfile
extern u16 gProcCreateProfile;
#endif
#ifndef PROTO_LOCAL_sProcCreateProfile
extern u16 sProcCreateProfile;
#endif
#ifndef PROTO_LOCAL_sProcCreateHook
extern u32 (*sProcCreateHook) (u32);
#endif
#ifndef PROTO_LOCAL_sProcDeleteHook
extern void (*sProcDeleteHook) (u32);
#endif
#ifndef PROTO_LOCAL_sProcCreateParam
extern u32 sProcCreateParam;
#endif
#ifndef PROTO_LOCAL_sProcNextId
extern u32 sProcNextId;
#endif
#ifndef PROTO_LOCAL_Proc_CallCreateHook
u32 Proc_CallCreateHook(u32 a);
#endif
#ifndef PROTO_LOCAL_Proc_CallDeleteHook
void Proc_CallDeleteHook(u32 a);
#endif
#ifndef PROTO_LOCAL_Main_InitTick
void Main_InitTick(void);
#endif
#ifndef PROTO_LOCAL_Mem_AllocForNew
void *Mem_AllocForNew(u32 size);
#endif
#ifndef PROTO_LOCAL_Mem_FreeForDelete
void Mem_FreeForDelete(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sProcCreateParent
extern TreeNode *sProcCreateParent;
#endif
#ifndef PROTO_LOCAL_gProfileTable
extern ProcProfile * *gProfileTable;
#endif
#ifndef PROTO_LOCAL_ProcBase_SetHeap
void ProcBase_SetHeap(ProcBase *self, Heap *heap);
#endif
#ifndef PROTO_LOCAL_ProcBase_RequestDelete
void ProcBase_RequestDelete(ProcBase *self);
#endif
#ifndef PROTO_LOCAL_ProcBase_GetParent
ProcBase *ProcBase_GetParent(ProcBase *self);
#endif
#ifndef PROTO_LOCAL_ProcBase_SetExecutePriority
void ProcBase_SetExecutePriority(ProcBase *self, u16 v);
#endif
#ifndef PROTO_LOCAL_ProcBase_SetDrawPriority
void ProcBase_SetDrawPriority(ProcBase *self, u16 v);
#endif
#ifndef PROTO_LOCAL_ProcBase_StartCreate
void ProcBase_StartCreate(ProcBase *self);
#endif
#ifndef PROTO_LOCAL_ProcBase_HasCreatingChild
BOOL ProcBase_HasCreatingChild(ProcBase *self);
#endif
#ifndef PROTO_LOCAL_Proc_SetCreateParams
void Proc_SetCreateParams(u32 a, TreeNode *parent, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Proc_Create
ProcBase *Proc_Create(u32 a, TreeNode *parent, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Proc_CreateChild
ProcBase *Proc_CreateChild(u32 a, ProcBase *parent, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Proc_CreateRoot
ProcBase *Proc_CreateRoot(u32 a, u32 b, u32 c);
#endif
}
#endif

#endif
