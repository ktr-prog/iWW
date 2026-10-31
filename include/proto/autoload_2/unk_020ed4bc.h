#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020ED4BC_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020ED4BC_H


#include "types.h"
#include "sys/ListNode.h"
#ifdef __cplusplus
#include "sys/QNode.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Task_GetPhaseName
const char *Task_GetPhaseName(u32 a);
#endif
#ifndef PROTO_LOCAL_Task_RunAllPhases
void Task_RunAllPhases(void);
#endif
#ifndef PROTO_LOCAL_Task_RunDrawPhase
void Task_RunDrawPhase(void);
#endif
#ifndef PROTO_LOCAL_Task_RunFrame
void Task_RunFrame(s32 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Task_InsertByPriority
BOOL Task_InsertByPriority(List *list, QNode *node);
#endif
#ifndef PROTO_LOCAL_ProcList_FindById
void *ProcList_FindById(QList *list, u32 id);
#endif
#ifndef PROTO_LOCAL_ProcList_FindByProfile
void *ProcList_FindByProfile(QList *list, u32 id, QNode *p);
#endif
}
#endif

#endif
