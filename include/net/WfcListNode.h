#ifndef NET_WFCLISTNODE_H
#define NET_WFCLISTNODE_H

#include "types.h"

struct WfcListNode {
    /* 0x0 */ WfcListNode *prev;
    /* 0x4 */ WfcListNode *next;
};

#endif
