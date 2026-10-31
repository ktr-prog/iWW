#include "types.h"
#include "sys/TaskList.h"
#include "sys/ProcBase.h"
#include "sys/ListNode.h"
#include "proto/autoload_2/unk_020ed4bc.h"
#include "proto/itcm/unk_01ffcfc0.h"

typedef void (ProcBase::*TaskFn)();



struct PrioNodeB { void *a, *b, *c; u16 priority; };





extern "C" {
BOOL List_PushBack(List *list, ListNode *node);
BOOL List_InsertAfter(List *list, ListNode *node, ListNode *after);
void Task_RunDrawPhase(void);
void Task_RunAllPhases(void);

extern QNode *gTaskCurrentNode;
extern s32 gTaskPhase;
extern char data_0213b1a8[];
extern char data_0213b1b0[];
extern char data_0213b1b8[];
extern char data_0213b1c0[];
extern char data_0213b1d8[];
extern char data_0213b1f8[];
extern const char *const sTaskPhaseNames[];
extern TaskTree gProcTree;
extern TaskList gTaskExecuteList;
extern TaskList gTaskCreateList;
extern TaskList gTaskDrawList;
extern TaskList gTaskDeleteList;
}

QNode *gTaskCurrentNode;
s32 gTaskPhase = 1;
char data_0213b1b0[] = "NULL";
char data_0213b1f8[] = "CONNECT";
char data_0213b1c0[] = "CREATE";
char data_0213b1a8[] = "DRAW";
const char *const sTaskPhaseNames[] = {data_0213b1b0, data_0213b1f8, data_0213b1c0, data_0213b1d8, data_0213b1b8, data_0213b1a8};
char data_0213b1d8[] = "EXECUTE";
TaskTree gProcTree(&ProcBase::taskConnect);
TaskList gTaskCreateList(&ProcBase::taskCreate);
TaskList gTaskExecuteList(&ProcBase::taskExecute);
TaskList gTaskDrawList(&ProcBase::taskDraw);
TaskList gTaskDeleteList(&ProcBase::taskDelete);
char data_0213b1b8[] = "DELETE";

BOOL TaskTree::run() {
    TreeNode *n;
    if (fn == 0) return TRUE;
    n = head;
    while (n != NULL) {
        TreeNode *cur = n;
        n = (TreeNode *)TreeNode_GetNextPreOrder(cur);
        (cur->owner->*fn)();
    }
    return TRUE;
}

extern "C" const char *Task_GetPhaseName(u32 a) {
    return sTaskPhaseNames[a];
}

extern "C" void Task_RunAllPhases(void) {
    gTaskPhase = 4;
    gTaskDeleteList.run();
    gTaskPhase = 2;
    gTaskCreateList.run();
    gTaskPhase = 3;
    gTaskExecuteList.run();
    gTaskPhase = 5;
    gTaskDrawList.run();
    gTaskPhase = 1;
    gProcTree.run();
    gTaskPhase = 0;
}

extern "C" void Task_RunDrawPhase(void) {
    gTaskPhase = 5;
    gTaskDrawList.run();
    gTaskPhase = 0;
}

extern "C" void Task_RunFrame(s32 v) {
    if (v != 0) {
        Task_RunDrawPhase();
    } else {
        Task_RunAllPhases();
    }
}

extern "C" BOOL Task_InsertByPriority(List *list, QNode *node) {
    QNode *prev = (QNode *)list->head;
    QNode *next;
    if (node == NULL) return FALSE;
    if (prev == NULL) return List_PushBack(list, (ListNode *)node);
    if (prev->priority > node->priority) return List_InsertAfter(list, (ListNode *)node, NULL);
    while ((next = prev->next) != NULL && next->priority <= ((PrioNodeB *)node)->priority) prev = next;
    return List_InsertAfter(list, (ListNode *)node, (ListNode *)prev);
}

BOOL TaskList::run() {
    QNode *n;
    if (fn == 0) return TRUE;
    n = head;
    gTaskCurrentNode = n;
    if (n != NULL) {
        do {
            QNode *next = n->next;
            (n->owner->*fn)();
            gTaskCurrentNode = next;
            n = next;
        } while (n != NULL);
    }
    return TRUE;
}

extern "C" void *ProcList_FindById(QList *list, u32 id) {
    QNode *n = list->head;
    while (n != NULL) {
        BOOL ne = (n->owner->id != id);
        if (ne == 0) return n;
        n = n->next;
    }
    return NULL;
}

extern "C" void *ProcList_FindByProfile(QList *list, u32 id, QNode *p) {
    QNode *n;
    if (p != NULL) {
        n = p->next;
    } else {
        n = list->head;
    }
    while (n != NULL) {
        BOOL ne = (n->owner->profile != id);
        if (ne == 0) return n;
        n = n->next;
    }
    return NULL;
}
