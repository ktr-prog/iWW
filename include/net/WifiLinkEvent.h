#ifndef NET_WIFILINKEVENT_H
#define NET_WIFILINKEVENT_H

#include "types.h"
#include "nitro/wm.h"


struct WifiLinkEvent {
    /* 0x00 */ s16 request;
    /* 0x02 */ s16 result;
    /* 0x04 */ WMBssDesc *bssDesc;
    /* 0x08 */ u32 detail;
    /* 0x0c */ s32 sourceLine;
};

typedef void (*WifiLinkNotifyCallback)(WifiLinkEvent *);

#endif
