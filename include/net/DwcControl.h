#ifndef NET_DWCCONTROL_H
#define NET_DWCCONTROL_H

#include "types.h"
#include "net/gp.h"
#include "net/DwcFriendControl.h"
#include "net/DwcUserData.h"
#include "net/DwcMatchControl.h"

#ifndef __cplusplus
typedef struct DwcHttp DwcHttp;
typedef struct DwcLoginControl DwcLoginControl;
typedef struct DwcControl DwcControl;
#endif

struct DwcHttp;


typedef void (*DwcDoneCallback)(s32, s32, s32);
typedef void (*DwcMatchedCallback)(s32, s32, s32);
typedef void (*DwcConnectionClosedCallback)(s32, s32, s32, s32, s32, s32);
typedef void (*DwcLoginResultCallback)(s32, s32, u32);
typedef void (*DwcNasLoginCallback)(const char *, const char *, u32);

struct DwcLoginControl {
    /* 0x000 */ GPConnection *gpConnection;
    /* 0x004 */ s32 state;
    /* 0x008 */ u32 productId;
    /* 0x00c */ u32 gameCode;
    /* 0x010 */ u32 unk_10;
    /* 0x014 */ u32 unk_14;
    /* 0x018 */ DwcLoginResultCallback resultCallback;
    /* 0x01c */ u32 resultCallbackArg;
    /* 0x020 */ DwcUserData *userData;
    /* 0x024 */ u8 unk_24[4];
    /* 0x028 */ DwcHttp *nasAuthWork;
    /* 0x02c */ u64 nasAuthStartTick;
    /* 0x034 */ s32 gpConnectPending;
    /* 0x038 */ u64 gpConnectStartTick;
    /* 0x040 */ DwcLoginId loginId;
    /* 0x04c */ char authToken[0x100];
    /* 0x14c */ char authChallenge[0x100];
    /* 0x24c */ u8 loginIdText[9];
    /* 0x255 */ char gsbrcd[0x264 - 0x255];
};

struct DwcControl {
    /* 0x000 */ void *transportSocket;
    /* 0x004 */ void *gt2ConnectedCallback;
    /* 0x008 */ void *gt2ReceivedCallback;
    /* 0x00c */ void *gt2ClosedCallback;
    /* 0x010 */ void *gt2PingCallback;
    /* 0x014 */ s32 gt2SendBufferSize;
    /* 0x018 */ s32 gt2RecvBufferSize;
    /* 0x01c */ GPConnection gpConnection;
    /* 0x020 */ void *userData;
    /* 0x024 */ s32 state;
    /* 0x028 */ s32 prevState;
    /* 0x02c */ u8 myAid;
    /* 0x02d */ u8 isClosingAll;
    /* 0x02e */ u16 unk_2e;
    /* 0x030 */ u32 ownProfileId;
    /* 0x034 */ char buddyRequestText[0x20];
    /* 0x054 */ char *gameName;
    /* 0x058 */ char *secretKey;
    /* 0x05c */ DwcDoneCallback loginCallback;
    /* 0x060 */ s32 loginCallbackArg;
    /* 0x064 */ DwcDoneCallback updateCallback;
    /* 0x068 */ s32 updateCallbackArg;
    /* 0x06c */ DwcMatchedCallback matchCallback;
    /* 0x070 */ s32 matchCallbackArg;
    /* 0x074 */ DwcMatchedScCallback serverMatchCallback;
    /* 0x078 */ void *serverMatchCallbackArg;
    /* 0x07c */ DwcConnectionClosedCallback closedCallback;
    /* 0x080 */ s32 closedCallbackArg;
    /* 0x084 */ DwcLoginControl loginControl;
    /* 0x2e8 */ DwcFriendControl friendControl;
    /* 0x33c */ DwcMatchControl matchControl;
    /* 0x7a0 */ u8 netChannelTable[4];
};

#endif
