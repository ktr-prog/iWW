#ifndef NET_WFCCONFIGSLOT_H
#define NET_WFCCONFIGSLOT_H

#include "types.h"

typedef struct WfcWepModeBits WfcWepModeBits;
typedef struct WfcConfigSlot WfcConfigSlot;
typedef struct WfcConfigData WfcConfigData;

struct WfcWepModeBits {
    u8 wepKeySize : 2;
    u8 wepAscii : 6;
};

struct WfcConfigSlot {
    /* 0x00 */ u8 unk_00[0x40];
    /* 0x40 */ u8 ssid[0x20];
    /* 0x60 */ u8 aossWep64Ssid[0x20];
    /* 0x80 */ u8 wepKeys[0x40];
    /* 0xc0 */ u8 ipAddress[4];
    /* 0xc4 */ u8 gateway[4];
    /* 0xc8 */ u8 dnsServers[8];
    /* 0xd0 */ u8 subnetPrefixLen;
    /* 0xd1 */ u8 aossWepKeys[0x15];
    /* 0xe6 */ WfcWepModeBits wepMode;
    /* 0xe7 */ u8 status;
    /* 0xe8 */ u8 unk_e8[7];
    /* 0xef */ u8 configuredMask;
    /* 0xf0 */ u8 editSubnetMask[4];
    /* 0xf4 */ u8 editSlotIndex;
    /* 0xf5 */ u8 editAutoIp;
    /* 0xf6 */ u8 editAutoDns;
    /* 0xf7 */ u8 unk_f7;
    /* 0xf8 */ u8 unk_f8[6];
    /* 0xfe */ u16 crc16;
};

struct WfcConfigData {
    /* 0x000 */ WfcConfigSlot slots[4];
    union {
        /* 0x400 */ WfcConfigSlot editSlot;
        struct {
            /* 0x400 */ u8 editSlotHead[0xf8];
            /* 0x4f8 */ u16 crcTable[0x100];
        };
    };
};

#endif
