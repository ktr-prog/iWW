#ifndef NET_SOCKCORECONFIG_H
#define NET_SOCKCORECONFIG_H

#include "types.h"

struct SockCoreConfig {
    /* 0x00 */ u32 useDhcp;
    /* 0x04 */ u32 ownIp;
    /* 0x08 */ u32 netmask;
    /* 0x0c */ u32 gateway;
    /* 0x10 */ u32 dns1;
    /* 0x14 */ u32 dns2;
    /* 0x18 */ void *(*alloc)(u32);
    /* 0x1c */ void (*free)(void *);
    /* 0x20 */ s32 msgPoolSize;
    /* 0x24 */ u32 recvRingSize;
    /* 0x28 */ u8 *recvRingBuf;
    /* 0x2c */ s32 threadPriority;
    /* 0x30 */ s32 mtu;
    /* 0x34 */ s32 recvWindow;
};

#endif
