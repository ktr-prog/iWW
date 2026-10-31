#ifndef NET_WIFILINKSENDSTATE_H
#define NET_WIFILINKSENDSTATE_H

#include "types.h"


typedef void (*WifiLinkRecvCallback)(void *, void *, void *, u32);

struct WifiLinkSendState {
    /* 0x00 */ u8 initialized;
    /* 0x01 */ u8 unk_01[3];
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0c */ u8 unk_0c[0x18];
    /* 0x24 */ s32 sendResult;
    /* 0x28 */ WifiLinkRecvCallback recvCallback;
};

#endif
