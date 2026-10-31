#ifndef NET_AOSSPARAM_H
#define NET_AOSSPARAM_H

#include "types.h"

typedef union AossClientInfo AossClientInfo;
typedef struct AossParam AossParam;
typedef struct AossApInfo AossApInfo;
typedef struct AossApConfig AossApConfig;
typedef struct AossConnectResult AossConnectResult;


union AossClientInfo {
    /* 0x000 */ u16 words[0x82];
    struct {
        /* 0x000 */ u8 tlvType;
        /* 0x001 */ u8 pad_01;
        /* 0x002 */ u16 nameLength;
        /* 0x004 */ u8 name[0x100];
    };
};

struct AossParam {
    /* 0x000 */ u16 keyTypeMask;
    /* 0x002 */ AossClientInfo clientInfo;
    /* 0x106 */ s16 apRetryCount;
    /* 0x108 */ s16 apRetryWait;
    /* 0x10a */ s16 packetRetryCount;
    /* 0x10c */ s16 packetRetryWait;
    /* 0x10e */ s16 recvTimeout;
    /* 0x110 */ u8 macAddress[6];
    /* 0x116 */ u8 errorCode;
    /* 0x117 */ u8 result[0x155];
};

struct AossApInfo {
    /* 0x00 */ u32 ssidLength;
    /* 0x04 */ u8 ssid[0x20];
    /* 0x24 */ u32 channel;
    /* 0x28 */ u8 pad_28[8];
    /* 0x30 */ u8 bssid[6];
    /* 0x36 */ u8 pad_36[2];
    /* 0x38 */ u32 numRates;
    /* 0x3c */ u8 rates[0x10];
    /* 0x4c */ u32 beaconPeriod;
    /* 0x50 */ u32 bssType;
};

struct AossApConfig {
    /* 0x00 */ s32 ssidLength;
    /* 0x04 */ u8 ssid[0x20];
    /* 0x24 */ s32 mode;
    /* 0x28 */ s32 wepKeyLength;
    /* 0x2c */ u8 wepKey[0x10];
};

struct AossConnectResult {
    /* 0x00 */ s32 connected;
    /* 0x04 */ AossApInfo ap;
};

#endif
