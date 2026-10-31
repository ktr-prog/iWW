#ifndef NET_SOCKSTARTUPCONFIG_H
#define NET_SOCKSTARTUPCONFIG_H

#include "types.h"


typedef void *(*SockAllocFunc)(s32, u32);
typedef void (*SockFreeFunc)(s32, void *, u32);

typedef struct SockStartupConfig SockStartupConfig;
struct SockStartupConfig {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ SockAllocFunc allocFunc;
    /* 0x08 */ SockFreeFunc freeFunc;
    /* 0x0c */ u32 dhcpMode;
    /* 0x10 */ u32 ownIp;
    /* 0x14 */ u32 netmask;
    /* 0x18 */ u32 gateway;
    /* 0x1c */ u32 dns1;
    /* 0x20 */ u32 dns2;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ u32 unk_28;
    /* 0x2c */ u32 mtu;
    /* 0x30 */ u32 recvWindow;
    /* 0x34 */ u32 unk_34[5];
    /* 0x48 */ const char *hostName;
    /* 0x4c */ u32 unk_4c;
    /* 0x50 */ u32 unk_50[2];
};

#endif
