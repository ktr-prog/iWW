#ifndef NET_WFCAPSCANENTRY_H
#define NET_WFCAPSCANENTRY_H

#include "types.h"

struct WfcApScanEntry {
    /* 0x00 */ u8 ssid[0x20];
    /* 0x20 */ u8 bssid[6];
    /* 0x26 */ u16 linkLevel;
    /* 0x28 */ u8 security;
    /* 0x29 */ u8 unk_29;
};

#endif
