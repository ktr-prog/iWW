#ifndef NET_FRIENDENTRY_H
#define NET_FRIENDENTRY_H

#include "types.h"

struct FriendEntry {
    /* 0x00 */ u8 friendData[0xc];
    /* 0x0c */ u8 playerName[8];
    /* 0x14 */ u8 townName[8];
};

struct FriendList {
    /* 0x000 */ FriendEntry entries[0x20];
    /* 0x380 */ u16 checksum;
};

struct PlayerWifiData {
    /* 0x00 */ u8 userData[0x40];
    /* 0x40 */ u8 ownFriendData[0xc];
    /* 0x4c */ u16 checksum;
};

#endif
