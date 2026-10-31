#ifndef NET_WFCPOOL_H
#define NET_WFCPOOL_H

#include "types.h"

struct WfcPool {
    /* 0x0 */ u16 capacity;
    /* 0x2 */ u8 head;
    /* 0x3 */ u8 top;
    /* 0x4 */ void *entries[1];
};

#endif
