#ifndef NET_NET_H
#define NET_NET_H

#include "types.h"
#include "net/DwcUserData.h"


typedef void (*NetSendDoneFn)(u32 size);
typedef void (*NetRecvFn)(u32 aid, u8 *data, u32 size);
typedef void (*NetFriendFn)(u32 index);
typedef void *(*NetAllocFn)(u32 size, u32 align);
typedef void (*NetFreeFn)(void *p);

typedef struct NetWifiUserData {
    /* 0x00 */ char playerName[8];
    /* 0x08 */ char townName[8];
    /* 0x10 */ DwcUserData userData;
    /* 0x38 */ u8 pad38[0x50 - 0x10 - sizeof(DwcUserData)];
} NetWifiUserData;

typedef struct NetWifiFriendData {
    u8 data[12];
} NetWifiFriendData;
typedef struct NetWifiFriendStatus {
    char statusString[16];
    u8 status;
    u8 b;
    u8 c;
} NetWifiFriendStatus;
typedef struct NetWifiFriends {
    /* 0x000 */ NetWifiFriendData friends[32];
    /* 0x180 */ NetWifiFriendStatus status[32];
} NetWifiFriends;

#endif
