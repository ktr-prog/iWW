#ifndef NET_DWCMATCHCONTROL_H
#define NET_DWCMATCHCONTROL_H

#include "types.h"


typedef void (*DwcMatchedScCallback)(s32, s32, s32, s32, s32, void *);
typedef void (*DwcNewClientCallback)(s32, void *);
typedef s32 (*DwcEvalCallback)(s32, void *);

#ifndef __cplusplus
typedef struct Unk_ov065_02290814_Sub Unk_ov065_02290814_Sub;
typedef struct DwcNnRequest DwcNnRequest;
typedef struct DwcMatchControl DwcMatchControl;
typedef struct DwcMatchSyncOption DwcMatchSyncOption;
#endif

struct Unk_ov065_02290814_Sub {
    /* 0x00 */ void *transportSocket;
};

struct DwcNnRequest {
    /* 0x00 */ u8 clientIndex;
    /* 0x01 */ u8 retryCount;
    /* 0x02 */ u16 peerPort;
    /* 0x04 */ u32 peerIp;
    /* 0x08 */ u32 cookie;
};

struct DwcMatchControl {
    /* 0x000 */ void *gpConnection;
    /* 0x004 */ Unk_ov065_02290814_Sub *transportSocketPtr;
    /* 0x008 */ void *transportCallbacks;
    /* 0x00c */ u8 connectRetryCount;
    /* 0x00d */ u8 numClients;
    /* 0x00e */ u8 numValidClients;
    /* 0x00f */ u8 unk_0f;
    /* 0x010 */ struct qr2_implementation_s *qr2Object;
    /* 0x014 */ volatile u8 numPlayers;
    /* 0x015 */ volatile u8 matchType;
    /* 0x016 */ u8 maxPlayers;
    /* 0x017 */ u8 hasReservation;
    /* 0x018 */ u8 qr2ShutdownPending;
    /* 0x019 */ u8 unk_19;
    /* 0x01a */ u16 publicPort;
    /* 0x01c */ u32 publicIp;
    /* 0x020 */ u32 reservation;
    /* 0x024 */ u32 memberIps[32];
    /* 0x0a4 */ u16 memberPorts[32];
    /* 0x0e4 */ struct _ServerBrowser *serverBrowser;
    /* 0x0e8 */ s32 queryRetryMode;
    /* 0x0ec */ u32 queryRetryTick;
    /* 0x0f0 */ u32 queryRetryTickHi;
    /* 0x0f4 */ u32 memberProfileIds[32];
    /* 0x174 */ u8 nnRetryCount;
    /* 0x175 */ u8 nnFailCount;
    /* 0x176 */ u16 nnCookieHigh;
    /* 0x178 */ u32 nnLastCookie;
    /* 0x17c */ u32 nnRetryTime;
    /* 0x180 */ u32 nnRetryTimeHi;
    /* 0x184 */ u32 connectWaitTime;
    /* 0x188 */ u32 connectWaitTimeHi;
    /* 0x18c */ DwcNnRequest nnRequest;
    /* 0x198 */ s32 matchState;
    /* 0x19c */ u8 connectOrderIndex;
    /* 0x19d */ u8 friendCursor;
    /* 0x19e */ u8 unk_19e;
    /* 0x19f */ u8 rejoinRetries;
    /* 0x1a0 */ u8 closeState;
    /* 0x1a1 */ u8 unk_1a1;
    /* 0x1a2 */ u8 reservationRetries;
    /* 0x1a3 */ u8 syncRetryCount;
    /* 0x1a4 */ u8 cancelSyncRetryCount;
    /* 0x1a5 */ u8 unk_1a5;
    /* 0x1a6 */ u16 syncWaitMs;
    /* 0x1a8 */ u16 cancelSyncWaitMs;
    /* 0x1aa */ u16 targetServerPort;
    /* 0x1ac */ u32 targetServerIp;
    /* 0x1b0 */ u32 reservationRetryPending;
    /* 0x1b4 */ u32 reservationRetryTick;
    /* 0x1b8 */ u32 reservationRetryTickHi;
    /* 0x1bc */ u32 reservationTimeoutMs;
    /* 0x1c0 */ u32 reservationTick;
    /* 0x1c4 */ u32 reservationTickHi;
    /* 0x1c8 */ u32 syncAckMask;
    /* 0x1cc */ u32 cancelSyncAckMask;
    /* 0x1d0 */ u32 syncSendTime;
    /* 0x1d4 */ u32 syncSendTimeHi;
    /* 0x1d8 */ u32 cancelSyncSendTime;
    /* 0x1dc */ u32 cancelSyncSendTimeHi;
    /* 0x1e0 */ u32 waitStartTime;
    /* 0x1e4 */ u32 waitStartTimeHi;
    /* 0x1e8 */ u32 profileId;
    /* 0x1ec */ u32 serverProfileId;
    /* 0x1f0 */ u32 targetProfileId;
    /* 0x1f4 */ u32 resultProfileId;
    /* 0x1f8 */ u32 memberConnectIps[32];
    /* 0x278 */ u16 memberConnectPorts[32];
    /* 0x2b8 */ u8 aids[0x20];
    /* 0x2d8 */ u32 validAidMask;
    /* 0x2dc */ char *gameName;
    /* 0x2e0 */ char *secretKey;
    /* 0x2e4 */ struct DwcFriendData *friendList;
    /* 0x2e8 */ u32 friendCount;
    /* 0x2ec */ u8 friendIndices[0x40];
    /* 0x32c */ s32 friendIndexCount;
    /* 0x330 */ u32 memberListCount;
    /* 0x334 */ u32 memberListSender;
    /* 0x338 */ u32 memberListPids[0x1f];
    /* 0x3b4 */ u8 cmdType;
    /* 0x3b5 */ u8 cmdRetryCount;
    /* 0x3b6 */ u16 cmdPort;
    /* 0x3b8 */ u32 cmdIp;
    /* 0x3bc */ u32 cmdArgs[32];
    /* 0x43c */ u32 cmdProfileId;
    /* 0x440 */ u32 cmdArgCount;
    /* 0x444 */ u32 cmdTime;
    /* 0x448 */ u32 cmdTimeHi;
    /* 0x44c */ DwcMatchedScCallback matchCallback;
    /* 0x450 */ void *matchCallbackParam;
    /* 0x454 */ DwcNewClientCallback newClientCallback;
    /* 0x458 */ void *newClientCallbackParam;
    /* 0x45c */ DwcEvalCallback evalCallback;
    /* 0x460 */ void *evalCallbackParam;
};

struct DwcMatchSyncOption {
    /* 0x00 */ u8 isEnabled;
    /* 0x01 */ u8 minPlayers;
    /* 0x02 */ u8 retryCount;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u32 timeoutMs;
    /* 0x08 */ u32 answeredAidMask;
    /* 0x0c */ u32 acceptedAidMask;
    /* 0x10 */ u64 startTime;
    /* 0x18 */ u64 lastSendTime;
};

#endif
