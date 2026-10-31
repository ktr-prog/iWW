#ifndef SYS_PRIOLISTNODE_H
#define SYS_PRIOLISTNODE_H

#include "types.h"

class PrioListNode {
public:
    /* 0x0 */ uptr prev;
    /* 0x4 */ uptr next;
    /* 0x8 */ u8 priority;

    PrioListNode() : prev(0), next(0), priority(0xff) {}
    MWCC_LAYOUT
};

#endif
