#ifndef NET_DWCFRIENDCONTROL_H
#define NET_DWCFRIENDCONTROL_H

#include "types.h"
#include "net/gp.h"


#ifndef __cplusplus
typedef struct DwcFriendData DwcFriendData;
typedef struct DwcFriendControl DwcFriendControl;
#endif

struct DwcFriendData {
#ifdef __cplusplus
    DwcFriendData();
    ~DwcFriendData();
#endif

    /* 0x00 */ u8 unk_00[0xc];
};

typedef void (*DwcFriendUpdateCallback)(s32, u32, s32);
typedef void (*DwcFriendStatusCallback)(s32, s32, char *, s32);
typedef void (*DwcFriendDeleteCallback)(s32, s32, s32);
typedef void (*DwcFriendAddedCallback)(s32, s32);

struct DwcFriendControl {
    /* 0x00 */ s32 updateState;
    /* 0x04 */ GPConnection *gpConnection;
    /* 0x08 */ u32 tickCount;
    /* 0x0c */ u32 lastTick;
    /* 0x10 */ u32 lastProcessTickHi;
    /* 0x14 */ s32 numFriends;
    /* 0x18 */ DwcFriendData *friendList;
    /* 0x1c */ u8 syncIndex;
    /* 0x1d */ u8 isListChanged;
    /* 0x1e */ u8 syncPhase;
    /* 0x1f */ u8 updateStep;
    /* 0x20 */ u32 usePersist;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ char *buddyRequestText;
    /* 0x2c */ DwcFriendUpdateCallback updateCallback;
    /* 0x30 */ s32 updateCallbackArg;
    /* 0x34 */ DwcFriendStatusCallback statusCallback;
    /* 0x38 */ s32 statusCallbackArg;
    /* 0x3c */ DwcFriendDeleteCallback deleteCallback;
    /* 0x40 */ s32 deleteCallbackArg;
    /* 0x44 */ DwcFriendAddedCallback addedCallback;
    /* 0x48 */ s32 addedCallbackArg;
    /* 0x4c */ u32 unk_4c;
    /* 0x50 */ u32 unk_50;
};

#endif
