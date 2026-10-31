#ifndef SYS_QNODE_H
#define SYS_QNODE_H

#include "types.h"

class ProcBase;

struct QNode {
    /* 0x00 */ QNode *prev;
    /* 0x04 */ QNode *next;
    /* 0x08 */ ProcBase *owner;
    /* 0x0c */ u16 priority;
    /* 0x0e */ u16 pendingPriority;
};

struct QList {
    /* 0x00 */ QNode *head;
    /* 0x04 */ QNode *tail;
};

#endif
