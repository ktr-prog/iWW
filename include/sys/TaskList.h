#ifndef SYS_TASKLIST_H
#define SYS_TASKLIST_H

#include "types.h"
#include "sys/QNode.h"
#include "sys/TreeNode.h"

class ProcBase;
typedef void (ProcBase::*TaskFn)();

class TaskList {
public:
    TaskList(TaskFn f) : head(0), tail(0), fn(f) {}
    BOOL run();

    /* 0x00 */ QNode *head;
    /* 0x04 */ QNode *tail;
    /* 0x08 */ TaskFn fn;
};

class TaskTree {
public:
    TaskTree(TaskFn f) : head(0), fn(f) {}
    BOOL run();

    /* 0x00 */ TreeNode *head;
    /* 0x04 */ TaskFn fn;
};
typedef TaskTree TaskList4;

#endif
