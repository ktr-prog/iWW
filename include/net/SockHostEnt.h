#ifndef NET_SOCKHOSTENT_H
#define NET_SOCKHOSTENT_H

#include "types.h"


struct SockHostEnt {
    /* 0x0 */ char *hostName;
    /* 0x4 */ char **aliases;
    /* 0x8 */ s16 addrType;
    /* 0xa */ s16 addrLength;
    /* 0xc */ char **addrList;
};

#endif
