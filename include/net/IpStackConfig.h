#ifndef NET_IPSTACKCONFIG_H
#define NET_IPSTACKCONFIG_H

#include "types.h"
#include "nitro/math.h"


struct IpStackConfig {
    /* 0x00 */ u32 stackFlags;
    /* 0x04 */ void *(*allocFunc)(u32);
    /* 0x08 */ void (*freeFunc)(void *);
    /* 0x0c */ void (*addrReadyCallback)(void);
    /* 0x10 */ s32 (*linkCheckCallback)(void);
    /* 0x14 */ u32 randSeed;
    /* 0x18 */ u32 randSeedHi;
    /* 0x1c */ u8 *recvRingBuf;
    /* 0x20 */ u32 recvRingSize;
    /* 0x24 */ u32 mss;
    /* 0x28 */ u32 requestedIp;
    /* 0x2c */ u32 yieldMode;
};

struct IpRandStateSigned {
    /* 0x00 */ s64 x;
    /* 0x08 */ s64 mul;
    /* 0x10 */ s64 add;
};

struct IpRandStateSignedStep {
    /* 0x00 */ u64 x;
    /* 0x08 */ s64 mul;
    /* 0x10 */ s64 add;
};

#endif
