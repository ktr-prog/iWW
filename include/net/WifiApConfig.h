#ifndef NET_WIFIAPCONFIG_H
#define NET_WIFIAPCONFIG_H

#include "types.h"


typedef void *(*WifiApAllocFunc)(u32, u32);
typedef void (*WifiApFreeFunc)(u32, void *, u32);

typedef struct WifiApConfig {
    /* 0x0 */ WifiApAllocFunc allocFunc;
    /* 0x4 */ WifiApFreeFunc freeFunc;
    /* 0x8 */ u8 dmaNo;
    /* 0x9 */ u8 powerMode;
    /* 0xa */ u8 apFilter;
    /* 0xb */ u8 netCheckMode;
} WifiApConfig;

typedef struct WifiApAllocator {
    /* 0x0 */ WifiApAllocFunc allocFunc;
    /* 0x4 */ WifiApFreeFunc freeFunc;
    /* 0x8 */ u32 unk_08;
} WifiApAllocator;

#endif
