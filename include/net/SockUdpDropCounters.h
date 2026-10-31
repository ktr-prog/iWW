#ifndef NET_SOCKUDPDROPCOUNTERS_H
#define NET_SOCKUDPDROPCOUNTERS_H

#include "types.h"


struct SockUdpDropCounters {
    /* 0x0 */ u32 noMemDrops;
    /* 0x4 */ u32 queueFullDrops;
};

#endif
