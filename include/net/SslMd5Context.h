#ifndef NET_SSLMD5CONTEXT_H
#define NET_SSLMD5CONTEXT_H

#include "types.h"


typedef struct SslMd5Context SslMd5Context;
struct SslMd5Context {
    /* 0x00 */ u32 st[4];
    /* 0x10 */ u32 lo;
    /* 0x14 */ u32 hi;
    /* 0x18 */ u8 buf[64];
};

#endif
