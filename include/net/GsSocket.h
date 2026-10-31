#ifndef NET_GSSOCKET_H
#define NET_GSSOCKET_H

#include "types.h"


struct GsSockAddr {
    /* 0x0 */ u8 b[8];
};

struct GsHostAddrList {
    /* 0x0 */ u32 *firstAddr;
    /* 0x4 */ u32 listEnd;
    /* 0x8 */ u8 pad_08[0x10];
};

struct GsHostAddr {
    /* 0x00 */ u32 hostIp;
    /* 0x04 */ u8 pad_04[0x10];
};

struct GsPollFd {
    /* 0x0 */ s32 fd;
    /* 0x4 */ s16 events;
    /* 0x6 */ s16 revents;
};

#endif
