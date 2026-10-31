#ifndef NET_SSLSESSION_H
#define NET_SSLSESSION_H

#include "types.h"


typedef struct SslSession SslSession;
struct SslSession {
    /* 0x00 */ u8 sessionId[0x20];
    /* 0x20 */ u8 masterSecret[0x30];
    /* 0x50 */ u32 lastUsed;
    /* 0x54 */ u32 peerAddr;
    /* 0x58 */ u16 peerPort;
    /* 0x5a */ u8 inUse;
    /* 0x5b */ u8 pad_5b;
};

#endif
