#ifndef NET_SOCKADDRIN_H
#define NET_SOCKADDRIN_H

#include "types.h"

typedef struct SockAddrIn SockAddrIn;

typedef struct SockAddrIn SockAddrIn;
struct SockAddrIn {
    /* 0x0 */ u8 len;
    /* 0x1 */ u8 family;
    /* 0x2 */ u16 port;
    /* 0x4 */ u32 addr;
};

#endif
