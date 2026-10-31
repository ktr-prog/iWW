#ifndef NET_WIFILINKCONFIG_H
#define NET_WIFILINKCONFIG_H

#include "types.h"

struct WifiLinkConfig {
    /* 0x0 */ s32 dmaNo;
    /* 0x4 */ void *bssDescBuffer;
    /* 0x8 */ s32 bssDescBufferSize;
    /* 0xc */ s32 bssDescMode;
};
#ifndef __cplusplus
typedef struct WifiLinkConfig WifiLinkConfig;
#endif

#endif
