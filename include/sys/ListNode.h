#ifndef SYS_LISTNODE_H
#define SYS_LISTNODE_H

#include "types.h"

#ifndef __cplusplus
typedef struct ListNode ListNode;
typedef struct List List;
#endif

struct ListNode {
    /* 0x0 */ ListNode *prev;
    /* 0x4 */ ListNode *next;
};

struct List {
    /* 0x0 */ ListNode *head;
    /* 0x4 */ ListNode *tail;

#ifdef __cplusplus
    List() : head(0), tail(0) {}
#endif
};

#endif
